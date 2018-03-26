#include <string>
#include <vector>

#ifndef VOL_IMAGE_H//this is a header guard
#define VOL_IMAGE_H

class VolImage
{
private:
// private members
int width, height,numberOfImages;
// width and height of image stack
std::vector<unsigned char**> slices;
// data for each slice, in order
public:
// public members
VolImage();
// default constructor - define in .cpp
~VolImage();
// destructor - define in .cpp file
// populate the object with images in stack and
//set member variables define in .cpp
bool readImages(std::string baseName);
// compute difference map and write out;  define in .cpp
void diffmap(int sliceI, int sliceJ, std::string output_prefix);
// extract slice sliceId and write to output - define in .cpp
void extract(int sliceId, std::string output_prefix);
// number of bytes uses to store image data bytes
//and pointers (ignore vector<> container, dims etc)
void volImageSize(void);
// define in .cpp

//member function for extracting the specified row of each slice and turn into an imgae
void extractOnRows(int row,std::string output_prefix);

//setters and getters
void setWidth(int length1){
  width =length1;
}

void setNumberOfImages(int number){
  numberOfImages=number;
}
void setHeight(int length2){
  height =length2;
}

int getWidth(){
  return width;
}

int getHeight(){
  return height;
}

int getNumberOfImages(){
  return numberOfImages;
}
};

//forward declaration of a method
void readHeader(std::string baseName,VolImage &volImage);
#endif
