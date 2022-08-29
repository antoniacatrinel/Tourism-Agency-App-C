#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domain.h"

Offer* createOffer(char* type, char* destination, char* departureDate, double price)
{
	Offer* o = malloc(sizeof(Offer));
	if (o == NULL)
	{
		return NULL;
	}
	o->type = malloc(sizeof(char) * (strlen(type) + 1));
	if (o->type == NULL)
	{
		free(o);
		return NULL;
	}
	strcpy(o->type, type);

	o->destination = malloc(sizeof(char) * (strlen(destination) + 1));
	if (o->destination == NULL)
	{
		free(o->type);
		free(o);
		return NULL;
	}
	strcpy(o->destination, destination);

	o->departureDate = malloc(sizeof(char) * (strlen(departureDate) + 1));
	if (o->departureDate == NULL)
	{
		free(o->destination);
		free(o->type);
		free(o);
		return NULL;
	}
	strcpy(o->departureDate, departureDate);

	o->price = price;

	return o;
}

void destroyOffer(Offer* o)
{
	if (o == NULL)
		return;

	// free memory allocated for the fiels of offer
	free(o->type);
	free(o->destination);
	free(o->departureDate);

	// free memory allocated for the offer structure
	free(o);
}

char* getType(Offer* o)
{
	if (o == NULL)
		return NULL;

	return o->type;
}

char* getDestination(Offer* o)
{
	if (o == NULL)
		return NULL;

	return o->destination;
}

char* getDepartureDate(Offer* o)
{
	if (o == NULL)
		return NULL;

	return o->departureDate;
}

double getPrice(Offer* o)
{
	if (o == NULL)
		return -1;

	return o->price;
}

void toString(Offer* o, char str[])
{
	if (o == NULL)
		return;

	sprintf(str, "    Offer of type %s, with destination %s, departure date %s and price %.2lf.\n", o->type, o->destination, o->departureDate, o->price);
}

Offer* copyOffer(Offer* offerToCopy)
{
	if (offerToCopy == NULL)
		return NULL;
	if (offerToCopy->type == NULL || offerToCopy->destination == NULL || offerToCopy->departureDate == NULL)
		return NULL;

	Offer* copy = createOffer(offerToCopy->type, offerToCopy->destination, offerToCopy->departureDate, offerToCopy->price);
	return copy;
}
