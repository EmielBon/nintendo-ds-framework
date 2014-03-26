/**
 * \enum ContainmentType
 * \brief Indicates the extent to which bounding volumes intersect or contain one another.
 */

#pragma once

namespace Framework
{
	enum class ContainmentType
	{ 
		/// Indicates that one bounding volume completely contains the other.
		Contains,
		/// Indicates there is no overlap between the bounding volumes.
		Disjoint, 
		/// Indicates that the bounding volumes partially overlap.
		Intersects, 
	};
}