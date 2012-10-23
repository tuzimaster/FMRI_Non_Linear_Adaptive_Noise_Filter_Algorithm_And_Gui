#include "Filter.h"

Filter::Filter(void)
{
}

Filter::~Filter(void)
{
}

Image * Filter::process(Image &img, int M, int N)
{
	int i,j,x,y,k,l;
	int rowBorder = (M-1)/2;
	int colBorder = (N-1)/2;
	float temp;

	Image *out = new Image(img);
	if(!out) {
		cout << "Error creating output image." << endl; 
		return NULL;
	}

	if((M%2 == 0) || (N%2 == 0)) {
		cout << "Error: Neighborhood dimensions must be odd integers." << endl;
	} else {
		Image *nbh = new Image(M, N);
		if(!nbh) {
			cout << "Error creating neighborhood." << endl; 
			return NULL;
		}
		//Avoid the borders
		for(i=rowBorder;i<(img.getNumRows()-rowBorder);i++) {
			for(j=colBorder;j<(img.getNumCols()-colBorder);j++) {
				//Set the neighborhood
				k=0;
				l=0;
				for(x=i-rowBorder;x<=i+rowBorder;x++) {
					for(y=j-colBorder;y<=j+colBorder;y++) {
						nbh->setVal(k,l,img.getVal(x,y));
						l++;
					}
					k++;
					l=0;
				}
				temp = updatePixel(*nbh); //Update the pixel
				out->setVal(i,j,temp);
			}
		}
		delete nbh;
	}

	return out;
}