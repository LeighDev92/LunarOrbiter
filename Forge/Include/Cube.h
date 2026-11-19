#pragma once
#include "Mesh.h"

namespace Forge
{
	class FORGE_API Cube : public Mesh
	{
	public:
		Cube(FTransform transform = FTransform());
	};
}