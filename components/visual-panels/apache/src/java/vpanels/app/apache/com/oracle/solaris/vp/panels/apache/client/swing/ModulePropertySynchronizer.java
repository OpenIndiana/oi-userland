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

package com.oracle.solaris.vp.panels.apache.client.swing;

import java.util.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.property.*;

/**
 * The {@code ModulePropertySynchronizer} class synchronizes a {@link
 * MutableProperty}{@code <List<String>>} with a {@code Module}'s {@link
 * MutableProperty}s so that changes in one will automatically be reflected in
 * the other.
 */
public class ModulePropertySynchronizer
    extends PropertySynchronizer<List<String>, Module> {

    //
    // Static data
    //

    public static final String SMF_VALUE_PREFIX = "MODULE:";

    //
    // Instance data
    //

    private ChangeListener listener =
	new ChangeListener() {
	    @Override
	    public void stateChanged(ChangeEvent e) {
		objectChanged();
	    }
	};

    //
    // Constructors
    //

    public ModulePropertySynchronizer(MutableProperty<List<String>> property,
	Module module, boolean initFromProp) {

	super(property, module, initFromProp);

	module.getNameProperty().addChangeListener(listener);
	module.getFileProperty().addChangeListener(listener);
    }

    /**
     * Constructs a {@code ModulePropertySynchronizer} with initial
     * synchronization from {@code property} to {@code module}.
     */
    public ModulePropertySynchronizer(MutableProperty<List<String>> property,
	Module module) {

	this(property, module, true);
    }

    //
    // PropertySynchronizer methods
    //

    @Override
    protected boolean differ() {
	return super.differ() || !ObjectUtil.equals(getSavedValue(),
	    getProperty().getSavedValue());
    }

    @Override
    public void desynchronize() {
	super.desynchronize();

	Module module = getObject();
	module.getNameProperty().removeChangeListener(listener);
	module.getFileProperty().removeChangeListener(listener);
    }

    @Override
    public List<String> getValue() {
	return getValue(false);
    }

    @Override
    protected void syncObjectChanges() {
	super.syncObjectChanges();
	List<String> value = getSavedValue();
	getProperty().setSavedValue(value);
    }

    @Override
    protected void syncPropertyChanges() {
	super.syncPropertyChanges();
	List<String> value = getProperty().getSavedValue();
	setSavedValue(value);
    }

    @Override
    public void setValue(List<String> value) {
	setValue(value, false);
    }

    //
    // ModulePropertySynchronizer methods
    //

    public List<String> getSavedValue() {
	return getValue(true);
    }

    public void setSavedValue(List<String> value) {
	setValue(value, true);
    }

    //
    // Private methods
    //

    private List<String> getValue(boolean saved) {
	List<String> value = new ArrayList<String>(2);

	Module module = getObject();

	MutableProperty<String> nameProperty = module.getNameProperty();
	String name = saved ? nameProperty.getSavedValue() :
	    nameProperty.getValue();

	value.add(SMF_VALUE_PREFIX + name);

	MutableProperty<String> fileProperty = module.getFileProperty();
	String file = saved ? fileProperty.getSavedValue() :
	    fileProperty.getValue();

	value.add(file);

	return value;
    }

    private void setValue(List<String> value, boolean saved) {
	Module module = getObject();
	String name = null;
	String file = null;

	if (value != null) {
	    for (String sValue : value) {
		if (sValue.startsWith(SMF_VALUE_PREFIX)) {
		    name = sValue.substring(SMF_VALUE_PREFIX.length());
		    if (name.isEmpty()) {
			name = null;
		    }
		} else {
		    file = sValue;
		    if (file.isEmpty()) {
			file = null;
		    }
		}
	    }
	}

	MutableProperty<String> nameProperty = module.getNameProperty();
	if (saved) {
	    nameProperty.setSavedValue(name);
	} else {
	    nameProperty.setValue(name);
	}

	MutableProperty<String> fileProperty = module.getFileProperty();
	if (saved) {
	    fileProperty.setSavedValue(file);
	} else {
	    fileProperty.setValue(file);
	}
    }
}
