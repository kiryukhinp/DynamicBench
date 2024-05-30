#ifndef REACTORSTATE_H_
#define REACTORSTATE_H_

#include <vector>
#include "Point2D.h"
#include "ReactorUtilits.h"

enum CalculationType
{
    Dynamic,
    Static,
    Skip
};

class ReactorState
{
public:
    ReactorState();
    ReactorState(std::vector<double> &Beta_, std::vector<double> &Lam_, double const &LAM_, double const &Keff_0, double W_nom, double const &Source,
                 double Tin, double Tout, double Din, double Dout, double RCWT_, double RCDW_, double _additionalReactivity);

    double N; // Neutron flux density in current time step
    double N0 = 1;
    double W0;
    double t; // current time
    double T = -INFINITY;
    std::vector<Point2D> N_t;
    std::vector<Point2D> W_t;
    double Keff;
    double AdditionalReactivity, AdditionalReactivityNew;
    bool bUnderCritic = false;
    std::vector<Point2D> Keff_t;
    std::vector<double> C; // Delayed neutron emitters concentrations
    std::vector<std::vector<Point2D>> C_t;
    std::vector<double> Lam; // fission constants for emitter groups
    std::vector<double> Beta;
    double SumBeta = 0.0065;
    double TWater = 35;
    double Tfuel = 40;
    double TWaterIn = 30;
    double TWaterOut = 40;
    double DWaterIn = 1000;
    double DWaterOut = 1000;
    double DWater = (DWaterIn + DWaterOut) / 2;
    double LAM = 1e-4;
    double S = 0;
    double RCWT = 0; // Water temperature reactivity coefficient
    double RCDW = 0; // Water density reactivity coefficient
    int Index;
    void CalculateNextStep(double DeltaTime, CalculationType Type, double Tin, double Tout, double Din, double Dout);
    void CalculateC();
    void ThinOut();
    double CalculateTav(int step) const;
    void SetSource(double Source);

private:
    std::vector<std::vector<double>> KRK(double ro, double step, std::vector<double> beta, std::vector<double> lam, std::vector<double> NI, double S);
    void DynamicCalculation(double DeltaTime, double TWaterNew, double DWaterNew);
    void StaticCalculate(double DeltaTime);
};

#endif // REACTORSTATE_H_