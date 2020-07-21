#pragma once

#include <utility>
#include <vector>
#include "Face.h"

struct Object
{
	Object()
	{

	}

	Object(std::vector<Face> faces)
	{
		this->faces = std::move(faces);
	}

	std::vector<Face> faces;

    Float3 position;
    Float3 rotation;
};