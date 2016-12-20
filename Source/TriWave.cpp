/*
  ==============================================================================

    TriWave.cpp
    Created: 18 Nov 2016 11:46:14pm
    Author:  WangRex

  ==============================================================================
*/

#include "TriWave.h"

Triwave:: Triwave( StkFloat frequency )
{
    if ( frequency <= 0.0 ) {
        oStream_ << "Triwave::Triwave: argument (" << frequency << ") must be positive!";
        handleError( StkError::FUNCTION_ARGUMENT );
    }
    
    nHarmonics_ = 0;
    this->reset();
    this->setFrequency( frequency );
}

Triwave :: ~Triwave()
{
}

void Triwave :: reset()
{
    phase_ = 0.0f;
    state_ = 0.0;
    lastFrame_[0] = 0.0;
}

void Triwave :: setFrequency( StkFloat frequency )
{
    if ( frequency <= 0.0 ) {
        oStream_ << "Triwave::setFrequency: argument (" << frequency << ") must be positive!";
        handleError( StkError::WARNING ); return;
    }
    
    p_ = Stk::sampleRate() / frequency;
    C2_ = 1 / p_;
//    rate_ =  C2_;
    this->updateHarmonics();
}

void Triwave :: setHarmonics( unsigned int nHarmonics )
{
    nHarmonics_ = nHarmonics;
    this->updateHarmonics();
    
    // I found that the initial DC offset could be minimized with an
    // initial state setting as given below.  This initialization should
    // only happen before starting the oscillator for the first time
    // (but after setting the frequency and number of harmonics).  I
    // struggled a bit to decide where best to put this and finally
    // settled on here.  In general, the user shouldn't be messing with
    // the number of harmonics once the oscillator is running because
    // this is automatically taken care of in the setFrequency()
    // function.  (GPS - 1 October 2005)
    state_ = -0.5 * a_;
}

void Triwave :: updateHarmonics( void )
{
    if ( nHarmonics_ <= 0 ) {
        unsigned int maxHarmonics = (unsigned int) floor( 0.5 * p_ );
        m_ = 2 * maxHarmonics + 1;
    }
    else
        m_ = 2 * nHarmonics_ + 1;
    
    a_ = m_ / p_;
}
