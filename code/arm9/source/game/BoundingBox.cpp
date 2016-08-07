#include "game/BoundingBox.h"
#include "util/Mat.h"
#include "debug/Debug.h"

namespace Framework
{
	//-------------------------------------------------------------------------------------------------
	ContainmentType BoundingBox::Contains(const BoundingBox &other) const
	{
		if(other.Min.x > Max.x ||				
		   other.Max.x < Min.x ||
		   other.Min.y > Max.y ||
		   other.Max.y < Min.y ||
		   other.Min.z > Max.z ||
		   other.Max.z < Min.z)
		   		   return ContainmentType::Disjoint;
		
		if(other.Min.x >= Min.x ||
		   other.Max.x <= Max.x ||
		   other.Min.y >= Min.y ||
		   other.Max.y <= Max.y ||
		   other.Min.z >= Min.z ||
		   other.Max.z <= Max.z)
		   return ContainmentType::Contains;
		
		return ContainmentType::Intersects;
	}

	//-------------------------------------------------------------------------------------------------
	ContainmentType BoundingBox::Contains(const Vector3 &point) const
	{
		if (point.x >= Min.x &&
			point.x <= Max.x &&
			point.y >= Min.y &&
			point.y <= Max.y &&
			point.z >= Min.z &&
			point.z <= Max.z)
			return ContainmentType::Contains;

		return ContainmentType::Disjoint;
	}

	//-------------------------------------------------------------------------------------------------
	BoundingBox BoundingBox::Transform(const Matrix &m) const
	{
		auto translation = New<Vector3>();
		auto scale = New<Vector3>();
		m.Decompose(scale, nullptr, translation);

		Array<fx12, 16> trans = {
			scale->x,        0,        0, translation->x,
				   0, scale->y,        0, translation->y,
				   0,        0, scale->z, translation->z,
				   0,        0,        0,              1,
		};
		return BoundingBox(Min.Transform(trans), Max.Transform(trans));
	}
}
