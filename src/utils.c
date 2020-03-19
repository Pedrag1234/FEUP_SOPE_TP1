#include "utils.h"

int isNumber(char *string)
{
    int s_size = strlen(string);

    for (int i = 0; i < s_size; i++)
    {
        if (isdigit(string[i]) == 0)
            return 1;
    }
    return 0;
}