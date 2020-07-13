#pragma once

#include <chrono>
#include <thread>
#include <iostream>

#include "../Helpers/Callback.h"

#include "../Primitives/Int2.h"

#include "../Primitives/Constants.h"

/* Wrapper to handle Canvas2D callbacks allowing other scripts to use callbacks*/
class EventSystem
{
	public:

	enum class MouseButton
	{
		Left = 0,
		Middle = 1,
		Right = 2
	};

	enum class MouseButtonState
	{
		Down = 0,
		Up = 1
	};
	static void Start();
	static void OnUpdate();
	static void OnKeyDown(int key);
	static void OnKeyUp(int key);
	static void OnMouseUpdate(int button, int state, int wheel, int direction, int x, int y);
    static void ScreenUpdate();
	static void MouseButtonClick(Callback<> downCallback, Callback<> upCallback, EventSystem::MouseButtonState btnState);

	static float LastFrameDuration;
	static Callback<float> UpdateCallback;
	static Callback<int> KeyDownCallback;
	static Callback<int> KeyUpCallback;
	static Callback<int, int, int, int, int, int> MouseUpdateCallback;

	static Callback<> LeftMouseButtonDownCallback;
	static Callback<> LeftMouseButtonUpCallback;

	static Callback<> MiddleMouseButtonDownCallback;
	static Callback<> MiddleMouseButtonUpCallback;

	static Callback<> RightMouseButtonDownCallback;
	static Callback<> RightMouseButtonUpCallback;

	static Callback<> MouseMovementCallback;
	static Callback<> MouseWheelCallback;

    static Callback<> ScreenUpdateCallback;

    static Int2 MousePosition;
	static Int2 MousePositionDelta;

};