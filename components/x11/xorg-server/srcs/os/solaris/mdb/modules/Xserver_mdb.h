/*
 * Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef _XSERVER_MDB_H
#define _XSERVER_MDB_H

#include <sys/mdb_modapi.h>
#include <X11/Xfuncproto.h>

/* Xserver_client.c */
_X_HIDDEN int	client_walk_init(mdb_walk_state_t *wsp);
_X_HIDDEN int	client_walk_step(mdb_walk_state_t *wsp);
_X_HIDDEN void	client_walk_fini(mdb_walk_state_t *wsp);
_X_HIDDEN int	client_pids(uintptr_t addr, uint_t flags,
			    int argc, const mdb_arg_t *argv);

/* Xserver_device_grabs.c */
_X_HIDDEN int	inputdev_walk_init(mdb_walk_state_t *wsp);
_X_HIDDEN int	inputdev_walk_step(mdb_walk_state_t *wsp);
_X_HIDDEN void	inputdev_walk_fini(mdb_walk_state_t *wsp);
_X_HIDDEN int	inputdev_grabs(uintptr_t addr, uint_t flags,
			       int argc, const mdb_arg_t *argv);

#endif /* _XSERVER_MDB_H */
