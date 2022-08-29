#pragma once
#define _NO_CRT_STDIO_INLINE
#include "domain.h"
#include "dynamicArray.h"

/// Structure OfferRepository that holds a pointer to a vector of pointers to offers.
/// size = current number of elements of the vector
/// capacity = how many elements can the vector hold, capacity >= size
typedef struct
{
	/*int capacity, size; // last version
	Offer** offers;*/
	DynamicArray* offers;
}OfferRepository;

/// <summary>
/// Creates an Offer Repository (= allocates the necessary memory) and returns a pointer to it.
/// <returns> a pointer to the created repository, NULL if allocation was unsuccessful and deallocates used memory
OfferRepository* createRepository();

/// <summary>
/// Deallocates the memory occupied by the Offer Repository r.
/// <param r= "Offer Repository", OfferRepository*>
/// <returns> nothing
void destroyRepository(OfferRepository* r);

/// <summary>
/// Gets the size of the offer repository.
/// <param o= "Offer", Offer*>
/// <returns> size of repo, int
int getSize(OfferRepository* o);

/// <summary>
/// Gets the capacity of the offer repository.
/// <param o= "Offer", Offer*>
/// <returns> capacity of repo, int
int getCapacity(OfferRepository* o);

/// <summary>
/// Searches for an offer with a given destination and departure date in repository r.
/// <param r= "Offer Repository", OfferRepository*>
/// <param destination[]= "destination of given offer", char>
/// <param departureDate[]= "departure date of given offer", char>
/// <returns> the position on which the offer with given destination and departure date is in the repo;
/// <returns> -1  if the offer does not exist in the repo 
int search(OfferRepository* r, char destination[], char departureDate[]);

/// <summary>
/// Searches for an offer with a given type and price date in repository r.
/// <param r= "Offer Repository", OfferRepository*>
/// <param type[]= "type of given offer", char>
/// <param price= "price of given offer", double>
/// <returns> the position on which the offer with given destination and departure date is in the repo;
/// <returns> -1  if the offer does not exist in the repo
int searchByTypePrice(OfferRepository* r, char type[], double price);

/// <summary>
/// Searches for an offer with a given destination and departure date in repository r.
/// <param r= "Offer Repository", OfferRepository*>
/// <param destination= "destination of given offer", char*>
/// <param departureDate= "departure date of given offer", char*>
/// <returns> pointer to the offer with given destination and departure date if it is in the repo;
/// <returns> NULL  if the offer does not exist in the repo 
Offer* findByDestDeparture(OfferRepository* r, char* destination, char* departureDate);

/// <summary>
/// Returns the offer on position <pos> in the offer repository.
/// <param o= "Offer", Offer*>
/// <param pos= "position of offer", int>
/// <returns> a pointer to the offer on position <pos>
Offer* getOfferOnPosition(OfferRepository* r, int pos);

/// <summary>
/// Adds an offer o to the repository of offers.
/// <param r= "Offer Repository", OfferRepository*>
/// <param o= "offer to be added", Offer*>
/// <returns> 1 if the offer was successfully added to the repo
/// <returns> 0 if the offer couldn't be added, because another offer with the same destination and departure date already exists in the repo.
int add(OfferRepository* r, Offer* o);

/// <summary>
/// Removes an offer o to the repository of offers.
/// <param r= "Offer Repository", OfferRepository*>
/// <param destination[]= "destination of offer to be removed", char>
/// <param departureDate[]= "departure date of offer to be removed", char>/// <returns> 1 if the offer was successfully added to the repo
/// <returns> 1 if the offer was successfully deleted from the repo
/// <returns> 0 if the offer couldn't be deleted, because the offer doesn't exist in the repo.
int delete(OfferRepository* r, char* destination, char* departureDate);

/// <summary>
/// Updates the an Offer from the repository.
/// <param r= "Offer Repository", Service*>
/// <param offerToUpdate= "Offer to update", Offer*>
/// <param pos = "position of offer", int>
void update(OfferRepository* r, Offer* offerToUpdate, int pos);

/// <summary>
/// Creates a copy of the current repository.
/// <param repoToCopy= "Offer Repository to be copied", Service*>
/// <returns> pointer to the created repository
OfferRepository * copyRepo(OfferRepository * repoToCopy); 
