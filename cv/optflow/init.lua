local cv = require 'cv._env'

local ffi = require 'ffi'

ffi.cdef[[

]]

local C = ffi.load(cv.libPath('optflow'))

return cv
