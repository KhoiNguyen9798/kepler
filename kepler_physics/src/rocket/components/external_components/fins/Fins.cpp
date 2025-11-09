class Fin {
    private:
        double root_chord;
        double tip_chord;
        double height;
        double sweep; 
        double mass;
        double position_from_nose; // along centerline
        double thickness;
    public:
        Fin(double root_chord_, double tip_chord_, double height_, double sweep_, double
            position_from_nose_, double thickness_)
            : root_chord(root_chord_), tip_chord(tip_chord_), height(height_), sweep(sweep_),
              position_from_nose(position_from_nose_), thickness(thickness_) {}
        double getRootChord() const { return root_chord; }
        double getTipChord() const { return tip_chord; }
        double getHeight() const { return height; }
        double getSweep() const { return sweep; }
        double getMass() const { return mass; }
        double getPositionFromNose() const { return position_from_nose; }
        double getThickness() const { return thickness; }
}

