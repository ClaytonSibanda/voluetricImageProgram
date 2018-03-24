#include "volImage.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>      // std::ifstream
#include <sstream>

//definitions
#define COL 429
#define ROW 303
#define number_of_images 123

using namespace std;

//forward declaration of a method
void readHeader(string baseName);
//define the constructor
VolImage::VolImage(){
  VolImage::width=0;
  VolImage::height=0;
}
//define the destructo
VolImage::~VolImage(){}

  VolImage volImage;//volImage object
int main(int argc, char * argv[]){

  string baseName= argv[1];
//read the header file and set the width and the height
  readHeader(baseName);
  cout<<"the width is "<<volImage.getWidth()<<"  hieght is "<<volImage.getHeight()<<endl;
  //bulid the internal structure here
  bool isRead=volImage.readImages(baseName);

  if(argc==6){
    string operation =argv[2];
    string outputfile=argv[argc-1];
    stringstream ss;//for parsing integers
    ss<<argv[3];
    int firstImage;
    ss>>firstImage;
    ss.str(string());//clear string stream

    int secondImage;
    ss<<argv[4];
    ss>>secondImage;

    cout<<"We are here with "<<argc<<" commands";

    volImage.diffmap(firstImage,secondImage,outputfile);
  }

  if(argc ==5)
  {
    cout<<"We are here with "<<argc<<" commands";
    stringstream ss(argv[3]);
    string operation =argv[2];
    string outputfile=argv[argc-1];
    int firstImage;
    ss>>firstImage;
    volImage.extract(firstImage,outputfile);
  }
  if(argc<5){
    //print the size
    volImage.volImageSize();
  }
  return 0;}

  //funciton for reading the .dat file
  void readHeader(string baseName){
    stringstream ss;
    ss<<"./brain_mri_raws/"<<baseName<<".data";

    ifstream file(ss.str());
    //ss.str(string());//clear the stringstream
    if(!file){
      cout<<"file failed to open"<<endl;
    }
    string line;
    int count=0;
    int width;
    int height=0;
    int numberOfImages;
  //  getline(file,line);

    while(getline(file,line,' ')){//get the line from the input file stream
      stringstream ss1;//create a new stringstream everytime, safer than claring it in a loop
      ss1<<line;
      cout<<"strign stream is "<<ss1.str()<<" count is "<<count<<endl;
      if(count==0){
      ss1>>width;

    }

      if(count==1){
  cout<<"string string is "<<ss1.str()<<endl;
      ss1>>height;
  cout<<"inner height is "<<height<<endl;
    }
    if(count==2){
      ss1>>numberOfImages;
    }
    count++;
      //ss.str(string());//clear string stream
    }
    std::cout << width<<" "<<height<<" "<<numberOfImages << '\n';
    volImage.setWidth(width);
    volImage.setHeight(height);
    volImage.setNumberOfImages(numberOfImages);
    std::cout << volImage.getWidth()<<" "<<volImage.getHeight()<<" "<<volImage.getNumberOfImages() << '\n';
  }


  bool VolImage::readImages(string baseName){
    ifstream file;// input filestream for reading the file
    char temp;
    stringstream fileName;
    fileName<<"./brain_mri_raws/MRI0.raw";//use baseName here

    for(int k=0;k<number_of_images;k++){
      file.open(fileName.str(),ios::binary);//read in binary file

      if(!file){
        cout<<"failed to open file"<<endl;

        return false;
      }

      unsigned char **topLArr= new unsigned char*[ROW];
      slices.push_back(topLArr);

      for(int i=0;i<ROW;i++){
        unsigned char *t= new unsigned char[COL];// remember strong typing, a row has col number of elements
        slices[k][i]=t;
        for(int j=0;j<COL;j++){
          file.get(temp);
          slices[k][i][j]=temp;
        }
      }
      file.close();
      //clear the stringstream before  moving one here
      fileName.str(string());//clear the string stream
      fileName<<"./brain_mri_raws/"<<baseName<<k+1<<".raw";//also use baseName here

    }

    return true;
  }



  void VolImage::diffmap(int sliceI,int sliceJ,string output_prefix){
    stringstream fileName;
    fileName<<output_prefix<<".raw";
    ofstream hFile(fileName.str(),ios::out|ios::app);//opens the file for appending output filestream for opening a file for writing


    for(int r=0;r<ROW;r++){
      for(int c=0;c<COL;c++){
        unsigned char diff =(unsigned char)(abs((float)slices[sliceI][r][c] - (float)slices[sliceJ][r][c])/2);
        hFile<<diff;
      }
    }

    hFile.close();

  }

  void VolImage::extract(int sliceId,string output_prefix){
    stringstream fileName;
    fileName<<output_prefix<<".raw";
    ofstream file(fileName.str(),ios::out|ios::app);

    for(int slice=0;slice<number_of_images;slice++){
      for(int c=0;c<COL;c++){
        file<<slices[slice][sliceId][c];
      }
    }
    file.close();
  }

  //implement this next broe



  void VolImage::volImageSize(){
    int size =0;
    for(int k=0;k<number_of_images;k++){
      size+=sizeof(slices[k]);
      for(int i=0;i<ROW;i++){
        size+=sizeof(slices[k][i]);
        for(int j=0;j<COL;j++){
          size+=sizeof(slices[k][i][j]);
        }
      }

    }
    std::cout << "number of bytes required "<<size << '\n';
  }



  /*Extra credit*/
  //note that the this changes the hieght of the image to be the same as the number of images in the stack
  void VolImage::extractOnRows(int row,string output_prefix){
    stringstream fileName;
    fileName<<output_prefix<<".raw";
    ofstream file(fileName.str(),ios::out|ios::app);

    for(int slice=0;slice<number_of_images;slice++){
      for(int c=0;c<COL;c++){
        file<<slices[slice][row][c];
      }
    }
    file.close();
  }
