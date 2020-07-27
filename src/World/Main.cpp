#include "EventSystem.h"
#include "Main.h"

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
	rpmSlider.Draw();
	Canvas2D::DrawText({5, 200}, rpmText.c_str());
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
	rightMouseCallback = EventSystem::UpdateCallback.Register([this](float tick)
	{
		this->OnRightMouse();
	});
}

void Main::OnRightMouseUp() const
{
    EventSystem::UpdateCallback.Deregister(rightMouseCallback);
}

void Main::OnRightMouse()
{
    Float2 diff = EventSystem::MousePositionDelta;
    camera.rotation += Float3(0, -diff.x, -diff.y) * DegToRad * 0.25f;
}

void Main::OnMiddleMouseDown()
{
	middleMouseCallback = EventSystem::UpdateCallback.Register([this](float tick)
 	{
		this->OnMiddleMouse(tick);
 	});
}

void Main::OnMiddleMouseUp() const
{
	EventSystem::UpdateCallback.Deregister(middleMouseCallback);
}

void Main::OnMiddleMouse(float tick)
{
	Float2 diff = EventSystem::MousePositionDelta;
	camera.position += Float3(-diff.x, -diff.y, 0) * tick;
}

void Main::OnScrollMouse(int direction)
{
	camera.fieldOfView -= direction;
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

	EventSystem::RightMouseButtonDownCallback.Register([this]{this->OnLeftMouseDown();});
	EventSystem::RightMouseButtonUpCallback.Register([this]{this->OnRightMouseUp();});

	EventSystem::MiddleMouseButtonDownCallback.Register([this]{this->OnMiddleMouseDown();});
	EventSystem::MiddleMouseButtonUpCallback.Register([this]{this->OnMiddleMouseUp();});

	EventSystem::UpdateCallback.Register([this](float tick){this->OnUpdate(tick);});
	EventSystem::KeyDownCallback.Register([this](int key){this->OnKeyboard(key);});

	EventSystem::MouseWheelCallback.Register([this](int dir){this->OnScrollMouse(dir);});

	camera.position = {-0.15f, 0.55f, -2};
	camera.rotation = {0, PI / 3, -PI / 10};

	rpmSlider.valueChangeCallback.Register([this](float val)
	{
		float rpm = powf(45, val + 0.5f);
		this->motor.UpdateRpm(rpm);
		this->crankshaft2D.UpdateRpm(rpm);
		UpdateRpmText(rpm);
	});
	UpdateRpmText(45);
}

void Main::UpdateRpmText(float rpm)
{
	rpmText = std::to_string(rpm) + " RPM";
}

int main()
{
	EventSystem::Start();
	Main mainInstance = Main();
    Canvas2D(&Screen::Height, &Screen::Width, "Canvas", &EventSystem::OnKeyDown, &EventSystem::OnKeyUp,
             &EventSystem::OnMouseUpdate, &EventSystem::OnUpdate, &EventSystem::ScreenUpdate);
}