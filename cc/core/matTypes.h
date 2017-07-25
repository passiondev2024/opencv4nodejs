#include <nan.h>
#include <opencv2/core.hpp>

#define FF_TYPE(C) \
  matTypesModule->Set(Nan::New<v8::String>(#C).ToLocalChecked(), Nan::New<v8::Integer>(C));

static void initMatTypes(v8::Local<v8::Object> matTypesModule) {
	FF_TYPE(CV_8U);
	FF_TYPE(CV_8S);
	FF_TYPE(CV_16U);
	FF_TYPE(CV_16S);
	FF_TYPE(CV_32S);
	FF_TYPE(CV_32F);
	FF_TYPE(CV_64F);

	FF_TYPE(CV_8UC1);
	FF_TYPE(CV_8UC2);
	FF_TYPE(CV_8UC3);
	FF_TYPE(CV_8UC4);

	FF_TYPE(CV_8SC1);
	FF_TYPE(CV_8SC2);
	FF_TYPE(CV_8SC3);
	FF_TYPE(CV_8SC4);

	FF_TYPE(CV_16UC1);
	FF_TYPE(CV_16UC2);
	FF_TYPE(CV_16UC3);
	FF_TYPE(CV_16UC4);

	FF_TYPE(CV_16SC1);
	FF_TYPE(CV_16SC2);
	FF_TYPE(CV_16SC3);
	FF_TYPE(CV_16SC4);

	FF_TYPE(CV_32SC1);
	FF_TYPE(CV_32SC2);
	FF_TYPE(CV_32SC3);
	FF_TYPE(CV_32SC4);

	FF_TYPE(CV_32FC1);
	FF_TYPE(CV_32FC2);
	FF_TYPE(CV_32FC3);
	FF_TYPE(CV_32FC4);

	FF_TYPE(CV_64FC1);
	FF_TYPE(CV_64FC2);
	FF_TYPE(CV_64FC3);
	FF_TYPE(CV_64FC4);
}
