/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * [origin: Linux kernel arch/arm/mach-at91/include/mach/at91_wdt.h]
 *
 * Copyright (C) 2008 Jean-Christophe PLAGNIOL-VILLARD <plagnioj@jcrosoft.com>
 * Copyright (C) 2007 Andrew Victor
 * Copyright (C) 2018 Microchip Technology Inc.
 *
 * Watchdog Timer (WDT) - System peripherals regsters.
 * Based on AT91SAM9261 datasheet revision D.
 */

#ifndef AT91_WDT_H
#define AT91_WDT_H

#ifdef __ASSEMBLY__

#define AT91_ASM_WDT_MR	(ATMEL_BASE_WDT +  0x04)

#else

enum {
	AT91_WDT_MODE_SAM9260 = 0,
	AT91_WDT_MODE_SAM9X60 = 1
};

struct at91_wdt_priv {
	void __iomem *regs;
	u32 mr;
	u32 wddis;
	u8 mode;
};

#endif

/* Watchdog Control Register */
#define AT91_WDT_CR			0x00
#define AT91_WDT_CR_WDRSTT		1
#define AT91_WDT_CR_KEY			0xa5000000	/* KEY Password */

/* Watchdog Mode Register*/
#define AT91_WDT_MR			0x04
#define AT91_WDT_MR_WDV(x)		((x) & 0xfff)
#define AT91_SAM9X60_MR_PERIODRST	0x00000010
#define AT91_WDT_MR_WDFIEN		0x00001000
#define AT91_SAM9X60_MR_WDDIS		0x00001000
#define AT91_WDT_MR_WDRSTEN		0x00002000
#define AT91_WDT_MR_WDRPROC		0x00004000
#define AT91_WDT_MR_WDDIS		0x00008000
#define AT91_WDT_MR_WDD(x)		(((x) & 0xfff) << 16)
#define AT91_WDT_MR_WDDBGHLT		0x10000000
#define AT91_SAM9X60_MR_WDIDLEHLT	0x10000000
#define AT91_WDT_MR_WDIDLEHLT		0x20000000
#define AT91_SAM9X60_MR_WDDBGHLT	0x20000000

/* Watchdog Window Level Register */
#define AT91_SAM9X60_WLR		0x0c
#define AT91_SAM9X60_WLR_COUNTER(x)	((x) & 0xfff)

/* Hardware timeout in seconds */
#define WDT_MAX_TIMEOUT		16

#endif
