#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Point2D.h"
#include "HHUtilits.h"

inline void output(std::string const& name, std::vector<Point2D> row)
{
	int SolutionSize= row.size();
	std::ofstream fout(name);
	for (int i = 0; i < SolutionSize; i++)
	{
		fout << std::setw(10) << row[i].X << ' '<< row[i].Y << std::endl;
	}
}


Point2D GetNearstLowerValue(double t, std::vector<Point2D> row)
{

  if (row.size()>1)
  {
    for (int i = 0; i < row.size()-1; i++)
      {
        if (t >= row[i].X & t < row[i+1].X) return row[i];
      }
  return row[0];
  }
  
}


Point2D Lerp(float t, std::vector<Point2D> row)
{
  if (row.size()>1)
  {
    for (int i = 0; i < row.size(); i++)
    {
      if (t <= row[i].X) return Point2D((row[i].Y - row[i-1].Y)/(row[i].X - row[i-1].X)*t,t);
    }
  }
  return row[0];
}

Point2D Search(double t, std::vector<Point2D> row)
{
   for (int i = 0; i < row.size(); i++)
    {
      if (t == row[i].X) 
        return  row[i];
    }  
  return row[0];
}