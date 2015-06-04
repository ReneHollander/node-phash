#ifndef VIDEO_HASH_H
#define VIDEO_HASH_H

#include <string>
#include <nan.h>
#include "pHash.h"

#include "Helper.h"

using namespace v8;
using namespace std;

void InitVideoHash(Handle<Object> exports);
NAN_METHOD(VideoHash);

class VideoHashWorker : public NanAsyncWorker {
  public:
    VideoHashWorker(NanCallback *callback, string filename) : NanAsyncWorker(callback), filename(filename) {}
    ~VideoHashWorker() {}

    void Execute();
    void HandleOKCallback();

  private:
    string filename;

    int hashArrayLength;
    ulong64* hashArray;
};

#endif
