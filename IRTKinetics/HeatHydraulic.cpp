#pragma once
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
    dT = Tout-Tin;
    WaterDensRow = Density;   
    Dens = Lerp(Tav,WaterDensRow).Y;
}

void HeatHydraulic::CalculateNextStep(float step)
{
    t +=step;
    dT = W/(C*G);
    Tout = Tin+dT;
    Tav = (Tin+Tout)/2;
    Dens = Lerp(Tav,WaterDensRow).Y;
    T_t.push_back(Point2D(t,Tav));
    D_t.push_back(Point2D(t,Dens));
}