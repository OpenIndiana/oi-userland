/*
 * Copyright (c) 2010, 2015, Oracle and/or its affiliates. All rights reserved.
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

/*
 * Avoid dragging in all the inline functions that cause invalid references
 * to Xserver & libpixman symbols to appear in the mdb module, but provide
 * stub typedefs needed by other headers from the excluded files.
 */
/* include/regionstr.h */
#define REGIONSTRUCT_H
typedef struct pixman_region16 RegionRec, *RegionPtr;
typedef struct pixman_box16 BoxRec;
/* include/callback.h */
#define CALLBACK_H
typedef void (*CallbackProcPtr) (void *, void *, void *);

/* Xserver_client.c */
_X_HIDDEN int	client_walk_init(mdb_walk_state_t *wsp);
_X_HIDDEN int	client_walk_step(mdb_walk_state_t *wsp);
_X_HIDDEN void	client_walk_fini(mdb_walk_state_t *wsp);
_X_HIDDEN int	client_pids(uintptr_t addr, uint_t flags,
			    int argc, const mdb_arg_t *argv);
_X_HIDDEN void	client_pids_help(void);
			    
/* Xserver_device_grabs.c */
_X_HIDDEN int	inputdev_walk_init(mdb_walk_state_t *wsp);
_X_HIDDEN int	inputdev_walk_step(mdb_walk_state_t *wsp);
_X_HIDDEN void	inputdev_walk_fini(mdb_walk_state_t *wsp);
_X_HIDDEN int	inputdev_grabs(uintptr_t addr, uint_t flags,
			       int argc, const mdb_arg_t *argv);
_X_HIDDEN void	inputdev_grabs_help(void);

#endif /* _XSERVER_MDB_H */
