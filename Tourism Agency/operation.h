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
/// Creates an Operation (= allocates the necessary memory) and returns a pointer to it.
/// <param type= "type of Operation", operationType>
/// <param o= "Offer", Offer*>
/// <returns> a pointer to the created operation, NULL if allocation was unsuccessful and deallocates used memory
Operation* createOperation(operationType type, Offer* o);

/// <summary>
/// Deallocates the memory occupied by an Operation o.
/// <param o= "Operation", Operation*>
/// <returns> nothing
void destroyOperation(Operation* o);

/// <summary>
/// Copies an Operation (= allocates the necessary memory) and returns a pointer to it.
/// <param o= "Offer", Offer*>
/// <returns> a pointer to the copy operation, NULL if allocation was unsuccessful and deallocates used memory
Operation* copyOperation(Operation* o);

/// <summary>
/// Gets the type of an Operation o.
/// <param o= "Operation", Operation*>
/// <returns> type of o, operationType
operationType getOperationType(Operation* o);

/// <summary>
/// Gets the object of an Operation o.
/// <param o= "Operation", Operation*>
/// <returns> offer of o, Offer*
Offer* getOperationObject(Operation* o);