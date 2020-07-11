#include "TextButton.h"

#include <utility>

TextButton::TextButton(std::string label, Float2 bottomLeft, Float2 topRight) : rect(bottomLeft, topRight), Button((IPointInside&) rect)
{
    this->label = std::move(label);
    deleted = false;
}

TextButton::~TextButton()
{
    deleted = true;
}

void TextButton::Draw(Color color, bool selected)
{
    if (deleted)
    {
        std::cout << "Deleted" << std::endl;

        return;
    }
    Color rectColor = selected ? Color(0.85f, 0.85f, 0.85f) : Color(0.5f, 0.5f, 0.5f);
    rectColor *= IsMouseOver() ? 1.2f : 1.0f;
    Canvas2D::SetColor(rectColor);
    Canvas2D::DrawFilledRect(rect.bottomLeft, rect.topRight);

    Float2 mid = (rect.topRight + rect.bottomLeft) * 0.5f;
    Canvas2D::SetColor(color);
    Canvas2D::DrawText(mid - Float2((float) label.length() * 5, 3), label.c_str());

}
