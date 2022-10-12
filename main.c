// main.c
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <curl/curl.h>

#include "logger.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Unable to process the arguments, exit.");
        return 0;
    }

    LogConfig *cfg = (LogConfig *)malloc(sizeof(LogConfig));
    if (config_load(argv[1], cfg) == 0)
    {
        printf("YEaaaa!");
    }
    else
        printf("Invalid JSON config, exit.");
    
    // Free the memory;
    config_unload(cfg);
    free(cfg);
    return 0;
}