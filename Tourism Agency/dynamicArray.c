#pragma once
#include "dynamicarray.h"
#include <stdlib.h>
#include <stdio.h>

DynamicArray* createArray(int capacity, destroyFunction destroy, copyFunction copy)
{
	DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));

	if (arr == NULL)
		return NULL;

	arr->capacity = capacity;
	arr->size = 0;

	arr->elements = (TElem*)malloc(sizeof(TElem) * arr->capacity);
	if (arr->elements == NULL)
	{
		free(arr);
		return NULL;
	}

	arr->destroyFunction = destroy;
	arr->copyFunction = copy;
	return arr;
}

void destroyArray(DynamicArray* arr)
{
	if (arr == NULL)
		return;
	if (arr->elements == NULL)
	{
		free(arr);
		return;
	}

	for (int i = 0; i < arr->size; i++)
		arr->destroyFunction(arr->elements[i]);

	free(arr->elements);
	free(arr);
}

void resize(DynamicArray* arr)
{
	if (arr == NULL)
		return;

	arr->capacity *= 2; // double capacity

	// allocate new memory, copy everything and deallocate the old memory
	int i;
	TElem* new_elems = (TElem*)malloc(sizeof(TElem) * arr->capacity);
	if (new_elems == NULL)
		return;
	else
	{
		for (i = 0; i < arr->size; i++)
			new_elems[i] = arr->elements[i];
		free(arr->elements);
		arr->elements = new_elems;  // point to newly allocated memory
	}
}

void addElem(DynamicArray* arr, TElem elem)
{
	if (arr == NULL)
		return;

	if (arr->elements == NULL)
		return;

	int old_capacity = arr->capacity;
	if (arr->size == arr->capacity)   // resize array if necessary
	{
		resize(arr);
		if (old_capacity == arr->capacity) // resize failed
			return;
	}

	arr->elements[arr->size++] = elem;
}

int getArraySize(DynamicArray* arr)
{
	if (arr == NULL)
		return -1;

	return arr->size;
}

int getArrayCapacity(DynamicArray* arr)
{
	if (arr == NULL)
		return -1;

	return arr->capacity;
}

TElem getElement(DynamicArray* arr, int pos)
{
	if (arr == NULL || pos < 0)
		return NULL;

	return arr->elements[pos];
}

void deleteElem(DynamicArray* arr, int pos)
{
	if (arr == NULL || pos < 0 || pos >= arr->size)
		return;

	arr->destroyFunction(arr->elements[pos]);
	
	if (pos != arr->size - 1)
		arr->elements[pos] = arr->elements[arr->size - 1];
	arr->size--;
}

void updateElem(DynamicArray* arr, int pos, TElem t)
{
	arr->elements[pos] = t;
}

DynamicArray* copyArray(DynamicArray* arr)
{
	DynamicArray* new = (DynamicArray*)malloc(sizeof(DynamicArray));
	if (new == NULL)
	{
		free(new);
		return NULL;
	}
	else
	{
		new->capacity = arr->capacity;
		new->size = arr->size;
		new->elements = (TElem*)malloc(sizeof(TElem) * new->capacity);
		if (new->elements == NULL)
		{
			free(new);
			return NULL;
		}
		new->destroyFunction = arr->destroyFunction;
		new->copyFunction = arr->copyFunction;
		for (int i = 0; i < arr->size; i++)
			new->elements[i] = arr->copyFunction(arr->elements[i]);
		return new;
	}
}
