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
#include "GameGenProject.h"
#include "DebuggerTest.h"
#include "JumpBumpGame.h"

int main(void) 
{
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
	//Test::Test3D test;
	//GameGenProject test;
	//DebuggerTest test;
	JumpBumpGame test;
	test.Run();

	return 0;
}