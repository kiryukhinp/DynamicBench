#include "HeatHydraulic.h"
HeatHydraulic::HeatHydraulic(double W_, double G_, double C_, double Tin_, double Tout_,  std::vector<Point2D> Density)
{
    t= 0;
    W = W_;
    G = G_;
    C = C_;
    Tin = Tin_;
    Tout = Tout_;
    Tav = (Tin+Tout)/2;    
}

void HeatHydraulic::CalculateNextStep(float step)
{
    t +=step;
    Tav += W/(C*G);
}