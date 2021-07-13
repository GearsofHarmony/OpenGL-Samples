#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H


const float PI = 3.1415926f;
const int WIDTH = 800;
const int HEIGHT = 600;

template<class T> void SAFE_DELETE(T*& ptr) { if (ptr) { delete (ptr); (ptr) = NULL; } };
template<class T> void SAFE_DELETE_ARRAY(T*& ptr) { if (ptr) { delete[](ptr); (ptr) = NULL; } };
#endif // !CONSTANTS_H
