#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <omp.h>

#define NUM_RANDOM_POINTS 1000000


typedef struct Point 
{
    float x;
    float y;
} Point;


typedef struct CountInsideCircleArgs
{
    Point* random_points;
    int result;
} CountInsideCircleArgs;


typedef struct calculatePiArgs 
{
    int points_inside;
    float result;
} calculatePiArgs;


int isInsideCircle(float x, float y)
{
    float distance_from_circle_squared = (x-0)*(x-0) + (y-0)*(y-0);
    float distance_from_circle = sqrt(distance_from_circle_squared);
    
    return (distance_from_circle <= 1.0) ? 1 : 0;
}


// float randomFloatMinus1To1()
// {
//     return ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
// }


void generateRandomPoints(Point* randomPointsArray)
{
    #pragma omp parallel for
    for (int i = 0; i < NUM_RANDOM_POINTS; i++)
    {
        unsigned int seed = time(NULL) ^ omp_get_thread_num();
        float x = ((float)rand_r(&seed) / RAND_MAX) * 2.0f - 1.0f;
        float y = ((float)rand_r(&seed) / RAND_MAX) * 2.0f - 1.0f;
        randomPointsArray[i].x = x;
        randomPointsArray[i].y = y;
    }
}


void* CountInsideCircle(void* arg_struct)
{
    CountInsideCircleArgs* arg = (CountInsideCircleArgs*) arg_struct;

    int num_points_inside_circle = 0;

    #pragma omp parallel for
    for (int i = 0; i < NUM_RANDOM_POINTS; i++)
    {
        if (isInsideCircle(arg->random_points[i].x, arg->random_points[i].y))
        {
            num_points_inside_circle++;
        }
    }

    arg->result = num_points_inside_circle;
    arg_struct = arg;

    return arg_struct;
    // pthread_exit(NULL);
}


void* calculatePi(void* arg_struct)
{
    calculatePiArgs* arg = (calculatePiArgs*) arg_struct;

    float estimate_pi = 4.0 * (float)arg->points_inside / NUM_RANDOM_POINTS;

    arg->result = estimate_pi;
    arg_struct = arg;

    return arg_struct;
    // pthread_exit(NULL);
}


int main()
{
    // generate random points within the 2x2 square
    srand(time(NULL));

    pthread_t thread2;
    void* ret;

    Point randomPointsArray[NUM_RANDOM_POINTS];
    
    generateRandomPoints(randomPointsArray);

    CountInsideCircleArgs args1;
    args1.random_points = randomPointsArray;

    CountInsideCircle(&args1);

    calculatePiArgs args2;
    args2.points_inside = args1.result;
    
    pthread_create(&thread2, NULL, calculatePi, &args2);
    pthread_join(thread2,&ret);

    printf("Estimate for Pi is: %f\n", args2.result);

    return 0;
}