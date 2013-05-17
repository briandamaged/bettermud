// MUD Programming
// Ron Penton
// (C)2003
// BasicLibRandom.h - This file contains random number related functions.


#ifndef BASICLIBRANDOM_H
#define BASICLIBRANDOM_H

#include <stdlib.h>
#include <math.h>

#include "BasicLibTypes.h"

namespace BasicLib
{


template<typename type, type modulus, type multiplier, type increment>
struct linear_congruency
{
    linear_congruency( type p_seed = 0 )
        : m_seed( p_seed )
    {  /* do nothing */ }


    void seed( type p_seed = 0 )
    {
        m_seed = p_seed;
    }


    type minimum() { return 0; }
    type maximum() { return modulus - 1; }

    type operator()()
    {
        m_seed = (multiplier * m_seed + increment) % modulus;
        return m_seed;
    }

protected:

    type m_seed;
};


typedef linear_congruency<uint32, 2147483648u, 1103515245, 12345> random;
//typedef linear_congruency<uint64, 18446744073709551615, 6364136223846793005, 12345> randon64;



// ----------------------------------------------------------------------------
//  returns a random double number from [0..1, inclusivity of 1 is 
//  configurable.
// ----------------------------------------------------------------------------
template< bool inclusive, typename generator = random >
struct random_percent
{
    random_percent() { init(); }
    random_percent( generator& p_generator )
        : m_generator( p_generator )    { init(); }

    void init()
    { 
        m_max = m_generator.maximum();

        // if 1.0 is exclusive, then the max should be incremented, so that
        // 1.0 is never generated.
        if( !inclusive )
            m_max += 1.0;
    }

    template< typename type >
    void seed( type p_seed )   { m_generator.seed( p_seed ); }

    double minimum() { return m_generator.minimum() / m_max; }
    double maximum() { return m_generator.maximum() / m_max; }

    double operator()()
    {
        return m_generator() / m_max;
    }

protected:
    generator m_generator;
    double m_max;

};


typedef random_percent<true> random_percent_inclusive;
typedef random_percent<false> random_percent_exclusive;



template<bool inclusive, typename generator = random_percent<inclusive> >
struct normal_generator
{

    normal_generator( double p_mean = 0, double p_sigma = 1 )
    {
        init( p_mean, p_sigma );
    }

    normal_generator( generator& p_generator, 
                      double p_mean = 0,
                      double p_sigma = 1 )
        : m_generator( p_generator )
    {
        init( p_mean, p_sigma );
    }

    void init( double p_mean, double p_sigma )
    { 
        m_mean = p_mean;
        m_sigma = p_sigma;
        m_valid = false;
    }



    double mean() { return m_mean; }
    double sigma() { return m_sigma; }
    void reset() { m_valid = false; }

    double operator()()
    {
        if(!m_valid) 
        {
            m_rho1 = m_generator();
            m_rho2 = m_generator();
            m_rho = sqrt(-2 * log(1- m_rho2));
            m_valid = true;
        } 
        else 
        {
            m_valid = false;
        }

        return m_rho * ( m_valid ? cos(2 * pi * m_rho1) : sin( 2 * pi * m_rho1)) * m_sigma + m_mean;
    }

private:
  generator m_generator;
  double m_mean;
  double m_sigma;
  double m_rho1, m_rho2, m_rho;
  bool m_valid;
};


typedef normal_generator<true> random_normal;





// ----------------------------------------------------------------------------
//  returns a random double number from [a..b, inclusivity of b is 
//  configurable.
// ----------------------------------------------------------------------------
template< bool inclusive, typename generator = random_percent<inclusive> >
struct random_range
{
    random_range( double a = 0, double b = 1 ) 
    { 
        init( a, b );
    }

    random_range( generator& p_generator, double a = 0, double b = 1 )
        : m_generator( p_generator )    
    { 
        init( a, b );
    }

    void init( double a, double b )
    { 
        m_range = b - a;
        m_offset = a;
    }

    template< typename type >
    void seed( type p_seed )   { m_generator.seed( p_seed ); }

    double minimum() { return m_generator.minimum() * m_range + m_offset; }
    double maximum() { return m_generator.maximum() * m_range + m_offset; }

    double generate( double p_range, double p_offset )
    {
        return m_generator() * p_range + p_offset;
    }

    double operator()()
    {
        return generate( m_range, m_offset );
    }

    double operator()( double a, double b )
    {
        return generate( b - a, a );
    }

protected:
    generator m_generator;
    double m_range;
    double m_offset;

};


typedef random_range<true> random_range_inclusive;
typedef random_range<false> random_range_exclusive;







// ----------------------------------------------------------------------------
//  returns a random integer from [a..b]
// ----------------------------------------------------------------------------
template< typename generator = random_percent_exclusive >
struct random_int_range
{
    random_int_range( sint32 a = 0, sint32 b = 1 ) 
    { 
        init( a, b );
    }

    random_int_range( generator& p_generator, sint32 a = 0, sint32 b = 1 )
        : m_generator( p_generator )    
    { 
        init( a, b );
    }

    void init( sint32 a, sint32 b )
    { 
        m_range = b - a + 1;
        m_offset = a;
    }

    template< typename type >
    void seed( type p_seed )   { m_generator.seed( p_seed ); }

    sint32 minimum() { return (sint32)(m_generator.minimum() * m_range) + m_offset; }
    sint32 maximum() { return (sint32)(m_generator.maximum() * m_range) + m_offset; }

    sint32 generate( sint32 p_range, sint32 p_offset )
    {
        return (sint32)(m_generator() * p_range) + p_offset;
    }

    sint32 operator()()
    {
        return generate( m_range, m_offset );
    }

    sint32 operator()( sint32 a, sint32 b )
    {
        return generate( b - a + 1, a );
    }

protected:
    generator m_generator;
    sint32 m_range;
    sint32 m_offset;

};

typedef random_int_range<> random_int;


// ----------------------------------------------------------------------------
//  returns a "simulated binomial" random number by adding N RNG's together.
// ----------------------------------------------------------------------------
template< sint32 N = 4, typename generator = random_int >
struct simulated_binomial
{
    simulated_binomial( sint32 a = 0, sint32 b = 1 ) 
    { 
        init( a, b );
    }

    simulated_binomial( generator& p_generator, sint32 a = 0, sint32 b = 1 )
        : m_generator( p_generator )    
    { 
        init( a, b );
    }

    void init( sint32 a, sint32 b )
    { 
        m_range = b - a;
        m_offset = a;
    }

    template< typename type >
    void seed( type p_seed )   { m_generator.seed( p_seed ); }

    sint32 minimum() { return m_offset; }
    sint32 maximum() { return m_range + m_offset; }

    sint32 generate( sint32 p_range, sint32 p_offset )
    {
        sint32 minorrange = p_range / N;
        sint32 mod = p_range % N;

        sint32 sum = 0;

        for( int i = 0; i < N; i++ )
        {
            if( mod > i )   // add 1 to the first range%N ranges, in case
                            // the range isn't divisible by N
                sum += m_generator( 0, minorrange + 1 );
            else
                sum += m_generator( 0, minorrange );
        }

        return sum + p_offset;
    }

    sint32 operator()()
    {
        return generate( m_range, m_offset );
    }

    sint32 operator()( sint32 a, sint32 b )
    {
        return generate( b - a, a );
    }

protected:
    generator m_generator;
    sint32 m_range;
    sint32 m_offset;
};


typedef simulated_binomial<> random_binomial;


// ----------------------------------------------------------------------------
//  Global RNGs for the C-like RNG functions
// ----------------------------------------------------------------------------
extern random Random;
extern random_percent_inclusive RandomPercent;
extern random_percent_exclusive RandomPercentExclusive;
extern random_range_inclusive RandomRange;
extern random_range_exclusive RandomRangeExclusive;
extern random_int RandomInt;
extern random_normal RandomNormal;
extern random_binomial RandomIntNormal;
    

} // end namespace BasicLib


#endif

