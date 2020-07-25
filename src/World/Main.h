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

class Main
{
    public:

	enum class Dimension {D2, D3};

    void OnKeyboard(int key);

    void OnUpdate(float tick);

    void OnLeftMouseDown();

    void OnLeftMouseUp() const;

    Main();

	private:

	Camera camera = Camera(75);
	Crankshaft2D crankshaft2D = Crankshaft2D(20, 100, 320);
	Motor motor = Motor(50, 0.2f, 0.6f, 0.5f, camera);

	Dimension dimension = Dimension::D3;
	MultipleToggleOption drawingMask3D = MultipleToggleOption({96, 18}, {192, 36},
															  {"Pistons", "Cranks", "Rods","Counter-Weights", "Normals"}, {0, 1, 2, 3});
	OptionToggle shaderMode = OptionToggle({96, 54}, {192, 36}, {"Wireframe", "Unlit", "Lit"});
	OptionToggle projectionMode = OptionToggle({96, 90}, {192, 36}, {"Perspective", "Orthographic"});
	OptionToggle dimensionMode = OptionToggle({96, 126}, {192, 36}, {"2D", "3D"}, 1);

	int callbackId = -1;

	void OnLeftMouse();

	void On3DRenderModeChange(int mode);

	void OnShaderModeChange(int mode);

	void OnProjectionChange(int mode);

	void OnDimensionChange(int mode);

	void DrawUserInterface() const;
};
