# Bohan - C++ 高性能网络服务器框架

Bohan 是一个自研的 C++ 高性能网络服务器框架，支持多线程、线程池、定时器和 TCP 网络通信。适用于构建即时通讯服务器、游戏服务器等需要高并发处理能力的场景。

## 特性

- **多线程支持**：基于 `std::thread` 的跨平台线程封装
- **线程池**：高效的任务调度和线程复用机制
- **定时器**：支持周期定时器和重复定时器
- **网络库**：基于事件驱动的 TCP 网络通信
- **跨平台**：支持 Windows、Linux、macOS
- **Protocol Buffers**：集成 Protobuf 协议支持

## 项目结构

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
│   │   ├── Timer.h        # 定时器
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

## 系统架构图

```
┌─────────────────────────────────────────────────────────────────┐
│                         Application Layer                        │
│                    (MsgServer / examples)                        │
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

## 核心类说明

### 基础库 (base)

| 类名 | 说明 | 主要功能 |
|------|------|----------|
| `ThreadPool` | 线程池 | 管理固定数量的工作线程，支持任务提交和异步执行 |
| `Timer` | 定时器 | 支持周期定时器、重复定时器，基于优先级队列实现 |
| `BlockQueue<T>` | 阻塞队列 | 线程安全的阻塞队列，支持生产者 - 消费者模式 |
| `Hash_Map<K,V>` | 哈希表 | 线程安全的哈希表封装 |
| `CLock` / `AutoLock` | 锁 | RAII 风格的自动锁 |
| `Singleton<T>` | 单例 | 线程安全的单例模式实现 |
| `SimpleBuffer` | 缓冲区 | 简单的内存缓冲区管理 |
| `PackageBase` | 协议包 | 网络协议包的封包和拆包 |

### 网络库 (net)

| 类名 | 说明 | 主要功能 |
|------|------|----------|
| `BaseSocket` | Socket 基类 | 封装 Socket 基础操作，支持 TCP 服务端和客户端 |
| `Connection` | 连接类 | TCP 连接封装，支持数据收发和回调 |
| `TcpSocketCallback` | Socket 回调 | 虚接口，定义连接事件回调 |
| `EventDispatch` | 事件分发器 | 单例模式，管理 Socket 事件、定时器、循环事件 |

### 消息服务器 (MsgServer)

| 类名 | 说明 | 主要功能 |
|------|------|----------|
| `MsgConn` | 消息连接 | 继承 Connection，处理消息连接逻辑 |
| `UserInfo` | 用户信息 | 管理用户登录状态、连接信息 |
| `UserInfoManager` | 用户管理器 | 单例模式，管理所有在线用户 |

## 快速开始

### 环境要求

- C++17 或更高版本
- CMake 3.10.2 或更高版本
- Windows: Visual Studio 2019+ / MinGW
- Linux: g++ 7+
- macOS: Clang 7+

### 编译和运行

```bash
cd bohan
mkdir build
cd build
cmake ..
make  # Windows 上可使用 cmake --build . --config Release
```

### 使用示例

#### 1. 线程池使用

```cpp
#include "ThreadPool.h"
using namespace bohan;

int main() {
    ThreadPool pool(4);  // 创建 4 个线程

    pool.addTask([](){
        printf("任务执行中\n");
    });

    return 0;
}
```

#### 2. 定时器使用

```cpp
#include "Timer.h"
using namespace bohan;

int main() {
    Timer timer(1);
    timer.StartLoop();

    // 添加周期定时器，每 1000ms 执行一次
    timer.AddPeriodTimer(1000, [](){
        printf("定时器触发\n");
    });

    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}
```

#### 3. TCP 服务器示例

```cpp
#include "net/Connection.h"
using namespace bohan;

class MyConnection : public Connection {
    void OnNewConn(socket_handle handle) override {
        printf("新连接：%d\n", handle);
    }

    void OnReceiveData(const char* data, int32_t size) override {
        printf("收到数据：%s\n", data);
    }
};

int main() {
    MyConnection conn;
    // 监听端口
    // ...
    return 0;
}
```

## 协议包格式

```
┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
│ length  │ version │  flag   │serviceId│commandId│ seqNum  │
│ 4 bytes │ 2 bytes │ 2 bytes │ 2 bytes │ 2 bytes │ 2 bytes │
└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
```

## 设计亮点

1. **线程安全**：所有共享数据结构都使用互斥锁保护
2. **RAII 资源管理**：使用智能指针和自动锁管理资源
3. **事件驱动**：基于 epoll/kqueue/IOCP 的事件驱动模型
4. **零拷贝设计**：使用 SimpleBuffer 减少内存拷贝
5. **跨平台兼容**：统一的跨平台接口封装

## License

MIT License

## 作者

bohan.lj
