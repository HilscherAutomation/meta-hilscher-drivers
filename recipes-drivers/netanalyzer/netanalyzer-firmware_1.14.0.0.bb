SUMMARY = "netANALYZER firmware for Hilscher netANALYZER devices"
HOMEPAGE = "www.hilscher.com"
LICENSE = "HilscherSLA"

LIC_FILES_CHKSUM = "file://LICENSE-HSLA;md5=4e75f587deeeacc8793d0d650113a260"
NO_GENERIC_LICENSE[HilscherSLA] ?= "LICENSE-HSLA"

require driver_version.inc
PV="1.14.0.0"

inherit allarch

do_install() {
  install -d ${D}/lib/firmware/netanalyzer/
  cp -r ${S}/firmware/* ${D}/lib/firmware/netanalyzer/
  cp -r ${S}/bsl/* ${D}/lib/firmware/netanalyzer/
}

PACKAGES="${PN}"
RPROVIDES:${PN}="netanalyzer-bsl"
FILES:${PN}="/lib"
