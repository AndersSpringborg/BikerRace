#include "allIncludes.h"

void opgave4(structParticipant * _participant){
    int riderNumber = 0, bestTime, hour, min, sec;
    
    bestTime = bestRider(&riderNumber, _participant, "ParisRoubaix", "AmstelGoldRace");
    

    hour = bestTime / _SECOUNDS_IN_HOUR;
    min = (bestTime % _SECOUNDS_IN_HOUR) /_SECOUNDS_IN_MIN;
    sec = ((bestTime % _SECOUNDS_IN_HOUR) % _SECOUNDS_IN_MIN);

    printf("The quickest rider is :%-35s\n"
           "With the time gathered time at %2d:%.2d:%.2d\n"
           ,_participant[riderNumber].nameParticipant, hour, min, sec);
}

int bestRider(int *riderNumber, structParticipant* _participant, char* firstCity, char* secoundCity)
{
    int i ,tempCounter = 0, duplicateIndex, bestTime;
    struct tm tempStruct;
    structTimeSum *gatheredTime;    
    gatheredTime = (structTimeSum*)malloc(sizeof(structTimeSum));

    for(i = 0; i < _AMOUNT_PARTICIPANT; i++)
    {

        if (inCities("ParisRoubaix", "AmstelGoldRace", _participant, i, &duplicateIndex))
        {
            gatheredTime = (structTimeSum *) realloc(gatheredTime, (tempCounter + 1) * sizeof(structTimeSum));
            gatheredTime[tempCounter].indexId = i;

            sscanf(_participant[i].finishTime, "%d:%d:%d", &tempStruct.tm_hour, &tempStruct.tm_min, &tempStruct.tm_sec);
            gatheredTime[tempCounter].timeSum = (tempStruct.tm_hour * _SECOUNDS_IN_HOUR) + (tempStruct.tm_min * _SECOUNDS_IN_MIN) + tempStruct.tm_sec;

            sscanf(_participant[duplicateIndex].finishTime, "%d:%d:%d", &tempStruct.tm_hour, &tempStruct.tm_min, &tempStruct.tm_sec);
            gatheredTime[tempCounter++].timeSum += (tempStruct.tm_hour * _SECOUNDS_IN_HOUR) + (tempStruct.tm_min * _SECOUNDS_IN_MIN) + tempStruct.tm_sec;
        }
    }
    qsort(gatheredTime, tempCounter, sizeof(structTimeSum), timeCompare);
    
    *riderNumber = gatheredTime[0].indexId;
    bestTime = gatheredTime[0].timeSum;
    free(gatheredTime);
    
    return bestTime;
}

int inCities (char *firstCity, char *secoundCity, structParticipant *_participant, int i, int *index)
{
    if (strcmp(firstCity, _participant[i].nameRace) == 0 && strcmp("DNF", _participant[i].placement) != 0)
    {
        for (*index = 0; *index < _AMOUNT_PARTICIPANT; (*index)++)
        {
            if (strcmp(secoundCity, _participant[*index].nameRace) == 0 && 
                strcmp(_participant[i].nameParticipant, _participant[*index].nameParticipant) == 0 &&
                strcmp ("DNF", _participant[*index].placement) != 0)
            {
                return 1;   
            }
        }
    }
    return 0;
}

int timeCompare(const void *a, const void *b)
{
    structTimeSum *pa = (structTimeSum *)a,
                  *pb = (structTimeSum *)b;
    
    if (pa->timeSum > pb->timeSum) return 1;
    else if(pa->timeSum < pb->timeSum) return -1;
    else return 0;
}
