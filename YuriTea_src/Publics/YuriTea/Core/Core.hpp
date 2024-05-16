#pragma once

#ifdef YuriTea_DLL

#define YURITEA_API __declspec(dllexport)
#else
#define YURITEA_API __declspec(dllimport)
#endif

#define BIT(x) (1 << x) // Bitwise shift operator
