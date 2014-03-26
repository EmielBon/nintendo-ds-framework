/**
 * \class BoundingBox
 * \brief Defines an axis-aligned box-shaped 3D volume
 * \todo Support for the Intersects() method, like in BoundingSphere
 */

#pragma once

#include "types.h"
#include "ContainmentType.h"
#include "Vec3.h"

namespace Framework
{
	struct BoundingBox
	{
	public:
		
		/** \brief Creates a default instance of BoundingBox. */
		BoundingBox() = default;
		
		/** \brief Creates an instance of BoundingBox.
		 *  \param pMin The minimum point the BoundingBox includes.
		 *  \param pMax The maximum point the BoundingBox includes. */
		BoundingBox(const Vector3 &pMin, const Vector3 &pMax);
		
		/** \brief Tests whether the BoundingBox contains another BoundingBox.
		 *  \param box The BoundingBox to test for overlap.
		 *  \returns Enumeration indicating the extent of overlap.
		 *  \todo Add support for other bounding volumes. */
		ContainmentType Contains(const BoundingBox &box) const;
		
		/** \brief Translates and scales the BoundingBox using a given Matrix.
		 *  \param matrix A transformation matrix that might include translation or scaling.
		 *  \returns The transformed BoundingBox.
		 *
		 *  Note that BoundingBox.Transform will not return correct results if there are rotations, shears, or other 
		 *  unusual transforms in this transformation matrix. */
		BoundingBox Transform(const Matrix &matrix);

	public:
		
		Vector3 Min, Max;
	};

	//-------------------------------------------------------------------------------------------------
	inline BoundingBox::BoundingBox(const Vector3 &pMin, const Vector3 &pMax) : Min(pMin), Max(pMax)
	{

	}
}