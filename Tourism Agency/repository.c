#include <string.h>
#include <stdlib.h>
#include "repository.h"
#include "domain.h"

OfferRepository* createRepository()
{
	OfferRepository* r = (OfferRepository*)malloc(sizeof(OfferRepository));
	if (r == NULL)
		return NULL;

	r->offers = createArray(CAPACITY, &destroyOffer, &copyOffer);
	if (r->offers == NULL)
	{
		free(r);
		return NULL;
	}
	return r;
}

void destroyRepository(OfferRepository* r)
{
	if (r == NULL)
		return;

	if (r->offers == NULL)
	{
		free(r);
		return;
	}

	destroyArray(r->offers);
	free(r->offers);
	free(r);
}

int getSize(OfferRepository* o)
{
	if (o == NULL)
		return -1;
	return getArraySize(o->offers);
}

int getCapacity(OfferRepository* o)
{
	if (o == NULL)
		return -1;
	return getArrayCapacity(o->offers);
}

Offer* getOfferOnPosition(OfferRepository* r, int pos)
{
	if (r == NULL)
		return NULL;

	return getElement(r->offers, pos);
}

int search(OfferRepository* r, char destination[], char departureDate[])
{
	if (r == NULL)
		return -1;

	int i;
	for (i = 0; i < getArraySize(r->offers); i++)
		if (strcmp(getDestination(getElement(r->offers, i)), destination) == 0 && strcmp(getDepartureDate(getElement(r->offers, i)), departureDate) == 0)
			return i;
	return -1;
}

int searchByTypePrice(OfferRepository* r, char type[], double price)
{
	if (r == NULL)
		return -1;

	int i;
	for (i = 0; i < getArraySize(r->offers); i++)
		if (strcmp(getType(getElement(r->offers, i)), type) == 0 && getPrice(getElement(r->offers, i)) == price)
			return i;
	return -1;
}

Offer* findByDestDeparture(OfferRepository* r, char* destination, char* departureDate)
{
	if (r == NULL || destination == NULL || departureDate == NULL)
		return NULL;

	int i;
	for (i = 0; i < getArraySize(r->offers); i++)
	{
		Offer* o = getElement(r->offers, i);
		if (strcmp(getDestination(o), destination) == 0 && strcmp(getDepartureDate(o), departureDate) == 0)
			return o;
	}
	return NULL;
}

int add(OfferRepository* r, Offer* o)
{
	if (r == NULL || o == NULL)
		return 0;

	addElem(r->offers, o);
	return 1;
}

int delete(OfferRepository* r, char* destination, char* departureDate)
{
	if (r == NULL || destination == NULL || departureDate == NULL)
		return 0;

	Offer* o = findByDestDeparture(r, destination, departureDate);
	if (o == NULL)
		return 0;

	int i;
	for (i = 0; i < getArraySize(r->offers); i++)
		if (getElement(r->offers, i) == o)
		{
			deleteElem(r->offers, i);
			return 1;
		}
	return 0;
}

void update(OfferRepository* r, Offer* offerToUpdate, int pos)
{
	destroyOffer(r->offers->elements[pos]);
	updateElem(r->offers, pos, copyOffer(offerToUpdate));
}

OfferRepository* copyRepo(OfferRepository* repoToCopy)
{
	if (repoToCopy == NULL)
		return NULL;

	OfferRepository* copy = (OfferRepository*)malloc(sizeof(OfferRepository));
	if (copy == NULL)
		return NULL;

	copy->offers = copyArray(repoToCopy->offers);
	if (copy->offers == NULL)
	{
		free(copy);
		return NULL;
	}
	return copy;
}