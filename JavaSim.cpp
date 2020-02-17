#include "JavaSim.hpp"
#include "CacheEmitter.hpp"
#include <fstream>
#include <random>
using namespace std;

/*
 * This file defines the functions decalred in JavaSim.hpp
 *  Creation of a 2D int array of size mxn simulating the method Java uses to do so
 */
int** makeJavaArray(int n, int m)
{
    /*Note that beacuse the matrix multiply method occurs within the scope of a method, java
    garbage collection doesn't need to be taken into account. Simple memory management of auto
    scope variables will be sufficient.*/

    /*2D array is a pointer to other pointers*/
    int** multiArray;
    /*Now the variable m for rows dictates how many pointers are in this array of pointers*/
    multiArray = new int*[m];  /*The new keyword is used to dynamically allocate memory*/
    /*The variable n represents the number of elements in the rows of this array*/
    for (int i = 0; i < m; i++) {
        multiArray[i] = new int[n]; /*Dynamically allocate an array of size n at every row m of multiArray*/
    }

    /*By dynamically allocating the memory for the array of pointers, and then separately each of array of integers within, this
    method simulates how each array within a Java multidimensional array cannot e guarunteed to be in sequential memory locations.
    This is beacause Java creates arrays as objects, and allocates them in the same way.*/

    /*Uses the Mercenne twister engine for random number generation*/
    random_device rando;    /* random device is a seed for the mersenne twister */
    mt19937 engine{ rando() };  /* Mersenne twister engine provides seudo random numbers */
    uniform_real_distribution<double> distrib{ 0.0,15.0 }; /* bottleneck the engine to produce values in range */
    /* Note that the values in the distribution are inclusive on both ends*/
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            multiArray[m][n] = (int)distrib(engine); /* Place a randomly generated number at each index */
        }
    }

    
	return multiArray;  /*Return our new dynamically allocated multidimensional array*/
}

/* The same matrix building method, using the double precision floating point data type */
double** makeJavaDoubleArray(int n, int m) {
    double** multiArray;
    multiArray = new double* [m];
    for (int i = 0; i < m; i++) {
        multiArray[i] = new double[n];
    }

    /*Uses the Mercenne twister engine for random number generation*/
    random_device rando;    /* random device is a seed for the mersenne twister */
    mt19937 engine{ rando() };  /* Mersenne twister engine provides seudo random numbers */
    uniform_real_distribution<double> distrib{ 0.0,15.0 }; /* bottleneck the engine to produce values in range */
    /* Note that the values in the distribution are inclusive on both ends*/

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            multiArray[m][n] = distrib(engine); /* Place a randomly generated number at each index */
        }
    }

    return multiArray;
}

/* The same matrix building method, using the floating point data type */
float** makeJavaFloatArray(int n, int m) {
    float** multiArray;
    multiArray = new float* [m];
    for (int i = 0; i < m; i++) {
        multiArray[i] = new float[n];
    }


    /*Uses the Mercenne twister engine for random number generation*/
    random_device rando;    /* random device is a seed for the mersenne twister */
    mt19937 engine{ rando() };  /* Mersenne twister engine provides seudo random numbers */
    uniform_real_distribution<float> distrib{ 0.0,15.0 }; /* bottleneck the engine to produce values in range */
    /* Note that the values in the distribution are inclusive on both ends*/

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            multiArray[m][n] = distrib(engine); /* Place a randomly generated number at each index */
        }
    }

    return multiArray;
}

