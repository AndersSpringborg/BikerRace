#include "allIncludes.h"

void opgave2(structParticipant *_participant)
{
    int danes = 0;
    structIdAndRace *danishRider;

    danishRider = finishrace("DEN", _participant, &danes);
    printStructIdAndRace(_participant, danishRider, danes);
    free(danishRider);
}

structIdAndRace *finishrace(char *_nation, structParticipant *_participant, int *_dane)
{
    int i, index;
    structIdAndRace *danishRider;
    danishRider = (structIdAndRace *) malloc(sizeof(structIdAndRace));    

    for (i = 0; i < _AMOUNT_PARTICIPANT; i++)
    {
        printf("i: %d\n", i);
        if (strcmp(_nation, _participant[i].nation) == 0 &&
            strcmp("DNF", _participant[i].placement) != 0)
        {
            printf("if DEN i: %d\n", i);
            if (duplicateParticipant(_participant, i, &index, *_dane)) 
            {
                printf("dupli i: %d\n", i);
                danishRider[index].racesComplete++;
            }
            else
            {
                printf("else i: %d\n", i);
                danishRider = (structIdAndRace *)realloc(danishRider, ((*_dane) + 1) * sizeof(structIdAndRace));
                danishRider[*_dane].id = i;
                danishRider[(*_dane)++].racesComplete = 1;
            }
            printf("i: %d\n", i);
        }
    }
    return danishRider;
}

void printStructIdAndRace(structParticipant *_participant, structIdAndRace *idAndRace, int _numberOfDanes)
{
    int i;
    for (i = 0; i < _numberOfDanes; i++)
    {
        printf("%-35s races completed: %d", _participant[idAndRace[i].id].nameParticipant, idAndRace[i].racesComplete);
    }
}
