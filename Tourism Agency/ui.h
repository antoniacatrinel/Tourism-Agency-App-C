#pragma once
#include "service.h"

// Structure UI that holds a pointer to the user interface.
typedef struct
{
	Service* srv;
} UI;

/// <summary>
/// Creates an user interface (= allocates the necessary memory) and returns a pointer to it.
/// <param srv= "Offer Service", Service*>
/// <returns> a pointer to the created ui, NULL if allocation was unsuccessful
UI* createUI(Service* srv);

/// <summary>
/// Deallocates the memory occupied by the UI.
/// <param ui= "user interface", UI*>
/// <returns> nothing
void destroyUI(UI* ui);

/// <summary>
/// Starts the application.
/// <param ui= "user interface", UI*>
/// <returns> nothing
void startUI(UI* ui);

/// add a few offer instances to the repo
void populate(UI* ui);

int addOfferRun(UI* ui);

int deleteOfferRun(UI* ui);

int updateOfferRun(UI* ui);