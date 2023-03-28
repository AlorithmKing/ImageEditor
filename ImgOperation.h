//
// Created by 24091 on 2023-03-28.
//

#ifndef FILESYSTEM_IMGOPERATION_H
#define FILESYSTEM_IMGOPERATION_H
#include <iostream>

#include "ImgFormatConv.h"
#include <opencv2/imgproc.hpp>
// const int MAXWIDTH = GetSystemMetrics(SM_CXSCREEN);
// const int MAXHEIGHT = GetSystemMetrics(SM_CYSCREEN);

class ImgOperation
{
public:
    ImgOperation(ImgFormatConv &picture)
    {
        _Img = picture.GetImg();
    }
    inline Point2f GetImgCenter(){return Point2f (_Img->rows/2,_Img->cols/2);}
    void Rotation(float _angle,float Scale);
    void Resize(int width, int height);
    void Translate(float  dx, float  dy);
    void ImgShow(const std::string&,Mat& ) const;
protected:
    Mat GetWarpAffineMatrix();


private:
    int _width;
    int _height;
    int _channel;
    std::shared_ptr<Mat> _Img;
};

#endif //FILESYSTEM_IMGOPERATION_H
