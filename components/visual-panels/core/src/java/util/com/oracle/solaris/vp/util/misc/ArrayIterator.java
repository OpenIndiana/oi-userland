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

public class ArrayIterator<T> implements Iterator<T>, Iterable<T> {
    //
    // Instance data
    //

    private T[] array;
    private int index;

    //
    // Constructors
    //

    public ArrayIterator(T... array) {
	this.array = array;
        reset();
    }

    //
    // Iterator methods
    //

    @Override
    public boolean hasNext() {
        return index < array.length;
    }

    @Override
    public T next() {
        try {
            return array[index++];
        } catch (ArrayIndexOutOfBoundsException e) {
            throw new NoSuchElementException();
        }
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }

    //
    // Iterable methods
    //

    @Override
    public Iterator<T> iterator() {
        return this;
    }

    //
    // ArrayIterator methods
    //

    public void reset() {
        index = 0;
    }
}
