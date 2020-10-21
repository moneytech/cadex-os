/*
Copyright (C) 2019-2020 The CadexOS Project
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef CDROMFS_H
#define CDROMFS_H

#include "kernel/types.h"

#define CDROMFS_BLOCK_SIZE 2048

struct cdrom_volume {
    int root_sector;
    int root_length;
    int total_sectors;
};

struct cdrom_dirent {
    int sector;
};

int cdrom_init();

#endif
