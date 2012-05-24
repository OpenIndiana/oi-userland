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
import com.oracle.solaris.vp.util.cli.exception.*;

public class OptionElement extends Option {
    //
    // Instance data
    //

    private boolean required;
    private boolean documented;
    private List<String> names;
    private String argName;
    private boolean argOptional;
    private String description;
    private int useLimit;

    //
    // Constructors
    //

    public OptionElement(String[] names, boolean required,
	String argName, boolean argOptional, String description, int useLimit) {
	setNames(names);
	setRequired(required);
	setArgName(argName);
	setArgOptional(argOptional);
	setDescription(description);
	setUseLimit(useLimit);
	setDocumented(true);
    }

    public OptionElement(String name, boolean required, String argName,
	String description) {
	this(new String[] {name}, required, argName, false, description, 1);
    }

    public OptionElement(String name, boolean required, String description) {
	this(name, required, null, description);
    }

    public OptionElement(String name1, String name2, boolean required,
	String argName, String description) {
	this(new String[] {name1, name2},
	    required, argName, false, description, 1);
    }

    public OptionElement(String name1, String name2, boolean required,
	String description) {
	this(name1, name2, required, null, description);
    }

    //
    // Option methods
    //

    @Override
    public boolean isDocumented() {
	return documented;
    }

    @Override
    public boolean isRequired() {
	return required;
    }

    //
    // OptionElement methods
    //

    public void setDocumented(boolean documented) {
	this.documented = documented;
    }

    public void setRequired(boolean required) {
	this.required = required;
    }

    public void setNames(String[] names) {
	this.names = Arrays.asList(names);
    }

    public String[] getNames() {
	return names.toArray(new String[names.size()]);
    }

    public String getName() {
	try {
	    return names.get(0);
	}
	catch (IndexOutOfBoundsException e) {
	    return null;
	}
    }

    public void setArgName(String argName) {
	this.argName = argName;
    }

    public String getArgName() {
	return argName;
    }

    public boolean getTakesArgument() {
	return argName != null;
    }

    public void setArgOptional(boolean argOptional) {
	this.argOptional = argOptional;
    }

    public boolean getArgOptional() {
	return argOptional;
    }

    public void setDescription(String description) {
	this.description = description;
    }

    public String getDescription() {
	return description;
    }

    public void setUseLimit(int useLimit) {
	this.useLimit = useLimit;
    }

    public int getUseLimit() {
	return useLimit;
    }

    /**
     * Returns a boolean indicating whether the given
     * <code>ParsedOption</code> matches this
     * <code>OptionElement</code>.
     */
    protected boolean matches(ParsedOption processed) {
	String opt = processed.getOpt();
	if (opt != null) {
	    for (String name : getNames()) {
//		System.out.printf("Testing opt=%s optArg=%s against %s\n",
//		    opt, processed.getOptArg(), name);

		if (opt.equals(name)) {
		    return true;
		}
	    }
	}
	return false;
    }

    /**
     * Validates the given option and optional argument against the
     * option/optArg that this OptionElement expects.  If the option is valid,
     * does nothing.	Otherwise, an exception is thrown.
     *
     * @param	    parsed
     *		    the option parsed from the command line
     *
     * @param	    useCount
     *		    the number of times this option has been used
     *
     * @param	    formatter
     *		    used to format the option string in exception
     *		    messages
     *
     * @param	    processed
     *		    the options processed so far, for use in exceptions
     *
     * @exception   InvalidOptionException
     *		    if the given option doesn't match the name of this
     *		    OptionElement
     *
     * @exception   OptionUseExceededException
     *		    if this OptionElement has been used more times
     *		    than it is allowed
     *
     * @exception   MissingOptArgException
     *		    if this OptionElement requires an argument but
     *		    none was specified
     *
     * @exception   UnexpectedOptArgException
     *		    if this OptionElement takes no argument but
     *		    one was specified
     *
     * @exception   InvalidOptArgException
     *		    if this OptionElement's argument is invalid --
     *		    not thrown in this default implementation
     */
    protected void validate(ParsedOption parsed, int useCount,
	OptionFormatter formatter, OptionMap[] processed) throws
	InvalidOptionException, OptionUseExceededException,
	MissingOptArgException, UnexpectedOptArgException,
	InvalidOptArgException {

	String opt = parsed.getOpt();
	String optArg = parsed.getOptArg();
	String formatted = OptionMap.getFormatted(parsed, this, formatter);

//	System.out.printf("Validating: opt=%s optArg=%s\n", opt, optArg);

	// Verify given option identifies this OptionElement
	if (!matches(parsed)) {
	    throw new InvalidOptionException(formatted, processed);
	}

	// Change message to reflect the option syntax, not the passed-in opt
	formatted = formatter.getFormatted(this, false);

	// Verify this option hasn't been specified too many times
	int useLimit = getUseLimit();
	if (useLimit >= 0 && useCount > useLimit) {
	    throw new OptionUseExceededException(
		formatted, useLimit, processed);
	}

	// Verify optArg if required
	if (getTakesArgument() && !getArgOptional() && optArg == null) {
	    throw new MissingOptArgException(formatted, processed);
	}

	// Verify no optArg if not expected
	if (!getTakesArgument() && optArg != null) {
	    throw new UnexpectedOptArgException(
		formatted, optArg, processed);
	}
    }
}
