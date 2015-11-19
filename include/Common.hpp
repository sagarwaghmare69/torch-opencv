#pragma once
#include <opencv2/core.hpp>

extern "C" {
#include <TH/TH.h>
}

#include <iostream>
#include <array>

extern "C" int getIntMax() { return INT_MAX; }

/***************** Tensor <=> Mat conversion *****************/

#define TO_MAT_OR_NOARRAY(mat) (mat.isNull() ? cv::noArray() : mat.toMat())

#define TO_MAT_LIST_OR_NOARRAY(mat) (mat.isNull() ? cv::noArray() : mat.toMatList())

struct TensorWrapper {
    void *tensorPtr;
    char typeCode;

    TensorWrapper();
    TensorWrapper(cv::Mat & mat);
    TensorWrapper(cv::Mat && mat);
    operator cv::Mat();
    // synonym for operator cv::Mat()
    inline cv::Mat toMat() { return *this; }

    inline bool isNull() { return tensorPtr == nullptr; }
};

struct TensorArray {
    struct TensorWrapper *tensors;
    short size;

    TensorArray();
    TensorArray(std::vector<cv::Mat> & matList);
    explicit TensorArray(short size);

    operator std::vector<cv::Mat>();
    // synonym for operator std::vector<cv::Mat>()
    inline std::vector<cv::Mat> toMatList() { return *this; }

    inline bool isNull() { return tensors == nullptr; }
};

inline
std::string typeStr(cv::Mat & mat) {
    switch (mat.depth()) {
        case CV_8U:  return "Byte";
        case CV_8S:  return "Char";
        case CV_16S: return "Short";
        case CV_32S: return "Int";
        case CV_32F: return "Float";
        case CV_64F: return "Double";
        default:     return "Unknown";
    }
}

/***************** Wrappers for small OpenCV classes *****************/

struct SizeWrapper {
    int width, height;

    inline operator cv::Size() { return cv::Size(width, height); }
    SizeWrapper(const cv::Size & other);
    inline SizeWrapper() {}
};

struct Size2fWrapper {
    float width, height;

    inline operator cv::Size2f() { return cv::Size2f(width, height); }
    inline Size2fWrapper() {}
    Size2fWrapper(const cv::Size2f & other);
};

struct TermCriteriaWrapper {
    int type, maxCount;
    double epsilon;

    inline operator cv::TermCriteria() { return cv::TermCriteria(type, maxCount, epsilon); }
    inline cv::TermCriteria orDefault(cv::TermCriteria defaultVal) {
        return (this->type == 0 ? defaultVal : *this);
    }
    TermCriteriaWrapper(cv::TermCriteria && other);
};

struct ScalarWrapper {
    double v0, v1, v2, v3;

    inline operator cv::Scalar() { return cv::Scalar(v0, v1, v2, v3); }
    inline cv::Scalar orDefault(cv::Scalar defaultVal) {
        return (isnan(this->v0) ? defaultVal : *this);
    }
};

struct Vec2dWrapper {
    double v0, v1;

    inline operator cv::Vec2d() { return cv::Vec2d(v0, v1); }
    inline Vec2dWrapper(const cv::Vec2d & other) {
        this->v0 = other.val[0];
        this->v1 = other.val[1];
    }
};

struct Vec3dWrapper {
    double v0, v1, v2;
};

struct Vec3fWrapper {
    float v0, v1, v2;
};

struct Vec3iWrapper {
    int v0, v1, v2;
};

struct RectWrapper {
    int x, y, width, height;

    inline operator cv::Rect() { return cv::Rect(x, y, width, height); }
    RectWrapper & operator=(cv::Rect & other);
    RectWrapper(const cv::Rect & other);
    inline RectWrapper() {}
};

struct PointWrapper {
    int x, y;

    inline operator cv::Point() { return cv::Point(x, y); }
    PointWrapper(const cv::Point & other);
};

struct Point2fWrapper {
    float x, y;

    inline operator cv::Point2f() { return cv::Point2f(x, y); }
    Point2fWrapper(const cv::Point2f & other);
    inline Point2fWrapper() {}
};

struct RotatedRectWrapper {
    struct Point2fWrapper center;
    struct Size2fWrapper size;
    float angle;

    inline operator cv::RotatedRect() { return cv::RotatedRect(center, size, angle); }
    RotatedRectWrapper(const cv::RotatedRect & other);
};

struct MomentsWrapper {
    double m00, m10, m01, m20, m11, m02, m30, m21, m12, m03;
    double mu20, mu11, mu02, mu30, mu21, mu12, mu03;
    double nu20, nu11, nu02, nu30, nu21, nu12, nu03;

    MomentsWrapper(const cv::Moments & other);
    inline operator cv::Moments() {
        return cv::Moments(m00, m10, m01, m20, m11, m02, m30, m21, m12, m03);
    }
};

/***************** Helper wrappers for [OpenCV class + some primitive] *****************/

struct TensorPlusDouble {
    struct TensorWrapper tensor;
    double val;
};

struct TensorPlusFloat {
    struct TensorWrapper tensor;
    float val;
};

struct TensorPlusInt {
    struct TensorWrapper tensor;
    int val;
};

struct TensorPlusBool {
    struct TensorWrapper tensor;
    bool val;
};

struct TensorArrayPlusFloat {
    struct TensorArray tensors;
    float val;
};

struct TensorArrayPlusDouble {
    struct TensorArray tensors;
    double val;
};

struct TensorArrayPlusInt {
    struct TensorArray tensors;
    int val;
};

struct TensorArrayPlusBool {
    struct TensorArray tensors;
    bool val;
};

struct RectPlusInt {
    struct RectWrapper rect;
    int val;
};

struct ScalarPlusBool {
    struct ScalarWrapper scalar;
    bool val;
};

struct SizePlusInt {
    struct SizeWrapper size;
    int val;
};

struct Point2fPlusInt {
    struct Point2fWrapper point;
    int val;
};

/***************** Other helper structs *****************/

// Arrays

struct IntArray {
    int *data;
    int size;
};

struct FloatArray {
    float *data;
    int size;
    inline std::vector<float>& toFloatList(std::vector<float>& res) {
        for (int i = 0; i < size; ++i)
            res.push_back(data[i]);
        return res;
    }
};

struct DoubleArray {
    double *data;
    int size;
};

struct PointArray {
    struct PointWrapper *data;
    int size;
};

struct RectArray {
    struct RectWrapper *data;
    int size;
};

// Arrays of arrays

struct FloatArrayOfArrays {
    float **pointers;
    float *realData;
    int dims;
};

struct PointArrayOfArrays {
    struct PointWrapper **pointers;
    struct PointWrapper *realData;
    int dims;
    int *sizes;
};
