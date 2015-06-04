#include "VideoHash.h"

NAN_METHOD(VideoHash) {
	NanScope();

	string fileName(*NanAsciiString(args[0]));
	NanCallback *callback = new NanCallback(args[1].As<Function>());

	NanAsyncQueueWorker(new VideoHashWorker(callback, fileName));
	NanReturnUndefined();
}

void VideoHashWorker::Execute() {
	try {
		if (!fileExists(filename)) {
			SetErrorMessage("Invalid file");
			return;
		}
		hashArray = ph_dct_videohash(filename.c_str(), hashArrayLength);
		if (hashArrayLength <= 0 && hashArray == NULL) {
			SetErrorMessage("error calculating video hash");
		}
	} catch (exception& e) {
		SetErrorMessage(e.what());
	}
}

void VideoHashWorker::HandleOKCallback() {
	NanScope();
	Local<Array> array = NanNew<Array>(hashArrayLength);
	for (int i = 0; i < hashArrayLength; i++) {
		ulong64 curr = *(hashArray + i);
		uint32_t x = (uint32_t)((curr & 0xFFFFFFFF00000000) >> 32);
		uint32_t y = (uint32_t)(curr & 0xFFFFFFFF);

		Local<Object> obj = NanNew<Object>();
		obj->Set(NanNew<String>("lower"), NanNew<Number>(x));
		obj->Set(NanNew<String>("higher"), NanNew<Number>(y));
		array->Set(i, obj);
	}
	Local<Value> argv[] = {
		NanUndefined(),
		array
	};
	callback->Call(2, argv);
}

void InitVideoHash(Handle<Object> exports) {
	NanScope();
	exports->Set(NanNew<String>("videoHash"), NanNew<FunctionTemplate>(VideoHash)->GetFunction());
}
