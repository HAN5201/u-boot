// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2002
 * Rich Ireland, Enterasys Networks, rireland@enterasys.com.
 */

/* Generic FPGA support */
#include <init.h>
#include <log.h>
#include <xilinx.h>             /* xilinx specific definitions */
#include <altera.h>             /* altera specific definitions */
#include <lattice.h>
#include <dm/device_compat.h>

/* Local static data */
static int next_desc = FPGA_INVALID_DEVICE;
static fpga_desc desc_table[CONFIG_MAX_FPGA_DEVICES];

/* fpga_get_desc
 *	map a device number to a descriptor
 */
const fpga_desc *fpga_get_desc(int devnum)
{
	const fpga_desc *desc = NULL;

	if ((devnum >= 0) && (devnum < next_desc)) {
		desc = &desc_table[devnum];
		log_debug("found fpga descriptor #%d @ 0x%p\n",
			  devnum, desc);
	}

	return desc;
}

/*
 * fpga_validate
 *	generic parameter checking code
 */
const fpga_desc *fpga_validate(int devnum, const void *buf,
			       size_t bsize)
{
	const fpga_desc *desc = fpga_get_desc(devnum);

	if (!desc)
		log_err("Invalid device number %d\n", devnum);

	if (!buf) {
		log_err("Null buffer.\n");
		return NULL;
	}
	return desc;
}

/*
 * fpga_dev_info
 *	generic multiplexing code
 */
static int fpga_dev_info(int devnum)
{
	int ret_val = FPGA_FAIL; /* assume failure */
	const fpga_desc *desc = fpga_get_desc(devnum);

	if (desc) {
		log_info("Device Descriptor @ 0x%p\n",
			 desc->devdesc);

		switch (desc->devtype) {
		case fpga_xilinx:
#if defined(CONFIG_FPGA_XILINX)
			log_info("Xilinx Device\nDescriptor @ 0x%p\n", desc);
			ret_val = xilinx_info(desc->devdesc);
#else
			log_err("No support for Xilinx devices.\n");
#endif
			break;
		case fpga_altera:
#if defined(CONFIG_FPGA_ALTERA)
			log_info("Altera Device\nDescriptor @ 0x%p\n", desc);
			ret_val = altera_info(desc->devdesc);
#else
			log_err("No support for Altera devices.\n");
#endif
			break;
		case fpga_lattice:
#if defined(CONFIG_FPGA_LATTICE)
			log_info("Lattice Device\nDescriptor @ 0x%p\n", desc);
			ret_val = lattice_info(desc->devdesc);
#else
			log_err("No support for Lattice devices.\n");
#endif
			break;
		default:
			log_err("Invalid or unsupported device type %d\n",
				desc->devtype);
		}
	} else {
		log_err("Invalid device number %d\n", devnum);
	}

	return ret_val;
}

/*
 * fpga_init is usually called from misc_init_r() and MUST be called
 * before any of the other fpga functions are used.
 */
void fpga_init(void)
{
	next_desc = 0;
	memset(desc_table, 0, sizeof(desc_table));

	debug("%s\n", __func__);
}

/*
 * fpga_count
 * Basic interface function to get the current number of devices available.
 */
int fpga_count(void)
{
	return next_desc;
}

/*
 * fpga_add
 *	Add the device descriptor to the device table.
 */
int fpga_add(fpga_type devtype, void *desc)
{
	int devnum = FPGA_INVALID_DEVICE;

	if (!desc) {
		log_err("NULL device descriptor\n");
		return devnum;
	}

	if (next_desc < 0) {
		log_err("FPGA support not initialized!\n");
	} else if ((devtype > fpga_min_type) && (devtype < fpga_undefined)) {
		if (next_desc < CONFIG_MAX_FPGA_DEVICES) {
			devnum = next_desc;
			desc_table[next_desc].devtype = devtype;
			desc_table[next_desc++].devdesc = desc;
		} else {
			log_err("Exceeded Max FPGA device count\n");
		}
	} else {
		log_err("Unsupported FPGA type %d\n", devtype);
	}

	return devnum;
}

/*
 * Return 1 if the fpga data is partial.
 * This is only required for fpga drivers that support bitstream_type.
 */
int __weak fpga_is_partial_data(int devnum, size_t img_len)
{
	return 0;
}

/*
 * Convert bitstream data and load into the fpga
 */
int __weak fpga_loadbitstream(int devnum, char *fpgadata, size_t size,
			      bitstream_type bstype)
{
	log_err("Bitstream support not implemented for this FPGA device\n");
	return FPGA_FAIL;
}

#if defined(CONFIG_CMD_FPGA_LOADFS)
int fpga_fsload(int devnum, const void *buf, size_t size,
		 fpga_fs_info *fpga_fsinfo)
{
	int ret_val = FPGA_FAIL;           /* assume failure */
	const fpga_desc *desc = fpga_validate(devnum, buf, size);

	if (desc) {
		switch (desc->devtype) {
		case fpga_xilinx:
#if defined(CONFIG_FPGA_XILINX)
			ret_val = xilinx_loadfs(desc->devdesc, buf, size,
						fpga_fsinfo);
#else
			log_err("No support for Xilinx devices.\n");
#endif
			break;
		default:
			log_err("Invalid or unsupported device type %d\n",
				desc->devtype);
		}
	}

	return ret_val;
}
#endif

#if CONFIG_IS_ENABLED(FPGA_LOAD_SECURE)
int fpga_loads(int devnum, const void *buf, size_t size,
	       struct fpga_secure_info *fpga_sec_info)
{
	int ret_val = FPGA_FAIL;

	const fpga_desc *desc = fpga_validate(devnum, buf, size);

	if (desc) {
		switch (desc->devtype) {
		case fpga_xilinx:
#if defined(CONFIG_FPGA_XILINX)
			ret_val = xilinx_loads(desc->devdesc, buf, size,
					       fpga_sec_info);
#else
			log_err("No support for Xilinx devices.\n");
#endif
			break;
		default:
			log_err("Invalid or unsupported device type %d\n",
				desc->devtype);
		}
	}

	return ret_val;
}
#endif

static int fpga_load_event_notify(const void *buf, size_t bsize, int result)
{
	if (CONFIG_IS_ENABLED(EVENT)) {
		struct event_fpga_load load = {
			.buf = buf,
			.bsize = bsize,
			.result = result
		};

		return event_notify(EVT_FPGA_LOAD, &load, sizeof(load));
	}

	return 0;
}

/*
 * Generic multiplexing code
 */
int fpga_load(int devnum, const void *buf, size_t bsize, bitstream_type bstype,
	      int flags)
{
	int ret_val = FPGA_FAIL;           /* assume failure */
	int ret_notify;
	const fpga_desc *desc = fpga_validate(devnum, buf, bsize);

	if (desc) {
		switch (desc->devtype) {
		case fpga_xilinx:
#if defined(CONFIG_FPGA_XILINX)
			ret_val = xilinx_load(desc->devdesc, buf, bsize,
					      bstype, flags);
#else
			log_err("No support for Xilinx devices.\n");
#endif
			break;
		case fpga_altera:
#if defined(CONFIG_FPGA_ALTERA)
			ret_val = altera_load(desc->devdesc, buf, bsize);
#else
			log_err("No support for Altera devices.\n");
#endif
			break;
		case fpga_lattice:
#if defined(CONFIG_FPGA_LATTICE)
			ret_val = lattice_load(desc->devdesc, buf, bsize);
#else
			log_err("No support for Lattice devices.\n");
#endif
			break;
		default:
			log_err("Invalid or unsupported device type %d\n",
				desc->devtype);
		}
	}

	ret_notify = fpga_load_event_notify(buf, bsize, ret_val);
	if (ret_notify)
		return ret_notify;

	return ret_val;
}

/*
 * fpga_dump
 *	generic multiplexing code
 */
int fpga_dump(int devnum, const void *buf, size_t bsize)
{
	int ret_val = FPGA_FAIL;           /* assume failure */
	const fpga_desc *desc = fpga_validate(devnum, buf, bsize);

	if (desc) {
		switch (desc->devtype) {
		case fpga_xilinx:
#if defined(CONFIG_FPGA_XILINX)
			ret_val = xilinx_dump(desc->devdesc, buf, bsize);
#else
			log_err("No support for Xilinx devices.\n");
#endif
			break;
		case fpga_altera:
#if defined(CONFIG_FPGA_ALTERA)
			ret_val = altera_dump(desc->devdesc, buf, bsize);
#else
			log_err("No support for Altera devices.\n");
#endif
			break;
		case fpga_lattice:
#if defined(CONFIG_FPGA_LATTICE)
			ret_val = lattice_dump(desc->devdesc, buf, bsize);
#else
			log_err("No support for Lattice devices.\n");
#endif
			break;
		default:
			log_err("Invalid or unsupported device type %d\n",
				desc->devtype);
		}
	}

	return ret_val;
}

/*
 * fpga_info
 *	front end to fpga_dev_info.  If devnum is invalid, report on all
 *	available devices.
 */
int fpga_info(int devnum)
{
	if (devnum == FPGA_INVALID_DEVICE) {
		if (next_desc > 0) {
			int dev;

			for (dev = 0; dev < next_desc; dev++)
				fpga_dev_info(dev);

			return FPGA_SUCCESS;
		} else {
			log_err("No FPGA devices available.\n");
			return FPGA_FAIL;
		}
	}

	return fpga_dev_info(devnum);
}

#if CONFIG_IS_ENABLED(FPGA_LOAD_SECURE)
int fpga_compatible2flag(int devnum, const char *compatible)
{
	const fpga_desc *desc = fpga_get_desc(devnum);

	if (!desc)
		return 0;

	switch (desc->devtype) {
#if defined(CONFIG_FPGA_XILINX)
	case fpga_xilinx:
	{
		xilinx_desc *xdesc = (xilinx_desc *)desc->devdesc;

		if (xdesc->operations && xdesc->operations->str2flag)
			return xdesc->operations->str2flag(xdesc, compatible);
	}
#endif
	default:
		break;
	}

	return 0;
}
#endif
