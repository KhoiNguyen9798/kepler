// reference frame: x -> along centerline, y -> up, # z -> out of the screen




class GenericMassComponent {
    private:
        double mass; 
        double x_offset; // with respect to centerline 
        double y_offset; // with respect to the nosetip
        double z_offset; // out of the screen
        double z_length;    // in z direction
        double y_length;   // in y direction
        double x_length;    // in x direction

    public:
        GenericMassComponent(double m, double x_off, double y_off)
            : mass(m), x_offset(x_off), y_offset(y_off) {}
        double getMass() const { return mass;}
        double getXOffset() const { return x_offset; }
        double getYOffset() const { return y_offset; }
        double getZOffset() const { return z_offset; }
        double getZLength() const { return z_length; }
        double getYLength() const { return y_length; }
        double getXLength() const { return x_length; }
}