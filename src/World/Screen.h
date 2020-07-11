#pragma once
#include "../Primitives/Int2.h"
/* Class to store view screen information */
class Screen
{
	public:
	static int Height;
	static int Width;
	static Int2 Center();
    static Int2 Size() ;
};

