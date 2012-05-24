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

import java.util.*;

/**
 * The {@code EventListeners} class encapsulates event listener management.
 * <p/>
 * A note about thread safety: the {@link #add} and {@link #remove} methods are
 * synchronized to prevent concurrent modifications to the listener list.
 * However, {@link #dispatch} may safely iterate over this list while it's being
 * modified.
 * <p/>
 * The {@code Iterator}s returned by {@link #iterator}, however, will throw a
 * {@code ConcurrentModificationException} if the list changes during iteration.
 */
public class EventListeners<L> implements Iterable<L> {
    //
    // Inner classes
    //

    protected static class Entry<L> {
	public L data;
	public Entry<L> next;

	public Entry(L data) {
	    this.data = data;
	}
    }

    public class EntryIterator implements Iterator<L> {
	//
	// Instance data
	//

	private int expectedModCount = modCount;
	private Entry<L> entry = first;

	//
	// Iterator methods
	//

	@Override
	public boolean hasNext() {
	    synchronized (EventListeners.this) {
		checkForComodification();
		return entry.next != null;
	    }
	}

	@Override
	public L next() {
	    synchronized (EventListeners.this) {
		checkForComodification();
		entry = entry.next;
		return entry.data;
	    }
	}

	@Override
	public void remove() {
	    synchronized (EventListeners.this) {
		checkForComodification();
		if (EventListeners.this.remove(entry.data)) {
		    expectedModCount++;
		}
	    }
	}

	//
	// Private methods
	//

	private void checkForComodification() {
	    if (modCount != expectedModCount) {
		throw new ConcurrentModificationException();
	    }
	}
    }

    //
    // Instance data
    //

    private Entry<L> first;
    private int modCount;

    //
    // Iterable methods
    //

    @Override
    public Iterator<L> iterator() {
	return new EntryIterator();
    }

    //
    // EventListeners methods
    //

    /**
     * Adds a listener to the list to be notified by {@link #dispatch}.
     */
    public synchronized void add(L listener) {
	if (first == null) {
	    first = new Entry<L>(listener);
	    modCount++;
	} else {
	    for (Entry<L> entry = first; ; entry = entry.next) {
		if (entry.data == listener) {
		    return;
		}
		if (entry.next == null) {
		    entry.next = new Entry<L>(listener);
		    modCount++;
		    break;
		}
	    }
	}
    }

    /**
     * Removes all managed listeners.
     */
    public synchronized void clear() {
	first = null;
	modCount = 0;
    }

    /**
     * Notifies each listener of the given event, in the order in which they
     * were {@link #add add}ed.
     *
     * @param	    dispatcher
     *		    the dispatcher that knows how to deliver the event
     *
     * @param	    event
     *		    the event to be delivered
     */
    protected <E extends EventObject> void dispatch(
	EventDispatcher<E, L> dispatcher, E event) {

	for (Entry<L> entry = first; entry != null; entry = entry.next) {
	    L listener = entry.data;
	    dispatcher.dispatch(listener, event);
	}
    }

    /**
     * Removes a listener from the list to be notified by {@link #dispatch}.
     *
     * @return	    {@code true} if the list contained the given data, {@code
     *		    false} otherwise
     */
    public synchronized boolean remove(L listener) {
	boolean found = false;
	if (first != null) {
	    if (first.data == listener) {
		first = first.next;
		found = true;
		modCount++;
	    } else {
		for (Entry<L> entry = first; entry != null &&
		    entry.next != null; entry = entry.next) {

		    if (entry.next.data == listener) {
			entry.next = entry.next.next;
			found = true;
			modCount++;
		    }
		}
	    }
	}
	return found;
    }
}
