#pragma once

#include <nds/ndstypes.h>
#include <array>
#include <string>
#include <cstring>
#include <vector>
#include <memory>
#include <set>
#include <list>
#include <map>
#include <utility>
#include <tuple>
#include <stack>
#include <sstream>
#include <initializer_list>
#include "fixed.h"

// Template aliases
template<class T> using Ptr = std::shared_ptr<T>;
template<class T> using WeakPtr = std::weak_ptr<T>;
template<class T> using List = std::vector<T>;
template<class T> using Set = std::set<T>;
template<class T> using LinkedList = std::list<T>;
template<class T> using Stack = std::stack<T>;
template<class... T> using Tuple = std::tuple<T...>;
template<class T, int N> using Array = std::array<T, N>;
template<class T, class U> using TreeMap = std::map<T, U>;

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

/// Forward declarations
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


/// Aliases
using String = std::string;
using StringBuilder = std::stringstream;
using fx4 = fixed<4>;
using fx8 = fixed<8>;
using fx12 = fixed<12>;
using fx16 = fixed<16>;
using fx24 = fixed<24>;

namespace Framework
{
	using Matrix  = Mat<fx12>;
	using Point   = Vec2<int>;
	using Vector2 = Vec2<fx12>;
	using Vector3 = Vec3<fx12>;
}

// Defines
#define New        std::make_shared
#define MakePair   std::make_pair
#define MakeTuple  std::make_tuple

#define finline __attribute__((always_inline)) inline

template<typename T, typename U>
inline static bool IsOfType(Ptr<U> x)
{
	return (bool)std::dynamic_pointer_cast<T>(x);
}

#ifndef NULL
	#define NULL 0
#endif
