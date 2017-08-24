#include <nan.h>
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include "macros.h"

#ifndef __FF_OBJDETECT_H__
#define __FF_OBJDETECT_H__

class Objdetect {
public:
  static NAN_MODULE_INIT(Init);
};

#endif