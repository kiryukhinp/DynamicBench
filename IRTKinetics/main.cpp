#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "ReactorState.h"
#include "HeatHydraulic.h"

void output(std::string const& name, std::vector<Point2D> row)
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
int main()
{    
    float t_start = 0;
    float t_end = 10;
    float t = 0;
    int Nt = 100000;  

    std::vector<double> lam{0.01332, 0.0326, 0.121, 0.304, 0.854, 2.868}, 
                        beta{2.40212e-4, 1.23990e-3, 1.18371e-3,2.65399e-3,1.08810e-3, 4.55802e-4};
    std::vector<Point2D> ro{Point2D(0.,0.),Point2D(1.,-0.005454), Point2D(4.,0.)};
    double LAM{ 6.8E-5 }, n0{ 1 }, W{2.5e6}, Tin0{45}, Tout0{50.95}, G{100};
		float step{ (t_end - t_start) / Nt };  
    ReactorState reactor = ReactorState(beta,lam,LAM,1.,W,0,Tin0,Tout0,1000,1000,-1.0e-1,1,0);
    HeatHydraulic Pool = HeatHydraulic(W,G,4200.,Tin0,Tout0,std::vector({Point2D(0,0)}));


    for (int i = 0;  i < Nt; i++)
    {
      if (abs(reactor.t - 1.0)< step) reactor.AdditionalReactivityNew += 1;
      //std::cout<<reactor.t<<"   "<<reactor.Keff<<std::endl;
      reactor.CalculateNextStep(step,Dynamic,Pool.Tin,Pool.Tout,1000,1000);
      Pool.W = W*reactor.N; 
      Pool.CalculateNextStep(step);
      //std::cout<<reactor.t<<"   "<<reactor.N<<std::endl;
    } 
    output("Test.txt", reactor.N_t);
    output("Keff.txt", reactor.Keff_t);
    output("T", Pool.T_t);
    return 0;
}