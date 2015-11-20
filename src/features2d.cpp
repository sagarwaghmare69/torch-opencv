#include <features2d.hpp>

KeyPointWrapper::KeyPointWrapper(const cv::KeyPoint & other) {
    this->pt = other.pt;
    this->size = other.size;
    this->angle = other.angle;
    this->response = other.response;
    this->octave = other.octave;
    this->class_id = other.class_id;
}

KeyPointArray::KeyPointArray(const std::vector<cv::KeyPoint> & v)
{
    // TODO: IMPORTANT! Prevent memory leak here
    this->size = v.size();
    this->data = static_cast<KeyPointWrapper *>(
            malloc(sizeof(KeyPointWrapper) * this->size));
    for (int i = 0; i < this->size; ++i) {
        this->data[i] = v[i];
    }
}

KeyPointArray::operator std::vector<cv::KeyPoint>()
{
    std::vector<cv::KeyPoint> retval(this->size);
    for (int i = 0; i < this->size; ++i) {
        retval[i] = this->data[i];
    }
    return retval;
}

KeyPointMat::KeyPointMat(const std::vector<std::vector<cv::KeyPoint> > & v)
{
    // TODO: this function
    this->size1 = v.size();
    this->size2 = v[0].size();
}

KeyPointMat::operator std::vector<std::vector<cv::KeyPoint> >()
{
    // TODO: this function
    std::vector<std::vector<cv::KeyPoint> > retval;
    return retval;
}

// KeyPointsFilter

extern "C" struct KeyPointsFilterPtr KeyPointsFilter_ctor()
{
    return new cv::KeyPointsFilter();
}

extern "C" void KeyPointsFilter_dtor(struct KeyPointsFilterPtr ptr)
{
    delete static_cast<cv::KeyPointsFilter *>(ptr.ptr);
}

extern "C" struct KeyPointArray KeyPointsFilter_runByImageBorder(struct KeyPointArray keypoints,
                    struct SizeWrapper imageSize, int borderSize)
{
    std::vector<cv::KeyPoint> keypointsVector(keypoints);
    cv::KeyPointsFilter::runByImageBorder(keypointsVector, imageSize, borderSize);
    return KeyPointArray(keypointsVector);
}

extern "C" struct KeyPointArray KeyPointsFilter_runByKeypointSize(struct KeyPointArray keypoints,
                        float minSize, float maxSize)
{
    std::vector<cv::KeyPoint> keypointsVector(keypoints);
    cv::KeyPointsFilter::runByKeypointSize(keypointsVector, minSize, maxSize);
    return KeyPointArray(keypointsVector);
}

extern "C" struct KeyPointArray KeyPointsFilter_runByPixelsMask(struct KeyPointArray keypoints,
                        struct TensorWrapper mask)
{
    std::vector<cv::KeyPoint> keypointsVector(keypoints);
    cv::KeyPointsFilter::runByPixelsMask(keypointsVector, mask.toMat());
    return KeyPointArray(keypointsVector);
}

extern "C" struct KeyPointArray KeyPointsFilter_removeDuplicated(struct KeyPointArray keypoints)
{
    std::vector<cv::KeyPoint> keypointsVector(keypoints);
    cv::KeyPointsFilter::removeDuplicated(keypointsVector);
    return KeyPointArray(keypointsVector);
}

extern "C" struct KeyPointArray KeyPointsFilter_retainBest(struct KeyPointArray keypoints, int npoints)
{
    std::vector<cv::KeyPoint> keypointsVector(keypoints);
    cv::KeyPointsFilter::retainBest(keypointsVector, npoints);
    return KeyPointArray(keypointsVector);
}

// Feature2D

extern "C" struct Feature2DPtr Feature2D_ctor()
{
    return new cv::Feature2D();
}

extern "C" struct KeyPointArray Feature2D_detect(struct Feature2DPtr ptr, struct TensorWrapper image,
                        struct KeyPointArray keypoints, struct TensorWrapper mask)
{
    std::vector<cv::KeyPoint> keypointsVector(keypoints);
    ptr->detect(image.toMat(), keypointsVector, TO_MAT_OR_NOARRAY(mask));
    return KeyPointArray(keypointsVector);
}

extern "C" struct KeyPointMat Feature2D_detect2(struct Feature2DPtr ptr, struct TensorArray images,
                        struct KeyPointMat keypoints, struct TensorArray masks)
{
    std::vector<std::vector<cv::KeyPoint> > keypointsMat(keypoints);
    ptr->detect(images.toMatList(), keypointsMat, TO_MAT_LIST_OR_NOARRAY(masks));
    return KeyPointMat(keypointsMat);
}

extern "C" struct KeyPointArray Feature2D_compute(struct Feature2DPtr ptr, struct TensorWrapper image,
                        struct KeyPointArray keypoints, struct TensorWrapper descriptors)
{
    std::vector<cv::KeyPoint> keypointsVector(keypoints);
    ptr->compute(image.toMat(), keypointsVector, descriptors.toMat());
    return KeyPointArray(keypointsVector);
}

extern "C" struct KeyPointMat Feature2D_compute2(struct Feature2DPtr ptr, struct TensorArray images,
                        struct KeyPointMat keypoints, struct TensorArray descriptors)
{
    std::vector<std::vector<cv::KeyPoint> > keypointsMat(keypoints);
    ptr->compute(images.toMatList(), keypointsMat, descriptors.toMatList());
    return KeyPointMat(keypointsMat);
}

extern "C" struct KeyPointArray Feature2D_detectAndCompute(struct Feature2DPtr ptr, struct TensorWrapper image,
                        struct TensorWrapper mask, struct KeyPointArray keypoints,
                        struct TensorWrapper descriptors, bool useProvidedKeypoints)
{
    std::vector<cv::KeyPoint> keypointsVector(keypoints);
    ptr->detectAndCompute(image.toMat(), mask.toMat(), keypointsVector, descriptors.toMat(), useProvidedKeypoints);
    return KeyPointArray(keypointsVector);
}

extern "C" int Feature2D_descriptorSize(struct Feature2DPtr ptr)
{
    return ptr->descriptorSize();
}

extern "C" int Feature2D_descriptorType(struct Feature2DPtr ptr)
{
    return ptr->descriptorType();
}

extern "C" int Feature2D_defaultNorm(struct Feature2DPtr ptr)
{
    return ptr->defaultNorm();
}

extern "C" bool Feature2D_empty(struct Feature2DPtr ptr)
{
    return ptr->empty();
}

// BRISK

extern "C" struct BRISKPtr BRISK_ctor(int thresh, int octaves, float patternScale)
{
    return rescueObjectFromPtr(cv::BRISK::create(thresh, octaves, patternScale));
}

extern "C" struct BRISKPtr BRISK_ctor2(struct TensorWrapper radiusList, struct TensorWrapper numberList,
                        float dMax, float dMin, struct TensorWrapper indexChange)
{
    std::vector<int> indexVec = std::vector<int>();
    if (!indexChange.isNull())
        indexVec = std::vector<int>(indexChange.toMat());

    return rescueObjectFromPtr(cv::BRISK::create(radiusList.toMat(), numberList.toMat(), dMax, dMin, indexVec));
}

// ORB

extern "C" struct ORBPtr ORB_ctor(int nfeatures, float scaleFactor, int nlevels, int edgeThreshold, int firstLevel,
                        int WTA_K, int scoreType, int patchSize, int fastThreshold)
{
    return rescueObjectFromPtr(cv::ORB::create(nfeatures, scaleFactor, nlevels, edgeThreshold, firstLevel,
                            WTA_K, scoreType, patchSize, fastThreshold));
}

extern "C" void ORB_setMaxFeatures(struct ORBPtr ptr, int maxFeatures)
{
    ptr->setMaxFeatures(maxFeatures);
}

extern "C" int ORB_getMaxFeatures(struct ORBPtr ptr)
{
    return ptr->getMaxFeatures();
}

extern "C" void ORB_setScaleFactor(struct ORBPtr ptr, int scaleFactor)
{
    ptr->setScaleFactor(scaleFactor);
}

extern "C" int ORB_getScaleFactor(struct ORBPtr ptr)
{
    return ptr->getScaleFactor();
}

extern "C" void ORB_setNLevels(struct ORBPtr ptr, int nlevels)
{
    ptr->setNLevels(nlevels);
}

extern "C" int ORB_getNLevels(struct ORBPtr ptr)
{
    return ptr->getNLevels();
}

extern "C" void ORB_setEdgeThreshold(struct ORBPtr ptr, int edgeThreshold)
{
    ptr->setEdgeThreshold(edgeThreshold);
}

extern "C" int ORB_getEdgeThreshold(struct ORBPtr ptr)
{
    return ptr->getEdgeThreshold();
}

extern "C" void ORB_setFirstLevel(struct ORBPtr ptr, int firstLevel)
{
    ptr->setFirstLevel(firstLevel);
}

extern "C" int ORB_getFirstLevel(struct ORBPtr ptr)
{
    return ptr->getFirstLevel();
}

extern "C" void ORB_setWTA_K(struct ORBPtr ptr, int wta_k)
{
    ptr->setWTA_K(wta_k);
}

extern "C" int ORB_getWTA_K(struct ORBPtr ptr)
{
    return ptr->getWTA_K();
}

extern "C" void ORB_setScoreType(struct ORBPtr ptr, int scoreType)
{
    ptr->setScoreType(scoreType);
}

extern "C" int ORB_getScoreType(struct ORBPtr ptr)
{
    return ptr->getScoreType();
}

extern "C" void ORB_setPatchSize(struct ORBPtr ptr, int patchSize)
{
    ptr->setPatchSize(patchSize);
}

extern "C" int ORB_getPatchSize(struct ORBPtr ptr)
{
    return ptr->getPatchSize();
}

extern "C" void ORB_setFastThreshold(struct ORBPtr ptr, int fastThreshold)
{
    ptr->setFastThreshold(fastThreshold);
}

extern "C" int ORB_getFastThreshold(struct ORBPtr ptr)
{
    return ptr->getFastThreshold();
}







extern "C" struct KeyPointArray AGAST(struct TensorWrapper image, int threshold, bool nonmaxSuppression)
{
    std::vector<cv::KeyPoint> result;
    cv::AGAST(image.toMat(), result, threshold, nonmaxSuppression);
    return KeyPointArray(result);
}