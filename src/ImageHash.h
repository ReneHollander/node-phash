#ifndef IMAGE_HASH_H
#define IMAGE_HASH_H

#include <string>
#include <nan.h>
#include "pHash.h"

#include "Helper.h"

using namespace v8;
using namespace std;

void InitImageHash(Handle<Object> exports);
NAN_METHOD(ImageHashSync);
NAN_METHOD(ImageHashAsync);

class ImageHashWorker : public NanAsyncWorker {
  public:
    ImageHashWorker(NanCallback *callback, string filename) : NanAsyncWorker(callback), filename(filename) {}
    ~ImageHashWorker() {}

    void Execute();
    void HandleOKCallback();

  private:
    string filename;

    string errmsg;
    ulong64 returnHash;
};

#endif
