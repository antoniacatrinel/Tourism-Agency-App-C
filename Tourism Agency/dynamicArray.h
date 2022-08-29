#pragma once
#include "domain.h"
#define CAPACITY 10

typedef void* TElem;
typedef void(*destroyFunction)(TElem);  
typedef TElem(*copyFunction)(TElem);

typedef struct
{
	TElem* elements;
	int size, capacity;
	destroyFunction destroyFunction;
	copyFunction copyFunction;

} DynamicArray;
// array that stores pointers to offers

DynamicArray* createArray(int capacity, destroyFunction destroy, copyFunction copy);

void destroyArray(DynamicArray* v);

int getArraySize(DynamicArray* arr);

int getArrayCapacity(DynamicArray* arr);

TElem getElement(DynamicArray* arr, int pos);

void addElem(DynamicArray* v, TElem elem);

void deleteElem(DynamicArray* arr, int pos);

void updateElem(DynamicArray* arr, int pos, TElem t);

DynamicArray* copyArray(DynamicArray* v);
