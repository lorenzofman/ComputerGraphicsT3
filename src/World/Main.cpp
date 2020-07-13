#include "EventSystem.h"
#include "Main.h"
#include "Screen.h"
//Todo: Remove edge structure
#include "../Primitives/Edge.h"

void Main::OnUpdate(float tick)
{
	Canvas2D::ClearScreen(Colors::Background);
	crankshaft.Update(tick);
//	crankshaft.Draw();
	camera.Draw(sphere);
	camera.Draw(cube);
	Canvas2D::ClearScreen(Colors::Background);
}

void Main::OnKeyboard(int key)
{
    switch (key)
    {
        case 'W':
        case 'w':
            camera.position += Float3(0, 0, 1);
            break;
        case 'A':
        case 'a':
            camera.position += Float3(-1, 0, 0);
            break;
        case 'S':
        case 's':
            camera.position += Float3(0, 0, -1);
            break;
        case 'D':
        case 'd':
            camera.position += Float3(1, 0, 0);
            break;
        default:
            break;
    }
}


void Main::OnLeftMouseDown()
{
    callbackId = EventSystem::UpdateCallback.Register([this](float tick) {this->OnLeftMouse(tick);});
}

void Main::OnLeftMouseUp() const
{
    EventSystem::UpdateCallback.Deregister(callbackId);
}

void Main::OnLeftMouse(float tick)
{
    Float2 diff = EventSystem::MousePositionDelta;
    camera.rotation += Float3(0, -diff.x,-diff.y) * DegToRad;
}

void Main::Start()
{
	cube.Translate({0, 0, 10});
}

int main()
{
    Main mainInstance = Main();
	mainInstance.Start();
    EventSystem::UpdateCallback.Register([&mainInstance](float tick){mainInstance.OnUpdate(tick);});
    EventSystem::KeyDownCallback.Register([&mainInstance](int key){mainInstance.OnKeyboard(key);});
    EventSystem::RightMouseButtonDownCallback.Register([&mainInstance]{mainInstance.OnLeftMouseDown();});
    EventSystem::RightMouseButtonUpCallback.Register([&mainInstance]{mainInstance.OnLeftMouseUp();});
    Canvas2D(&Screen::Height, &Screen::Width, "Canvas", &EventSystem::OnKeyDown, &EventSystem::OnKeyUp,
             &EventSystem::OnMouseUpdate, &EventSystem::OnUpdate, &EventSystem::ScreenUpdate);
}