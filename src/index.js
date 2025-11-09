const talib = require('./binding.node');

// Export individual functions for easier usage
class TALib {
  constructor() {
    this.instance = new talib.TALib();
  }

  // Moving Averages
  SMA(data, options = {}) {
    const defaultOptions = { timePeriod: 5 };
    const opts = { ...defaultOptions, ...options };
    return this.instance.sma(data, opts);
  }

  EMA(data, options = {}) {
    return this.instance.ema(data, options);
  }

  MA(data, options = {}) {
    const defaultOptions = {
      timePeriod: 30,
      maType: 0 // SMA
    };
    const opts = { ...defaultOptions, ...options };
    return this.instance.ma(data, opts);
  }

  // Momentum Indicators
  RSI(data, options = {}) {
    const defaultOptions = { timePeriod: 14 };
    const opts = { ...defaultOptions, ...options };
    return this.instance.rsi(data, opts);
  }

  MACD(data, options = {}) {
    return this.instance.macd(data, options);
  }

  // Volatility Indicators
  ATR(high, low, close, options = {}) {
    return this.instance.atr(high, low, close, options);
  }

  BBANDS(data, options = {}) {
    return this.instance.bbands(data, options);
  }

  // Volume Indicators
  AD(high, low, close, volume) {
    return this.instance.ad(high, low, close, volume);
  }

  OBV(close, volume) {
    return this.instance.obv(close, volume);
  }
}

// Create singleton instance
const talibInstance = new TALib();

// Export both class and singleton instance
module.exports = talibInstance;
module.exports.TALib = TALib;

// Export constants for MA types
module.exports.MAType = {
  SMA: 0,
  EMA: 1,
  WMA: 2,
  DEMA: 3,
  TEMA: 4,
  TRIMA: 5,
  KAMA: 6,
  MAMA: 7,
  T3: 8
};

// Export function compatibility
module.exports.SMA = talibInstance.SMA.bind(talibInstance);
module.exports.EMA = talibInstance.EMA.bind(talibInstance);
module.exports.MA = talibInstance.MA.bind(talibInstance);
module.exports.RSI = talibInstance.RSI.bind(talibInstance);
module.exports.MACD = talibInstance.MACD.bind(talibInstance);
module.exports.ATR = talibInstance.ATR.bind(talibInstance);
module.exports.BBANDS = talibInstance.BBANDS.bind(talibInstance);
module.exports.AD = talibInstance.AD.bind(talibInstance);
module.exports.OBV = talibInstance.OBV.bind(talibInstance);