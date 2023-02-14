# Logitech G733 Headset Driver

## Build

```
$ sudo apt install libhidapi-dev libhidapi-libusb0
$ gcc main.c -o main -I/usr/include/hidapi -lhidapi-libusb
```

## Run

I don't follow standards and I don't have time to implement a proper help atm 🤣.

```
$ ./main -t [top|bottom] -r <rgb hex value> -mode [fixed|breathing]
```

Example:

```
sudo ./main -t top -r fc200c -m fixed
```

To work without sudo you need to add an udev rule as documented in https://github.com/libusb/hidapi#hidapi-has-four-back-ends

