#include "header_func.h"
#include "libusbi.h"
extern  __attribute__((visibility("default"))) int libusb_control_transfer (libusb_device_handle *dev_handle, uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, unsigned char *data, uint16_t wLength, unsigned int timeout){
    struct libusb_transfer *transfer;
    unsigned char *buffer;
    int completed = 0;
    int r;
    if (usbi_handling_events(((dev_handle) ? (((dev_handle)->dev)->ctx) : ((void *)0))))
        return LIBUSB_ERROR_BUSY;
    return r;
}
