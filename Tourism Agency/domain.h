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
/// Creates an Offer (= allocates the necessary memory) and returns a pointer to it.
/// <param type= "type of Offer", char*>
/// <param destination= "destination of Offer", char*>
/// <param departureDate= "departureDate of Offer", char*>
/// <param price= "price of Offer", double>
/// <returns> a pointer to the created offer, NULL if allocation was unsuccessful and deallocates used memory
Offer* createOffer(char* type, char* destination, char* departureDate, double price);

/// <summary>
/// Deallocates the memory occupied by an Offer o.
/// <param o= "Offer", Offer*>
/// <returns> nothing
void destroyOffer(Offer* o);

/// <summary>
/// Gets the type of an Offer o.
/// <param o= "Offer", Offer*>
/// <returns> type of o, char*
char* getType(Offer* o);

/// <summary>
/// Gets the destination of an Offer o.
/// <param o= "Offer", Offer*>
/// <returns> destination of o, char*
char* getDestination(Offer* o);

/// <summary>
/// Gets the departure date of an Offer o.
/// <param o= "Offer", Offer*>
/// <returns> deaprture date of o, char*
char* getDepartureDate(Offer* o);

/// <summary>
/// Gets the price of an Offer o.
/// <param o= "Offer", Offer*>
/// <returns> price of o, double
double getPrice(Offer* o);

/// <summary>
/// Pretty prints the fields of an Offer o.
/// <param o= "Offer", Offer*>
/// <param str[]= "string that holds print version of o", char>
/// <returns> nothing
void toString(Offer* o, char str[]);

/// Creates a copy of a given offer
Offer* copyOffer(Offer* OfferToCopy);