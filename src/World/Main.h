#pragma once

#include "../UI/Graph.h"
#include "../Primitives/Float2.h"
#include "../UI/TextButton.h"
#include "Camera.h"
#include "../Objects/Crankshaft2D.h"
#include "../Objects/Object.h"
#include "../Objects/ObjectCreator.h"

class Main
{
    public:

    void OnKeyboard(int key);

    void OnUpdate(float tick);

    void OnLeftMouseDown();

    void OnLeftMouseUp() const;

	void Start();

	private:
    //Object cylinder = ObjectCreator::BuildCylinder(32, 1, 3);
	Object sphere = ObjectCreator::BuildFlatRoundedRectangle(10, 2, 3, 32);
	Object cube = ObjectCreator::BuildCube(1);
    Crankshaft2D crankshaft = Crankshaft2D(200, 100, 320);

    Camera camera = Camera(75);
    int callbackId = -1;
    void OnLeftMouse(float tick);
};
