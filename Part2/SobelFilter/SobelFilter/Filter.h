#pragma once
/* FILTER.H - Filter Class */
#ifndef FILTER_H
#define FILTER_H

#include "Image.h"

class Filter
{
protected: 
	virtual float updatePixel(Image &nbh) =0;
public:
	Filter(void);	//Constructor
	~Filter(void);	//Destructor
	Image * process(Image &img, int M, int N);
};

#endif /* !defined( FILTER_H ) */