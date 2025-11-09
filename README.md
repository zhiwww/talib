# @zhiwww/talib

[![npm version](https://badge.fury.io/js/%40zhiwww%2Ftalib.svg)](https://badge.fury.io/js/%40zhiwww%2Ftalib)
[![Build Status](https://github.com/zhiwww/talib/workflows/CI/badge.svg)](https://github.com/zhiwww/talib/actions)
[![License: ISC](https://img.shields.io/badge/License-ISC-blue.svg)](https://opensource.org/licenses/ISC)

高性能的 TA-Lib (Technical Analysis Library) Node.js wrapper，为JavaScript/TypeScript提供技术分析功能。

## 特性

- 🚀 **高性能**: 基于TA-Lib C库，提供接近原生的性能
- 📊 **功能完整**: 支持150+技术指标
- 🎯 **TypeScript支持**: 完整的类型定义
- 💻 **跨平台**: 支持Windows、macOS、Linux
- 📈 **易于使用**: 简洁的API设计

## 安装

```bash
npm install @zhiwww/talib
```

### 系统要求

- Node.js >= 14.0.0
- Python 3.x (用于构建)
- C++编译工具链
  - Windows: Visual Studio Build Tools
  - macOS: Xcode Command Line Tools
  - Linux: gcc/g++, make

## 快速开始

```javascript
const talib = require('@zhiwww/talib');

// 计算简单移动平均线
const data = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
const result = talib.MA(data, { timePeriod: 5 });

console.log(result);
// 输出: [null, null, null, null, 3, 4, 5, 6, 7, 8]
```

### TypeScript 示例

```typescript
import * as talib from '@zhiwww/talib';

const data: number[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
const result: number[] = talib.MA(data, { timePeriod: 5 });
```

## API 文档

### 支持的指标类别

#### 趋势指标
- `SMA` - 简单移动平均线
- `EMA` - 指数移动平均线
- `DEMA` - 双指数移动平均线
- `TEMA` - 三重指数移动平均线
- `WMA` - 加权移动平均线
- `KAMA` - Kaufman自适应移动平均线
- `MAMA` - MESA自适应移动平均线

#### 动量指标
- `RSI` - 相对强弱指数
- `MOM` - 动量
- `ROC` - 变化率
- `ROCR` - 变化率百分比

#### 波动率指标
- `ATR` - 平均真实波幅
- `NATR` - 归一化平均真实波幅

#### 成交量指标
- `AD` - 累积/派发线
- `OBV` - 能量潮

### 基本用法

```javascript
// 相对强弱指数 (RSI)
const rsi = talib.RSI(prices, { timePeriod: 14 });

// MACD
const macd = talib.MACD(prices, {
  fastPeriod: 12,
  slowPeriod: 26,
  signalPeriod: 9
});

// 布林带
const bbands = talib.BBANDS(prices, {
  timePeriod: 20,
  nbDevUp: 2,
  nbDevDn: 2
});
```

## 开发计划

### 当前版本: 0.6.4

- [x] 项目基础设置
- [ ] TA-Lib C库集成
- [ ] 核心指标实现 (SMA, EMA, RSI, MACD, Bollinger Bands)
- [ ] TypeScript类型定义
- [ ] 完整测试套件
- [ ] 性能优化
- [ ] 文档完善

### 路线图

#### v0.7.0 (开发中)
- 核心功能实现
- 基础指标支持
- TypeScript支持

#### v0.8.0
- 扩展指标库
- 性能优化
- 更多使用示例

#### v1.0.0
- 稳定API
- 完整文档
- 生产就绪

## 贡献指南

欢迎贡献代码！请查看 [CONTRIBUTING.md](CONTRIBUTING.md) 了解详细信息。

### 开发环境设置

```bash
# 克隆仓库
git clone https://github.com/zhiwww/talib.git
cd talib

# 安装依赖
npm install

# 运行测试
npm test

# 构建项目
npm run build
```

## 许可证

[ISC License](LICENSE)

## 相关链接

- [TA-Lib 官网](http://ta-lib.org/)
- [TA-Lib GitHub](https://github.com/mrjbq7/ta-lib)
- [API 文档](https://github.com/zhiwww/talib/wiki)

## 支持

如果遇到问题，请：
1. 查看 [FAQ](https://github.com/zhiwww/talib/wiki/FAQ)
2. 搜索现有 [Issues](https://github.com/zhiwww/talib/issues)
3. 创建新的 Issue

---

**注意**: 本项目目前处于开发阶段，API可能会发生变化。