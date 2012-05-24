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

public class PosixOptionFormatter extends OptionFormatter {
    //
    // Static data
    //

    public static final String PREFIX_SHORT_OPTION = "-";
    public static final String PREFIX_LONG_OPTION = "--";
    public static final String OPT_ARG_LONG_SEPARATOR = "=";
    public static final String OPT_ARG_SHORT_SEPARATOR = " ";

    //
    // OptionFormatter methods
    //

    @Override
    public String getFormatted(String[] opts) {
	return getFormatted(opts, null);
    }

    @Override
    public String getFormatted(String[] opts, String optArg) {
	String separator = "";
	StringBuilder buffer = new StringBuilder();

	for (int i = 0; i < opts.length; i++) {
	    String opt = opts[i];

	    if (i != 0) {
		buffer.append(OPT_NAME_DELIM);
	    }

	    // Is this a non-option opt?
	    if (opt.isEmpty()) {
		separator = "";
	    } else

	    // Is this a short opt?
	    if (opt.length() == 1) {
		separator = OPT_ARG_SHORT_SEPARATOR;
		buffer.append(PREFIX_SHORT_OPTION);
	    } else {

		// This is a long opt
		separator = OPT_ARG_LONG_SEPARATOR;
		buffer.append(PREFIX_LONG_OPTION);
	    }

	    buffer.append(opt);

	    if (optArg != null) {
		buffer.append(separator).append(OPT_ARG_ENCLOSE_LEFT).
		    append(optArg).append(OPT_ARG_ENCLOSE_RIGHT);
	    }
	}

	return buffer.toString();
    }
}
