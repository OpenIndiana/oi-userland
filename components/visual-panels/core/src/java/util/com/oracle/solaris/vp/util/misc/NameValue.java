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

import com.oracle.solaris.vp.util.misc.ObjectUtil;

public class NameValue<V> implements Comparable<NameValue<V>> {
    //
    // Instance data
    //

    private String name;
    private V value;

    //
    // Constructors
    //

    public NameValue(String name, V value) {
	this.name = name;
	this.value = value;
    }

    //
    // Comparable methods
    //

    /**
     * Compares this {@code NameValue} to another based on name.  If equal,
     * attempts to compare based on value.
     */
    @Override
    @SuppressWarnings({"unchecked"})
    public int compareTo(NameValue<V> o) {
	if (o == null) {
	    return 1;
	}

	String n1 = getName();
	String n2 = o.getName();
	int result = ObjectUtil.compare(n1, n2);

	if (result == 0) {
	    V v1 = getValue();
	    V v2 = o.getValue();
	    if (v1 instanceof Comparable && v2 instanceof Comparable) {
		result = ObjectUtil.compare((Comparable)v1, (Comparable)v2);
	    }
	}

	return result;
    }

    //
    // Object methods
    //

    @Override
    public boolean equals(Object o) {
	if (o != null && o instanceof NameValue) {
	    NameValue nv = (NameValue)o;
	    return ObjectUtil.equals(getName(), nv.getName()) &&
		ObjectUtil.equals(getValue(), nv.getValue());
	}

	return false;
    }

    @Override
    public int hashCode() {
	int hash = 7;
	hash = 67 * hash + (name != null ? name.hashCode() : 0);
	hash = 67 * hash + (value != null ? value.hashCode() : 0);
	return hash;
    }


    @Override
    public String toString() {
	return getName();
    }

    //
    // NameValue methods
    //

    public String getName() {
	return name;
    }

    public V getValue() {
	return value;
    }
}
