// logger.h

typedef int boolean;

#define true 1
#define false 0

typedef struct _userInfo
{
    char *username;
    char *password;
    char *domain;
} UserInfo;

typedef struct _platformInfo
{
    char *loginURL;
    char *device;
    char *os;
} PlatformInfo;

typedef struct _config
{
    struct UserInfo *userInfo;
    struct PlatformInfo *platformInfo;
} LogConfig;

int load_config(char *path, LogConfig *config);