#include "allIncludes.h"



void assigmnetSelect(structParticipant *_participant)
{
    switch (userSelect(1,5))
    {
        case 1: opgave1(_participant); break;
        case 2: opgave2(_participant); break;
        case 3: opgave3(_participant); break;
        case 4: opgave4(_participant); break;
        case 5: opgave5(_participant); break;
        default: printf("not done yet\n"); break;
    }
}

int userSelect(int _lower, int _upper)
{
    int userinput;
    do
    {
        printf("Choose an assigmnet: [1], [2], [3], [4] or [5]\n :");
        scanf(" %d", &userinput);
    }   while (userinput < _lower || userinput > _upper);
    return userinput;
}
