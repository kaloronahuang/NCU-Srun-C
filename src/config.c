// config.c
#include "include/ncu_srun_universal.h"
#include "include/config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cjson/cJSON.h>

char *util_copy_string(char *src)
{
    size_t len = strlen(src);
    char *ret = (char *)malloc(len + 1ull);
    memcpy(ret, src, len);
    ret[len] = '\0';
    return ret;
}

int config_load(const char *path, LogConfig *config)
{
    FILE *config_file = fopen(path, "r");
    // unable to read;
    if (config_file == NULL)
        return -1;
    fseek(config_file, 0, SEEK_END);
    size_t file_size = ftell(config_file);
    rewind(config_file);
    char *buff = (char *)malloc(file_size + 1);
    size_t real_size = fread(buff, 1, file_size, config_file);

    int ret_value = 0;
    if (real_size == file_size)
    {
        cJSON *doc = cJSON_Parse(buff);
        if (doc == NULL)
            ret_value = -1;
        else
        {
            cJSON *ui = cJSON_GetObjectItem(doc, "userInfo");
            cJSON *pi = cJSON_GetObjectItem(doc, "platformInfo");

            if (ui != NULL && pi != NULL)
            {
                cJSON *username = cJSON_GetObjectItem(ui, "username");
                cJSON *password = cJSON_GetObjectItem(ui, "password");
                cJSON *domain = cJSON_GetObjectItem(ui, "domain");

                cJSON *loginURL = cJSON_GetObjectItem(pi, "loginURL");
                cJSON *device = cJSON_GetObjectItem(pi, "device");
                cJSON *os = cJSON_GetObjectItem(pi, "os");

                if (username != NULL && password != NULL && domain != NULL &&
                    loginURL != NULL && device != NULL && os != NULL &&
                    cJSON_IsString(username) &&
                    cJSON_IsString(password) &&
                    cJSON_IsString(domain) &&
                    cJSON_IsString(loginURL) &&
                    cJSON_IsString(device) &&
                    cJSON_IsString(os))
                {
                    config->userInfo.username = util_copy_string(username->valuestring);
                    config->userInfo.password = util_copy_string(password->valuestring);
                    config->userInfo.domain = util_copy_string(domain->valuestring);

                    config->platformInfo.loginURL = util_copy_string(loginURL->valuestring);
                    config->platformInfo.device = util_copy_string(device->valuestring);
                    config->platformInfo.os = util_copy_string(os->valuestring);
                }
            }
            else
                ret_value = -1;

            cJSON_Delete(doc);
        }
    }
    else
        ret_value = -1;

    fclose(config_file);
    free(buff);
    return ret_value;
}

void config_unload(const LogConfig *config)
{
    if (config == NULL)
        return;

    if (config->userInfo.username != NULL)
        free(config->userInfo.username);
    if (config->userInfo.password != NULL)
        free(config->userInfo.password);
    if (config->userInfo.domain != NULL)
        free(config->userInfo.domain);

    if (config->platformInfo.loginURL != NULL)
        free(config->platformInfo.loginURL);
    if (config->platformInfo.device != NULL)
        free(config->platformInfo.device);
    if (config->platformInfo.os != NULL)
        free(config->platformInfo.os);
}