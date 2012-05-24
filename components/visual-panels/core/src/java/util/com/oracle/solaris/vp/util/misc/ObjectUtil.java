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

import java.util.Arrays;

public class ObjectUtil {
    public static <T> int compare(Comparable<T> o1, T o2) {
	if (o1 == null) {
	    return o2 == null ? 0 : -1;
	}

	if (o2 == null) {
	    return 1;
	}

	return o1.compareTo(o2);
    }

    public static boolean equals(Object o1, Object o2) {
	if (o1 == null) {
	    return o2 == null;
	}

	if (o2 != null && o1.getClass().isArray() && o2.getClass().isArray()) {
	    try {
		return Arrays.deepEquals((Object[])o1, (Object[])o2);
	    } catch (ClassCastException ignore) {
	    }

	    try {
		return Arrays.equals((boolean[])o1, (boolean[])o2);
	    } catch (ClassCastException ignore) {
	    }

	    try {
		return Arrays.equals((byte[])o1, (byte[])o2);
	    } catch (ClassCastException ignore) {
	    }

	    try {
		return Arrays.equals((char[])o1, (char[])o2);
	    } catch (ClassCastException ignore) {
	    }

	    try {
		return Arrays.equals((double[])o1, (double[])o2);
	    } catch (ClassCastException ignore) {
	    }

	    try {
		return Arrays.equals((float[])o1, (float[])o2);
	    } catch (ClassCastException ignore) {
	    }

	    try {
		return Arrays.equals((int[])o1, (int[])o2);
	    } catch (ClassCastException ignore) {
	    }

	    try {
		return Arrays.equals((long[])o1, (long[])o2);
	    } catch (ClassCastException ignore) {
	    }

	    try {
		return Arrays.equals((short[])o1, (short[])o2);
	    } catch (ClassCastException ignore) {
	    }
	}

	return o1.equals(o2);
    }
}
