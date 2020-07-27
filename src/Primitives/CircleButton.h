#include "../UI/Button.h"
#include "../UI/Circle.h"

/* Button with circle format */
class CircleButton : public Button
{
    public:
    CircleButton(Float2 pos, float radius, Color color);
    void Draw() const;
    Circle circle;
    private:
    const Color color;
};