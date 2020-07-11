#pragma once

#include "../UI/Graph.h"
#include "../Primitives/Float2.h"
#include "../UI/TextButton.h"
#include "Camera.h"
#include "../Objects/Crankshaft.h"
#include "../Objects/Object.h"
#include "../Objects/ObjectCreator.h"
//#include "../Objects/ObjectCreator.h"

class Main
{
    public:

    void OnKeyboard(int key);

    void OnUpdate(float tick);

    void OnLeftMouseDown();

    void OnLeftMouseUp() const;

    private:
    Object sphere = ObjectCreator::BuildCylinder(32, 32, 1, 3);

    Crankshaft crankshaft = Crankshaft(200, 100, 320);

    Camera camera = Camera(75);
    int callbackId = -1;
    void OnLeftMouse(float tick);
};
