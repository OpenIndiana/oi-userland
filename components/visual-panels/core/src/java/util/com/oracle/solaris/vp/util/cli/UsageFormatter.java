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

import java.util.*;
import com.oracle.solaris.vp.util.misc.TextUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class UsageFormatter {
    //
    // Static data
    //

    public static final int _WIDTH = 65;
    public static final int _INDENT = 4;

    //
    // Instance data
    //

    private String command;
    private Option option;
    private OptionFormatter formatter;
    private String usageLabel = Finder.getString("command.usage.header");
    private int width = _WIDTH;
    private int indent = _INDENT;

    //
    // Constructors
    //

    public UsageFormatter(String command, Option option,
	OptionFormatter formatter) {

	this.command = command;
	this.option = option;
	this.formatter = formatter;
    }

    //
    // UsageFormatter methods
    //

    public String getCommand() {
	return command;
    }

    public Option getOption() {
	return option;
    }

    public OptionFormatter getOptionFormatter() {
	return formatter;
    }

    public void setUsageLabel(String usageLabel) {
	this.usageLabel = usageLabel;
    }

    public String getUsageLabel() {
	return usageLabel;
    }

    public void setWidth(int width) {
	this.width = width;
    }

    public int getWidth() {
	return width;
    }

    public void setIndent(int indent) {
	this.indent = indent;
    }

    public int getIndent() {
	return indent;
    }

    public String getUsage() {
	Option option = getOption();
	List<Option> options;
	if (option instanceof OptionGroup) {
	    options = ((OptionGroup)option).getOptions();
	} else {
	    options = new ArrayList<Option>();
	    options.add(option);
	}

	String usageLabel = getUsageLabel();
	String whitespace = usageLabel.replaceAll("\\S", " ");
	String indent1 = usageLabel;
	String indent2 = whitespace +
	    String.format("%" + getIndent() + "s", "");
	int width = getWidth();

	StringBuilder buffer = new StringBuilder();
	for (int i = 0, n = options.size(); i < n; i++) {
	    Option o = options.get(i);
	    if (o.isDocumented()) {
		String synopsis = command + " " +
		    formatter.getFormatted(o, false);

		buffer.append(TextUtil.format(
		    synopsis, width, indent1, indent2, false));

		if (indent1 == usageLabel) {
		    indent1 = "\n" + whitespace;
		}
	    }
	}

	return buffer.toString();
    }
}
