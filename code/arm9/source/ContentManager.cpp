#include "ContentManager.h"

#include "StreamReader.h"
#include "StringHelper.h"
#include "Debug.h"
#include "Size.h"

// Stuff you can load
#include "TiledBackground.h"
#include "TileSet.h"
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
#include "Sprite.h"

namespace Framework
{
	using namespace std;
	using namespace Util;
	using namespace Debug;
	using namespace Graphics;
	using namespace FileSystem;
	using namespace Framework;
	using namespace Framework2D;
	using namespace Framework3D;

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<TileSet> ContentManager::LoadResourceFromStream(FileStream &fs)
	{
		struct TileSetFileHeader
		{
			int TileWidth;
			int TileHeight;
		};

		TileSetFileHeader header;
		fs.Read(&header);

		sassert(header.TileWidth % 8 == 0 && header.TileHeight % 8 == 0, "Error: Invalid tile size");

		auto tileSet = New<TileSet>(header.TileWidth, header.TileHeight);

		Tile16bpp rawTile;
		size_t tilesRead = fs.Read(&rawTile);

		while (tilesRead > 0)
		{
			auto tile = Tile(rawTile);
			tileSet->AddTile(tile);
			tilesRead = fs.Read(&rawTile);
		}

		return tileSet;
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<Font> ContentManager::LoadResourceFromStream(FileStream &fs)
	{
		return static_pointer_cast<Font>( LoadResourceFromStream<TileSet>(fs) );
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<TiledBackground> ContentManager::LoadResourceFromStream(FileStream &fs)
	{
		StreamReader reader(fs);
		auto lines = reader.ReadToEnd();

		Size                   mapSize;
		List<ScreenBlockEntry> screenBlockEntries;
		Ptr<CollisionMap>      collisionMap;
		Ptr<TileSet>           tileSet;
		Ptr<Palette>           palette;

		for(auto &line : lines)
		{
			auto tokens = StringHelper::Split(line, ' ');

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
			if (type == "d")
			{
				auto dataFileStream = FileStream(fileName);
				dataFileStream.Open("/" + fileName + ".bin");
				screenBlockEntries = dataFileStream.ReadAll<ScreenBlockEntry>();
			}
			// \todo Support for loading more than one tile set per map
			if (type == "t") tileSet = ContentManager::Load<TileSet>(fileName);
		}

		auto tiledBackground = New<TiledBackground>(mapSize.Width, mapSize.Height, 8);

		for(u32 i = 0; i < screenBlockEntries.size(); ++i)
		{
			auto screenBlockEntry = screenBlockEntries[i];
			auto tile = &(tileSet->Tiles[screenBlockEntry.TileIndex()]);
			sassert(tile, "Loaded tile was null");
			tiledBackground->SetTile(i, tile);
			tiledBackground->TileParameters[i] = screenBlockEntry;
		}

		return tiledBackground;
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<SpriteSet> ContentManager::LoadResourceFromStream(FileStream &fs)
	{
		StreamReader reader(fs);
		auto lines = reader.ReadToEnd();

		//sassert(false, "%s\n%s\n%s\n%s\n%s\n%s\n%s", lines[0].c_str(), lines[1].c_str(), lines[2].c_str(), lines[3].c_str(), lines[4].c_str(), lines[5].c_str(), lines[6].c_str());

		Size         size;
		Ptr<TileSet> tileSet;
		auto spriteSet = New<SpriteSet>();

		for (u32 i = 0; i < lines.size(); ++i)
		{
			auto tokens = StringHelper::Split(lines[i], ' ');

			if (tokens[0] == "") {
				continue;
			}

			String type = tokens[0];
			String fileName = tokens[1];

			if (fileName == "none" || fileName == "") {
				continue;
			}

			if (type == "s") {
				auto sizeStr = StringHelper::Split(tokens[1], 'x');
				int width = StringHelper::ParseInt(sizeStr[0]);
				int height = StringHelper::ParseInt(sizeStr[1]);
				size = Size(width / 8, height / 8);
			} else if (type == "t") {
				tileSet = ContentManager::Load<TileSet>(fileName);
			} else if (type == "i") {
				String name = tokens[1];
				List<TiledImage> subImages;
				int tileCount = size.Width * size.Height;
				for (u32 i = 2; i < tokens.size(); ++i)
				{
					TiledImage subImage(size.Width, size.Height, 8);
					for (int j = 0; j < tileCount; ++j)
					{
						u32 subImageBaseIdentifier = StringHelper::ParseInt(tokens[i]) * tileCount;
						subImage.Tiles[j] = &tileSet->Tiles[subImageBaseIdentifier + j];
					}
					subImages.push_back(subImage);
				}
				(*spriteSet)[name] = new Sprite(subImages);
			}
		}

		return spriteSet;
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<Path> ContentManager::LoadResourceFromStream(FileStream &fs)
	{
		auto path = New<Path>();
		auto wayPoints = fs.ReadAll<uint16_t>();

		ASSERT(wayPoints.size() % 2 == 0, "Error: Incorrect path file");
		
		for(int i = 0; i < (int)wayPoints.size(); i+=2) {
			path->Add(wayPoints[i], wayPoints[i+1]); // Todo: check for valid coordinates
		}

		return path;
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<Model> ContentManager::LoadResourceFromStream(FileStream &fs)
	{
		auto model = New<Model>();

		StreamReader reader(fs);

		auto lines = reader.ReadToEnd();
		for(auto &line : lines)
		{
			auto tokens = StringHelper::Split(line, ' ');
			
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
	Ptr<ModelMesh> ContentManager::LoadResourceFromStream(FileStream &fs)
	{
		struct MeshFileHeader
		{
			int VertexCount;
		};

		MeshFileHeader header;
		fs.Read(&header);
		
		ModelMeshPart meshPart;

		for (int i = 0; i < header.VertexCount; ++i)
		{
			VertexF vertexF;
			fs.Read(&vertexF);
			auto vertex = (Vertex) vertexF;
			meshPart.Vertices.push_back(vertex);
		}

		meshPart.Indices = fs.ReadAll<uint16_t>();
		meshPart.VertexBuffer->SetData(meshPart.Vertices);
		meshPart.IndexBuffer->SetData(meshPart.Indices);

		auto mesh = New<ModelMesh>();
		mesh->AddPart(meshPart);
		return mesh;
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<Texture> ContentManager::LoadResourceFromStream(FileStream &fs)
	{
		struct TextureFileHeader
		{
			int Width;
			int Height;
		};

		TextureFileHeader header;
		fs.Read(&header);

		int width = header.Width;
		int height = header.Height;

		auto texture = New<Texture>(width, height);
		texture->Pixels = fs.ReadAll<uint16_t>();

		sassert((int)texture->Pixels.size() == width * height, "File size does not match texture dimensions");

		return texture;
	}

	//-------------------------------------------------------------------------------------------------
	template<>
	Ptr<Scene> ContentManager::LoadResourceFromStream(FileStream &fs)
	{
		Ptr<Scene> scene = New<Scene>();

		StreamReader reader(fs);

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
