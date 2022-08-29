#pragma once
#include "repository.h"

// Structure Service that holds a pointer to the offer repository.
typedef struct
{
    OfferRepository* repo;
    DynamicArray* undoStack;
    DynamicArray* redoStack;
} Service;

/// <summary>
/// Creates an Offer Service (= allocates the necessary memory) and returns a pointer to it.
/// <param r= "Offer Repository", OfferRepository*>
/// <returns> a pointer to the created service, NULL if allocation was unsuccessful
Service* createService(OfferRepository* r, DynamicArray* undoStack, DynamicArray* redoStack);

/// <summary>
/// Deallocates the memory occupied by the Offer Sevice s.
/// <param s= "Offer Service", Service*>
/// <returns> nothing
void destroyService(Service* s);

/// <summary>
/// Gets the offer repository.
/// <param s= "Offer Service", Service*>
/// <returns> repo, OfferRepository*
OfferRepository* getRepository(Service* s);

/// <summary>
/// Adds an Offer to the repository.
/// <param s= "Offer Service", Service*>
/// <param type= "type of Offer", char*>
/// <param destination= "destination of Offer", char*>
/// <param departureDate= "departureDate of Offer", char*>
/// <param price= "price of Offer", double>
/// <returns> 1 if the offer was successfully added to the repo
/// <returns> 0 if the offer couldn't be added to the repo because it is duplicated
int addOffer(Service* s, char* type, char* destination, char* departureDate, double price);

/// <summary>
/// Deletes an Offer from the repository.
/// <param s= "Offer Service", Service*>
/// <param destination= "destination of Offer", char*>
/// <param departureDate= "departureDate of Offer", char*>
/// <returns> 1 if the offer was successfully deleted from the repo
/// <returns> 0 if the offer couldn't be deleted because it doesn't exist
int deleteOffer(Service* s, char* destination, char* departureDate);

/// <summary>
/// Updates the an Offer from the repository.
/// <param s= "Offer Service", Service*>
/// <param destination= "destination of Offer", char*>
/// <param departureDate= "departureDate of Offer", char*>
/// <param newType= "new type of Offer", char*>
/// <returns> 1 if the offer was successfully updated
/// <returns> 0 if the offer couldn't be updated because it doesn't exist
int updateOfferType(Service* s, char* destination, char* departureDate, char* newType);

/// <summary>
/// Updates the an Offer from the repository.
/// <param s= "Offer Service", Service*>
/// <param destination= "destination of Offer", char*>
/// <param departureDate= "departureDate of Offer", char*>
/// <param newDestination= "new destination of Offer", char*>
/// <returns> 1 if the offer was successfully updated
/// <returns> 0 if the offer couldn't be updated because it doesn't exist
int updateOfferDestination(Service* s, char* destination, char* departureDate, char* newDestination);

/// <summary>
/// Updates the an Offer from the repository.
/// <param s= "Offer Service", Service*>
/// <param destination= "destination of Offer", char*>
/// <param departureDate= "departureDate of Offer", char*>
/// <param newDeparture= "new departure of Offer", char*>
/// <returns> 1 if the offer was successfully updated
/// <returns> 0 if the offer couldn't be updated because it doesn't exist
int updateOfferDeparture(Service* s, char* destination, char* departureDate, char* newDeparture);

/// <summary>
/// Updates the an Offer from the repository.
/// <param s= "Offer Service", Service*>
/// <param destination= "destination of Offer", char*>
/// <param departureDate= "departureDate of Offer", char*>
/// <param newPrice= "new price of Offer", duble>
/// <returns> 1 if the offer was successfully updated
/// <returns> 0 if the offer couldn't be updated because it doesn't exist
int updateOfferPrice(Service* s, char* destination, char* departureDate, double newPrice);

/// <summary>
/// Filters offers from the current repo by destination having a keyword and creates a new auxiliary repo.
/// <param s= "Offer Service", Service*>
/// <param keyword= "searched key in destination of Offers", char[]>
/// <returns> auxiliary repo containing the offers that satisfy the condition
OfferRepository* filterByKeyWord(Service* s, char keyword[]);

/// <summary>
/// Filters offers from the current repo by type and creates a new auxiliary repo.
/// <param s= "Offer Service", Service*>
/// <param type[]= "type of Offers", char[]>
/// <returns> auxiliary repo containing the offers that satisfy the condition
OfferRepository* filterByType(Service* s, char type[]);

/// <summary>
/// Filters offers from the current repo by having the integer part of price a prime number.
/// <param s= "Offer Service", Service*>
/// <param type[]= "type of Offers", char[]>
/// <returns> auxiliary repo containing the offers that satisfy the condition
OfferRepository* filterByPrimePrice(Service* s);

/// <summary>
/// Filters offers from the current repo by type having departure date after a given date and creates a new auxiliary repo.
/// <param s= "Offer Service", Service*>
/// <param type[]= "type of Offers", char[]>
/// <param departureDate[]= "departure date of Offers", char[]>
/// <returns> auxiliary repo containing the offers that satisfy the condition
OfferRepository* findOffersAfterDate(Service* s, char type[], char departureDate[]);

/// <summary>
/// Sorts ascending by price the offers from the repo.
/// <param s= "Offer Service", Service*>
/// <param repo= "Offer repo", OfferRepository*>
/// <returns> sorted repo, OfferRepository*
OfferRepository* sortRepositoryByPriceAscending(Service* s, OfferRepository* repo);

/// <summary>
/// Sorts ascending by destination the offers from the repo.
/// <param s= "Offer Service", Service*>
/// <param repo= "Offer repo", OfferRepository*>
/// <returns> sorted repo, OfferRepository*
OfferRepository* sortByDestinationAscending(Service* s, OfferRepository* repo);

/// <summary>
/// Sorts descending by destination the offers from the repo.
/// <param s= "Offer Service", Service*>
/// <param repo= "Offer repo", OfferRepository*>
/// <returns> sorted repo, OfferRepository*
OfferRepository* sortByDestinationDescending(Service* s, OfferRepository* repo);

/// <summary>
/// Undoes the last performed operation.
/// <param s= "Offer Service", Service*>
/// <param repo= "Offer repo", OfferRepository*>
/// <returns> 1 - success; -1 - error; 0 - no more undos
int undoCommandPattern(Service* s);

/// <summary>
/// Redoes the last performed operation.
/// <param s= "Offer Service", Service*>
/// <param repo= "Offer repo", OfferRepository*>
/// <returns> 1 - success; -1 - error; 0 - no more redos
int redoCommandPattern(Service* s);