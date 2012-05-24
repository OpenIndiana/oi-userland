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

import java.util.ArrayList;
import com.oracle.solaris.vp.util.misc.TextUtil;

public abstract class OptionFormatter {
    //
    // Static data
    //

    public static final String OPT_LIST_DELIM = " ";
    public static final String OPT_NAME_DELIM = ",";
    public static final String OPT_CHOICE_DELIM = " | ";
    public static final String OPT_REQUIRED_ENCLOSE_LEFT = "[";
    public static final String OPT_REQUIRED_ENCLOSE_RIGHT = "]";
    public static final String OPT_GROUP_ENCLOSE_LEFT = "(";
    public static final String OPT_GROUP_ENCLOSE_RIGHT = ")";
    public static final String OPT_ARG_ENCLOSE_LEFT = "<";
    public static final String OPT_ARG_ENCLOSE_RIGHT = ">";
    public static final String OPT_REPEAT = "...";

    //
    // OptionFormatter methods
    //

    public String getFormatted(Option opt, boolean allNames) {
	return getFormatted(opt, allNames, false, true);
    }

    public String getFormatted(String opt) {
	return getFormatted(new String[] {opt});
    }

    public String getFormatted(String opt, String optArg) {
	return getFormatted(new String[] {opt}, optArg);
    }

    public abstract String getFormatted(String[] opts);

    public abstract String getFormatted(String[] opts, String optArg);

    //
    // Private methods
    //

    private String getFormatted(Option opt, boolean allNames,
	boolean showGroup, boolean required) {

	StringBuilder buffer = new StringBuilder();

	if (!required) {
	    buffer.append(OPT_REQUIRED_ENCLOSE_LEFT);
	    showGroup = false;
	}

	if (opt instanceof OptionElement) {
	    OptionElement element = (OptionElement)opt;

	    buffer.append(allNames ?
		getFormatted(element.getNames(), element.getArgName()) :
		getFormatted(element.getName(), element.getArgName()));

	    if (element.getUseLimit() < 0) {
		buffer.append(OPT_REPEAT);
	    }
	} else

	if (opt instanceof OptionGroup) {
	    ArrayList<String> list = new ArrayList<String>();
	    String delim = opt instanceof OptionChoiceGroup ?
		OPT_CHOICE_DELIM : OPT_LIST_DELIM;

	    for (Option subOpt : ((OptionGroup)opt).getOptions()) {
		if (subOpt.isDocumented()) {
		    list.add(getFormatted(subOpt, allNames, showGroup,
			opt instanceof OptionChoiceGroup ?
			true : subOpt.isRequired()));
		}
	    }

	    if (showGroup) {
		buffer.append(OPT_GROUP_ENCLOSE_LEFT);
	    }

	    buffer.append(TextUtil.join(delim, list));

	    if (showGroup) {
		buffer.append(OPT_GROUP_ENCLOSE_RIGHT);
	    }
	}

	if (!required) {
	    buffer.append(OPT_REQUIRED_ENCLOSE_RIGHT);
	}

	return buffer.toString();
    }
}
