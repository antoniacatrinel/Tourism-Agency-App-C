#pragma once

/// Structure Offer that holds pointers to a type (one of seaside, mountain or city break), a destination, a departure date and a price.
typedef struct
{
	char* type;
	char* destination;
	char* departureDate;
	double price;
}Offer;


/// <summary>
/// Creates an Offer (= allocates the necessary memory) and returns a pointer to it
/// </summary>
/// <param name="type">type of Offer, char*</param>
/// <param name="destination">destination of Offer, char*</param>
/// <param name="departureDate">departure date of Offer, char*</param>
/// <param name="price">price of Offer, double</param>
/// <returns>a pointer to the created offer, NULL if allocation was unsuccessful and deallocates used memory</returns>
Offer* createOffer(char* type, char* destination, char* departureDate, double price);

/// <summary>
/// Deallocates the memory occupied by an Offer o
/// </summary>
/// <param name="o">offer, Offer*</param>
void destroyOffer(Offer* o);

/// <summary>
/// Returns the type of an Offer o
/// </summary>
/// <param name="o">offer, Offer*</param>
/// <returns>type of o, char*</returns>
char* getType(Offer* o);

/// <summary>
/// Returns the destination of an Offer o
/// </summary>
/// <param name="o">offer, Offer*</param>
/// <returns>destination of o, char*</returns>
char* getDestination(Offer* o);

/// <summary>
/// Returns the departure date of an Offer o
/// </summary>
/// <param name="o">offer, Offer*</param>
/// <returns>departure date of o, char</returns>
char* getDepartureDate(Offer* o);

/// <summary>
/// Returns the price of an Offer o
/// </summary>
/// <param name="o">offer, Offer*</param>
/// <returns>price of o, double</returns>
double getPrice(Offer* o);

/// <summary>
/// Store the string containing the fields of an offer o in a buffer for printing
/// </summary>
/// <param name="o">offer, Offer*</param>
/// <param name="str">buffer that holds printing version of o</param>
void toString(Offer* o, char str[]);

/// <summary>
/// Creates a copy of a given offer
/// </summary>
/// <param name="OfferToCopy">offer to be coppied, Offer*</param>
/// <returns>copy of offer o, Offer*</returns>
Offer* copyOffer(Offer* OfferToCopy);