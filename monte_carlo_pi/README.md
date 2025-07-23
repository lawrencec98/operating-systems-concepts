An interesting way of calculating π is to use a technique known as Monte
Carlo, which involves randomization. This technique works as follows:
Suppose you have a circle inscribed within a square (Assume that the radius of this circle is 1.)

• First, generate a series of random points as simple (x, y) coordinates.
    These points must fall within the Cartesian coordinates that bound
    the square. Of the total number of random points that are generated,
    some will occur within the circle.

• Next, estimate π by performing the following calculation:
    π = 4× (number of points in circle) / (total number of points)


In this mini project I am writing a multithreaded version of this algorithm that creates a separate
thread to generate a number of random points. The thread will count the number of points that
occur within the circle and store that result in a global variable. When this thread has exited,
the parent thread will calculate and output the estimated value of π.

SAMPLE RESULTS:
    n is number of generated points

    n = 10,         pi = 3.600000
    n = 100,        pi = 3.280000
    n = 1000,       pi = 3.160000
    n = 10000,      pi = 3.104800
    n = 100000,     pi = 3.148760
    n = 1000000,    pi = 3.142516

    
Build: gcc -g -o out.exe main.c -lm