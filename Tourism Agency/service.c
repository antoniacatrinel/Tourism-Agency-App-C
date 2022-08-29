#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "service.h"
#include "repository.h"
#include "operation.h"

struct dates
{
    int day;
    int month;
    int year;
};

Service* createService(OfferRepository* r, DynamicArray* undoStack, DynamicArray* redoStack)
{
    Service* s = malloc(sizeof(Service));
    if (s == NULL)
        return NULL;

    s->repo = r;
    s->undoStack = undoStack;
    s->redoStack = redoStack;
    return s;
}

void destroyService(Service* s)
{
    if (s == NULL)
        return;

    destroyRepository(s->repo);
    destroyArray(s->undoStack);
    destroyArray(s->redoStack);
    free(s);
}

OfferRepository* getRepository(Service* s)
{
    if (s == NULL)
        return NULL;

    return s->repo;
}

void cleanStack(DynamicArray* stack)
{
    int i;
    for (i = 0; i < getArraySize(stack); i++)
        deleteElem(stack, i);
    stack->size = 0;
}

int addOffer(Service* s, char* type, char* destination, char* departureDate, double price)
{
    if (search(s->repo, destination, departureDate) != -1)
        return 0;  

    Offer* o = createOffer(type, destination, departureDate, price);

    if (o != NULL)
    {
        int result = add(s->repo, o);
        // if the offer couldn't be added, destroy it - free the allocated & unused memory
        if (result == 0)
            destroyOffer(o);
        if (result == 1) // offer was added
        {
            Operation* opUndo = createOperation(ADD, o);
            if (opUndo == NULL)
            {
                destroyOffer(o);
                return 0;
            }
            addElem(s->undoStack, opUndo); // add to undo
            // clean redoStack
            destroyArray(s->redoStack);
            s->redoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
            s->redoStack->size = 0;
            destroyOperation(opUndo);
        }
        return result;
    }
    return 0;
}

int deleteOffer(Service* s, char* destination, char* departureDate)
{
    Offer* o = findByDestDeparture(s->repo, destination, departureDate);
    if (o != NULL)
    {
        Operation* opUndo = createOperation(DELETE, o);
        if (opUndo == NULL)
            return 0;
        addElem(s->undoStack, opUndo);
        destroyArray(s->redoStack);
        s->redoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
        s->redoStack->size = 0;
    }
    return delete(s->repo, destination, departureDate);
}

int updateOfferType(Service* s, char* destination, char* departureDate, char* newType)
{
    int pos = search(s->repo, destination, departureDate);
    if (pos == -1)  // offer does not exist
        return 0;

    Offer* foundOffer = findByDestDeparture(s->repo, destination, departureDate);
    if (foundOffer == NULL)
        return 0;

    Operation* opUndo = createOperation(UPDATETYPE, foundOffer);
    if (opUndo == NULL)
        return 0;
    addElem(s->undoStack, opUndo);
    destroyArray(s->redoStack);
    s->redoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    s->redoStack->size = 0;

    Offer* offerToUpdate = createOffer(newType, destination, departureDate, foundOffer->price);

    update(s->repo, offerToUpdate, pos);
    destroyOffer(offerToUpdate);
    return 1;
}

int updateOfferDestination(Service* s, char* destination, char* departureDate, char* newDestination)
{
    int pos = search(s->repo, destination, departureDate);
    if (pos == -1)  // offer does not exist
        return 0;

    Offer* foundOffer = getOfferOnPosition(s->repo, pos);
    if (foundOffer == NULL)
        return 0;

    Operation* opUndo = createOperation(UPDATEDESTINATION, foundOffer);
    if (opUndo == NULL)
        return 0;
    addElem(s->undoStack, opUndo);
    destroyArray(s->redoStack);
    s->redoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    s->redoStack->size = 0;

    Offer* offerToUpdate = createOffer(foundOffer->type, newDestination, departureDate, foundOffer->price);

    update(s->repo, offerToUpdate, pos);
    destroyOffer(offerToUpdate);
    return 1;
}

int updateOfferDeparture(Service* s, char* destination, char* departureDate, char* newDeparture)
{
    int pos = search(s->repo, destination, departureDate);
    if (pos == -1)  // offer does not exist
        return 0;

    Offer* foundOffer = getOfferOnPosition(s->repo, pos);
    if (foundOffer == NULL)
        return 0;

    Operation* opUndo = createOperation(UPDATEDEPARTURE, foundOffer);
    if (opUndo == NULL)
        return 0;
    addElem(s->undoStack, opUndo);
    destroyArray(s->redoStack);
    s->redoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    s->redoStack->size = 0;

    Offer* offerToUpdate = createOffer(foundOffer->type, destination, newDeparture, foundOffer->price);

    update(s->repo, offerToUpdate, pos);
    destroyOffer(offerToUpdate);
    return 1;
}

int updateOfferPrice(Service* s, char* destination, char* departureDate, double newPrice)
{
    int pos = search(s->repo, destination, departureDate);
    if (pos == -1)  // offer does not exist
        return 0;

    Offer* foundOffer = getOfferOnPosition(s->repo, pos);
    if (foundOffer == NULL)
        return 0;

    Operation* opUndo = createOperation(UPDATEPRICE, foundOffer);
    if (opUndo == NULL)
        return 0;
    addElem(s->undoStack, opUndo);
    destroyArray(s->redoStack);
    s->redoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    s->redoStack->size = 0;

    Offer* offerToUpdate = createOffer(foundOffer->type, destination, departureDate, newPrice);

    update(s->repo, offerToUpdate, pos);
    destroyOffer(offerToUpdate);
    return 1;
}

int undoCommandPattern(Service* s)
{
    if (s == NULL)
        return -1;  // error

    int stackSize = getArraySize(s->undoStack);
    if (stackSize == 0)  // no more undos
        return 0;

    Operation* op = getElement(s->undoStack, stackSize - 1);
    if (op == NULL)
        return -1;  // error

    Offer* o = getOperationObject(op);
    if (o == NULL)
        return -1;  // error

    if (getOperationType(op) == ADD)
    {
        delete(s->repo, getDestination(o), getDepartureDate(o));
        addElem(s->redoStack, copyOperation(op)); // remove the operation from "the stack" & add to redo stack
        deleteElem(s->undoStack, stackSize - 1);
    }
    else
        if (getOperationType(op) == DELETE)
        {
            add(s->repo, copyOffer(o)); // we use a copy, because o will be destroyed when deleting the operation from the stack
            addElem(s->redoStack, copyOperation(op)); // remove the operation from "the stack" & add to redo stack
            deleteElem(s->undoStack, stackSize - 1);
        }
        else
            if (getOperationType(op) == UPDATETYPE)  //update was made
            {
                int pos = search(s->repo, getDestination(o), getDepartureDate(o));   // updated offer
                Offer* current = getOfferOnPosition(s->repo, pos);
                Offer* copy = copyOffer(o);
                Operation* opRedo = createOperation(UPDATETYPE, current);
                addElem(s->redoStack, copyOperation(opRedo));
                update(s->repo, copy, pos);  // initial one
                deleteElem(s->undoStack, stackSize - 1);
                destroyOperation(opRedo);
                destroyOffer(copy);
                destroyOffer(o);
                destroyOperation(op);
            }
            else
                if (getOperationType(op) == UPDATEDESTINATION)
                {
                    int pos = searchByTypePrice(s->repo, getType(o), getPrice(o));
                    Offer* current1 = getOfferOnPosition(s->repo, pos);
                    Offer* copy = copyOffer(o);
                    Operation* opRedo1 = createOperation(UPDATEDESTINATION, current1);
                    addElem(s->redoStack, copyOperation(opRedo1));
                    update(s->repo, copy, pos);  // initial one
                    deleteElem(s->undoStack, stackSize - 1);
                    destroyOperation(opRedo1);
                    destroyOffer(copy);
                    destroyOffer(o);
                    destroyOperation(op);
                }
                else
                    if (getOperationType(op) == UPDATEDEPARTURE)
                    {
                        int pos = searchByTypePrice(s->repo, getType(o), getPrice(o));
                        Offer* current2 = getOfferOnPosition(s->repo, pos);
                        Offer* copy = copyOffer(o);
                        Operation* opRedo2 = createOperation(UPDATEDEPARTURE, current2);
                        addElem(s->redoStack, copyOperation(opRedo2));
                        update(s->repo, copy, pos);  // initial one
                        deleteElem(s->undoStack, stackSize - 1);
                        destroyOperation(opRedo2);
                        destroyOffer(copy);
                        destroyOffer(o);
                        destroyOperation(op);
                    }
                    else
                        if (getOperationType(op) == UPDATEPRICE)
                        {
                            int pos = search(s->repo, getDestination(o), getDepartureDate(o));
                            Offer* current3 = getOfferOnPosition(s->repo, pos);
                            Offer* copy = copyOffer(o);
                            Operation* opRedo3 = createOperation(UPDATEPRICE, current3);
                            addElem(s->redoStack, copyOperation(opRedo3));
                            update(s->repo, copy, pos);  // initial one
                            deleteElem(s->undoStack, stackSize - 1);
                            destroyOperation(opRedo3);
                            destroyOffer(copy);
                            destroyOffer(o);
                            destroyOperation(op);
                        }
    return 1;  // success
}

int redoCommandPattern(Service* s)
{
    if (s == NULL)
        return -1;  // error

    int stackSize = getArraySize(s->redoStack);
    if (stackSize == 0)  // no more redos
        return 0;

    Operation* op = getElement(s->redoStack, stackSize - 1);
    if (op == NULL)
        return -1;  // error

    Offer* o = getOperationObject(op);
    if (o == NULL)
        return -1;  // error

    if (getOperationType(op) == ADD)
    {
        add(s->repo, copyOffer(o));
        addElem(s->undoStack, copyOperation(op));   // remove the operation from "the stack"
        deleteElem(s->redoStack, stackSize - 1);   // should be added to the undo stack
    }
    else
        if (getOperationType(op) == DELETE)
        {
            delete(s->repo, getDestination(o), getDepartureDate(o)); // we use a copy, because o will be destroyed when deleting the operation from the stack
            addElem(s->undoStack, copyOperation(op));
            deleteElem(s->redoStack, stackSize - 1);
        }
        else
            if (getOperationType(op) == UPDATETYPE)
            {
                int pos = search(s->repo, getDestination(o), getDepartureDate(o));  // initial one
                Offer* current = getOfferOnPosition(s->repo, pos);
                Offer* copy = copyOffer(o);
                Operation* opUndo = createOperation(UPDATETYPE, current);
                addElem(s->undoStack, copyOperation(opUndo));
                update(s->repo, copy, pos);
                deleteElem(s->redoStack, stackSize - 1);
                destroyOperation(opUndo);
                destroyOffer(copy);
                destroyOffer(o);
                destroyOperation(op);
            }
            else
                if (getOperationType(op) == UPDATEDESTINATION)
                {
                    int pos = searchByTypePrice(s->repo, getType(o), getPrice(o));
                    Offer* current1 = getOfferOnPosition(s->repo, pos);
                    Offer* copy = copyOffer(o);
                    Operation* opUndo1 = createOperation(UPDATEDESTINATION, current1);
                    addElem(s->undoStack, copyOperation(opUndo1));
                    update(s->repo, copy, pos);
                    deleteElem(s->redoStack, stackSize - 1);
                    destroyOperation(opUndo1);
                    destroyOffer(copy);
                    destroyOffer(o);
                    destroyOperation(op);
                }
                else
                    if (getOperationType(op) == UPDATEDEPARTURE)
                    {
                        int pos = searchByTypePrice(s->repo, getType(o), getPrice(o));
                        Offer* current2 = getOfferOnPosition(s->repo, pos);
                        Offer* copy = copyOffer(o);
                        Operation* opUndo2 = createOperation(UPDATEDEPARTURE, current2);
                        addElem(s->undoStack, copyOperation(opUndo2));
                        update(s->repo, copy, pos);
                        deleteElem(s->redoStack, stackSize - 1);
                        destroyOperation(opUndo2);
                        destroyOffer(copy);
                        destroyOffer(o);
                        destroyOperation(op);
                    }
                    else
                        if (getOperationType(op) == UPDATEPRICE)
                        {
                            int pos = search(s->repo, getDestination(o), getDepartureDate(o));
                            Offer* current3 = getOfferOnPosition(s->repo, pos);
                            Offer* copy = copyOffer(o);
                            Operation* opUndo3 = createOperation(UPDATEPRICE, current3);
                            addElem(s->undoStack, copyOperation(opUndo3));
                            update(s->repo, copy, pos);
                            deleteElem(s->redoStack, stackSize - 1);
                            destroyOperation(opUndo3);
                            destroyOffer(copy);
                            destroyOffer(o);
                            destroyOperation(op);
                        }
    return 1;  // success
}

OfferRepository* filterByKeyWord(Service* s, char keyword[])
{
    OfferRepository* filterRepo = createRepository();

    OfferRepository* repo = s->repo;
    int i;
    char destination[151];
    for (i = 0; i < getArraySize(repo->offers); i++)
    {
        strcpy(destination, getDestination(getElement(repo->offers, i)));
        lower(destination);
        if (strstr(destination, keyword) != NULL)
            add(filterRepo, copyOffer(getElement(repo->offers, i)));
    }
    return filterRepo;
}

OfferRepository* filterByType(Service* s, char type[])
{
    OfferRepository* filterRepo = createRepository();

    OfferRepository* repo = s->repo;
    int i;
    char offerType[151];
    for (i = 0; i < getArraySize(repo->offers); i++)
    {
        strcpy(offerType, getType(getElement(repo->offers, i)));
        lower(offerType);
        if (strcmp(offerType, type) == 0)
            add(filterRepo, copyOffer(getElement(repo->offers, i)));
    }
    return filterRepo;
}

OfferRepository* filterByPrimePrice(Service* s)
{
    OfferRepository* filterRepo = createRepository();

    OfferRepository* repo = s->repo;
    int i;
    int price;
    for (i = 0; i < getArraySize(repo->offers); i++)
    {
        price = (int)getPrice(getElement(repo->offers, i));  // integer part of price
        if (isPrime(price) == 1)
            add(filterRepo, copyOffer(getElement(repo->offers, i)));
    }
    return filterRepo;
}

OfferRepository* findOffersAfterDate(Service* s, char type[], char departureDate[])
{
    OfferRepository* filterRepo = createRepository();
    OfferRepository* offersFilteredByType = filterByType(s, type);

    char depart[51] = "";
    int i;
    for (i = 0; i < getArraySize(offersFilteredByType->offers); i++)
    {
        strcpy(depart, getDepartureDate(getElement(offersFilteredByType->offers, i)));
        if (compareDates(depart, departureDate) == 1)
            add(filterRepo, copyOffer(getElement(offersFilteredByType->offers, i)));
    }
    destroyRepository(offersFilteredByType);
    return filterRepo;
}

OfferRepository* sortRepositoryByPriceAscending(Service* s, OfferRepository* repo)
{
    Offer* auxOffer;
    int i, sorted;
    do  // Bubble sort
    {
        sorted = 1;
        for (i = 0; i < (getArraySize(repo->offers) - 1); i++)
            if (getPrice(getElement(repo->offers, i)) > getPrice(getElement(repo->offers, i + 1)))
            {
                auxOffer = getElement(repo->offers, i);
                updateElem(repo->offers, i, getElement(repo->offers, i + 1));
                updateElem(repo->offers, i + 1, auxOffer);
                sorted = 0;
            }

    } while (sorted == 0);
    return repo;
}


OfferRepository* sortByDestinationAscending(Service* s, OfferRepository* repo)
{
    Offer* auxOffer;
    int i, sorted = 1;
    do  // Bubble sort
    {
        sorted = 1;
        for (i = 0; i < (getArraySize(repo->offers) - 1); i++)
            if (strcmp(getDestination(getElement(repo->offers, i)), getDestination(getElement(repo->offers, i + 1))) > 0)
            {
                auxOffer = getElement(repo->offers, i);
                updateElem(repo->offers, i, getElement(repo->offers, i + 1));
                updateElem(repo->offers, i + 1, auxOffer);
                sorted = 0;
            }
    } while (sorted == 0);
    return repo;
}

OfferRepository* sortByDestinationDescending(Service* s, OfferRepository* repo)
{
    Offer* auxOffer;
    int i, sorted = 1;
    do  // Bubble sort
    {
        sorted = 1;
        for (i = 0; i < (getArraySize(repo->offers) - 1); i++)
            if (strcmp(getDestination(getElement(repo->offers, i)), getDestination(getElement(repo->offers, i + 1))) < 0)
            {
                auxOffer = getElement(repo->offers, i);
                updateElem(repo->offers, i, getElement(repo->offers, i + 1));
                updateElem(repo->offers, i + 1, auxOffer);
                sorted = 0;
            }
    } while (sorted == 0);
    return repo;
}

/// <summary>
/// Converts a string to date format
/// </summary>
time_t convertStringToDate(char* s)
{
    char str[51] = "";
    strcpy(str, s);
    struct tm str_time = { 0 };
    time_t date;
    int val, counter = 1;
    char* p;
    const char sep[2] = "/";
    p = strtok(str, sep);
    while (p != NULL)
    {
        val = atoi(p);
        if (counter == 1) // day
            str_time.tm_mday = val;
        else
            if (counter == 2) // month
                str_time.tm_mon = val;
            else // year
                str_time.tm_year = val - 1900;
        counter++;
        p = strtok(NULL, sep);
    }
    date = mktime(&str_time);
    time(&date);
    return date;
}

/// <summary>
/// Compares two dates
/// </summary>
int isDateAfter(time_t date1, time_t date2)
{
    double seconds = difftime(date1, date2);
    printf("%lf\n", seconds);
    if (seconds > 0)
        return 1;
    return 0;
}

/// <summary>
/// Compares 2 strings in format dd/mm/yyyy
/// /// </summary>
/// <returns> -1 if s1 < s2
///            0 if s1 = s2
///            1 if s1 > s2</returns>
int compareDates(char* s1, char* s2)
{
    struct dates d1 = { 0 }, d2 = { 0 };
    int val, counter = 1;
    char str1[51] = "", str2[51] = "", * p;
    strcpy(str1, s1);  // make a copy of the initial strings
    strcpy(str2, s2);
    p = strtok(str1, "/");
    while (p != NULL)
    {
        val = atoi(p);
        if (counter == 1) // day
            d1.day = val;
        else
            if (counter == 2) // month
                d1.month = val;
            else // year
                d1.year = val;
        counter++;
        p = strtok(NULL, "/");
    }

    counter = 1;
    p = strtok(str2, "/");
    while (p != NULL)
    {
        val = atoi(p);
        if (counter == 1) // day
            d2.day = val;
        else
            if (counter == 2) // month
                d2.month = val;
            else // year
                d2.year = val;
        counter++;
        p = strtok(NULL, "/");
    }
    if (d1.year < d2.year)
        return -1;
    else
        if (d1.year > d2.year)
            return 1;
        else // d1.year == d2.year
            if (d1.month < d2.month)
                return -1;
            else
                if (d1.month > d2.month)
                    return 1;
                else // d1.month == d2.month
                    if (d1.day < d2.day)
                        return -1;
                    else
                        if (d1.day > d2.day)
                            return 1;
                        else  // d1.day == d2.day
                            return 0;
}

/// <summary>
/// Tests the primality of a number
/// </summary>
int isPrime(int x)
{
    if (x < 2)
        return 0;
    if (x % 2 == 0 && x != 2)
        return 0;
    int d;
    for (d = 3; d * d <= x; d += 2)
        if (x % d == 0)
            return 0;
    return 1;
}

/// <summary>
/// Converts a string to lowercase
/// </summary>
void lower(char* s)
{
    int i = 0;
    while (i < strlen(s))
    {
        if (s[i] >= 'A' && s[i] <= 'Z') // lowercase
            s[i] = s[i] + 32;
        i++;
    }
}