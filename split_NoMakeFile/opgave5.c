#include "allIncludes.h"

void opgave5 (structParticipant* _participant) 
{
    double average = calculateAverage(_participant);
    printf("Average of the top ten riders, across all races is: %2.2lf\n", average);
}

double calculateAverage(structParticipant *_participant)
{
    int i, *indexParticipant, sizeArray = 0;
    double average = 0;
    indexParticipant = (int *)malloc(sizeof(int));

    for(i = 0; i < _AMOUNT_PARTICIPANT; i++)
    {   
        if (topTen(_participant[i]) && duplicateParticipant(_participant, i, indexParticipant, sizeArray) == 0)
        {
            average += _participant[i].age;
            indexParticipant = (int *)realloc(indexParticipant, (sizeArray + 1) * sizeof(int));
            indexParticipant[sizeArray++] = i;
        }   
    }
    free(indexParticipant);
    return (average /= sizeArray);
}

int topTen (structParticipant _participant)
{
    if (atoi(_participant.placement) >= 1 && atoi(_participant.placement) <= 10) return 1;
    else return 0;
}

int duplicateParticipant (structParticipant* _participant, int index, int* indexParticipant, int sizeArray){
    int i;
    printf("index: %d, ip: %d sa: %d\n", index, indexParticipant[0], sizeArray);
    for(i = 0; i < sizeArray; i++)
    {
        if (strcmp(_participant[indexParticipant[i]].nameParticipant, _participant[index].nameParticipant) == 0) return 1;
    }
    return 0;
}
