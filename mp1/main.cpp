
#include "rgbapixel.h"
#include "png.h"

/*
This function is going to ratote the phote 180 degrees.
It extract the width, height of the photo and the red, blue, green components of each pixel. Then it swap the location to rotate the photo.
*/
PNG rotate(PNG original){
   PNG output=PNG(original.width(),original.height());
  for (size_t y=0;y<original.height();y++){
    for (size_t x=0;x<original.width();x++){
      int wid=original.width()-x-1;
      int h=original.height()-y-1;
      int r=original(wid,h)->red;
      int g=original(wid,h)->green;
      int b=original(wid,h)->blue;
      output(x,y)->red=r;
      output(x,y)->green=g;
      output(x,y)->blue=b;
    }
  }
  return output;
}



/**
 * The main function in this program.
Save the input image to the variable input and use the rotate funciton to rotate the photo.
The output is saved as the out.png.
 */
int main()
{
    // Open a new PNG image from the file sample.png.
    PNG image("in.png");
    PNG output;
    
    output=rotate(image);
    output.writeToFile("out.png");

    return 0;
}
