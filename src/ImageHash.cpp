#include "ImageHash.h"

NAN_METHOD(ImageHash) {
	NanScope();

	string fileName(*NanAsciiString(args[0]));
	NanCallback *callback = new NanCallback(args[1].As<Function>());

	NanAsyncQueueWorker(new ImageHashWorker(callback, fileName));
	NanReturnUndefined();
}

void ImageHashWorker::Execute() {
	try {
		if (!fileExists(filename)) {
			SetErrorMessage("Invalid file");
			return;
		}
		int success = ph_dct_imagehash(filename.c_str(), returnHash);
		if (success < 0) {
			SetErrorMessage("Error computing image hash");
			return;
		}
	} catch (exception& e) {
		SetErrorMessage(e.what());
	}
}

void ImageHashWorker::HandleOKCallback() {
	NanScope();

	uint32_t x = (uint32_t)((returnHash & 0xFFFFFFFF00000000) >> 32);
	uint32_t y = (uint32_t)(returnHash & 0xFFFFFFFF);

	Local<Value> argv[] = {
		NanUndefined(),
		NanNew<Number>(x),
		NanNew<Number>(y)
	};

	callback->Call(3, argv);
}

void InitImageHash(Handle<Object> exports) {
	NanScope();
	exports->Set(NanNew<String>("imageHash"), NanNew<FunctionTemplate>(ImageHash)->GetFunction());
}
