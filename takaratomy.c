#include <stdio.h>
#include "takaratomy.h"

static struct usb_device* openUsbDevice(int vendorId, int productId, unsigned int devNum) {
  usb_init();
  usb_find_busses();
  usb_find_devices();

  for(struct usb_bus* pBus = usb_get_busses(); pBus; pBus = pBus->next) {
    for(struct usb_device* pDev = pBus->devices; pDev; pDev = pDev->next) {
      if((pDev->descriptor.idVendor == vendorId) && (pDev->descriptor.idProduct == productId)) {
        if(devNum == 0)
          return pDev;
        else
          devNum--;
      }
    }
  }

  return NULL;
}

struct usb_dev_handle* openButton(unsigned int devNum) {
  struct usb_device* pDev = openUsbDevice(VENDORID, BUTTON_PRODUCTID, devNum);

  if(!pDev) {
    fprintf(stderr, "ERROR: USB button was not found!\n");
    printf("Did you perhaps forget to sudo or add a udev rule?\n");

    return NULL;
  }

  struct usb_dev_handle* hDev = usb_open(pDev);

  if(!hDev) {
    fprintf(stderr, "ERROR: USB button could not be opened!\n");
    printf("Did you perhaps forget to sudo or add a udev rule?\n");

    return NULL;
  }

  usb_set_debug(1);

  if(usb_claim_interface(hDev, 0) < 0) {
    fprintf(stderr, "ERROR: Cannot claim interface!\n");

    return NULL;
  }

  return hDev;
}

static int sendUsbCommand(struct usb_dev_handle* pDev, unsigned char cmd) {
  int ec;

  if((ec = usb_interrupt_write(pDev, 0x02, &cmd, 1, 10)) < 0) {
    printf("Error writing to USB device (%d): %s\n", ec, usb_strerror());
    return 2;
  }

  return 0;

}

int openLid(struct usb_dev_handle* pDev) {
  return sendUsbCommand(pDev, CMD_OPEN);
}

int closeLid(struct usb_dev_handle* pDev) {
  return sendUsbCommand(pDev, CMD_CLOSE);
}

