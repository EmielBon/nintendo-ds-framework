#pragma once

#include "CoreTypes.h"
#include <nds/arm9/sprite.h>

#define IMPLIES(p, q) (!(p) || (q))

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
	class Sprite;
	class Palette;
	class Background;
	class TextRenderer;
	class Font;
	class GraphicsDevice;
	class Map;
	class ScreenBlockEntry;
	
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

	using TileParameters = ScreenBlockEntry;
	using SpriteSet = Dictionary<String, Sprite*>;
	using SpriteResource = List<SpriteEntry>;
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
	using Matrix   = Mat<fx12>;
	using Point    = Vec2<int>;
	using Vector2  = Vec2<fx12>;
	using Vector2b = Vec2<char>;
	using Vector2s = Vec2<short>;
	using Vector2i = Vec2<int>;
	using Vector2f = Vec2<float>;
	using Vector2  = Vec2<fx12>;
	using Vector3  = Vec3<fx12>;
	using Vector3b = Vec3<char>;
	using Vector3s = Vec3<short>;
	using Vector3i = Vec3<int>;
	using Vector3f = Vec3<float>;

	using GameComponentCollection = Set<GameComponent *>;
}
