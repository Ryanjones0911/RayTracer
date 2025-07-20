#include <iostream>
#include "../Include/Tuple.h"

struct Projectile {
    Tuple position = Tuple::point(0,0,0);
    Tuple velocity = Tuple::vector(0,0,0);

    Projectile() {
        position = Tuple::point(0,0,0);
        velocity = Tuple::vector(0,0,0);
    };

    void print() {
        std::cout << position.x << ", " << position.y << ", " << position.z << "\n";
    }

};

struct Environment {
    Tuple gravity = Tuple::vector(0,9.81,0); //vector
    Tuple wind = Tuple::vector(0,0,0); //vector

    Environment() {
        gravity = Tuple::vector(0,-.1,0);
        wind = Tuple::vector(-.01,0,0);
    }

};

Projectile tick(Environment env, Projectile projectile) {
    Projectile newProjectile = projectile;

    newProjectile.position = Tuple::add(projectile.position, projectile.velocity);
    newProjectile.velocity = Tuple::add(Tuple::add(projectile.velocity, env.gravity), env.wind);
    if (newProjectile.position.y <= 0) {
        newProjectile.position.y = 0;
    }

    return newProjectile;
}

int main() {
    Projectile ball;
    Environment earth;
    double seconds = 1;

    ball.position = Tuple::point(0, 1, 0);
    ball.velocity = Tuple::normalize(Tuple::vector(1, 1, 0));

    std::cout << "Starting position: ";
    ball.print();

    while (seconds != 150) {
        ball = tick(earth, ball);
        ball.print();
        if (ball.position.y == 0) {
            ball.velocity.x *= .9;
        }
        if (std::abs(ball.velocity.x) < .01) {
            ball.velocity = Tuple::vector(0, 0, 0);
            std::cout << "Exhausted velocity. Projectile stopped\n";
            break;
        }
        seconds = seconds + .5;
    }
    std::cout << "Ending position: ";
    ball.print();

    return 0;
}//
// Created by Ryan Jones on 7/5/25.
//
