#pragma once

#include <memory>
#include <tuple>

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


// 向量
template <typename T> struct Vector2 {
  T x, y;
  T& operator[](const uint32 index){
    if (index >= 2){
      throw std::out_of_range("Index out of range");
    }
    return *(&x + index);
  }
};

template <typename T> struct Vector3 {
  T x, y, z;
  T& operator[](const uint32 index){
    if (index >= 3){
      throw std::out_of_range("Index out of range");
    }
    return *(&x + index);
  }
};

template <typename T> struct Vector4 {
  T x, y, z, w;
  T& operator[](const uint32 index){
    if (index >= 4){
      throw std::out_of_range("Index out of range");
    }
    return *(&x + index);
  }
};

// 矩阵
template <typename T> struct Matrix2 {
  Vector2<T> columns[2];
  T& operator[](const uint32 x, const uint32 y){
    if (x >= 2 || y >= 2){
      throw std::out_of_range("Index out of range");
    }
    return columns[x][y];

  }
};

template <typename T> struct Matrix3 {
  Vector3<T> columns[3];
  T& operator[](const uint32 x, const uint32 y){
    if (x >= 3 || y >= 3){
      throw std::out_of_range("Index out of range");
    }
    return columns[x][y];
  }
};

template <typename T> struct Matrix4 {
  Vector4<T> columns[4];
  T& operator[](const uint32 x, const uint32 y){
    if (x >= 4 || y >= 4){
      throw std::out_of_range("Index out of range");
    }
    return columns[x][y];
  }
};

template <typename T> using Scope = std::unique_ptr<T>;
template <typename T ,typename ...Args> constexpr Scope<T> CreateScope(Args&& ...args) { return std::make_unique<T>(std::forward<Args>(args)...); }

template<typename T> using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args> constexpr Ref<T> CreateRef(Args&& ... args){ return std::make_shared<T>(std::forward<Args>(args)...);}


