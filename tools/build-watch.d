#!/usr/sbin/dtrace -s -q
/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 *
 * Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved.
 *
 *
 * build-watch.d - a simple dtrace script to keep track of some key
 *		   information to help determine build dependencies.
 */

/*
 * record paths successfully opened
 */
syscall::open:entry, syscall::open64:entry
/(pid == $target) || progenyof($target)/
{
	self->file = cleanpath(copyinstr(arg0));
}
syscall::openat:entry
/(pid == $target) || progenyof($target)/
{
	self->file = cleanpath(copyinstr(arg1));
}

syscall::open*:return
/((pid == $target) || progenyof($target)) && (arg0 != -1) && (self->file != "")/
{
	@opened[self->file] = count();
	self->file = 0;
}

/*
 * record the programs successfully execed (full path names)
 */
proc:::exec
/(pid == $target) || progenyof($target)/
{
	self->execpath = stringof(arg0);
}

proc:::exec-success
/(pid == $target) || progenyof($target)/
{
	@tools[execname, self->execpath] = count();
	self->execpath = 0;
}

/*
 * Summarize the results of watching the [sub]process tree
 */
END
{
	printf("\n");
	printa("TOOL: %s = %s\n", @tools);
	printa("FILE: %s\n", @opened);
}
