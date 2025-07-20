#include "../Include/Tuple.h"

#include <cstdlib>

#include <iostream>

#include <tuple>


//constructors
Tuple::Tuple(double x, double y, double z, double w) {
    this -> x = x;
    this -> y = y;
    this -> z = z;
    this -> w = w;
}

Tuple Tuple::point(double x, double y, double z) {
    return Tuple(x, y, z, 1);
}

Tuple Tuple::vector(double x, double y, double z) {
    return Tuple(x, y, z, 0);
}

Tuple Tuple::color(double x, double y, double z) {
    double r = x;
    double g = y;
    double b = z;

    return Tuple(r, g, b, -1);
}



//functions
bool Tuple::isEqual(Tuple one, Tuple two) {
    bool xEqual = floatingComp(one.x, two.x);
    bool yEqual = floatingComp(one.y, two.y);
    bool zEqual = floatingComp(one.z, two.z);
    bool wEqual = floatingComp(one.w, two.w);

    if (xEqual && yEqual && zEqual && wEqual) {
        return true;
    }
    return false;
}

Tuple Tuple::add(Tuple one, Tuple two) {
    double x, y, z, w;
    x = one.x + two.x;
    y = one.y + two.y;
    z = one.z + two.z;
    w = one.w + two.w;

    if (floatingComp(w, 1.0)) {
        Tuple result = Tuple::point(x, y, z);
        return result;
    } else if (floatingComp(w, 0.0)) {
        Tuple result = Tuple::vector(x, y, z);
        return result;
    }
    else if (floatingComp(w, -1.0)) {
        //color addition
        Tuple result = Tuple::color(x, y, z);
        return result;
    }
    else {
        std::cerr << "ERROR: Trying to add a point and a point, that makes no sense. Don't do that" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

Tuple Tuple::subtract(Tuple one, Tuple two) {
    double x, y, z, w;
    x = one.x - two.x;
    y = one.y - two.y;
    z = one.z - two.z;
    w = one.w - two.w;

    //the subtraction of two points yields a vector (1-1 = 0 in w field). Specifically it returns the vector pointing
    //from point 2 to point 1

    //the subtraction of two vectors yields a vector (0-0 = 0 in w field). The resulting vector is conceptually
    //the change in direction between the two vectors (from the tip of the second vector back to the tip of the first)
    //Docs/Vector-Vector_Result_Example.png

    //the subtraction of a vector from a point yields a point (1-0 = 1 in w field). This is conceptually moving
    //backwards by the specified vector

    //the subtraction of a point from a vector would yield nothing (0-1 = -1 (not valid in geometric space))
    if (floatingComp(w, 1.0)) {
        Tuple result = Tuple::point(x, y, z);
        return result;
    }
    else if (floatingComp(w, 0.0)) {
        Tuple result = Tuple::vector(x, y, z);
        return result;
    }
    else if (floatingComp(w, -1.0)) {
        //colors
        Tuple result = Tuple::color(x, y, z);
        return result;
    }
    else {
        throw std::logic_error ("ERROR: Non-supported subtraction. You likely tried to subtract a point from a vector,"
                     " which is not geometrically meaningful as it results in neither a point"
                     " nor a vector.");
    }
}

bool Tuple::floatingComp(double a, double b) {
    if (double EPSILON = 0.000001; std::abs(a - b) < EPSILON) {
        return true;
    }
    return false;
}

void Tuple::print()  {
    std::cout << "(" << x << ", " << y << ", " << z << ", " << w << ")" << std::endl;
}

Tuple Tuple::operator-() {
    //This will only work for vectors, as I can't imagine why you would need to negate a point
    //at the moment
    if (w != 0) {
        throw std::logic_error("Cannot negate a point. That makes no sense.");
    }

    //if a vector is going this --> way, this operator will return the vector that goes this <-- way
    Tuple result = Tuple::vector(-x, -y, -z);
    return result;
}

Tuple Tuple::scalarMultiply(Tuple tuple, double scalar) {
    double x, y, z;
    x = tuple.x * scalar;
    y = tuple.y * scalar;
    z = tuple.z * scalar;
    if (floatingComp(tuple.w, 1.0)) {
        Tuple result = Tuple::point(x, y, z);
        return result;
    }
    else if (floatingComp(tuple.w, 0.0)) {
        Tuple result = Tuple::vector(x, y, z);
        return result;
    }
    else if (floatingComp(tuple.w, -1.0)) {
        //color
        Tuple result = Tuple::color(x, y, z);
        return result;
    }
    else {
        throw std::logic_error("Neither a point nor a vector was fed in. This is not yet supported");
    }
}

Tuple Tuple::scalarDivide(Tuple tuple, double scalar) {
    double x, y, z;
    x = tuple.x / scalar;
    y = tuple.y / scalar;
    z = tuple.z / scalar;
    if (floatingComp(tuple.w, 1.0)) {
        Tuple result = Tuple::point(x, y, z);
        return result;
    }
    else if (floatingComp(tuple.w, 0.0)) {
        Tuple result = Tuple::vector(x, y, z);
        return result;
    }
    else {
        throw std::logic_error("Neither a point nor a vector was fed in. This is not yet supported");
    }
}

double Tuple::magnitude(Tuple vector) {
    //only for vectors
    if (floatingComp(vector.w, 1.0)) {
        throw std::logic_error("Magnitude of a point is not possible. A point is static, therfore has no magnitude.");
    }

    /*
     * the formula for finding the magnitude of a vector can be denoted by
     * M = sqrt(x^2 + y^2 + z^2)
     * Magnitude being more or less the cumulative 'size' of the vector
     */
    double magnitude = std::sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
    return magnitude;
}

Tuple Tuple::normalize(Tuple vector) {
    //only for vectors
    /*
     * we can normalize a vector by dividing each component by the magnitude of the overall vector
     */

    double magnitude = Tuple::magnitude(vector);
    if (magnitude < 0) {
        throw std::logic_error("Cannot normalize a vector with a negative magnitude.");
    }

    Tuple normalized = Tuple::vector((vector.x / magnitude), (vector.y / magnitude), (vector.z / magnitude));
    return normalized;
}

double Tuple::dotProduct(Tuple vector1, Tuple vector2)
{
    if (floatingComp(vector1.w, 1.0) || floatingComp(vector2.w, 1.0)) {
        throw std::logic_error("One of your dot product inputs is a point, not a vector. You can't just up and be doing that.");
    }
    /*
     * the dot product of two vectors can be computed by adding the products of corresponding components of each vecor
     * for instance, take two vectors of (1,2,3) and (4,5,6). The corresponding components would be
     * 1*4 + 2*5 + 3*6 for a scalar value of 32
     *
     * FUN FACT: The dot product of two vectors equals the product of their magnitudes and the cosine of the angle
     * between them. Meaning that if we know the dot product and the magnitudes of the two vectors, we can in fact
     * calculate the cosine. I will no doubt write this as a function later
     */

    double dotProduct = (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
    return dotProduct;
}

Tuple Tuple::crossProduct(Tuple vector1, Tuple vector2) {
    if (floatingComp(vector1.w, 1.0) || floatingComp(vector2.w, 1.0)) {
        throw std::logic_error("One of your dot product inputs is a point, not a vector. "
                               "You can't just up and be doing that.");
    }

    /*
     * the cross product of two vectors will return a new vector that is at right angles to both original vectors,
     * or put another way it will generate a vector that is perpendicular to both original vectors. It can be calculated
     * by (with given vectors A and B):
     *         x = | (Ay * Bz) - (Az * By)
     * A x B = y = | (Az * Bx) - (Ax * Bz)
     *         z = | (Ax * By) - (Ay * Bx)
     */

    double x = (vector1.y * vector2.z) - (vector1.z * vector2.y);
    double y = (vector1.z * vector2.x) - (vector1.x * vector2.z);
    double z = (vector1.x * vector2.y) - (vector1.y * vector2.x);

    Tuple cross = Tuple::vector(x, y, z);
    return cross;
}

Tuple Tuple::multiply(Tuple color1, Tuple color2) {
    //this is specifically for colors. Turns out that if you multiply one color by another color, what you get is the
    //blend of both colors. This is known as the Hadamard product
    //r*r, g*g and b*b. Simple

    Tuple result = Tuple::color(0,0,0);
    result.x = color1.x * color2.x;
    result.y = color1.y * color2.y;
    result.z = color1.z * color2.z;
    return result;
}