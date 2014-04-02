#include "MatrixPerformanceTest.h"
#include "Debug.h"
#include "Framework.h"

namespace Test
{
	using namespace Debug;
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	void MatrixPerformanceTest::Initialize()
	{
		auto timer1 = Timer::Start();
		int i = 0;
		Matrix mat1( Matrix::Identity());
		while (i++ < 10000)
		{
			mat1 = std::move(Matrix::Identity() * Matrix::Identity());
		}
		timer1->Stop();
		
		auto timer2 = Timer::Start();
		int j = 0;
		Matrix mat2 = Matrix::Identity();
		while (j++ < 10000)
		{
			Matrix m = Matrix::Identity() * Matrix::Identity();
			mat2 = std::move(m);
		}
		timer2->Stop();
		
		CRASH("Timer 1: " << timer1->GetTimeNanoSeconds() << " | Timer 2: " << timer2->GetTimeNanoSeconds());
	}
}