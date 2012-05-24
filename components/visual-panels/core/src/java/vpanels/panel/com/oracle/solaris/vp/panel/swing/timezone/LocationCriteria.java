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

package com.oracle.solaris.vp.panel.swing.timezone;

import java.util.Comparator;

public abstract class LocationCriteria<T, U> {
    /**
     * Returns a localized description of this set of criteria.
     */
    public abstract String getLabel();

    /**
     * Returns localized unselected-item text.
     */
    public abstract String getUnselectedText();

    /**
     * Returns a {@code Comparator} used to compare two criteria, or
     * {@code null} if the criteria should be lexigraphically sorted
     * using their descriptions.
     */
    public Comparator<? super U> getComparator() {
	return null;
    }

    /**
     * Obtains the criterion that matches the specified object.
     */
    public abstract U toCriterion(T object);

    /**
     * Obtains a localized description of the specified criterion.
     */
    public abstract String toDescription(U criterion);
}
