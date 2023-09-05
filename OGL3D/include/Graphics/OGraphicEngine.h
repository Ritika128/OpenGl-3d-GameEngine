#pragma once
#include <OGL3D/Math/OVec4.h>

class OGraphicsEngine
{
public:
	OGraphicsEngine();
	~OGraphicsEngine();

public:
	void clear(const OVec4& color);
};
