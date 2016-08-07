#include "game/BoundingSphere.h"
#include "core/types.h"
#include "util/Vec3.h"
#include "util/Mat.h"
#include "game/BoundingBox.h"
#include "debug/Logging.h"

namespace Framework
{
	//-------------------------------------------------------------------------------------------------
	BoundingSphere::BoundingSphere(Vector3 c, fx12 r)
	{
		Center = c;
		Radius = r;
	}

	//-------------------------------------------------------------------------------------------------
	bool BoundingSphere::Intersects(const BoundingSphere &other)
	{
		return (Center - other.Center).LengthSquared() < (Radius + other.Radius)*(Radius + other.Radius);
	}

	//-------------------------------------------------------------------------------------------------
	BoundingSphere BoundingSphere::Transform(const Matrix &m)
	{
		auto translation = New<Vector3>();
		auto scale = New<Vector3>();
		m.Decompose(scale, nullptr, translation);
		return BoundingSphere(Center + *translation, Radius * scale->x);
	}

	//-------------------------------------------------------------------------------------------------
	BoundingSphere BoundingSphere::CreateFromBoundingBox(const BoundingBox &box)
	{
		BoundingSphere sphere;
		sphere.Center = (box.Min + box.Max) * 0.5f;
		sphere.Radius = (box.Max - sphere.Center).Length();
		return sphere;
	}
}