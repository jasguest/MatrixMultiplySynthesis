/** This is a Cpp file Which synthesizes an input file to be read by
 * the cache simulator. By analyzing matrix multiply algorithms from both
 * the Python and Java perspectives, this file performs 'cache emissions'
 * which will build the input file. 
 * author Jason Guest
 * version 2.2020
 */

/* -----INCLUSIONS----- */
#include "CacheEmitter.hpp" /*For cache emission methods*/
#include "JavaSim.hpp"      /*For Java simulated code */
#include "PythonSim.hpp"    /*For Python simulated code */
#include <iostream>         /*Library for user input and console messages*/
#include <fstream>          /*Library for text file writing/reading methods*/
#include <string>           /*Library for use of string datatype, used in emitting cahe data to file*/
using namespace std;        

/* -----METHODS----- */

/* Main entry and exit point for program execution */
int main()
{
    cout << "size of int: " << sizeof(int) << " bytes\n";
    cout << "size of double: " << sizeof(double) << " bytes\n";
    cout << "size of float: " << sizeof(float) << " bytes\n";
    cout << "Enter a filename in .txt format to create: " << "\n";
    char fileName[24];  /*Declare a variable to hold the input file name*/
    cin.get(fileName, 24);  /*Get the file name from user input*/
    ofstream outFile (fileName);    /*Create our file from the input to be written to*/

    if (outFile.is_open()) {    /*Perform actions if the file is open*/

        /*Our file is ready to be written to, now take input to see whether a Java or Python code shoud=ld be simulated*/
        cout << "Enter a 1 for Java code simulation, and a 0 for Python (1 is default): " << "\n";
        int choice = 1; /*Default the choice to 1*/
        cin >> choice;  /*Initialize the choice by input*/
        if (choice == 1) { /*default case is to look at Java*/

            /* Build integer matrices */
            int** javaIntOne = makeJavaArray(100, 100); /* ~16,000,000 bytes = 16 megabytes */
            int** javaIntTwo = makeJavaArray(100, 100);

            /* Build Double matrices */
            double** javaDoubleOne = makeJavaDoubleArray(50, 50); /* ~16,000,000 bytes = 16 megabytes */
            double** javaDoubleTwo = makeJavaDoubleArray(50, 50); 

            /* Build float arrays */
            float** javaFloatOne = makeJavaFloatArray(100, 100); /* ~16,000,000 bytes = 16 megabytes */
            float** javaFloatTwo = makeJavaFloatArray(100, 100); 

            /* Perform matrix multiply methods, pass the file into method for cache emitter to write */
            int i, j, k;
            /*  Since I can't pass the ofstream to the CahceEmitter class and its methods, what I'll do instead
                is have the CacheEmitter take the information I give it, spit out the hex formatted data I need as a
                string, and use that to write the file in this class */

            /* Below are the calulations to get the number of rows and columns for each matrix */
            /* These values will be read by the loops and multiply int he matrix multiply methods */
            int javaIntRowsOne = sizeof(javaIntOne) / sizeof(javaIntOne[0]);
            int javaIntColsOne = sizeof(javaIntOne[0]) / sizeof(int);
            int javaIntRowsTwo = sizeof(javaIntTwo) / sizeof(javaIntTwo[0]);
            int javaIntColsTwo = sizeof(javaIntTwo[0]) / sizeof(int);

            int javaDoubleRowsOne = sizeof(javaDoubleOne) / sizeof(javaDoubleOne[0]);
            int javaDoubleColsOne = sizeof(javaDoubleOne[0]) / sizeof(double);
            int javaDoubleRowsTwo = sizeof(javaDoubleTwo) / sizeof(javaDoubleTwo[0]);
            int javaDoubleColsTwo = sizeof(javaDoubleTwo[0]) / sizeof(double);

            int javaFloatRowsOne = sizeof(javaFloatOne) / sizeof(javaFloatOne[0]);
            int javaFloatColsOne = sizeof(javaFloatOne[0]) / sizeof(float);
            int javaFloatRowsTwo = sizeof(javaFloatTwo) / sizeof(javaFloatTwo[0]);
            int javaFloatColsTwo = sizeof(javaFloatTwo[0]) / sizeof(float);

            /* integer matrix multiply */

            int** javaIntResult = makeJavaArray(javaIntColsTwo, javaIntRowsOne);
            outFile << emit_readInt(javaIntColsTwo);
            outFile << emit_readInt(javaIntRowsOne);

            for (i = 0; i < javaIntRowsOne; i++) { /*Rows of first*/
                /*CacheEmitter calls*/
                /*reads*/
                outFile << emit_readInt(i);
                outFile << emit_readInt(javaIntRowsOne);
                for (j = 0; j < javaIntColsTwo; j++) { /*Columns of second*/
                    /*CacheEmitter calls*/
                    /*reads*/
                    outFile << emit_readInt(j);
                    outFile << emit_readInt(javaIntColsTwo);
                    for (k = 0; k < javaIntColsOne; k++) { /*Columns of first*/
                        /*CacheEmitter calls*/
                        /*Reads and writes*/
                        outFile << emit_readInt(k);
                        outFile << emit_readInt(javaIntColsOne);
                        outFile << emit_readInt(javaIntOne[i][k]);
                        outFile << emit_readInt(javaIntTwo[k][j]);
                        javaIntResult[i][j] += javaIntOne[i][k] * javaIntTwo[k][j];
                        outFile << emit_writeInt(javaIntResult[i][j]);
                        outFile << emit_writeInt(k);
                    }
                    outFile << emit_writeInt(j);
                }
                outFile << emit_writeInt(i);
            }

            /*Double matrix multiply*/
            double** javaDoubleResult = makeJavaDoubleArray(javaDoubleColsTwo, javaDoubleRowsOne);
            
            for (i = 0; i < javaDoubleRowsOne; i++) { /*Rows of first*/
                /*CacheEmitter calls*/
                outFile << emit_readInt(i);
                for (j = 0; j < javaDoubleColsTwo; j++) { /*Columns of second*/
                    /*CacheEmitter calls*/
                    outFile << emit_readInt(j);
                    for (k = 0; k < javaDoubleColsOne; k++) { /*Columns of first*/
                        /*CacheEmitter calls*/
                        outFile << emit_readInt(k);
                        outFile << emit_readDouble(javaDoubleOne[i][k]);
                        outFile << emit_readDouble(javaDoubleTwo[k][j]);
                        javaDoubleResult[i][j] += javaDoubleOne[i][k] * javaDoubleTwo[k][j];
                        outFile << emit_writeDouble(javaDoubleResult[i][j]);
                        outFile << emit_writeInt(k);
                    }
                    outFile << emit_writeInt(j);
                }
                outFile << emit_writeInt(i);
            }

            /*Float matrix multiply*/
            float** javaFloatResult = makeJavaFloatArray(javaFloatColsTwo, javaFloatRowsOne);
            outFile << emit_readInt(javaFloatColsTwo);
            outFile << emit_readInt(javaFloatRowsOne);

            for (i = 0; i < javaFloatRowsOne; i++) { /*Rows of first*/
                /*CacheEmitter calls*/
                outFile << emit_readInt(i);
                outFile << emit_readInt(javaFloatRowsOne);
                for (j = 0; j < javaFloatColsTwo; j++) { /*Columns of second*/
                    /*CacheEmitter calls*/
                    outFile << emit_readInt(j);
                    outFile << emit_readInt(javaFloatColsTwo);
                    for (k = 0; k < javaFloatColsOne; k++) { /*Columns of first*/
                        /*CacheEmitter calls*/
                        outFile << emit_readInt(k);
                        outFile << emit_readInt(javaFloatColsOne);
                        outFile << emit_readFloat(javaFloatOne[i][k]);
                        outFile << emit_readFloat(javaFloatTwo[k][j]);
                        javaFloatResult[i][j] += javaFloatOne[i][k] * javaFloatTwo[k][j];
                        outFile << emit_writeFloat(javaFloatResult[i][j]);
                        outFile << emit_writeInt(k);
                    }
                    outFile << emit_writeInt(j);
                }
                outFile << emit_writeInt(i);
            }

            //int** javaIntResult = matrixMultiplyInt(javaIntOne, javaIntTwo, outFile);
            //double** javaDoubleResult = matrixMultiplyDouble(javaDoubleOne, javaDoubleTwo, outFile);
            //float** javaFloatResult = matrixMultiplyFloat(javaFloatOne, javaFloatTwo, outFile);
        }
        else {  /*Should the user enter anything but a 1, we will look at Python code*/
            /* Rows first, columns second, rows second
                result[i][j] += first[i][k] * second[k][j] */

            /* Build the Python 2D arrays */
            int* pythonIntOne = makePythonArray(1000, 1000);
            int* pythonIntTwo = makePythonArray(1000, 1000);

            double* pythonDoubleOne = makePythonDoubleArray(500, 500);
            double* pythonDoubleTwo = makePythonDoubleArray(500, 500);

            float* pythonFloatOne = makePythonFloatArray(1000, 1000);
            float* pythonFloatTwo = makePythonFloatArray(1000, 1000);

            /* Variables to hold the number of columns and rows per amtrix */
            int pythonIntRowsOne = 1000;
            int pythonIntColsOne = 1000;
            int pythonIntRowsTwo = 1000;
            int pythonIntColsTwo = 1000;
            int pythonDoubleRowsOne = 500;
            int pythonDoubleColsOne = 500;
            int pythonDoubleRowsTwo = 500;
            int pythonDoubleColsTwo = 500;
            int pythonFloatRowsOne = 1000;
            int pythonFloatColsOne = 1000;
            int pythonFloatRowsTwo = 1000;
            int pythonFloatColsTwo = 1000;
            /* May change this to accept user input to build the size of the arrays, then these variables would be 
               calculated using the user input for cols and rows */

            /* Matrix mutliply methods below */
            int i, j, k;
            int tempValue;
            /* Matrix multiply int */
            int* pythonIntResult = makePythonArray(pythonIntColsTwo, pythonIntRowsOne);
            outFile << emit_readInt(pythonIntColsTwo);
            outFile << emit_readInt(pythonIntRowsOne);

            for (i = 0; i < pythonIntRowsOne; i++) {
                outFile << emit_readInt(i);
                outFile << emit_readInt(pythonIntRowsOne);
                for (j = 0; j < pythonIntColsTwo; j++) {
                    outFile << emit_readInt(j);
                    outFile << emit_readInt(pythonIntColsTwo);
                    for (k = 0; k < pythonIntRowsTwo; k++) {
                        outFile << emit_readInt(k);
                        outFile << emit_readInt(pythonIntRowsTwo);
                        tempValue = getIntAt(pythonIntOne, pythonIntColsOne, k, i) * getIntAt(pythonIntTwo, pythonIntColsTwo, j, k);
                        outFile << emit_readInt(getIntAt(pythonIntOne, pythonIntColsOne, k, i));
                        outFile << emit_readInt(getIntAt(pythonIntTwo, pythonIntColsTwo, j, k));
                        outFile << emit_writeInt(tempValue);
                        setIntAt(pythonIntResult, pythonIntColsTwo, j, i, tempValue);
                        outFile << emit_readInt(tempValue);
                        outFile << emit_writeInt(getIntAt(pythonIntResult, pythonIntColsTwo, j, i));
                        outFile << emit_writeInt(k);
                    }
                    outFile << emit_writeInt(j);
                }
                outFile << emit_writeInt(i);
            }

            /* Matrix multiply double */
            double* pythonDoubleResult = makePythonDoubleArray(pythonDoubleColsTwo, pythonDoubleRowsOne);
            double tempProduct;
            outFile << emit_readInt(pythonDoubleColsTwo);
            outFile << emit_readInt(pythonDoubleRowsOne);

            for (i = 0; i < pythonDoubleRowsOne; i++) {
                outFile << emit_readInt(i);
                outFile << emit_readInt(pythonDoubleRowsOne);
                for (j = 0; j < pythonDoubleColsTwo; j++) {
                    outFile << emit_readInt(j);
                    outFile << emit_readInt(pythonDoubleColsTwo);
                    for (k = 0; k < pythonDoubleRowsTwo; k++) {
                        outFile << emit_readInt(k);
                        outFile << emit_readInt(pythonDoubleRowsTwo);
                        tempProduct = getDoubleAt(pythonDoubleOne, pythonDoubleColsOne, k, i) * getDoubleAt(pythonDoubleTwo, pythonDoubleColsTwo, j, k);
                        outFile << emit_readDouble(getDoubleAt(pythonDoubleOne, pythonDoubleColsOne, k, i));
                        outFile << emit_readDouble(getDoubleAt(pythonDoubleTwo, pythonDoubleColsTwo, j, k));
                        outFile << emit_writeDouble(tempProduct);
                        setDoubleAt(pythonDoubleResult, pythonDoubleColsTwo, j, i, tempProduct);
                        outFile << emit_readDouble(tempProduct);
                        outFile << emit_writeDouble(getDoubleAt(pythonDoubleResult, pythonDoubleColsTwo, j, i));
                        outFile << emit_writeInt(k);
                    }
                    outFile << emit_writeInt(j);
                }
                outFile << emit_writeInt(i);
            }

            /* Matrix multiply float */
            float* pythonFloatResult = makePythonFloatArray(pythonFloatColsTwo, pythonFloatRowsOne);
            float floatValue;
            outFile << emit_readInt(pythonFloatColsTwo);
            outFile << emit_readInt(pythonFloatRowsOne);

            for (i = 0; i < pythonFloatRowsOne; i++) {
                outFile << emit_readInt(i);
                outFile << emit_readInt(pythonFloatRowsOne);
                for (j = 0; j < pythonFloatColsTwo; j++) {
                    outFile << emit_readInt(j);
                    outFile << emit_readInt(pythonFloatColsTwo);
                    for (k = 0; k < pythonFloatRowsTwo; k++) {
                        outFile << emit_readInt(k);
                        outFile << emit_readInt(pythonFloatRowsTwo);
                        floatValue = getFloatAt(pythonFloatOne, pythonFloatColsOne, k, i) * getFloatAt(pythonFloatTwo, pythonFloatColsTwo, j, k);
                        outFile << emit_readFloat(getFloatAt(pythonFloatOne, pythonFloatColsOne, k, i));
                        outFile << emit_readFloat(getFloatAt(pythonFloatTwo, pythonFloatColsTwo, j, k));
                        outFile << emit_writeFloat(floatValue);
                        setFloatAt(pythonFloatResult, pythonFloatColsTwo, j, i, floatValue);
                        outFile << emit_readFloat(floatValue);
                        outFile << emit_writeFloat(getFloatAt(pythonFloatResult, pythonFloatColsTwo, j, i));
                        outFile << emit_writeInt(k);
                    }
                    outFile << emit_writeInt(j);
                }
                outFile << emit_writeInt(i);
            }

        }


    }
    else {  /*Do not performa actions if the file isn't open*/
        cout << "No valid file to write is open" << "\n";
    }

    std::cout << "Hello World!\n";
}
