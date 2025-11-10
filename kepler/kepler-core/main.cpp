#include <iostream>
#include <memory>
#include "kepler/rocket/Rocket.h"
#include "kepler/rocket/RocketStage.h"
#include "kepler/rocket/NoseCone.h"
#include "kepler/rocket/FinSet.h"
#include "kepler/aero/Aerodynamics.h"
#include "kepler/environment/Environment.h"
#include "kepler/simulation/Simulation.h"



rocket galah() {
    //nosecone
    auto nosecone = std::make_shared<NoseCone>(NoseConeProfile.HAACK, 0.858, 0.156, 0, 1.656); //profile, lenght, base diameter, profile, mass
    auto nosetip = std::make_shared<Bulkhead>(0.03, 0.018, 0.045, 0.086);  // thickness, diamter, position from nosecone, mass
    nosecone.addInternalComponent(nosetip_bulkhead);

    // nose cone straight section
    auto nosecone_straight_profile = std::make_shared<BodyTube>(0.35, 0.156, 0.152, 0); //length, inner diam, outer diam, mass
    auto nosetip_bulkhead = std::make_shared<Bulkhead>(0.013, 0.05, 0.13, 0.0673);
    auto main_parachute = std::make_shared<Parachute>(3.05, 2.2, 12, 3.81, 0.42, 0.508, 0.11, 2.811); // diam, cd, n shroud lines, shroud line length, position, packed length, packed diameter, mass (to do add deploymenr)
    auto shock_cord_1 = std::make_shared<ShockCord>(0.4, 0.18, 0.24, 0.055, 0);  //length, position, packed length, packed diameter
    auto shock_cord_2 = std::make_shared<ShockCord>(0.4, 0.56, 0.35, 0.007, 0);  
    auto shock_cord_3 = std::make_shared<ShockCord>(12.5, 0.932, 0.074, 0.14, 0);  
    auto eye_bolt = std::make_shared<GenericMassComponent>(MassComponentType.RECOVERY, 0.12, 0.8, 0.071, 0.00435) //type, length, diameter, mass, position
    nosecone_straight_profile.addInternalComponent(nosetip_bulkhead);
    nosecone_straight_profile.addInternalComponent(main_parachute);
    nosecone_straight_profile.addInternalComponent(shock_cord_1);
    nosecone_straight_profile.addInternalComponent(shock_cord_2);
    nosecone_straight_profile.addInternalComponent(shock_cord_3);
    nosecone_straight_profile.addInternalComponent(eyebolt);

    //switchband
    switchband = std::make_shared<BodyTube>(0.051, 0.156, 0.153, 0);
    av_bay_coupler = std::make_shared<TubeCoupler>(0.33, 0.153, 0.15, 0.002, 0.602);
    auto main_bp_charge_wells = std::make_shared<GenericMassComponent>(MassComponentType.DEFAULT, 0.05, 0.13, 0.045); //type, length, diameter, mass, position
    auto u_bolt = std::make_shared<GenericMassComponent>(MassComponentType.RECOVERY, 0.083, 0.008, 0.071, 0.004) //type, length, diameter, mass, position
    auto forward_av_bulkhead = std::make_shared<Bulkhead>(0.014, 0.15, 1.07, 0.338);
    auto total_av = std::make_shared<GenericMassComponent>(MassComponentType.FC, 0.203, 0.12, 1.09, 1.25)
    auto aft_av_bulkhead = std::make_shared<Bulkhead>(0.014, 0.15, 1.39, 0.338);
    auto av_rod = std:make_shared<InnerTube>(0.33, 0.1, 0.078, 1.07, 0.69); 
    auto drogue_bp_charge_wells = std::make_shared<GenericMassComponent>(MassComponentType.DEFAULT, 0.05, 0.13, 0.045, 1.4); //type, length, diameter, mass, position
    av_bay_coupler.addInternalComponent(main_bp_charge_wells);
    av_bay_coupler.addInternalComponent(u_bolt);
    av_bay_coupler.addInternalComponent(forward_av_bulkhead);
    av_bay_coupler.addInternalComponent(total_av);
    av_bay_coupler.addInternalComponent(aft_av_bulkhead);
    av_bay_coupler.addInternalComponent(av_rod);
    av_bay_coupler.addInternalComponent(drogue_bp_charge_wells);
    switchband.addInternalComponent(switchband);

    //center body tube
    auto center_body_tube = std::make_shared<BodyTube>(1.1, 0.152, 0.156, 1.06);
    auto 3u_payload = std::make_shared<GenericMassComponent>(MassComponentType.DEFAULT, 0.05, 0.13, 0.045, 1.4); //type, length, diameter, mass, position
    auto drogue_parachute = std::make_shared<Parachute>(0.762, 2.2, 8, 1, 1.41, 0.35  , 0.14, 1.26); // diam, cd, n shroud lines, shroud line length, position, packed length, packed diameter, mass (to do add deploymenr)
    auto shock_cord_4 = std::make_shared<ShockCord>(0.4, 1.41, 0.051, 0.14, 0);  //length, position, packed length, packed diameter
    auto shock_cord_5 = std::make_shared<ShockCord>(0.4, 1.71, 0.051, 0.14, 0);  //length, position, packed length, packed diameter
    auto rail_button = std::make_shared<Protuberence>(0.016, 0.008, 0.003, 0.003, 0.011, 0, 2, 1.1, 2.19, 45, 0.002); //od, id, base height, flange height, total height, screw height, instance count, instance seperation, position, rotation, mass
    auto aft_recovery_bulkhead = std::make_shared<Bulkhead>(0.011, 0.152, 1.76, 0.433);
    auto u_bolt_2 = std::make_shared<GenericMassComponent>(MassComponentType.RECOVERY, 0.083, 0.008, 1.68, 0.004); //type, length, diameter, position, mass
    auto vent_assembly = std::make_shared<GenericMassComponent>(MassComponentType.DEFAULT, 0.12, 0.092, 2.24, 1.39);
    auto vent_closure = std::make_shared<TubeCoupler>(0.041, 0.152, 0, 2.34, 0.996);
    auto forward_truss = std::make_shared<GenericMassComponent>(0.18, 0.15, 2.18, 1);
    auto airbrakes = std::make_shared<GenericMassComponent>(MassComponentType.DEFAULT, 0.016, 0.15, 2.2, 1);
    auto cameras = std::make_shared<GenericMassComponent>(MassComponentType.DEFAULT, 0.074, 0.141, 1.78); 
    center_body_tube.addInternalComponent(3u_payload);
    center_body_tube.addInternalComponent(drogue_parachute);
    center_body_tube.addInternalComponent(shock_cord_4);
    center_body_tube.addInternalComponent(shock_cord_5);
    center_body_tube.addInternalComponent(rail_button);
    center_body_tube.addInternalComponent(aft_recovery_bulkhead);
    center_body_tube.addInternalComponent(u_bolt_2);
    center_body_tube.addInternalComponent(vent_assembly);
    center_body_tube.addInternalComponent(vent_closure);
    center_body_tube.addInternalComponent(forward_truss);
    center_body_tube.addInternalComponent(airbrakes);
    center_body_tube.addInternalComponent(cameras);

    //tank tube
    tank_tube = std::make_shared<BodyTube>(0.304, 0.156, 0, 0);
    tank_mass = std::make_shared<GenericMassComponent>(MassComponentType.DEFAULT, 0.386, 0.152, 2.33, 2.8);
    tank_tube.addInternalComponent(tank_mass)

    //boat tail stright
    boat_tail_straight_profile = std::make_shared<BodyTube>(0.56, 0.156, 0.152, 0.563);
    aft_rail_button_hardpoint = std::make_shared<GenericMassComponent>(MassComponentType.DEFAULT, 0.038, 0.014, 3.19, 0.026);
    rear_truss = std::make_shared<GenericMassComponent>(MassComponentType.DEFAULT, 0.152, 0.15, 2.67, 1);
    valve = std::make_shared<GenericMassComponent>(MassComponentType.DEFAULT, 0.07, 0.12, 2.71, 1.53);
    datalogger = std::make_shared<GenericMassComponent>(MassComponentType.DEFAULT, 0.05, 0.06, 2.75, 0.5);
    fill_closure  = std::make_shared<TubeCoupler>(0.041, 0.152, 0.152, 2.67, 1.13);
    boat_tail_straight_profile.addInternalComponent(aft_rail_button_hardpoint);
    boat_tail_straight_profile.addInternalComponent(rear_truss);
    boat_tail_straight_profile.addInternalComponent(valve);
    boat_tail_straight_profile.addInternalComponent(datalogger);
    boat_tail_straight_profile.addInternalComponent(fill_closure);

    //boat tail transition
    boat_tail_transition = std::make_shared<Transition>(NoseConeProfile.HAACK, 0.268, 0.156, 0.133, 0.002, 0);
    fins = std::make_shared<Fins>(4, 0, 0.005, 3.04, 0, 0.005, 1.49); //nfins, cant, thickness, position, rotation, fillet radius, mass
    phenolic = std::make_shared<InnerTube>(0.48, 0.114, 0.111, 3, 0.173);
    combustion_chamber = std::make_shared<GenericMassComponent>(0.671, 0.113, 2.83, 4.5);   
    phenolic.addInternalComponent(combustion_chamber);
    forward_centering_ring = std::make_shared<CenteringRing>(0.006, 0.152, 0.114, 3.01, 0.035);
    aft_centering_ring = std::make_shared<CenteringRing>(0.006, 0.152, 0.114, 3.39, 0.035);
    fin_dam_set = std::make_shared<GenericMassComponent>(0.382, 0.01, 3.02, 0.224 + 0.573);
    boat_tail_transition.addInternalComponent(fins);
    boat_tail_transition.addInternalComponent(phenolic);
    boat_tail_transition.addInternalComponent(forward_centering_ring);
    boat_tail_transition.addInternalComponent(aft_centering_ring);
    boat_tail_transition.addInternalComponent(fin_dam_set);

    // endcap
    endcap = std::make_shared<Transition>(NoseConeProfile.CONICAL, 0.04, 0.133, 0.121, 0.002, 0.376);

    stage = Stage() //what is the best way to define this class?
    return rocket([stage])

}


int main() {
    rocket galah = galah();
    rocket example_two_stage = two_stage()
    



    
};