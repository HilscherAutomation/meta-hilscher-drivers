DESCRIPTION = "User space API library for Hilscher netANALYZER devices."
HOMEPAGE = "http://www.hilscher.com"
LICENSE = "MIT"

LIC_FILES_CHKSUM ?= "file://COPYING;md5=1fa11fad31b4e7f6aa54d2e771c852a6"

inherit pkgconfig
inherit autotools

S .= "/libnetana"

DEBIAN_NOAUTONAME:${PN} = "1"
RDEPENDS:${PN} = "kernel-module-netanalyzer"
