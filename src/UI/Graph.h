#pragma once

#include "../Primitives/Int2.h"
#include "../World/Debug.h"
#include "../Primitives/Float2.h"
#include "../Canvas2D/Canvas2D.h"
/* Draw graphs onto screen with this class. Create it with a configuration structure
 * The class caches all the information about the data.
 * Graph bounds are normalized between min and max (they might be overrided)
 */
class Graph
{
    public:

    struct Configuration
    {
        enum class DrawMode {Discrete, Continuous, Bars};

        Float2* data;
        int n;
        Int2 bottomLeft;
        Int2 topRight;
        DrawMode drawMode;
        Color dataColor;
        Color backgroundColor;
        Color complementaryColor;
        std::string name;
        float min;
        float max;
        bool initialized = false;
        bool overrideMinMax = false;
        Configuration();
        Configuration(Float2 *data, int n, Int2 bottomLeft, Int2 topRight, DrawMode drawMode,
                      Color dataColor, Color backgroundColor,
                      Color complementaryColor, std::string name, float min = 0, float max = 0, bool overrideMinMax = false);
    };

    explicit Graph(Configuration configuration);
    void Draw();
    Configuration configuration;

    private:

    void DrawBackground(const Int2 &bl, const Int2 &tr) const;
    void DrawAxes(const Int2 &bl, const Int2 &tr, const Int2 &offsetBl, const Int2 &offsetTr, const Float2 &min, const Float2 &max) const;
    void DrawData(const Float2 *screenSpaceData) const;
    void DrawDiscrete(const Float2 *finalValues) const;
    void DrawContinuous(const Float2 *finalValues) const;
    void DrawBars(const Float2 *finalValues) const;

    Float2 *GetScreenSpaceData() const;
    static void MinMax(const Float2* data, int size, float* xMin, float* xMax, float* yMin, float* yMax);
    static float Normalized(float x, float min, float max);

    Float2 ConvertToScreenSpace(const Float2 &value) const;

    void DrawTitle() const;

    void DrawSeriesMinMax() const;

    Int2 internalOffset;
    Int2 bl;
    Int2 tr;
    Int2 size;
    Float2 min;
    Float2 max;
    Float2* screenData;
    Float2 screenOrigin;

};