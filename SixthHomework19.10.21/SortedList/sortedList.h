#pragma once
#include <stdbool.h>

// type of data that will be stored in the sortedList
typedef int Value;

// sortedList structure
typedef struct SortedList SortedList;

// created an empty sortedList
SortedList* createSortedList();

// checks if the sortedList is empty
bool sortedListIsEmpty(SortedList** head);

// created new element and returns it
SortedList* createNewElement(Value value, SortedList* next);

// adds an element to the sortedList
int push(SortedList** head, Value value);

// removes an element form the head of the sortedList and returns it
Value removeItemFromHead(SortedList** head, int* errorCode);

// removes the element with the specified value
// if there is no such element returns -1
int removeTheItem(SortedList** head, Value value);

// removes the entire sortedList
void deleteSortedList(SortedList** head);

// prints the entire sortedList
void printSortedList(SortedList** head);

// returns value from head of the SortedList
Value getValueFromHead(SortedList* head, int* errorCode);