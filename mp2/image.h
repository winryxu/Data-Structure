#ifndef IMAGE_H
#define IMAGE_H
#include "png.h"

class Image : public PNG
{
public:
  void flipleft();
  void invertcolors();
  void adjustbrightness(int r, int g, int b);
};

#endif
