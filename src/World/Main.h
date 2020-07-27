#pragma once

#include "../UI/Graph.h"
#include "../Primitives/Float2.h"
#include "../UI/TextButton.h"
#include "Camera.h"
#include "../Objects/Crankshaft2D.h"
#include "../Objects/Object.h"
#include "../Objects/ObjectCreator.h"
#include "../Objects/Crankshaft3D.h"
#include "../UI/OptionToggle.h"
#include "../UI/MultipleToggleOption.h"
#include "../Objects/Motor.h"
#include "../UI/Slider.h"
#include "Screen.h"

class Main
{
	public:

    Main();

	private:

	enum class Dimension {D2, D3};

	Camera camera = Camera(75);
	Crankshaft2D crankshaft2D = Crankshaft2D(20, 100, 320);
	Motor motor = Motor(45, 0.2f, 0.6f, camera);

	Dimension dimension = Dimension::D3;
	MultipleToggleOption drawingMask3D = MultipleToggleOption({96, 18}, {192, 36},
															  {"Pistons", "Cranks", "Rods", "Cylinder", "Counter-Weights", "Normals"}, {0, 1, 2, 3, 4});
	OptionToggle shaderMode = OptionToggle({96, 54}, {192, 36}, {"Wireframe", "Unlit"});
	OptionToggle projectionMode = OptionToggle({96, 90}, {192, 36}, {"Perspective", "Orthographic"});
	OptionToggle dimensionMode = OptionToggle({96, 126}, {192, 36}, {"2D", "3D"}, 1);
	Slider rpmSlider = Slider(Float2(128, 168),256, 20, {0.4f, 0.4f, 0.4f},
			{0.6f, 0.6f, 0.6f}, {1, 0.9f, 0.76f});
	std::string rpmText;
	int rightMouseCallback = -1;
	int middleMouseCallback = -1;

	void OnKeyboard(int key);
	void OnUpdate(float tick);

	void OnLeftMouseDown();
	void OnRightMouseUp() const;
	void OnRightMouse();

	void OnMiddleMouseDown();
	void OnMiddleMouseUp() const;
	void OnMiddleMouse(float tick);

	void OnScrollMouse(int dir);

	void On3DRenderModeChange(int mode);

	void OnShaderModeChange(int mode);

	void OnProjectionChange(int mode);

	void OnDimensionChange(int mode);

	void DrawUserInterface() const;

	void UpdateRpmText(float rpm);
};
