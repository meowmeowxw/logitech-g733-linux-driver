#include <stdio.h>
#include <hidapi.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 255

int main(int argc, char* argv[])
{
    int res;
    unsigned char buf[65];
    wchar_t wstr[MAX_STR];
    hid_device *handle;
    int i;

    // Initialize the hidapi library
    res = hid_init();

    // Open the device using the VID, PID,
    // and optionally the Serial number.
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
    printf("Serial Number String: (%d) %ls\n", wstr[0], wstr);

    // Read Indexed String 1
    //
    res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
    printf("Indexed String 1: %ls\n", wstr);

    // Toggle LED (cmd 0x80). The first byte is the report number (0x0).
    uint8_t *x = "\x11\xff\x04\x3a\x01\x01\x03\x01\x21\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
    memcpy(buf, x, 27);
    printf("%d\n", *(uint8_t *)buf);
    res = hid_write(handle, buf, 20);
    printf("%d\n", res);

    hid_close(handle);
    hid_exit();

    return 0;
}
