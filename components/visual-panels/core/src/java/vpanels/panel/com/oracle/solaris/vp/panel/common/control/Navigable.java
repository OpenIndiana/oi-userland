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

package com.oracle.solaris.vp.panel.common.control;

import java.util.*;
import com.oracle.solaris.vp.util.misc.*;

/**
 * The {@code Navigable} class encapsulates the information needed to
 * locate and initialize a {@link Control}.  Namely, its {@link #getId
 * identifier} and optional {@link #getParameters initialization parameters}.
 *
 * @see		Control
 */
public interface Navigable extends HasId, HasName {
    //
    // Inner classes
    //

    class Util {
	public static boolean equals(Navigable a, Navigable b) {
	    if (a == null || b == null) {
		return a == b;
	    }

	    boolean retVal = false;

	    if (ObjectUtil.equals(a.getId(), b.getId())) {
		Map<String, String> aParams = a.getParameters();
		Map<String, String> bParams = b.getParameters();

		int aParamSize = aParams == null ? 0 : aParams.size();
		int bParamSize = bParams == null ? 0 : bParams.size();

		if (aParamSize == bParamSize) {
		    retVal = true;

		    if (aParamSize != 0) {
			for (String name : aParams.keySet()) {
			    if (!ObjectUtil.equals(
				aParams.get(name), bParams.get(name))) {
				retVal = false;
				break;
			    }
			}
		    }
		}
	    }

	    return retVal;
	}
    }

    //
    // Static data
    //

    /**
     * {@code Comparator} used to order a list of {@link Navigable}s by their
     * names.
     */
    static Comparator<Navigable> NAVIGABLE_COMPARATOR =
	new Comparator<Navigable>() {
	    @Override
	    public int compare(Navigable a, Navigable b) {
		return a.getName().compareToIgnoreCase(b.getName());
	    }
	};

    //
    // Navigable methods
    //

    /**
     * Gets the {@link Control} initialization parameters.
     */
    Map<String, String> getParameters();
}
