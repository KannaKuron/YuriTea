#pragma once

typedef signed char int8;
typedef short int16;
typedef int int32;
typedef long long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef float float32;
typedef double float64;
typedef long double float128;

template <typename T> struct Vector2 {
  T x, y;
};

template <typename T> struct Vector3 {
  T x, y, z;
};

template <typename T> struct Vector4 {
  T x, y, z, w;
};

template <typename T> using Scope = std::unique_ptr<T>;
template <typename T ,typename ...Args> constexpr Scope<T> CreateScope(Args&& ...args) { return std::make_unique<T>(std::forward<Args>(args)...); }

template<typename T> using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args> constexpr Ref<T> CreateRef(Args&& ... args){ return std::make_shared<T>(std::forward<Args>(args)...);}


