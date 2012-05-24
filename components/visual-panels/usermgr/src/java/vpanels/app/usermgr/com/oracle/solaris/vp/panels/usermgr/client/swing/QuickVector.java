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
 * Copyright (c) 1998, 2012, Oracle and/or its affiliates. All rights reserved.
 */


package com.oracle.solaris.vp.panels.usermgr.client.swing;

import java.util.Vector;

/**
 * SMC code adapted for Visual Panels
 *
 * The <code>QuickVector</code> class extends the Vector class,
 * providing additional methods which allow faster
 * access to elements of the array.
 *
 */
public
class QuickVector extends Vector {

    /**
     * Constructs an empty vector with the specified initial capacity and
     * capacity increment.
     *
     * @param   initialCapacity	    the initial capacity of the vector.
     * @param   capacityIncrement   the amount by which the capacity is
     *				    increased when the vector overflows.
     */
    public QuickVector(int initialCapacity, int capacityIncrement) {
        super(initialCapacity, capacityIncrement);
    }

    /**
     * Constructs an empty vector with the specified initial capacity.
     *
     * @param   initialCapacity   the initial capacity of the vector.
     */
    public QuickVector(int initialCapacity) {
        super(initialCapacity);
    }

    /**
     * Constructs an empty vector.
     *
     */
    public QuickVector() {
        super();
    }

    /**
     * Returns the component at the specified index.
     *
     * @param	index   an index into this vector.
     * @return	the component at the specified index.
     * @exception  ArrayIndexOutOfBoundsException  if an invalid index was
     * given.
     */
    public final Object quickElementAt(int index) {
        if (index >= elementCount) {
            throw new ArrayIndexOutOfBoundsException(
		index + " >= " + elementCount);
        }
        return elementData[index];
    }

    /**
     * Sets the component at the specified <code>index</code> of this
     * vector to be the specified object. The previous component at that
     * position is discarded.
     * <p>
     * The index must be a value greater than or equal to <code>0</code>
     * and less than the current size of the vector.
     *
     * @param	obj	what the component is to be set to.
     * @param	index	the specified index.
     * @exception  ArrayIndexOutOfBoundsException  if the index was invalid.
     */
    public final void quickSetElementAt(Object obj, int index) {
        if (index >= elementCount) {
            throw new ArrayIndexOutOfBoundsException(
		index + " >= " + elementCount);
        }
        elementData[index] = obj;
    }

    public final void quickSwapElementsAt(int element1, int element2) {
        Object obj = null;

        if (element1 >= elementCount) {
            throw new ArrayIndexOutOfBoundsException(
		element1 + " >= " + elementCount);
        }
        if (element2 >= elementCount) {
            throw new ArrayIndexOutOfBoundsException(
		element2 + " >= " + elementCount);
        }
        obj =  elementData[element1];
        elementData[element1] = elementData[element2];
        elementData[element2] = obj;
    }

}
