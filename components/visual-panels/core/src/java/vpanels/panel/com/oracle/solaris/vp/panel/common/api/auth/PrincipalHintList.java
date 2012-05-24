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

package com.oracle.solaris.vp.panel.common.api.auth;

import java.io.Serializable;
import java.util.Arrays;

public class PrincipalHintList implements Serializable {
    //
    // Instance data
    //

    protected PrincipalHint[] hints;

    //
    // Constructors
    //

    public PrincipalHintList(PrincipalHint... hints) {
	this.hints = Arrays.copyOf(hints, hints.length);
    }

    //
    // PrincipalHintList methods
    //

    public PrincipalHint[] getHints() {
	return Arrays.copyOf(hints, hints.length);
    }

    public PrincipalHint getFirstHint(PrincipalHint.PrincipalType type) {
	for (PrincipalHint hint : hints) {
	    if (hint.getType() == type) {
		return hint;
	    }
	}
	return null;
    }

    @SuppressWarnings({"unchecked"})
    public <C extends PrincipalHint> C getFirstHint(Class<C> clazz) {
	for (PrincipalHint hint : hints) {
	    if (clazz.isInstance(hint)) {
		return (C)hint;
	    }
	}
	return null;
    }
}
