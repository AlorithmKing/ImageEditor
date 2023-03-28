//
// Created by 24091 on 2023-03-28.
//
#include <iostream>

#include <string>
#include "ImgFormatConv.h"
using namespace std;


int main() {
    ImgFormatConv imgfile("../images.jpg",ImgFormatType::png);
    //  auto str = imgfile.GetFilename();
    //  auto bol=imgfile.isOpenFile();
    imgfile.ConvertImgFormat("../images.png");
    //  // std::cout<<str<<":"<<bol;
    
    return 0;
}
