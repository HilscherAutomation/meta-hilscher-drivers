## Overview

The layer meta-hilscher-drivers provides recipes and resources to driver's of products of the [Hilscher Gesellschaft für Systemautomation mbH](https://www.hilscher.com/).

Currently provided drivers:
 - cifX
 - netANALYZER

### cifX

The Linux cifX driver provides support of multiple devices of the [cifX product portfolio](https://www.hilscher.com/products/pc-cards-for-industrial-ethernet-fieldbus) ([driver source](https://github.com/HilscherAutomation/nxdrvlinux)).

### netANALYZER

The netANALYZER driver for linux provides support for using [cifX products](https://www.hilscher.com/products/pc-cards-for-industrial-ethernet-fieldbus) and special netANALYZER products to non-invasively capture ethernet traffic

### Usage

 - Include this layer in your bblayers.conf
 - Make sure your kernel has uio support enabled (CONFIG_UIO=y/m) if PCI support is enabled.

   **_NOTE:_** This can usually be achieved by setting ``` KERNEL_EXTRA_FEATURES:append = " features/uio/uio.scc" ```
 - Include libcifx (or your application / exampled using libcifx) into your image.

   ``` IMAGE_INSTALL:append = " libcifx cifxsample" ```
