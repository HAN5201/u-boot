# SPDX-License-Identifier: GPL-2.0+
#
# (C) Copyright 2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.

obj-$(CONFIG_$(PHASE_)DM_SPI_FLASH) += sf-uclass.o
spi-nor-y := sf_probe.o spi-nor-ids.o

ifdef CONFIG_XPL_BUILD
obj-$(CONFIG_SPL_SPI_BOOT)	+= fsl_espi_spl.o
ifeq ($(CONFIG_$(PHASE_)SPI_FLASH_TINY),y)
spi-nor-y += spi-nor-tiny.o
else
spi-nor-y += spi-nor-core.o
endif
else
spi-nor-y += spi-nor-core.o
endif

obj-$(CONFIG_SPI_FLASH) += spi-nor.o
obj-$(CONFIG_SPI_FLASH_DATAFLASH) += sf_dataflash.o
obj-$(CONFIG_$(PHASE_)SPI_FLASH_MTD) += sf_mtd.o
obj-$(CONFIG_SPI_FLASH_SANDBOX) += sandbox.o
obj-$(CONFIG_$(PHASE_)BOOTDEV_SPI_FLASH) += sf_bootdev.o
