// config.h

// configuration descriptions;

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
    UserInfo userInfo;
    PlatformInfo platformInfo;
} LogConfig;

int config_load(const char *path, LogConfig *config);
void config_unload(const LogConfig *config);