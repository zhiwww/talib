#include "talib.h"
#include <iostream>

Napi::FunctionReference TALibWrapper::constructor;
bool TALibWrapper::taLibInitialized = false;

Napi::Object TALibWrapper::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    // Initialize TA-Lib
    InitializeTALib();

    Napi::Function func = DefineClass(env, "TALib", {
        InstanceMethod("sma", &TALibWrapper::SMA),
        InstanceMethod("ema", &TALibWrapper::EMA),
        InstanceMethod("ma", &TALibWrapper::MA),
        InstanceMethod("rsi", &TALibWrapper::RSI),
        InstanceMethod("macd", &TALibWrapper::MACD),
        InstanceMethod("atr", &TALibWrapper::ATR),
        InstanceMethod("bbands", &TALibWrapper::BBANDS),
        InstanceMethod("ad", &TALibWrapper::AD),
        InstanceMethod("obv", &TALibWrapper::OBV)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("TALib", func);
    return exports;
}

TALibWrapper::TALibWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<TALibWrapper>(info) {
    // Constructor logic
}

void TALibWrapper::InitializeTALib() {
    if (!taLibInitialized) {
        TA_RetCode retCode = TA_Initialize();
        if (retCode != TA_SUCCESS) {
            // We can't throw exceptions in static initialization, so we'll just not initialize
            return;
        }
        taLibInitialized = true;
    }
}

std::vector<double> TALibWrapper::JSArrayToVector(const Napi::Array& arr) {
    size_t length = arr.Length();
    std::vector<double> result(length);

    for (size_t i = 0; i < length; ++i) {
        Napi::Value val = arr[i];
        if (val.IsNumber()) {
            result[i] = val.As<Napi::Number>().DoubleValue();
        } else {
            result[i] = std::numeric_limits<double>::quiet_NaN();
        }
    }

    return result;
}

Napi::Array TALibWrapper::VectorToJSArray(Napi::Env env, const std::vector<double>& vec) {
    Napi::Array result = Napi::Array::New(env, vec.size());

    for (size_t i = 0; i < vec.size(); ++i) {
        if (std::isnan(vec[i])) {
            result[i] = env.Null();
        } else {
            result[i] = Napi::Number::New(env, vec[i]);
        }
    }

    return result;
}

Napi::Value TALibWrapper::HandleResult(Napi::Env env, TA_RetCode retCode, const std::vector<double>& result) {
    if (retCode != TA_SUCCESS) {
        Napi::Error::New(env, "TA-Lib function failed").ThrowAsJavaScriptException();
        return env.Null();
    }

    return VectorToJSArray(env, result);
}

// SMA Implementation
Napi::Value TALibWrapper::SMA(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsArray()) {
        Napi::TypeError::New(env, "First argument must be an array").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Array inputArray = info[0].As<Napi::Array>();
    int timePeriod = 30; // default value

    if (info.Length() > 1 && info[1].IsObject()) {
        Napi::Object options = info[1].As<Napi::Object>();
        if (options.Has("timePeriod")) {
            timePeriod = options.Get("timePeriod").As<Napi::Number>().Int32Value();
        }
    }

    std::vector<double> input = JSArrayToVector(inputArray);
    int size = static_cast<int>(input.size());

    if (size < timePeriod) {
        Napi::RangeError::New(env, "Input array length must be greater than or equal to timePeriod").ThrowAsJavaScriptException();
        return env.Null();
    }

    // TA-Lib output arrays
    std::vector<double> output(size, 0.0);
    int outBegIdx, outNbElement;

    TA_RetCode retCode = TA_SMA(0, size - 1, input.data(), timePeriod, &outBegIdx, &outNbElement, output.data());

    if (retCode != TA_SUCCESS) {
        Napi::Error::New(env, "TA-Lib SMA function failed").ThrowAsJavaScriptException();
        return env.Null();
    }

    // Create result array with correct size
    std::vector<double> result(size);

    // Fill with NaN for values before the first valid output
    for (int i = 0; i < outBegIdx; ++i) {
        result[i] = std::numeric_limits<double>::quiet_NaN();
    }

    // Copy the actual SMA values
    // The TA-Lib output starts at outBegIdx and has outNbElement values
    for (int i = 0; i < outNbElement; ++i) {
        result[outBegIdx + i] = output[i];
    }

    return VectorToJSArray(env, result);
}

// EMA Implementation
Napi::Value TALibWrapper::EMA(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsArray()) {
        Napi::TypeError::New(env, "First argument must be an array").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Array inputArray = info[0].As<Napi::Array>();
    int timePeriod = 30; // default value

    if (info.Length() > 1 && info[1].IsObject()) {
        Napi::Object options = info[1].As<Napi::Object>();
        if (options.Has("timePeriod")) {
            timePeriod = options.Get("timePeriod").As<Napi::Number>().Int32Value();
        }
    }

    std::vector<double> input = JSArrayToVector(inputArray);
    int size = static_cast<int>(input.size());

    if (size < timePeriod) {
        Napi::RangeError::New(env, "Input array length must be greater than or equal to timePeriod").ThrowAsJavaScriptException();
        return env.Null();
    }

    std::vector<double> output(size);
    int outBegIdx, outNbElement;

    TA_RetCode retCode = TA_EMA(0, size - 1, input.data(), timePeriod, &outBegIdx, &outNbElement, output.data());

    if (retCode == TA_SUCCESS) {
        // Fill the beginning with null values
        for (int i = 0; i < outBegIdx; ++i) {
            output[i] = std::numeric_limits<double>::quiet_NaN();
        }
    }

    return HandleResult(env, retCode, output);
}

// MA Implementation (Generic Moving Average)
Napi::Value TALibWrapper::MA(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsArray()) {
        Napi::TypeError::New(env, "First argument must be an array").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Array inputArray = info[0].As<Napi::Array>();
    int timePeriod = 30;
    TA_MAType maType = TA_MAType_SMA; // default to SMA

    if (info.Length() > 1 && info[1].IsObject()) {
        Napi::Object options = info[1].As<Napi::Object>();
        if (options.Has("timePeriod")) {
            timePeriod = options.Get("timePeriod").As<Napi::Number>().Int32Value();
        }
        if (options.Has("maType")) {
            maType = static_cast<TA_MAType>(options.Get("maType").As<Napi::Number>().Int32Value());
        }
    }

    std::vector<double> input = JSArrayToVector(inputArray);
    int size = static_cast<int>(input.size());

    if (size < timePeriod) {
        Napi::RangeError::New(env, "Input array length must be greater than or equal to timePeriod").ThrowAsJavaScriptException();
        return env.Null();
    }

    std::vector<double> output(size);
    int outBegIdx, outNbElement;

    TA_RetCode retCode = TA_MA(0, size - 1, input.data(), timePeriod, maType, &outBegIdx, &outNbElement, output.data());

    if (retCode == TA_SUCCESS) {
        // Fill the beginning with null values
        for (int i = 0; i < outBegIdx; ++i) {
            output[i] = std::numeric_limits<double>::quiet_NaN();
        }
    }

    return HandleResult(env, retCode, output);
}

// RSI Implementation
Napi::Value TALibWrapper::RSI(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsArray()) {
        Napi::TypeError::New(env, "First argument must be an array").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Array inputArray = info[0].As<Napi::Array>();
    int timePeriod = 14; // default value

    if (info.Length() > 1 && info[1].IsObject()) {
        Napi::Object options = info[1].As<Napi::Object>();
        if (options.Has("timePeriod")) {
            timePeriod = options.Get("timePeriod").As<Napi::Number>().Int32Value();
        }
    }

    std::vector<double> input = JSArrayToVector(inputArray);
    int size = static_cast<int>(input.size());

    if (size < timePeriod) {
        Napi::RangeError::New(env, "Input array length must be greater than or equal to timePeriod").ThrowAsJavaScriptException();
        return env.Null();
    }

    std::vector<double> output(size);
    int outBegIdx, outNbElement;

    TA_RetCode retCode = TA_RSI(0, size - 1, input.data(), timePeriod, &outBegIdx, &outNbElement, output.data());

    if (retCode == TA_SUCCESS) {
        // Fill the beginning with null values
        for (int i = 0; i < outBegIdx; ++i) {
            output[i] = std::numeric_limits<double>::quiet_NaN();
        }
    }

    return HandleResult(env, retCode, output);
}

// Placeholder implementations for other indicators
Napi::Value TALibWrapper::MACD(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Error::New(env, "MACD not implemented yet").ThrowAsJavaScriptException();
    return env.Null();
}

Napi::Value TALibWrapper::ATR(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Error::New(env, "ATR not implemented yet").ThrowAsJavaScriptException();
    return env.Null();
}

Napi::Value TALibWrapper::BBANDS(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Error::New(env, "BBANDS not implemented yet").ThrowAsJavaScriptException();
    return env.Null();
}

Napi::Value TALibWrapper::AD(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Error::New(env, "AD not implemented yet").ThrowAsJavaScriptException();
    return env.Null();
}

Napi::Value TALibWrapper::OBV(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Error::New(env, "OBV not implemented yet").ThrowAsJavaScriptException();
    return env.Null();
}