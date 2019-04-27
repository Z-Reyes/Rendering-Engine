#pragma once
#include "RenderableObject.h"
#include "lightStruct.h"
class lightMarker : public RenderableObject {

public:
	lightMarker();
	~lightMarker();
	void OnUpdate();
};