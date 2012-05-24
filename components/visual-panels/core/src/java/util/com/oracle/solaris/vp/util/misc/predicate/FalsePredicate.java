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

package com.oracle.solaris.vp.util.misc.predicate;

/**
 * The {@code FalsePredicate<T>} class is a {@code Predicate} that always
 * returns {@code false}.  The {@link #getInstance} method is the preferred way
 * to get an instance of this class.
 */
public class FalsePredicate<T> implements Predicate<T> {
    //
    // Static data
    //

    private static final FalsePredicate<Object> instance =
	new FalsePredicate<Object>();

    //
    // Predicate methods
    //

    /**
     * Returns false.
     *
     * @param	    o
     *		    the object to ignore
     *
     * @return	    {@code false}
     */
    @Override
    public boolean test(T o) {
	return (false);
    }

    //
    // Static methods
    //

    /**
     * Gets a type-safe, immutable, singleton instance of this class.
     */
    @SuppressWarnings({"unchecked"})
    public static <T> FalsePredicate<T> getInstance() {
	return (FalsePredicate<T>)instance;
    }
}
