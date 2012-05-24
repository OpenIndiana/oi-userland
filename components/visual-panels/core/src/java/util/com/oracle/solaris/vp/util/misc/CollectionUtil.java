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
import com.oracle.solaris.vp.util.misc.converter.Converter;
import com.oracle.solaris.vp.util.misc.predicate.Predicate;

public class CollectionUtil {
    public static <T> void addAll(Collection<T> collection, T... array) {
	for (T t : array) {
	    collection.add(t);
	}
    }

    public static <T> Set<T> clone(Set<T> set) {
	Set<T> clone = new HashSet<T>();
	clone.addAll(set);
	return clone;
    }

    public static <T> List<T> clone(List<T> list) {
	List<T> clone = new ArrayList<T>(list.size());
	clone.addAll(list);
	return clone;
    }

    public static <F, T> List<T> convert(
	Collection<? extends F> from, Converter<F, T> converter) {

	if (from == null) {
	    return null;
	}

	List<T> to = new ArrayList<T>(from.size());
	for (F f : from) {
	    to.add(converter.convert(f));
	}

	return to;
    }

    /**
     * Returns a three-element array of mutable {@code List}s:
     * <ol>
     *	 </li>
     *	   the intersection of {@code a} and {@code b}
     *	 <li>
     *	 </li>
     *	   the {@code a} - {@code b} difference
     *	 <li>
     *	 </li>
     *	   the {@code b} - {@code a} difference
     *	 <li>
     * </ol>
     *
     * @param	    comparator
     *		    a comparator to sort results, or {@code null} to remain
     *		    unsorted
     */
    public static <T> List<T>[] getIntersectAndDiffs(
	Collection<? extends T> a, Collection<? extends T> b,
	Comparator<T> comparator) {

	int aSize = a.size();
	List<T> aDiff = new ArrayList<T>(aSize);
	aDiff.addAll(a);

	int bSize = b.size();
	List<T> bDiff = new ArrayList<T>(bSize);
	bDiff.addAll(b);

	if (comparator != null) {
	    Collections.sort(aDiff, comparator);
	    Collections.sort(bDiff, comparator);
	}

	List<T> abInter = new ArrayList<T>(Math.min(aSize, bSize));

	for (int i = aDiff.size() - 1; i >= 0; i--) {
	    T element = aDiff.get(i);

	    int index = comparator == null ? bDiff.indexOf(element) :
		Collections.binarySearch(bDiff, element, comparator);

	    if (index != -1) {
		bDiff.remove(index);
		aDiff.remove(i);
		abInter.add(element);
	    }
	}

	@SuppressWarnings({"unchecked"})
	List<T>[] array = (List<T>[])new List[] {
	    abInter, aDiff, bDiff
	};

	return array;
    }

    /**
     * Returns a modifiable {@code List} of matching elements.
     */
    public static <T> List<T> filter(
	Collection<? extends T> collection, Predicate<T> matcher) {

	List<T> subset = new ArrayList<T>(collection.size());
	for (T element : collection) {
	    if (matcher.test(element)) {
		subset.add(element);
	    }
	}

	return subset;
    }

    public static <T> void removeAll(Collection<T> collection, T... array) {
	for (T t : array) {
	    collection.remove(t);
	}
    }
}
