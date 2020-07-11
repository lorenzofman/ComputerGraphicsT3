#include "EventSystem.h"
#include "Main.h"
#include "Screen.h"
#include "../Primitives/Edge.h"

void Main::OnUpdate(float tick)
{
	Canvas2D::ClearScreen(Colors::Background);
	crankshaft.Update(tick);
	crankshaft.Draw();


	Canvas2D::ClearScreen(Colors::Background);
	Canvas2D::SetColor(Color(1, 1, 1));
	Float3 p[] =
	{
		Float3(-1, -1, -1),
		Float3(-1, -1, +1),
		Float3(-1, +1, -1),
		Float3(-1, +1, +1),
		Float3(+1, -1, -1),
		Float3(+1, -1, +1),
		Float3(+1, +1, -1),
		Float3(+1, +1, +1)
	};
	for (auto & i : p)
	{
		i += Float3(0, 0, 10);
	}
	Edge e[] =
	{
		Edge(p[0], p[1]),
		Edge(p[0], p[2]),
		Edge(p[0], p[4]),
		Edge(p[1], p[3]),
		Edge(p[1], p[5]),
		Edge(p[2], p[3]),
		Edge(p[2], p[6]),
		Edge(p[3], p[7]),
		Edge(p[4], p[5]),
		Edge(p[4], p[6]),
		Edge(p[5], p[7]),
		Edge(p[6], p[7]),
	};


	for (Edge edge : e)
	{
		Canvas2D::DrawLine(camera.WorldToDisplay(edge.p1), camera.WorldToDisplay(edge.p2));
	}

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
    camera.rotation += Float3(0, diff.x,-diff.y) * DegToRad *  tick;
}

int main()
{
    std::cout << "Ok" << std::endl;
    Main mainInstance = Main();
    EventSystem::UpdateCallback.Register([&mainInstance](float tick){mainInstance.OnUpdate(tick);});
    EventSystem::KeyDownCallback.Register([&mainInstance](int key){mainInstance.OnKeyboard(key);});
    EventSystem::RightMouseButtonDownCallback.Register([&mainInstance]{mainInstance.OnLeftMouseDown();});
    EventSystem::RightMouseButtonUpCallback.Register([&mainInstance]{mainInstance.OnLeftMouseUp();});
    Canvas2D(&Screen::Height, &Screen::Width, "Canvas", &EventSystem::OnKeyDown, &EventSystem::OnKeyUp,
             &EventSystem::OnMouseUpdate, &EventSystem::OnUpdate, &EventSystem::ScreenUpdate);
}