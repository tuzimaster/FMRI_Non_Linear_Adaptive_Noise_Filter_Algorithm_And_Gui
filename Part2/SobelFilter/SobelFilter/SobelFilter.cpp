#include "SobelFilter.h"

SobelFilter::SobelFilter(void)
{
	//Initialize horizontal kernel
	gx[0][0] = -1;
	gx[0][1] = 0;
	gx[0][2] = 1;
	gx[1][0] = -2;
	gx[1][1] = 0;
	gx[1][2] = 2;
	gx[2][0] = -1;
	gx[2][1] = 0;
	gx[2][2] = 1;

	//Initialize vertical kernel
	gy[0][0] = 1;
	gy[0][1] = 2;
	gy[0][2] = 1;
	gy[1][0] = 0;
	gy[1][1] = 0;
	gy[1][2] = 0;
	gy[2][0] = -1;
	gy[2][1] = -2;
	gy[2][2] = -1;

}

SobelFilter::~SobelFilter(void)
{
}

void SobelFilter::setHorzKernel(int horz[3][3]) 
{
	int i, j;
	for(i=0;i<3;i++) {
		for(j=0;j<3;j++) {
			this->gx[i][j] = horz[i][j];
		}
	}

	return;
}

void SobelFilter::setVertKernel(int vert[3][3]) 
{
	int i, j;
	for(i=0;i<3;i++) {
		for(j=0;j<3;j++) {
			this->gy[i][j] = vert[i][j];
		}
	}

	return;
}

//////////////////////////////////////////////////////
//Method that performs the Sobel Filter on 1 pixel
//////////////////////////////////////////////////////
float SobelFilter::updatePixel(Image &nbh)
{
	float xtot, ytot;
	float temp;
	int i,j;

	xtot = 0;
	ytot = 0;

	//Error check dimensions of neighborhood (must be 3x3)
	if((nbh.getNumCols() != 3) || (nbh.getNumRows() != 3)) {
		cout << "Error in use of SobelFilter::updatePixel. Neighborhood dimensions must be 3x3." << endl;
		return NULL; 
	}
	
	//Multiply neighborhood by gx and gy
	//and calculate the totals 
    for(i=0; i<3; i++){ 
        for (j=0; j<3; j++){ 
			xtot += (nbh.getVal(i,j)*this->gx[i][j]); 
            ytot += (nbh.getVal(i,j)*this->gy[i][j]); 
        } 
    } 

	//Return the gradient
	temp = (sqrt((xtot*xtot)+(ytot*ytot)));
	if(temp > 255) {
		temp = 255;
	} else if (temp < 0) {
		temp = 0;
	}
	return temp;
}