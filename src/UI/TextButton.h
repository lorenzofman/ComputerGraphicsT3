#pragma once

#include "Button.h"
#include "Rect.h"

/* A rectangular button with centered text inside it */
class TextButton : public Button
{
    public:
    TextButton(std::string label, Float2 bottomLeft, Float2 topRight);
    void Draw(Color color, Color textColor);
    private:
    Rect rect;
    std::string label;
};