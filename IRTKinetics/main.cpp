#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "ReactorState.h"

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

int main()
{    
    float t_start = 0;
    float t_end = 8;
    float t = 0;
    int Nt = 10000;  

    std::vector<double> lam{0.01332, 0.0326, 0.121, 0.304, 0.854, 2.868}, 
                        beta{2.40212e-4, 1.23990e-3, 1.18371e-3,2.65399e-3,1.08810e-3, 4.55802e-4};
    std::vector<Point2D> ro{Point2D(0.,0.),Point2D(1.,-0.005454), Point2D(4.,0.)};
    double LAM{ 6.8E-5 }, n0{ 1 },
		step{ (t_end - t_start) / Nt };
    std::vector<Point2D> Result;
    ReactorState reactor = ReactorState(beta,lam,LAM,1.,2e5,0,40,40,1000,1000,1,1,0);
    


    for (int i = 0;  i < Nt; i++)
    {
      reactor.Keff = 1 + GetNearstLowerValue(reactor.t,ro).Y;
      //std::cout<<reactor.t<<"   "<<reactor.Keff<<std::endl;
      reactor.CalculateNextStep(step,Dynamic,40,40,1000,1000);
      //std::cout<<reactor.t<<"   "<<reactor.N<<std::endl;
    } 
    output("Test.txt", reactor.N_t);
    return 0;
}