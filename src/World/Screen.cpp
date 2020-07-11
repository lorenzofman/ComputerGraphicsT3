#include "Screen.h"
int Screen::Width = 1366;
int Screen::Height = 768;

Int2 Screen::Center()
{
	return {Width / 2, Height / 2};
}

Int2 Screen::Size()
{
    return {Width, Height};
}
