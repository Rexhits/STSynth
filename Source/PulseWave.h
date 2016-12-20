/*
  ==============================================================================

    PulseWave.h
    Created: 19 Nov 2016 4:34:55pm
    Author:  WangRex

  ==============================================================================
*/

#ifndef PULSEWAVE_H_INCLUDED
#define PULSEWAVE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
using namespace stk;

class PulseWave: public Generator
{
public:
    //! Class constructor.
    PulseWave( StkFloat frequency = 220.0 );
    
    //! Class destructor.
    ~PulseWave();
    
    //! Resets the oscillator state and phase to 0.
    void reset();
    
    //! Set the sawtooth oscillator rate in terms of a frequency in Hz.
    void setFrequency( StkFloat frequency );
    
    //! Set the number of harmonics generated in the signal.
    /*!
     This function sets the number of harmonics contained in the
     resulting signal.  It is equivalent to (2 * M) + 1 in the BLIT
     algorithm.  The default value of 0 sets the algorithm for maximum
     harmonic content (harmonics up to half the sample rate).  This
     parameter is not checked against the current sample rate and
     fundamental frequency.  Thus, aliasing can result if one or more
     harmonics for a given fundamental frequency exceeds fs / 2.  This
     behavior was chosen over the potentially more problematic solution
     of automatically modifying the M parameter, which can produce
     audible clicks in the signal.
     */
    void setHarmonics( unsigned int nHarmonics = 0 );
    void setBandwidth(StkFloat bandwidth_) {
        bandWidth = PI * bandwidth_;
    }
    
    //! Return the last computed output value.
    StkFloat lastOut( void ) const { return lastFrame_[0]; };
    
    //! Compute and return one output sample.
    StkFloat tick( void );
    
    //! Fill a channel of the StkFrames object with computed outputs.
    /*!
     The \c channel argument must be less than the number of
     channels in the StkFrames argument (the first channel is specified
     by 0).  However, range checking is only performed if _STK_DEBUG_
     is defined during compilation, in which case an out-of-range value
     will trigger an StkError exception.
     */
    StkFrames& tick( StkFrames& frames, unsigned int channel = 0 );
    
protected:
    
    void updateHarmonics( void );
    
    unsigned int nHarmonics_;
    unsigned int m_;
    StkFloat rate_;
    StkFloat phase_;
    StkFloat phase_1;
    StkFloat phase_2;
    StkFloat bandWidth;
    StkFloat p_;
    StkFloat C2_;
    StkFloat a_;
    StkFloat state_;
    StkFloat state_2;
    
};

inline StkFloat PulseWave :: tick( void )
{
    // The code below implements the BLIT algorithm of Stilson and
    // Smith, followed by a summation and filtering operation to produce
    // a sawtooth waveform.  After experimenting with various approaches
    // to calculate the average value of the BLIT over one period, I
    // found that an estimate of C2_ = 1.0 / period (in samples) worked
    // most consistently.  A "leaky integrator" is then applied to the
    // difference of the BLIT output and C2_. (GPS - 1 October 2005)
    
    // A fully  optimized version of this code would replace the two sin
    // calls with a pair of fast sin oscillators, for which stable fast
    // two-multiply algorithms are well known. In the spirit of STK,
    // which favors clarity over performance, the optimization has
    // not been made here.
    
    // Avoid a divide by zero, or use of a denormalized divisor
    // at the sinc peak, which has a limiting value of m_ / p_.
    
    phase_ += rate_;
    if ( phase_ >= PI ) phase_ -= PI;
    phase_2 = phase_ + 0.5 * bandWidth;
    phase_1 = phase_ - 0.5 * bandWidth;
    
    StkFloat tmp, denominator = sin( phase_1);
    if ( fabs(denominator) <= std::numeric_limits<StkFloat>::epsilon() )
        tmp = a_;
    else {
        tmp =  sin( m_ * phase_1 );
        tmp /= p_ * denominator;
    }
    tmp += state_ - C2_;
    state_ = tmp * 0.995;
    
    StkFloat tmp2, denominator2 = sin( phase_2 );
    if ( fabs(denominator2) <= std::numeric_limits<StkFloat>::epsilon() )
        tmp2 = a_;
    else {
        tmp2 =  sin( m_ * phase_2);
        tmp2 /= p_ * denominator2;
    }
    
    tmp2 += state_2 - C2_;
    state_2 = tmp2 * 0.995;
    
    
    if ( phase_2 >= PI ) phase_2 -= PI;
    
    lastFrame_[0] = tmp - tmp2;
    return lastFrame_[0];
}

inline StkFrames& PulseWave :: tick( StkFrames& frames, unsigned int channel )
{
#if defined(_STK_DEBUG_)
    if ( channel >= frames.channels() ) {
        oStream_ << "PulseWave::tick(): channel and StkFrames arguments are incompatible!";
        handleError( StkError::FUNCTION_ARGUMENT );
    }
#endif
    
    
    StkFloat *samples = &frames[channel];
    unsigned int hop = frames.channels();
    for ( unsigned int i=0; i<frames.frames(); i++, samples += hop )
        *samples = PulseWave::tick();
    
    return frames;
}




#endif  // PULSEWAVE_H_INCLUDED
