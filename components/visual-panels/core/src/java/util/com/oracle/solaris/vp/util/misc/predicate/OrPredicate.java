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

import java.util.*;

/**
 * A predicate that ORs a number of wrapped of predicates.
 */
public class OrPredicate<T> implements Predicate<T> {
    //
    // Instance data
    //

    private Predicate<T>[] predicates;

    //
    // Constructors
    //

    /**
     * Constructs a OrPredicate.
     *
     * @param	    predicates
     *		    the predicates to OR together
     */
    public OrPredicate(Predicate<T>... predicates) {
	this.predicates = predicates;
    }

    //
    // Predicate methods
    //

    /**
     * Returns {@code true} if any of the wrapped predicates returns {@code
     * true}, {@code false} otherwise.
     */
    @Override
    public boolean test(T o) {
	for (Predicate<T> predicate : predicates) {
	    if (predicate.test(o)) {
		return true;
	    }
	}
	return false;
    }
}
