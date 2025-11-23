#pragma once
#include "Entity.h"
#include "Component.h"
#include <QPainter>

void RenderEllipse(QPainter& painter, Entity& entity, CPen cpen)
{
    auto ellipses = entity.GetComponentsOfType<CEllipse>();

    for (auto comp : ellipses)
    {
        auto ellipse = dynamic_cast<CEllipse*>(comp.get());
        QPen pen(cpen.color, cpen.thikness);
        painter.setPen(pen);
        //painter.setBrush(cpen.color);
        painter.drawEllipse(QPoint(ellipse->position.x, ellipse->position.y), ellipse->rx, ellipse->ry);
    }
}
void RenderComponentWithPositionCapability(QPainter& painter, Entity& entity, CPen cpen)
{
    auto components = entity.GetAllComponents();


    for (auto& comp : components)
    {
        if (!HaveCapability<Component, Position>(*comp))
        {
            continue;
        }


        QPen pen(cpen.color, cpen.thikness);

        if (HaveCapability<Component, EllipseRadius>(*comp))
        {
            auto ellipse = static_cast<CShape<EllipseRadius>*>(comp.get());
            painter.setPen(pen);
            //painter.setBrush(cpen.color);
            painter.drawEllipse(QPoint(ellipse->position.x, ellipse->position.y), ellipse->rx, ellipse->ry);
        }
        else if (HaveCapability<Component, SquareSize>(*comp))
        {
            auto square = static_cast<CShape<SquareSize>*>(comp.get());
            painter.setPen(pen);
            //painter.setBrush(cpen.color);
            painter.drawRect(QRect(square->position.x-square->side, square->position.y-square->side, square->side*2, square->side*2));
        }
        else if (HaveCapability<Component, RectangleSize>(*comp))
        {
            auto shape = static_cast<CShape<RectangleSize>*>(comp.get());
            painter.setPen(pen);
            //painter.setBrush(cpen.color);
            painter.drawRect(shape->position.x, shape->position.y, shape->width, shape->height);
        }
        else  if (HaveCapability<Component, CircleRadius>(*comp))
        {
            auto shape = static_cast<CShape<CircleRadius>*>(comp.get());
            painter.setPen(pen);
            //painter.setBrush(cpen.color);
            painter.drawEllipse(shape->position.x, shape->position.y, shape->radius, shape->radius);
        }
    }
}

void RenderSquare(QPainter& painter, Entity& entity, CPen cpen)
{
    if (!HaveCapability<Entity, CSquare>(entity))
    {
        return;
    }
    auto square = entity.GetComponentOfType<CSquare>();
    QPen pen(cpen.color, cpen.thikness);
    painter.setPen(pen);
    //painter.setBrush(cpen.color);
    painter.drawRect(square->position.x, square->position.y, square->side, square->side);
}
