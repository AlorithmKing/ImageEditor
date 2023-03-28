//
// Created by 24091 on 2023-03-28.
//

#ifndef FILESYSTEM_IMGFORMATCONV_H
#define FILESYSTEM_IMGFORMATCONV_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <opencv2/opencv.hpp>
using namespace cv;
enum class ImgFormatType
{
    jpg,
    jpeg,
    png,
    bmp,
    errorType
};

//设计模式：接口隔离 单一职责
class VImgFormat
{
public :
    ~VImgFormat()=default;
    [[nodiscard]] virtual ImgFormatType GetImgFormat() const = 0;
    virtual ImgFormatType SetImgFormat(ImgFormatType) = 0;
};

//作用： 获取图像文件的后缀属性 并可以修改成目标属性后缀
class ImgFormat : public VImgFormat
{
public:
    explicit ImgFormat(ImgFormatType type);
    inline ImgFormatType GetImgFormat() const override
    { return DisImgFormatType_; }
    ImgFormatType SetImgFormat(ImgFormatType Newtype) override;
    std::string GetMapValue(ImgFormatType) const;
    ImgFormatType GetMapKey(const std::string &) const;
    ~ImgFormat() = default;
private:
    ImgFormatType DisImgFormatType_;
    std::unordered_map<ImgFormatType, std::string> ImgFormatMap_;
};

class VImgFormatConv
{
public:
    ~VImgFormatConv()=default;
 
    [[nodiscard]] virtual std::string GetFilename() const = 0;
    virtual void SetFilename(const std::string &) = 0;
};

class ImgFormatConv : public VImgFormatConv
{
public:
public:
    ImgFormatConv(const std::string &&filename, ImgFormatType Distype);
    inline std::string GetFilename() const override
    { return _filename; }
    inline void SetFilename(const std::string &name) override
    { _filename = name; }
    inline std::shared_ptr<Mat> GetImg() const
    { return std::make_shared<Mat>(SrcImg_); }
    void ConvertImgFormat(std::string &&savefilename);
    ~ImgFormatConv()=default;
protected:
    bool isOpenFile();
    int GetSourceImgFormatPos();
private:
    ImgFormat ImgFormat_;
    Mat SrcImg_;
    std::string _filename;
};

#endif //FILESYSTEM_IMGFORMATCONV_H
