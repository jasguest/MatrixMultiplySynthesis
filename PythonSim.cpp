#include "PythonSim.hpp"
#include <random>
using namespace std;

/* Python is row major, so the memory allocation will be row following row to represent the multidimensional array*/
int* makePythonArray(int n, int m)
{
	/*Representing a multidimensional array in 1D, the length will be m*n*/
	int size = m * n;
	int* multiArray = new int[size];	/*Initialize an array of size m*n*/
	/*Will need a method used to get the value at a specific index */

	/*Uses the Mercenne twister engine for random number generation*/
	random_device rando;    /* random device is a seed for the mersenne twister */
	mt19937 engine{ rando() };  /* Mersenne twister engine provides seudo random numbers */
	uniform_real_distribution<double> distrib{ 0.0,15.0 }; /* bottleneck the engine to produce values in range */
	/* Note that the values in the distribution are inclusive on both ends*/

	for (int i = 0; i < size; i++) {
		multiArray[i] = (int)distrib(engine);	// fill each index with a random number
	}

	return multiArray;
}

double* makePythonDoubleArray(int n, int m) {
	int size = n * m;
	double* multiArray = new double[size];

	/*Uses the Mercenne twister engine for random number generation*/
	random_device rando;    /* random device is a seed for the mersenne twister */
	mt19937 engine{ rando() };  /* Mersenne twister engine provides seudo random numbers */
	uniform_real_distribution<double> distrib{ 0.0,15.0 }; /* bottleneck the engine to produce values in range */
	/* Note that the values in the distribution are inclusive on both ends*/

	for (int i = 0; i < size; i++) {
		multiArray[i] = distrib(engine);	// fill each index with a random number
	}

	return multiArray;
} 

float* makePythonFloatArray(int n, int m) {
	int size = n * m;
	float* multiArray = new float[size];

	/*Uses the Mercenne twister engine for random number generation*/
	random_device rando;    /* random device is a seed for the mersenne twister */
	mt19937 engine{ rando() };  /* Mersenne twister engine provides seudo random numbers */
	uniform_real_distribution<float> distrib{ 0.0,15.0 }; /* bottleneck the engine to produce values in range */
	/* Note that the values in the distribution are inclusive on both ends*/

	for (int i = 0; i < size; i++) {
		multiArray[i] = distrib(engine);	// fill each index with a random number
	}

	return multiArray;
}

/* Below are methods used to get the items at a specific index of the array */

int getIntAt(int* array, int numCols, int m, int n) {
	/* Row major, so row follows row, there will be m rows n long */
	/* Multiply (m-1) by the number of columns to get to the start
		of the row the item is in, then add the specified column number
		n to get the item we are looking for */
	int index = (m - 1) * numCols + n;
	return array[index];
}

double getDoubleAt(double* array, int numCols, int m, int n) {
	int index = (m - 1) * numCols + n;
	return array[index];
}

float getFloatAt(float* array, int numCols, int m, int n) {
	int index = (m - 1) * numCols + n;
	return array[index];
}

/* Methods for setting the value of a specific index of the array */

void setIntAt(int* array, int numCols, int m, int n, int value) {
	int index = (m - 1) * numCols + n;
	array[index] += value;	// += following the standard calculation in matrix multiply method
}

void setDoubleAt(double* array, int numCols, int m, int n, double value) {
	int index = (m - 1) * numCols + n;
	array[index] += value;
}

void setFloatAt(float* array, int numCols, int m, int n, float value) {
	int index = (m - 1) * numCols + n;
	array[index] += value;
}
