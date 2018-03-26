#include "volImage.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>      // std::ifstream
#include <sstream>
#include <ctype.h>

using namespace std;

//forward declaration of a method
// void readHeader(string baseName);

VolImage volImage;//volImage object
int main(int argc, char * argv[]){

string baseName= argv[1];
//read the header file and set the width and the height and the number of images to be read
readHeader(baseName, volImage);

//  cout<<"the width is "<<volImage.getWidth()<<"  hieght is "<<volImage.getHeight()<<endl;
//bulid the internal structure here
bool isRead=volImage.readImages(baseName);

if(argc==6){
  cout<<"not here "<<endl;
  string operation =argv[2];
  string outputfile=argv[argc-1];
if(!isdigit(*(argv[3])) || !isdigit(*(argv[4]))){
  cout<<"i and j should be digits"<<endl;
  exit(1);
}

stringstream ss;//for parsing integers

  int firstImage;
ss<<argv[3];
  ss>>firstImage;
  // ss.str(string());//clear string stream
stringstream ss2;
  int secondImage;
  ss2<<argv[4];
  ss2>>secondImage;

  cout<<"arg[4] "<<argv[4]<<" secondImage is "<<secondImage<<endl;
  cout<<"arg[3] "<<argv[3]<<" firstImage is "<<firstImage<<endl;

  volImage.diffmap(firstImage,secondImage,outputfile);

}
// std::cout <<argv[2]<< '\n';
if(argc ==5 && string(argv[2])=="-x")
{  std::cout <<"-x executing" << '\n';

  // cout<<"We are here with "<<argc<<" commands";
  stringstream ss(argv[3]);
  string operation =argv[2];
  string outputfile=argv[argc-1];
  if(!isdigit(*(argv[3]))){
    cout<<"i should be a digit"<<endl;
    exit(1);
  }

  int firstImage;
  ss>>firstImage;
  volImage.extract(firstImage,outputfile);
}

if(argc ==5 && string(argv[2])=="-r"){
  std::cout <<"-r executing" << '\n';
stringstream ss(argv[1]);
string operation =argv[2];
string outputfile=argv[argc-1];
int row;
ss>>row;
volImage.extractOnRows(row,outputfile);

}

if(argc<3)
{
  volImage.volImageSize();
}
return 0;}
