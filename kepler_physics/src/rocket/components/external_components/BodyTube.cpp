class BodyTube {
    private:
        double length;
        double outer_diameter;
        double inner_diameter;
        double mass;
    
    public:
        BodyTube(double len, double outer_dia, double inner_dia)
            : length(len), outer_diameter(outer_dia), inner_diameter(inner_dia) {}
        double getLength() const { return length; }
        double getOuterDiameter() const { return outer_diameter; }
        double getInnerDiameter() const { return inner_diameter; }
        double getMass() const { return mass; }
}