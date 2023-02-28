# Logitech G733 Headset Driver

It's at the moment just an RGB controller(?), but in the future I would like to know what is the headset battery percentage.
Logitech hub is not available on linux so I created my own.

## Build

```
$ sudo apt install libhidapi-dev libhidapi-libusb0
$ gcc main.c -o main -I/usr/include/hidapi -lhidapi-libusb
```

## Run

```
$ ./main -t [top|bottom] -r <rgb hex value> -m [fixed|breathing]
```

Example:

```
sudo ./main -t top -r fc200c -m fixed
```

To work without sudo you need to add an udev rule as documented in https://github.com/libusb/hidapi#hidapi-has-four-back-ends

