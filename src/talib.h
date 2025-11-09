#ifndef TALIB_WRAPPER_H
#define TALIB_WRAPPER_H

#include <napi.h>
#include <vector>
#include <memory>
#include "ta_libc.h"

class TALibWrapper : public Napi::ObjectWrap<TALibWrapper> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    TALibWrapper(const Napi::CallbackInfo& info);

    // Moving Averages
    Napi::Value SMA(const Napi::CallbackInfo& info);
    Napi::Value EMA(const Napi::CallbackInfo& info);
    Napi::Value MA(const Napi::CallbackInfo& info);

    // Momentum Indicators
    Napi::Value RSI(const Napi::CallbackInfo& info);
    Napi::Value MACD(const Napi::CallbackInfo& info);

    // Volatility Indicators
    Napi::Value ATR(const Napi::CallbackInfo& info);
    Napi::Value BBANDS(const Napi::CallbackInfo& info);

    // Volume Indicators
    Napi::Value AD(const Napi::CallbackInfo& info);
    Napi::Value OBV(const Napi::CallbackInfo& info);

private:
    static Napi::FunctionReference constructor;

    // Helper methods
    std::vector<double> JSArrayToVector(const Napi::Array& arr);
    Napi::Array VectorToJSArray(Napi::Env env, const std::vector<double>& vec);
    Napi::Value HandleResult(Napi::Env env, TA_RetCode retCode, const std::vector<double>& result);

    // TA-Lib initialization
    static bool taLibInitialized;
    static void InitializeTALib();
};

#endif // TALIB_WRAPPER_H