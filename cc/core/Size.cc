#include "Size.h"

Nan::Persistent<v8::FunctionTemplate> Size::constructor;

NAN_MODULE_INIT(Size::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Size::New);
	Size::constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("Size").ToLocalChecked());
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("width").ToLocalChecked(), Size::GetWidth);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("height").ToLocalChecked(), Size::GetHeight);

  Nan::Set(target,Nan::New("Size").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(Size::New) {
	FF_ASSERT_CONSTRUCT_CALL(Size);
	Size* self = new Size();
	if (info.Length() > 0) {
		if (info.Length() < 2) {
			return Nan::ThrowError("Size::New - expected arguments width, height");
		}
		double width = info[0]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
		double height = info[1]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
		self->size = cv::Size2d(width, height);
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}
