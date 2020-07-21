#pragma once

#include "../UI/Graph.h"
#include "../Primitives/Float2.h"
#include "../UI/TextButton.h"
#include "Camera.h"
#include "../Objects/Crankshaft2D.h"
#include "../Objects/Object.h"
#include "../Objects/ObjectCreator.h"
#include "../Objects/Crankshaft3D.h"

class Main
{
    public:
    void OnKeyboard(int key);

    void OnUpdate(float tick);

    void OnLeftMouseDown();

    void OnLeftMouseUp() const;


	private:
    Crankshaft2D crankshaft2D = Crankshaft2D(20, 100, 320);
	Camera camera = Camera(75);
	Crankshaft3D crankshaft1 = Crankshaft3D(50, 0.2f, 0.6f,0.5f, camera, 0, 0);
	Crankshaft3D crankshaft2 = Crankshaft3D(50, 0.2f, 0.6f,0.5f, camera, 0.314, PI);
	Crankshaft3D crankshaft3 = Crankshaft3D(50, 0.2f, 0.6f,0.5f, camera, 0.628, PI);
	Crankshaft3D crankshaft4 = Crankshaft3D(50, 0.2f, 0.6f,0.5f, camera, 0.942, 0);


	int callbackId = -1;
    void OnLeftMouse();

	Object connectingPipe = ObjectCreator::BuildCylinder(32, 0.1f, 0.6f);
};
