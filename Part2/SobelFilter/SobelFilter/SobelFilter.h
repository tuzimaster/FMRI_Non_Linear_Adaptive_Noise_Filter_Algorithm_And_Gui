#pragma once
/* SOBELFILTER.H - Median Filter Class */
#ifndef SOBELFILTER_H
#define SOBELFILTER_H

#include "Filter.h"
#include <cmath>

class SobelFilter : public Filter
{
protected: 
	int gx[3][3]; 
	int gy[3][3];
	void setHorzKernel(int horz[3][3]);
	void setVertKernel(int vert[3][3]);
	float updatePixel(Image &nbh);
public:
	SobelFilter(void);		//Constructor
	~SobelFilter(void);		//Destructor
};

#endif /* !defined( SOBELFILTER_H ) */