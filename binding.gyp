{
  "targets": [
    {
      "target_name": "talib",
      "sources": [
        "src/talib.cpp",
        "src/binding.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "/opt/homebrew/Cellar/ta-lib/0.6.4/include/ta-lib"
      ],
      "cflags_cc": [
        "-std=c++17",
        "-Wall",
        "-Wextra"
      ],
      "libraries": [
        "-L/opt/homebrew/Cellar/ta-lib/0.6.4/lib",
        "-lta-lib"
      ],
      "defines": [
        "NAPI_DISABLE_CPP_EXCEPTIONS"
      ],
      "msvs_settings": {
        "VCCLCompilerTool": {
          "ExceptionHandling": 1,
          "AdditionalOptions": ["/std:c++17"]
        }
      },
      "xcode_settings": {
        "CLANG_CXX_LANGUAGE_STANDARD": "c++17",
        "CLANG_CXX_LIBRARY": "libc++"
      }
    }
  ]
}