// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    harddisk.h

    Generic MAME hard disk implementation, with differencing files

***************************************************************************/

#ifndef MAME_LIB_UTIL_HARDDISK_H
#define MAME_LIB_UTIL_HARDDISK_H

#pragma once

#include "chd.h"
#include "utilfwd.h"

#include "osdcore.h"


class hard_disk_file {
public:
	struct info
	{
		uint32_t          cylinders;
		uint32_t          heads;
		uint32_t          sectors;
		uint32_t          sectorbytes;
		uint32_t          fileoffset;       // offset in the file where the HDD image starts.  not valid for CHDs.
	};


	hard_disk_file(chd_file *chd);
	hard_disk_file(util::random_read_write &corefile, uint32_t skipoffs);

	~hard_disk_file();

	chd_file *get_chd() const { return chd; }
	const info &get_info() const { return hdinfo; }

	bool set_block_size(uint32_t blocksize);

	bool read(uint32_t lbasector, void *buffer);
	bool write(uint32_t lbasector, const void *buffer);

private:
	chd_file *                  chd;        // CHD file
	util::random_read_write *   fhandle;    // file if not a CHD
	info                        hdinfo;     // hard disk info
};

#endif // MAME_LIB_UTIL_HARDDISK_H
