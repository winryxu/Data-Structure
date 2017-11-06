/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
     // get the row and columns of source image
     int row = theSource.getRows();
     int col = theSource.getColumns();
     // dynamically allocated MosaicCanvas
     MosaicCanvas* mosaic = new MosaicCanvas(row,col);
     // create a vector to store the average color
     vector<Point<3>> average;
     // create a map to store RGBAPixel and TileImage
     map<RGBAPixel, TileImage> imagemap;
     // prepare for insertion to map
     //auto it = imagemap.begin();
     for (size_t i = 0; i < theTiles.size(); i++)
     {
       // get average color
       RGBAPixel tempTile = theTiles[i].getAverageColor();
       // create a 3 dimension double and turn into point
       double arr[3];
       arr[0] = tempTile.red;
       arr[1] = tempTile.green;
       arr[2] = tempTile.blue;
       Point<3> colors(arr);
       // store in vector and map
       average.push_back(colors);
       imagemap.insert(std::pair<RGBAPixel,TileImage>(tempTile,theTiles[i]));
     }
     // build tree
     KDTree<3> threedtree(average);

     for (int i = 0; i < row; i++)
     {
       for (int j = 0; j < col; j++)
       {
         // get region color
         RGBAPixel region = theSource.getRegionColor(i,j);
         double arr[3];
         arr[0] = region.red;
         arr[1] = region.green;
         arr[2] = region.blue;
         Point<3> colors(arr);
         // use findNearestNeighbor to find the closest average color
         Point<3> nearPoint = threedtree.findNearestNeighbor(colors);
         // create a RGBAPixel
         RGBAPixel colorPoint(nearPoint[0],nearPoint[1],nearPoint[2]);
         // find the colorPoint in the map to get the tileimage
         auto lookup = imagemap.find(colorPoint);
         TileImage temp = lookup->second;
         // set mosaic
         mosaic->setTile(i,j,temp);
       }
     }


    return mosaic;
}
