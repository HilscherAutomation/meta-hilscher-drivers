DESCRIPTION = "Example applications for Hilscher cifX devices."
HOMEPAGE = "http://www.hilscher.com"
LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://../LICENSE.md;md5=eae965cb67f143ba6a9eb017ac821601"

inherit pkgconfig cmake useradd

S .= "./examples"

USERADD_PACKAGES = "${PN}"
GROUPADD_PARAM_${PN} = "-r cifx"

EXTRA_OECMAKE = "-DCMAKE_INSTALL_PREFIX=/opt/cifx/demo/"

DEPENDS="libcifx libpciaccess libnl"

do_install_append() {
  chgrp -R cifx ${D}/opt/cifx
  chmod 0775 ${D}/opt/cifx
}

PACKAGES =+ "cifxtcpserver"
FILES_${PN} += "/opt/cifx/demo"
