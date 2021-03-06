local cv = require 'cv._env'

local ffi = require 'ffi'
require 'cv.Classes'

ffi.cdef[[
struct TensorWrapper BackgroundSubtractor_apply(struct PtrWrapper ptr, struct TensorWrapper image,
                        struct TensorWrapper fgmast, double learningRate);

struct TensorWrapper BackgroundSubtractor_getBackgroundImage(struct PtrWrapper ptr,
                        struct TensorWrapper backgroundImage);

struct PtrWrapper BackgroundSubtractorMOG2_ctor(int history, double varThreshold, bool detectShadows);

int BackgroundSubtractorMOG2_getHistory(struct PtrWrapper ptr);

void BackgroundSubtractorMOG2_setHistory(struct PtrWrapper ptr, int history);

int BackgroundSubtractorMOG2_getNMixtures(struct PtrWrapper ptr);

void BackgroundSubtractorMOG2_setNMixtures(struct PtrWrapper ptr, int nmixtures);

int BackgroundSubtractorMOG2_getShadowValue(struct PtrWrapper ptr);

void BackgroundSubtractorMOG2_setShadowValue(struct PtrWrapper ptr, int shadow_value);

double BackgroundSubtractorMOG2_getBackgroundRatio(struct PtrWrapper ptr);

void BackgroundSubtractorMOG2_setBackgroundRatio(struct PtrWrapper ptr, double ratio);

double BackgroundSubtractorMOG2_getVarThreshold(struct PtrWrapper ptr);

void BackgroundSubtractorMOG2_setVarThreshold(struct PtrWrapper ptr, double varThreshold);

double BackgroundSubtractorMOG2_getVarThresholdGen(struct PtrWrapper ptr);

void BackgroundSubtractorMOG2_setVarThresholdGen(struct PtrWrapper ptr, double varThresholdGen);

double BackgroundSubtractorMOG2_getVarInit(struct PtrWrapper ptr);

void BackgroundSubtractorMOG2_setVarInit(struct PtrWrapper ptr, double varInit);

double BackgroundSubtractorMOG2_getVarMin(struct PtrWrapper ptr);

void BackgroundSubtractorMOG2_setVarMin(struct PtrWrapper ptr, double varMin);

double BackgroundSubtractorMOG2_getVarMax(struct PtrWrapper ptr);

void BackgroundSubtractorMOG2_setVarMax(struct PtrWrapper ptr, double varMax);

bool BackgroundSubtractorMOG2_getDetectShadows(struct PtrWrapper ptr);

void BackgroundSubtractorMOG2_setDetectShadows(struct PtrWrapper ptr, bool detectShadows);

double BackgroundSubtractorMOG2_getComplexityReductionThreshold(struct PtrWrapper ptr);

void BackgroundSubtractorMOG2_setComplexityReductionThreshold(struct PtrWrapper ptr, double complexityReductionThreshold);

double BackgroundSubtractorMOG2_getShadowThreshold(struct PtrWrapper ptr);

void BackgroundSubtractorMOG2_setShadowThreshold(struct PtrWrapper ptr, double shadowThreshold);

struct PtrWrapper BackgroundSubtractorKNN_ctor(int history, double dist2Threshold, bool detectShadows);

int BackgroundSubtractorKNN_getHistory(struct PtrWrapper ptr);

void BackgroundSubtractorKNN_setHistory(struct PtrWrapper ptr, int history);

int BackgroundSubtractorKNN_getNSamples(struct PtrWrapper ptr);

void BackgroundSubtractorKNN_setNSamples(struct PtrWrapper ptr, int nSamples);

int BackgroundSubtractorKNN_getkNNSamples(struct PtrWrapper ptr);

void BackgroundSubtractorKNN_setkNNSamples(struct PtrWrapper ptr, int kNNSamples);

int BackgroundSubtractorKNN_getShadowValue(struct PtrWrapper ptr);

void BackgroundSubtractorKNN_setShadowValue(struct PtrWrapper ptr, int shadowValue);

double BackgroundSubtractorKNN_getDist2Threshold(struct PtrWrapper ptr);

void BackgroundSubtractorKNN_setDist2Threshold(struct PtrWrapper ptr, double dist2Threshold);

double BackgroundSubtractorKNN_getShadowThreshold(struct PtrWrapper ptr);

void BackgroundSubtractorKNN_setShadowThreshold(struct PtrWrapper ptr, double shadowThreshold);

bool BackgroundSubtractorKNN_getDetectShadows(struct PtrWrapper ptr);

void BackgroundSubtractorKNN_setDetectShadows(struct PtrWrapper ptr, bool detectShadows);
]]

local C = ffi.load(cv.libPath('video'))
local Classes = ffi.load(cv.libPath('Classes'))

-- BackgroundSubtractor

do
    local BackgroundSubtractor = cv.newTorchClass('cv.BackgroundSubtractor', 'cv.Algorithm')

    function BackgroundSubtractor:apply()
        local argRules = {
            {"image", required = true},
            {"fgmast", default = nil},
            {"learningRate", default = -1}
        }
        local image, fgmast, learningRate = cv.argcheck(t, argRules)

        return cv.unwrap_tensors(
                C.BackgroundSubtractor_apply(
                    self.ptr, cv.wrap_tensors(image), cv.wrap_tensor(fgmast), learningRate))
    end

    function BackgroundSubtractor:getBackgroundImage(t)
        local argRules = {
            {"backgroundImage", required = true}
        }
        local backgroundImage = cv.argcheck(t, argRules)

        return cv.unwrap_tensors(
            C.BackgroundSubtractor_getBackgroundImage(self.ptr, cv.wrap_tensor(backgroundImage)))
    end
end

-- BackgroundSubtractorMOG2

do
    local BackgroundSubtractorMOG2 = cv.newTorchClass('cv.BackgroundSubtractorMOG2', 'cv.BackgroundSubtractor')

    function BackgroundSubtractorMOG2:__init(t)
        local argRules = {
            {"history", default = 500},
            {"varThreshold", default = 16},
            {"detectShadows", default = true}
        }
        local history, varThreshold, detectShadows = cv.argcheck(t, argRules)

        self.ptr = ffi.gc(C.BackgroundSubtractorMOG2_ctor(history, varThreshold, detectShadows), Classes.Algorithm_dtor)
    end

    function BackgroundSubtractorMOG2:getHistory()
        return C.BackgroundSubtractorMOG2_getHistory(self.ptr)
    end

    function BackgroundSubtractorMOG2:setHistory(t)
        local argRules = {
            {"history", required = true}
        }
        local history = cv.argcheck(t, argRules)

        C.BackgroundSubtractorMOG2_setHistory(self.ptr, history)
    end

    function BackgroundSubtractorMOG2:getNMixtures()
        return C.BackgroundSubtractorMOG2_getNMixtures(self.ptr)
    end

    function BackgroundSubtractorMOG2:setNMixtures(t)
        local argRules = {
            {"nmixtures", required = true}
        }
        local nmixtures = cv.argcheck(t, argRules)

        C.BackgroundSubtractorMOG2_setNMixtures(self.ptr, nmixtures)
    end

    function BackgroundSubtractorMOG2:getShadowValue()
        return C.BackgroundSubtractorMOG2_getShadowValue(self.ptr)
    end

    function BackgroundSubtractorMOG2:setShadowValue(t)
        local argRules = {
            {"shadow_value", required = true}
        }
        local shadow_value = cv.argcheck(t, argRules)

        C.BackgroundSubtractorMOG2_setShadowValue(self.ptr, shadow_value)
    end

    function BackgroundSubtractorMOG2:getBackgroundRatio()
        return C.BackgroundSubtractorMOG2_getBackgroundRatio(self.ptr)
    end

    function BackgroundSubtractorMOG2:setBackgroundRatio(t)
        local argRules = {
            {"ratio", required = true}
        }
        local ratio = cv.argcheck(t, argRules)

        C.BackgroundSubtractorMOG2_setBackgroundRatio(self.ptr, ratio)
    end

    function BackgroundSubtractorMOG2:getVarThreshold()
        return C.BackgroundSubtractorMOG2_getVarThreshold(self.ptr)
    end

    function BackgroundSubtractorMOG2:setVarThreshold(t)
        local argRules = {
            {"varThreshold", required = true}
        }
        local varThreshold = cv.argcheck(t, argRules)

        C.BackgroundSubtractorMOG2_setVarThreshold(self.ptr, varThreshold)
    end

    function BackgroundSubtractorMOG2:getVarThresholdGen()
        return C.BackgroundSubtractorMOG2_getVarThresholdGen(self.ptr)
    end

    function BackgroundSubtractorMOG2:setVarThresholdGen(t)
        local argRules = {
            {"varThresholdGen", required = true}
        }
        local varThresholdGen = cv.argcheck(t, argRules)

        C.BackgroundSubtractorMOG2_setVarThresholdGen(self.ptr, varThresholdGen)
    end

    function BackgroundSubtractorMOG2:getVarInit()
        return C.BackgroundSubtractorMOG2_getVarInit(self.ptr)
    end

    function BackgroundSubtractorMOG2:setVarInit(t)
        local argRules = {
            {"varInit", required = true}
        }
        local varInit = cv.argcheck(t, argRules)

        C.BackgroundSubtractorMOG2_setVarInit(self.ptr, varInit)
    end

    function BackgroundSubtractorMOG2:getVarMin()
        return C.BackgroundSubtractorMOG2_getVarMin(self.ptr)
    end

    function BackgroundSubtractorMOG2:setVarMin(t)
        local argRules = {
            {"varMin", required = true}
        }
        local varMin = cv.argcheck(t, argRules)

        C.BackgroundSubtractorMOG2_setVarMin(self.ptr, varMin)
    end

    function BackgroundSubtractorMOG2:getVarMax()
        return C.BackgroundSubtractorMOG2_getVarMax(self.ptr)
    end

    function BackgroundSubtractorMOG2:setVarMax(t)
        local argRules = {
            {"varMax", required = true}
        }
        local varMax = cv.argcheck(t, argRules)

        C.BackgroundSubtractorMOG2_setVarMax(self.ptr, varMax)
    end

    function BackgroundSubtractorMOG2:getDetectShadows()
        return C.BackgroundSubtractorMOG2_getDetectShadows(self.ptr)
    end

    function BackgroundSubtractorMOG2:setDetectShadows(t)
        local argRules = {
            {"detectShadows", required = true}
        }
        local detectShadows = cv.argcheck(t, argRules)

        C.BackgroundSubtractorMOG2_setDetectShadows(self.ptr, detectShadows)
    end

    function BackgroundSubtractorMOG2:getComplexityReductionThreshold()
        return C.BackgroundSubtractorMOG2_getComplexityReductionThreshold(self.ptr)
    end

    function BackgroundSubtractorMOG2:setComplexityReductionThreshold(t)
        local argRules = {
            {"ct", required = true}
        }
        local complexityReductionThreshold = cv.argcheck(t, argRules)

        C.BackgroundSubtractorMOG2_setComplexityReductionThreshold(self.ptr, complexityReductionThreshold)
    end

    function BackgroundSubtractorMOG2:getShadowThreshold()
        return C.BackgroundSubtractorMOG2_getShadowThreshold(self.ptr)
    end

    function BackgroundSubtractorMOG2:setShadowThreshold(t)
        local argRules = {
            {"threshold", required = true}
        }
        local shadowThreshold = cv.argcheck(t, argRules)

        C.BackgroundSubtractorMOG2_setShadowThreshold(self.ptr, shadowThreshold)
    end
end

-- BackgroundSubtractorKNN

do
    local BackgroundSubtractorKNN = cv.newTorchClass('cv.BackgroundSubtractorKNN', 'cv.BackgroundSubtractor')

    function BackgroundSubtractorKNN:__init(t)
        local argRules = {
            {"history", default = 500},
            {"dist2Threshold", default = 400.0},
            {"detectShadows", default = true}
        }
        local history, dist2Threshold, detectShadows = cv.argcheck(t, argRules)

        self.ptr = ffi.gc(C.BackgroundSubtractorKNN_ctor(history, dist2Threshold, detectShadows), Classes.Algorithm_dtor)
    end

    function BackgroundSubtractorKNN:getHistory()
        return C.BackgroundSubtractorKNN_getHistory(self.ptr)
    end

    function BackgroundSubtractorKNN:setHistory(t)
        local argRules = {
            {"history", required = true}
        }
        local history = cv.argcheck(t, argRules)

        C.BackgroundSubtractorKNN_setHistory(self.ptr, history)
    end

    function BackgroundSubtractorKNN:getNSamples()
        return C.BackgroundSubtractorKNN_getNSamples(self.ptr)
    end

    function BackgroundSubtractorKNN:setNSamples(t)
        local argRules = {
            {"_nN", required = true}
        }
        local nSamples = cv.argcheck(t, argRules)

        C.BackgroundSubtractorKNN_setNSamples(self.ptr, nSamples)
    end

    function BackgroundSubtractorKNN:getkNNSamples()
        return C.BackgroundSubtractorKNN_getkNNSamples(self.ptr)
    end

    function BackgroundSubtractorKNN:setkNNSamples(t)
        local argRules = {
            {"_nkNN", required = true}
        }
        local kNNSamples = cv.argcheck(t, argRules)

        C.BackgroundSubtractorKNN_setkNNSamples(self.ptr, kNNSamples)
    end

    function BackgroundSubtractorKNN:getShadowValue()
        return C.BackgroundSubtractorKNN_getShadowValue(self.ptr)
    end

    function BackgroundSubtractorKNN:setShadowValue(t)
        local argRules = {
            {"value", required = true}
        }
        local shadowValue = cv.argcheck(t, argRules)

        C.BackgroundSubtractorKNN_setShadowValue(self.ptr, shadowValue)
    end

    function BackgroundSubtractorKNN:getDist2Threshold()
        return C.BackgroundSubtractorKNN_getDist2Threshold(self.ptr)
    end

    function BackgroundSubtractorKNN:setDist2Threshold(t)
        local argRules = {
            {"_dist2Threshold", required = true}
        }
        local dist2Threshold = cv.argcheck(t, argRules)

        C.BackgroundSubtractorKNN_setDist2Threshold(self.ptr, dist2Threshold)
    end

    function BackgroundSubtractorKNN:getShadowThreshold()
        return C.BackgroundSubtractorKNN_getShadowThreshold(self.ptr)
    end

    function BackgroundSubtractorKNN:setShadowThreshold(t)
        local argRules = {
            {"threshold", required = true}
        }
        local shadowThreshold = cv.argcheck(t, argRules)

        C.BackgroundSubtractorKNN_setShadowThreshold(self.ptr, shadowThreshold)
    end

    function BackgroundSubtractorKNN:getDetectShadows()
        return C.BackgroundSubtractorKNN_getDetectShadows(self.ptr)
    end

    function BackgroundSubtractorKNN:setDetectShadows(t)
        local argRules = {
            {"detectShadows", required = true}
        }
        local detectShadows = cv.argcheck(t, argRules)

        C.BackgroundSubtractorKNN_setDetectShadows(self.ptr, detectShadows)
    end
end

return cv