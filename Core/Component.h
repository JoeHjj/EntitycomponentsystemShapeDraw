#pragma once

#include "Capability.h"

#include <string>
#include <bitset>
#include <memory>
#include <algorithm>
#include <typeindex>
#include <QColor>


class Component : Capability
{
public:
    virtual ~Component() = default;
    Component() = default;
    CapabilityMask capabilityMask;
};

class Position : public Component
{
public:
    int x = 0;
    int y = 0;

    void update(int mx, int my)
    {
        x = mx;
        y = my;
    }
};

class SquareSize : public Component
{
public:
    int side = 0;
};

class CircleRadius : public Component
{
public:
    int radius = 10;
};

class EllipseRadius : public Component
{
public:
    int rx = 30;
    int ry = 20;
};

class RectangleSize : public Component
{
public:
    int width = 1;
    int height = 1;
};

template <typename SizeComponent>
class CShape : public SizeComponent
{
public:
    Position position;
    CShape()
    {
        Assign<Component, Position>(*this);
        Assign<Component, SizeComponent>(*this);
    }
};

class CEllipse : public CShape<EllipseRadius>
{
public:
    CEllipse()
    {
    }
    CEllipse(int mx, int my, int mrx = 10, int mry = 10)
        : CEllipse()
    {
        update(mx, my, mrx, mry);
    }
    void update(int mx, int my)
    {
        position.update(mx, my);
    }

    void update(int mx, int my, int mrx, int mry)
    {
        position.update(mx, my);
        rx= mrx;
        ry = mry;
    }
};
/*
class CCircle : public CShape<CircleRadius>
{
public:
    CCircle()
    {
    }
    CCircle(int mx, int my, int mr = 60)
        : CCircle()
    {
        update(mx, my, mr);
    }
    void update(int mx, int my)
    {
        position.update(mx, my);
    }

    void update(int mx, int my, int mr)
    {
        position.update(mx, my);
        radius= mr;
    }
};
*/
class CSquare : public CShape<SquareSize>
{
public:
    CSquare()
    {
    }
    CSquare(int mx, int my, int mside = 10)
        : CSquare()
    {
        update(mx, my, mside);
    }

    void update(int mx, int my, int mside)
    {
        side= mside;
        position.update(mx, my);
    }

    void update(int mside)
    {
        side= mside;
    }

    void update(int mx, int my)
    {
        position.update(mx, my);
    }
};

class CRectangle : public CShape<RectangleSize>
{
public:
    CRectangle()
    {
    }
    CRectangle(int mx, int my, int mwidth = 10, int mHeight = 10)
        : CRectangle()
    {
        update(mx, my);
        width = mwidth;
        height = mHeight;
    }

    void update(int mx, int my)
    {
        position.update(mx, my);
    }
};

class CPen : public Component
{
public:
    CPen() = default;
    CPen(QColor col, int thik)
        : color(col)
        , thikness(thik)
    {}
    QColor color;
    int thikness = 2;
};

