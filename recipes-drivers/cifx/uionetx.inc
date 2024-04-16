SUMMARY = "Kernel mode driver for Hilscher cifX devices."
HOMEPAGE = "www.hilscher.com"
LICENSE = "GPL-2.0-only"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0-only;md5=801f80980d171dd6425610833a22dbe6"

S .= "uio_netx"

EXTRA_OEMAKE = "KDIR=${STAGING_KERNEL_DIR} \
                TMPSYMVERS=${KBUILD_EXTRA_SYMBOLS}"

inherit module
