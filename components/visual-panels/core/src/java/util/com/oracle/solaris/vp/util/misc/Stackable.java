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

/**
 * The {@code Stackable} interface represents a last-in-first-out (LIFO) queue.
 */
public interface Stackable<E> {
    /**
     * Clears the stack.
     */
    void clear();

    /**
     * Gets the number of elements in the stack.
     */
    int getCount();

    /**
     * Gets the element at the top of the stack, or {@code null} if the stack
     * contains no elements
     */
    E peek();

    /**
     * Gets the element at the top of the stack.  Equivalent to {@link
     * #peekOrErr peekOrErr}{@code (0)};
     *
     * @exception   NoSuchElementException
     *		    if the stack contains no elements
     */
    E peekOrErr();

    /**
     * Gets the {@code n}th element at the top of the stack.
     *
     * @param	    n
     *		    an integer between 0 and {@link #getCount getCount()} {@code
     *		    - 1}, inclusive
     *
     * @exception   NoSuchElementException
     *		    if n is invalid
     */
    E peekOrErr(int n);

    /**
     * Removes the element at the top of the stack.
     *
     * @return	    the removed element
     *
     * @exception   NoSuchElementException
     *		    if the stack contains no elements
     */
    E pop();

    /**
     * Adds the given element to the stack.
     */
    void push(E element);
}
