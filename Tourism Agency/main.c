#include <stdio.h>
#include "ui.h"
#include "tests.h"
#include "operation.h"

int main()
{
    runAllTests();
    printf("%s\n", "All tests passed!");

    OfferRepository* repo = createRepository();

    DynamicArray* undoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);
    DynamicArray* redoStack = createArray(CAPACITY, &destroyOperation, &copyOperation);

    Service* srv = createService(repo, undoStack, redoStack);

    UI* ui = createUI(srv);

    startUI(ui);

    destroyUI(ui);

    return 0;
}