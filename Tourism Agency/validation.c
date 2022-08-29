#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validateUserCommand(int command)
{
	return command >= 0 && command <= 10;
}

int isEmptyString(char* s)
{
	return strlen(s) == 0;
}

int isInteger(char* x)
{
	int result = 0, xx = 0;

	// reads data from x and stores it as integer in xx, if possible; returns 1 if successful
	result = sscanf(x, "%d", &xx);
	if (result == 1)  // x is integer
		return xx;
	return -1;
}

double isDouble(char* x)
{
	int result = 0;
	double xx = 0;

	// reads data from x and stores it as double in xx, if possible; returns 1 if successful
	result = sscanf(x, "%lf", &xx);
	if (result == 1)  // x is double
		return xx;
	return -1;
}

int validateOfferType(char* type)
{
	if (strcmp(type, "seaside") == 0 || strcmp(type, "mountain") == 0 || strcmp(type, "city break") == 0)
		return 1;
	return 0;
}

int validateDepartureDay(char* day)
{
	int valid = 1, offerDay = 0;
	if (isInteger(day) == -1)
	{
		printf("Input error: day of departure must be integer!\n");
		valid = 0;
	}
	else
	{
		offerDay = atoi(day);  // atoi() converts char* to int
		if (offerDay < 1 || offerDay > 30)
		{
			printf("Input error: day of departure must be integer between 1 and 30!\n");
			valid = 0;
		}
	}
	return valid;
}

int validateDepartureMonth(char* month)
{
	int valid = 1, offerMonth = 0;
	if (isInteger(month) == -1)
	{
		printf("Input error: month of departure must be integer!\n");
		valid = 0;
	}
	else
	{
		offerMonth = atoi(month); // atoi() converts char* to int
		if (offerMonth < 1 || offerMonth > 12)
		{
			printf("Input error: month of departure must be integer between 1 and 12!\n");
			valid = 0;
		}
	}
	return valid;
}

int validateDepartureYear(char* year)
{
	int valid = 1, offerYear = 0;
	if (isInteger(year) == -1)
	{
		printf("Input error: year of departure must be integer!\n");
		valid = 0;
	}
	else
	{
		offerYear = atoi(year); // atoi() converts char* to int
		if (offerYear < 2000 || offerYear > 2100)
		{
			printf("Input error: year of departure must be integer between 2000 and 2100!\n");
			valid = 0;
		}
	}
	return valid;
}

int validateOfferPrice(char* price)
{
	if (isDouble(price) == -1)
	{
		printf("Input error: price must be a rational number!\n");
		return 0;
	}
	return 1;
}

int validateSortType(char* sort)
{
	if (strlen(sort) != 1)
	{
		printf("Input error: sort type can only be 'a' or 'd'!\n");
		return 0;
	}
	if (strcmp(sort, "a") == 0 || strcmp(sort, "d") == 0)
		return 1;
	else
	{
		printf("Input error: sort type can only be 'a' or 'd'!\n");
		return 0;
	}
}