#include "ReactorState.h"
#include "cmath"

ReactorState::ReactorState()
{
}

ReactorState::ReactorState(std::vector<double> &Beta_, std::vector<double> &Lam_, double const &LAM_, double const &Keff_0, double W_nom, double const &Source,
                           double Tin, double Tout, double Din, double Dout, double RCWT_, double RCDW_, double _additionalReactivity)
{
    S = Source;
    Keff = Keff_0;
    W0 = W_nom;
    if (Keff_0 < 1)
        bUnderCritic = true;
    Beta = Beta_;
    Lam = Lam_;
    LAM = LAM_;
    const double Reactivity = (Keff - 1) / Keff;
    if (bUnderCritic)
        N = -S * LAM / Reactivity;
    else
        N = N0;
    SumBeta = 0;
    TWaterIn = Tin;
    TWaterOut = Tout;
    TWater = (TWaterIn + TWaterOut) / 2;
    DWaterIn = Din;
    DWaterOut = Dout;
    DWater = (Din + Dout) / 2;
    CalculateC();
    t = 0;
    N_t.push_back(Point2D(t, N));
    RCWT = RCWT_;
    RCDW = RCDW_;
    AdditionalReactivity = _additionalReactivity;
    AdditionalReactivityNew = AdditionalReactivity;
}

void ReactorState::CalculateNextStep(double DeltaTime, CalculationType Type, double Tin, double Tout, double Din, double Dout)
{
    switch (Type)
    {
    case Static:
    {
        if (Keff < 1 && bUnderCritic)
        {
            StaticCalculate(DeltaTime);
        }
        else
        {
            if (bUnderCritic)
                CalculateC();
            bUnderCritic = false;
            DynamicCalculation(DeltaTime, (Tin + Tout) / 2, (Din + Dout) / 2);
        }
        break;
    }
    case Dynamic:
    {
        DynamicCalculation(DeltaTime, (Tin + Tout) / 2, (Din + Dout) / 2);
        break;
    };
    }
    t += DeltaTime;
    // T = DeltaTime/(log(N) - log(N_t.back().Y));
    N_t.push_back(Point2D(t, N));
    W_t.push_back(Point2D(t, N*W0));
    Keff_t.push_back(Point2D(t, Keff));
    Index++;
    if (Index > 10000)
    {
        ThinOut();
        Index = 0;
    }
    TWaterIn = Tin;
    TWaterOut = Tout;
    TWater = (TWaterIn + TWaterOut) / 2;
    DWaterIn = Din;
    DWaterOut = Dout;
    DWater = (DWaterIn + DWaterOut) / 2;
    AdditionalReactivity = AdditionalReactivityNew;
}

void ReactorState::CalculateC()
{
    C.clear();
    SumBeta = 0;
    for (int j = 0; j < Lam.size(); j++)
    {
        if (Lam[j] != 0)
        {
            C.push_back(Beta[j] * N / (LAM * Lam[j]));
            SumBeta = SumBeta + Beta[j];
        }
        else
            C.push_back(0);
    }
}

void ReactorState::ThinOut()
{
    ReactorUtilits::ThinOutVector(Keff_t, 100, 0, Keff_t.size());
    ReactorUtilits::ThinOutVector(N_t, 100, 0, N_t.size());
}

double ReactorState::CalculateTav(int step) const
{
    if (N_t.size() > step)
    {
        size_t n = N_t.size();
        return -(N_t.back().X - N_t[n - step - 1].X) / (log(N_t[n - step - 1].Y) - log(N_t.back().Y));
    }
    return INFINITY;
}
void ReactorState::SetSource(double Source)
{
    S = Source;
}

void ReactorState::DynamicCalculation(double DeltaTime, double TWaterNew, double DWaterNew)
{
    std::vector<double> NI(Lam.size() + 1);
    Keff = Keff + RCWT * (TWaterNew - TWater) + RCDW * (DWaterNew - DWater) + SumBeta * (AdditionalReactivityNew - AdditionalReactivity);
    double Reactivity = (Keff - 1) / Keff;
    NI[0] = N;
    for (int j = 0; j < Lam.size(); j++)
    {
        NI[j + 1] = C[j];
    }

    std::vector<std::vector<double>> K = KRK(Reactivity, DeltaTime, Beta, Lam, NI, S);
    for (int j = 0; j < (Lam.size() + 1); j++)
    {
        NI[j] = NI[j] + DeltaTime * (K[0][j] + 2 * K[1][j] + 2 * K[2][j] + K[3][j]) / 6;
    }
    N = NI[0];
    for (int j = 0; j < (Lam.size()); j++)
    {
        C[j] = NI[j + 1];
    }
}

std::vector<std::vector<double>>
ReactorState::KRK(double ro, double step, std::vector<double> beta, std::vector<double> lam,
                  std::vector<double> NI, double Source)
{
    std::vector<std::vector<double>> K(4, std::vector<double>(beta.size() + 1)); // Матрица компонентов формулы для решения методом Рунге Кутты
    size_t KSize = beta.size() + 1;
    K[0][0] = ((ro - SumBeta) * NI[0]) / LAM + Source;
    for (int j = 0; j < KSize - 1; j++)
    {
        K[0][0] = K[0][0] + lam[j] * NI[j + 1];
    }
    for (int j = 1; j < KSize; j++)
    {
        K[0][j] = (beta[j - 1] * NI[0] / LAM - lam[j - 1] * NI[j]);
    }
    for (int i = 1; i < 3; i++)
    {
        K[i][0] = ((ro - SumBeta) * (NI[0] + (K[i - 1][0]) * step / 2)) / LAM + Source;
        for (int j = 0; j < KSize - 1; j++)
        {
            K[i][0] = K[i][0] + lam[j] * (NI[j + 1] + K[i - 1][j + 1] * step / 2);
        }
        for (int j = 1; j < KSize; j++)
        {
            K[i][j] = (beta[j - 1] * (NI[0] + K[i - 1][0] * step / 2) / LAM - lam[j - 1] * (NI[j] + K[i - 1][j] * step / 2));
        }
    }
    K[3][0] = ((ro - SumBeta) * (NI[0] + K[2][0] * step)) / LAM + Source;
    for (int j = 0; j < KSize - 1; j++)
    {
        K[3][0] = (K[3][0] + lam[j] * (NI[j + 1] + K[2][j + 1] * step));
    }
    for (int j = 1; j < KSize; j++)
    {
        K[3][j] = (beta[j - 1] * (NI[0] + K[2][0] * step) / LAM - lam[j - 1] * (NI[j] + K[2][j] * step));
    }
    return {K};
}

void ReactorState::StaticCalculate(double DeltaTime)
{
    double Reactivity = (Keff - 1) / Keff;
    N = -S * LAM / Reactivity;
    CalculateC();
}
