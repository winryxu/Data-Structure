#include <cstdint>
#include <string>
#include "scene.h"
#include "png.h"
#include "iostream"
using namespace std;

Scene::Scene(int max){
  if (max<0) max=0;
  theMax = max;
  image = new Image*[theMax];
  x = new int[theMax];
  y = new int[theMax];
  for (int i=0;i<theMax;i++){
    image[i] = NULL;
    x[i] = 0;
    y[i] = 0;
  }
}

void Scene::clear(){
  for (int i=0;i<theMax;i++){
    delete image[i];
  }
  delete[] image;
  image = NULL;
  delete[] x;
  x = NULL;
  delete[] y;
  y = NULL;
}

Scene::~Scene(){
  clear();}

void Scene::copy(const Scene& source){
  theMax = source.theMax;
  image = new Image*[theMax];
  x = new int[theMax];
  y = new int[theMax];
  for (int i=0; i<source.theMax;i++){
    if (source.image[i]!=NULL){
      image[i] = new Image(*source.image[i]);
      x[i] = source.x[i];
      y[i] = source.y[i];
    }
    else{
      image[i]=NULL;
      x[i]=0;
      y[i]=0;
    }
  }
}


Scene::Scene(const Scene& source){
  copy(source);
}


const Scene& Scene::operator=(const Scene &source){
  if (&source != this){
      clear();
      copy(source);
    }
    return *this;
}


void Scene::changemaxlayers	(	int 	newmax	)	{
  if (newmax < theMax){
    for (int i = newmax; i < theMax; i++){
      if (image[i] != NULL){
        cout<<"invalid nexmax"<<endl;
        return;
      }
    }
  }
  Image** newimage = new Image*[newmax];
  int* xtemp = new int[newmax];
  int* ytemp = new int[newmax];

  if (newmax < theMax){
    for (int i = 0; i < newmax; i++){
      newimage[i] = image[i];
      xtemp[i] = x[i];
      ytemp[i] = y[i];
    }
  }
  else{

    for (int i=0; i < theMax; i++){
      newimage[i] = image[i];
      xtemp[i] = x[i];
      ytemp[i] = y[i];
    }

    for (int i =theMax; i<newmax; i++){
      newimage[i] = NULL;
    }
}
    theMax = newmax;
    delete[] image;
    delete[] x;
    delete[] y;
    image = newimage;
    x = xtemp;
    y = xtemp;
}

void Scene::addpicture	(	const char * 	FileName, int 	index, int 	x, int 	y){
  string filename(FileName);
  Image* newimage = new Image();
  newimage->readFromFile(FileName);
  if (index<0 || index > theMax-1){
    cout << "index out of bounds" << endl;
  }
  else{
    if(image[index]!=NULL) {
      delete image[index];
      image[index] = NULL;
    }
    image[index] = newimage;
    this-> x[index] = x;
    this-> y[index] = y;
  }
}


void Scene::changelayer	(	int 	index, int 	newindex ){
  if (index < 0 || index > theMax-1 || newindex < 0 || newindex > theMax-1){
    cout << "invalid index" << endl;
    return;
  }
  if (index == newindex){
    return;
  }
  if (image[newindex] != NULL){
    delete image[newindex];
    image[newindex] = NULL;
  }
  image[newindex] = image[index];
  x[newindex] = x[index];
  y[newindex] = y[index];
  if (image[index] != NULL){
    image[index] = NULL;
  }
}


void Scene::translate	(	int 	index, int 	xcoord, int 	ycoord){
  if (index < 0 || index > theMax-1 || image[index] == NULL){
    cout << "invalid index" << endl;
  }
  else{
    this-> x[index] = xcoord;
    this -> y[index] = ycoord;
  }
}


void Scene::deletepicture	(	int 	index	)	{
  if (index < 0 || index > theMax-1 || image[index]==NULL){
    cout << "invalid index" << endl;
    return;
  }
  delete image[index];
  image[index] = NULL;
}


Image * Scene::getpicture	(	int 	index	)	const{
  if (index < 0 || index > theMax-1 || image[index] == NULL){
    cout << "invalid index" << endl;
    return NULL;
  }
  return image[index];
}

Image Scene::drawscene()	const{
  size_t w = 0;
  size_t h = 0;
  for (int i=0; i < theMax; i++){
    if(image[i]==NULL) continue;
    if(w < image[i]->width() + (size_t)x[i])
    w = image[i]->width() + (size_t)x[i];
    if(h < image[i]->height() + (size_t)y[i])
    h = image[i]->height() + (size_t)y[i];
  }
  Image draw;
  draw.resize(w,h);
  for (int i=0; i < theMax; i++){
    if (image[i] != NULL){
          for (size_t j=0;j<(image[i]->height());j++){
            for (size_t k=0;k<(image[i]->width());k++){
              *draw(k+x[i],j+y[i]) = *((*image[i])(k,j));
        }
      }
    }
  }
  return draw;
}
