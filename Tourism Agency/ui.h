#pragma once
#include "service.h"

// Structure UI that holds a pointer to the user interface
typedef struct
{
	Service* srv;
} UI;

/// <summary>
/// Creates an user interface (= allocates the necessary memory) 
/// </summary>
/// <param name="srv">Offer Service, Service*</param>
/// <returns>a pointer to the created ui, NULL if allocation was unsuccessful</returns>
UI* createUI(Service* srv);

/// <summary>
/// Deallocates the memory occupied by the UI
/// </summary>
/// <param name="ui">user interface, UI*</param>
void destroyUI(UI* ui);

/// <summary>
/// Starts the application.
/// </summary>
/// <param name="ui">user interface, UI*>
void startUI(UI* ui);

/// <summary>
/// Populate the repository
/// </summary>
/// <param name="ui">user interface, UI*>
void populate(UI* ui);

/// <summary>
/// Adds a new offer the the repository
/// </summary>
/// <param name="ui">user interface, UI*>
int addOfferRun(UI* ui);

/// <summary>
/// Deletes an offer from the repository
/// </summary>
/// <param name="ui">user interface, UI*>
int deleteOfferRun(UI* ui);

/// <summary>
/// Updates an offer from the repository
/// </summary>
/// <param name="ui">user interface, UI*>
int updateOfferRun(UI* ui);

/// <summary>
/// Undoes the last performed operation
/// </summary>
/// <param name="ui">user interface, UI*>
int undoRun(UI* ui);

/// <summary>
/// Redoes the last performed operation
/// </summary>
/// <param name="ui">user interface, UI*>
int redoRun(UI* ui);