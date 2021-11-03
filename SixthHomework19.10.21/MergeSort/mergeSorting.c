#include "mergeSorting.h"
#include <stdio.h>
#include <stdlib.h>

List* mergeSorting(List* list, List* buffer, Position* leftBoarder,
                   Position* rightBoarder, Priority priority)
{
    if (leftBoarder->position == rightBoarder->position)
    {
        return list;
    }
    if (leftBoarder->position->next == rightBoarder->position)
    {
        if (!isFirstEarlier(getPriorityValue(leftBoarder, priority) ,
                            getPriorityValue(rightBoarder, priority)))
        {
            char* name1 = getPriorityValue(leftBoarder, name);
            char* phone1 = getPriorityValue(leftBoarder, phone);
            changePriorityValue(leftBoarder,
                                getPriorityValue(rightBoarder, name),
                                name);
            changePriorityValue(leftBoarder,
                                getPriorityValue(rightBoarder, phone),
                                phone);
            changePriorityValue(rightBoarder, name1,name);
            changePriorityValue(rightBoarder, phone1,phone);
        }
        return list;
    }

    int lengthOfSegment = lengthPartOfList(leftBoarder, rightBoarder);
    Position* newRightBoarder = createPosition();
    Position* newLeftBoarder = createPosition();
    if (newLeftBoarder == NULL || newRightBoarder == NULL)
    {
        free(newRightBoarder);
        free(newLeftBoarder);
        return NULL;
    }
    

    mergeSorting(list, buffer, leftBoarder, newRightBoarder, priority);
    mergeSorting(list, buffer, leftBoarder, newRightBoarder, priority);

}