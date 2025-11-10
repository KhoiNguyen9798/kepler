#pragma once
#include <cmath>
#include "Rocket.h"

class Aerodynamics {
private:
    Rocket rocket_;

    double computeReynoldsNumber(double velocity, double L, double rho, double mu) const;
    double computeB(double Re) const;

public:
    explicit Aerodynamics(const Rocket& r);

    double computeDragCoefficient(double mach, double velocity, double rho, double aoa, double mu);
    double computeCenterOfPressure();
    double computeNormalCoefficient(double velocity, double rho, double aoa, double mu);
    double computeCompressibleFlowCorrection(double mach, double C_i);
};

