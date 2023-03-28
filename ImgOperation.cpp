//
// Created by 24091 on 2023-03-28.
//

#include "ImgOperation.h"

Mat ImgOperation::GetWarpAffineMatrix()
{
    Point2f srcTri[3];
    Point2f dstTri[3];
    Mat warp_mat{2, 3, CV_32FC1};
    //设置三个点来计算仿射变换
    srcTri[0] = Point2f(0, 0);
    srcTri[1] = Point2f(_Img->cols - 1, 0);
    srcTri[2] = Point2f(0, _Img->rows - 1);
    
    dstTri[0] = Point2f(_Img->cols*0.0, _Img->rows*0.33);
    dstTri[1] = Point2f(_Img->cols*0.85,_Img->rows*0.25);
    dstTri[2] = Point2f(_Img->cols*0.15, _Img->rows*0.7);
    //计算仿射变换矩阵
    warp_mat = getAffineTransform(srcTri, dstTri);
    return warp_mat;
}
void ImgOperation::Rotation(float _angle,float Scale)
{
    Mat rot_mat{2, 3, CV_32F};
    auto center = GetImgCenter();
    auto Rmatrix = getRotationMatrix2D(center,_angle,Scale);
    Mat warp_dstImage = _Img->clone();
    warpAffine(*_Img,warp_dstImage,Rmatrix,warp_dstImage.size());
    ImgShow("Rotation Image",warp_dstImage);
    
}
void ImgOperation::Resize(int width, int height)
{
    if(width<0||height<0)
        std::cerr<<"Error params of shape! ";
    _Img->resize(width,height);
    ImgShow("Resize img",*_Img);
}
void ImgOperation::Translate(float  dx, float  dy)
{
    float  TransArray[]={1.0,0,dx,0,1.0,dy};//必须是浮点型
    Mat rot_mat{2, 3, CV_32F,TransArray};
    Mat translated_image = _Img->clone();
    warpAffine(*_Img,translated_image,rot_mat,translated_image.size());
    ImgShow("Translation Image",translated_image);
}
void ImgOperation::ImgShow(const std::string& name, Mat& mat) const
{
    imshow(name,mat);
    waitKey(0);
}

