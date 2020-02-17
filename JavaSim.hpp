#pragma once

/* This file will simulate the way that java builds and works with 2D arrays and matrices
 * which will then be used in running and analyzing the amtrix multiply algorithm. 
 * author: Jason Guest
 */

/* The method used to build a 2D array works differently in Java from cpp. This is because Java 2D
 * arrays store references to arrays, all of which are not specifically in sequential memory locations.
 * The new keyword is used in making it, the object will be stored in heap memory. 
 */
int** makeJavaArray(int n, int m); /* Provide rows and columns */
double** makeJavaDoubleArray(int n, int m);
float** makeJavaFloatArray(int n, int m);
