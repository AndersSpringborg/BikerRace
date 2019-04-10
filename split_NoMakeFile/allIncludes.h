#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
/*
 ------------------------Læsevejledning------------------------
 opgave 1 linje 120 - 200
 opgave 2 linje 200 - 340, lav enum
 */
/*----------------------Defines--------------------
--------------------------LAV ALLE TAL OM TIL DEFINES-----------------*/
#define _AMOUNT_PARTICIPANT 790
#define _CHAR_SPACE 40
#define _BLUE "\x1B[34m"
#define _RESET "\x1B[0m"
#define _TOP_TEN 10
#define _FALSE 0
#define _SECOUNDS_IN_HOUR 3600
#define _SECOUNDS_IN_MIN 60

/* --------------- #include "topAfMain.h" -------- */

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
    structParticipant id2;
    int id;
    int racesComplete;
} structIdAndRace;

typedef struct opgave3
{
    structParticipant id;
    int points;
    char lastname[30];
} structIdandPoints;

typedef struct opgave4
{
    int indexId;
    int timeSum;
} structTimeSum;

/*----------------STRUCTS-----------------*/

/*-------prototyper---------*/

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
void findAndPrint(char *, structParticipant *);

void opgave2(structParticipant *);
structIdAndRace *finishrace(char *, structParticipant *, int *);
int duplicatePerson(structIdAndRace, structIdAndRace *, int);
void printStructIdAndRace(structParticipant *_participant, structIdAndRace *id, int _numberOfDanes);

void opgave3(structParticipant *);
structIdandPoints *gatherParticipants(structParticipant *, int *);
int duplicateIDPOINTS(structParticipant, structIdandPoints *, int);
int pointCompare(const void *, const void *);
void printTopParticipants();
void assignLastname(structIdandPoints *_participant, int counter);

void opgave4(structParticipant *);
int bestRider(int *riderNumber, structParticipant *_participant, char *firstCity, char *secoundCity);
struct tm scanner(structParticipant _participant);
int timeCompare(const void *a, const void *b);
int inCities(char *firstCity, char *secoundCity, structParticipant *_participant, int i, int *index);

void opgave5(structParticipant *_participant);
int duplicateParticipant(structParticipant *_participant, int index, int *indexParticipant, int sizeArray);
int topTen(structParticipant _participant);
double calculateAverage(structParticipant *_participant);
