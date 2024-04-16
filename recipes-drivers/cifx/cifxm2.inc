SUMMARY = "Kernel mode driver of Hilscher cifX M.2 devices."
HOMEPAGE = "www.hilscher.com"
LICENSE = "GPL-2.0-only"

LIC_FILES_CHKSUM ?= "file://LICENSE.txt;md5=eae965cb67f143ba6a9eb017ac821601"

S .= "cifx_m2"

EXTRA_OEMAKE = "KDIR=${STAGING_KERNEL_DIR} \
                TMPSYMVERS=${KBUILD_EXTRA_SYMBOLS}"

inherit module
