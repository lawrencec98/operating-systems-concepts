#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_RANDOM_POINTS 10


int isInsideCircle(float x, float y)
{
    float distance_from_circle_squared = (x-0)*(x-0) + (y-0)*(y-0);
    float distance_from_circle = sqrt(distance_from_circle_squared);
    
    return (distance_from_circle <= 1.0) ? 1 : 0;
}


float randomFloatMinus1To1()
{
    return ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
}


void generateRandomPoints(float* randomPointsArray)
{
    for (int i = 0; i < NUM_RANDOM_POINTS; i++)
    {
        randomPointsArray[i] = randomFloatMinus1To1();
    }
}


int main()
{
    // generate random points within the 2x2 square
    srand(time(NULL));

    float randomPointsArray[NUM_RANDOM_POINTS];

    generateRandomPoints(&randomPointsArray);

    // int inside = isInsideCircle(x,y);

    return 0;
}