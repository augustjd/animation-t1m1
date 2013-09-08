#include "ExplicitEuler.h"
#include <iostream>

ExplicitEuler::ExplicitEuler()
: SceneStepper()
{}

ExplicitEuler::~ExplicitEuler()
{}

bool ExplicitEuler::stepScene( TwoDScene& scene, scalar dt )
{
    // Your code goes here!
    
    // Some tips on getting data from TwoDScene:
    // A vector containing all of the system's position DoFs. x0, y0, x1, y1, ...
    //VectorXs& x = scene.getX();
    // A vector containing all of the system's velocity DoFs. v0, v0, v1, v1, ...
    //VectorXs& v = scene.getV();
    // A vector containing the masses associated to each DoF. m0, m0, m1, m1, ...
    //const VectorXs& m = scene.getM();
    // Determine if the ith particle is fixed
    // if( scene.isFixed(i) )
    VectorXs& x = scene.getX();
    VectorXs& v = scene.getV();

    const VectorXs& F = scene.getF();

    const VectorXs& m = scene.getM();

    assert(x.rows() == v.rows() && v.rows() == m.rows()); // we need to be sure that all objects are properly
                                              // accounted for, in position, velocity, and mass
    int particles = scene.getNumParticles();

    int x0 = 0;
    int x1 = 0;
    for(int p = 0; p < particles; ++p) {
        if ( !scene.isFixed(p) ) {
            // Set the indicies for axes 0 and 1
            x0 = 2 * p;
            x1 = 2 * p + 1;

            Vector2s new_pos(x[x0] + (v[x0] * dt), x[x1] + (v[x1] * dt));
            Vector2s new_vel(v[x0] + (dt / m[x0]) * F[x0], v[x1] + (dt / m[x1]) * F[x1]);
            
            scene.setPosition(p, new_pos);
            scene.setVelocity(p, new_vel);
        }
    }
    
    return true;
}

std::string ExplicitEuler::getName() const
{
    return "Explicit Euler";
}
