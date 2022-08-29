#pragma once
#define _NO_CRT_STDIO_INLINE
#include "domain.h"
#include "dynamicArray.h"

/// Structure OfferRepository holds a pointer to a dynamic array of pointers to offers
typedef struct
{
	DynamicArray* offers;
}OfferRepository;

/// <summary>
/// Creates an Offer Repository (= allocates the necessary memory)
/// </summary>
/// <returns>a pointer to the created repository, NULL if allocation was unsuccessful and deallocates used memory</returns>
OfferRepository* createRepository();

/// <summary>
/// Deallocates the memory occupied by the Offer Repository r
/// </summary>
/// <param name="r">Offer Repository, OfferRepository*</param>
void destroyRepository(OfferRepository* r);

/// <summary>
/// Returns the size of the offer repository
/// </summary>
/// <param name="o">Offer, OfferRepository*</param>
int getSize(OfferRepository* o);

/// <summary>
/// Returns the capacity of the offer repository
/// </summary>
/// <param name="o">Offer, OfferRepository*</param>
int getCapacity(OfferRepository* o);

/// <summary>
/// Searches for an offer with a given destination and departure date in repository r
/// </summary>
/// <param name="r">Offer Repository, OfferRepository*</param>
/// <param name="destination">destination of given offer, char</param>
/// <param name="departureDate">departure date of given offer, char</param>
/// <returns> the position on which the offer with given destination and departure date is in the repo
///			 -1  if the offer does not exist in the repo </returns>
int search(OfferRepository* r, char destination[], char departureDate[]);

/// <summary>
/// Searches for an offer with a given type and price date in repository r
/// </summary>
/// <param name="r">Offer Repository, OfferRepository*</param>
/// <param name="type">type of given offer, char</param>
/// <param name="price">price of given offer, double</param>
/// <returns> the position on which the offer with given destination and departure date is in the repo
///			  -1  if the offer does not exist in the repo</returns>
int searchByTypePrice(OfferRepository* r, char type[], double price);

/// <summary>
/// Searches for an offer with a given destination and departure date in repository r
/// </summary>
/// <param name="r">Offer Repository, OfferRepository*</param>
/// <param name="destination">destination of given offer, char*</param>
/// <param name="departureDate">departure date of given offer, char*</param>
/// <returns> a pointer to the offer with given destination and departure date if it is in the repo
///           NULL  if the offer does not exist in the repo </returns>
Offer* findByDestDeparture(OfferRepository* r, char* destination, char* departureDate);

/// <summary>
/// Returns the offer on position <pos> in the offer repository
/// </summary>
/// <param name="r">Offer Repository, OfferRepository*</param>
/// <param name="pos">position of offer, int</param>
/// <returns> a pointer to the offer on position <pos></returns>
Offer* getOfferOnPosition(OfferRepository* r, int pos);

/// <summary>
/// Adds an offer o to the repository of offers
/// </summary>
/// <param name="r">Offer Repository, OfferRepository*</param>
/// <param name="o">offer to be added, Offer*</param>
/// <returns>1 if the offer was successfully added to the repo
/// <returns> 1 if the offer was successfully added to the repo
///			  0 if the offer couldn't be added, because another offer with the same destination and departure date already exists in the repo</returns>
int add(OfferRepository* r, Offer* o);


/// <summary>
/// Removes an offer o to the repository of offers
/// </summary>
/// <param name="r">Offer Repository, OfferRepository*</param>
/// <param name="destination">destination of offer to be removed, char</param>
/// <param name="departureDate">departure date of offer to be removed, char</param>
/// <returns> 1 if the offer was successfully deleted from the repo
///			   0 if the offer couldn't be deleted, because the offer doesn't exist in the repo</returns>
int delete(OfferRepository* r, char* destination, char* departureDate);

/// <summary>
/// Updates the an Offer from the repository
/// </summary>
/// <param name="r">Offer Repository, OfferRepository*</param>
/// <param name="offerToUpdate">Offer to update, Offer*</param>
/// <param name="pos">position of offer, int</param>
void update(OfferRepository* r, Offer* offerToUpdate, int pos);

/// <summary>
/// Creates a copy of the current repository
/// </summary>
/// <param name="repoToCopy">Offer Repository to be copied, OfferRepository*</param>
/// <returns>pointer to the copy repository</returns>
OfferRepository * copyRepo(OfferRepository * repoToCopy); 
