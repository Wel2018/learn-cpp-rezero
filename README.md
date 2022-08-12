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

📝 [Blog](https://juejin.cn/user/2594503171769720/posts)
| 📄 [Documentation](doc/overview.md)
| 💬 [FAQ](FAQ.md)
| ⁉ [Issues](https://github.com/Wel2018/learn-cpp-rezero/issues)

Learn C++ from scratch.

## Table of Contents

- [Learn C++ Re:Zero](#learn-c-rezero)
  - [Table of Contents](#table-of-contents)
  - [Motivation](#motivation)
  - [Content arrangement](#content-arrangement)
  - [Project structure](#project-structure)
  - [Dev environment](#dev-environment)
  - [References](#references)
  - [License](#license)

## Motivation

**Why do I create this project?**

In the process of learning network programming, I met a lot of knowledges which I didn't learn even didn't seen, such as threadpool, memory-pool, coroutines, Reactor model, ORM and so on. Although these content has a lot of third-party libraries available on the Internet, but I'm not satisfied with just call API. I'm always confused and have only a hazy notion if I don't know how it is implemented. Therefore, through this project, I want to learn C++ from *zero* in the perspective of production practice, and gradually learn the practical basic knowledge that should be mastered in application development. I will validate the learning effect by writing blogs and implementing relevant codes to further strengthen my understanding about C++.

**why do I choose C++?**

C language is very elegant, with few syntax features, but it can implement a lot of powerful functions by combining macros, structures and Pointers. However, C is a low-level language, it is not suitable for creating large-scale applications, including complex Web services, GUI programming, etc. By contrast, the programming experience of Java, Python, Golang and other high-level languages is much better than C, and you can implement a lot of functions by using the powerful and complete standard library. However, for some performance sensitive scenarios, such as finance, medical, game server, GUI programming, image processing, or some energy sensitive scenarios, Such as robotics, embedded, driver development, machine learning, C++ is more suitable. In addition, language itself has a strong degree of freedom, which is also a kind of charm (I mean, pain and pleasure).

> *Note*: 
> From C++11 to 20, the standard library's support for some important features (such as network, asynchronous programming, coroutines, reflection, etc.) is still have a long way from the high-level languages. Fortunately, the C++ standards committee have made great contributions over the years. Many useful features in C++ 11-17, such as smart-pointers, rvalues, string_view, variadic templates, lambda, and more are introduced. The quasi-standard library Boost provides even more useful "infrastructure" that makes programming easier.

Welcome all friends who are interested in C++ to ⭐ star this project, your support is the biggest motivation for me to continue updating!
Due to my level and energy are limited, the blogs and related code may have inadequacies and errors, welcome to ask questions and discussion in ⁉ [Issues](https://github.com/Wel2018/learn-cpp-rezero/issues), also welcome to **Pull Request** directly!

## Content arrangement

The tentative arrangements are listed as follows:

- Dynamic thread pooling 
- Custom memory-pools
- C++ custom spatial allocator
- the implementation of coroutine based on `u_context`
- Object pooling
- C++ thread synchronization
- Reactor network library
- Memory leak detection tool
- Function call tracing
- Implement String class based on `std::vector`
- C++ STL implementation
- C++ compile-time reflection and serialization
- Template metaprogramming
- C++ `Logger` class implementation
- The most common new feature in C++
- Implements a simple TCP/HTTP server
- a simple implementation of C++ ORM library
- How to ensure memory consistency in a multithreaded environment
- Cache elimination algorithm implementation
- Malloc principle analysis
- manage memory mapping by using slab mechanism 
- Bitmap application
- ...

## Project structure

```
. 
|-- bin/                 # binary output directory
|-- doc/                 # all the source code of supporting documents
|-- include/             # header file directory
|-- src/                 # source file directory
|-- test/                # test file directory
|-- FAQ.md               # common problems
|-- LICENSE              # open source LICENSE agreement
|-- Makefile             # make build script
|-- README-CN.md         # project documents (Chinese ver.)
|-- README.md            # project documents (English ver.)
```

## Dev environment

All the test code passed in the following environment:

- OS: Ubuntu 20.04 Focal (WSL2)
- Kernel: x86_64 Linux 5.10
- Shell: ZSH
- GCC version 9.4.0
- Editor: vscode
- C++ standard: C++17

## References 
 
- [C++ reference](https://en.cppreference.com/w/)
- [Boost C++ Libraries](https://www.boost.org/doc/libs/1_80_0/)

## License

MIT License (for more details, see the [license file](LICENSE))


