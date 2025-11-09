const talib = require('../src/index');

console.log('TA-Lib Node.js Wrapper Examples\n');

// Sample price data
const prices = [
  44.0, 44.34, 44.09, 44.15, 43.61, 43.44, 43.39, 42.95, 42.71, 42.56,
  42.6, 43.13, 43.44, 43.75, 43.86, 43.79, 43.64, 43.43, 43.33, 43.27,
  43.1, 42.77, 42.63, 42.5, 42.28, 41.98, 41.71, 41.55, 41.47, 41.42,
  41.48, 41.43, 41.31, 41.2, 41.11, 40.94, 40.89, 40.8, 40.67, 40.48,
  40.25, 39.92, 39.54, 39.17, 38.97, 38.65, 38.52, 38.25, 38.28, 38.36
];

console.log('Sample prices:', prices.slice(0, 10), '...');

try {
  // Simple Moving Average (SMA)
  console.log('\n=== Simple Moving Average (SMA) ===');
  const sma = talib.SMA(prices, { timePeriod: 10 });
  console.log('SMA (period 10):');
  sma.forEach((val, idx) => {
    if (val !== null) {
      console.log(`  Day ${idx + 1}: ${val.toFixed(2)}`);
    }
  });

  // Exponential Moving Average (EMA)
  console.log('\n=== Exponential Moving Average (EMA) ===');
  const ema = talib.EMA(prices, { timePeriod: 10 });
  console.log('EMA (period 10):');
  ema.forEach((val, idx) => {
    if (val !== null) {
      console.log(`  Day ${idx + 1}: ${val.toFixed(2)}`);
    }
  });

  // Relative Strength Index (RSI)
  console.log('\n=== Relative Strength Index (RSI) ===');
  const rsi = talib.RSI(prices, { timePeriod: 14 });
  console.log('RSI (period 14):');
  rsi.forEach((val, idx) => {
    if (val !== null) {
      console.log(`  Day ${idx + 1}: ${val.toFixed(2)}%`);
    }
  });

  // Generic Moving Average with different types
  console.log('\n=== Different Moving Average Types ===');
  console.log('MA Types available:', talib.MAType);

  const smaResult = talib.MA(prices, { timePeriod: 10, maType: talib.MAType.SMA });
  const emaResult = talib.MA(prices, { timePeriod: 10, maType: talib.MAType.EMA });

  console.log('Last SMA value:', smaResult[smaResult.length - 1]?.toFixed(2));
  console.log('Last EMA value:', emaResult[emaResult.length - 1]?.toFixed(2));

} catch (error) {
  console.error('Error:', error.message);
  console.log('\nNote: This is expected during development as the native bindings are not built yet.');
  console.log('To build the project, run: npm run build');
}