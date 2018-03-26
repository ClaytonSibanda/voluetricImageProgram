#include "volImage.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>      // std::ifstream
#include <sstream>

//definitions no longer needed here
// #define COL 429
// #define ROW 303
// #define number_of_images 123

using namespace std;


//define the constructor
VolImage::VolImage(){
  VolImage::width=0;
  VolImage::height=0;
  VolImage::numberOfImages=0;
}
//define the destructor
VolImage::~VolImage(){
  //deallocate memory

  for(int i=0;i<numberOfImages;i++){
    for(int j=0;j<height;j++){
      delete [] slices[i][j];
    }
    delete []slices[i];
  }
}

bool VolImage::readImages(string baseName){
    ifstream file;// input filestream for reading the file
    char temp;
    stringstream fileName;
    fileName<<"./brain_mri_raws/MRI0.raw";//use baseName here

    for(int k=0;k<numberOfImages;k++){
      file.open(fileName.str(),ios::binary);//read in binary file

      if(!file){
        cout<<"failed to open file"<<endl;

        return false;
      }

      unsigned char **topLArr= new unsigned char*[height];
      slices.push_back(topLArr);

      for(int i=0;i<height;i++){
        unsigned char *t= new unsigned char[width];// remember strong typing, a height has col number of elements
        slices[k][i]=t;
        for(int j=0;j<width;j++){
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
  // cout<<"not here too "<<endl;
cout<<"first image is "<<sliceI<<" second is "<<sliceJ<<endl;
    for(int r=0;r<height;r++){
      for(int c=0;c<width;c++){
        unsigned char diff =(unsigned char)(abs((float)slices[sliceI][r][c] - (float)slices[sliceJ][r][c])/2);
        hFile<<diff;
      }
    }
    cout<<"not here too too"<<endl;

    hFile.close();

  }


  void VolImage::extract(int sliceId,string output_prefix){
  //write to a .raw image file
  //create a .dat file which has three
  string fileName;
  stringstream ss(output_prefix);
  ss<<output_prefix<<".raw";
  ss>>fileName;
  ofstream binaryFile (fileName, ios::out |ios::app|ios::binary);
  for(int i=0;i<height;i++){

    binaryFile.write((char*)slices[sliceId][i],width);
  }
  binaryFile.close();
  ofstream hFile("output.dat",ios::out);
  hFile<<"1 1 1";
  hFile.close();
  }

  //implement this next broe



  void VolImage::volImageSize(){
    int size =0;
    for(int k=0;k<numberOfImages;k++){
      size+=sizeof(slices[k]);
      for(int i=0;i<height;i++){
        size+=sizeof(slices[k][i]);
        for(int j=0;j<width;j++){
          size+=sizeof(slices[k][i][j]);
        }
      }

    }
    std::cout<<"Number of images: "<<numberOfImages<<endl;
    std::cout << "number of bytes required: "<<size << '\n';
  }



  /*Extra credit*/
  //note that the this changes the hieght of the image to be the same as the number of images in the stack
  void VolImage::extractOnRows(int row,string output_prefix){
    stringstream fileName;
    fileName<<output_prefix<<".raw";
    ofstream file(fileName.str(),ios::out|ios::app);
cout<<"extra feature here"<<endl;
    for(int slice=0;slice<numberOfImages;slice++){
      for(int c=0;c<width;c++){
        file<<slices[slice][row][c];
      }
    }
    file.close();
  }




//  funciton for reading the .dat file
  void readHeader(string baseName,VolImage &volImage){
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
      // cout<<"string stream is "<<ss1.str()<<" count is "<<count<<endl;
      if(count==0){
      ss1>>width;

    }

      if(count==1){
  // cout<<"string string is "<<ss1.str()<<endl;
      ss1>>height;
  // cout<<"inner height is "<<height<<endl;
    }
    if(count==2){
      ss1>>numberOfImages;
    }
    count++;
      //ss.str(string());//clear string stream
    }
    // std::cout << width<<" "<<height<<" "<<numberOfImages << '\n';
    volImage.setWidth(width);
    volImage.setHeight(height);
    volImage.setNumberOfImages(numberOfImages);
    // std::cout << volImage.getWidth()<<" "<<volImage.getHeight()<<" "<<volImage.getNumberOfImages() << '\n';
  }
