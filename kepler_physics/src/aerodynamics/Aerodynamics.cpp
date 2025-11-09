#pragma once
#include <cmath>
#include "Rocket.h"

class Aerodynamics {
private:
    Rocket rocket_;   // Rocket contains geometry + stage info

    double computeReynoldsNumber(double velocity, double L, double rho, double mu) const {
        return (rho * velocity * L) / mu;
    }

    double computeB(double Re) const {
        return 5e5 * ((0.074 / std::pow(Re, 0.2)) - (1.328 / std::sqrt(Re)));
    }

public:
    Aerodynamics(const Rocket& r) : rocket_(r) {}

    double computeDragCoefficient(double mach, double velocity, double rho, double aoa, double mu) {
        // aerodynamic features
        double L_total = rocket_.getLengthTotalRocket();
        double D_body  = rocket_.getDiameterBody();
        double L_body  = rocket_.getLengthBody();
        double L_nose  = rocket_.getLengthNoseCone();
        double D_base  = rocket_.getBaseDiameter();
        double L_base  = rocket_.getLengthBase();
        double L_fin   = rocket_.getMidchordLengthFins();
        double t_fin   = rocket_.getThicknessFins();
        int n_fins     = rocket_.getNFins();
        double A_fin_plan = rocket_.getAreaFinPlanform();
        double D_root  = rocket_.getDiameterBodyFinRoot();
        double A_fin_exp = rocket_.getAreaFinTotalExposed();
        double R_s = rocket_.getFinSectionRatio();

        // re number (fin + body)
        double Re_crit = 5e5;
        double Re_body = computeReynoldsNumber(velocity, L_body, rho, mu);
        double Re_fins = computeReynoldsNumber(velocity, L_fin, rho, mu);

        // cf (fin + body)
        double Cf_body, Cf_fins;
        if (Re_body < Re_crit)
            Cf_body = 1.328 / std::sqrt(Re_body);
        else
            Cf_body = (0.074 / std::pow(Re_body, 0.2)) - (1.328 / std::sqrt(Re_body)) + (computeB(Re_body) / Re_body);

        if (Re_fins < Re_crit)
            Cf_fins = 1.328 / std::sqrt(Re_fins);
        else
            Cf_fins = (0.074 / std::pow(Re_fins, 0.2)) - (1.328 / std::sqrt(Re_fins)) + (computeB(Re_fins) / Re_fins);

        // cd body
        double Cd_body = (1 + ((60 / std::pow((L_total / D_body), 3))
            + 0.0025 * (L_body / D_body)) *
            ((2.7 * (L_nose / D_body)) +
             (4 * (L_body / D_body)) +
             (2 * (1 - (D_base / D_body))) * (L_base / D_body)))
             * Cf_body;

        // cd fin 
        double Cd_fins = 2 * Cf_fins * (1 + 2 * (t_fin / L_fin)) *
            ((4 * n_fins * A_fin_plan) / (M_PI * std::pow(D_root, 2)));

        // cd base
        double Cd_base = 0.029 * (std::pow((D_base / D_body), 3) / std::sqrt(Cd_body));

        // cd interference
        double Cd_interf = 2 * Cf_fins * (1 + 2 * (t_fin / L_fin)) *
            ((4 * n_fins * (A_fin_plan - A_fin_exp)) / (M_PI * std::pow(D_root, 2)));

        // net cd @ 0 aoa
        double Cd_0 = Cd_body + Cd_fins + Cd_base + Cd_interf;

        // cd aoa (body)
        double sigma = 0.9;
        double n = 0.7;
        double Cd_alpha_body = (2 * sigma * std::pow(aoa, 2))
            + ((3.6 * n * (1.36 * L_total - 0.55 * L_nose) / (M_PI * D_body)) * std::pow(aoa, 3));

        // cd aoa (fins)
        double kappa_fb = 0.8065 * std::pow(R_s, 2) + 1.1553 * R_s; 
        double kappa_bf = 0.1935 * std::pow(R_s, 2) + 0.8174 * R_s + 1;
        double Cd_alpha_fin = std::pow(aoa, 2) * (1.2 * ((A_fin_plan * 4) / (M_PI * std::pow(D_root, 2))) +
            3.12 * (kappa_fb + kappa_bf - 1) * ((A_fin_exp * 4) / (M_PI * std::pow(D_root, 2))));

        // complete cd 
        double cd_net = Cd_0 + Cd_alpha_body + Cd_alpha_fin;

        // axial drag coefficient
        double cn = computeNormalCoefficient(velocity, rho, aoa, mu);
        double ca = (cd_net * std::cos(aoa) - 0.5 * cn * std::sin(2 * aoa)) / (1 - std::pow(std::sin(aoa), 2));

        return computeCompressibleFlowCorrection(mach, ca);
    }


    double computeCenterOfPressure() {
        double ln = rocket_.getLengthNoseCone();
        double CNalpha_nose = 2.0;
        double Xcp_nose = (2.0 / 3.0) * ln; // assuming conical
        int n_fins = rocket_.getNFins();
        double ls = rocket_.getFinSpan();
        double lm = rocket_.getFinMidChord();
        double lr = rocket_.getFinRootChord();
        double lt = rocket_.getFinTipChord();
        double df = rocket_.getDiameterBodyFinRoot();
        double dn = rocket_.getDiameterBody();
        double Xf = rocket_.getFinLeadingEdgeDistance();

        double Kfb = 1.0 + ((df / 2.0) / (ls + df / 2.0));
        double CNalpha_fins = Kfb * (4.0 * n_fins * std::pow(ls / dn, 2.0)) /
            (1.0 + std::sqrt(1.0 + std::pow(2.0 * lm / (lr + lt), 2.0)));

        double Xcp_fins = Xf + (lm * (lr + 2 * lt)) / (3.0 * (lr + lt))
            + (1.0 / 6.0) * (lr + lt - (lr * lt) / (lr + lt));

        double CNalpha_total = CNalpha_nose + CNalpha_fins;
        double Xcp_total = (CNalpha_nose * Xcp_nose + CNalpha_fins * Xcp_fins) / CNalpha_total;

        return Xcp_total;
    }
    double computeNormalCoefficient(double velocity, double rho, double aoa, double mu) {
        double D_ref = rocket_.getDiameterBody();
        double A_ref = M_PI * std::pow(D_ref * 0.5, 2);

        // nose
        double CNalpha_nose = 2.0;

        // fin
        int n_fins = rocket_.getNFins();
        if (n_fins <= 0) {
            return CNalpha_nose * aoa;
        }

        double ls = rocket_.getFinSpan();        
        double lm = rocket_.getFinMidChord();    
        double lr = rocket_.getFinRootChord();    
        double lt = rocket_.getFinTipChord();      
        double df = rocket_.getDiameterBodyFinRoot(); 

        // body interference 
        double K_fb = 1.0 + ( (df * 0.5) / (ls + df * 0.5) );

        // fins 
        double term = 2.0 * lm / (lr + lt);
        double CNalpha_fins =
            K_fb *
            (4.0 * n_fins * std::pow(ls / D_ref, 2.0)) /
            (1.0 + std::sqrt(1.0 + term * term));

        double CNalpha_cones = 0.0; 

        double CNalpha_total = CNalpha_nose + CNalpha_fins + CNalpha_cones;
        double Ap = rocket_.getPlanformAreaNoFins();
        double K_body = 1.0;
        double CNalpha_bodylift = K_body * (Ap / A_ref) * aoa; 
        CNalpha_total += CNalpha_bodylift;
        double CN = CNalpha_total * aoa;

        return computeCompressibleFlowCorrection(mach, CN);
    }   

    double computeCompressibleFlowCorrection(double mach, double C_i) {
        if (mach >= 0.8 && mach <= 1.1) {
            return C_i / (sqrt(1 - std::pow(0.8, 2)));
        }

        if (mach > 1) {
            return C_i / (sqrt(std::pow(mach, 2) - 1));
        }

        return c_i / sqrt(1 - std::pow(mach, 2));
    }
};
