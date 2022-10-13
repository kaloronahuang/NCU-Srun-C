// main.c
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/ncu_srun_universal.h"
#include "include/config.h"
#include "include/encryption.h"

int main(int argc, char **argv)
{
    char *s1 = encryption_md5("jcudhafshfkjadshvkb", "scabkshd");
    printf("%s\n", s1);
    free(s1);
    return 0;
}