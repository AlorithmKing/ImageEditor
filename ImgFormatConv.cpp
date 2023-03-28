
#include "ImgFormatConv.h"
ImgFormat::ImgFormat(ImgFormatType type) : _DisImgFormatType{type}
{
    _ImgFormatMap = {{ImgFormatType::jpg,  "jpg"},
                     {ImgFormatType::jpeg, "jpeg"},
                     {ImgFormatType::png,  "png"},
                     {ImgFormatType::bmp,  "bmp"}};
}
ImgFormatType ImgFormat::SetImgFormat(const ImgFormatType Newtype)
{
    _DisImgFormatType = Newtype;
}
std::string ImgFormat::GetMapValue(const ImgFormatType type) const
{
    for (auto iter: _ImgFormatMap)
    {
        if (iter.first == type)
            return iter.second;
    }
    return std::string();
}
bool ImgFormatConv::isOpenFile()
{
    auto pos = GetSourceImgFormatPos();
    if (pos == -1)
    {
        std::cerr << "Error Format!";
        return false;
    } else
    {
        auto _str = _filename.substr(pos + 1);
        std::cout << _str;
        if (_str == "jpg" || _str == "jpeg" || _str == "png" || _str == "bmp")
        {
            std::cout << _str << std::endl;
            return true;
        }
        return false;
    }
}
void ImgFormatConv::ConvertImgFormat(const std::string &savefilename)
{
    auto pos = GetSourceImgFormatPos();
    auto Distancetype = _ImgFormat.GetImgFormat();
    auto DistanceFormat = _ImgFormat.GetMapValue(Distancetype);
    auto SourceFormat = _filename.substr(pos + 1);
    if (!_SrcImg.empty())
    {
        if (SourceFormat == "png" && DistanceFormat != "png")
        {
            cv::Mat dstImage;
            cv::cvtColor(_SrcImg, dstImage, COLOR_BGRA2BGR);
            cv::imwrite(savefilename, dstImage);
        } else if (DistanceFormat == "png" && SourceFormat != "png")
        {
            cv::Mat dstImage;
            cv::cvtColor(_SrcImg, dstImage, COLOR_BGR2BGRA);
            
            // 将灰度图像保存为PNG格式
            cv::imwrite(savefilename, dstImage);
        } else
            imwrite(savefilename, _SrcImg);
    } else
        std::cerr << "Img is empty!" << std::endl;
}
int ImgFormatConv::GetSourceImgFormatPos()
{
    auto pos = _filename.find_last_of(".");
    if (pos == std::string::npos)
        return -1;
    else
        return pos;
}
ImgFormatConv::ImgFormatConv(const std::string &&filename, ImgFormatType Distype) : _filename{
        std::forward<const std::string>(filename)},
                                                                                    _ImgFormat{Distype}
{
    if (isOpenFile())
    {
        auto pos = GetSourceImgFormatPos();
        auto sourceFormat = _filename.substr(pos + 1);
        auto SourceType = StringToType(sourceFormat);
        switch (SourceType)
        {
            case ImgFormatType::jpeg:
            case ImgFormatType::jpg:
            case ImgFormatType::bmp:
                _SrcImg = imread(_filename, cv::IMREAD_COLOR);
                break;
            case ImgFormatType::png:
                _SrcImg = imread(_filename, IMREAD_UNCHANGED);
                break;
            default:
                break;
        }
    } else
        std::cerr << "Error clash,This project Only support jpg,jpeg,png,bmp!";
}
ImgFormatType ImgFormatConv::StringToType(const std::string str)
{
    if (str == "jpg")
        return ImgFormatType::jpg;
    else if (str == "jpeg")
        return ImgFormatType::jpeg;
    else if (str == "png")
        return ImgFormatType::png;
    else if (str == "bmp")
        return ImgFormatType::bmp;
    else
        std::cerr << "Error params";
}
