# Logitech G733 Headset Driver

## Build

```
$ sudo apt install libhidapi-dev libhidapi-libusb0
$ gcc main.c -o main -I/usr/include/hidapi -lhidapi-libusb
```

## Run

```
$ ./main
```
