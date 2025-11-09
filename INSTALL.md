# Installation Guide

## Prerequisites

Before installing `@zhiwww/talib`, you need to have the TA-Lib C library installed on your system.

### Install TA-Lib C Library

#### macOS

```bash
# Using Homebrew
brew install ta-lib

# Or from source
curl -L http://prdownloads.sourceforge.net/ta-lib/ta-lib-0.4.0-src.tar.gz | tar xz
cd ta-lib/
./configure --prefix=/usr/local
make
sudo make install
```

#### Ubuntu/Debian

```bash
# From source (recommended)
wget http://prdownloads.sourceforge.net/ta-lib/ta-lib-0.4.0-src.tar.gz
tar -xzf ta-lib-0.4.0-src.tar.gz
cd ta-lib/
./configure --prefix=/usr
make
sudo make install

# Or using apt (may not have latest version)
sudo apt-get install libta-lib-dev
```

#### Windows

1. Download the precompiled binaries from [TA-Lib GitHub Releases](https://github.com/mrjbq7/ta-lib/releases)
2. Extract to `C:\ta-lib` or add to PATH
3. Set environment variable `TA_LIBRARY_PATH=C:\ta-lib\lib\ta_lib.lib`
4. Set environment variable `TA_INCLUDE_PATH=C:\ta-lib\include`

#### Other Linux Distributions

```bash
# From source (works on most distributions)
curl -L http://prdownloads.sourceforge.net/ta-lib/ta-lib-0.4.0-src.tar.gz | tar xz
cd ta-lib/
./configure --prefix=/usr/local
make
sudo make install
```

## Node.js Package Installation

```bash
npm install @zhiwww/talib
```

### Build from Source

If you want to build from source or contribute:

```bash
git clone https://github.com/zhiwww/talib.git
cd talib
npm install
npm run build
```

## Troubleshooting

### Common Issues

1. **"ta-lib.h not found"**: Make sure TA-Lib C library is properly installed and include directory is accessible.

2. **"Cannot find module"**: The build failed. Check that you have all build tools installed.

3. **Windows build errors**: Ensure Visual Studio Build Tools are installed with C++ support.

### Build Tools Required

- **Node.js** >= 14.0.0
- **Python** >= 3.6 (for node-gyp)
- **C++ Compiler**:
  - Windows: Visual Studio Build Tools or Visual Studio
  - macOS: Xcode Command Line Tools (`xcode-select --install`)
  - Linux: GCC/G++ and Make

### Verify Installation

```javascript
const talib = require('@zhiwww/talib');
console.log('TA-Lib version:', talib.version || 'loaded successfully');

// Test basic functionality
const data = [1, 2, 3, 4, 5];
const sma = talib.SMA(data, { timePeriod: 3 });
console.log('SMA result:', sma);
```

## Docker Support

For Docker environments, include TA-Lib installation in your Dockerfile:

```dockerfile
# Example for Ubuntu-based Docker image
RUN apt-get update && apt-get install -y \
    build-essential \
    wget \
    && wget http://prdownloads.sourceforge.net/ta-lib/ta-lib-0.4.0-src.tar.gz \
    && tar -xzf ta-lib-0.4.0-src.tar.gz \
    && cd ta-lib/ \
    && ./configure --prefix=/usr \
    && make \
    && make install \
    && cd .. \
    && rm -rf ta-lib* \
    && apt-get clean

# Install Node.js package
RUN npm install @zhiwww/talib
```