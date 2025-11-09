#!/bin/bash

echo "TA-Lib Node.js Wrapper Development Script"
echo "========================================="

# Check if TA-Lib is installed
echo "Checking TA-Lib installation..."
if pkg-config --exists ta-lib; then
    echo "✓ TA-Lib found"
else
    echo "✗ TA-Lib not found. Please install TA-Lib first:"
    echo "  macOS: brew install ta-lib"
    echo "  Ubuntu: wget and compile from source"
    echo "  Windows: Download from ta-lib.org"
    exit 1
fi

# Install npm dependencies
echo ""
echo "Installing npm dependencies..."
npm install

# Build the project
echo ""
echo "Building the project..."
npm run build

if [ $? -eq 0 ]; then
    echo ""
    echo "✓ Build successful!"

    # Run tests
    echo ""
    echo "Running tests..."
    npm test

    # Run example
    echo ""
    echo "Running example..."
    node examples/basic.js
else
    echo ""
    echo "✗ Build failed. Please check the error messages above."
    exit 1
fi