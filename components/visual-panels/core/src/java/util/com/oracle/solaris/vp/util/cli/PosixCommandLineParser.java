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

public class PosixCommandLineParser extends CommandLineParser {
    //
    // Inner classes
    //

    protected static class Pointer {
	public int argPointer;
	public int charIndex;
	public Pointer(int argPointer, int charIndex) {
	    this.argPointer = argPointer;
	    this.charIndex = charIndex;
	}
    }

    //
    // Static data
    //

    // Options consist of any character except whitespace and '='
    private static final String ALLOWED_OPTION_CHARS = "[\\S&&[^=]]";

    // Group 1 is the short option list
    private static final String REGEX_SHORT_OPTION =
	"^" + PosixOptionFormatter.PREFIX_SHORT_OPTION +
	"(" + ALLOWED_OPTION_CHARS + ".*)";

    // Group 1 is the long option, group 3 is the (optional) value
    private static final String REGEX_LONG_OPTION =
	"^" + PosixOptionFormatter.PREFIX_LONG_OPTION +
	"(" + ALLOWED_OPTION_CHARS + "*)(=(.*))?";

    //
    // Instance data
    //

    private int argPointer;
    private int charIndex;
    private Stack<Pointer> pointerStack = new Stack<Pointer>();
    private OptionFormatter formatter = new PosixOptionFormatter();

    //
    // Constructors
    //

    public PosixCommandLineParser() {
	reset();
    }

    //
    // PosixCommandLineParser methods
    //

    public ParsedOption getNextOption() {
	// Are we at the end of the raw argument list?
	if (isDoneParsing()) {
	    return null;
	}

	// Save position of this option
	pointerStack.push(new Pointer(argPointer, charIndex));

	String arg = getArgs()[argPointer];
	String opt = null;
	String optArg = null;
	String[] groups;

	// Is the current raw argument a long option?
	if ((groups = TextUtil.match(arg, REGEX_LONG_OPTION)) != null) {
	    // Group 1 is the long option, group 3 is the (optional) value
	    opt = groups[1];
	    optArg = groups[3];

	    // Go to next raw argument
	    argPointer++;

	// Is the current raw argument a short option?
	} else if ((groups = TextUtil.match(arg, REGEX_SHORT_OPTION)) != null) {
	    // Group 1 is the short option list
	    opt = groups[1].substring(charIndex, charIndex + 1);

	    // Have we reached the end of this raw argument?
	    if (++charIndex == groups[1].length()) {
		// Go to next raw argument
		argPointer++;
		charIndex = 0;
	    }
	} else {
	    // The current raw argument is not an option -- return an
	    // empty short option
	    opt = "";
	    optArg = arg;

	    // Go to next raw argument
	    argPointer++;
	}

//	System.out.println("Found option: " + opt + "=" + optArg);

	ParsedOption option = new ParsedOption(opt, optArg);

	return option;
    }

    public void getNextOptArg(ParsedOption option) {
	// An opt arg must not aleady have been found
	if (option.getOptArg() != null ||

	    // Are we at the end of the raw argument list?
	    isDoneParsing()) {
	    return;
	}

	String arg = getArgs()[argPointer];
	String[] groups;

	// Is the current raw argument a short option?
	if ((groups = TextUtil.match(arg, REGEX_SHORT_OPTION)) != null &&
	    charIndex != 0) {

	    // The remainder of the short option list (group 1) is
	    // the optArg
	    option.setOptArg(groups[1].substring(charIndex));

	    charIndex = 0;
	} else {

	    // The whole option is the optArg
	    option.setOptArg(arg);
	}
	argPointer++;

//	System.out.println("Found optArg: " + option.getOpt() + "=" +
//	    option.getOptArg());
    }

    public void reset() {
	argPointer = 0;
	charIndex = 0;
	pointerStack.clear();
    }

    public void resetToPreviousOption() {
	try {
	    Pointer pointer = pointerStack.pop();
	    argPointer = pointer.argPointer;
	    charIndex = pointer.charIndex;
	}
	catch (EmptyStackException ignore) {}
    }

    public boolean isDoneParsing() {
	return argPointer == getArgs().length;
    }

    public OptionFormatter getOptionFormatter() {
	return formatter;
    }
}
