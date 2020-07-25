#include "EventSystem.h"
#include "Main.h"
#include "Screen.h"

void Main::OnUpdate(float tick)
{
	Canvas2D::ClearScreen(Colors::Background);
	Canvas2D::SetColor({0.8f, 0.8f, 0.8f});

	switch (dimension)
	{
		case Dimension::D2:
			crankshaft2D.Update(tick);
			break;
		case Dimension::D3:
			motor.Update(tick);
			break;
	}

	DrawUserInterface();
}

void Main::DrawUserInterface() const
{
	projectionMode.Draw({0.2f, 0.2f, 0.2f}, {0.8f, 0.8f, 0.8f});
	dimensionMode.Draw({0.2f, 0.2f, 0.2f}, {0.8f, 0.8f, 0.8f});
	drawingMask3D.Draw({0.2f, 0.2f, 0.2f}, {0.8f, 0.8f, 0.8f});
	shaderMode.Draw({0.2f, 0.2f, 0.2f}, {0.8f, 0.8f, 0.8f});
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
    callbackId = EventSystem::UpdateCallback.Register([this](float tick)
	{
		this->OnLeftMouse();
	});
}

void Main::OnLeftMouseUp() const
{
    EventSystem::UpdateCallback.Deregister(callbackId);
}

void Main::OnLeftMouse()
{
    Float2 diff = EventSystem::MousePositionDelta;
    camera.rotation += Float3(0, -diff.x, -diff.y) * DegToRad * 0.25f;
}


void Main::On3DRenderModeChange(int mode)
{
	motor.InvertBitFlag(mode);
}

void Main::OnShaderModeChange(int mode)
{
	camera.shader = (Camera::ShaderType) mode;
}

void Main::OnProjectionChange(int mode)
{
	camera.projection = (Camera::ProjectionType) mode;
}

void Main::OnDimensionChange(int mode)
{
	dimension = (Dimension) mode;
}

Main::Main()
{
	drawingMask3D.OptionSelected.Register([this](int m) {this->On3DRenderModeChange(m);});
	shaderMode.OptionSelected.Register([this](int m) {this->OnShaderModeChange(m);});
	projectionMode.OptionSelected.Register([this](int m) {this->OnProjectionChange(m);});
	dimensionMode.OptionSelected.Register([this](int m) {this->OnDimensionChange(m);});
}

int main()
{
    Main mainInstance = Main();
	EventSystem::Start();
    EventSystem::UpdateCallback.Register([&mainInstance](float tick){mainInstance.OnUpdate(tick);});
    EventSystem::KeyDownCallback.Register([&mainInstance](int key){mainInstance.OnKeyboard(key);});
    EventSystem::RightMouseButtonDownCallback.Register([&mainInstance]{mainInstance.OnLeftMouseDown();});
    EventSystem::RightMouseButtonUpCallback.Register([&mainInstance]{mainInstance.OnLeftMouseUp();});
    Canvas2D(&Screen::Height, &Screen::Width, "Canvas", &EventSystem::OnKeyDown, &EventSystem::OnKeyUp,
             &EventSystem::OnMouseUpdate, &EventSystem::OnUpdate, &EventSystem::ScreenUpdate);
}