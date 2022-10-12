# NCU-Srun-C

This is a repo for codes to login the NCU campus network. The codes are written in C with lightweight library and able to be deployed on embedded systems like network routers and most other devices.

## Usage

```shell
ncu-srun -c config.json
```

`config.json` be like:

```json
{
    "userInfo": {
        "username": "",
        "password": "",
        "domain": ""
    },
    "platformInfo": {
        "loginURL" : "http://222.204.3.154",
        "device" : "Macintosh",
        "os": "Mac OS"
    }
}
```