#include <cstdint>

#include "image.h"
#include "png.h"

//This function is going to flip the picture vertically
// It swap the value of the pixel
void Image::flipleft(){
  RGBAPixel *ptr, *ptr1;
  for (size_t xi=0; xi<(this->width()/2);xi++){
    for (size_t yi=0;yi<this->height();yi++){
    int w=this->width();
    ptr = this->operator()(xi,yi);
    ptr1 = this->operator()((w-xi-1),yi);
    int r=ptr->red;
    int g=ptr->green;
    int b=ptr->blue;
    ptr->red=ptr1->red;
    ptr->green=ptr1->green;
    ptr->blue=ptr1->blue;
    ptr1->red=r;
    ptr1->green=g;
    ptr1->blue=b;
  }
  }
}

//This function is going to adjust the brightness of the picture
// It add a number to each pixel's red green blue.
void Image::adjustbrightness(int r,int g, int b){
  for (size_t xi=0; xi<this->width();xi++){
    for (size_t yi=0;yi<this->height();yi++){
      int red = this->operator()(xi,yi)->red;
      int green = this->operator()(xi,yi)->green;
      int blue = this->operator()(xi,yi)->blue;
      if (red+r>255){
        this->operator()(xi,yi)->red=255;
      }
      else if (red+r<0) this->operator()(xi,yi)->red=0;
      else this->operator()(xi,yi)->red+=r;
      if (green+g>255) this->operator()(xi,yi)->green=255;
      else if (green+g<0) this->operator()(xi,yi)->green=0;
      else this->operator()(xi,yi)->green+=g;
      if (blue+b>255) this->operator()(xi,yi)->blue=255;
      else if (blue+b<0) this->operator()(xi,yi)->blue=0;
      else this->operator()(xi,yi)->blue+=b;
    }
    }
}
//This function is going to invert the color of the picture
//It use 255 to minus the original value
void Image::invertcolors(){
  for (size_t xi=0; xi<this->width();xi++){
    for (size_t yi=0;yi<this->height();yi++){
      this->operator()(xi,yi)->red=255-this->operator()(xi,yi)->red;
      this->operator()(xi,yi)->green=255-this->operator()(xi,yi)->green;
      this->operator()(xi,yi)->blue=255-this->operator()(xi,yi)->blue;
    }
  }
}
