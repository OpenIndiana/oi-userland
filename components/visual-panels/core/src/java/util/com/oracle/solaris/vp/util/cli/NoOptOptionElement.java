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

package com.oracle.solaris.vp.util.cli;

public class NoOptOptionElement extends OptionElement {
    //
    // Constructors
    //

    public NoOptOptionElement(boolean required,
	String argName, String description, int useLimit) {

	super(new String[] {""}, required, argName, false, description,
	    useLimit);
    }

    public NoOptOptionElement(boolean required, String argName,
	String description) {

	this(required, argName, description, 1);
    }

    //
    // OptionElement methods
    //

    /**
     * Returns a boolean indicating whether the given ParsedOption
     * matches this NoOptOptionElement.
     *
     * @param	    option
     *		    a ParsedOption
     *
     * @return	    <code>true</code> if the option flag is
     *		    <code>null</code> or an empty string,
     *		    <code>false</code> otherwise
     */
    @Override
    protected boolean matches(ParsedOption option) {
	String opt = option.getOpt();
	return opt == null || opt.isEmpty();
    }
}
