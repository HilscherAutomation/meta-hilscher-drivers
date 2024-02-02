
DEFAULT_PREFERENCE = "-1"

SRC_URI = "git://github.com/HilscherAutomation/nxdrvlinux.git;branch=main;protocol=https"
SRCREV = "${AUTOREV}"

PV = "dev+git${SRCPV}"

S = "${WORKDIR}/git/"
