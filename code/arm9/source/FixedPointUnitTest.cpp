#include "FixedPointUnitTest.h"
#include "Debug.h"
#include "Framework.h"

namespace Test
{
	using namespace Debug;
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	void FixedPointUnitTest::Initialize()
	{
		// Constructor overflow
		//fx12 x = 1234567.1234f;
		//fx16 x = 123456.1234f;
		
		// Multiplication overflow
		/*fx12 x = 262144.0f;
		fx12 y = 2.0f;
		fx12 z = x * y; */

		// Conversion
		//fx16 x = fx12(123.123f);
		//CRASH((float)x);

		// Multiplication correctness
		/*fx12 x = 0.10f;
		x *= 2.5f;
		CRASH((float)x);*/

		// Division correctness
		/*fx12 x = 25.25f;
		x /= 2.5f;
		CRASH((float)x);*/
	}
}