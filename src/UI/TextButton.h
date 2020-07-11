#pragma once

#include "Button.h"
#include "Rect.h"

/* A rectangular button with centered text inside it */
class TextButton : public Button
{
    public:
    TextButton(std::string label, Float2 bottomLeft, Float2 topRight);
    ~TextButton();
    void Draw(Color color, bool selected);
    private:
    bool deleted;
    Rect rect;
    std::string label;
};