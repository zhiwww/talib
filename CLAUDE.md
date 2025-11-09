# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Essential Commands

### Build & Development
```bash
npm run build              # Rebuild C++ addon with node-gyp
npm run build:debug        # Build with debug symbols
npm run clean              # Remove build artifacts
./scripts/dev.sh           # Full dev setup: install deps, build, test, run example
```

### Testing
```bash
npm test                   # Run all Jest tests
npm run test:watch         # Run tests in watch mode
npm run test:coverage      # Generate coverage report
npx jest test/basic.test.js  # Run specific test file
npx jest -t "SMA"          # Run tests matching pattern
```

### Linting
```bash
npm run lint               # Check JS code style
npm run lint:fix           # Auto-fix linting issues
```

## Architecture Overview

This is a **Node.js C++ addon** that wraps the TA-Lib C library for technical analysis. The architecture has three distinct layers:

### 1. C++ Layer (Native Addon)
- **Entry point**: `src/binding.cpp` - Minimal NAPI initialization
- **Implementation**: `src/talib.cpp` + `src/talib.h` - TALibWrapper class
- **Pattern**: Each indicator method follows the same flow:
  1. Validate arguments (count, types, array length)
  2. Convert JS arrays → `std::vector<double>` (NaN for non-numeric values)
  3. Call TA-Lib C function (e.g., `TA_SMA()`)
  4. Pad output with NaN for lookback period indices
  5. Convert `std::vector<double>` → JS array (null for NaN values)

### 2. JavaScript Wrapper Layer
- **File**: `src/index.js`
- **Purpose**: Provides user-friendly API over C++ addon
- **Pattern**: Singleton instance exported by default
  ```javascript
  const talib = require('@zhiwww/talib');
  talib.SMA(data);  // Uses singleton

  const { TALib } = require('@zhiwww/talib');
  new TALib().SMA(data);  // Create new instance
  ```
- **Exports**: Constants (MAType enum), bound functions, TALib class

### 3. TA-Lib C Library Integration
- **Headers**: `/opt/homebrew/Cellar/ta-lib/0.6.4/include/ta-lib`
- **Library**: `/opt/homebrew/Cellar/ta-lib/0.6.4/lib` (libtalibc)
- **Configured in**: `binding.gyp`
- **Note**: Paths are currently hardcoded for macOS Homebrew

## Key Technical Details

### Data Conversion Pattern
All indicator methods handle data conversion consistently:
- **Input**: JavaScript arrays with potential non-numeric values
- **Internal**: `std::vector<double>` with NaN for invalid values
- **Output**: JavaScript arrays with `null` for NaN (user-friendly)

### NAPI Integration
- Uses `node-addon-api` (v7.1.0) for C++ → JavaScript bridging
- `TALibWrapper` inherits from `Napi::ObjectWrap<TALibWrapper>`
- All methods use `Napi::CallbackInfo` for parameter handling
- Exception handling via `NAPI_DISABLE_CPP_EXCEPTIONS` define

### Build System
- **node-gyp**: Compiles C++ addon to `lib/talib.node`
- **C++ Standard**: C++17 (`-std=c++17` in binding.gyp)
- **Output**: Mach-O 64-bit bundle on macOS, DLL on Windows
- **Auto-build**: Triggered on `npm install` via install script

### Implementation Status
Currently implemented indicators: **SMA, EMA, MA, RSI**

Most other indicators (MACD, BBANDS, ATR, etc.) are stubs that throw "not implemented yet". When adding new indicators:
1. Add C++ method in `src/talib.cpp` following the established pattern
2. Expose method in `TALibWrapper::Init()`
3. Add wrapper method in `src/index.js`
4. Add TypeScript definition in `src/index.d.ts`
5. Write tests in `test/` following existing patterns

### Naming Conventions
- **C++ methods**: PascalCase (e.g., `TALibWrapper::SMA`)
- **JavaScript wrapper methods**: camelCase (e.g., `instance.sma`)
- **Exported functions**: PascalCase (e.g., `module.exports.SMA`)

### Error Handling
C++ methods validate in this order:
1. Argument count (`info.Length()`)
2. Argument types (`.IsArray()`, `.IsObject()`)
3. Data length vs. required period
4. TA-Lib return code (`TA_RetCode`)

Errors are thrown as JavaScript exceptions via `Napi::TypeError::New()` or `Napi::Error::New()`.

## Project Version
Current version: **0.7.0** (see package.json)

Node.js requirement: **>= 14.0.0**

## Critical Files for Development
- `binding.gyp` - Build configuration, TA-Lib paths
- `src/talib.cpp` - Core indicator implementations
- `src/index.js` - JavaScript API layer
- `src/index.d.ts` - TypeScript definitions
- `test/basic.test.js` - Test patterns to follow
