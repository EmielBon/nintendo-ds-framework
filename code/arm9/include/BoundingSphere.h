/**
 * \class BoundingSphere
 * \brief Defines a sphere.
 * \todo Support for the Contains() method, like in BoundingBox
 */

#pragma once

#include "Vec3.h"
#include "Mat.h"

namespace Framework
{
	struct BoundingSphere
	{
	public:

		/** \brief Creates a new default instance of BoundingSphere. */
		BoundingSphere() = default;

		/** \brief Creates a new instance of BoundingSphere. 
		 *  \param center Center point of the sphere.
		 *  \param radius Radius of the sphere. */
		BoundingSphere(Vector3 center, fx12 radius);

		/** \brief Checks whether the current BoundingSphere intersects with a specified BoundingSphere. 
		 *  \param other The BoundingSphere to check for intersection with the current BoundingSphere.
		 *  \returns \e true if the BoundingSpheres intersect; \e false otherwise. 
		 *  \todo Support for other bounding volumes. */
		bool Intersects(const BoundingSphere &other);

		/** \brief Translates and scales the BoundingSphere using a given Matrix. 
		 *  \param matrix A transformation matrix that might include translation, rotation, or uniform scaling.
		 *  \returns The transformed BoundingSphere.
		 *
		 *  Note that BoundingSphere.Transform will not return correct results if there are non-uniform scaling, 
		 *  shears, or other unusual transforms in this transformation matrix. This is because there is no way to shear
		 *  or non-uniformly scale a sphere. Such an operation would cause the sphere to lose its shape as a sphere. */
		BoundingSphere Transform(const Matrix &matrix);

		/** \brief Creates the smallest BoundingSphere that can contain a specified BoundingBox.
		 *  \param box The BoundingBox to create the BoundingSphere from.
		 *  \returns The created BoundingSphere. 
		 *  \bug Despite the description, this actually returns the smallest bounding sphere contained by the box! */
		static BoundingSphere CreateFromBoundingBox(const BoundingBox &box);

	public:

		Vector3 Center;
		fx12 Radius;
	};
}