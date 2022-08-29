#pragma once

/// <summary>
/// Validates the command received from the user
/// </summary>
int validateUserCommand(int command);

/// <summary>
/// Validates the offer type
/// </summary>
int validateOfferType(char* type);

/// <summary>
/// Validates the offer departure day
/// </summary>
int validateDepartureDay(char* day);

/// <summary>
/// Validates the offer departure month
/// </summary>
int validateDepartureMonth(char* month);

/// <summary>
/// Validates the offer departure year
/// </summary>
int validateDepartureYear(char* year);

/// <summary>
/// Validates the offer price
/// </summary>
int validateOfferPrice(char* price);

/// <summary>
/// Validates the sort type
/// </summary>
int validateSortType(char* sort);

/// <summary>
/// Checks if a string is empty
/// </summary>
int isEmptyString(char* s);

/// <summary>
/// Checks if a number is integer
/// </summary>
int isInteger(char* x);

/// <summary>
/// Checks if a number is double
/// </summary>
double isDouble(char* x);
