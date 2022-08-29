#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "validation.h"
#pragma once

UI* createUI(Service* srv)
{
    UI* ui = malloc(sizeof(UI));
    if (ui == NULL)
        return NULL;

    ui->srv = srv;
    return ui;
}

void destroyUI(UI* ui)
{
    if (ui == NULL)
        return;

    // first destroy the service, then free up the memory
    destroyService(ui->srv);
    free(ui);
}

int readUserCommand()
{
    char input[11] = { 0 };
    int finishReading = 0, result = 0;

    while (finishReading == 0)
    {
        printf("Please select an option from the menu: ");
        int scanfResult = scanf("%10s", input);
        result = isInteger(input);
        if (result == -1)
            printf("Input Error: selected option must be an integer number!\n");
        else
            finishReading = 1;
    }
    return result;
}

void readOfferType(char* type)
{
    char temp;
    int validType = 0;
    int scanf_result = -1;
    while (validType == 0)
    {
        printf("   Input the type of Offer(seaside, mountain or city break): ");
        scanf_result = scanf("%c", &temp); // temp statement to clear buffer
        scanf_result = scanf("%[^\n]50s", type);
        if (isEmptyString(type) == 1)
            printf("Input error: type of Offer cannot be empty!\n");
        else
        {
            trimWhiteSpace(type);
            lowerString(type);
            validType = validateOfferType(type);
            if (validType == 0)
                printf("Input error: type of offer can be: seaside, mountain or city break!\n");
        }
    }
}

void readOfferDestination(char* destination)
{
    char temp;
    int scanf_result = -1;
    int validDestination = 0;
    while (validDestination == 0)
    {
        printf("   Input the destination of Offer: ");
        scanf_result = scanf("%c", &temp); // temp statement to clear buffer
        scanf_result = scanf("%[^\n]50s", destination);
        if (isEmptyString(destination) == 1)
            printf("Input error: destination of Offer cannot be empty!\n");
        else
        {
            trimWhiteSpace(destination);
            lowerString(destination);
            validDestination = 1;
        }
    }
}

void readOfferDepartureDate(char* departureDate)
{
    char day[5] = { 0 }, month[5] = { 0 }, year[5] = { 0 };
    int scanf_result = -1;
    int valid;

    valid = 0;
    while (valid == 0)
    {
        printf("   Input the departure day of Offer: ");
        scanf_result = scanf("%50s", day);
        if (isEmptyString(day) == 1)
            printf("Input error: day of departure cannot be empty!\n");
        else
        {
            trimWhiteSpace(day);
            valid = validateDepartureDay(day);
        }
    }
    if (atoi(day) <= 9)
        strcat(departureDate, "0");
    strcat(departureDate, day);
    strcat(departureDate, "/");

    valid = 0;
    while (valid == 0)
    {
        printf("   Input the departure month of Offer: ");
        scanf_result = scanf("%50s", month);
        if (isEmptyString(month) == 1)
            printf("Input error: month of departure cannot be empty!\n");
        else
        {
            trimWhiteSpace(month);
            valid = validateDepartureMonth(month);
        }
    }
    if (atoi(month) <= 9)
        strcat(departureDate, "0");
    strcat(departureDate, month);
    strcat(departureDate, "/");

    valid = 0;
    while (valid == 0)
    {
        printf("   Input the departure year of Offer: ");
        scanf_result = scanf("%50s", year);
        if (isEmptyString(year) == 1)
            printf("Input error: year of departure cannot be empty!\n");
        else
        {
            trimWhiteSpace(year);
            valid = validateDepartureYear(year);
        }
    }
    strcat(departureDate, year);
}

double readOfferPrice()
{
    char offerPrice[52] = { 0 };
    double price = 0;
    int scanf_result = -1;
    int validPrice = 0;
    while (validPrice == 0)
    {
        printf("   Input the price of Offer: ");
        scanf_result = scanf("%50s", offerPrice);
        validPrice = validateOfferPrice(offerPrice);
    }
    price = atof(offerPrice);
    return price;
}

void readSortType(char* sort)
{
    char temp;
    int scanf_result = -1;
    int validSorting = 0;
    while (validSorting == 0)
    {
        printf("   Input type of sort for destination(a for ascending and d for descending): ");
        scanf_result = scanf("%c", &temp); // temp statement to clear buffer
        scanf_result = scanf("%[^\n]10s", sort);
        if (isEmptyString(sort) == 1)
            printf("Input error: sorting type cannot be empty!\n");
        else
        {
            trimWhiteSpace(sort);
            lowerString(sort);
            validSorting = validateSortType(sort);
        }
    }
}

void displayAllOffers(UI* ui)
{
    if (ui == NULL)
        return;
    OfferRepository* repo = getRepository(ui->srv);
    if (repo == NULL)
        return;
    if (getSize(repo) == 0)
    {
        printf("There are no offers in the repository!\n");
        return;
    }

    printf("\nOffers:\n");
    int i;
    for (i = 0; i < getSize(repo); i++)
    {
        Offer* offer = getOfferOnPosition(repo, i);
        char offerToPrint[251] = "";
        toString(offer, offerToPrint);
        printf("%s\n", offerToPrint);
    }
}

int addOfferRun(UI* ui)
{
    char type[51] = { 0 }, destination[51] = { 0 }, departureDate[51] = { 0 };
    double price = 0;

    readOfferType(type);
    readOfferDestination(destination);
    readOfferDepartureDate(departureDate);
    price = readOfferPrice();

    return addOffer(ui->srv, type, destination, departureDate, price);
}

int deleteOfferRun(UI* ui)
{
    char destination[51] = { 0 }, departureDate[51] = { 0 };

    readOfferDestination(destination);
    readOfferDepartureDate(departureDate);
    return deleteOffer(ui->srv, destination, departureDate);
}

int updateOfferRun(UI* ui)
{
    int scanf_result = -1, valid = 0;
    char destination[51] = { 0 }, departureDate[51] = { 0 }, option[51] = { 0 };
    char newType[51] = { 0 }, newDeparture[51] = { 0 }, newDestination[51] = { 0 }, temp;
    double newPrice = 0;

    printf("Please input data of the offer you wish to update!\n");
    readOfferDestination(destination);
    readOfferDepartureDate(departureDate);

    printf("\n What do you want to update?\n");
    printf("Choose between: type, destination, departure and price: ");
    while (valid == 0)
    {
        scanf_result = scanf("%c", &temp); // temp statement to clear buffer
        scanf_result = scanf("%[^\n]50s", option);

        trimWhiteSpace(option);
        lowerString(option);
        if (strcmp(option, "type") == 0)
        {
            valid = 1;
            readOfferType(newType);
            return updateOfferType(ui->srv, destination, departureDate, newType);
        }
        else
            if (strcmp(option, "destination") == 0)
            {
                valid = 1;
                readOfferDestination(newDestination);
                return updateOfferDestination(ui->srv, destination, departureDate, newDestination);
            }
            else
                if (strcmp(option, "departure") == 0)
                {
                    valid = 1;
                    readOfferDepartureDate(newDeparture);
                    return updateOfferDeparture(ui->srv, destination, departureDate, newDeparture);
                }
                else
                    if (strcmp(option, "price") == 0)
                    {
                        valid = 1;
                        newPrice = readOfferPrice();
                        return updateOfferPrice(ui->srv, destination, departureDate, newPrice);
                    }
                    else
                    {
                        printf("Input error: you can only update an offer's type, destination, departure or price!\n");
                    }
    }
    return 1;
}

int undoRun(UI* ui)
{
    return undoCommandPattern(ui->srv);
}

int redoRun(UI* ui)
{
    return redoCommandPattern(ui->srv);
}

void filterOffersRun(UI* ui)
{
    char key[51], offerToPrint[201];
    int scanf_result = -1, i;
    printf("Search for offers whose whose destination contain the a given string:\n");
    printf("   Input the searched string: ");
    scanf_result = scanf("%50s", key);
    key[strlen(key)] = '\0';
    trimWhiteSpace(key);
    lowerString(key);
    if (strcmp(key, "null") == 0)
        displayAllOffers(ui);
    else
    {
        OfferRepository* repo = filterByKeyWord(ui->srv, key);
        OfferRepository* sortedRepo;
        if (getSize(repo) == 0)
        {
            printf("Sorry! No offers matching the requested keyword!\n");
        }
        else
        {
            sortedRepo = sortRepositoryByPriceAscending(ui->srv, repo);
            for (i = 0; i < getArraySize(sortedRepo->offers); i++)
            {
                toString(getElement(sortedRepo->offers, i), offerToPrint);
                printf("%s\n", offerToPrint);
            }
            destroyRepository(sortedRepo);
        }
        destroyRepository(repo);
    }
}

void displaySortedByDestination(UI* ui)
{
    if (ui == NULL)
        return;
    OfferRepository* repo = getRepository(ui->srv);
    if (repo == NULL)
        return;
    if (getSize(repo) == 0)
    {
        printf("There are no offers in the repository!\n");
        return;
    }

    printf("\nOffers sorted ascending by destination:\n");
    char offerToPrint[201];
    OfferRepository* copy = copyRepo(repo);
    OfferRepository* sortedRepo = sortByDestinationAscending(ui->srv, copy);
    for (int i = 0; i < getArraySize(sortedRepo->offers); i++)
    {
        toString(getElement(sortedRepo->offers, i), offerToPrint);
        printf("%s\n", offerToPrint);
    }
    destroyRepository(copy);
    destroyRepository(sortedRepo);
}

void displayGivenTypeAfterDate(UI* ui)
{
    char offerToPrint[201] = "";
    char type[51] = { 0 }, departureDate[51] = { 0 }, sort[11] = { 0 };
    readOfferType(type);
    readOfferDepartureDate(departureDate);
    readSortType(sort);
    OfferRepository* result = findOffersAfterDate(ui->srv, type, departureDate);
    if (getSize(result) == 0)
        printf("Sorry! There are no offers of type %s having their departure time after %s!\n", type, departureDate);
    else {
        if (strcmp(sort, "a") == 0) {
            OfferRepository* sortedRepo = sortByDestinationAscending(ui->srv, result);
            printf("Offers of type %s, having their departure time after %s are, sorted ascending by destination:\n",
                type, departureDate);
            for (int i = 0; i < getArraySize(result->offers); i++) {
                toString(getElement(result->offers, i), offerToPrint);
                printf("%s\n", offerToPrint);
            }
            destroyRepository(sortedRepo);
        }
        else {
            OfferRepository* sortedRepo = sortByDestinationDescending(ui->srv, result);
            printf("Offers of type %s, having their departure time after %s are, sorted descending by destination:\n",
                type, departureDate);
            for (int i = 0; i < getArraySize(result->offers); i++) {
                toString(getElement(result->offers, i), offerToPrint);
                printf("%s\n", offerToPrint);
            }
            destroyRepository(sortedRepo);
        }
    }
    destroyRepository(result);
}

void displayGivenTypeAfterDateFunctionPointers(UI* ui)
{
    char offerToPrint[201] = "";
    char type[51] = { 0 }, departureDate[51] = { 0 }, sort[11] = { 0 };
    readOfferType(type);
    readOfferDepartureDate(departureDate);
    readSortType(sort);
    OfferRepository* (*function_pointer)(Service*, char[], char[]) = &findOffersAfterDate;   /// syntax: return_type (*function_name)(arguments)
    OfferRepository* result = (*function_pointer)(ui->srv, type, departureDate);
    if (getSize(result) == 0)
        printf("Sorry! There are no offers of type %s having their departure time after %s!\n", type, departureDate);
    else {
        if (strcmp(sort, "a") == 0)
        {
            OfferRepository* (*pointer_sortAsc)(Service*, OfferRepository*) = &sortByDestinationAscending;
            OfferRepository* sortedRepo = (*pointer_sortAsc)(ui->srv, result);
            printf("Offers of type %s, having their departure time after %s are, sorted ascending by destination:\n",
                type, departureDate);
            for (int i = 0; i < getArraySize(result->offers); i++) {
                toString(getElement(result->offers, i), offerToPrint);
                printf("%s\n", offerToPrint);
            }
            destroyRepository(sortedRepo);
        }
        else
        {
            OfferRepository* (*pointer_sortDesc)(Service*, OfferRepository*) = &sortByDestinationDescending;
            OfferRepository* sortedRepo = (*pointer_sortDesc)(ui->srv, result);
            printf("Offers of type %s, having their departure time after %s are, sorted descending by destination:\n",
                type, departureDate);
            for (int i = 0; i < getArraySize(result->offers); i++) {
                toString(getElement(result->offers, i), offerToPrint);
                printf("%s\n", offerToPrint);
            }
            destroyRepository(sortedRepo);
        }
    }
    destroyRepository(result);
}

void displayPrimePriceOffers(UI* ui)
{
    char offerToPrint[151] = "";
    OfferRepository* result = filterByPrimePrice(ui->srv);
    if (getSize(result) == 0)
        printf("Sorry! There are no offers whose integer part of price is a prime number!\n");
    else
    {
        OfferRepository* sortedRepo = sortRepositoryByPriceAscending(ui->srv, result);
        printf("Offers whose integer part of price is a prime number, sorted ascending by price, are:\n");
        for (int i = 0; i < getArraySize(sortedRepo->offers); i++)
        {
            toString(getElement(sortedRepo->offers, i), offerToPrint);
            printf("%s\n", offerToPrint);
        }
        destroyRepository(sortedRepo);
    }
    destroyRepository(result);
}

void displayPrimePriceOffersFunctionPointers(UI* ui)
{
    char offerToPrint[151] = "";
    OfferRepository* (*function_ptr)(Service*) = &filterByPrimePrice;   /// syntax: return_type (*function_name)(arguments)
    OfferRepository* result = (*function_ptr)(ui->srv);
    if (getSize(result) == 0)
        printf("Sorry! There are no offers whose integer part of price is a prime number!\n");
    else
    {
        OfferRepository* sortedRepo = sortRepositoryByPriceAscending(ui->srv, result);
        printf("Offers whose integer part of price is a prime number, sorted ascending by price, are:\n");
        for (int i = 0; i < getArraySize(sortedRepo->offers); i++)
        {
            toString(getElement(sortedRepo->offers, i), offerToPrint);
            printf("%s\n", offerToPrint);
        }
        destroyRepository(sortedRepo);
    }
    destroyRepository(result);
}

void populate(UI* ui)
{
    addOffer(ui->srv, "seaside", "antalya", "12/08/2018", 1087.50);
    addOffer(ui->srv, "mountain", "mount everest", "22/02/2022", 1009.75);
    addOffer(ui->srv, "seaside", "tenerife", "07/06/2019", 1555.45);
    addOffer(ui->srv, "city break", "rome", "28/05/2022", 1400.00);
    addOffer(ui->srv, "seaside", "ibiza", "11/07/2022", 2070.55);
    addOffer(ui->srv, "mountain", "switzerland", "15/03/2022", 875.75);
    addOffer(ui->srv, "city break", "madrid", "13/09/2022", 701.90);
    addOffer(ui->srv, "mountain", "tatra mountains", "12/09/2022", 555.55);
    addOffer(ui->srv, "city break", "stockholm", "16/10/2020", 690.90);
    addOffer(ui->srv, "seaside", "zakynthos", "09/06/2022", 1700.80);
    addOffer(ui->srv, "seaside", "mamaia", "13/08/2021", 207.67);
    addOffer(ui->srv, "mountain", "himalaya", "17/01/2023", 978.88);
    addOffer(ui->srv, "seaside", "bali", "16/06/2024", 2333.24);
    addOffer(ui->srv, "city break", "oslo", "07/05/2018", 773.90);
    addOffer(ui->srv, "city break", "cluj-napoca", "28/11/2020", 408.78);

    ui->srv->undoStack->size = 0;
    ui->srv->redoStack->size = 0;
}

void printMenu()
{
    printf("\n------------------------------------------------------------------------------------------------------------------------\n");
    printf("Menu:\n");
    printf("   Press 0 to exit the application.\n");
    printf("   Press 1 to add an offer.\n");
    printf("   Press 2 to delete an offer.\n");
    printf("   Press 3 to update an offer.\n");
    printf("   Press 4 to display all offers.\n");
    printf("   Press 5 to display all tourism offers whose destinations contain a given string, sorted ascending by price.\n");
    printf("   Press 6 to display all tourism offers, sorted ascending by destination.\n");
    printf("   Press 7 to display all tourism offers of a given type, having their departure after a given date.\n");
    printf("   Press 8 to display all tourism offers whose integer part of price is a prime number, sorted ascending by price.\n");
    printf("   Press 9 to undo the last performed operation.\n");
    printf("   Press 10 to redo the last performed operation.\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

void startUI(UI* ui)
{
    printf("Welcome to your Tourism Agency app!\n");
    populate(ui);
    int running = 1;

    while (running)
    {
        printMenu();
        int command = readUserCommand();
        while (validateUserCommand(command) == 0)
        {
            printf("Please input a valid command (between 1 and 5)!\n");
            command = readUserCommand();
        }
        if (command == 0)
            running = 0;

        switch (command)
        {
        case 1:
        {
            int addResult = addOfferRun(ui);
            if (addResult == 1)
                printf("Offer added successfully!\n");
            else
                printf("Repository error: duplicate destination and departure date! Offer couldn't be added!\n");
            break;
        }
        case 2:
        {
            int deleteResult = deleteOfferRun(ui);
            if (deleteResult == 1)
                printf("Offer deleted successfully!\n");
            else
                printf("Repository error: non-existent offer! Couldn't be deleted!\n");
            break;
        }
        case 3:
        {
            int updateResult = updateOfferRun(ui);
            if (updateResult == 1)
                printf("Offer updated successfully!\n");
            else
                printf("Repository error: non-existent offer! Couldn't be updated!\n");
            break;
        }
        case 4:
        {
            displayAllOffers(ui);
            break;
        }
        case 5:
        {
            filterOffersRun(ui);
            break;
        }
        case 6:
        {
            displaySortedByDestination(ui);
            break;
        }
        case 7:
        {
            displayGivenTypeAfterDateFunctionPointers(ui);
            break;
        }
        case 8:
        {
            displayPrimePriceOffersFunctionPointers(ui);
            break;
        }
        case 9:
        {
            int undoResult = undoRun(ui);
            if (undoResult == 1)
                printf("Operation undone successfully!\n");
            else
                if (undoResult == 0)
                    printf("Cannot undo anymore!\n");
                else
                    printf("Undo error: cannot undo last operation!\n");
            break;
        }
        case 10:
        {
            int redoResult = redoRun(ui);
            if (redoResult == 1)
                printf("Operation redone successfully!\n");
            else
                if (redoResult == 0)
                    printf("Cannot redo anymore!\n");
                else
                    printf("Redo error: cannot redo last operation!\n");
            break;
        }
        default:
        {
            break;
        }
        }
    }
}

void trimWhiteSpace(char* s)
{
    int i;

    //cut whitespaces at beginning of string
    i = 0;
    while (i < strlen(s))
    {
        if (s[i] == ' ' || s[i] == '\t')
            i++;
        else
            break;
    }

    // cut trailing whitespaces
    i = (int)strlen(s) - 1;
    while (i > 0)
    {
        if (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
            i--;
        else
            break;
    }
    s[i + 1] = '\0';  // put NULL at end of string
}

void lowerString(char* s)
{
    int i = 0;
    while (i < strlen(s))
    {
        if (s[i] >= 'A' && s[i] <= 'Z') // lowercase
            s[i] = s[i] + 32;
        i++;
    }
}