#pragma once
#include <iostream>
#include <vector>
#include "RenderableObjectLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class ObjectFileReader : public RenderableObjectLayout {
public:
	ObjectFileReader(std::string path, std::string name);
	~ObjectFileReader();

private:
	int ParseObjectFile(std::string in, float *& re);
};