/*
    libparted - a library for manipulating disk partitions
    Copyright (C) 2004, 2005, 2007 Free Software Foundation, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _PROBE_H
#define _PROBE_H

#include <parted/parted.h>
#include <parted/endian.h>
#include <parted/debug.h>

#include "hfs.h"

int
hfsc_can_use_geom (PedGeometry* geom);

PedGeometry*
hfs_and_wrapper_probe (PedGeometry* geom);

PedGeometry*
hfsplus_probe (PedGeometry* geom);

PedGeometry*
hfs_probe (PedGeometry* geom);

PedGeometry*
hfsx_probe (PedGeometry* geom);

#endif /* _PROBE_H */
