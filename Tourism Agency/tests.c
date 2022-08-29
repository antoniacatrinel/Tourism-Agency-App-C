#include <assert.h>
#include "tests.h"
#include "operation.h"
#include <string.h>


// tests for Dynamic Array structure
void testArray()
{
    DynamicArray* arr = createArray(2, &destroyOffer, &copyOffer);

    Offer* o1 = createOffer("seaside", "greece", "01/08/2026", 1890.80);
    Offer* o2 = createOffer("mountain", "bucovina", "14/03/2022", 340.90);
    Offer* o3 = createOffer("city break", "los angeles", "26/09/2023", 1200.50);
    assert(arr->capacity == 2);
    assert(arr->size == 0);

    addElem(arr, o1);
    addElem(arr, o2);
    assert(arr->capacity == 2);
    assert(arr->size == 2);

    addElem(arr, o3);
    assert(arr->size == 3);
    assert(arr->capacity == 4);

    destroyOffer(o3);
    destroyOffer(o2);
    destroyOffer(o1);
    destroyArray(arr);
}


// tests for domain
void testOffer()
{
    Offer* o = createOffer("city break", "barcelona", "28/04/2023", 1900.80);
    assert(o != NULL);

    destroyOffer(o);
}

void testGetters()
{
    Offer* o = createOffer("mountain", "bucovina", "19/05/2023", 500.45);

    assert(strcmp(getType(o), "mountain") == 0);
    assert(strcmp(getDestination(o), "bucovina") == 0);
    assert(strcmp(getDepartureDate(o), "19/05/2023") == 0);
    assert(getPrice(o) == 500.45);

    destroyOffer(o);
}

void testCopy()
{
    Offer* o = createOffer("mountain", "bucovina", "19/05/2023", 500.45);
    Offer* copy_o = copyOffer(o);

    assert(strcmp(getType(o), getType(copy_o)) == 0);
    assert(strcmp(getDestination(o), getDestination(copy_o)) == 0);
    assert(strcmp(getDepartureDate(o), getDepartureDate(copy_o)) == 0);
    assert(getPrice(o) == getPrice(copy_o));

    destroyOffer(copy_o);
    destroyOffer(o);
}


// tests for repository
void testSearch()
{
    OfferRepository* r = createRepository();
    Offer* o1 = createOffer("seaside", "hawaii", "16/06/2022", 2000.50);
    add(r, o1);
    Offer* o2 = createOffer("mountain", "bucovina", "19/05/2023", 500.45);
    add(r, o2);

    assert(search(r, "bucovina", "19/05/2023") == 1);
    assert(search(r, "hawaii", "16/06/2022") == 0);
    assert(search(r, "milano", "16/06/2022") == -1);
    destroyOffer(o1);
    destroyOffer(o2);
    destroyRepository(r);
}

void testAdd()
{
    OfferRepository* r = createRepository();
    assert(getSize(r) == 0);
    assert(getCapacity(r) == 10);
    Offer* o1 = createOffer("seaside", "hawaii", "16/06/2022", 2000.50);
    add(r, o1);

    assert(getSize(r) == 1);
    Offer* o2 = createOffer("mountain", "bucovina", "19/05/2023", 500.45);
    add(r, o2);

    assert(getSize(r) == 2);
    destroyOffer(o1);
    destroyOffer(o2);
    destroyRepository(r);
}

void testDelete()
{
    OfferRepository* r = createRepository();
    assert(getSize(r) == 0);
    assert(getCapacity(r) == 10);
    Offer* o1 = createOffer("seaside", "hawaii", "16/06/2022", 2000.50);
    add(r, o1);

    assert(getSize(r) == 1);
    Offer* o2 = createOffer("mountain", "bucovina", "19/05/2023", 500.45);
    add(r, o2);
    assert(getSize(r) == 2);
    assert(delete(r, "bucovina", "19/05/2023") == 1);
    assert(getSize(r) == 1);
    assert(delete(r, "macedonia", "19/05/2023") == 0);
    assert(getSize(r) == 1);
    destroyOffer(o1);
    destroyOffer(o2);
    destroyRepository(r);
}

void testUpdate()
{
    OfferRepository* r = createRepository();
    Offer* o = createOffer("seaside", "hawaii", "16/06/2022", 2000.50);
    add(r, o);
    assert(search(r, "hawaii", "16/06/2022") == 0);
    assert(strcmp(getDepartureDate(getElement(r->offers, 0)), "16/06/2022") == 0);
    Offer* newoff = createOffer("seaside", "hawaii", "19/08/2022", 2300.50);
    update(r, newoff, 0);
    assert(search(r, "hawaii", "19/08/2022") == 0);
    assert(search(r, "hawaii", "16/06/2022") == -1);
    assert(strcmp(getDepartureDate(getElement(r->offers, 0)), "19/08/2022") == 0);
    destroyOffer(o);
    destroyOffer(newoff);
    destroyRepository(r);
}


// tests for service
void testAddService()
{
    OfferRepository* r = createRepository();
    DynamicArray* undoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    DynamicArray* redoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    assert(getSize(r) == 0);
    Service* s = createService(r, undoStack, redoStack);
    assert(addOffer(s, "seaside", "hawaii", "16/06/2022", 2000.50) == 1);
    assert(getSize(r) == 1);
    assert(addOffer(s, "seaside", "hawaii", "16/06/2022", 2000.50) == 0);
    assert(getSize(r) == 1);
    destroyArray(undoStack);
    destroyArray(redoStack);
    destroyService(s);
}

void testDeleteService()
{
    OfferRepository* r = createRepository();
    assert(getSize(r) == 0);
    DynamicArray* undoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    DynamicArray* redoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    Service* s = createService(r, undoStack, redoStack);
    addOffer(s, "seaside", "hawaii", "16/06/2022", 2000.50);
    addOffer(s, "mountain", "bucovina", "19/05/2023", 500.45);
    assert(getSize(r) == 2);
    assert(deleteOffer(s, "bucovina", "19/05/2023") == 1);
    assert(getSize(r) == 1);
    assert(deleteOffer(s, "bucovina", "19/05/2023") == 0); 
    assert(deleteOffer(s, "milano", "19/05/2023") == 0);
    destroyArray(undoStack);
    destroyArray(redoStack);
    destroyService(s);
}

void testUpdateService()
{
    OfferRepository* r = createRepository();
    assert(getSize(r) == 0);
    DynamicArray* undoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    DynamicArray* redoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    Service* s = createService(r, undoStack, redoStack);

    addOffer(s, "seaside", "hawaii", "16/06/2022", 2000.50);
    assert(strcmp(getType(getElement(s->repo->offers, 0)), "seaside") == 0);
    assert(updateOfferType(s, "hawaii", "16/06/2022", "city break") == 1);
    assert(strcmp(getType(getElement(s->repo->offers, 0)), "city break") == 0);

    assert(strcmp(getDestination(getElement(s->repo->offers, 0)), "hawaii") == 0);
    assert(updateOfferDestination(s, "hawaii", "16/06/2022", "tenerife") == 1);
    assert(strcmp(getDestination(getElement(s->repo->offers, 0)), "tenerife") == 0);

    assert(strcmp(getDepartureDate(getElement(s->repo->offers, 0)), "16/06/2022") == 0);
    assert(updateOfferDeparture(s, "tenerife", "16/06/2022", "23/09/2024") == 1);
    assert(strcmp(getDepartureDate(getElement(s->repo->offers, 0)), "23/09/2024") == 0);

    assert(getPrice(getElement(s->repo->offers, 0)) == 2000.50);
    assert(updateOfferPrice(s, "tenerife", "23/09/2024", 3000) == 1);
    assert(getPrice(getElement(s->repo->offers, 0)) == 3000);

    assert(updateOfferType(s, "hawaii", "23/09/2024", "mountain") == 0);
    destroyArray(undoStack);
    destroyArray(redoStack);
    destroyService(s);
}

void testUndoRedo()
{
    OfferRepository* r = createRepository();
    assert(getSize(r) == 0);
    DynamicArray* undoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    DynamicArray* redoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    Service* s = createService(r, undoStack, redoStack);

    assert(getArrayCapacity(undoStack) == 10);
    assert(getArrayCapacity(redoStack) == 10);
    assert(getArraySize(undoStack) == 0);
    assert(getArraySize(redoStack) == 0);
    assert(getSize(r) == 0);
    addOffer(s, "seaside", "hawaii", "16/06/2022", 2000.50);
    assert(getArraySize(undoStack) == 1);
    assert(getSize(r) == 1);
    int res = undoCommandPattern(s);
    assert(res == 1);
    assert(getArraySize(redoStack) == 1);
    assert(getSize(r) == 0);
    int res2 = redoCommandPattern(s);
    assert(res2 == 1);
    assert(getSize(r) == 1);
    destroyArray(undoStack);
    destroyArray(redoStack);
    destroyService(s);
}

void testfilterByKeyWord()
{
    OfferRepository* r = createRepository();
    DynamicArray* undoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    DynamicArray* redoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    Service* s = createService(r, undoStack, redoStack);
    addOffer(s, "seaside", "hawaii", "16/06/2022", 2000.50);
    addOffer(s, "city break", "rome", "28/05/2022", 1400.00);
    addOffer(s, "seaside", "zakynthos", "09/06/2022", 1700.80);
    assert(getSize(r) == 3);

    OfferRepository* filtered2 = filterByKeyWord(s, "ii");
    assert(getSize(filtered2) == 1);
    destroyRepository(filtered2);

    OfferRepository* filtered3 = filterByKeyWord(s, "a");
    assert(getSize(filtered3) == 2);
    destroyRepository(filtered3);
    destroyArray(undoStack);
    destroyArray(redoStack);
    destroyService(s);
}

void testsortRepository()
{
    OfferRepository* r = createRepository();
    DynamicArray* undoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    DynamicArray* redoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    Service* s = createService(r, undoStack, redoStack);
    addOffer(s, "seaside", "hawaii", "16/06/2022", 2000.50);
    addOffer(s, "city break", "rome", "28/05/2022", 1400.00);
    addOffer(s, "seaside", "zakynthos", "09/06/2022", 1700.80);

    assert(getPrice(getElement(s->repo->offers, 0)) == 2000.50);
    assert(getPrice(getElement(s->repo->offers, 1)) == 1400.00);
    assert(getPrice(getElement(s->repo->offers, 2)) == 1700.80);

    OfferRepository* sorted = sortRepositoryByPriceAscending(s, r);
    assert(getPrice(getElement(s->repo->offers, 0)) == 1400.00);
    assert(getPrice(getElement(s->repo->offers, 1)) == 1700.80);
    assert(getPrice(getElement(s->repo->offers, 2)) == 2000.50);
    destroyArray(undoStack);
    destroyArray(redoStack);
    destroyService(s);
}

void runAllTests()
{
    testArray();
    testOffer();
    testGetters();
    testCopy();
    testSearch();
    testAdd();
    testDelete();
    testUpdate();
    testAddService();
    testDeleteService();
    testUpdateService();
    testfilterByKeyWord();
    testsortRepository();
    testUndoRedo();
}