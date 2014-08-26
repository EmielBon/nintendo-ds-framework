#pragma once

#include "CoreTypes.h"

/// Forward declarations

namespace Framework
{
	struct BoundingBox;
	struct BoundingSphere;
	struct Color;

	template<class T> class Mat;
	template<class T> class Vec2;
	template<class T> class Vec3;
	
	class Game;
	class GameTime;
	class GameComponent;
	class DrawableGameComponent;
	class GraphicsDeviceManager;
	class IGameHost;
}

namespace Graphics
{
	using namespace Framework;

	class Tile;
	class TileSet;
	class TileSet16;
	class TileSet256;
	class TiledBackground;
	class Sprite;
	class Palette;
	class Background;
	class TextRenderer;
	class Font;
	class GraphicsDevice;
	class Map;
	class SpriteSet;

	class TileMemory;
	class BackgroundMemory;
	class SpriteMemory;
	class PaletteMemory;
	class TextureMemory;
	class Memory2D;

	class Model;
	class Camera;
	
	class Vertex;
	class Texture;
	class BasicEffect;
	class GraphicsDevice;
	class VertexBuffer;
	class IndexBuffer;
}

namespace FileSystem
{
	class FileStream;
}

namespace Framework2D
{
	using namespace Framework;

	class Room;
	class CollisionMap;
}

namespace Framework3D
{
	using namespace Framework;
	using namespace Graphics;

	class FlyingCamera;
	class GameCamera;
	class Scene;
}

namespace Input
{

}

namespace LLR
{
	struct MapResource;
	struct SpriteResource;
}

namespace System
{
	class Console;
	struct TimeSpan;
}

namespace Debug
{
	class DebugUI;
	class FPSCounter;
	class Log;
	class LogEntry;
	struct Timer;
}

namespace Test
{
	using namespace Framework;
	using namespace Graphics;
}

namespace Util
{
	class IActionListener;
}

namespace Framework
{
	using Matrix  = Mat<fx12>;
	using Point   = Vec2<int>;
	using Vector2 = Vec2<fx12>;
	using Vector3 = Vec3<fx12>;
}
