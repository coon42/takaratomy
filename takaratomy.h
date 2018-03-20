#ifndef _TAKARATOMY_H
#define _TAKARATOMY_H

#include <usb.h>

#define VENDORID             (0x0F30) // Takara Tomy (reported as Jess Technologies Co., Ltd)
#define BUTTON_PRODUCTID     (0x0010) // USB Glitter Button Panel
#define LED_MATRIX_PRODUCTID (0x0040) // USB Led Matrix

enum Commands {
  CMD_OPEN  = 0x50, // alternatively: 0xE0
  CMD_CLOSE = 0x60  // alternatively: 0xD0
};

struct usb_dev_handle* openButton(unsigned int devNum);
int openLid(struct usb_dev_handle* pDev);
int closeLid(struct usb_dev_handle* pDev);

#endif // _TAKARATOMY_H

