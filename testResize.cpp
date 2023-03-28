//
// Created by 24091 on 2023-03-28.
//
#include <iostream>

#include <string>
#include "ImgFormatConv.h"
#include "ImgOperation.h"
#include <thread>
using namespace std;


int main() {
    ImgFormatConv imgfile("../images.jpg",ImgFormatType::png);
    ImgOperation ImgOp(imgfile);
    ImgOp.Rotation(50,0.8);
    // ImgOp.Translate(10.0,10.0);
    ImgOp.Resize(960,640);
     auto str = imgfile.GetFilename();
    //  auto bol=imgfile.isOpenFile();
    // imgfile.ConverImgFormat("../tiger.png");
     // std::cout<<str<<":"<<bol;
  
    return 0;
}
