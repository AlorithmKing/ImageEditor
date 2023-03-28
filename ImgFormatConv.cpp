
#include "ImgFormatConv.h"
ImgFormat::ImgFormat(ImgFormatType type) : DisImgFormatType_{type}
{
    ImgFormatMap_ = {{ImgFormatType::jpg,  "jpg"},
                     {ImgFormatType::jpeg, "jpeg"},
                     {ImgFormatType::png,  "png"},
                     {ImgFormatType::bmp,  "bmp"}};
}
ImgFormatType ImgFormat::SetImgFormat(const ImgFormatType Newtype)
{
    DisImgFormatType_ = Newtype;
}
std::string ImgFormat::GetMapValue(const ImgFormatType type) const
{
    for (auto &iter: ImgFormatMap_)
    {
        if (iter.first == type)
            return iter.second;
    }
    return std::string{};
}
ImgFormatType ImgFormat::GetMapKey(const std::string &str) const
{
    for (auto &iter: ImgFormatMap_)
        if (iter.second == str)
            return ImgFormatType::png;
    return ImgFormatType::errorType;
}
bool ImgFormatConv::isOpenFile()
{
    auto pos = GetSourceImgFormatPos();
    if (pos == -1)
    {
        std::cerr << "Error!Can't find given token!";
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
void ImgFormatConv::ConvertImgFormat(std::string &&savefilename)
{
    auto pos = GetSourceImgFormatPos();
    auto Distancetype = ImgFormat_.GetImgFormat();
    auto DistanceFormat = ImgFormat_.GetMapValue(Distancetype);
    auto SourceFormat = _filename.substr(pos + 1);
    savefilename = _filename.substr(0, pos + 1) + DistanceFormat;
    std::cout << savefilename;
    if (!SrcImg_.empty())
    {
        if (SourceFormat == "png" && DistanceFormat != "png") //png->others
        {
            cv::Mat dstImage;
            cv::cvtColor(SrcImg_, dstImage, COLOR_BGRA2BGR);
            cv::imwrite(savefilename, dstImage);
        } else if (DistanceFormat == "png" && SourceFormat != "png")//others->png
        {
            cv::Mat dstImage;
            cv::cvtColor(SrcImg_, dstImage, COLOR_BGR2BGRA);
            
            // 将灰度图像保存为PNG格式
            cv::imwrite(savefilename, dstImage);
        } else
            imwrite(savefilename, SrcImg_);
    } else
        std::cerr << "ImgData is empty!" << std::endl;
}
int ImgFormatConv::GetSourceImgFormatPos()
{
    auto pos = _filename.find_last_of('.');
    if (pos == std::string::npos)
        return -1;
    else
        return static_cast<int>(pos);
}
ImgFormatConv::ImgFormatConv(const std::string &&filename, ImgFormatType Distype) : _filename{
        std::forward<const std::string>(filename)},
                                                                                    ImgFormat_{Distype}
{
    if (isOpenFile())
    {
        int pos = GetSourceImgFormatPos();
        auto sourceFormat = _filename.substr(pos + 1);
        auto SourceType = ImgFormat_.GetMapKey(sourceFormat);
        switch (SourceType)
        {
            case ImgFormatType::jpeg:
            case ImgFormatType::jpg:
            case ImgFormatType::bmp:
                SrcImg_ = imread(_filename, cv::IMREAD_COLOR);
                break;
            case ImgFormatType::png:
                SrcImg_ = imread(_filename, IMREAD_UNCHANGED);
                break;
            default:
                break;
        }
    } else
        std::cerr << "Open Specific File Fail,This project only supports format likes jpg,jpeg,png,bmp!";
}
