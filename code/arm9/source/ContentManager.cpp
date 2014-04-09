#include "ContentManager.h"

#include "StreamReader.h"
#include "StringHelper.h"
#include "Debug.h"
#include "Size.h"

// Stuff you can load
#include "TiledBackground.h"
#include "MapResource.h"
#include "TileSet16.h"
#include "TileSet256.h"
#include "Palette.h"
#include "CollisionMap.h"
#include "Path.h"
#include "Font.h"
#include "Scene.h"

#include "Vertex.h"
#include "Texture.h"
#include "Model.h"
#include "ModelMesh.h"
#include "ModelMeshPart.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BasicEffect.h"
#include "TilesManager.h"
#include "Sprite.h"
#include "SpriteSet.h"
#include "SpriteSubImage.h"

namespace Framework
{
	using namespace std;
	using namespace LLR;
	using namespace Util;
	using namespace Debug;
	using namespace Graphics;
	using namespace FileSystem;
	using namespace Framework;
	using namespace Framework2D;

	// Todo: code duplications in TileSet16 and TileSet256
	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<TileSet16> ContentManager::LoadResourceFromStream(const String &resourceName, FileStream &fs)
	{
		struct TileSetFileHeader
		{
			byte Width;
			byte Height;
			byte TileCount;
		};

		auto header = fs.ReadHeader<TileSetFileHeader>();
		auto tiles = New<TileSet16>();
		tiles->tileSize.Width  = header.Width;
		tiles->tileSize.Height = header.Height;
		tiles->AddTiles(*(fs.ReadAll<Tile4bpp>()));

		ASSERT(tiles->tileSize.Width % 8 == 0 || tiles->tileSize.Height % 8 == 0, "Error: Invalid tile size");
		
		TilesManager::AddTileSet(tiles);

		return tiles;
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<TileSet256> ContentManager::LoadResourceFromStream(const String &resourceName, FileStream &fs)
	{
		struct TileSetFileHeader
		{
			byte Width;
			byte Height;
			byte TileCount;
		};

		auto header = fs.ReadHeader<TileSetFileHeader>();
		auto tiles = New<TileSet256>();
		tiles->AddTiles(*(fs.ReadAll<Tile8bpp>()));
		tiles->tileSize.Width  = header.Width;
		tiles->tileSize.Height = header.Height;
		//tiles->Transparent = header.Transparent;

		ASSERT(tiles->tileSize.Width % 8 == 0 || tiles->tileSize.Height % 8 == 0, "Error: Invalid tile size");

		TilesManager::AddTileSet(tiles);

		return tiles;
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<Font> ContentManager::LoadResourceFromStream(const String &resourceName, FileStream &fs)
	{
		return static_pointer_cast<Font>( LoadResourceFromStream<TileSet16>(resourceName, fs) );
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<TiledBackground> ContentManager::LoadResourceFromStream(const String &resourceName, FileStream &fs)
	{
		StreamReader reader(&fs);
		auto lines = reader.ReadToEnd();

		Size              mapSize;
		Ptr<MapResource>  mapData;
		Ptr<CollisionMap> collisionMap;
		Ptr<TileSet256>   tileSet;

		for(u32 i = 0; i < lines.size(); ++i)
		{
			auto tokens = StringHelper::Split(lines[i], ' ');

			if (tokens[0] == "")
				continue;

			String type     = tokens[0];
			String fileName = tokens[1];

			if (fileName == "none" || fileName == "")
				continue;

			if (type == "s")
			{
				auto sizeStr = StringHelper::Split(tokens[1], 'x');
				int width    = StringHelper::ParseInt(sizeStr[0]);
				int height   = StringHelper::ParseInt(sizeStr[1]);
				mapSize = Size(width, height);
			}
			if (type == "d") mapData      = ContentManager::Load<MapResource>(fileName);
			if (type == "c") collisionMap = ContentManager::Load<CollisionMap>(fileName);
			// \todo Support for loading more than one tile set per map
			if (type == "t") tileSet      = ContentManager::Load<TileSet256>(fileName);
			if (type == "p") tileSet->SetPalette( ContentManager::Load<Palette>(fileName) );
		}

		Ptr<TiledBackground> map = New<TiledBackground>(mapSize.Width, mapSize.Height);
		map->CollisionMap = collisionMap;

		auto& screenBlockEntries = mapData->ScreenBlockEntries;

		for(u32 i = 0; i < screenBlockEntries.size(); ++i)
		{
			ScreenBlockEntry screenBlockEntry = screenBlockEntries[i];

			MapTile mapTile;
			mapTile.TileIdentifier = TilesManager::IdentifierForTile(tileSet, screenBlockEntry.TileIndex());
			mapTile.PaletteIndex   = screenBlockEntry.PaletteIndex();
			mapTile.FlipHorizontal = screenBlockEntry.IsFlippedHorizontal();
			mapTile.FlipVertical   = screenBlockEntry.IsFlippedHorizontal();

			map->SetTile(i, mapTile);
		}

		return map;
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<SpriteSet> ContentManager::LoadResourceFromStream(const String &resourceName, FileStream &fs)
	{
		StreamReader reader(&fs);
		auto lines = reader.ReadToEnd();

		Size              size;
		Ptr<TileSet256>   tileSet;
		auto spriteSet = New<SpriteSet>();

		for (u32 i = 0; i < lines.size(); ++i)
		{
			auto tokens = StringHelper::Split(lines[i], ' ');

			if (tokens[0] == "")
				continue;

			String type = tokens[0];
			String fileName = tokens[1];

			if (fileName == "none" || fileName == "")
				continue;

			if (type == "s")
			{
				auto sizeStr = StringHelper::Split(tokens[1], 'x');
				int width = StringHelper::ParseInt(sizeStr[0]);
				int height = StringHelper::ParseInt(sizeStr[1]);
				size = Size(width / 8, height / 8);
			}
			// \todo Support for loading more than one tile set per map
			if (type == "t") tileSet = ContentManager::Load<TileSet256>(fileName);
			if (type == "p") tileSet->SetPalette(ContentManager::Load<Palette>(fileName));
			if (type == "i")
			{
				String name = tokens[1];
				List<SpriteSubImage> subImages;
				for (int i = 2; i < tokens.size(); ++i)
				{
					SpriteSubImage subImage(size.Width, size.Height);
					u32 tilesetBaseIdentifier = TilesManager::IdentifierForTileSet(tileSet);
					int tileCount = size.Width * size.Height;
					for (int j = 0; j < tileCount; ++j)
						subImage.TileIdentifiers[j] = tilesetBaseIdentifier + StringHelper::ParseInt(tokens[i]) * tileCount + j;

					subImages.push_back(subImage);
				}
				auto sprite = New<Sprite>(subImages);
				spriteSet->Sprites[name] = sprite;
			}
		}

		return spriteSet;
	}

	//------------------------------------------------------------------------------------------------- 
	// \todo What would be better is a custom load function where you can specify the header and content type. 
	// MapResource's purpose is not for loading, it just happens to contain a list op ScreenBlockEntries
	template<>
	Ptr<MapResource> ContentManager::LoadResourceFromStream(const String &resourceName, FileStream &fs)
	{
		struct MapFileHeader
		{
			byte Width;
			byte Height;
		};

		auto header = fs.ReadHeader<MapFileHeader>();
		auto map = New<MapResource>(header.Width, header.Height);
		map->ScreenBlockEntries = *(fs.ReadAll<ScreenBlockEntry>());

		return map;
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<Palette> ContentManager::LoadResourceFromStream(const String &resourceName, FileStream &fs)
	{
		Ptr<Palette> palette = New<Palette>();
		palette->Entries = *(fs.ReadAll<u16>());
		return palette;
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<CollisionMap> ContentManager::LoadResourceFromStream(const String &resourceName, FileStream &fs)
	{
		struct CollisionMapFileHeader
		{
			byte Width;
			byte Height;
		};

		auto header = fs.ReadHeader<CollisionMapFileHeader>();
		auto colmap = New<CollisionMap>(header.Width, header.Height);
		colmap->Entries = *(fs.ReadAll<u8>());

		return colmap;
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<Path> ContentManager::LoadResourceFromStream(const String &resourceName, FileStream &fs)
	{
		auto path = New<Path>();
		auto data = *(fs.ReadAll<u16>());
		int size = data.size();

		ASSERT(size % 2 == 0, "Error: Incorrect path file");
		
		for(int i = 0; i < size; i+=2)
			path->Add(data[i], data[i+1]); // Todo: check for valid coordinates

		return path;
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<Model> ContentManager::LoadResourceFromStream(const String &resourceName, FileStream &fs)
	{
		Ptr<Model> model = New<Model>();

		StreamReader reader(&fs);

		auto lines = reader.ReadToEnd();
		for(u32 i = 0; i < lines.size(); ++i)
		{
			auto tokens = StringHelper::Split(lines[i], ' ');
			
			if (tokens[0] == "")
				continue;

			auto mesh = ContentManager::Load<ModelMesh>(tokens[0]);
			String textureName = (tokens.size() == 2) ? tokens[1] : "no_texture";
			
			if (textureName == "no_texture")
			{
				LOG_WARNING("- Texture missing");
			}

			mesh->MeshParts[0].Effect->Texture = ContentManager::Load<Texture>(textureName);
			model->AddMesh(*mesh);
		}

		return model;
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<ModelMesh> ContentManager::LoadResourceFromStream(const String &resourceName, FileStream &fs)
	{
		struct MeshFileHeader
		{
			int VertexCount;
		};

		auto header = fs.ReadHeader<MeshFileHeader>();
		auto mesh = New<ModelMesh>();
		
		ModelMeshPart meshPart;
		
		List<VertexF> vertices = *(fs.Read<VertexF>(header.VertexCount));
		for(u32 i = 0; i < vertices.size(); ++i)
		{
			Vertex v;
			v.Position.x = vertices[i].Position.x;
			v.Position.y = vertices[i].Position.y;
			v.Position.z = vertices[i].Position.z;

			v.Normal.x = vertices[i].Normal.x;
			v.Normal.y = vertices[i].Normal.y;
			v.Normal.z = vertices[i].Normal.z;

			v.TextureCoordinates.x = vertices[i].TextureCoordinates.x;
			v.TextureCoordinates.y = vertices[i].TextureCoordinates.y;

			meshPart.Vertices.push_back(v);
		}
		//meshPart.Vertices = *(fs.Read<VertexF>(header.VertexCount));
		meshPart.Indices = *(fs.ReadAll<u16>());

		for(u32 i = 0; i < meshPart.Vertices.size(); ++i)
		{
			Vector3 &normal = meshPart.Vertices[i].Normal;
			normal = normal.Normalize(); 
		}

		meshPart.VertexBuffer->SetData(meshPart.Vertices);
		meshPart.IndexBuffer->SetData(meshPart.Indices);

		mesh->AddPart(meshPart);

		return mesh;
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<Texture> ContentManager::LoadResourceFromStream(const String &resourceName, FileStream &fs)
	{
		struct TextureFileHeader
		{
			int Width;
			int Height;
		};

		auto header = fs.ReadHeader<TextureFileHeader>();
		auto texture = New<Texture>(header.Width, header.Height);
		texture->Pixels = *(fs.ReadAll<u16>());
		
		return texture;
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<Scene> ContentManager::LoadResourceFromStream(const String &resourceName, FileStream &fs)
	{
		Ptr<Scene> scene = New<Scene>();

		StreamReader reader(&fs);

		auto lines = reader.ReadToEnd();
		for(u32 i = 0; i < lines.size(); ++i)
		{
			auto tokens = StringHelper::Split(lines[i], ' ');
			
			if (tokens[0] == "")
				continue;

			if (StringHelper::HasPrefix(tokens[0], "//"))
				continue;

			auto model = ContentManager::Load<Model>(tokens[0]);
			
			Matrix translation = Matrix::CreateTranslation( StringHelper::ParseFloat(tokens[1]), StringHelper::ParseFloat(tokens[2]), StringHelper::ParseFloat(tokens[3]));
			Matrix scale = Matrix::CreateScale( StringHelper::ParseFloat(tokens[4]), StringHelper::ParseFloat(tokens[5]), StringHelper::ParseFloat(tokens[6]) );
			Matrix rotX = Matrix::CreateRotationX(StringHelper::ParseFloat(tokens[7]));
			Matrix rotY = Matrix::CreateRotationY(StringHelper::ParseFloat(tokens[8]));
			Matrix rotZ = Matrix::CreateRotationZ(StringHelper::ParseFloat(tokens[9]));
			bool isSolid = StringHelper::ParseBool(tokens[10]);
			Matrix world = scale * rotX * rotY * rotZ * translation;
			
			auto object = New<SceneObject>(model, world, isSolid);

			scene->AddObject(object);
		}

		return scene;
	}

	//-------------------------------------------------------------------------------------------------
	/*void ContentManager::BeginProfiling()
	{
		profiler.Begin();
	}

	//-------------------------------------------------------------------------------------------------
	void ContentManager::EndProfiling(const String &typeName, const String &resourceName)
	{
		profiler.End();
		String time = profiler.GetElapsedTimeAsString();
		LOG("Loaded " << typeName << " " << resourceName << " (" << time << ")" );
	}*/
}