SUMMARY="netANALYZER sample application"
HOMEPAGE="http://www.hilscher.com"
LICENSE="MIT"

LIC_FILES_CHKSUM ?= "file://../LICENSE-MIT;md5=87524f2b56aa5423a16a6351a2bd2be3"

S .= "/example"

DEPENDS="libnetana"

do_configure() {
    :
}

CFLAGS:append = " -I=/usr/include/netana"
EXTRA_OEMAKE = "CFLAGS='${CFLAGS}' LDFLAGS='${LDFLAGS}' CC='${CC}'"

do_install() {
    install -d ${D}/opt/netanalyzer
    install ${B}/netanalyzer_demo ${D}/opt/netanalyzer
}

FILES:${PN} = "/opt"
