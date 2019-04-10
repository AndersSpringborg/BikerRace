#include "allIncludes.h"

void loadStruct (structParticipant* _participant) {
    /* Tildeler alle deltager en struct, som representere deres data.
        Sidst i funktionen, får alle struct tilddelt point, ud fra deres data*/
    int counter;
    FILE *filedata = fopen("cykelloeb", "r");
    for(counter = 0; counter < _AMOUNT_PARTICIPANT; counter++)
    {
        _participant[counter] = assignStruct(filedata);
    }
    fclose(filedata);
    loadPoints(_participant);
}

structParticipant assignStruct(FILE* _filedata){
    /*Indlæser rå data fra en tekst fil, og returner det data der er indlæst*/
    structParticipant result;

    fscanf(_filedata,
           " %[a-zA-Z]"            /*race*/
           " \" %[a-z\'A-Z -] \" " /*participant*/
           "| %d"                  /*age*/
           " %[A-Z]"               /*team*/
           " %[A-Z]"               /*nation*/
           " | %s"                 /*placement*/
           " %s",                  /*time*/
           result.nameRace, result.nameParticipant, &result.age, result.nameTeam, 
           result.nation, result.placement, result.finishTime);
    
    return result;
}

/*-------------------------- POINTS ------------------------*/
void loadPoints(structParticipant* _participant){
    completePoint(_participant);
    placementPoints(_participant);
    podiumPoints(_participant);
}

void completePoint(structParticipant* _participant){
    int i;
    for (i = 0; i < _AMOUNT_PARTICIPANT; i++)
    {
        _participant[i].points = 0;
        if (atoi(_participant[i].placement)) /*atoi laver string om til int. Hvis der er bogstaver, int er 0*/
        {
            _participant[i].points = 3;
        }
        else if (strcmp("OTL", _participant[i].placement) == 0)
        {
            _participant[i].points = 1;
        }
    }
}

void podiumPoints(structParticipant* _participant){
    int i;
    for (i = 0; i < _AMOUNT_PARTICIPANT; i++)
    {
        if (atoi(_participant[i].placement) == 1)
        {
            _participant[i].points += 10;
        }
        else if (atoi(_participant[i].placement) == 2)
        {
            _participant[i].points += 5;
        }
        else if (atoi(_participant[i].placement) == 3)
        {
            _participant[i].points += 2;
        }
    }
}

void placementPoints(structParticipant* _participant){
    int i,
        ParisRoubaix       = participantsInRace("ParisRoubaix", _participant),
        AmstelGoldRace     = participantsInRace("AmstelGoldRace", _participant),
        LaFlecheWallonne   = participantsInRace("LaFlecheWallonne", _participant),
        LiegeBastogneLiege = participantsInRace("LiegeBastogneLiege", _participant);

    for(i = 0; i < _AMOUNT_PARTICIPANT; i++)
    {
        if      (strcmp("ParisRoubaix", _participant[i].placement) == 0) pointCalculator(_participant, i, ParisRoubaix);
        else if (strcmp("AmstelGoldRace", _participant[i].placement) == 0) pointCalculator(_participant, i, AmstelGoldRace);
        else if (strcmp("LaLiegeBastogneLiege", _participant[i].placement) == 0)pointCalculator(_participant, i, LaFlecheWallonne);
        else pointCalculator(_participant, i, LiegeBastogneLiege);
    }
}

void pointCalculator(structParticipant* _participant, int i, int _raceParticipants)
{
    if (atoi(_participant[i].placement)){
        _participant[i].points += (_raceParticipants - (atoi(_participant[i].placement))) / 13;
    }
}

int participantsInRace(char* raceCity, structParticipant* _participant) {
    int i, result = 0;
    for(i = 0; i < _AMOUNT_PARTICIPANT; i++)
    {
        if (strcmp(raceCity, _participant[i].nameRace) == 0) 
        {
            result ++;
        }
    }
    return result;    
}
