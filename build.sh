g++ src/config.c src/encryption.c src/main.c -o ncu-login -lcjson -lcrypto -g
g++ src/config.c src/encryption.c src/test.c -o ncu-login-test -lcjson -lcrypto -g