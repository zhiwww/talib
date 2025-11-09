#include <node_api.h>
#include "talib.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    return TALibWrapper::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)