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

public abstract class OptionGroup extends Option {
    //
    // Instance data
    //

    private boolean required;
    private boolean documented;
    private List<Option> options = new ArrayList<Option>();

    // Used when processing options
    private List<Option> usedOptions = new ArrayList<Option>();

    //
    // Constructors
    //

    public OptionGroup(boolean required) {
	setRequired(required);
	setDocumented(true);
    }

    public OptionGroup(boolean required, Option[] options) {
	this(required);
	this.options.addAll(Arrays.asList(options));
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
    // OptionGroup methods
    //

    public void addOption(Option option) {
	synchronized (options) {
	    options.add(option);
	}
    }

    protected List<Option> getOptions() {
	return options;
    }

    public List<Option> getUsedOptions() {
	return usedOptions;
    }

    protected boolean removeOption(Option option) {
	synchronized (options) {
	    return options.remove(option);
	}
    }

    public void setDocumented(boolean documented) {
	this.documented = documented;
    }

    public void setRequired(boolean required) {
	this.required = required;
    }

    //
    // Private methods
    //

    private void addUsedOption(Option option) {
	usedOptions.add(option);
    }

    private boolean removeUsedOption(Option option) {
	return usedOptions.remove(option);
    }
}
