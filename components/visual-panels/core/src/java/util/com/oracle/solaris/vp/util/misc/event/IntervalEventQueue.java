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

public class IntervalEventQueue {
    //
    // Enums
    //

    public enum Type {
	ADD,
	REMOVE,
    }

    //
    // Instance data
    //

    private IntervalEventSource source;
    private IntervalListeners listeners;
    private Type type;
    private int first;
    private int last;

    //
    // Constructors
    //

    public IntervalEventQueue(IntervalEventSource source,
	IntervalListeners listeners) {

	this.source = source;
	this.listeners = listeners;
    }

    //
    // IntervalEventQueue methods
    //

    public synchronized void addInterval(int f, int l, Type t) {
	if (f > l || f < 0)
	    throw new IllegalArgumentException(Integer.toString(f));

	/*
	 * We need to map l and f to pre-previous-removes values so we
	 * can accurately compare them to first and last.  (The tests we
	 * perform are invariant under addition, so we only need to do
	 * this for removes).
	 */
	int rawf = f;
	int rawl = l;
	if (type == Type.REMOVE && t == Type.REMOVE) {
	    int total = last - first + 1;
	    if (f >= first)
		f += total;
	    if (l >= first)
		l += total;
	}

	/*
	 * If this is a new event type or a disjoint interval, flush
	 * and start with a fresh interval.
	 */
	if (t != type || l < first  - 1 || f > last + 1) {
	    flush();
	    first = rawf;
	    last = rawl;
	    type = t;
	    return;
	}

	/*
	 * Extend the range as necessary.
	 */
	if (type == Type.REMOVE) {
	    /*
	     * We abut or straddle the existing range; extend the
	     * appropriate limits.
	     */
	    first = Math.min(f, first);
	    last = Math.max(l, last);
	} else {
	    /*
	     * We're inserting into the existing range; add our length
	     * to its.
	     */
	    last += (l - f + 1);
	}
    }

    public void addIndex(int index, Type type) {
	addInterval(index, index, type);
    }

    public synchronized void flush() {
	if (type != null) {
	    switch (type) {
		case ADD:
		    listeners.intervalAdded(
			new IntervalEvent(source, first, last));
		    break;

		case REMOVE:
		    listeners.intervalRemoved(
			new IntervalEvent(source, first, last));
		    break;
	    }
	}
	type = null;
    }

    public synchronized int getFirstIndex() {
	return first;
    }

    public synchronized int getLastIndex() {
	return last;
    }

    public synchronized Type getType() {
	return type;
    }
}
