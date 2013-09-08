#ifndef __EXPLICIT_EULER__
#define __EXPLICIT_EULER__

#include "SceneStepper.h"
#include "MathDefs.h"
#include <iostream>

using namespace std;

class ExplicitEuler : public SceneStepper
{
public:
    ExplicitEuler();
    virtual ~ExplicitEuler();
    
    virtual bool stepScene( TwoDScene& scene, scalar dt );
    
    virtual std::string getName() const;
};

#endif
