#include "Test2D.h"
#include "Test3D.h"
#include "ConsoleTest.h"
#include "DebugUITest.h"
#include "PaletteTest.h"
#include "TextRenderingTest.h"
#include "EfficientVectorsTest.h"
#include "TimerTest.h"
#include "ProfilingTest.h"
#include "MatrixPerformanceTest.h"
#include "FixedPointUnitTest.h"

int main(void) 
{
	Test::Test2D test;
	//Test::Test3D test;
	//Test::CollisionTest test;
	//Test::ConsoleTest test;
	//Test::DebugUITest test;
	//Test::PaletteTest test;
	//Test::TextRenderingTest test;
	//Test::EVTest test;
	//Test::TimerTest test;
	//Test::SpriteTest test;
	//Test::ProfilingTest test;
	//Test::MatrixPerformanceTest test;
	//Test::FixedPointUnitTest test;

	test.Run();

	return 0;
}