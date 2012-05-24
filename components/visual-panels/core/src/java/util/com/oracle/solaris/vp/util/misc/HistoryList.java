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

package com.oracle.solaris.vp.util.misc;

import java.util.*;

/**
 * The {@code HistoryList} class encapsulates a traversable list and a pointer
 * to the "current" insertion point in that list.  The pointer can be
 * incremented or decremented (within the range of the list) without affecting
 * the data within the list.
 * <p>
 * When an element is added to the list, all elements from the current position
 * of the pointer to the end of the list are first removed.
 */
public class HistoryList<E> implements Stackable<E> {
    //
    // Instance data
    //

    private List<E> data = new LinkedList<E>();
    private int pointer;

    //
    // Stackable methods
    //

    /**
     * Removes all elements from the list and sets the pointer to zero.
     */
    @Override
    public void clear() {
	data.clear();
	pointer = 0;
    }

    /**
     * Gets the number of items before the pointer.
     */
    @Override
    public int getCount() {
	return pointer;
    }

    /**
     * Retrieves the element immediately before the position of the pointer, or
     * {@code null} if the pointer is at the beginning of the list.  Note that
     * this only returns the last element of the list if the pointer is at the
     * end of the list.
     */
    @Override
    public E peek() {
	try {
	    return peekOrErr();
	} catch (NoSuchElementException e) {
	    return null;
	}
    }

    /**
     * Retrieves the element immediately before the position of the pointer.
     * Note that this only returns the last element of the list if the pointer
     * is at the end of the list.
     *
     * @exception   NoSuchElementException
     *		    if the pointer is at the beginning of the list
     */
    @Override
    public E peekOrErr() {
	try {
	    return data.get(pointer - 1);
	} catch (IndexOutOfBoundsException e) {
	    throw new NoSuchElementException();
	}
    }

    @Override
    public E peekOrErr(int n) {
	return data.get(pointer - 1 - n);
    }

    /**
     * Removes the element immediately before the position of the pointer, and
     * all elements following.
     *
     * @return	    the element immediately before the position of the pointer,
     *		    prior to the removal
     *
     * @exception   NoSuchElementException
     *		    if the pointer is at the beginning of the list
     */
    @Override
    public E pop() {
	try {
	    E datum = data.remove(pointer - 1);
	    goBack();
	    clearForward();
	    return datum;
	} catch (IndexOutOfBoundsException e) {
	    throw new NoSuchElementException();
	}
    }

    /**
     * Removes all elements from the position of the pointer to the end of the
     * list, then adds the given element the list end of the list.
     */
    @Override
    public void push(E element) {
	clearForward();
	data.add(element);
	goForward();
    }

    //
    // HistoryList methods
    //

    /**
     * Removes all elements from the position of the pointer to the end of the
     * list.
     */
    public void clearForward() {
	for (int i = data.size() - 1; i >= pointer; i--) {
	    data.remove(i);
	}
    }

    /**
     * Gets the full number of items in the list, regardless of the position of
     * the pointer.
     */
    public int getFullCount() {
	return data.size();
    }

    /**
     * Returns the current insertion point in the history list.
     */
    public int getPointer() {
	return pointer;
    }

    /**
     * Decrements the position of the pointer.
     *
     * @exception   NoSuchElementException
     *		    if the pointer is at the beginning of the list
     */
    public void goBack() {
	if (pointer == 0) {
	    throw new NoSuchElementException(
		"cannot move beyond beginning of list");
	}
	pointer--;
    }

    /**
     * Increments the position of the pointer.
     *
     * @exception   NoSuchElementException
     *		    if the pointer is at the end of the list
     */
    public void goForward() {
	if (pointer == data.size()) {
	    throw new NoSuchElementException(
		"cannot move beyond end of list");
	}
	pointer++;
    }

    /**
     * Retrieves the element at the position of the pointer.  Note that this
     * returns the element immediately <i>after</i> the element returned by
     * {@link #peek}.
     *
     * @exception   NoSuchElementException
     *		    if the pointer is at the end of the list
     */
    public E peekForward() {
	try {
	    return data.get(pointer);
	} catch (IndexOutOfBoundsException e) {
	    throw new NoSuchElementException();
	}
    }
}
