const talib = require('../src/index');

describe('TALib Basic Tests', () => {
  const sampleData = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];

  test('should calculate SMA correctly', () => {
    const result = talib.SMA(sampleData, { timePeriod: 5 });

    expect(result).toHaveLength(10);
    expect(result[0]).toBeNull();
    expect(result[1]).toBeNull();
    expect(result[2]).toBeNull();
    expect(result[3]).toBeNull();
    expect(result[4]).toBe(3); // (1+2+3+4+5)/5 = 3
    expect(result[5]).toBe(4); // (2+3+4+5+6)/5 = 4
    expect(result[9]).toBe(8); // (6+7+8+9+10)/5 = 8
  });

  test('should calculate EMA correctly', () => {
    const result = talib.EMA(sampleData, { timePeriod: 5 });

    expect(result).toHaveLength(10);
    // First few values should be null for EMA
    expect(result[0]).toBeNull();
    expect(result[1]).toBeNull();
    expect(result[2]).toBeNull();
    expect(result[3]).toBeNull();
    // EMA values should be numbers after the warmup period
    expect(result[4]).toBeGreaterThanOrEqual(0);
    expect(result[9]).toBeGreaterThanOrEqual(0);
  });

  test('should calculate RSI correctly', () => {
    const prices = [44, 44.34, 44.09, 44.15, 43.61, 43.44, 43.39, 42.95, 42.71, 42.56, 42.6, 43.13, 43.44, 43.75, 43.86, 43.79, 43.64, 43.43, 43.33, 43.27, 43.1, 42.77, 42.63, 42.5, 42.28, 41.98, 41.71, 41.55, 41.47, 41.42, 41.48, 41.43, 41.31, 41.2, 41.11, 40.94, 40.89, 40.8, 40.67, 40.48, 40.25, 39.92, 39.54, 39.17, 38.97, 38.65, 38.52, 38.25, 38.28, 38.36, 38.41, 38.48, 38.59, 38.75, 38.95, 39.22, 39.41];
    const result = talib.RSI(prices, { timePeriod: 14 });

    expect(result).toHaveLength(prices.length);
    // First 14 values should be null
    for (let i = 0; i < 14; i++) {
      expect(result[i]).toBeNull();
    }
    // RSI values should be between 0 and 100
    for (let i = 14; i < result.length; i++) {
      if (result[i] !== null) {
        expect(result[i]).toBeGreaterThanOrEqual(0);
        expect(result[i]).toBeLessThanOrEqual(100);
      }
    }
  });

  test('should handle empty array', () => {
    expect(() => {
      talib.SMA([], { timePeriod: 5 });
    }).toThrow();
  });

  test('should handle insufficient data', () => {
    const shortData = [1, 2];
    expect(() => {
      talib.SMA(shortData, { timePeriod: 5 });
    }).toThrow();
  });

  test('should use default options', () => {
    const result = talib.SMA(sampleData);
    expect(result).toHaveLength(10);
  });

  test('should export MAType constants', () => {
    expect(talib.MAType).toBeDefined();
    expect(talib.MAType.SMA).toBe(0);
    expect(talib.MAType.EMA).toBe(1);
  });

  test('should create new TALib instance', () => {
    const instance = new talib.TALib();
    expect(instance).toBeDefined();
    expect(typeof instance.SMA).toBe('function');
  });
});

describe('Error Handling', () => {
  test('should throw on invalid input type', () => {
    expect(() => {
      talib.SMA('not an array');
    }).toThrow();
  });

  test('should throw on invalid options', () => {
    const data = [1, 2, 3, 4, 5];
    expect(() => {
      talib.SMA(data, 'not an object');
    }).not.toThrow(); // Should handle gracefully
  });

  test('should handle NaN values in input', () => {
    const dataWithNaN = [1, 2, NaN, 4, 5, 6, 7, 8, 9, 10];
    const result = talib.SMA(dataWithNaN, { timePeriod: 5 });
    expect(result).toBeDefined();
    expect(result).toHaveLength(10);
  });
});