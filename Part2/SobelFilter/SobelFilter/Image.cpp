#include "Image.h"

/* 
 * Default Constructor
 */ 
Image::Image() 
{
	//Set number or rows and cols
	num_rows = 0;
	num_cols = 0;
	//Dynamically allocate data
	data = new float[num_rows*num_cols];
}

/*
 * Constructor
 * rows - number of rows in array
 * cols - number of cols in arry
 */
Image::Image(int rows, int cols)
{
	//Set number or rows and cols
	num_rows = rows;
	num_cols = cols;
	//Dynamically allocate data
	data = new float[num_rows*num_cols];
}

/* 
 * Copy Constructor 
 * Allocate and copy a new data array 
 * rather than copying the pointer
 */ 
Image::Image(Image & I)
{
	int i,j;

	//Set number of rows and cols
	num_rows = I.num_rows;
	num_cols = I.num_cols;

	//Allocate and copy new data array
	data = new float[num_rows*num_cols];
	
	for(i=0;i<num_rows;i++) {
		for(j=0;j<num_cols;j++) {
			setVal(i,j,I.getVal(i,j));
		}
	}

}

/*
 * Destructor
 */
Image::~Image(void)
{
	//Remove dynamically allocated memory
	delete [] data;
}

/* 
 * returns: number of rows
 */
int Image::getNumRows()
{
	return num_rows;
}

/* 
 * returns: number of cols
 */
int Image::getNumCols() 
{
	return num_cols;
}

/* 
 * Gets a value from the 1D data array using (i,j) notation
 *
 * row - row #
 * col - col #
 * 
 * returns value at data[i,j] = data[row*num_cols+col]
 */
float Image::getVal(int row, int col)
{
	return data[row*num_cols+col];
}

/* 
 * Sets data[row,col] to val
 *
 * row - row #
 * col - col #
 * val - float value to set 
 *
 */
void Image::setVal(int row, int col, float val) {

	data[row*num_cols+col] = val;

	return;
}

/*
 * Opens a file of binary floating point numbers (4 bytes)
 * and reads values into data array.
 *
 * bin - input filename 
 *
 * returns NULL
 */
void Image::readImage(char *filename) 
{
	ifstream infile;

	infile.open(filename, std::ios::in|std::ios::binary);
	if (infile.is_open()) {
		infile.read((char*)data, num_rows*num_cols*4);
		infile.close();
	} else std::cout<< "Unable to open " << filename << " for reading. \n";

	return;
}

/* 
 * Writes the image to file in floating point 
 * binary format (4 bytes) in row order 
 * (first row, second row, ...)
 *
 * bin - output file name
 *
 * returns NULL
 */
void Image::writeImage(char *filename) 
{
	std::ofstream outfile;
	//cout << "Attempting to open file." << endl;
	outfile.open(filename, std::ios::out|std::ios::binary);
	if(outfile.is_open()) {
		outfile.write((char *) data, num_cols*num_rows*4);
		outfile.close();
	} else std::cout<< "Unable to open " << filename << " for writing. \n";

	return;
}
