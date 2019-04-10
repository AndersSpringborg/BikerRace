#include "allIncludes.h"

void opgave3(structParticipant* _participant)
{
    int participantCounter = 0;
    structIdandPoints* topParticipants;
    
    topParticipants = gatherParticipants(_participant, &participantCounter);

    qsort(topParticipants, participantCounter, sizeof(structIdandPoints), pointCompare);

    printTopParticipants(topParticipants);
    free(topParticipants);
}

int pointCompare(const void *a, const void *b)
{
    structIdandPoints *pa = (structIdandPoints*)a,
                      *pb = (structIdandPoints*)b;
    if (pa->points < pb->points) return 1;
    else if (pb->points < pa->points) return -1;
    else return 0;
}

int lastnameCompare(const void *a, const void *b)
{
    structIdandPoints *pa = (structIdandPoints *)a,
                      *pb = (structIdandPoints *)b;
    int strValue = strcmp(pa->lastname, pb->lastname);
    
    if (strValue < 0) return 1;
    else if (strValue > 0) return -1;
    else return 0;
}

void printTopParticipants(structIdandPoints *_participant)
{
    int i;
    for (i = 0; i < _TOP_TEN; i++)
    {
        printf("Last name: %-35s point: %2d i: %3d\n", _participant[i].lastname, _participant[i].points, i);
    }
}

structIdandPoints *gatherParticipants(structParticipant *_participant, int *participantCounter)
{
    int i;
    structIdandPoints *topParticipants;
    topParticipants = (structIdandPoints *)malloc(sizeof(structIdAndRace));

    
    for(i = 0; i < _AMOUNT_PARTICIPANT; i++)
    {
        if (duplicateIDPOINTS(_participant[i], topParticipants, (*participantCounter) +1) != 1) 
        {
            topParticipants = (structIdandPoints *)realloc(topParticipants, ((*participantCounter) + 1) * sizeof(structIdAndRace));
            topParticipants[*participantCounter].id = _participant[i];
            topParticipants[*participantCounter].points = topParticipants[*participantCounter].id.points;
            (*participantCounter)++;
        }
    }

    assignLastname(topParticipants, *participantCounter);
    return topParticipants;
}

void assignLastname (structIdandPoints* _participant, int counter)
{
    int i, j, strlengh;
    for(i = 0; i < counter; i++)
    {
        strlengh = strlen(_participant[i].id.nameParticipant);
        for(j = 0; j < strlengh; j++)
        {

            if (isupper(_participant[i].id.nameParticipant[j]) && isupper(_participant[i].id.nameParticipant[j+1]))
            {
                strncpy(_participant[i].lastname, _participant[i].id.nameParticipant + j, strlengh - j);
                break;
            }
        }
    }   
}

int duplicateIDPOINTS (structParticipant _compareStruct, structIdandPoints* _array, int arraySize)
{
    int i;
    for(i = 0; i < arraySize; i++)
    {
        if (strcmp(_compareStruct.nameParticipant, _array[i].id.nameParticipant) == 0)
        {
            _array[i].points += _compareStruct.points;
            return 1;
        }
    }
    return 0;
}
