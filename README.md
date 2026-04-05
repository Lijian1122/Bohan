# Bohan - C++ 高性能网络服务器框架

<div align="center">

**跨平台 · 高性能 · 事件驱动 · 易于扩展**

[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-blue)](https://github.com/bohan-lj/Bohan)
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-17-green)](https://isocpp.org/)
[![License](https://img.shields.io/badge/license-MIT-orange)](LICENSE)

</div>

---

Bohan 是一个自研的 **C++ 高性能网络服务器框架**，采用事件驱动架构和多线程设计，支持 TCP 网络通信、定时器、线程池等核心功能。适用于构建即时通讯服务器、游戏服务器、IoT 网关等需要高并发处理能力的场景。

## 🌟 核心特性

| 特性 | 说明 |
|------|------|
| **🚀 高性能** | 基于事件驱动的异步 I/O 模型，支持高并发连接 |
| **🧵 多线程** | 内置线程池，高效的任务调度和线程复用 |
| **⏱️ 定时器** | 支持周期定时器和重复定时器，基于优先级队列 |
| **🔌 网络库** | 封装完整的 TCP 网络通信，支持连接管理和事件回调 |
| **🔒 线程安全** | 所有共享数据结构均有完善的锁机制保护 |
| **📦 跨平台** | Windows / Linux / macOS 全平台支持 |
| **🔧 易扩展** | 模块化设计，支持快速业务定制 |

---

## 🏗️ 系统架构

```
┌─────────────────────────────────────────────────────────────────┐
│                         Application Layer                        │
│                    (MsgServer / Custom Server)                   │
├─────────────────────────────────────────────────────────────────┤
│                         Network Layer                            │
│  ┌─────────────┬─────────────┬─────────────┬─────────────────┐  │
│  │ Connection  │ BaseSocket  │EventDispatch│   NetCoreLib    │  │
│  │  TCP 连接    │  Socket 封装 │  事件分发器  │   网络核心库     │  │
│  └─────────────┴─────────────┴─────────────┴─────────────────┘  │
├─────────────────────────────────────────────────────────────────┤
│                      Infrastructure Layer                        │
│  ┌──────────┬──────────┬──────────┬──────────┬───────────────┐  │
│  │ThreadPool│  Timer   │BlockQueue│ HashMap  │    Lock       │  │
│  │ 线程池   │ 定时器   │ 阻塞队列  │ 哈希表   │    锁封装     │  │
│  └──────────┴──────────┴──────────┴──────────┴───────────────┘  │
├─────────────────────────────────────────────────────────────────┤
│                          System Layer                            │
│            pthread / std::thread / mutex / condition             │
└─────────────────────────────────────────────────────────────────┘
```

---

## 📁 项目结构

```
Bohan/
├── bohan/
│   ├── base/              # 基础库模块
│   │   ├── ThreadPool.h   # 线程池
│   │   ├── Timer.h        # 定时器
│   │   ├── BlockQueue.h   # 阻塞队列
│   │   ├── HashMap.h      # 线程安全的哈希表
│   │   ├── Lock.h         # 锁封装
│   │   ├── Singleton.h    # 单例模式
│   │   ├── Util.h         # 工具函数
│   │   ├── SimpleBuffer.h # 简单缓冲区
│   │   ├── PackageBase.h  # 协议包基础
│   │   └── ...
│   ├── net/               # 网络库模块
│   │   ├── Connection.h   # TCP 连接封装
│   │   ├── BaseSocket.h   # Socket 基础类
│   │   ├── EventDispatch.h# 事件分发器
│   │   └── NetCoreLib.h   # 网络核心库
│   ├── MsgServer/         # 消息服务器示例
│   │   ├── MsgConn.h      # 消息连接处理
│   │   ├── UserInfo.h     # 用户信息管理
│   │   └── ServerDefine.h # 服务器定义
│   └── examples/          # 示例代码
│       ├── server/        # TCP 服务器示例
│       └── client/        # TCP 客户端示例
└── CMakeLists.txt         # CMake 构建配置
```

---

## 🧩 核心组件

### 基础库 (base)

| 组件 | 说明 | 应用场景 |
|------|------|----------|
| `ThreadPool` | 线程池 | 异步任务执行、后台任务处理 |
| `Timer` | 定时器 | 心跳检测、超时处理、周期性任务 |
| `BlockQueue<T>` | 阻塞队列 | 生产者 - 消费者模型 |
| `Hash_Map<K,V>` | 线程安全哈希表 | 缓存、会话管理 |
| `CLock` / `AutoLock` | RAII 锁 | 自动资源管理 |
| `Singleton<T>` | 单例模式 | 全局管理器 |
| `SimpleBuffer` | 内存缓冲区 | 网络数据收发 |
| `PackageBase` | 协议包封装 | 网络协议解析 |

### 网络库 (net)

| 组件 | 说明 | 应用场景 |
|------|------|----------|
| `BaseSocket` | Socket 封装 | TCP 服务端/客户端 |
| `Connection` | 连接管理 | 客户端连接处理 |
| `TcpSocketCallback` | 事件回调接口 | 自定义连接事件 |
| `EventDispatch` | 事件分发器 | 事件循环、定时器管理 |

### 消息服务器 (MsgServer)

| 组件 | 说明 | 应用场景 |
|------|------|----------|
| `MsgConn` | 消息连接 | 业务连接处理 |
| `UserInfo` | 用户信息 | 登录状态管理 |
| `UserInfoManager` | 用户管理器 | 在线用户管理 |

---

## 🚀 快速开始

### 环境要求

| 系统 | 要求 |
|------|------|
| **C++** | C++17 或更高版本 |
| **CMake** | 3.10.2 或更高版本 |
| **Windows** | Visual Studio 2019+ / MinGW |
| **Linux** | g++ 7+ |
| **macOS** | Clang 7+ |

### 编译指南

```bash
# 进入项目目录
cd bohan

# 创建构建目录
mkdir build && cd build

# 配置 CMake
cmake ..

# 编译
# Windows: cmake --build . --config Release
# Linux/macOS: make
cmake --build .
```

---

## 💡 使用示例

### 1. 线程池

```cpp
#include "ThreadPool.h"
using namespace bohan;

int main() {
    ThreadPool pool(4);  // 创建 4 个工作线程

    // 提交任务
    pool.addTask([](){
        printf("任务执行中...\n");
    });

    return 0;
}
```

### 2. 定时器

```cpp
#include "Timer.h"
using namespace bohan;

int main() {
    Timer timer(1);
    timer.StartLoop();  // 启动事件循环

    // 添加周期定时器，每 1000ms 触发一次
    timer.AddPeriodTimer(1000, [](){
        printf("定时器触发\n");
    });

    // 运行 10 秒
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}
```

### 3. TCP 服务器

```cpp
#include "net/Connection.h"
using namespace bohan;

class MyServer : public Connection {
    void OnNewConn(socket_handle handle) override {
        printf("新连接到来：%d\n", handle);
    }

    void OnReceiveData(const char* data, int32_t size) override {
        printf("收到数据：%.*s\n", size, data);
        // 回显数据
        SendData(data, size);
    }

    void OnCloseConn(socket_handle handle) override {
        printf("连接关闭：%d\n", handle);
    }
};

int main() {
    MyServer server;
    server.Listen("0.0.0.0", 8080);  // 监听 8080 端口
    server.StartEventLoop();         // 启动事件循环
    return 0;
}
```

### 4. TCP 客户端

```cpp
#include "net/Connection.h"
using namespace bohan;

class MyClient : public Connection {
    void OnConnectComplete(socket_handle handle) override {
        printf("连接服务器成功\n");
        SendData("Hello Server", 12);
    }

    void OnReceiveData(const char* data, int32_t size) override {
        printf("收到服务器响应：%.*s\n", size, data);
    }
};

int main() {
    MyClient client;
    client.Connect("127.0.0.1", 8080);  // 连接本地服务器
    client.StartEventLoop();
    return 0;
}
```

---

## 📦 协议格式

Bohan 使用自定义二进制协议格式：

```
┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
│ length  │ version │  flag   │serviceId│commandId│ seqNum  │
│ 4 bytes │ 2 bytes │ 2 bytes │ 2 bytes │ 2 bytes │ 2 bytes │
└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
```

| 字段 | 说明 |
|------|------|
| `length` | 数据包总长度 |
| `version` | 协议版本号 |
| `flag` | 标志位（加密、压缩等） |
| `serviceId` | 服务 ID |
| `commandId` | 命令 ID |
| `seqNum` | 序列号（用于请求 - 响应匹配） |

---

## 🎯 设计亮点

| 设计理念 | 实现方式 | 收益 |
|---------|---------|------|
| **线程安全** | 所有共享数据结构使用互斥锁保护 | 避免竞态条件 |
| **RAII 资源管理** | 智能指针 + AutoLock | 自动资源释放，防止泄漏 |
| **事件驱动** | epoll/kqueue/IOCP 模型 | 高并发、低延迟 |
| **零拷贝设计** | SimpleBuffer 缓冲区 | 减少内存拷贝，提升性能 |
| **跨平台兼容** | 统一接口封装 | 一次编写，多端运行 |
| **模块化设计** | 清晰的分层架构 | 易于理解和扩展 |

---

## 📊 性能指标

> 在标准测试环境下的基准性能（仅供参考）：

| 测试场景 | 指标 | 数值 |
|---------|------|------|
| 最大并发连接数 | Connections | 10,000+ |
| 消息吞吐量 | msgs/sec | 100,000+ |
| 平均延迟 | latency | < 1ms |
| 线程池任务调度 | tasks/sec | 50,000+ |

---

## 🔮 未来规划

- [ ] 支持 UDP 协议
- [ ] 集成 SSL/TLS 加密
- [ ] 支持 HTTP/WebSocket 协议
- [ ] 增加性能监控和日志系统
- [ ] 添加更多示例代码和文档

---

## 🤝 贡献指南

欢迎提交 Issue 和 Pull Request！

1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'feat: [by AI] Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request

---

## 📄 License

MIT License

---

## 👨‍💻 作者

**bohan.lj**

---

<div align="center">

如果这个项目对你有帮助，请给一个 ⭐️ **Star** 支持一下！

</div>
