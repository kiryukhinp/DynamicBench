#include <vector>
#include "Point2d.h"

class HeatHydraulic
{
public:
    HeatHydraulic();
    HeatHydraulic(double W_, double G_, double C_, double Tin_, double TOut_,  std::vector<Point2D> Density);
    double t;
    double W; 
    double G;   
    double C;
    double Tin;
    double Tout;
    void CalculateNextStep();
};