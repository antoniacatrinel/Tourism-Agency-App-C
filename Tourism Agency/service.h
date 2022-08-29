#pragma once
#include "repository.h"

// Structure Service that holds a pointer to the offer repository, the undo and redo stacks
typedef struct
{
    OfferRepository* repo;
    DynamicArray* undoStack;
    DynamicArray* redoStack;
} Service;

/// <summary>
/// Creates an Offer Service (= allocates the necessary memory)
/// </summary>
/// <param name="r">Offer Repository, OfferRepository*</param>
/// <param name="undoStack">undo stack, DynamicArray*</param>
/// <param name="redoStack">redo stack, DynamicArray*</param>
/// <returns> a pointer to the created service, NULL if allocation was unsuccessful</returns>
Service* createService(OfferRepository* r, DynamicArray* undoStack, DynamicArray* redoStack);

/// <summary>
/// Deallocates the memory occupied by the Offer Sevice s
/// </summary>
/// <param name="s">Offer Service, Service*</param>
void destroyService(Service* s);

/// <summary>
/// Returns the offer repository
/// </summary>
/// <param name="s">Offer Service, Service*</param>
/// <returns>repo, OfferRepository*</returns>
OfferRepository* getRepository(Service* s);

/// <summary>
/// Adds an Offer to the repository
/// </summary>
/// <param name="s">Offer Service, Service*</param>
/// <param name="type">type of Offer, char*</param>
/// <param name="destination">destination of Offer, char*</param>
/// <param name="departureDate">departure date of Offer, char*</param>
/// <param name="price">price of Offer, double</param>
/// <returns> 1 if the offer was successfully added to the repo
///           0 if the offer couldn't be added to the repo because it is duplicated</returns>
int addOffer(Service* s, char* type, char* destination, char* departureDate, double price);

/// <summary>
/// Deletes an Offer from the repository
/// </summary>
/// <param name="s">Offer Service, Service*</param>
/// <param name="destination">destination of Offer, char*</param>
/// <param name="departureDate">departure date of Offer, char*</param>
/// <returns> 1 if the offer was successfully deleted from the repo
///           0 if the offer couldn't be deleted because it doesn't exist</returns>
int deleteOffer(Service* s, char* destination, char* departureDate);

/// <summary>
/// Updates the type of an Offer from the repository
/// </summary>
/// <param name="s">Offer Service, Service*</param>
/// <param name="destination">destination of Offer, char*</param>
/// <param name="departureDate">departure date of Offer, char*</param>
/// <param name="newType">new type of Offer, char*</param>
/// <returns> 1 if the offer was successfully updated
///           0 if the offer couldn't be updated because it doesn't exist</returns>
int updateOfferType(Service* s, char* destination, char* departureDate, char* newType);

/// <summary>
/// Updates the destination of an Offer from the repository
/// </summary>
/// <param name="s">Offer Service, Service*</param>
/// <param name="destination">destination of Offer, char*</param>
/// <param name="departureDate">departure date of Offer, char*</param>
/// <param name="newDestination">new destination of Offer, char*</param>
/// <returns> 1 if the offer was successfully updated
///           0 if the offer couldn't be updated because it doesn't exist</returns>
int updateOfferDestination(Service* s, char* destination, char* departureDate, char* newDestination);

/// <summary>
/// Updates the departure day of an Offer from the repository
/// </summary>
/// <param name="s">Offer Service, Service*</param>
/// <param name="destination">destination of Offer, char*</param>
/// <param name="departureDate">departure date of Offer, char*</param>
/// <param name="newDeparture">new departure date of Offer, char*</param>
/// <returns> 1 if the offer was successfully updated
///           0 if the offer couldn't be updated because it doesn't exist</returns>
int updateOfferDeparture(Service* s, char* destination, char* departureDate, char* newDeparture);

/// <summary>
/// Updates the price of an Offer from the repository
/// </summary>
/// <param name="s">Offer Service, Service*</param>
/// <param name="destination">destination of Offer, char*</param>
/// <param name="departureDate">departure date of Offer, char*</param>
/// <param name="newPrice">new price of Offer, double</param>
/// <returns> 1 if the offer was successfully updated
///           0 if the offer couldn't be updated because it doesn't exist</returns>
int updateOfferPrice(Service* s, char* destination, char* departureDate, double newPrice);


OfferRepository* filterByKeyWord(Service* s, char keyword[]);

/// <summary>
/// Filters offers from the current repo by destination having a keyword and creates a new auxiliary repo
/// </summary>
/// <param name="s">Offer Service, Service*</param>
/// <param name="type">searched key in destination of Offers, char[]</param>
/// <returns>auxiliary repo containing the offers that satisfy the condition</returns>
OfferRepository* filterByType(Service* s, char type[]);

/// <summary>
/// Filters offers from the current repo by having the integer part of price a prime number
/// </summary>
/// <param name="s">Offer Service, Service*</param>
/// <returns>auxiliary repo containing the offers that satisfy the condition</returns>
OfferRepository* filterByPrimePrice(Service* s);

/// <summary>
/// Filters offers from the current repo by type having departure date after a given date and creates a new auxiliary repo
/// </summary>
/// <param name="s">Offer Service, Service*</param>
/// <param name="type">type of Offers, char[]</param>
/// <param name="departureDate">departure date of Offers, char[]</param>
/// <returns>auxiliary repo containing the offers that satisfy the condition</returns>
OfferRepository* findOffersAfterDate(Service* s, char type[], char departureDate[]);

/// <summary>
/// Sorts ascending by price the offers from the repo
/// </summary>
/// <param name="s">Offer Service, Service*</param>
/// <param name="repo">Offer repo, OfferRepository*</param>
/// <returns>sorted repo, OfferRepository*</returns>
OfferRepository* sortRepositoryByPriceAscending(Service* s, OfferRepository* repo);


/// <summary>
/// Sorts ascending by destination the offers from the repo
/// </summary>
/// <param name="s">Offer Service, Service*</param>
/// <param name="repo">Offer repo, OfferRepository*</param>
/// <returns>sorted repo, OfferRepository*</returns>
OfferRepository* sortByDestinationAscending(Service* s, OfferRepository* repo);

/// <summary>
/// Sorts descending by destination the offers from the repo
/// </summary>
/// <param name="s">Offer Service, Service*</param>
/// <param name="repo">Offer repo, OfferRepository*</param>
/// <returns>sorted repo, OfferRepository*</returns>
OfferRepository* sortByDestinationDescending(Service* s, OfferRepository* repo);

/// <summary>
/// Undoes the last performed operation
/// <param name="s">Offer Service, Service*</param>
/// <returns> 1 - success; -1 - error; 0 - no more undos</returns>
int undoCommandPattern(Service* s);

/// <summary>
/// Redoes the last performed operation
/// <param name="s">Offer Service, Service*</param>
/// <returns> 1 - success; -1 - error; 0 - no more redos</returns>
int redoCommandPattern(Service* s);