#include "SimpleGravityForce.h"

#define IGNORE_ORIGIN true // if false, gravity will not affect particles
                           // whose y-coordinate is < 0

SimpleGravityForce::SimpleGravityForce( const Vector2s& gravity )
: Force()
, m_gravity(gravity)
{
    assert( (m_gravity.array()==m_gravity.array()).all() );
    assert( (m_gravity.array()!=std::numeric_limits<scalar>::infinity()).all() );
}

SimpleGravityForce::~SimpleGravityForce()
{}

void SimpleGravityForce::addEnergyToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, scalar& E )
{
    assert( x.size() == v.size() );
    assert( x.size() == m.size() );
    assert( x.size()%2 == 0 );

    int size = x.size();
    for (int x = 0, y = 1; x < size; x += 2, y += 2) {
        E += -(m[x] * ((v[x] * m_gravity[0]) + (v[y] * m_gravity[1]))); // U(x) = -m(g . x)
    }
}

void SimpleGravityForce::addGradEToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, VectorXs& gradE )
{
    assert( x.size() == v.size() );
    assert( x.size() == m.size() );
    assert( x.size() == gradE.size() );
    assert( x.size()%2 == 0 );
    
    int size = x.size();
    for (int x0 = 0, x1 = 1; x0 < size; x0 += 2, x1 += 2) {
        if (IGNORE_ORIGIN || x[x1] > 0) {
            gradE[x0] += m[x0] * m_gravity[0];
            gradE[x1] += m[x1] * m_gravity[1];
        }
    }
}

void SimpleGravityForce::addHessXToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, MatrixXs& hessE )
{
    assert( x.size() == v.size() );
    assert( x.size() == m.size() );
    assert( x.size() == hessE.rows() );
    assert( x.size() == hessE.cols() );
    assert( x.size()%2 == 0 );
    // Nothing to do.
}

void SimpleGravityForce::addHessVToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, MatrixXs& hessE )
{
    assert( x.size() == v.size() );
    assert( x.size() == m.size() );
    assert( x.size() == hessE.rows() );
    assert( x.size() == hessE.cols() );
    assert( x.size()%2 == 0 );
    // Nothing to do.
}

Force* SimpleGravityForce::createNewCopy()
{
    return new SimpleGravityForce(*this);
}
