#include "Mat.h"
#include "MatImgproc.h"
#include "MatCalib3d.h"
#include "MatBindings.h"

#ifdef HAVE_XIMGPROC
#include "MatXimgproc.h"
#endif // HAVE_XIMGPROC

Nan::Persistent<v8::FunctionTemplate> Mat::constructor;

NAN_MODULE_INIT(Mat::Init) {

  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Mat::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Mat").ToLocalChecked());
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("rows").ToLocalChecked(), Mat::GetRows);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("cols").ToLocalChecked(), Mat::GetCols);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("type").ToLocalChecked(), Mat::GetType);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("channels").ToLocalChecked(), Mat::GetChannels);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("dims").ToLocalChecked(), Mat::GetDims);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("depth").ToLocalChecked(), Mat::GetDepth);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("empty").ToLocalChecked(), Mat::GetIsEmpty);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("sizes").ToLocalChecked(), Mat::GetSizes);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("elemSize").ToLocalChecked(), Mat::GetElemSize);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("step").ToLocalChecked(), Mat::GetStep);

  Nan::SetMethod(ctor, "eye", Eye);
  Nan::SetPrototypeMethod(ctor, "flattenFloat", FlattenFloat);

  Nan::SetPrototypeMethod(ctor, "at", At);
  Nan::SetPrototypeMethod(ctor, "atRaw", AtRaw);
  Nan::SetPrototypeMethod(ctor, "set", Set);
  Nan::SetPrototypeMethod(ctor, "setTo", SetTo);
  Nan::SetPrototypeMethod(ctor, "setToAsync", SetToAsync);
  Nan::SetPrototypeMethod(ctor, "push_back", PushBack);
  Nan::SetPrototypeMethod(ctor, "push_backAsync", PushBackAsync);
  Nan::SetPrototypeMethod(ctor, "pushBack", PushBack);
  Nan::SetPrototypeMethod(ctor, "pushBackAsync", PushBackAsync);
  Nan::SetPrototypeMethod(ctor, "pop_back", PopBack);
  Nan::SetPrototypeMethod(ctor, "pop_backAsync", PopBackAsync);
  Nan::SetPrototypeMethod(ctor, "popBack", PopBack);
  Nan::SetPrototypeMethod(ctor, "popBackAsync", PopBackAsync);
  Nan::SetPrototypeMethod(ctor, "getData", GetData);
  Nan::SetPrototypeMethod(ctor, "getDataAsync", GetDataAsync);
  Nan::SetPrototypeMethod(ctor, "getDataAsArray", GetDataAsArray);
  Nan::SetPrototypeMethod(ctor, "getRegion", GetRegion);
  Nan::SetPrototypeMethod(ctor, "row", Row);
  Nan::SetPrototypeMethod(ctor, "copy", Copy);
  Nan::SetPrototypeMethod(ctor, "copyAsync", CopyAsync);
  Nan::SetPrototypeMethod(ctor, "copyTo", CopyTo);
  Nan::SetPrototypeMethod(ctor, "copyToAsync", CopyToAsync);
  Nan::SetPrototypeMethod(ctor, "convertTo", ConvertTo);
  Nan::SetPrototypeMethod(ctor, "convertToAsync", ConvertToAsync);
  Nan::SetPrototypeMethod(ctor, "norm", Norm);
  Nan::SetPrototypeMethod(ctor, "normalize", Normalize);
  Nan::SetPrototypeMethod(ctor, "normalizeAsync", NormalizeAsync);
  Nan::SetPrototypeMethod(ctor, "split", SplitChannels);
  Nan::SetPrototypeMethod(ctor, "splitAsync", SplitChannelsAsync);
  Nan::SetPrototypeMethod(ctor, "splitChannels", SplitChannels);
  Nan::SetPrototypeMethod(ctor, "splitChannelsAsync", SplitChannelsAsync);
  Nan::SetPrototypeMethod(ctor, "addWeighted", AddWeighted);
  Nan::SetPrototypeMethod(ctor, "addWeightedAsync", AddWeightedAsync);
  Nan::SetPrototypeMethod(ctor, "minMaxLoc", MinMaxLoc);
  Nan::SetPrototypeMethod(ctor, "minMaxLocAsync", MinMaxLocAsync);
  Nan::SetPrototypeMethod(ctor, "findNonZero", FindNonZero);
  Nan::SetPrototypeMethod(ctor, "findNonZeroAsync", FindNonZeroAsync);
  Nan::SetPrototypeMethod(ctor, "countNonZero", CountNonZero);
  Nan::SetPrototypeMethod(ctor, "countNonZeroAsync", CountNonZeroAsync);
  Nan::SetPrototypeMethod(ctor, "padToSquare", PadToSquare);
  Nan::SetPrototypeMethod(ctor, "padToSquareAsync", PadToSquareAsync);
  Nan::SetPrototypeMethod(ctor, "dct", Dct);
  Nan::SetPrototypeMethod(ctor, "dctAsync", DctAsync);
  Nan::SetPrototypeMethod(ctor, "idct", Idct);
  Nan::SetPrototypeMethod(ctor, "idctAsync", IdctAsync);
  Nan::SetPrototypeMethod(ctor, "dft", Dft);
  Nan::SetPrototypeMethod(ctor, "dftAsync", DftAsync);
  Nan::SetPrototypeMethod(ctor, "idft", Idft);
  Nan::SetPrototypeMethod(ctor, "idftAsync", IdftAsync);
  Nan::SetPrototypeMethod(ctor, "mulSpectrums", MulSpectrums);
  Nan::SetPrototypeMethod(ctor, "mulSpectrumsAsync", MulSpectrumsAsync);
  Nan::SetPrototypeMethod(ctor, "transform", Transform);
  Nan::SetPrototypeMethod(ctor, "transformAsync", TransformAsync);
  Nan::SetPrototypeMethod(ctor, "perspectiveTransform", PerspectiveTransform);
  Nan::SetPrototypeMethod(ctor, "perspectiveTransformAsync", PerspectiveTransformAsync);
  Nan::SetPrototypeMethod(ctor, "flip", Flip);
  Nan::SetPrototypeMethod(ctor, "flipAsync", FlipAsync);
  Nan::SetPrototypeMethod(ctor, "convertScaleAbs", ConvertScaleAbs);
  Nan::SetPrototypeMethod(ctor, "convertScaleAbsAsync", ConvertScaleAbsAsync);
  Nan::SetPrototypeMethod(ctor, "sum", Sum);
  Nan::SetPrototypeMethod(ctor, "sumAsync", SumAsync);
  Nan::SetPrototypeMethod(ctor, "goodFeaturesToTrack", GoodFeaturesToTrack);
  Nan::SetPrototypeMethod(ctor, "goodFeaturesToTrackAsync", GoodFeaturesToTrackAsync);
  Nan::SetPrototypeMethod(ctor, "mean", Mean);
  Nan::SetPrototypeMethod(ctor, "meanAsync", MeanAsync);
  Nan::SetPrototypeMethod(ctor, "meanStdDev", MeanStdDev);
  Nan::SetPrototypeMethod(ctor, "meanStdDevAsync", MeanStdDevAsync);
  Nan::SetPrototypeMethod(ctor, "copyMakeBorder", CopyMakeBorder);
  Nan::SetPrototypeMethod(ctor, "copyMakeBorderAsync", CopyMakeBorderAsync);
  Nan::SetPrototypeMethod(ctor, "reduce", Reduce);
  Nan::SetPrototypeMethod(ctor, "reduceAsync", ReduceAsync);
  Nan::SetPrototypeMethod(ctor, "eigen", Eigen);
  Nan::SetPrototypeMethod(ctor, "eigenAsync", EigenAsync);
  Nan::SetPrototypeMethod(ctor, "solve", Solve);
  Nan::SetPrototypeMethod(ctor, "solveAsync", SolveAsync);

#if CV_VERSION_MINOR > 1
  Nan::SetPrototypeMethod(ctor, "rotate", Rotate);
  Nan::SetPrototypeMethod(ctor, "rotateAsync", RotateAsync);
#endif

  Nan::SetPrototypeMethod(ctor, "release", Release);


  FF_PROTO_SET_MAT_OPERATIONS(ctor);

  MatImgproc::Init(ctor);
  MatCalib3d::Init(ctor);
  #ifdef HAVE_XIMGPROC
  MatXimgproc::Init(ctor);
  #endif // HAVE_XIMGPROC

  Nan::Set(target,Nan::New("Mat").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(Mat::New) {
	FF::TryCatch tryCatch("Mat::New");
	FF_ASSERT_CONSTRUCT_CALL();
  Mat* self = new Mat();
  /* from channels */
  if (info.Length() == 1 && info[0]->IsArray()) {
    v8::Local<v8::Array> jsChannelMats = v8::Local<v8::Array>::Cast(info[0]);
    std::vector<cv::Mat> channels;
    for (uint i = 0; i < jsChannelMats->Length(); i++) {
      v8::Local<v8::Object> jsChannelMat = FF_CAST_OBJ(Nan::Get(jsChannelMats, i).ToLocalChecked());
	  if (!Nan::New(Mat::constructor)->HasInstance(jsChannelMat)) {
		return tryCatch.throwError("expected channel " + std::to_string(i) + " to be an instance of Mat");
	  }
      cv::Mat channelMat = Mat::Converter::unwrapUnchecked(jsChannelMat);
      channels.push_back(channelMat);
      if (i > 0) {
		if (channels.at(i - 1).rows != channelMat.rows) {
			return tryCatch.throwError("Mat::New - rows mismatch "
				+ std::to_string(channels.at(i - 1).rows) + ", have " + std::to_string(channelMat.rows)
				+ " at channel " + std::to_string(i));
		}
		if (channels.at(i - 1).cols != channelMat.cols) {
			return tryCatch.throwError("Mat::New - cols mismatch "
				+ std::to_string(channels.at(i - 1).cols) + ", have " + std::to_string(channelMat.rows)
				+ " at channel " + std::to_string(i));
		}
      }
    }
    cv::Mat mat;
    cv::merge(channels, mat);
    self->setNativeObject(mat);
  }
  /* data array, type */
  else if (info.Length() == 2 && info[0]->IsArray() && info[1]->IsInt32()) {
    v8::Local<v8::Array> rowArray = v8::Local<v8::Array>::Cast(info[0]);
    int type = info[1]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value();

    long numCols = -1;
    for (uint i = 0; i < rowArray->Length(); i++) {
      if (!Nan::Get(rowArray, i).ToLocalChecked()->IsArray()) {
        return tryCatch.throwError("Mat::New - Column should be an array, at column: " + std::to_string(i));
      }
      v8::Local<v8::Array> colArray = v8::Local<v8::Array>::Cast(Nan::Get(rowArray, i).ToLocalChecked());
      if (numCols != -1 && numCols != colArray->Length()) {
        return tryCatch.throwError("Mat::New - Mat cols must be of uniform length, at column: " + std::to_string(i));
      }
      numCols = colArray->Length();
    }

    cv::Mat mat = cv::Mat(rowArray->Length(), numCols, type);
    FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray, type, FF_MAT_FROM_JS_ARRAY, FF::matPut);
    self->setNativeObject(mat);
  }
  /* row, col, type */
  else if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsInt32()) {
    int type = info[2]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value();
    cv::Mat mat(info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), info[1]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), type);
    /* fill vector */
    // TODO by Vec
    if (info[3]->IsArray()) {
      v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(info[3]);
      if (mat.channels() != (long)vec->Length()) {
        return tryCatch.throwError(
          std::string("Mat::New - number of channels (") + std::to_string(mat.channels())
          + std::string(") do not match fill vector length ") + std::to_string(vec->Length())
        );
      }
      FF_MAT_APPLY_TYPED_OPERATOR(mat, vec, type, FF_MAT_FILL, FF::matPut);
    }
    if (info[3]->IsNumber()) {
      FF_MAT_APPLY_TYPED_OPERATOR(mat, info[3], type, FF_MAT_FILL, FF::matPut);
    }
    self->setNativeObject(mat);
  }
  /* raw data, row, col, type */
  else if (info.Length() == 4 && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsInt32()) {
    int type = info[3]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value();
    char *data = static_cast<char *>(node::Buffer::Data(info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked()));
    cv::Mat mat(info[1]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), info[2]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), type);
    size_t size = mat.rows * mat.cols * mat.elemSize();
    memcpy(mat.data, data, size);
    self->setNativeObject(mat);
  }
  self->Wrap(info.Holder());

  // if ExternalMemTracking is disabled, the following instruction will be a no op
    // notes: I *think* New should be called in JS thread where cv::mat has been created async,
    // so a good place to rationalise memory
  ExternalMemTracking::onMatAllocated();

  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Mat::Eye) {
	FF::TryCatch tryCatch("Mat::Eye");
	int rows, cols, type;
	if (
		FF::IntConverter::arg(0, &rows, info) ||
		FF::IntConverter::arg(1, &cols, info) ||
		FF::IntConverter::arg(2, &type, info)
	) {
		return tryCatch.reThrow();
	}
	info.GetReturnValue().Set(Mat::Converter::wrap(cv::Mat::eye(cv::Size(cols, rows), type)));
}

NAN_METHOD(Mat::FlattenFloat) {
	FF::TryCatch tryCatch("Mat::FlattenFloat");
	int rows, cols;
	if (
		FF::IntConverter::arg(0, &rows, info) ||
		FF::IntConverter::arg(1, &cols, info)
		) {
		return tryCatch.reThrow();
	}

	cv::Mat matSelf = Mat::unwrapSelf(info);
	cv::Mat mat2D(rows, cols, CV_32F, matSelf.ptr<float>());
	info.GetReturnValue().Set(Mat::Converter::wrap(mat2D));
}

NAN_METHOD(Mat::At) {
	FF::TryCatch tryCatch("Mat::At");

  cv::Mat matSelf = Mat::unwrapSelf(info);
  v8::Local<v8::Value> val;
  v8::Local<v8::Value> jsVal;

  if (FF_IS_ARRAY(info[0])) {
    if ((long)v8::Local<v8::Array>::Cast(info[0])->Length() != matSelf.dims) {
		tryCatch.throwError("expected array length to be equal to the dims");
    }
    FF_MAT_APPLY_TYPED_OPERATOR(matSelf, val, matSelf.type(), FF_MAT_AT_ARRAY, FF::matGet);
  } else {
    FF_ASSERT_INDEX_RANGE(info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), matSelf.size[0] - 1, "Mat::At row");
    FF_ASSERT_INDEX_RANGE(info[1]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), matSelf.size[1] - 1, "Mat::At col");
    FF_MAT_APPLY_TYPED_OPERATOR(matSelf, val, matSelf.type(), FF_MAT_AT, FF::matGet);
  }

  if (val->IsArray()) {
    v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(val);
    v8::Local<v8::Value> jsVec;
    if (vec->Length() == 2) {
      jsVec = Vec2::Converter::wrap(cv::Vec2d(FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 0).ToLocalChecked()), FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 1).ToLocalChecked())));
    }
    else if (vec->Length() == 3) {
      jsVec = Vec3::Converter::wrap(cv::Vec3d(FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 0).ToLocalChecked()), FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 1).ToLocalChecked()), FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 2).ToLocalChecked())));
    }
    else {
      jsVec = Vec4::Converter::wrap(cv::Vec4d(FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 0).ToLocalChecked()), FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 1).ToLocalChecked()), FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 2).ToLocalChecked()), FF::DoubleConverter::unwrapUnchecked(Nan::Get(vec, 3).ToLocalChecked())));
    }
    jsVal = jsVec;
  }
  else {
    jsVal = v8::Local<v8::Value>::Cast(val);
  }
  info.GetReturnValue().Set(jsVal);
}

NAN_METHOD(Mat::AtRaw) {
	FF::TryCatch tryCatch("Mat::AtRaw");
  cv::Mat matSelf = Mat::unwrapSelf(info);
  FF_ASSERT_INDEX_RANGE(info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), matSelf.size[0] - 1, "Mat::At row");
  FF_ASSERT_INDEX_RANGE(info[1]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), matSelf.size[1] - 1, "Mat::At col");
  v8::Local<v8::Value> val;
  FF_MAT_APPLY_TYPED_OPERATOR(matSelf, val, matSelf.type(), FF_MAT_AT, FF::matGet);
  info.GetReturnValue().Set(val);
}

NAN_METHOD(Mat::Set) {
	FF::TryCatch tryCatch("Mat::Set");
  cv::Mat matSelf = Mat::unwrapSelf(info);
  FF_ASSERT_INDEX_RANGE(info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), matSelf.size[0] - 1, "Mat::At row");
  FF_ASSERT_INDEX_RANGE(info[1]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), matSelf.size[1] - 1, "Mat::At col");

  int cn = matSelf.channels();
  if (info[2]->IsArray()) {
    v8::Local<v8::Array> vec = v8::Local<v8::Array>::Cast(info[2]);
    FF_ASSERT_CHANNELS(cn, (long)vec->Length(), "Mat::Set");
    FF_MAT_APPLY_TYPED_OPERATOR(matSelf, vec, matSelf.type(), FF_MAT_SET, FF::matPut);
  }
  else if (Vec2::hasInstance(info[2])) {
    FF_ASSERT_CHANNELS(cn, 2, "Mat::Set");
    FF_MAT_APPLY_TYPED_OPERATOR(matSelf, FF::vecToJsArr<2>(Vec2::Converter::unwrapUnchecked(info[2])), matSelf.type(), FF_MAT_SET, FF::matPut);
  }
  else if (Vec3::hasInstance(info[2])) {
    FF_ASSERT_CHANNELS(cn, 3, "Mat::Set");
    FF_MAT_APPLY_TYPED_OPERATOR(matSelf, FF::vecToJsArr<3>(Vec3::Converter::unwrapUnchecked(info[2])), matSelf.type(), FF_MAT_SET, FF::matPut);
  }
  else if (Vec4::hasInstance(info[2])) {
    FF_ASSERT_CHANNELS(cn, 4, "Mat::Set");
    FF_MAT_APPLY_TYPED_OPERATOR(matSelf, FF::vecToJsArr<4>(Vec4::Converter::unwrapUnchecked(info[2])), matSelf.type(), FF_MAT_SET, FF::matPut);
  }
  else if (info[2]->IsNumber()) {
    FF_MAT_APPLY_TYPED_OPERATOR(matSelf, info[2], matSelf.type(), FF_MAT_SET, FF::matPut);
  }
  else {
    return tryCatch.throwError("unexpected argument 2");
  }
}

NAN_METHOD(Mat::SetTo) {
  FF::SyncBinding(
    std::make_shared<MatBindings::SetToWorker>(Mat::unwrapSelf(info)),
    "Mat::SetTo",
    info
  );
}

NAN_METHOD(Mat::SetToAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::SetToWorker>(Mat::unwrapSelf(info)),
    "Mat::SetToAsync",
    info
  );
}

NAN_METHOD(Mat::GetDataAsArray) {
	FF::TryCatch tryCatch("Mat::GetDataAsArray");
  cv::Mat mat = Mat::unwrapSelf(info);
  v8::Local<v8::Array> rowArray = Nan::New<v8::Array>(mat.size[0]);
  if (mat.dims > 2) { // 3D
    FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray, mat.type(), FF_JS_ARRAY_FROM_MAT_3D, FF::matGet);
  } else { // 2D
    FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray, mat.type(), FF_JS_ARRAY_FROM_MAT, FF::matGet);
  }
  info.GetReturnValue().Set(rowArray);
}

NAN_METHOD(Mat::GetRegion) {
	FF::TryCatch tryCatch("Mat::GetRegion");
	cv::Rect2d rect;
	if (Rect::Converter::arg(0, &rect, info)) {
		return tryCatch.reThrow();
	}
	info.GetReturnValue().Set(Mat::Converter::wrap(Mat::unwrapSelf(info)(rect)));
}

NAN_METHOD(Mat::Norm) {
	FF::TryCatch tryCatch("Mat::Norm");
  bool withSrc2 = FF::hasArg(info, 0) && Mat::hasInstance(info[0]);
  uint i = withSrc2 ? 1 : 0;
  double norm;

  // optional args
  bool hasOptArgsObj = FF::isArgObject(info, i);
  v8::Local<v8::Object> optArgs = hasOptArgsObj ? info[i]->ToObject(Nan::GetCurrentContext()).ToLocalChecked() : Nan::New<v8::Object>();

  uint normType = cv::NORM_L2;
  cv::Mat mask = cv::noArray().getMat();

  if (
	  (hasOptArgsObj && (
		FF::UintConverter::optProp(&normType, "normType", optArgs) ||
		Mat::Converter::optProp(&mask, "mask", optArgs)
		)) || (
		FF::UintConverter::optArg(i, &normType, info) ||
		Mat::Converter::optArg(i + 1, &mask, info)
		)
	  ) {
	  return tryCatch.reThrow();
  }

  if (withSrc2) {
	cv::Mat src2;
	if (Mat::Converter::arg(0, &src2, info)) {
		return tryCatch.reThrow();
	}
    norm = cv::norm(Mat::unwrapSelf(info), src2, (int)normType, mask);
  }
  else {
    norm = cv::norm(Mat::unwrapSelf(info), (int)normType, mask);
  }
  info.GetReturnValue().Set(norm);
}

NAN_METHOD(Mat::Normalize) {
	FF::SyncBinding(
		std::make_shared<MatBindings::NormalizeWorker>(Mat::unwrapSelf(info)),
		"Mat::Normalize",
		info
	);
}

NAN_METHOD(Mat::NormalizeAsync) {
	FF::AsyncBinding(
		std::make_shared<MatBindings::NormalizeWorker>(Mat::unwrapSelf(info)),
		"Mat::NormalizeAsync",
		info
	);
}

NAN_METHOD(Mat::Row) {
	FF::TryCatch tryCatch("Mat::Row");
  if (!info[0]->IsNumber()) {
    return tryCatch.throwError("usage: row(int r)");
  }
  int r = (int)info[0]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
  cv::Mat mat = Mat::unwrapSelf(info);
  v8::Local<v8::Array> row = Nan::New<v8::Array>(mat.cols);
  try {
    if (mat.type() == CV_32FC1) {
      for (int c = 0;  c < mat.cols; c++) {
		Nan::Set(row, c, Nan::New(mat.at<float>(r, c)));
      }
    } else if (mat.type() == CV_8UC1) {
      for (int c = 0;  c < mat.cols; c++) {
        Nan::Set(row, c, Nan::New((uint)mat.at<uchar>(r, c)));
      }
    } else if (mat.type() == CV_8UC3) {
      for (int c = 0;  c < mat.cols; c++) {
        cv::Vec3b vec = mat.at<cv::Vec3b>(r, c);
        v8::Local<v8::Array> jsVec = Nan::New<v8::Array>(3);
        for (int i = 0; i < 3; i++) {
			Nan::Set(jsVec, i, Nan::New(vec[i]));
        }
        Nan::Set(row, c, jsVec);
      }
    } else {
      return tryCatch.throwError("not implemented yet - mat type:" + std::to_string(mat.type()));
    }
  } catch(std::exception &e) {
    return tryCatch.throwError(e.what());
  } catch(...) {
    return tryCatch.throwError("... Exception");
  }
  info.GetReturnValue().Set(row);
}

NAN_METHOD(Mat::Release) {
    // must get pointer to the original; else we are just getting a COPY and then releasing that!
    Mat::unwrapThis(info)->self.release();
}

NAN_METHOD(Mat::PushBack) {
  FF::SyncBinding(
    std::make_shared<MatBindings::PushBackWorker>(Mat::unwrapSelf(info)),
    "Mat::PushBack",
    info
  );
}

NAN_METHOD(Mat::PushBackAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::PushBackWorker>(Mat::unwrapSelf(info)),
    "Mat::PushBackAsync",
    info
  );
}

NAN_METHOD(Mat::PopBack) {
  FF::SyncBinding(
    std::make_shared<MatBindings::PopBackWorker>(Mat::unwrapSelf(info)),
    "Mat::PopBack",
    info
  );
}

NAN_METHOD(Mat::PopBackAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::PopBackWorker>(Mat::unwrapSelf(info)),
    "Mat::PopBackAsync",
    info
  );
}

NAN_METHOD(Mat::GetData) {
  FF::SyncBinding(
    std::make_shared<MatBindings::GetDataWorker>(Mat::unwrapSelf(info)),
    "Mat::GetData",
    info
  );
}

NAN_METHOD(Mat::GetDataAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::GetDataWorker>(Mat::unwrapSelf(info)),
    "Mat::GetDataAsync",
    info
  );
}

NAN_METHOD(Mat::Copy) {
  FF::SyncBinding(
    std::make_shared<MatBindings::CopyWorker>(Mat::unwrapSelf(info)),
    "Mat::Copy",
    info
  );
}

NAN_METHOD(Mat::CopyAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::CopyWorker>(Mat::unwrapSelf(info)),
    "Mat::CopyAsync",
    info
  );
}

NAN_METHOD(Mat::CopyTo) {
  FF::SyncBinding(
    std::make_shared<MatBindings::CopyToWorker>(Mat::unwrapSelf(info)),
    "Mat::CopyTo",
    info
  );
}

NAN_METHOD(Mat::CopyToAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::CopyToWorker>(Mat::unwrapSelf(info)),
    "Mat::CopyToAsync",
    info
  );
}

NAN_METHOD(Mat::ConvertTo) {
  FF::SyncBinding(
    std::make_shared<MatBindings::ConvertToWorker>(Mat::unwrapSelf(info)),
    "Mat::ConvertTo",
    info
  );
}

NAN_METHOD(Mat::ConvertToAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::ConvertToWorker>(Mat::unwrapSelf(info)),
    "Mat::ConvertToAsync",
    info
  );
}

NAN_METHOD(Mat::SplitChannels) {
  FF::SyncBinding(
    std::make_shared<MatBindings::SplitChannelsWorker>(Mat::unwrapSelf(info)),
    "Mat::SplitChannels",
    info
  );
}

NAN_METHOD(Mat::SplitChannelsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::SplitChannelsWorker>(Mat::unwrapSelf(info)),
    "Mat::SplitChannelsAsync",
    info
  );
}

NAN_METHOD(Mat::AddWeighted) {
  FF::SyncBinding(
    std::make_shared<MatBindings::AddWeightedWorker>(Mat::unwrapSelf(info)),
    "Mat::AddWeighted",
    info
  );
}

NAN_METHOD(Mat::AddWeightedAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::AddWeightedWorker>(Mat::unwrapSelf(info)),
    "Mat::AddWeightedAsync",
    info
  );
}

NAN_METHOD(Mat::MinMaxLoc) {
  FF::SyncBinding(
    std::make_shared<MatBindings::MinMaxLocWorker>(Mat::unwrapSelf(info)),
    "Mat::MinMaxLoc",
    info
  );
}

NAN_METHOD(Mat::MinMaxLocAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::MinMaxLocWorker>(Mat::unwrapSelf(info)),
    "Mat::MinMaxLocAsync",
    info
  );
}

NAN_METHOD(Mat::FindNonZero) {
  FF::SyncBinding(
    std::make_shared<MatBindings::FindNonZeroWorker>(Mat::unwrapSelf(info)),
    "Mat::FindNonZero",
    info
  );
}

NAN_METHOD(Mat::FindNonZeroAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::FindNonZeroWorker>(Mat::unwrapSelf(info)),
    "Mat::FindNonZeroAsync",
    info
  );
}

NAN_METHOD(Mat::CountNonZero) {
  FF::SyncBinding(
    std::make_shared<MatBindings::CountNonZeroWorker>(Mat::unwrapSelf(info)),
    "Mat::CountNonZero",
    info
  );
}

NAN_METHOD(Mat::CountNonZeroAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::CountNonZeroWorker>(Mat::unwrapSelf(info)),
    "Mat::CountNonZeroAsync",
    info
  );
}

NAN_METHOD(Mat::PadToSquare) {
  FF::SyncBinding(
    std::make_shared<MatBindings::PadToSquareWorker>(Mat::unwrapSelf(info)),
    "Mat::PadToSquare",
    info
  );
}

NAN_METHOD(Mat::PadToSquareAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::PadToSquareWorker>(Mat::unwrapSelf(info)),
    "Mat::PadToSquareAsync",
    info
  );
}

NAN_METHOD(Mat::Dct) {
  FF::SyncBinding(
    std::make_shared<MatBindings::DCTWorker>(Mat::unwrapSelf(info)),
    "Mat::Dct",
    info
  );
}

NAN_METHOD(Mat::DctAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::DCTWorker>(Mat::unwrapSelf(info)),
    "Mat::DctAsync",
    info
  );
}

NAN_METHOD(Mat::Idct) {
  FF::SyncBinding(
    std::make_shared<MatBindings::DCTWorker>(Mat::unwrapSelf(info)),
    "Mat::Idct",
    info
  );
}

NAN_METHOD(Mat::IdctAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::DCTWorker>(Mat::unwrapSelf(info)),
    "Mat::IdctAsync",
    info
  );
}

NAN_METHOD(Mat::Dft) {
  FF::SyncBinding(
    std::make_shared<MatBindings::DFTWorker>(Mat::unwrapSelf(info)),
    "Mat::Dft",
    info
  );
}

NAN_METHOD(Mat::DftAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::DFTWorker>(Mat::unwrapSelf(info)),
    "Mat::DftAsync",
    info
  );
}

NAN_METHOD(Mat::Idft) {
  FF::SyncBinding(
    std::make_shared<MatBindings::DFTWorker>(Mat::unwrapSelf(info)),
    "Mat::Idft",
    info
  );
}

NAN_METHOD(Mat::IdftAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::DFTWorker>(Mat::unwrapSelf(info)),
    "Mat::IdftAsync",
    info
  );
}

NAN_METHOD(Mat::MulSpectrums) {
  FF::SyncBinding(
    std::make_shared<MatBindings::MulSpectrumsWorker>(Mat::unwrapSelf(info)),
    "Mat::MulSpectrums",
    info
  );
}

NAN_METHOD(Mat::MulSpectrumsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::MulSpectrumsWorker>(Mat::unwrapSelf(info)),
    "Mat::MulSpectrumsAsync",
    info
  );
}

NAN_METHOD(Mat::Transform) {
  FF::SyncBinding(
    std::make_shared<MatBindings::TransformWorker>(Mat::unwrapSelf(info)),
    "Mat::Transform",
    info
  );
}

NAN_METHOD(Mat::TransformAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::TransformWorker>(Mat::unwrapSelf(info)),
    "Mat::TransformAsync",
    info
  );
}

NAN_METHOD(Mat::PerspectiveTransform) {
  FF::SyncBinding(
    std::make_shared<MatBindings::PerspectiveTransformWorker>(Mat::unwrapSelf(info)),
    "Mat::PerspectiveTransform",
    info
  );
}

NAN_METHOD(Mat::PerspectiveTransformAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::PerspectiveTransformWorker>(Mat::unwrapSelf(info)),
    "Mat::PerspectiveTransformAsync",
    info
  );
}

NAN_METHOD(Mat::Flip) {
  FF::SyncBinding(
    std::make_shared<MatBindings::FlipWorker>(Mat::unwrapSelf(info)),
    "Mat::Flip",
    info
  );
}

NAN_METHOD(Mat::FlipAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::FlipWorker>(Mat::unwrapSelf(info)),
    "Mat::FlipAsync",
    info
  );
}

NAN_METHOD(Mat::Sum) {
  FF::SyncBinding(
    std::make_shared<MatBindings::SumWorker>(Mat::unwrapSelf(info)),
    "Mat::Sum",
    info
  );
}

NAN_METHOD(Mat::SumAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::SumWorker>(Mat::unwrapSelf(info)),
    "Mat::SumAsync",
    info
  );
}

NAN_METHOD(Mat::ConvertScaleAbs) {
  FF::SyncBinding(
    std::make_shared<MatBindings::ConvertScaleAbsWorker>(Mat::unwrapSelf(info)),
    "Mat::ConvertScaleAbs",
    info
  );
}

NAN_METHOD(Mat::ConvertScaleAbsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::ConvertScaleAbsWorker>(Mat::unwrapSelf(info)),
    "Mat::ConvertScaleAbsAsync",
    info
  );
}

NAN_METHOD(Mat::GoodFeaturesToTrack) {
  FF::SyncBinding(
    std::make_shared<MatBindings::GoodFeaturesToTrackWorker>(Mat::unwrapSelf(info)),
    "Mat::GoodFeaturesToTrack",
    info
  );
}

NAN_METHOD(Mat::GoodFeaturesToTrackAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::GoodFeaturesToTrackWorker>(Mat::unwrapSelf(info)),
    "Mat::GoodFeaturesToTrackAsync",
    info
  );
}

NAN_METHOD(Mat::Mean) {
	FF::SyncBinding(
		std::make_shared<MatBindings::MeanWorker>(Mat::unwrapSelf(info)),
		"Mat::Mean",
		info
	);
}

NAN_METHOD(Mat::MeanAsync) {
	FF::AsyncBinding(
		std::make_shared<MatBindings::MeanWorker>(Mat::unwrapSelf(info)),
		"Mat::MeanAsync",
		info
	);
}

NAN_METHOD(Mat::MeanStdDev) {
  FF::SyncBinding(
    std::make_shared<MatBindings::MeanStdDevWorker>(Mat::unwrapSelf(info)),
    "Mat::MeanStdDev",
    info
  );
}

NAN_METHOD(Mat::MeanStdDevAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::MeanStdDevWorker>(Mat::unwrapSelf(info)),
    "Mat::MeanStdDevAsync",
    info
  );
}

NAN_METHOD(Mat::CopyMakeBorder) {
	FF::SyncBinding(
		std::make_shared<MatBindings::CopyMakeBorderWorker>(Mat::unwrapSelf(info)),
		"Mat::CopyMakeBorder",
		info
	);
}

NAN_METHOD(Mat::CopyMakeBorderAsync) {
	FF::AsyncBinding(
		std::make_shared<MatBindings::CopyMakeBorderWorker>(Mat::unwrapSelf(info)),
		"Mat::CopyMakeBorderAsync",
		info
	);
}

NAN_METHOD(Mat::Reduce) {
	FF::SyncBinding(
		std::make_shared<MatBindings::ReduceWorker>(Mat::unwrapSelf(info)),
		"Mat::Reduce",
		info
	);
}

NAN_METHOD(Mat::ReduceAsync) {
	FF::AsyncBinding(
		std::make_shared<MatBindings::ReduceWorker>(Mat::unwrapSelf(info)),
		"Mat::ReduceAsync",
		info
	);
}

NAN_METHOD(Mat::Eigen) {
  FF::SyncBinding(
    std::make_shared<MatBindings::EigenWorker>(Mat::unwrapSelf(info)),
    "Mat::Eigen",
    info
  );
}

NAN_METHOD(Mat::EigenAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::EigenWorker>(Mat::unwrapSelf(info)),
    "Mat::EigenAsync",
    info
  );
}

NAN_METHOD(Mat::Solve) {
  FF::SyncBinding(
    std::make_shared<MatBindings::SolveWorker>(Mat::unwrapSelf(info)),
    "Mat::Solve",
    info
  );
}

NAN_METHOD(Mat::SolveAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::SolveWorker>(Mat::unwrapSelf(info)),
    "Mat::SolveAsync",
    info
  );
}

#if CV_VERSION_MINOR > 1
NAN_METHOD(Mat::Rotate) {
  FF::SyncBinding(
    std::make_shared<MatBindings::RotateWorker>(Mat::unwrapSelf(info)),
    "Mat::Rotate",
    info
  );
}

NAN_METHOD(Mat::RotateAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::RotateWorker>(Mat::unwrapSelf(info)),
    "Mat::RotateAsync",
    info
  );
}
#endif
