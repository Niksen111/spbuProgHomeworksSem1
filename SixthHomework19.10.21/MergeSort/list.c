#include "list.h"
#include <stdlib.h>
#include <string.h>

typedef struct Directory
{
    char* name;
    char* phoneNumber;
} Directory;

typedef struct ListElement
{
    Directory* directory;
    struct ListElement* next;
} ListElement;

typedef struct List
{
    ListElement* head;
} List;

typedef struct Position
{
    ListElement* position;
} Position;


int min(const int first, const int second)
{
    return first < second ? first : second;
}

bool isFirstEarlier(char* first, char* second)
{
    int lengthOfShorterString = min(strlen(first), strlen(second));
    for (int i = 0; i < lengthOfShorterString; ++i)
    {
        if (first[i] < second[i])
        {
            return true;
        }
        if (first[i] > second[i])
        {
            return false;
        }
    }
    return strlen(first) <= strlen(second);
}

void changePriorityValue(Position* position, char* newValue, Priority priority)
{
    free(getPriorityValue(position, priority));
    if (priority == name)
    {
        position->position->directory->name = newValue;
    }
    else
    {
        position->position->directory->phoneNumber = newValue;
    }
}

List* createList()
{
    return calloc(1, sizeof(List));
}

Position* createPosition()
{
    return calloc(1, sizeof(Position));
}

void deleteList(List* list)
{
    ListElement* position = list->head;
    while (position != NULL)
    {
        list->head = list->head->next;
        free(position);
        position = list->head;
    }
    free(list);
}

void deletePosition(Position* position)
{
    free(position);
}

void add(List* list, Position* position, char* name, char* phone)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->directory->name = name;
    newElement->directory->phoneNumber = phone;
    if (position->position == NULL)
    {
        list->head = newElement;
        return;
    }
    newElement->next = position->position->next;
    position->position->next = newElement;
}

int lengthPartOfList(Position* start, Position* end)
{
    if (start == NULL)
    {
        return 0;
    }
    Position* position = calloc(1, sizeof(Position));
    if (position == NULL)
    {
        return -1;
    }
    position->position = start->position;
    int counter = 0;
    while (position != end)
    {
        if (position == NULL)
        {
            free(position);
            return -1;
        }
        ++counter;
        position = next(position);
    }
    free(position);
    return counter;
}

Position* first(List* list)
{
    Position* positionFirst = calloc(1, sizeof(Position));
    positionFirst->position = list->head;
    return positionFirst;
}

Position* next(Position* position)
{
    Position* newPosition = calloc(1, sizeof(Position));
    newPosition->position = position->position->next;
    return newPosition;
}

bool isLast(Position* position)
{
    return position->position == NULL;
}

ListElement* getListElement(Position* position)
{

}

Directory* getDirectory(List* list, Position* position)
{
    return position->position->directory;
}

char* getPriorityValue(Position* position, Priority priority)
{
    return priority == name ? position->position->directory->name :
           position->position->directory->phoneNumber;
}