#include "mergeSorting.h"



List* mergeSorting(List* list, List* buffer,
                   Position* leftBoarder, Position* rightBoarder)
{
    if (leftBoarder->position == rightBoarder->position)
    {
        return list;
    }
    if (leftBoarder->position->next == rightBoarder->position)
    {

    }
}