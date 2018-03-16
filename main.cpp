#include <iostream>
#include <string>
#include <vector>
#include <fstream>      // std::ifstream
#include <sstream>
//define the height as the number of rows and width as the number of columns
#define COL 429
#define ROW 303
#define number_of_images 123
using namespace std;

void extract(int image_number,string fileName,const vector<unsigned char**> &imgVector);
void differenceMap(int image1,int image2,string fileName,const vector<unsigned char**> &imgVector);
void extractOnRows(int row,const vector<unsigned char**> &volume);


int main(int argc, char *argv[])
{

ifstream file;

char temp;
vector<unsigned char**> imgVector;
stringstream fileName;
fileName<<"./brain_mri_raws/MRI0.raw";
for(int k=0;k<number_of_images;k++){
  file.open(fileName.str(),ios::binary);
  if(!file){
    cout<<"failed to open file"<<endl;
    exit(1);
  }

  unsigned char **topLArr= new unsigned char*[ROW];
  imgVector.push_back(topLArr);

for(int i=0;i<ROW;i++){
unsigned char *t= new unsigned char[COL];// remember strong typing, a row has col number of elements
imgVector[k][i]=t;
for(int j=0;j<COL;j++){
file.get(temp);
imgVector[k][i][j]=temp;
}
}
file.close();
//clear the stringstream before  moving one here
fileName.str(string());//clear the string stream
fileName<<"./brain_mri_raws/MRI"<<k+1<<".raw";
}


//differenceMap(10,32,"diff1.raw",imgVector);
//TEST the extra feature
extractOnRows(4,imgVector);

// file.close();
return 0;
}

void extract(int image_number,string fileName,const vector<unsigned char**> &imgVector){
//write to a .raw image file
//create a .dat file which has three 1s
ofstream binaryFile (fileName, ios::out |ios::app|ios::binary);
for(int i=0;i<ROW;i++){

  binaryFile.write((char*)imgVector[image_number][i],COL);
}
binaryFile.close();
ofstream hFile("output.dat",ios::out);
hFile<<"1 1 1";
hFile.close();
}

//NEXT IS TO DO THE COMPARE FEATURE ADN THEN WE ARE DONE
void differenceMap(int image1,int image2,string outputFileName,const vector<unsigned char**> &volume){
  ofstream hFile(outputFileName,ios::out|ios::app);

for(int r=0;r<ROW;r++){
  for(int c=0;c<COL;c++){
    unsigned char diff =(unsigned char)(abs((float)volume[image1][r][c] - (float)volume[image2][r][c])/2);
    hFile<<diff;
  }
}

hFile.close();
}

//note that the this changes the hieght of the image to be the same as the number of images in the stack
void extractOnRows(int row,const vector<unsigned char**> &volume){
  ofstream file("extra.raw",ios::out|ios::app);
  for(int slice=0;slice<number_of_images;slice++){
    for(int c=0;c<COL;c++){
      file<<volume[slice][row][c];
    }
  }
  file.close();
}
