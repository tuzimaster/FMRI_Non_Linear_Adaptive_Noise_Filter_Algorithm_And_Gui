#include "SobelFilter.h"
#include <iostream>
#include <fstream>

#define MINSLICE	0
#define MAXSLICE	255

#define AXIAL		0
#define SAGGITAL	1
#define CORONAL		2

using namespace std;

int main(int argc, char *argv[]) 
{

	FILE *inFile, *outFile;
	int slice, orient;
	int i, j, n;
	float temp;

	Image *img = new Image(256,256);
	Image *out = new Image(256,256);
	SobelFilter *filt = new SobelFilter();

	//Error check # arguments
	if(argc != 5) {
		cout << "Error: Program requires 4 input arguments" << endl;
		cout << "       1) Input file name" << endl;
		cout << "       2) Output file name" << endl;
		cout << "       3) Slice number" << endl;
		cout << "       4) Slice orientation (a=axial, s=saggital, c=coronal)" << endl;
		return -1;
	}

	//Get slice number of input image
	//Ensure slice is a valid integer in range
	slice = atoi(argv[3]);
	if((slice < MINSLICE) || (slice > MAXSLICE)) {
		cout << "Error: Slice must be a number between " << MINSLICE << " and " << MAXSLICE << "." << endl;
		return -1;
	}
	
	//Get image orientation (axial, sagittal or coronal)
	//Ensure orientation is valid
	if(!strcmp(argv[4],"a")) {
		orient = AXIAL;
	} else if (!strcmp(argv[4],"s")) {
		orient = SAGGITAL;
	} else if (!strcmp(argv[4],"c")) {
		orient = CORONAL;
	} else {
		cout << "Error: Orientation must be one of the following: a=axial, s=saggital, or c=coronal" << endl;
		cout << "       You supplied " << argv[4] << endl;
		return -1;
	}

	//Get input file name - stored in argv
	//Ensure file exists - handled by Image class
	//Open File
	cout << "Opening File..." << endl;
	inFile = fopen(argv[1],"r");
	i=0;
	j=0;

	int x_axis = 0;
	int y_axis = 0;
	int z_axis = 0;

	while(fscanf(inFile,"%*d\t%d\t%d\t%d\t%f\n",&x_axis,&y_axis,&z_axis,&temp) != EOF) {
		
		if(orient == SAGGITAL && x_axis == slice)
		{
			img->setVal(i,j,temp);
			j++;
			if(j>=img->getNumCols()) {
				j=0;
				i++;
			}
		} 
		else if(orient == AXIAL && y_axis == slice)
		{
			img->setVal(i,j,temp);
			j++;
			if(j>=img->getNumCols()) {
				j=0;
				i++;
			}
		}
		else if(orient == CORONAL && z_axis == slice)
		{
			img->setVal(i,j,temp);
			j++;
			if(j>=img->getNumCols()) {
				j=0;
				i++;
			}
		}
	}

	cout << "Processing..." << endl;
	//Apply Sobel filter
	out = filt->process(*img,3,3);

	//Get output file name
	//Open and write to file
	cout << "Writing File..." << endl;
	outFile = fopen(argv[2],"w");
	rewind(inFile);
	i=0;
	j=0;
	int index = 0;
	while(fscanf(inFile,"%d\t%d\t%d\t%d\t%f\n",&index,&x_axis,&y_axis,&z_axis,&temp) != EOF) {
		if(orient == SAGGITAL && x_axis == slice)
		{
			fprintf(outFile,"%d\t%d\t%d\t%d\t%f\n",index,x_axis,y_axis,z_axis,out->getVal(i,j));
			j++;
			if(j>=out->getNumCols()) {
				j=0;
				i++;
			}
		}
		else if(orient == AXIAL && y_axis == slice)
		{
			fprintf(outFile,"%d\t%d\t%d\t%d\t%f\n",index,x_axis,y_axis,z_axis,out->getVal(i,j));
			j++;
			if(j>=out->getNumCols()) {
				j=0;
				i++;
			}
		}
		else if(orient == CORONAL && z_axis == slice)
		{
			fprintf(outFile,"%d\t%d\t%d\t%d\t%f\n",index,x_axis,y_axis,z_axis,out->getVal(i,j));
			j++;
			if(j>=out->getNumCols()) {
				j=0;
				i++;
			}
		}
		else
		{
			fprintf(outFile,"%d\t%d\t%d\t%d\t%f\n",index,x_axis,y_axis,z_axis,temp);
		}
	}

	fclose(inFile);
	fclose(outFile);
	
	delete img;
	delete out;

	return 0;
}