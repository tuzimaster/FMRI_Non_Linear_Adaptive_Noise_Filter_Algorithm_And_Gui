#pragma once
/* IMAGE.H - Image class */
#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

class Image
{
	int num_rows; //Number of rows in array
	int num_cols; //Number of cols in array
	float *data; //Array to contain pixel data

public:
	Image(void);				//Default Constructor
	Image(int rows, int cols);  //Constructor
	~Image(void);				//Destructor
	Image(Image & I);     //Copy Constructor
	int getNumRows();
	int getNumCols();
	float getVal(int row, int col); 
	void setVal(int row, int col, float val);
	void readImage(char *filename);
	void writeImage(char *filename);
};

#endif // !defined( IMAGE_H)
