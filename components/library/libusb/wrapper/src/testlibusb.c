/*
 * testlibusb.c
 *
 *  Test suite program
 */

#include <stdio.h>
#include "usb.h"

void
dump_data(unsigned char *data, int size)
{
  int i;

  if (size) {
    printf("data dump:");
    for (i = 0; i < size; i++) {
      if (i % 16 == 0) {
        printf("\n%08x  ", i);
      }
      printf("%02x ", (uchar_t)data[i]);
    }
    printf("\n");
  }
}

void print_endpoint(struct usb_endpoint_descriptor *endpoint)
{
  printf("  Endpoint descriptor:\n");
  printf("      bEndpointAddress: %02xh\n", endpoint->bEndpointAddress);
  printf("      bmAttributes:     %02xh\n", endpoint->bmAttributes);
  printf("      wMaxPacketSize:   %d\n", endpoint->wMaxPacketSize);
  printf("      bInterval:        %d\n", endpoint->bInterval);
  printf("      bRefresh:         %d\n", endpoint->bRefresh);
  printf("      bSynchAddress:    %d\n", endpoint->bSynchAddress);
  printf("      extralen:	  %d\n", endpoint->extralen);
  dump_data(endpoint->extra, endpoint->extralen);
}

void print_altsetting(struct usb_interface_descriptor *interface)
{
  int i;

  printf("  Interface descriptor:\n");
  printf("    bInterfaceNumber:   %d\n", interface->bInterfaceNumber);
  printf("    bAlternateSetting:  %d\n", interface->bAlternateSetting);
  printf("    bNumEndpoints:      %d\n", interface->bNumEndpoints);
  printf("    bInterfaceClass:    %d\n", interface->bInterfaceClass);
  printf("    bInterfaceSubClass: %d\n", interface->bInterfaceSubClass);
  printf("    bInterfaceProtocol: %d\n", interface->bInterfaceProtocol);
  printf("    iInterface:         %d\n", interface->iInterface);
  printf("    extralen:		  %d\n", interface->extralen);
  dump_data(interface->extra, interface->extralen);

  for (i = 0; i < interface->bNumEndpoints; i++)
    print_endpoint(&interface->endpoint[i]);
}

void print_interface(struct usb_interface *interface)
{
  int i;
  printf("num_altsetting: %d\n", interface->num_altsetting);

  for (i = 0; i < interface->num_altsetting; i++)
    print_altsetting(&interface->altsetting[i]);

  printf("\n");
}

void print_configuration(struct usb_config_descriptor *config)
{
  int i;

  printf("  Configuration descriptor:\n");
  printf("  wTotalLength:         %d\n", config->wTotalLength);
  printf("  bNumInterfaces:       %d\n", config->bNumInterfaces);
  printf("  bConfigurationValue:  %d\n", config->bConfigurationValue);
  printf("  iConfiguration:       %d\n", config->iConfiguration);
  printf("  bmAttributes:         %02xh\n", config->bmAttributes);
  printf("  MaxPower:             %d\n", config->MaxPower);

  printf("  extralen:		  %d\n", config->extralen);
  dump_data(config->extra, config->extralen);

  for (i = 0; i < config->bNumInterfaces; i++)
    print_interface(&config->interface[i]);

  printf("\n");
}

void print_device_descriptor(struct usb_device_descriptor *dev)
{
  printf("  Device descriptor:\n");
  printf("  bLength:                %d\n", dev->bLength);
  printf("  bDescriptorType:        %xh\n", dev->bDescriptorType);
  printf("  bcdUSB:                 %xh\n", dev->bcdUSB);
  printf("  bDeviceClass:           %xh\n", dev->bDeviceClass);
  printf("  bDeviceSubClass:        %xh\n", dev->bDeviceSubClass);
  printf("  bDeviceProtocol:        %xh\n", dev->bDeviceProtocol);
  printf("  bMaxPacketSize0:        %xh\n", dev->bMaxPacketSize0);
  printf("  idVendor:               %xh\n", dev->idVendor);
  printf("  idProduct:              %xh\n", dev->bcdDevice);
  printf("  bcdDevice:              %xh\n", dev->bcdDevice);
  printf("  iManufacturer:          %xh\n", dev->iManufacturer);
  printf("  iProduct:               %xh\n", dev->iProduct);
  printf("  iSerialNumber:          %xh\n", dev->iSerialNumber);
  printf("  bNumConfigurations:     %xh\n", dev->bNumConfigurations);

  printf("\n");
}

int main(void)
{
  struct usb_bus *bus;
  struct usb_device *dev;

  usb_init();

  usb_find_busses();
  usb_find_devices();

  printf("bus/device  idVendor/idProduct\n");

  for (bus = usb_busses; bus; bus = bus->next) {
    for (dev = bus->devices; dev; dev = dev->next) {
      int i, ret;
      char string[256];
      usb_dev_handle *udev;

      printf("%s/%s     %04X/%04X\n", bus->dirname, dev->filename,
	dev->descriptor.idVendor, dev->descriptor.idProduct);

      udev = usb_open(dev);
      if (udev) {
        if (dev->descriptor.iManufacturer) {
          ret = usb_get_string_simple(udev, dev->descriptor.iManufacturer, string, sizeof(string));
          if (ret > 0)
            printf("- Manufacturer : %s\n", string);
          else
            printf("- Unable to fetch manufacturer string %d\n", ret);
        }


        if (dev->descriptor.iProduct) {
          ret = usb_get_string_simple(udev, dev->descriptor.iProduct, string, sizeof(string));
          if (ret > 0)
            printf("- Product      : %s\n", string);
          else
            printf("- Unable to fetch product string\n");
        }

        if (dev->descriptor.iSerialNumber) {
          ret = usb_get_string_simple(udev, dev->descriptor.iSerialNumber, string, sizeof(string));
          if (ret > 0)
            printf("- Serial Number: %s\n", string);
          else
            printf("- Unable to fetch serial number string\n");
        }
        usb_close(udev);
      }

      if (!dev->config) {
        printf("  Couldn't retrieve descriptors\n");
        continue;
      }

      print_device_descriptor(&dev->descriptor);

      for (i = 0; i < dev->descriptor.bNumConfigurations; i++) {
        print_configuration(&dev->config[i]);
      }

    }
  }

  return 0;
}

