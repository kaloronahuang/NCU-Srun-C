// main.c
#include <curl/curl.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "logger.h"

boolean check_path_exist(char path[])
{
}

int main(int argc, char **argv)
{
    if (argc != 1)
    {
        printf("Unable to process the arguments, exit.");
        return 0;
    }
    return 0;
}