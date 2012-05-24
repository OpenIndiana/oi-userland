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

import java.beans.IntrospectionException;
import java.lang.reflect.InvocationTargetException;
import java.util.*;
import com.oracle.solaris.vp.util.cli.exception.*;
import com.oracle.solaris.vp.util.misc.*;

public class CommandLineProcessor {
    //
    // Instance data
    //

    private OptionGroup group;
    private CommandLineParser parser;
    private Stack<OptionMap> processed;
    private Map<Option, Integer> used;

    //
    // Constructors
    //

    private CommandLineProcessor(OptionGroup group, CommandLineParser parser) {
	this.group = group;
	this.parser = parser;
	this.processed = new Stack<OptionMap>();
	used = new HashMap<Option, Integer>();
    }

    //
    // Private methods
    //

    private int getUseCount(Option option) {
	try {
	    return used.get(option);
	}
	catch (NullPointerException e) {
	    return 0;
	}
    }

    private int incUseCount(Option option) {
	int count = getUseCount(option) + 1;
	used.put(option, count);
	return count;
    }

    private int decUseCount(Option option) {
	int count = getUseCount(option) - 1;
	used.put(option, count);
	return count;
    }

    private boolean isUsed(Option option) {
	return getUseCount(option) > 0;
    }

    private OptionMap[] getProcessed() {
	return processed.toArray(new OptionMap[processed.size()]);
    }

    private void process(Option curOpt, OptionMap conflict, String indent)
	throws OptionException {

	OptionFormatter formatter = parser.getOptionFormatter();

//	System.out.println(indent + "Current option: " +
//	    TextUtil.getClassBaseName(curOpt) + ": " +
//	    formatter.getFormatted(curOpt, false));

	if (parser.isDoneParsing()) {
	    // Last check
	    verifyRequiredOptions(group);
	    return;
	}

	OptionException exception = null;

	if (curOpt instanceof OptionElement) {
	    OptionElement element = (OptionElement)curOpt;

	    ParsedOption parsed = parser.getNextOption();
//	    System.out.println(indent + "Next option: " +
//		formatter.getFormatted(parsed.getOpt()));

	    // Does this OptionElement expect an opt arg?
	    if (element.getTakesArgument()) {
		// Parse opt arg
		parser.getNextOptArg(parsed);
	    }

	    // Create mapping between parsed option and option definition
	    OptionMap map = new OptionMap(parsed, (OptionElement)curOpt);

//	    System.out.println(indent + "Used options:");
//	    for (int i = 0, n = processed.size(); i < n; i++) {
//		System.out.println(indent + "  " + i + ": " +
//		    processed.get(i).getFormatted(formatter));
//	    }

	    // Add the mapping to list of saved options
	    processed.push(map);

	    int useCount = incUseCount(element);

	    try {
		// Validate syntax (throws OptionException)
		element.validate(parsed, useCount, formatter, getProcessed());

//		System.out.println(indent + "Validated option: " +
//		    map.getFormatted(formatter));

		// The option is lexically and syntactically valid --
		// check for conflict with previously-specified option
		if (conflict != null) {
		    throw new ConflictingOptionsException(
			conflict.getFormatted(formatter),
			map.getFormatted(formatter), getProcessed());
		}

		exception = null;

		// Recurse... (throws OptionException)
		process(group, conflict, indent + "  ");

		// Success!  All args have been parsed.
		return;
	    }

	    catch (OptionException e) {

//		System.out.println(indent + "Should I save 1:");
//		System.out.println(indent + "  " +
//		    (exception == null ? "null" : exception.getMessage()));
//		System.out.println(indent + "  " +
//		    (e == null ? "null" : e.getMessage()));

		// Save only the most significant exception to throw later
		exception = getMostSignificantException(exception, e);

//		System.out.println(indent + "saved: " +
//		    (exception == null ? "null" : exception.getMessage()));

		decUseCount(element);

		// Remove the ParsedOption from saved options
		processed.pop();

		// Un-parse previously-parsed option
		parser.resetToPreviousOption();
	    }
	} else

	if (curOpt instanceof OptionGroup) {

	    OptionMap newConflict = conflict;

	    // If this option is represents a list of options from which only
	    // one can be chosen...
	    if (curOpt instanceof OptionChoiceGroup &&

		// ...and no conflict option has thus far been specified...
		newConflict == null) {

		// Get the first option in this group, if any, which has already
		// been specified and validated.  Later, if another otherwise
		// valid option is found, it will conflict with this option and
		// a ConflictingOptionsException will be thrown.
		newConflict = getFirstUsedOpt((OptionGroup)curOpt, processed);

//		System.out.println(indent + "Assigning conflict opt: " +
//		    (newConflict == null ? "null" :
//		    newConflict.getFormatted(formatter)));
	    }

	    for (Option subOpt : ((OptionGroup)curOpt).getOptions()) {
		try {
		    incUseCount(curOpt);

		    // Recurse... (throws OptionException)
		    process(subOpt, isUsed(subOpt) ?
			conflict : newConflict, indent + "  ");

		    // Success!  All args have been parsed.
		    return;
		}

		catch (OptionException e) {
//		    System.out.println(indent + "Should I save 2:");
//		    System.out.println(indent + "  " +
//			(exception == null ? "null" : exception.getMessage()));
//		    System.out.println(indent + "  " +
//			(e == null ? "null" : e.getMessage()));

		    // Save only the most significant exception to throw later
		    exception = getMostSignificantException(exception, e);

//		    System.out.println(indent + "saved: " +
//			(exception == null ? "null" : exception.getMessage()));

		    decUseCount(curOpt);
		}
	    }
	}

	if (exception == null) {
	    ParsedOption parsed = parser.getNextOption();
	    exception = new InvalidOptionException(
		formatter.getFormatted(parsed.getOpt()), getProcessed());
	    parser.resetToPreviousOption();
	}

	throw exception;
    }

    /**
     * Retrieves the first ParsedOption from this option group.
     */
    private OptionMap getFirstUsedOpt(OptionGroup parent,
	List<OptionMap> maps) {

	for (Option subOpt : parent.getOptions()) {

	    if (isUsed(subOpt)) {
		if (subOpt instanceof OptionElement) {
		    // Search for matching ParsedOption
		    for (OptionMap map : maps) {
			if (((OptionElement)subOpt).matches(
			    map.getParsed())) {
			    return map;
			}
		    }
		    // Shouldn't be here
		} else

		if (subOpt instanceof OptionGroup) {
		    OptionMap map = getFirstUsedOpt((OptionGroup)subOpt, maps);

		    if (map != null) {
			return map;
		    }
		}
	    }
	}

	return null;
    }

    private void verifyRequiredOptions(Option option)
	throws MissingOptionException {

	OptionFormatter formatter = parser.getOptionFormatter();

	if (!isUsed(option)) {
	    if (option.isRequired()) {
		throw new MissingOptionException(
		    formatter.getFormatted(option, false),
		    getProcessed());
	    }
	} else {
	    if (option instanceof OptionGroup) {
		for (Option subOpt : ((OptionGroup)option).getOptions()) {
		    verifyRequiredOptions(subOpt);
		}
	    }
	}
    }

    //
    // Static methods
    //

    public static void setInBean(OptionMap[] maps, Object bean)
	throws InvalidOptArgException, IntrospectionException,
	IllegalAccessException, NoSuchMethodException {

	// Populate bean
	for (OptionMap map : maps) {

	    ParsedOption parsed = map.getParsed();
	    String opt = parsed.getOpt();
	    String optArg = parsed.getOptArg();

//	    // Call boolean mutators for no-arg options
//	    if (!map.getOption().getTakesArgument()) {
//		optArg = Boolean.toString(true);
//	    }

//	    System.out.println("opt: " + opt);
//	    System.out.println("optArg: " + optArg);
//	    System.out.println("argName: " + map.getOption().getArgName());

	    OptionElement option = map.getOption();
	    String[] names = option.getNames();

	    // Handle no-opt options
	    if (names.length == 1 && names[0].isEmpty()) {
		names = new String[] {option.getArgName()};
	    }

	    List<String> mutators = new ArrayList<String>(names.length);
	    for (int i = 0; i < names.length; i++) {
		String name = TextUtil.toJavaIdentifier(names[i], "");
		if (name.isEmpty()) {
		    name = names[i];
		}

//		System.out.println("Looking for property: " + name);
		try {
		    BeanUtil.setPropertyInBean(bean, name, optArg);
		    break;
		}

		// Thrown by data conversion routines
		catch (RuntimeException e) {
//		    System.out.println("Caught RuntimeException: " +
//			e.getMessage());
		    throw new InvalidOptArgException(opt, optArg, maps, e);
		}

		// Thrown by data validation routines
		catch (InvocationTargetException e) {
//		    System.out.println("Caught InvocationTargetException: " +
//			e.getMessage());
		    throw new InvalidOptArgException(opt, optArg,
			maps, e.getTargetException());
		}

		// No appropriate mutator in bean
		catch (NoSuchMethodException e) {
//		    System.out.println("Caught NoSuchMethodException: " +
//			e.getMessage());

		    // Strip class from fully-qualified method
		    mutators.add(e.getMessage().replaceFirst(".*\\.", ""));

		    if (i == names.length - 1) {
			// No need to internationalize since this is an error
			// that should only be seen during development
			throw new NoSuchMethodException(
			    "mutator method(s) not found (perhaps these " +
			    "methods are private?): " +
			    TextUtil.join(", ", mutators));
		    }
		}
	    }
	}
    }

    public static OptionMap[] process(String[] args, OptionGroup group,
	CommandLineParser parser, Object bean) throws OptionException,
	IntrospectionException, IllegalAccessException, NoSuchMethodException {

	parser.setArgs(args);

	CommandLineProcessor processor =
	    new CommandLineProcessor(group, parser);

	processor.process(group, null, "");

	OptionMap[] maps = processor.getProcessed();

	if (bean != null) {
	    setInBean(maps, bean);
	}

	return maps;
    }

    private static OptionException getMostSignificantException(
	OptionException a, OptionException b) {

	// Sorted in order of significance
	Class[] classes = {
	    InvalidOptArgException.class,
	    UnexpectedOptArgException.class,
	    MissingOptArgException.class,
	    OptionUseExceededException.class,
	    ConflictingOptionsException.class,
	    MissingOptionException.class,
	    InvalidOptionException.class,

	    // Catch-all (except null a and b)
	    OptionException.class
	};

	for (Class clazz : classes) {
	    boolean aIsInstance = clazz.isInstance(a);
	    boolean bIsInstance = clazz.isInstance(b);

	    if (aIsInstance) {
		if (bIsInstance) {

		    // Return the exception that occured when the most options
		    // had been validated
		    return a.getProcessed().length >
			b.getProcessed().length ? a : b;
		}
		return a;
	    }

	    if (bIsInstance) {
		return b;
	    }
	}

	return null;
    }
}
