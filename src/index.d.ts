export interface IndicatorOptions {
  timePeriod?: number;
  [key: string]: any;
}

export interface MAOptions extends IndicatorOptions {
  maType?: MAType;
}

export interface MACDOptions extends IndicatorOptions {
  fastPeriod?: number;
  slowPeriod?: number;
  signalPeriod?: number;
}

export interface BBANDSOptions extends IndicatorOptions {
  nbDevUp?: number;
  nbDevDn?: number;
  maType?: MAType;
}

export enum MAType {
  SMA = 0,
  EMA = 1,
  WMA = 2,
  DEMA = 3,
  TEMA = 4,
  TRIMA = 5,
  KAMA = 6,
  MAMA = 7,
  T3 = 8
}

export class TALib {
  constructor();

  // Moving Averages
  SMA(data: number[], options?: IndicatorOptions): (number | null)[];
  EMA(data: number[], options?: IndicatorOptions): (number | null)[];
  MA(data: number[], options?: MAOptions): (number | null)[];

  // Momentum Indicators
  RSI(data: number[], options?: IndicatorOptions): (number | null)[];
  MACD(data: number[], options?: MACDOptions): any; // TODO: Define proper return type

  // Volatility Indicators
  ATR(high: number[], low: number[], close: number[], options?: IndicatorOptions): (number | null)[];
  BBANDS(data: number[], options?: BBANDSOptions): any; // TODO: Define proper return type

  // Volume Indicators
  AD(high: number[], low: number[], close: number[], volume: number[]): (number | null)[];
  OBV(close: number[], volume: number[]): (number | null)[];
}

// Default instance
declare const talib: TALib;

// Export both default instance and individual functions
export default talib;
export { TALib, MAType };

// Individual function exports
export function SMA(data: number[], options?: IndicatorOptions): (number | null)[];
export function EMA(data: number[], options?: IndicatorOptions): (number | null)[];
export function MA(data: number[], options?: MAOptions): (number | null)[];
export function RSI(data: number[], options?: IndicatorOptions): (number | null)[];
export function MACD(data: number[], options?: MACDOptions): any;
export function ATR(high: number[], low: number[], close: number[], options?: IndicatorOptions): (number | null)[];
export function BBANDS(data: number[], options?: BBANDSOptions): any;
export function AD(high: number[], low: number[], close: number[], volume: number[]): (number | null)[];
export function OBV(close: number[], volume: number[]): (number | null)[];