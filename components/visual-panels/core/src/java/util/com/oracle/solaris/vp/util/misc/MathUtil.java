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

public class MathUtil {
    //
    // Static methods
    //

    public static int min(int... array) {
	int min = array[0];
	for (int i = 1; i < array.length; i++) {
	    if (array[i] < min) {
		min = array[i];
	    }
	}
	return min;
    }

    public static int max(int... array) {
	int max = array[0];
	for (int i = 1; i < array.length; i++) {
	    if (array[i] > max) {
		max = array[i];
	    }
	}
	return max;
    }

    public static String toBinary(long l, int bits) {
	StringBuilder buffer = new StringBuilder(bits);

	for (int i = 0; i < bits; i++) {
	    buffer.insert(0, l & 1);
	    l >>>= 1;
	}

	return buffer.toString();
    }

    public static String toBinary(long l) {
	return toBinary(l, 64);
    }

    public static String toBinary(int l) {
	return toBinary(l, 32);
    }

    public static String toBinary(short l) {
	return toBinary(l, 16);
    }

    public static String toBinary(char l) {
	return toBinary(l, 16);
    }

    public static String toBinary(byte l) {
	return toBinary(l, 8);
    }
}
