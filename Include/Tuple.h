#ifndef TUPLE_H
#define TUPLE_H

#include <iostream>
#include <__ostream/basic_ostream.h>

class Tuple {
public:
    double x;
    double y;
    double z;
    double w;

    //"constructors" for points, colors and vectors, respectively
    static Tuple point(double x, double y, double z);
    static Tuple vector(double x, double y, double z);
    static Tuple color(double x, double y, double z);
    Tuple() = default; //don't use this raw

    double r() const { return x; }
    double g() const { return y; }
    double b() const { return z; }


    //destructor
    ~Tuple() = default;

    //static functions
    static bool isEqual(Tuple one, Tuple two);
    static Tuple add(Tuple one, Tuple two);
    static Tuple subtract(Tuple one, Tuple two);

    //only for vectors (scalar multiply for colors too
    static Tuple scalarMultiply(Tuple tuple, double scalar);
    static Tuple scalarDivide(Tuple vector, double scalar);
    static double magnitude(Tuple vector);
    static Tuple normalize(Tuple vector);
    static double dotProduct(Tuple vector1, Tuple vector2);
    static Tuple crossProduct(Tuple vector1, Tuple vector2);

    //colors
    static Tuple multiply(Tuple color1, Tuple color2);



    //non-static functions
    void print();
    Tuple operator-();

private:
    /*
     * pure tuple constructor is private because we don't want user dealing
     * with raw tuples, rather we want them making vectors and points.
     */

    Tuple(double x, double y, double z, double w);
    static bool floatingComp(double a, double b);

};

#endif //TUPLE_H