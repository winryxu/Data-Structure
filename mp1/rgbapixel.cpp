#include "rgbapixel.h"

RGBAPixel::RGBAPixel(){
	red=green=blue=alpha=255;
}
RGBAPixel::RGBAPixel(uint8_t r,
		     uint8_t g,
		     uint8_t b){
	red=r;
	blue=b;
	green=g;
	alpha=255;
}
