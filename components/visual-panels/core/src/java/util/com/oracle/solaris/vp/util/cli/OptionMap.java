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

/**
 * The <code>OptionMap</code> class provides a 1x1 mapping between a
 * <code>ParsedOption</code> and an <code>OptionElement</code>.
 */
public class OptionMap {
    //
    // Instance data
    //

    private ParsedOption parsed;
    private OptionElement option;

    //
    // Constructors
    //

    public OptionMap(ParsedOption parsed, OptionElement option) {
	setParsed(parsed);
	setOption(option);
    }

    //
    // OptionMap methods
    //

    public void setParsed(ParsedOption parsed) {
	this.parsed = parsed;
    }

    /**
     * Gets the <code>ParsedOption</code> that was parsed from
     * the command line.
     */
    public ParsedOption getParsed() {
	return parsed;
    }

    public void setOption(OptionElement option) {
	this.option = option;
    }

    /**
     * Gets the <code>OptionElement</code> that matches the parsed
     * option.
     */
    public OptionElement getOption() {
	return option;
    }

    /**
     * Gets a formatted representation of this option.
     */
    public String getFormatted(OptionFormatter formatter) {
	return getFormatted(parsed, option, formatter);
    }

    //
    // Static methods
    //

    /**
     * Gets a formatted representation of this option.
     */
    public static String getFormatted(ParsedOption parsed, OptionElement option,
	OptionFormatter formatter) {

	// Return the formatted option if one was specified
	String opt = parsed.getOpt();
	if (opt != null && !opt.isEmpty()) {
	    return formatter.getFormatted(opt);
	}

	// Return the option argument if one was specified
	String optArg = parsed.getOptArg();
	if (optArg != null && !optArg.isEmpty()) {
	    return "\"" + optArg + "\"";
	}

	// Return the formatted option from the option definition
	return formatter.getFormatted(option, false);
    }
}
