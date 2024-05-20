#include "HeatHydraulic.h"
HeatHydraulic::HeatHydraulic(double W_, double G_, double C_, double Tin_, double TOut_,  std::vector<Point2D> Density)
{
    t= 0;
    W = W_;
    G = G_;
    C = C_;
    
}