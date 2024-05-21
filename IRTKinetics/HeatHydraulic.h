#include <vector>
#include "Point2d.h"

class HeatHydraulic
{
public:
    HeatHydraulic(){};
    HeatHydraulic(double W_, double G_, double C_, double Tin_, double Tout_,  std::vector<Point2D> Density);
    double t;
    double W; 
    double G;   
    double C;
    double Tin;
    double Tout;
    double Tav;
    double dT;
    std::vector<Point2D> T_t;
    void CalculateNextStep(float step);
};