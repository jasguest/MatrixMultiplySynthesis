#pragma once

/* This file simulates the way that python works with 2D arrays and matrices, and
 * will be used to analyze the matrix multiply algotirithm.
 * author: Jason Guest
 */

int* makePythonArray(int n, int m); /* Python 2D aray is continuous in memory, can be represented by a simple array*/
double* makePythonDoubleArray(int n, int m);
float* makePythonFloatArray(int n, int m);
int getIntAt(int* array, int numCols, int m, int n);
double getDoubleAt(double* array, int numCols, int m, int n);
float getFloatAt(float* array, int numCols, int m, int n);
void setIntAt(int* array, int numCols, int m, int n, int value);
void setDoubleAt(double* array, int numCols, int m, int n, double value);
void setFloatAt(float* array, int numCols, int m, int n, float value);