#ifndef BASIC_STRUCTS_HPP
#define BASIC_STRUCTS_HPP

#define EXPORT_DLL __declspec(dllexport)

template <typename T> struct EXPORT_DLL Vector2D {
  T w;
  T h;
};

#endif // BASIC_STRUCTS_HPP
