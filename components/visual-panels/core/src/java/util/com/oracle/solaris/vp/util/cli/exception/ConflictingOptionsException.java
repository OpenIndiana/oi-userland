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

package com.oracle.solaris.vp.util.cli.exception;

import com.oracle.solaris.vp.util.cli.OptionMap;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class ConflictingOptionsException extends OptionException {
    //
    // Instance data
    //

    private String opt;
    private String optInUse;

    //
    // Constructors
    //

    public ConflictingOptionsException(String optInUse, String opt,
	OptionMap[] processed) {

	super(Finder.getString("command.error.option.conflict", opt, optInUse),
	    processed);

	this.opt = opt;
	this.optInUse = optInUse;
    }

    //
    // ConflictingOptionsException methods
    //

    public String getOpt() {
	return opt;
    }

    public String getOptInUse() {
	return optInUse;
    }
}
