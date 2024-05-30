#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "ReactorState.h"
#include "HeatHydraulic.h"
#include "HHUtilits.h"
#include "Utilits.hpp"



int main()
{    
    float t_start = 0;
    float t_end = 10;
    float t = 10;
    int Nt = 100000;  

    std::vector<double> lam{0.01332, 0.0326, 0.121, 0.304, 0.854, 2.868}, 
                        beta{2.40212e-4, 1.23990e-3, 1.18371e-3,2.65399e-3,1.08810e-3, 4.55802e-4};
    std::vector<Point2D> ro{Point2D(0.,0.),Point2D(1.,-0.005454), Point2D(4.,0.)};
    double LAM{ 6.8E-5 }, n0{ 1 }, W{2.5e6}, Tin0{45}, Tout0{50.95}, G{100};
		float step{ (t_end - t_start) / Nt };  
    std:: vector<Point2D> Dens = HHUtilits::ReadRowFromFile("WaterDensity");
    HeatHydraulic Pool = HeatHydraulic(W,G,4200.,Tin0,Tout0,std::vector(Dens));
    std::vector<Point2D> KSUp = Linespace(1., 3.5, 0., 0.175, 100);
    std::vector<Point2D> Reactivity = HHUtilits::ReadRowFromFile("Reactivity.txt");
    ReactorState reactor = ReactorState(beta,lam,LAM,1.,W,0,Tin0,Tout0,Pool.Dens,Pool.Dens,0,0,0);//-1.23e-5, 0.000277,0);


    
    

    for (int i = 0;  i < Nt; i++)
    {
      //if (abs(reactor.t - 1.0)< step) reactor.AdditionalReactivityNew += 1;
      //std::cout<<reactor.t<<"   "<<reactor.Keff<<std::endl;
      //if (Search(reactor.t, KSUp, step/10).Y >0)
      //{
      //    reactor.AdditionalReactivityNew = Search(reactor.t, KSUp, step/10).Y;
      //}
      if (Search(reactor.t, Reactivity, step).Y >0)
      {
          reactor.AdditionalReactivityNew = Search(reactor.t, Reactivity, step).Y;
          std::cout<<reactor.t<<"   "<<reactor.AdditionalReactivityNew<<std::endl;
      }
      
      reactor.CalculateNextStep(step,Dynamic,Pool.Tin,Pool.Tout,Pool.Dens,Pool.Dens);
      Pool.W = W*reactor.N; 
      Pool.CalculateNextStep(step);
      //std::cout<<reactor.t<<"   "<<reactor.N<<std::endl;
    } 
    output("Test.txt", reactor.N_t);
    output("W.txt", reactor.W_t);
    output("Keff.txt", reactor.Keff_t);
    output("T", Pool.T_t);
    output("Dens", Pool.D_t);
    return 0;
}