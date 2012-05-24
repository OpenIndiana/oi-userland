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

import java.util.Comparator;

public class SimpleHasId implements HasId {
    //
    // Static data
    //

    public static final Comparator<HasId> COMPARATOR =
	new Comparator<HasId>() {
	    @Override
	    public int compare(HasId o1, HasId o2) {
		return ObjectUtil.compare(o1.getId(), o2.getId());
	    }
	};

    //
    // Instance data
    //

    private String id;

    //
    // Constructors
    //

    public SimpleHasId(String id) {
	setId(id);
    }

    public SimpleHasId() {
    }

    //
    // HasId methods
    //

    @Override
    public String getId() {
	return id;
    }

    //
    // SimpleHasId methods
    //

    public void setId(String id) {
	this.id = id;
    }
}
