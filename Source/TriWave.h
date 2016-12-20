/*
  ==============================================================================

    TriWave.h
    Created: 18 Nov 2016 11:46:14pm
    Author:  WangRex

  ==============================================================================
*/

#ifndef TRIWAVE_H_INCLUDED
#define TRIWAVE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
using namespace stk;

class Triwave: public Generator
{
public:
    //! Class constructor.
    Triwave( StkFloat frequency = 220.0 );
    
    //! Class destructor.
    ~Triwave();
    
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
    StkFloat p_;
    StkFloat C2_;
    StkFloat a_;
    StkFloat state_;
    StkFloat tmp = 0.0;
};

inline StkFloat Triwave :: tick( void )
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
    
    if ( tmp >= 1.0 ) tmp -= 1.0;

    StkFloat tri = 2.0 * fabs(2.0*tmp - 1.0) - 1.0;
    tmp += C2_;
    return tri;
}

inline StkFrames& Triwave :: tick( StkFrames& frames, unsigned int channel )
{
#if defined(_STK_DEBUG_)
    if ( channel >= frames.channels() ) {
        oStream_ << "Triwave::tick(): channel and StkFrames arguments are incompatible!";
        handleError( StkError::FUNCTION_ARGUMENT );
    }
#endif
    
    
    StkFloat *samples = &frames[channel];
    unsigned int hop = frames.channels();
    for ( unsigned int i=0; i<frames.frames(); i++, samples += hop )
        *samples = Triwave::tick();
    
    return frames;
}




#endif  // TRIWAVE_H_INCLUDED
