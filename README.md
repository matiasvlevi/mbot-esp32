# mbot-esp32

This repository contains:

* An esp32 webserver firmware. 
 Provides an API of commands called through websockets, allowing a web client to control the device.

* An [Oxenode](https://oxenode.io/) plugin (`./oxenode/mbot-esp32`). Provides bindings for sending instructions through websockets. Acts as a web client to the esp32 firmware.

<br/>

## Robot & Hardware

This firmware is meant to be used with an `esp32` devkit, wired to a `l298` motor controller.


![oxebot_angle](./assets/oxebot_angle.jpg)

## Oxenode Client Script

### Websocket creation

![mbot-begin](./assets/script-begin.png)

### Keyboard event (WASD controls)

![mbot-key](./assets/script-key.png)

<br/>


## Oxenode Plugin CDN

Use this static CDN to include the plugin in [Oxenode](https://oxenode.io/)

```
https://cdn.jsdelivr.net/gh/matiasvlevi/mbot-esp32@latest/oxenode/mbot-esp32
```

> NOTE: The firmware does not support encryptes websockets (wss) yet, which makes it impossible to use it from a https client.

<br/>

## Build & Upload Firmware

We are using the official esp-idf sdk, once installed, you can run the alias to get everything setup.

```
get_idf
```

#### Wifi Config

Edit `./main/wifi_cred.h` to match your wifi credentials.

You can then use make to build and upload to the esp32

####  Build

```
make build
```

####  Upload

```
make upload
```
