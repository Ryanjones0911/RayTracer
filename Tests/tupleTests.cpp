#include <gtest/gtest.h>
#include "../Include/Tuple.h"


//Prove that a Tuple is a point when W is 1 and a vector when W is 0
TEST(tupleTests, PointWhen1AndVectorWhen0) {
    Tuple point = Tuple::point(1.4, 2.3, 5.6);
    Tuple vector = Tuple::vector(3.6543, 2.543, 1.32);
    EXPECT_EQ(point.w, 1);
    EXPECT_EQ(vector.w, 0);
}
//Prove that a Point constructor makes a point
TEST(tupleTests, ProvePoint) {
    Tuple point = Tuple::point(1,2,3);
    EXPECT_EQ(point.w, 1);
}

//Prove that a Vector constructor makes a Vector
TEST(tupleTests, ProveVector) {
    Tuple vector = Tuple::vector(1,2,3);
    EXPECT_EQ(vector.w, 0);
}

//Tests tuple equality
TEST(tupleTests, Equality){
    Tuple point = Tuple::point(1.5432,2.3464,3.4332346);
    Tuple eqPoint = Tuple::point(1.5432,2.3464,3.4332346);
    Tuple neqPoint = Tuple::point(1,2,4);

    EXPECT_TRUE(Tuple::isEqual(point, eqPoint));
    EXPECT_FALSE(Tuple::isEqual(point, neqPoint));
}

//add two tuples
TEST(tupleTests, Addition) {
    Tuple point = Tuple::point(1,-2,3);
    Tuple vector = Tuple::vector(4,5,6);
    Tuple vector2 = Tuple::vector(7,8,9);
    Tuple result = Tuple::point(5, 3, 9);
    Tuple shouldEvalPoint = Tuple::add(point, vector);
    Tuple shouldEvalVector = Tuple::add(vector, vector2);

    EXPECT_TRUE(Tuple::isEqual(Tuple::add(point, vector), result));
    EXPECT_EQ(shouldEvalPoint.w, 1);
    EXPECT_EQ(shouldEvalVector.w, 0);
}

//the subtraction of two points yields a vector (1-1 = 0 in w field)
TEST(tupleTests, Subtraction2Points) {
    Tuple point = Tuple::point(1,2,3);
    Tuple point2 = Tuple::point(4,5,6);
    Tuple result = Tuple::vector(-3,-3,-3);

    EXPECT_TRUE(Tuple::isEqual(Tuple::subtract(point, point2), result));
}

//the subtraction of two vectors yields a vector (0-0 = 0 in w field)
TEST(tupleTests, Subtraction2Vectors) {
    Tuple vector = Tuple::vector(1,2,3);
    Tuple vector2 = Tuple::vector(4,5,6);
    Tuple result = Tuple::vector(-3,-3,-3);

    EXPECT_TRUE(Tuple::isEqual(Tuple::subtract(vector, vector2), result));
}

//the subtraction of a vector from a point yields a point (1-0 = 1 in w field)
TEST(tupleTests, SubtractionPointVector) {
    Tuple point = Tuple::point(1,2,3);
    Tuple vector = Tuple::vector(4,5,6);
    Tuple result = Tuple::point(-3,-3,-3);

    EXPECT_TRUE(Tuple::isEqual(Tuple::subtract(point, vector), result));
}

//subtracting the zero vector from a vector gives you that vector's negation
TEST(tupleTests, NegateVectorSub) {
    Tuple vector = Tuple::vector(1,2,3);
    Tuple zeroVector = Tuple::vector(0,0,0);
    Tuple result = Tuple::vector(-1,-2,-3);

    EXPECT_TRUE(Tuple::isEqual(Tuple::subtract(zeroVector, vector), result));
}

//using the negate overload on a vector does the same as subtracting by the zero vector
TEST(tupleTests, NegateVectorOverload) {
    Tuple vector = Tuple::vector(1,2,3);
    Tuple negation = -vector;
    Tuple result = Tuple::vector(-1,-2,-3);

    EXPECT_TRUE(Tuple::isEqual(negation, result));
}

//multiply by a scalar
TEST(tupleTests, ScalarMult) {
    Tuple vector = Tuple::vector(1,2,3);
    double scalar = 3.5;
    double scalar2 = .5;
    Tuple result = Tuple::vector(3.5, 7, 10.5);
    Tuple result2 = Tuple::vector(.5, 1, 1.5);

    EXPECT_TRUE(Tuple::isEqual(Tuple::scalarMultiply(vector, scalar), result));
    EXPECT_TRUE(Tuple::isEqual(Tuple::scalarMultiply(vector, scalar2), result2));
}

//divide by a scalar
TEST(tupleTests, ScalarDiv) {
    Tuple vector = Tuple::vector(1,2,3);
    double scalar = 2;
    Tuple result = Tuple::vector(.5, 1, 1.5);

    EXPECT_TRUE(Tuple::isEqual(Tuple::scalarDivide(vector, scalar), result));
}

//the magnitude of a vector with nothing but 1 value should be 1
//i.e. (1,0,0) or anything like that should be 1
TEST(tupleTests, Mag1) {
    Tuple vector = Tuple::vector(1,0,0);
    Tuple vector2 = Tuple::vector(0,1,0);
    Tuple vector3 = Tuple::vector(0,0,1);
    EXPECT_EQ(Tuple::magnitude(vector), 1);
    EXPECT_EQ(Tuple::magnitude(vector2), 1);
    EXPECT_EQ(Tuple::magnitude(vector3), 1);
}

//more complicated magnitude test
TEST(tupleTests, MagComplex) {
    Tuple vector = Tuple::vector(68.54, 34.32, 17.78);

    EXPECT_NEAR(Tuple::magnitude(vector), 78.687, 1e-2);
}

//normalization
TEST(tupleTests, Normalize) {
    Tuple vector = Tuple::vector(4,0,0);
    Tuple normalized = Tuple::normalize(vector);
    Tuple result = Tuple::vector(1,0,0);

    EXPECT_TRUE(Tuple::isEqual(normalized, result));

    Tuple vector2 = Tuple::vector(1,2,3);
    Tuple normalized2 = Tuple::normalize(vector2);
    Tuple result2 = Tuple::vector(0.267261, 0.534522, 0.801784);

    EXPECT_EQ(Tuple::isEqual(normalized2, result2), true);
}

//dot products
TEST(tupleTests, DotProduct) {
    Tuple vector = Tuple::vector(1,2,3);
    Tuple vector2 = Tuple::vector(4,5,6);
    double result = 32;

    EXPECT_EQ(Tuple::dotProduct(vector, vector2), result);
}

//cross products
TEST(tupleTests, CrossProduct) {
    Tuple vector = Tuple::vector(1,2,3);
    Tuple vector2 = Tuple::vector(4,5,6);
    Tuple result = Tuple::crossProduct(vector, vector2);
    Tuple check = Tuple::vector(-3,6,-3);

    EXPECT_TRUE(Tuple::isEqual(result, check));

    Tuple vector3 = Tuple::vector(3.553, 2.873, 1.894);
    Tuple vector4 = Tuple::vector(175.25, 784.27, 794.247);
    Tuple result2 = Tuple::crossProduct(vector3, vector4);
    Tuple check2 = Tuple::vector(796.464251,-2490.036091,2283.01806);
    EXPECT_TRUE(Tuple::isEqual(result2, check2));
}

//test colors
TEST(tupleTests, Colors) {
    Tuple color = Tuple::color(1,2,3);

    EXPECT_EQ(color.r(), 1);
    EXPECT_EQ(color.g(), 2);
    EXPECT_EQ(color.b(), 3);
    EXPECT_EQ(color.w, -1);
}

//test Hadamard product (just multiplying colors)
TEST(tupleTests, Hadamard) {
    Tuple color = Tuple::color(1,2,3);
    Tuple color2 = Tuple::color(2,3,4);
    Tuple result = Tuple::multiply(color, color2);
    Tuple check = Tuple::color(2, 6, 12);

    EXPECT_TRUE(Tuple::isEqual(result, check));
}