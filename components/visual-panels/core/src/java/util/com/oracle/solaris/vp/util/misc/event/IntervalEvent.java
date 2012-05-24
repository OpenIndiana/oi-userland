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
 */

/*
 * Copyright (c) 2009, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.util.misc.event;

import java.util.EventObject;

@SuppressWarnings({"serial"})
public class IntervalEvent extends EventObject {
    //
    // Instance data
    //

    private int firstIndex;
    private int lastIndex;

    //
    // Constructors
    //

    public IntervalEvent(Object source, int firstIndex,
	int lastIndex) {

	super(source);
	this.firstIndex = firstIndex;
	this.lastIndex = lastIndex;
    }

    public IntervalEvent(Object source, int index) {
	this(source, index, index);
    }

    //
    // IntervalEvent methods
    //

    public int getFirstIndex() {
	return firstIndex;
    }

    public int getLastIndex() {
	return lastIndex;
    }
}
