#pragma once

#include "WorldTransform.h"
#include"Mesh.h"

namespace Collision
{
	bool GetBoxCollision(Vector2 obj1, Vector2 obj1SIZE, Vector2 obj2, Vector2 obj2SIZE);
}