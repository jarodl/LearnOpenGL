#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>
#include <time.h>

class Random
{
public:
	Random(void) {}

	static float GenerateRandomNumber(float lowerBound, float upperBound)
	{
		static bool firstTime = true;
		static time_t randomNumberSeed;
		if (firstTime)
		{
			time(&randomNumberSeed);
			firstTime = false;
			srand((unsigned int)randomNumberSeed);
		}
		return (lowerBound + ((upperBound - lowerBound) * (float(rand()) / RAND_MAX)));
	}

};
#endif