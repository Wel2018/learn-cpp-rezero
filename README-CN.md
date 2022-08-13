[English](README.md) | [中文](README-CN.md)

# Learn C++ Re:Zero

<p>
<img src="https://img.shields.io/github/issues/Wel2018/learn-cpp-rezero"/>
<img src="https://img.shields.io/github/stars/Wel2018/learn-cpp-rezero"/>
<img src="https://img.shields.io/github/license/Wel2018/learn-cpp-rezero"/>
<img src="https://img.shields.io/badge/platform-linux%20%7C%20windows%20-blue"/>
<img src="https://img.shields.io/github/contributors/Wel2018/learn-cpp-rezero"/>
<img src="https://img.shields.io/github/commit-activity/m/Wel2018/learn-cpp-rezero"/>
</p>

📝 [博客主页](https://juejin.cn/user/2594503171769720/posts)
| 📄 [详细文档](doc/overview.md)
| 💬 [常见问题](FAQ.md)
| ⁉ [Issues](https://github.com/Wel2018/learn-cpp-rezero/issues)

从零开始学习 C++。

## 目录

- [Learn C++ Re:Zero](#learn-c-rezero)
  - [目录](#目录)
  - [序](#序)
  - [内容安排](#内容安排)
  - [项目结构](#项目结构)
  - [开发环境](#开发环境)
  - [贡献方式](#贡献方式)
  - [参考](#参考)
  - [开源协议](#开源协议)

## 序

**我为什么要创建该项目？**

在学习网络编程的过程中，我遇到很多在课本上没学会甚至没见过的知识，例如线程池、内存池、协程、Reactor、ORM 等，虽然这些内容在网络上有很多现成的第三方库，但是我并不满足于仅仅调用 api，如果不知道它是如何实现的，总觉得理解不到位，就像蒙上一层纸一般似懂非懂，偶尔还会误用。因此，我想通过这个项目，从生产实践角度的【零】开始，逐步学习应用开发时应该掌握的实用基础知识，通过写博客、实现相关代码来检验学习效果，进一步加强和巩固理解。

**我为什么选择 C++？** 

C 语言非常优雅，本身语法特性很少，却可以使用宏、结构体和指针实现很多强大的功能，然而 C 是底层语言，它不适合拿来写大型应用，包括复杂的 Web 服务、GUI 编程等。Java、Python、Golang 等高级语言的编程体验要好的多，仅仅使用标准库就能实现大量功能，但是对于一些对性能敏感的场景，如金融、医疗、游戏服务器、GUI 编程、图像处理等，或是一些对能敏感的场景，如机器人、嵌入式、驱动开发、机器学习等，C++ 就更加适合一些。此外，语言本身拥有很强的自由度，这本身也是一种魅力吧。

>   从 C++11 到 C++20，标准库对于一些重要特性（例如网络库、异步编程、协程、反射等）的支持仍然差强人意，与高级语言的标准库相比，还有很长的路要走。虽说如此，这几年 C++ 标准委员会已经在发力了，在 C++ 11 - 17 中引入了许多非常有用的特性，如智能指针、右值、不定参数模板、lambda 等，至于准标准库 Boost 则提供了更多有用的“基础设施”，给编程带来很大的便利。

## 内容安排

暂定内容安排如下：

- C++ 实现动态线程池
- C++ 自定义内存池
- C++ 自定义空间分配器
- C++ 基于 `u_context` 实现协程
- C++ 实现对象池
- C++ 中的线程同步工具
- Reactor 网络库
- 内存泄露检测工具
- 函数调用追踪
- 基于 vector 实现自己的 `String` 类
- C++ STL 容器实现
- 实现无锁队列
- C++ 编译期反射实现序列化
- 模板元编程
- C++ `Logger` 日志类实现
- C++ 最常用的新特性
- C++ 实现简单的 TCP / HTTP 服务器
- C++ ORM 库的简单实现
- C++ GC 机制
- 多线程环境下如何确保内存一致性
- 缓存淘汰算法实现
- malloc 原理分析
- slab 机制管理内存映射
- bitmap 的应用
- …

## 项目结构

```
. 
|-- bin/                 # 二进制文件输出目录
|-- doc/                 # 所有源码的配套文档
|-- include/             # 头文件目录
|-- src/                 # 源文件目录
|-- test/                # 测试文件目录
|-- FAQ.md               # 常见问题
|-- LICENSE              # 开源协议
|-- Makefile             # make 构建脚本
|-- README-CN.md         # 项目说明文件（中文版）
|-- README.md            # Project description document（English Version）
```

## 开发环境

所有代码均在如下环境测试通过：

- OS: Ubuntu 20.04 focal(WSL2)
- Kernel: x86_64 Linux 5.10 
- Shell: zsh 5.8
- gcc version: 9.4.0
- 编辑器: vscode
- C++ 标准：C++17

## 贡献方式

欢迎对 C++ 感兴趣的朋友 ⭐ star 该项目，您的支持是我继续更新下去的最大动力！
由于本人水平、精力有限，博客和相关代码可能存在疏漏之处，
欢迎在 ⁉ [Issues](https://github.com/Wel2018/learn-cpp-rezero/issues) 中提问和讨论，
也欢迎有能力的大佬直接 Pull Request。

## 参考

- [【C++】关于内存那些事](https://juejin.cn/post/7129510627436920863) 
- [C++ reference](https://en.cppreference.com/w/)
- [Boost C++ Libraries](https://www.boost.org/doc/libs/1_80_0/)

## 开源协议

MIT License

