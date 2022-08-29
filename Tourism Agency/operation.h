#pragma once
#include "domain.h"

typedef enum
{
	ADD,
	DELETE,
	UPDATETYPE,
	UPDATEDESTINATION,
	UPDATEDEPARTURE,
	UPDATEPRICE
}operationType;

typedef struct
{
	operationType type;
	Offer* offer;
}Operation;

/// <summary>
/// Creates an Operation (= allocates the necessary memory)
/// </summary>
/// <param name="type">type of Operation, operationType</param>
/// <param name="o">Offer, Offer*</param>
/// <returns>a pointer to the created operation, NULL if allocation was unsuccessful and deallocates used memory</returns>
Operation* createOperation(operationType type, Offer* o);

/// <summary>
/// Deallocates the memory occupied by an Operation o
/// </summary>
/// <param name="o">Operation, Operation*</param>
void destroyOperation(Operation* o);

/// <summary>
/// Creates a copy of an Operation (= allocates the necessary memory)
/// </summary>
/// <param name="o">Operation, Operation*</param>
/// <returns>pointer to the copy</returns>
Operation* copyOperation(Operation* o);

/// <summary>
/// Returns the type of an Operation o
/// </summary>
/// <param name="o">Operation, Operation*</param>
/// <returns>type of o, operationType</returns>
operationType getOperationType(Operation* o);

/// <summary>
/// Returns the object of an Operation o
/// </summary>
/// <param name="o">Operation, Operation*</param>
/// <returns>offer of o, Offer*</returns>
Offer* getOperationObject(Operation* o);