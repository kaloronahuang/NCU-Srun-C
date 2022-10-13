// encryption.h

extern const char encryption_paddingchar;
extern const char *encryption_alphabet;
extern const char *encryption_hex_alphabet;

char *encryption_base64(char *src);
char *encryption_md5(const char *password, const char *token);