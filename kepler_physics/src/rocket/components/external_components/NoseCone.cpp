enum NoseConeType {
    Conical,
    Ogive, 
    Ellipisoid, 
    Power, 
    Haack
}

class NoseCone {
    private:
        NoseConeType type; 
        double length; 
        double wall_thickness;
        double profile_parameter; // for power and haack types
        double mass;
    
    public:
        NoseCone(NoseConeType t, double len, double wall_thick, double profile_param = 0.0)
            : type(t), length(len), wall_thickness(wall_thick), profile_parameter(profile_param) {}

        // getters
        double getLength() const { return length; }
        double getWallThickness() const { return wall_thickness; }
        NoseConeType getType() const { return type; }
        double getProfileParameter() const { return profile_parameter; }
        double getMass() const { return mass; }

        // setters (TBD)
}  