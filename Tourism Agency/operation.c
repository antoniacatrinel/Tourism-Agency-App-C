#include "operation.h"
#include <stdlib.h> 

Operation* createOperation(operationType type, Offer* o)
{
	Operation* op = malloc(sizeof(Operation));

	if (op == NULL)
		return NULL;

	op->type = type;

	if (o == NULL)
		return NULL;

	Offer* copyOfO = copyOffer(o);
	if (copyOfO == NULL)
	{
		free(op);
		return NULL;
	}
	op->offer = copyOfO;

	return op;
}

void destroyOperation(Operation* o)
{
	if (o == NULL)
		return;

	destroyOffer(o->offer);
	free(o);
}

Operation* copyOperation(Operation* o)
{
	if (o == NULL)
		return NULL;

	Operation* new_op = createOperation(getOperationType(o), getOperationObject(o));
	return new_op;
}

operationType getOperationType(Operation* o)
{
	if (o == NULL)
		return -1;

	return o->type;
}

Offer* getOperationObject(Operation* o)
{
	if (o == NULL)
		return NULL;

	return o->offer;
}