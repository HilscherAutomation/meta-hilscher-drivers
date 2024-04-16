DESCRIPTION = "User space driver for Hilscher cifX devices."
HOMEPAGE = "http://www.hilscher.com"
LICENSE = "MIT & HilscherSLA"

LIC_FILES_CHKSUM ?= "file://LICENSE.md;md5=eae965cb67f143ba6a9eb017ac821601 \
                     file://Toolkit/HilscherSLA.pdf;md5=1d3864f430ae2bf421d0d76e91a3dbb8"
NO_GENERIC_LICENSE[HilscherSLA] ?= "Toolkit/HilscherSLA.pdf"

inherit pkgconfig
inherit cmake
inherit useradd

S .= "libcifx"

DEBIAN_NOAUTONAME:${PN} = "1"

USERADD_PACKAGES = "${PN} ${PN}-plugin-spm"
GROUPADD_PARAM:${PN} = "-r cifx"
GROUPADD_PARAM:${PN}-plugin-spm = "-r cifx"

# As we may be using different settings per machine, make libcifx a machine package
PACKAGE_ARCH = "${MACHINE_ARCH}"
PACKAGES =+ "${PN}-plugin-spm"
RDEPENDS:${PN} += "${@bb.utils.contains('PACKAGECONFIG', 'spm', '${PN}-plugin-spm', '', d)}"

DEPENDS        += "${@bb.utils.contains('PACKAGECONFIG', 'tun', 'libnl', '', d)}"
RDEPENDS:${PN} += "${@bb.utils.contains('PACKAGECONFIG', 'tun', 'libnl libnl-cli', '', d)}"

SRC_URI += " \
   file://80-hilscher-netx.rules \
   file://80-hilscher-cifxeth.rules \
   file://cifxeth \
   file://80-hilscher-netx-spi.rules"

PACKAGECONFIG ??= "${@bb.utils.contains('MACHINE_FEATURES', 'pci', 'pci', '' ,d)} \
                  tun"

CIFX_SPI_CONFIGS ??= "Device=spidev0.0;Speed=25000000;Mode=0;ChunkSize=0;CSChange=0"
PACKAGECONFIG[pci] = ",-DDISABLE_PCI=ON,libpciaccess,libpciaccess uionetx"
PACKAGECONFIG[spm] = "-DHWIF=ON -DSPM_PLUGIN=ON"
PACKAGECONFIG[tun] = "-DVIRTETH=ON"
PACKAGECONFIG[irq] = ""
PACKAGECONFIG[dma] = ""

do_install:append() {
  #bootloader
  cd "${S}/../BSL"
  install -d -m 0775 -g cifx "${D}/opt/cifx/deviceconfig/"
  install -m 444 NETX*  "${D}/opt/cifx/"

  if [ "${@bb.utils.contains('PACKAGECONFIG', 'pci', 'yes', 'no', d)}" = "yes" ]; then
    install -d ${D}${nonarch_base_libdir}/udev/rules.d/
    install -m 0644 ${WORKDIR}/80-hilscher-netx.rules ${D}${nonarch_base_libdir}/udev/rules.d/
  fi

  if [ "${@bb.utils.contains('PACKAGECONFIG', 'tun', 'yes', 'no', d)}" = "yes" ]; then
    install -d ${D}${nonarch_base_libdir}/udev/rules.d/
    install -m 0644 ${WORKDIR}/80-hilscher-cifxeth.rules ${D}${nonarch_base_libdir}/udev/rules.d/

    install -d "${D}/etc/init.d/"
    install -m 0744 ${WORKDIR}/cifxeth ${D}/etc/init.d/
  fi

  if [ "${@bb.utils.contains('PACKAGECONFIG', 'spm', 'yes', 'no', d)}" = "yes" ]; then
    install -d ${D}${nonarch_base_libdir}/udev/rules.d/
    install -m 0644 ${WORKDIR}/80-hilscher-netx-spi.rules ${D}${nonarch_base_libdir}/udev/rules.d/

    install -d ${D}/opt/cifx/plugins/netx-spm/
    # Delete delete spi configuration from driver as we bring our own
    rm ${D}/opt/cifx/plugins/netx-spm/*
    spi_ports="${CIFX_SPI_CONFIGS}"
    idx=0
    for tmp_config in $spi_ports; do
        echo "$tmp_config" > ${D}/opt/cifx/plugins/netx-spm/config${idx}
        sed -i -e 's/;/\n/g' ${D}/opt/cifx/plugins/netx-spm/config${idx}
        chmod 0744 ${D}/opt/cifx/plugins/netx-spm/config${idx}
        idx=$(expr $idx + 1)
    done
  fi

  install -d -m 0775 -g cifx ${D}/opt/cifx/deviceconfig/FW
  if [ "${@bb.utils.contains('PACKAGECONFIG', 'tun', '1', '', d)}" != "" ]; then
      echo "eth=yes" >> ${D}/opt/cifx/deviceconfig/FW/device.conf
  fi
  if [ "${@bb.utils.contains('PACKAGECONFIG', 'dma', '1', '', d)}" != "" ]; then
      echo "dma=yes" >> ${D}/opt/cifx/deviceconfig/FW/device.conf
  fi
  if [ "${@bb.utils.contains('PACKAGECONFIG', 'irq', '1', '', d)}" != "" ]; then
      echo "irq=yes" >> ${D}/opt/cifx/deviceconfig/FW/device.conf
  fi

  chgrp -R cifx ${D}/opt/cifx
  chmod 0775 ${D}/opt/cifx
}

FILES:${PN} += "/usr/lib/ \
                /opt/cifx/ \
                ${nonarch_base_libdir}/udev/rules.d/80-hilscher-netx.rules \
                ${nonarch_base_libdir}/udev/rules.d/80-hilscher-cifxeth.rules \
                "
FILES:${PN}-plugin-spm += "/opt/cifx/plugins/ \
                           ${nonarch_base_libdir}/udev/rules.d/80-hilscher-netx-spi.rules"
