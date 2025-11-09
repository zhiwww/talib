# Contributing to @zhiwww/talib

Thank you for your interest in contributing to the TA-Lib Node.js wrapper! This guide will help you get started.

## Development Setup

### Prerequisites

1. **TA-Lib C Library**: Ensure TA-Lib is installed (see [INSTALL.md](INSTALL.md))
2. **Node.js** >= 14.0.0
3. **Git**

### Setup Steps

1. **Fork and Clone**
   ```bash
   git clone https://github.com/YOUR_USERNAME/talib.git
   cd talib
   ```

2. **Install Dependencies**
   ```bash
   npm install
   ```

3. **Build the Project**
   ```bash
   npm run build
   ```

4. **Run Tests**
   ```bash
   npm test
   ```

## Project Structure

```
talib/
├── src/                 # Source code
│   ├── talib.h         # Header file with C++ class definitions
│   ├── talib.cpp       # Main implementation file
│   ├── binding.cpp     # Node.js binding entry point
│   ├── index.js        # JavaScript wrapper
│   └── index.d.ts      # TypeScript type definitions
├── test/               # Test files
├── examples/           # Example usage
├── lib/                # Compiled output (generated)
├── binding.gyp         # Native addon build configuration
└── package.json        # Project configuration
```

## Adding New Indicators

### 1. Update Header File

Add the new indicator method declaration in `src/talib.h`:

```cpp
// Example for adding Stochastic Oscillator
Napi::Value STOCH(const Napi::CallbackInfo& info);
```

### 2. Implement the Indicator

Add the implementation in `src/talib.cpp`:

```cpp
Napi::Value TALibWrapper::STOCH(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Validate input parameters
    if (info.Length() < 3) {
        Napi::TypeError::New(env, "STOCH requires high, low, close arrays").ThrowAsJavaScriptException();
        return env.Null();
    }

    // Extract parameters
    Napi::Array highArray = info[0].As<Napi::Array>();
    Napi::Array lowArray = info[1].As<Napi::Array>();
    Napi::Array closeArray = info[2].As<Napi::Array>();

    // Parse options
    int fastKPeriod = 5;
    int slowKPeriod = 3;
    int slowDPeriod = 3;

    if (info.Length() > 3 && info[3].IsObject()) {
        Napi::Object options = info[3].As<Napi::Object>();
        if (options.Has("fastKPeriod")) {
            fastKPeriod = options.Get("fastKPeriod").As<Napi::Number>().Int32Value();
        }
        // Parse other options...
    }

    // Convert JavaScript arrays to C++ vectors
    std::vector<double> high = JSArrayToVector(highArray);
    std::vector<double> low = JSArrayToVector(lowArray);
    std::vector<double> close = JSArrayToVector(closeArray);

    // Call TA-Lib function
    std::vector<double> outSlowK(high.size());
    std::vector<double> outSlowD(high.size());
    int outBegIdx, outNbElement;

    TA_RetCode retCode = TA_STOCH(0, high.size() - 1,
                                 high.data(), low.data(), close.data(),
                                 fastKPeriod, slowKPeriod, TA_MAType_SMA, slowDPeriod, TA_MAType_SMA,
                                 &outBegIdx, &outNbElement,
                                 outSlowK.data(), outSlowD.data());

    // Return result as object
    Napi::Object result = Napi::Object::New(env);
    result.Set("slowK", VectorToJSArray(env, outSlowK));
    result.Set("slowD", VectorToJSArray(env, outSlowD));

    return result;
}
```

### 3. Update Init Method

Add the new method to the `DefineClass` call in `src/talib.cpp`:

```cpp
Napi::Function func = DefineClass(env, "TALib", {
    // Existing methods...
    InstanceMethod("stoch", &TALibWrapper::STOCH),
});
```

### 4. Update JavaScript Wrapper

Add the new indicator to `src/index.js`:

```javascript
STOCH(high, low, close, options = {}) {
  return this.instance.stoch(high, low, close, options);
}
```

### 5. Update TypeScript Definitions

Add type definitions in `src/index.d.ts`:

```typescript
export interface STOCHOptions extends IndicatorOptions {
  fastKPeriod?: number;
  slowKPeriod?: number;
  slowDPeriod?: number;
}

export function STOCH(high: number[], low: number[], close: number[], options?: STOCHOptions): {
  slowK: (number | null)[];
  slowD: (number | null)[];
};
```

### 6. Add Tests

Create tests in `test/` directory:

```javascript
describe('STOCH - Stochastic Oscillator', () => {
  test('should calculate STOCH correctly', () => {
    const high = [/* data */];
    const low = [/* data */];
    const close = [/* data */];

    const result = talib.STOCH(high, low, close, {
      fastKPeriod: 5,
      slowKPeriod: 3,
      slowDPeriod: 3
    });

    expect(result).toHaveProperty('slowK');
    expect(result).toHaveProperty('slowD');
    // Add more assertions...
  });
});
```

## Code Style

### C++ Code
- Use modern C++17 features
- Follow existing naming conventions (PascalCase for methods)
- Include proper error handling
- Add comments for complex logic

### JavaScript Code
- Use ES6+ features
- Follow the existing style
- Use JSDoc comments for documentation

### Testing
- Write comprehensive tests for new features
- Include edge cases and error conditions
- Use descriptive test names

## Submitting Changes

1. **Create a Branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```

2. **Make Changes**
   - Implement your feature
   - Add tests
   - Update documentation

3. **Test Your Changes**
   ```bash
   npm test
   npm run lint
   ```

4. **Commit Changes**
   ```bash
   git add .
   git commit -m "feat: add [feature name] indicator"
   ```

5. **Push and Create Pull Request**
   ```bash
   git push origin feature/your-feature-name
   ```

## Running Tests

```bash
# Run all tests
npm test

# Run tests in watch mode
npm run test:watch

# Run tests with coverage
npm run test:coverage
```

## Build Process

```bash
# Clean previous build
npm run clean

# Build in debug mode
npm run build:debug

# Build for production
npm run build
```

## Getting Help

- Check existing [Issues](https://github.com/zhiwww/talib/issues)
- Read the [TA-Lib Documentation](http://ta-lib.org/)
- Join our discussions for questions

## Release Process

Releases are handled by maintainers. The process involves:

1. Updating version in `package.json`
2. Updating CHANGELOG.md
3. Creating a git tag
4. Publishing to npm

## License

By contributing, you agree that your contributions will be licensed under the ISC License.