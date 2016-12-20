/*
  ==============================================================================

    PulseWave.cpp
    Created: 19 Nov 2016 4:34:55pm
    Author:  WangRex

  ==============================================================================
*/

#include "PulseWave.h"

PulseWave:: PulseWave( StkFloat frequency )
{
    if ( frequency <= 0.0 ) {
        oStream_ << "PulseWave::PulseWave: argument (" << frequency << ") must be positive!";
        handleError( StkError::FUNCTION_ARGUMENT );
    }
    setBandwidth(0.5);
    nHarmonics_ = 0;
    this->reset();
    this->setFrequency( frequency );
}

PulseWave :: ~PulseWave()
{
}

void PulseWave :: reset()
{
    phase_ = 0.0f;
    state_ = 0.0;
    lastFrame_[0] = 0.0;
}

void PulseWave :: setFrequency( StkFloat frequency )
{
    if ( frequency <= 0.0 ) {
        oStream_ << "PulseWave::setFrequency: argument (" << frequency << ") must be positive!";
        handleError( StkError::WARNING ); return;
    }
    
    p_ = Stk::sampleRate() / frequency;
    C2_ = 1 / p_;
    rate_ = PI * C2_;
    this->updateHarmonics();
}

void PulseWave :: setHarmonics( unsigned int nHarmonics )
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
    state_2 = - 0.5 * a_;
}

void PulseWave :: updateHarmonics( void )
{
    if ( nHarmonics_ <= 0 ) {
        unsigned int maxHarmonics = (unsigned int) floor( 0.5 * p_ );
        m_ = 2 * maxHarmonics + 1;
    }
    else
        m_ = 2 * nHarmonics_ + 1;
    
    a_ = m_ / p_;
}
