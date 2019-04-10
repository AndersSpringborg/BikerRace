/*Anders Aaen Springborg - asprin18@student.aau.dk - A410 -SW1*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
/*------------------------Læsevejledning------------------------
 main           linje 106-115
 miscellaneous  linje 117-157   (bruger input)
 struct indlæs  linje 159-266
 opgave 1       linje 268-283
 opgave 2       linje 285-342
 opgave 3       linje 344-445
 opgave 4       linje 447-523
 opgave 5       linje 525-572
*/
/*---------------------- Defines --------------------*/
#define _AMOUNT_PARTICIPANT 790
#define _CHAR_SPACE 40
#define _LAST_NAME_SPACE 30
#define _BLUE "\x1B[34m"
#define _RESET "\x1B[0m"
#define _TOP_TEN 10
#define _SECOUNDS_IN_HOUR 3600                                                                              /*FEJL*//* kan ikke gange i defines*/
#define _SECOUNDS_IN_MIN 60

/*---------------------- Structs --------------------*/
typedef struct participant
{
    int age;
    char nameParticipant[_CHAR_SPACE],
        nation[_CHAR_SPACE];

    char nameRace[_CHAR_SPACE];
    char nameTeam[_CHAR_SPACE];
    char placement[_CHAR_SPACE];
    char finishTime[_CHAR_SPACE];

    int points;
} structParticipant;

typedef struct opgave2
{
    /*structParticipant id2;*/                                                                                 /*FEJL*//*bruges ikke*/
    int id;
    int racesComplete;
} structIdAndRace;

typedef struct opgave3
{
    structParticipant id;
    int points;
    char lastname[_LAST_NAME_SPACE];
} structIdandPoints;

typedef struct opgave4
{
    int indexId;
    int timeSum;
} structTimeSum;

/*------------------------------------------------prototyper--------------------------------------------*/          /*FEJL*/ /* nogle har navne, andre har ikke*/

int userSelect(int, int);
void assigmnetSelect(structParticipant *);
void loadStruct(structParticipant *);
structParticipant assignStruct(FILE *);
void doAllAssignments(structParticipant *_participant);

void loadPoints(structParticipant *);
void completePoint(structParticipant *);
void placementPoints(structParticipant *_participant);
void podiumPoints(structParticipant *_participant);
void pointCalculator(structParticipant *_participant, int i, int _raceParticipants);
int participantsInRace(char *, structParticipant *);

void opgave1(structParticipant *);
void findAndPrint(char *_nation, int age, structParticipant *_participant);

void opgave2(structParticipant *);
structIdAndRace *finishrace(char *, structParticipant *, int *);
void printStructIdAndRace(structParticipant *_participant, structIdAndRace *id, int _numberOfDanes);
int duplicateIdAndRace(structParticipant *_participant, int i, structIdAndRace *indexParticipant, int *index, int sizeArray);

void opgave3(structParticipant *);
structIdandPoints *gatherParticipantsPoints(structParticipant *, int *);
int duplicateIdAndPoints(structParticipant, structIdandPoints *, int);
void assignLastname(structIdandPoints *_participant, int counter);
int pointCompare(const void *, const void *);
int lastnameCompare(const void *a, const void *b);
void printTopParticipants(structIdandPoints *_participant);

void opgave4(structParticipant *);
int bestRider(int *riderNumber, structParticipant *_participant, char *firstCity, char *secoundCity);
struct tm scanner(structParticipant _participant);
int timeCompare(const void *a, const void *b);
int inCities(char *firstCity, char *secoundCity, structParticipant *_participant, int i, int *index);
void printBestTime(int bestTime, structParticipant _participant);

void opgave5(structParticipant *_participant);
int topTen(structParticipant _participant);
double calculateAverage(structParticipant *_participant);
int duplicateParticipant(structParticipant *_participant, int index, int *indexParticipant, int sizeArray);

/*-----------------------------MAIN------------------------------------------*/
int main(int nmb, char **input)
{
    structParticipant participant[_AMOUNT_PARTICIPANT];
    loadStruct(participant);

    if (nmb == 2 && strcmp(input[1], "--print") == 0)
        doAllAssignments(participant);
    else
        assigmnetSelect(participant);
    return 0;
}

/*---------------------------------------------- MISCELLANEOUS -------------------------------------------*/
void doAllAssignments(structParticipant *_participant)
{
    printf("---------------------------------------- " _BLUE "ASSIGNMENT 1" _RESET " ----------------------------------------\n");
    opgave1(_participant);
    printf("\n---------------------------------------- " _BLUE "ASSIGNMENT 2" _RESET " ----------------------------------------\n");
    opgave2(_participant);
    printf("\n---------------------------------------- " _BLUE "ASSIGNMENT 3" _RESET " ----------------------------------------\n");
    opgave3(_participant);
    printf("\n---------------------------------------- " _BLUE "ASSIGNMENT 4" _RESET " ----------------------------------------\n");
    opgave4(_participant);
    printf("\n---------------------------------------- " _BLUE "ASSIGNMENT 5" _RESET " ----------------------------------------\n");
    opgave5(_participant);
}

void assigmnetSelect(structParticipant *_participant)
{
    printf("Choose an assignment: [1], [2], [3], [4] or [5]\n :");
    switch (userSelect(1, 5))               /*FEJL*/ /* konstante */
    {
    case 1:
        opgave1(_participant);
        break;
    case 2:
        opgave2(_participant);
        break;
    case 3:
        opgave3(_participant);
        break;
    case 4:
        opgave4(_participant);
        break;
    case 5:
        opgave5(_participant);
        break;
    default:
        printf("You didn't input a correct assignment\n");
        break;
    }
}

int userSelect(int _lower, int _upper)
{
    int userinput;
    do
    {
        scanf(" %d", &userinput);

        if (userinput < _lower || userinput > _upper)                                   /*FEJL*/ /*kunne have været en condition. Betinget udtryk*/
            printf("You didn't choose assignment between 1-5, try again\n :");
        
    } while (userinput < _lower || userinput > _upper);
    return userinput;
}

/*---------------------------------------------- STRUCTS -------------------------------------------*/
void loadStruct(structParticipant *_participant)
{
    /* Tildeler alle deltager en struct, som representere deres data.
        Sidst i funktionen, får alle struct tilddelt point, ud fra deres data*/
    int counter;
    FILE *filedata = fopen("cykelloeb", "r");
    for (counter = 0; counter < _AMOUNT_PARTICIPANT; counter++)
    {
        _participant[counter] = assignStruct(filedata);
    }
    fclose(filedata);
    loadPoints(_participant);
}

structParticipant assignStruct(FILE *_filedata)
{
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

/*---------------------------------------------- POINTS -------------------------------------------*/
void loadPoints(structParticipant *_participant)
{
    /*uddeler de forskellige slags point*/
    completePoint(_participant);
    placementPoints(_participant);
    podiumPoints(_participant);
}

void completePoint(structParticipant *_participant)
{
    /*giver point for at gennemføre
       herunder bliver pointene også sat til 0 for alle deltagere*/
    int i;
    for (i = 0; i < _AMOUNT_PARTICIPANT; i++)
    {
        /*atoi laver string om til int. Hvis der er bogstaver, int er 0*/
        _participant[i].points = 0;
        if (atoi(_participant[i].placement))
            _participant[i].points = 3;
        else if (strcmp("OTL", _participant[i].placement) == 0)
            _participant[i].points = 1;
    }
}

void podiumPoints(structParticipant *_participant)
{
    /*point for forskellige podieplaceringer*/
    int i;
    for (i = 0; i < _AMOUNT_PARTICIPANT; i++)
    {
        if (atoi(_participant[i].placement) == 1)
            _participant[i].points += 10;                           /*compund assignment*/
        else if (atoi(_participant[i].placement) == 2)
            _participant[i].points += 5;
        else if (atoi(_participant[i].placement) == 3)
            _participant[i].points += 2;
    }
}

void placementPoints(structParticipant *_participant)
{
    /*Point for placering i givet løb*/
    int i,
        ParisRoubaix = participantsInRace("ParisRoubaix", _participant),
        AmstelGoldRace = participantsInRace("AmstelGoldRace", _participant),
        LaFlecheWallonne = participantsInRace("LaFlecheWallonne", _participant),
        LiegeBastogneLiege = participantsInRace("LiegeBastogneLiege", _participant);

    for (i = 0; i < _AMOUNT_PARTICIPANT; i++)
    {
        if (strcmp("ParisRoubaix", _participant[i].placement) == 0)                         
            pointCalculator(_participant, i, ParisRoubaix);
        else if (strcmp("AmstelGoldRace", _participant[i].placement) == 0)
            pointCalculator(_participant, i, AmstelGoldRace);
        else if (strcmp("LaLiegeBastogneLiege", _participant[i].placement) == 0)
            pointCalculator(_participant, i, LaFlecheWallonne);
        else
            pointCalculator(_participant, i, LiegeBastogneLiege); /*sparet på proccesorkraft, da der ikke skal strcmp*/
    }
}

void pointCalculator(structParticipant *_participant, int i, int _raceParticipants)
{
    /*giver point efter formlen i opgaven*/
    if (atoi(_participant[i].placement))
    {
        _participant[i].points += (_raceParticipants - (atoi(_participant[i].placement))) / 13;
    }
}

int participantsInRace(char *raceCity, structParticipant *_participant)
{
    /*Finder hvor mange deltagere der har været i hvert løb*/
    int i, result = 0;
    for (i = 0; i < _AMOUNT_PARTICIPANT; i++)
    {
        if (strcmp(raceCity, _participant[i].nameRace) == 0)
        {
            result++;
        }
    }
    return result;
}

/*----------------------------------------------OPGAVE 1 -------------------------------------------*/
void opgave1(structParticipant *_participant)
{
    /*kaldt en funktion, for at hele programmet er enstydigt*/
    findAndPrint("ITA", 30, _participant);
}

void findAndPrint(char *_nation, int age, structParticipant *_participant)
{
    /*kører alle deltagere igennem, og printer dem der indgår under betingelserne*/
    int counter;
    for (counter = 0; counter < _AMOUNT_PARTICIPANT; counter++)
    {
        if (strcmp(_nation, _participant[counter].nation) == 0 && _participant[counter].age > age)
            printf("%-20s %-32s | %2d %3s %3s |   %3s    %-s\n", _participant[counter].nameRace, _participant[counter].nameParticipant, _participant[counter].age, _participant[counter].nameTeam, _participant[counter].nation, _participant[counter].placement, _participant[counter].finishTime);
    }
}

/*----------------------------------------------OPGAVE 2 -------------------------------------------*/
void opgave2(structParticipant *_participant)
{
    /*finder danske ryttere og hvor mange løb de har gennemført ,printer dem derefter ud*/
    int danes = 0;
    structIdAndRace *danishRider;

    danishRider = finishrace("DEN", _participant, &danes);
    printStructIdAndRace(_participant, danishRider, danes);
    free(danishRider);
}

structIdAndRace *finishrace(char *_nation, structParticipant *_participant, int *_dane)
{
    /*finder ud af om de danksere og har gennemført, derefter tager stilling til om de er en ny person eller har optrådt før*/
    int i, index = 0;
    structIdAndRace *danishRider;
    danishRider = (structIdAndRace *)malloc(sizeof(structIdAndRace));

    for (i = 0; i < _AMOUNT_PARTICIPANT; i++)
    {
        if (strcmp(_nation, _participant[i].nation) == 0 &&
            strcmp("DNF", _participant[i].placement) != 0)
        {
            if (duplicateIdAndRace(_participant, i, danishRider, &index, *_dane))
            {
                danishRider[index].racesComplete++;
            }
            else
            {
                danishRider = (structIdAndRace *)realloc(danishRider, ((*_dane) + 1) * sizeof(structIdAndRace));
                danishRider[*_dane].id = i;
                danishRider[(*_dane)++].racesComplete = 1;
            }
        }
    }
    return danishRider;
}

int duplicateIdAndRace(structParticipant *_participant, int i, structIdAndRace *indexParticipant, int *index, int sizeArray)
{
    /*optræder den givne person "i" allerede i de danishRider*/
    for (*index = 0; *index < sizeArray; (*index)++)
    {
        if (strcmp(_participant[indexParticipant[*index].id].nameParticipant, _participant[i].nameParticipant) == 0)
            return 1;
    }
    return 0;
}

void printStructIdAndRace(structParticipant *_participant, structIdAndRace *idAndRace, int _numberOfDanes)
{
    /*simpel print*/
    int i;
    for (i = 0; i < _numberOfDanes; i++)
    {
        printf("%-25s races completed: %d\n", _participant[idAndRace[i].id].nameParticipant, idAndRace[i].racesComplete);
    }
}

/*----------------------------------------------OPGAVE 3 -------------------------------------------*/
void opgave3(structParticipant *_participant)
{
    /*samler deltageres point, hvis de kørt mere end et løb. Derefter sortere dem, printer dem, frigiver heapen*/
    int participantCounter = 0;
    structIdandPoints *topParticipants;

    topParticipants = gatherParticipantsPoints(_participant, &participantCounter);
    qsort(topParticipants, participantCounter, sizeof(structIdandPoints), pointCompare);
    printTopParticipants(topParticipants);
    free(topParticipants);
}

structIdandPoints *gatherParticipantsPoints(structParticipant *_participant, int *participantCounter)
{
    /*samler point, og indeler deltageres navn op i efternavn*/
    int i;
    structIdandPoints *topParticipants;

    topParticipants = (structIdandPoints *)malloc(sizeof(structIdandPoints));
    for (i = 0; i < _AMOUNT_PARTICIPANT; i++)
    {
        if (duplicateIdAndPoints(_participant[i], topParticipants, (*participantCounter) + 1) != 1)
        {
            topParticipants = (structIdandPoints *)realloc(topParticipants, ((*participantCounter) + 1) * sizeof(structIdandPoints));
            topParticipants[*participantCounter].id = _participant[i];
            topParticipants[*participantCounter].points = topParticipants[*participantCounter].id.points;
            (*participantCounter)++;
        }
    }
    assignLastname(topParticipants, *participantCounter);
    return topParticipants;
}

void assignLastname(structIdandPoints *_participant, int counter)
{
    /*Giver nye struct en string der består af efternavn*/
    int i, j, strlengh;

    for (i = 0; i < counter; i++)
    {
        strlengh = strlen(_participant[i].id.nameParticipant);
        for (j = 0; j < strlengh; j++)
        {
            if (isupper(_participant[i].id.nameParticipant[j]) && isupper(_participant[i].id.nameParticipant[j + 1]))
            {
                strncpy(_participant[i].lastname, _participant[i].id.nameParticipant + j, strlengh - j);
                break;
            }
        }
    }
}

int duplicateIdAndPoints(structParticipant _compareStruct, structIdandPoints *_array, int arraySize)
{
    /*Hvis deltageren allerede findes i det nye struct, samler funktionen hans point.
      returner også om det er sandt eller falsk at at der er en duplikat*/
    int i;

    for (i = 0; i < arraySize; i++)
    {
        if (strcmp(_compareStruct.nameParticipant, _array[i].id.nameParticipant) == 0)
        {
            _array[i].points += _compareStruct.points;
            return 1;
        }
    }
    return 0;
}

int pointCompare(const void *a, const void *b)
{
    /*sammenligner point, efternavn hvis det er ens*/
    structIdandPoints *pa = (structIdandPoints *)a,
                      *pb = (structIdandPoints *)b;
    if (pa->points < pb->points)
        return 1;
    else if (pb->points < pa->points)
        return -1;
    else
        return lastnameCompare(a, b);
}

int lastnameCompare(const void *a, const void *b)
{
    /*sammenlinger efternavn*/
    structIdandPoints *pa = (structIdandPoints *)a,
                      *pb = (structIdandPoints *)b;
    int strValue = strcmp(pa->lastname, pb->lastname);

    if (strValue < 0)
        return 1;
    else if (strValue > 0)
        return -1;
    else
        return 0;
}

void printTopParticipants(structIdandPoints *_participant)
{
    /*printer en deltageres efternavn og point*/
    int i;

    for (i = 0; i < _TOP_TEN; i++)
    {
        printf("LastName: %-35s point: %2d placement: %d\n", _participant[i].id.nameParticipant, _participant[i].points, i + 1);
    }
}

/*----------------------------------------------OPGAVE 4 -------------------------------------------*/

void opgave4(structParticipant *_participant)
{
    /*finder bedste tid, udskriver den*/
    int riderNumber = 0, bestTime;

    bestTime = bestRider(&riderNumber, _participant, "ParisRoubaix", "AmstelGoldRace");
    printBestTime(bestTime, _participant[riderNumber]);
}

int bestRider(int *riderNumber, structParticipant *_participant, char *firstCity, char *secoundCity)
{
    /*samler deltageres tid, sortere dem, og returnere den mindste som opgave beskriver*/
    int i, tempCounter = 0, duplicateIndex, bestTime;
    struct tm tempStruct;
    structTimeSum *gatheredTime;

    gatheredTime = (structTimeSum *)malloc(sizeof(structTimeSum));
    for (i = 0; i < _AMOUNT_PARTICIPANT; i++)
    {

        if (inCities("ParisRoubaix", "AmstelGoldRace", _participant, i, &duplicateIndex))
        {
            gatheredTime = (structTimeSum *)realloc(gatheredTime, (tempCounter + 1) * sizeof(structTimeSum));
            gatheredTime[tempCounter].indexId = i;
            sscanf(_participant[i].finishTime, "%d:%d:%d", &tempStruct.tm_hour, &tempStruct.tm_min, &tempStruct.tm_sec);
            gatheredTime[tempCounter].timeSum = (tempStruct.tm_hour * _SECOUNDS_IN_HOUR) + (tempStruct.tm_min * _SECOUNDS_IN_MIN) + tempStruct.tm_sec;
                            /* FEJL? */
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

void printBestTime(int bestTime, structParticipant _participant)
{
    /*printer bedste tid (har omregnet deres tider til sekunder*/
    int hour, min, sec;
    hour = bestTime / _SECOUNDS_IN_HOUR;
    min = (bestTime % _SECOUNDS_IN_HOUR) / _SECOUNDS_IN_MIN;
    sec = ((bestTime % _SECOUNDS_IN_HOUR) % _SECOUNDS_IN_MIN);
    printf("The quickest rider is :%-35s\n"
           "With the time gathered time at %2d:%.2d:%.2d\n",
           _participant.nameParticipant, hour, min, sec);
}

int inCities(char *firstCity, char *secoundCity, structParticipant *_participant, int i, int *index)
{
    /*Har deltager gennemført første by, gennemført anden by og hedder det samme, retuner sand */
    if (strcmp(firstCity, _participant[i].nameRace) == 0 && strcmp("DNF", _participant[i].placement) != 0)
    {
        for (*index = 0; *index < _AMOUNT_PARTICIPANT; (*index)++)
        {
            if (strcmp(secoundCity, _participant[*index].nameRace) == 0 &&
                strcmp("DNF", _participant[*index].placement) != 0 &&
                strcmp(_participant[i].nameParticipant, _participant[*index].nameParticipant) == 0)
                return 1;
        }
    }
    return 0;
}

int timeCompare(const void *a, const void *b)
{
    /*sammenligner tid, og returnere den laveste*/
    structTimeSum *pa = (structTimeSum *)a,
                  *pb = (structTimeSum *)b;

    if (pa->timeSum > pb->timeSum)
        return 1;
    else if (pa->timeSum < pb->timeSum)
        return -1;
    else
        return 0;
}

/*----------------------------------------------OPGAVE 5 -------------------------------------------*/
void opgave5(structParticipant *_participant)
{
    /*Finder gennemsnitsalderen på deltgere der har været i top ti*/
    double average = calculateAverage(_participant);
    printf("Average of the top ten riders, across all races is: %2.2lf\n", average);
}

double calculateAverage(structParticipant *_participant)
{
    /*Udregner gennemsnittet, men tæller kun alderen med på deltagere som har været i top ti, 
        og sørger for at samme deltager ikke indgår to gange.
        Returnere det uderegnede gennemsnit til sidst*/
    int i, *indexParticipant, sizeArray = 0;
    double average = 0;
    indexParticipant = (int *)malloc(sizeof(int));

    for (i = 0; i < _AMOUNT_PARTICIPANT; i++)
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

int topTen(structParticipant _participant)
{
    /*Finder ud af, om given deltager er i top ti*/
    if (atoi(_participant.placement) >= 1 && atoi(_participant.placement) <= 10)
        return 1;
    else
        return 0;
}

int duplicateParticipant(structParticipant *_participant, int index, int *indexParticipant, int sizeArray)
{
    /*Optræder deltageren allerede i dette struct array*/
    int i;

    for (i = 0; i < sizeArray; i++)
    {
        if (strcmp(_participant[indexParticipant[i]].nameParticipant, _participant[index].nameParticipant) == 0)
            return 1;
    }
    return 0;
}