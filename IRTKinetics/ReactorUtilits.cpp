//
// Created by Pavel on 11.07.2022.
//

#include "ReactorUtilits.h"

void ReactorUtilits::ThinOutVector(std::vector<Point2D> &Vector, size_t Interval, size_t ThinStart, size_t ThinEnd)
{
    size_t Start = ThinStart;
    size_t End = ThinStart + Interval;
    std::vector<Point2D> Buf(Interval);
    std::vector<Point2D> ResultVector;
    Point2D Min;
    Point2D Max;
    while (End < ThinEnd)
    {
        for (size_t i = 0; i < Interval; i++)
        {
            Buf[i] = Vector[i + Start];
        }
        Max = FindMax(Buf);
        Min = FindMin(Buf);
        if (Min.X < Max.X)
        {
            ResultVector.push_back(Min);
            ResultVector.push_back(Max);
        }
        else
        {
            ResultVector.push_back(Max);
            ResultVector.push_back(Min);
        }
        Start = End;
        End += Interval;
    }
    for (size_t i = ThinEnd; i < Vector.size(); i++)
    {
        ResultVector.push_back(Vector[i]);
    }

    Vector = ResultVector;
}
Point2D ReactorUtilits::FindMax(std::vector<Point2D> V)
{
    Point2D Max = V[0];
    for (size_t i = 1; i < V.size(); i++)
    {
        if (Max.Y < V[i].Y)
            Max = V[i];
    }
    return Max;
}
Point2D ReactorUtilits::FindMin(std::vector<Point2D> V)
{
    Point2D Min = V[0];
    for (size_t i = 1; i < V.size(); i++)
    {
        if (Min.Y > V[i].Y)
            Min = V[i];
    }
    return Min;
}