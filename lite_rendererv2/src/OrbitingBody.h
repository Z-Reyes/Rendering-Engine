#pragma once
#include "RenderableObject.h"

class OrbitingBody : public RenderableObject {
public:
	OrbitingBody(bool hp, bool usePR, bool pTransFirst, bool selfTransFirst);
	OrbitingBody();
	~OrbitingBody();
	void OnUpdate();
	float orbitalAdditive;
	float radiusMulti;

private:
	float orbitalValue;
};