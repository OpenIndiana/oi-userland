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

/**
 * A checked exception type for permissions errors that permits the
 * thrower to provide a list of possible valid {@code Principal}s.
 */
public class UnauthorizedException extends Exception {
    //
    // Instance data
    //

    private PrincipalHintList hints;

    //
    // Constructors
    //

    public UnauthorizedException(PrincipalHint... hints) {
	this(null, null, hints);
    }

    public UnauthorizedException(String message, PrincipalHint... hints) {
	this(message, null, hints);
    }

    public UnauthorizedException(Throwable cause, PrincipalHint... hints)
    {
	this(null, cause, hints);
    }

    public UnauthorizedException(String message, Throwable cause,
	PrincipalHint... hints) {

	super(message, cause);
	this.hints = new PrincipalHintList(hints);
    }

    //
    // UnauthorizedException methods
    //

    public PrincipalHintList getHints() {
	return hints;
    }
}
