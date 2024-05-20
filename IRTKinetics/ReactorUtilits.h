#pragma once
#include <vector>
#include "Point2D.h"

class ReactorUtilits
{
public:
	static void ThinOutVector(std::vector<Point2D>& Vector, size_t Interval, size_t ThinStart, size_t ThinEnd);
	static Point2D FindMax(std::vector<Point2D> V);
	static Point2D FindMin(std::vector<Point2D> V);

};





