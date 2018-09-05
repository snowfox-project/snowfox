Examples
========

# ISP/Debug-Tools

## eHajo µISP-Stick
When using the eHajo µISP-Stick with Ubuntu the default USB vendor/product id need to be set. The correct vendor/product id can be seen when plugging in the µISP-Stick in the computer while monitoring the output of dmesg.
```
dmesg -wH
...
[  +0.104109] usb 3-13.2.3: New USB device found, idVendor=16d0, idProduct=0ba5
[  +0.000004] usb 3-13.2.3: New USB device strings: Mfr=0, Product=2, SerialNumber=0
[  +0.000002] usb 3-13.2.3: Product: eHaJo ISP
```
In this case the vendor id is 0x16d0 and the product id is 0x0ba5. Since the eHajo µISP-Stick is behaving like an usbtiny programmer we need to edit the usbtiny configuration in /etc/avrdude.conf. 
```
programmer
  id              = "usbtiny";
  desc            = "USBtiny simple USB programmer, http://www.ladyada.net/make/usbtinyisp/";
  type            = "usbtiny";
  connection_type = usb;
  usbvid          = 0x16d0;
  usbpid          = 0x0ba5;
;
```
Now the eHajo µISP-Stick is ready to be used with avrude.
```
avrdude -p atmega1284p -c usbtiny -P usb
```