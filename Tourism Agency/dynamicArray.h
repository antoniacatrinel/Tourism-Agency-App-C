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

/// <summary>
/// Creates a dynamic array that stores pointers to offers with a given capacity, a destroy function and a copy function
/// </summary>
/// <param name="capacity">initial capacity</param>
/// <param name="destroy">destroy function</param>
/// <param name="copy">copy function</param>
/// <returns>dynamic array</returns>
DynamicArray* createArray(int capacity, destroyFunction destroy, copyFunction copy);

/// <summary>
/// Destroys the dynamic array by deallocating the memory
/// </summary>
/// <param name="v">dynamic array</param>
void destroyArray(DynamicArray* v);

/// <summary>
/// Returns the current size of the array
/// </summary>
/// <param name="arr">dynamic array</param>
int getArraySize(DynamicArray* arr);

/// <summary>
/// Returns the capacity of the array
/// </summary>
/// <param name="arr">dynamic array</param>
int getArrayCapacity(DynamicArray* arr);

/// <summary>
/// Returns the element on position <pos> in the dynamic array
/// </summary>
/// <param name="arr">dynamic array</param>
/// <param name="pos">position of desired element</param>
TElem getElement(DynamicArray* arr, int pos);

/// <summary>
/// Adds a new element to the dynamic array
/// </summary>
/// <param name="v">dynamic array</param>
/// <param name="elem">element to be added</param>
void addElem(DynamicArray* v, TElem elem);

/// <summary>
/// Deletes element on position <pos> from the dynamic array
/// </summary>
/// <param name="arr">dynamic array</param>
/// <param name="pos">position of element to be deleted</param>
void deleteElem(DynamicArray* arr, int pos);

/// <summary>
/// Updates the element from position pos with a new element
/// </summary>
/// <param name="arr">dynamic array</param>
/// <param name="pos">position of element to be updated</param>
/// <param name="t">new element</param>
void updateElem(DynamicArray* arr, int pos, TElem t);

/// <summary>
/// Creates a copy of the dynamic array
/// </summary>
/// <param name="v">dynamic array</param>
/// <returns>copy of the dynamic array</returns>
DynamicArray* copyArray(DynamicArray* v);
