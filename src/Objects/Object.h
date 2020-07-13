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
    void Translate(Float3 displacement)
    {
	    for (int i = 0; i< faces.size(); i++)
        {
	    	faces[i].Translate(displacement);
        }
    }
};