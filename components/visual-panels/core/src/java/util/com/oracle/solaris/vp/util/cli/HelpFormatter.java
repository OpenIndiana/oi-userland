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

public class HelpFormatter {
    //
    // Instance data
    //

    private String description;
    private UsageFormatter formatter;
    private String optionsLabel = Finder.getString("command.help.options");

    //
    // Constructors
    //

    public HelpFormatter(String description, UsageFormatter formatter) {
	this.description = description;
	this.formatter = formatter;
    }

    //
    // HelpFormatter methods
    //

    public String getDescription() {
	return description;
    }

    public UsageFormatter getUsageFormatter() {
	return formatter;
    }

    public void setOptionsLabel(String optionsLabel) {
	this.optionsLabel = optionsLabel;
    }

    public String getOptionsLabel() {
	return optionsLabel;
    }

    public String getHelp() {
	UsageFormatter usage = getUsageFormatter();
	OptionElement[] options = getOptionElements();
	OptionFormatter formatter = usage.getOptionFormatter();

	StringBuilder buffer = new StringBuilder();
	int width = usage.getWidth();

	buffer.append(usage.getUsage()).
	    append("\n\n").
	    append(TextUtil.format(getDescription(), width, "", "", false));

	if (options.length > 0) {
	    int indentlen = usage.getIndent();
	    String indent2 = String.format("%" + indentlen + "s", "");

	    String optionsLabel = getOptionsLabel();
	    if (optionsLabel != null) {
		buffer.append("\n\n").append(getOptionsLabel());
	    }

	    for (OptionElement option : options) {
		String synopsis = formatter.getFormatted(option, true);
		buffer.append("\n\n");

		String indent1;
		String description = option.getDescription();

		// Can synopsis and description be on the same line?
		if (synopsis.length() + 1 <= indentlen) {
		    description = String.format("%-" + indentlen + "s%s",
			synopsis, description);
		    indent1 = "";
		} else {
		    buffer.append(synopsis);
		    if (!description.isEmpty()) {
			buffer.append("\n");
		    }
		    indent1 = indent2;
		}

		buffer.append(TextUtil.format(description, width, indent1,
		    indent2, false));
	    }
	}

	return buffer.toString();
    }

    //
    // Private methods
    //

    private OptionElement[] getOptionElements() {
	// Recursively retrieve all OptionElements
	HashMap<String, OptionElement> map =
	    new HashMap<String, OptionElement>();
	getOptionElements(getUsageFormatter().getOption(), map);

	ArrayList<OptionElement> elements = new ArrayList<OptionElement>();
	elements.addAll(map.values());

	Collections.sort(elements,
	    new Comparator<OptionElement>() {
		public int compare(OptionElement a, OptionElement b) {
		    String aName = a.getName();
		    String bName = b.getName();

		    int result = aName.toLowerCase().compareTo(
			bName.toLowerCase());

		    if (result == 0) {
			// Lowercase before uppercase
			result = bName.compareTo(aName);
		    }

		    return result;
		}
	    });

	return elements.toArray(new OptionElement[elements.size()]);
    }

    private void getOptionElements(
	Option option, HashMap<String, OptionElement> map) {

	if (option.isDocumented()) {
	    if (option instanceof OptionElement) {
		OptionElement element = (OptionElement)option;
		String key = element.getName() + element.getArgName();
		map.put(key, element);
	    } else

	    if (option instanceof OptionGroup) {
		for (Option o : ((OptionGroup)option).getOptions()) {
		    getOptionElements(o, map);
		}
	    }
	}
    }
}
