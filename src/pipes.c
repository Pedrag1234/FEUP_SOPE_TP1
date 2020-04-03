#include "pipes.h"

void cmd_2_str(char *cmd, char *resp)
{

    FILE *f = popen(cmd, "r");

    if (f == NULL)
    {
        perror("Command");
        exit(1);
    }
    fgets(resp, MAX_RESP_SIZE, f);
    resp[strlen(resp) - 1] = '\0';

    fclose(f);
}
