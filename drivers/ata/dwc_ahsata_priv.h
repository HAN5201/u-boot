/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2010 Freescale Semiconductor, Inc.
 * Terry Lv <r65388@freescale.com>
 */

#ifndef __DWC_AHSATA_PRIV_H__
#define __DWC_AHSATA_PRIV_H__

/* Max host controller numbers */
#define SATA_HC_MAX_NUM		4
/* Max command queue depth per host controller */
#define DWC_AHSATA_HC_MAX_CMD	32
/* Max port number per host controller */
#define SATA_HC_MAX_PORT	16

/* Generic Host Register */

/* HBA Capabilities Register */
#define SATA_HOST_CAP_S64A		0x80000000
#define SATA_HOST_CAP_SNCQ		0x40000000
#define SATA_HOST_CAP_SSNTF		0x20000000
#define SATA_HOST_CAP_SMPS		0x10000000
#define SATA_HOST_CAP_SSS		0x08000000
#define SATA_HOST_CAP_SALP		0x04000000
#define SATA_HOST_CAP_SAL		0x02000000
#define SATA_HOST_CAP_SCLO		0x01000000
#define SATA_HOST_CAP_ISS_MASK		0x00f00000
#define SATA_HOST_CAP_ISS_OFFSET	20
#define SATA_HOST_CAP_SNZO		0x00080000
#define SATA_HOST_CAP_SAM		0x00040000
#define SATA_HOST_CAP_SPM		0x00020000
#define SATA_HOST_CAP_PMD		0x00008000
#define SATA_HOST_CAP_SSC		0x00004000
#define SATA_HOST_CAP_PSC		0x00002000
#define SATA_HOST_CAP_NCS		0x00001f00
#define SATA_HOST_CAP_CCCS		0x00000080
#define SATA_HOST_CAP_EMS		0x00000040
#define SATA_HOST_CAP_SXS		0x00000020
#define SATA_HOST_CAP_NP_MASK		0x0000001f

/* Global HBA Control Register */
#define SATA_HOST_GHC_AE	0x80000000
#define SATA_HOST_GHC_IE	0x00000002
#define SATA_HOST_GHC_HR	0x00000001

/* Interrupt Status Register */

/* Ports Implemented Register */

/* AHCI Version Register */
#define SATA_HOST_VS_MJR_MASK	0xffff0000
#define SATA_HOST_VS_MJR_OFFSET	16
#define SATA_HOST_VS_MJR_MNR	0x0000ffff

/* Command Completion Coalescing Control */
#define SATA_HOST_CCC_CTL_TV_MASK	0xffff0000
#define SATA_HOST_CCC_CTL_TV_OFFSET		16
#define SATA_HOST_CCC_CTL_CC_MASK	0x0000ff00
#define SATA_HOST_CCC_CTL_CC_OFFSET		8
#define SATA_HOST_CCC_CTL_INT_MASK	0x000000f8
#define SATA_HOST_CCC_CTL_INT_OFFSET	3
#define SATA_HOST_CCC_CTL_EN	0x00000001

/* Command Completion Coalescing Ports */

/* HBA Capabilities Extended Register */
#define SATA_HOST_CAP2_APST		0x00000004

/* BIST Activate FIS Register */
#define SATA_HOST_BISTAFR_NCP_MASK	0x0000ff00
#define SATA_HOST_BISTAFR_NCP_OFFSET	8
#define SATA_HOST_BISTAFR_PD_MASK	0x000000ff
#define SATA_HOST_BISTAFR_PD_OFFSET		0

/* BIST Control Register */
#define SATA_HOST_BISTCR_FERLB	0x00100000
#define SATA_HOST_BISTCR_TXO	0x00040000
#define SATA_HOST_BISTCR_CNTCLR	0x00020000
#define SATA_HOST_BISTCR_NEALB	0x00010000
#define SATA_HOST_BISTCR_LLC_MASK	0x00000700
#define SATA_HOST_BISTCR_LLC_OFFSET	8
#define SATA_HOST_BISTCR_ERREN	0x00000040
#define SATA_HOST_BISTCR_FLIP	0x00000020
#define SATA_HOST_BISTCR_PV		0x00000010
#define SATA_HOST_BISTCR_PATTERN_MASK	0x0000000f
#define SATA_HOST_BISTCR_PATTERN_OFFSET	0

/* BIST FIS Count Register */

/* BIST Status Register */
#define SATA_HOST_BISTSR_FRAMERR_MASK	0x0000ffff
#define SATA_HOST_BISTSR_FRAMERR_OFFSET	0
#define SATA_HOST_BISTSR_BRSTERR_MASK	0x00ff0000
#define SATA_HOST_BISTSR_BRSTERR_OFFSET	16

/* BIST DWORD Error Count Register */

/* OOB Register*/
#define SATA_HOST_OOBR_WE		0x80000000
#define SATA_HOST_OOBR_cwMin_MASK	0x7f000000
#define SATA_HOST_OOBR_cwMAX_MASK	0x00ff0000
#define SATA_HOST_OOBR_ciMin_MASK	0x0000ff00
#define SATA_HOST_OOBR_ciMax_MASK	0x000000ff

/* Timer 1-ms Register */

/* Global Parameter 1 Register */
#define SATA_HOST_GPARAM1R_ALIGN_M	0x80000000
#define SATA_HOST_GPARAM1R_RX_BUFFER	0x40000000
#define SATA_HOST_GPARAM1R_PHY_DATA_MASK	0x30000000
#define SATA_HOST_GPARAM1R_PHY_RST	0x08000000
#define SATA_HOST_GPARAM1R_PHY_CTRL_MASK	0x07e00000
#define SATA_HOST_GPARAM1R_PHY_STAT_MASK	0x001f8000
#define SATA_HOST_GPARAM1R_LATCH_M	0x00004000
#define SATA_HOST_GPARAM1R_BIST_M	0x00002000
#define SATA_HOST_GPARAM1R_PHY_TYPE	0x00001000
#define SATA_HOST_GPARAM1R_RETURN_ERR	0x00000400
#define SATA_HOST_GPARAM1R_AHB_ENDIAN_MASK	0x00000300
#define SATA_HOST_GPARAM1R_S_HADDR	0x00000080
#define SATA_HOST_GPARAM1R_M_HADDR	0x00000040

/* Global Parameter 2 Register */
#define SATA_HOST_GPARAM2R_DEV_CP	0x00004000
#define SATA_HOST_GPARAM2R_DEV_MP	0x00002000
#define SATA_HOST_GPARAM2R_DEV_ENCODE_M	0x00001000
#define SATA_HOST_GPARAM2R_RXOOB_CLK_M	0x00000800
#define SATA_HOST_GPARAM2R_RXOOB_M	0x00000400
#define SATA_HOST_GPARAM2R_TX_OOB_M	0x00000200
#define SATA_HOST_GPARAM2R_RXOOB_CLK_MASK	0x000001ff

/* Port Parameter Register */
#define SATA_HOST_PPARAMR_TX_MEM_M	0x00000200
#define SATA_HOST_PPARAMR_TX_MEM_S	0x00000100
#define SATA_HOST_PPARAMR_RX_MEM_M	0x00000080
#define SATA_HOST_PPARAMR_RX_MEM_S	0x00000040
#define SATA_HOST_PPARAMR_TXFIFO_DEPTH_MASK	0x00000038
#define SATA_HOST_PPARAMR_RXFIFO_DEPTH_MASK	0x00000007

/* Test Register */
#define SATA_HOST_TESTR_PSEL_MASK	0x00070000
#define SATA_HOST_TESTR_TEST_IF		0x00000001

/* Port Register Descriptions */
/* Port# Command List Base Address Register */
#define SATA_PORT_CLB_CLB_MASK		0xfffffc00

/* Port# Command List Base Address Upper 32-Bits Register */

/* Port# FIS Base Address Register */
#define SATA_PORT_FB_FB_MASK		0xfffffff0

/* Port# FIS Base Address Upper 32-Bits Register */

/* Port# Interrupt Status Register */
#define SATA_PORT_IS_CPDS		0x80000000
#define SATA_PORT_IS_TFES		0x40000000
#define SATA_PORT_IS_HBFS		0x20000000
#define SATA_PORT_IS_HBDS		0x10000000
#define SATA_PORT_IS_IFS		0x08000000
#define SATA_PORT_IS_INFS		0x04000000
#define SATA_PORT_IS_OFS		0x01000000
#define SATA_PORT_IS_IPMS		0x00800000
#define SATA_PORT_IS_PRCS		0x00400000
#define SATA_PORT_IS_DMPS		0x00000080
#define SATA_PORT_IS_PCS		0x00000040
#define SATA_PORT_IS_DPS		0x00000020
#define SATA_PORT_IS_UFS		0x00000010
#define SATA_PORT_IS_SDBS		0x00000008
#define SATA_PORT_IS_DSS		0x00000004
#define SATA_PORT_IS_PSS		0x00000002
#define SATA_PORT_IS_DHRS		0x00000001

/* Port# Interrupt Enable Register */
#define SATA_PORT_IE_CPDE		0x80000000
#define SATA_PORT_IE_TFEE		0x40000000
#define SATA_PORT_IE_HBFE		0x20000000
#define SATA_PORT_IE_HBDE		0x10000000
#define SATA_PORT_IE_IFE		0x08000000
#define SATA_PORT_IE_INFE		0x04000000
#define SATA_PORT_IE_OFE		0x01000000
#define SATA_PORT_IE_IPME		0x00800000
#define SATA_PORT_IE_PRCE		0x00400000
#define SATA_PORT_IE_DMPE		0x00000080
#define SATA_PORT_IE_PCE		0x00000040
#define SATA_PORT_IE_DPE		0x00000020
#define SATA_PORT_IE_UFE		0x00000010
#define SATA_PORT_IE_SDBE		0x00000008
#define SATA_PORT_IE_DSE		0x00000004
#define SATA_PORT_IE_PSE		0x00000002
#define SATA_PORT_IE_DHRE		0x00000001

/* Port# Command Register */
#define SATA_PORT_CMD_ICC_MASK		0xf0000000
#define SATA_PORT_CMD_ASP		0x08000000
#define SATA_PORT_CMD_ALPE		0x04000000
#define SATA_PORT_CMD_DLAE		0x02000000
#define SATA_PORT_CMD_ATAPI		0x01000000
#define SATA_PORT_CMD_APSTE		0x00800000
#define SATA_PORT_CMD_ESP		0x00200000
#define SATA_PORT_CMD_CPD		0x00100000
#define SATA_PORT_CMD_MPSP		0x00080000
#define SATA_PORT_CMD_HPCP		0x00040000
#define SATA_PORT_CMD_PMA		0x00020000
#define SATA_PORT_CMD_CPS		0x00010000
#define SATA_PORT_CMD_CR		0x00008000
#define SATA_PORT_CMD_FR		0x00004000
#define SATA_PORT_CMD_MPSS		0x00002000
#define SATA_PORT_CMD_CCS_MASK		0x00001f00
#define SATA_PORT_CMD_FRE		0x00000010
#define SATA_PORT_CMD_CLO		0x00000008
#define SATA_PORT_CMD_POD		0x00000004
#define SATA_PORT_CMD_SUD		0x00000002
#define SATA_PORT_CMD_ST		0x00000001

/* Port# Task File Data Register */
#define SATA_PORT_TFD_ERR_MASK		0x0000ff00
#define SATA_PORT_TFD_STS_MASK		0x000000ff
#define SATA_PORT_TFD_STS_ERR		0x00000001
#define SATA_PORT_TFD_STS_DRQ		0x00000008
#define SATA_PORT_TFD_STS_BSY		0x00000080

/* Port# Signature Register */

/* Port# Serial ATA Status {SStatus} Register */
#define SATA_PORT_SSTS_IPM_MASK		0x00000f00
#define SATA_PORT_SSTS_SPD_MASK		0x000000f0
#define SATA_PORT_SSTS_DET_MASK		0x0000000f

/* Port# Serial ATA Control {SControl} Register */
#define SATA_PORT_SCTL_IPM_MASK		0x00000f00
#define SATA_PORT_SCTL_SPD_MASK		0x000000f0
#define SATA_PORT_SCTL_DET_MASK		0x0000000f

/* Port# Serial ATA Error {SError} Register */
#define SATA_PORT_SERR_DIAG_X		0x04000000
#define SATA_PORT_SERR_DIAG_F		0x02000000
#define SATA_PORT_SERR_DIAG_T		0x01000000
#define SATA_PORT_SERR_DIAG_S		0x00800000
#define SATA_PORT_SERR_DIAG_H		0x00400000
#define SATA_PORT_SERR_DIAG_C		0x00200000
#define SATA_PORT_SERR_DIAG_D		0x00100000
#define SATA_PORT_SERR_DIAG_B		0x00080000
#define SATA_PORT_SERR_DIAG_W		0x00040000
#define SATA_PORT_SERR_DIAG_I		0x00020000
#define SATA_PORT_SERR_DIAG_N		0x00010000
#define SATA_PORT_SERR_ERR_E		0x00000800
#define SATA_PORT_SERR_ERR_P		0x00000400
#define SATA_PORT_SERR_ERR_C		0x00000200
#define SATA_PORT_SERR_ERR_T		0x00000100
#define SATA_PORT_SERR_ERR_M		0x00000002
#define SATA_PORT_SERR_ERR_I		0x00000001

/* Port# Serial ATA Active {SActive} Register */

/* Port# Command Issue Register */

/* Port# Serial ATA Notification Register */

/* Port# DMA Control Register */
#define SATA_PORT_DMACR_RXABL_MASK	0x0000f000
#define SATA_PORT_DMACR_TXABL_MASK	0x00000f00
#define SATA_PORT_DMACR_RXTS_MASK	0x000000f0
#define SATA_PORT_DMACR_TXTS_MASK	0x0000000f

/* Port# PHY Control Register */

/* Port# PHY Status Register */

#define SATA_HC_CMD_HDR_ENTRY_SIZE	sizeof(struct cmd_hdr_entry)

/* DW0
*/
#define CMD_HDR_DI_CFL_MASK	0x0000001f
#define CMD_HDR_DI_CFL_OFFSET	0
#define CMD_HDR_DI_A			0x00000020
#define CMD_HDR_DI_W			0x00000040
#define CMD_HDR_DI_P			0x00000080
#define CMD_HDR_DI_R			0x00000100
#define CMD_HDR_DI_B			0x00000200
#define CMD_HDR_DI_C			0x00000400
#define CMD_HDR_DI_PMP_MASK	0x0000f000
#define CMD_HDR_DI_PMP_OFFSET	12
#define CMD_HDR_DI_PRDTL		0xffff0000
#define CMD_HDR_DI_PRDTL_OFFSET	16

/* prde_fis_len
*/
#define CMD_HDR_PRD_ENTRY_SHIFT	16
#define CMD_HDR_PRD_ENTRY_MASK	0x003f0000
#define CMD_HDR_FIS_LEN_SHIFT	2

/* attribute
*/
#define CMD_HDR_ATTR_RES	0x00000800 /* Reserved bit, should be 1 */
#define CMD_HDR_ATTR_VBIST	0x00000400 /* Vendor BIST */
/* Snoop enable for all descriptor */
#define CMD_HDR_ATTR_SNOOP	0x00000200
#define CMD_HDR_ATTR_FPDMA	0x00000100 /* FPDMA queued command */
#define CMD_HDR_ATTR_RESET	0x00000080 /* Reset - a SRST or device reset */
/* BIST - require the host to enter BIST mode */
#define CMD_HDR_ATTR_BIST	0x00000040
#define CMD_HDR_ATTR_ATAPI	0x00000020 /* ATAPI command */
#define CMD_HDR_ATTR_TAG	0x0000001f /* TAG mask */

#define FLAGS_DMA	0x00000000
#define FLAGS_FPDMA	0x00000001

#define SATA_FLAG_Q_DEP_MASK	0x0000000f
#define SATA_FLAG_WCACHE	0x00000100
#define SATA_FLAG_FLUSH		0x00000200
#define SATA_FLAG_FLUSH_EXT	0x00000400

#define READ_CMD	0
#define WRITE_CMD	1

#endif /* __DWC_AHSATA_H__ */
