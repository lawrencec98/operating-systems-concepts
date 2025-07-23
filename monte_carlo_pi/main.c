#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_RANDOM_POINTS 1000000


typedef struct Point {
    float x;
    float y;
} Point;

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


void generateRandomPoints(Point* randomPointsArray)
{
    for (int i = 0; i < NUM_RANDOM_POINTS; i++)
    {
        randomPointsArray[i].x = randomFloatMinus1To1();
        randomPointsArray[i].y = randomFloatMinus1To1();
    }
}


float calculatePi(int num_points_inside, int num_points_total)
{
    return 4.0 * (float)num_points_inside / (float)num_points_total;
}


int main()
{
    // generate random points within the 2x2 square
    srand(time(NULL));

    Point randomPointsArray[NUM_RANDOM_POINTS];

    generateRandomPoints(randomPointsArray);

    int num_points_inside_circle = 0;

    for (int i = 0; i < NUM_RANDOM_POINTS; i++)
    {
        if (isInsideCircle(randomPointsArray[i].x, randomPointsArray[i].y))
        {
            printf("%f,%f\n", randomPointsArray[i].x, randomPointsArray[i].y);
            num_points_inside_circle++;
        }
    }

    float estimated_pi = calculatePi(num_points_inside_circle, NUM_RANDOM_POINTS);
    printf("Estimate for Pi is: %f\n", estimated_pi);

    return 0;
}