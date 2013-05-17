// MUD Programming
// Ron Penton
// (C)2003
// BasicLibRandom.cpp - This file contains random number related functions.



#include "BasicLibRandom.h"

namespace BasicLib
{

// initialize the global generators with a seed of 0.
// it is up to the user to re-seed them as needed.
random Random( 0 );
random_percent_inclusive RandomPercent;
random_percent_exclusive RandomPercentExclusive;
random_range_inclusive RandomRange;
random_range_exclusive RandomRangeExclusive;
random_int RandomInt;
random_normal RandomNormal;
random_binomial RandomIntNormal;


} // end namespace BasicLib
