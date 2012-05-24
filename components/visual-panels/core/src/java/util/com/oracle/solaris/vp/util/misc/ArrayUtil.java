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
 * Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.util.misc;

import java.lang.reflect.Array;
import com.oracle.solaris.vp.util.misc.converter.Converter;

public class ArrayUtil {
    public static <T, F extends T> T[] concat(Class<T> clazz, F[]... arrays) {
	int length = 0;
	for (T[] array : arrays) {
	    length += array.length;
	}

	@SuppressWarnings({"unchecked"})
	T[] dest = (T[])Array.newInstance(clazz, length);

	int offset = 0;
	for (T[] array : arrays) {
	    System.arraycopy(array, 0, dest, offset, array.length);
	    offset += array.length;
	}

	return dest;
    }

    public static <T> boolean contains(T[] array, T element) {
	return indexOf(array, element) != -1;
    }

    public static boolean contains(boolean[] array, boolean element) {
	return indexOf(array, element) != -1;
    }

    public static boolean contains(byte[] array, byte element) {
	return indexOf(array, element) != -1;
    }

    public static boolean contains(char[] array, char element) {
	return indexOf(array, element) != -1;
    }

    public static boolean contains(double[] array, double element) {
	return indexOf(array, element) != -1;
    }

    public static boolean contains(float[] array, float element) {
	return indexOf(array, element) != -1;
    }

    public static boolean contains(int[] array, int element) {
	return indexOf(array, element) != -1;
    }

    public static boolean contains(long[] array, long element) {
	return indexOf(array, element) != -1;
    }

    public static boolean contains(short[] array, short element) {
	return indexOf(array, element) != -1;
    }

    @SuppressWarnings({"unchecked"})
    public static <F, T> T[] convert(F[] from, Class<T> toClass,
	Converter<F, T> converter) {
	T[] to = (T[])Array.newInstance(toClass, from.length);
	for (int i = 0; i < from.length; i++) {
	    to[i] = converter.convert(from[i]);
	}
	return to;
    }

    public static <T> int indexOf(T[] array, T element) {
	for (int i = 0; i < array.length; i++) {
	    if (ObjectUtil.equals(array[i], element)) {
		return i;
	    }
	}
	return -1;
    }

    public static int indexOf(boolean[] array, boolean element) {
	for (int i = 0; i < array.length; i++) {
	    if (array[i] == element) {
		return i;
	    }
	}
	return -1;
    }

    public static int indexOf(byte[] array, byte element) {
	for (int i = 0; i < array.length; i++) {
	    if (array[i] == element) {
		return i;
	    }
	}
	return -1;
    }

    public static int indexOf(char[] array, char element) {
	for (int i = 0; i < array.length; i++) {
	    if (array[i] == element) {
		return i;
	    }
	}
	return -1;
    }

    public static int indexOf(double[] array, double element) {
	for (int i = 0; i < array.length; i++) {
	    if (array[i] == element) {
		return i;
	    }
	}
	return -1;
    }

    public static int indexOf(float[] array, float element) {
	for (int i = 0; i < array.length; i++) {
	    if (array[i] == element) {
		return i;
	    }
	}
	return -1;
    }

    public static int indexOf(int[] array, int element) {
	for (int i = 0; i < array.length; i++) {
	    if (array[i] == element) {
		return i;
	    }
	}
	return -1;
    }

    public static int indexOf(long[] array, long element) {
	for (int i = 0; i < array.length; i++) {
	    if (array[i] == element) {
		return i;
	    }
	}
	return -1;
    }

    public static int indexOf(short[] array, short element) {
	for (int i = 0; i < array.length; i++) {
	    if (array[i] == element) {
		return i;
	    }
	}
	return -1;
    }
}
