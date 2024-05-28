#pragma once
#include <vector>
#include "Point2d.h"
#include "Auxiliary.hpp"
#include "Utilits.hpp"

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
    double Dens;
    std::vector<Point2D> T_t;
    std::vector<Point2D> D_t;
    std::vector<Point2D> WaterDensRow;
    void CalculateNextStep(float step);
};