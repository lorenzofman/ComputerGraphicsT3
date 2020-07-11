#pragma once

#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <string>
#include <cmath>

#include "../Primitives/Float2.h"
#include "../Primitives/Color.h"
#undef DrawText /* DrawText conflicts with WinUser.h header*/

class Canvas2D
{
	public:

	Canvas2D(int*, int*, std::string,
		void(OnKeyDownCallback(int)),
		void(OnKeyUpCallback(int)),
		void(OnMouseUpdateCallback(int, int, int, int, int, int)),
		void(OnRender(void)),
        void(OnScreenDimensionUpdae(void)));

	static void DrawPoint(Float2);
	static void DrawLine(Float2, Float2);

	static void DrawTriangle(Float2, Float2, Float2);
    static void DrawFilledTriangle(Float2, Float2, Float2);
	static void DrawRect(Float2, Float2);
	static void DrawFilledRect(Float2, Float2);

	static void DrawPolygon(Float2 vertices[], int);
	static void DrawFilledPolygon(Float2 vertices[], int);

	static void DrawCircle(Float2 pos, float radius, int divisions);
	static void DrawFilledCircle(Float2 pos, float radius, int divisions);

	static void DrawText(Float2 pos, const char*);

	static void SetColor(Color color);
	static void ClearScreen(Color color);

	private:

	static int* scrWidth;
	static int* scrHeight;

	static void (*OnKeyDownCallback)(int);
	static void (*OnKeyUpCallback)(int);
	static void (*OnMouseUpdateCallback)(int, int, int, int, int, int);
	static void (*OnRenderCallback)(void);
    static void (*OnScreenDimensionUpdate)(void);

	static void OnSpecialKeyDown(int, int, int);

	static void OnSpecialKeyUp(int, int, int);

	static void OnKeyboardDownGlutCallback(unsigned char, int, int);

	static void OnKeyboardUpGlutCallback(unsigned char, int, int);

	static void OnMouseClick(int, int, int, int);

	static void OnMouseWheel(int, int, int, int);

	static void OnMouseMotion(int, int);

	static void ConvertMouseCoord(int, int, int, int, int, int);

	static void ScreenRedimensionCallback(int, int);

	static void Display();

	static void RunCanvas();
};
