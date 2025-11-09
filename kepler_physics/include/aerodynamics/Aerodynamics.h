#ifndef AERODYNAMICS_H
#define AERODYNAMICS_H

#pragma once
#include <cmath>
#include "Rocket.h"

class Aerodynamics {
private:
    Rocket rocket_;   // Rocket contains geometry + stage info

    double computeReynoldsNumber(double velocity, double L, double rho, double mu) const;
    double computeB(double Re) const;
    double computeCompressibleFlowCorrection(double mach, double C_i);

public:
    Aerodynamics(const Rocket& r);

    double computeDragCoefficient(double mach, double velocity, double rho, double aoa, double mu);
    double computeNormalCoefficient(double velocity, double rho, double aoa, double mu);
    double computeCenterOfPressure();
};

#endif // AERODYNAMICS_H
