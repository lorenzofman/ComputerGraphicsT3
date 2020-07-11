#include "Graph.h"
#include <iomanip>
#include <sstream>
#include <exception>
Graph::Graph(Configuration configuration)
{
    if (!configuration.initialized)
    {
        return;
    }
    this->configuration = configuration;
    internalOffset = {15, 30};
    bl = configuration.bottomLeft + Int2(internalOffset.x, internalOffset.y / 2);
    tr = configuration.topRight + Int2(0, -internalOffset.y / 2);
    size = tr - bl;
    Debug::Assert(size.x > 0, "Graph width must be greater than zero");
    Debug::Assert(size.y > 0, "Graph height must be greater than zero");

    if (configuration.overrideMinMax)
    {
        this->min.y = configuration.min;
        this->max.y = configuration.max;
        float unused;
        MinMax(configuration.data, configuration.n, &min.x, &max.x, &unused, &unused);
    }
    else
    {
        MinMax(configuration.data, configuration.n, &min.x, &max.x, &min.y, &max.y);
    }
    screenData = GetScreenSpaceData();
    screenOrigin = ConvertToScreenSpace({0, 0});
}

void Graph::Draw()
{
    DrawBackground(configuration.bottomLeft, configuration.topRight);

    DrawAxes(configuration.bottomLeft, configuration.topRight, bl, tr, min, max);

    DrawSeriesMinMax();

    DrawTitle();

    DrawData(screenData);
}

void Graph::DrawSeriesMinMax() const
{
    Canvas2D::SetColor(configuration.complementaryColor);

    std::stringstream minStream;
    minStream << std::fixed << std::setprecision(3) << min.y;
    std::stringstream maxStream;
    maxStream << std::fixed << std::setprecision(3) << max.y;

    Canvas2D::DrawText({(float) screenOrigin.x, (float) bl.y}, minStream.str().c_str());
    Canvas2D::DrawText({(float) screenOrigin.x, (float) tr.y}, maxStream.str().c_str());
}

void Graph::DrawTitle() const
{
    Canvas2D::SetColor(configuration.dataColor);
    int characterSize = 10;
    auto xPos = (float) (bl.x + tr.x - configuration.name.length() * characterSize) / 2;
    auto yPos = (float) (tr.y);

    Canvas2D::DrawText({xPos, yPos}, configuration.name.c_str());
}

void Graph::DrawAxes(const Int2 &bl, const Int2 &tr, const Int2 &offsetBl, const Int2 &offsetTr, const Float2 &min, const Float2 &max) const
{
    Canvas2D::SetColor(configuration.complementaryColor);
    if (min.x <= 0.0f && max.x >= 0.0f)
    {
        float abscissa = screenOrigin.x;
        Canvas2D::DrawLine({abscissa, (float) bl.y}, {abscissa, (float) tr.y});
    }
    if (min.y <= 0.0f && max.y >= 0.0f)
    {
        float ordinate = screenOrigin.y;
        Canvas2D::DrawLine({(float) bl.x, ordinate}, {(float) tr.x, ordinate});
    }
}

void Graph::DrawBackground(const Int2 &bl, const Int2 &tr) const
{
    Canvas2D::SetColor(configuration.backgroundColor);
    Canvas2D::DrawFilledRect({(float) bl.x, (float) bl.y}, {(float) tr.x, (float) tr.y});
}

void Graph::DrawData(const Float2 *screenSpaceData) const
{
    Canvas2D::SetColor(configuration.dataColor);
    switch (configuration.drawMode)
    {
        case Configuration::DrawMode::Discrete:
            DrawDiscrete(screenSpaceData);
            break;
        case Configuration::DrawMode::Continuous:
            DrawContinuous(screenSpaceData);
            break;
        case Configuration::DrawMode::Bars:
            DrawBars(screenSpaceData);
            break;
        default:
            throw "Invalid draw mode";
    }
}

void Graph::DrawDiscrete(const Float2 *finalValues) const
{
    for (int i = 0; i < configuration.n; i++)
    {
        Canvas2D::DrawFilledCircle(finalValues[i], 2, 16);
    }
}

void Graph::DrawContinuous(const Float2 *finalValues) const
{
    for (int i = 1; i < configuration.n; i++)
    {
        Canvas2D::DrawLine(finalValues[i-1], finalValues[i]);
    }
}

void Graph::DrawBars(const Float2 *finalValues) const
{
    float thickness = 1;
    for (int i = 0; i < configuration.n; i++)
    {
        float x = finalValues[i].x;
        Canvas2D::DrawFilledRect({x - thickness, screenOrigin.y}, {x + thickness, finalValues[i].y});
    }
}

Float2 *Graph::GetScreenSpaceData() const
{
    auto finalValues = new Float2[configuration.n];
    for (int i = 0; i < configuration.n; i++)
    {
        finalValues[i] = ConvertToScreenSpace(configuration.data[i]);
    }
    return finalValues;
}

Float2 Graph::ConvertToScreenSpace(const Float2 &value) const
{
    const Float2 normalized = {Normalized(value.x, min.x, max.x), Normalized(value.y, min.y, max.y) };
    const Float2 amplitude = { normalized.x * (float) size.x, normalized.y * (float) size.y};
    const Float2 final = amplitude + Float2((float) bl.x,(float) bl.y);
    return final;
}

void Graph::MinMax(const Float2 *data, int size, float *xMin, float *xMax, float* yMin, float* yMax)
{
    Debug::Assert(size > 0, "Graph data has no value");
    *xMin = *xMax = data[0].x;
    *yMin = *yMax = data[0].y;

    for (int i = 1; i< size; i++)
    {
        if (data[i].x < *xMin)
        {
            *xMin = data[i].x;
        }
        else if (data[i].x > *xMax)
        {
            *xMax = data[i].x;
        }
        if (data[i].y < *yMin)
        {
            *yMin = data[i].y;
        }
        else if (data[i].y > *yMax)
        {
            *yMax = data[i].y;
        }
    }
}

float Graph::Normalized(const float x,const float min, const float max)
{
    return (x - min) / (max - min);
}

Graph::Configuration::Configuration(Float2 *data, int n, Int2 bottomLeft, Int2 topRight,
                                    Graph::Configuration::DrawMode drawMode, Color dataColor,
                                    Color backgroundColor, Color complementaryColor,
                                    std::string name, float min, float max, bool overrideMinMax)
{
    this->data = data;
    this->n = n;
    this->bottomLeft = bottomLeft;
    this->topRight = topRight;
    this->drawMode = drawMode;
    this->dataColor = dataColor;
    this->backgroundColor = backgroundColor;
    this->complementaryColor = complementaryColor;
    this->name = std::move(name);
    this->min = min;
    this->max = max;
    this->overrideMinMax = overrideMinMax;
    initialized = true;

}

Graph::Configuration::Configuration()
{
    initialized = false;
}
