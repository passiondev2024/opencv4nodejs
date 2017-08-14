#include <nan.h>
#include <opencv2/core.hpp>
#include "macros.h"
#include "coreUtils.h"

#ifndef __FF_VEC3_H__
#define __FF_VEC3_H__

class Vec3 : public Nan::ObjectWrap {
public:
	cv::Vec3d vec;

	static NAN_METHOD(New) {
		Vec3* self = new Vec3();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	}

	static void Init(v8::Local<v8::FunctionTemplate> ctor) {
		FF_PROTO_SET_MATRIX_OPERATIONS(ctor);
	}

	static FF_GETTER(Vec3, GetX, vec[0]);
	static FF_GETTER(Vec3, GetY, vec[1]);
	static FF_GETTER(Vec3, GetZ, vec[2]);

	FF_INIT_VEC3_OPERATIONS();
	static NAN_METHOD(Dot) {
		FF_OPERATOR_RET_SCALAR(&cv::Vec3d::dot, FF_APPLY_CLASS_FUNC, FF_UNWRAP_VEC3_AND_GET, Vec3);
	}
	static NAN_METHOD(Cross) {
		FF_OPERATOR(&cv::Vec3d::cross, FF_APPLY_CLASS_FUNC, FF_UNWRAP_VEC3_AND_GET, Vec3);
	}

	static NAN_METHOD(At) {
		FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), 2, "Vec3");
		cv::Vec3d vecSelf = Nan::ObjectWrap::Unwrap<Vec3>(info.This())->vec;
		info.GetReturnValue().Set(vecSelf[info[0]->Int32Value()]);
	}

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif