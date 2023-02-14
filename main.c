#include <ctype.h>
#include <hidapi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_STR 255

void print_payload(uint8_t *ptr, size_t size) {
    for (int i = 0; i < size; i++) {
        printf("0x%02x ", *(ptr + i));
        if (i % 8 == 7) {
            printf("\n");
        }
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    int res;
    unsigned char buf[65];
    wchar_t wstr[MAX_STR];
    hid_device *handle;
    int i;
    int arg;
    int opt;
    uint32_t len = 0;

    uint8_t color_mode = 0x01;
    uint8_t top = 0x00;
    uint32_t rgb = 0xf74433;

      
    while((opt = getopt(argc, argv, ":r:t:m:")) != -1) 
    { 
        switch(opt) 
        { 
            case 't': 
                if (!strcmp("top", optarg)) {
                    top = 0x01;
                }
                printf("top: %d\n", top);
                break; 
            case 'r': 
                len = strlen(optarg);
                if (len != 6) {
                    printf("provide rgb in 6 hex characters, example: ff0404\n");
                    exit(1);
                }
                rgb = (int)strtol(optarg, NULL, 16);
                printf("rgb: %06x\n", rgb);
                break; 
            case 'm':
                if (!strcmp("breathing", optarg)) {
                    color_mode = 0x02;
                }
                break;
        } 
    }

    uint8_t payload[] = "\x11\xff\x04\x3a\x01\x01\xff\xff\xff\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
    print_payload(payload, 20);
    payload[4] = top;
    payload[5] = color_mode;
    payload[6] = (rgb >> 16) & 0xff;
    payload[7] = (rgb >> 8) & 0xff;
    payload[8] = rgb & 0xff;
    print_payload(payload, 20);

    // Initialize the hidapi library
    res = hid_init();

    // Open the device using the VID, PID,
    // and optionally the Serial number.
    // Get the data executing `lsusb` command
    handle = hid_open(0x46d, 0xab5, NULL);
    if (!handle) {
        printf("Unable to open device\n");
        hid_exit();
        return 1;
    }

    // Read the Manufacturer String
    res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
    printf("Manufacturer String: %ls\n", wstr);

    // Read the Product String
    res = hid_get_product_string(handle, wstr, MAX_STR);
    printf("Product String: %ls\n", wstr);

    // Read the Serial Number String
    res = hid_get_serial_number_string(handle, wstr, MAX_STR);
    printf("Serial Number String: (%d) %ls", wstr[0], wstr);

    res = hid_write(handle, payload, 20);
    printf("\nwrite %d bytes\n", res);

    hid_close(handle);
    hid_exit();

    return 0;
}

// "\x11\xff\x04\x3a\x01\x03\x00\x00\x00\x00\x00\x13\x88\x64\x00\x00\x00\x00\x00\x00" // cycle
// "\x11\xff\x04\xda\x01\x08\x13\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" // breathing
// "\x11\xff\x04\x3a\x01\x02\x00\xff\xff\x13\x88\x00\x64\x00\x00\x00\x00\x00\x00\x00"

// "\x11\xff\x04\x3a\x01\x02\x00\x61\x61\x13\x88\x00\x64\x00\x00\x00\x00\x00\x00\x00" // breathing
// "\x11\xff\x04\x3a\x01\x01\x00\x61\x61\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" // fixed
