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

import java.util.Map;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.control.SettingsControl;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class ModuleControl
    extends SettingsControl<ApachePanelDescriptor, ModulePanel> {

    //
    // Static data
    //

    public static final String ID = "module";
    public static final String PARAM_MODULE = "module";

    //
    // Instance data
    //

    private ModulesControl parent;
    private Module module;

    //
    // Constructors
    //

    public ModuleControl(ApachePanelDescriptor descriptor,
	ModulesControl parent) {

	super(ID, null, descriptor);

	this.parent = parent;
    }

    //
    // Control methods
    //

    @Override
    protected UnsavedChangesAction getUnsavedChangesAction() {
	// Automatically save changes to the Module -- let MainControl
	// prompt the user to save them to the repo
	return UnsavedChangesAction.SAVE;
    }

    @Override
    public boolean isBrowsable() {
	// This Control requires init parameters
	return false;
    }

    @Override
    protected boolean isChanged() {
	// Save unconditionally, since a property that reports itself as
	// unchanged in the panel may still be changed from the corresponding
	// property in the Module.  Alternatively, we could compare each panel
	// property to its Module counterpart and save only if there are
	// differences, but this is easier and save() has low overhead.
	return true;
    }

    @Override
    protected void save() throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	setPropertyChangeIgnore(true);

	try {
	    ModulePanel panel = getComponent();

	    String name = panel.getNameProperty().getValue();
	    String file = panel.getFileProperty().getValue();

	    validate(name, file);

	    Module child = module.getParent().getModule(name);
	    if (child != null && child != module) {
		throw new ActionFailedException(Finder.getString(
		    "module.error.duplicate", name));
	    }

	    module.getNameProperty().setValue(name);
	    module.getFileProperty().setValue(file);
	} finally {
	    setPropertyChangeIgnore(false);
	}
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	String param = getParameter(parameters, PARAM_MODULE);

	Module module = parent.getHasModules().getModules().
	    getModule(param);
	if (module == null) {
	    throw new InvalidParameterException(getId(), PARAM_MODULE, param);
	}

	this.module = module;
	setName(module.getName());

	setPropertyChangeSource(module);
	super.start(navigator, parameters);
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	super.stop(isCancel);

	// Remove reference so it can be garbage collected if deleted
	module = null;
    }

    //
    // SwingControl methods
    //

    @Override
    protected ModulePanel createComponent() {
	return new ModulePanel();
    }

    @Override
    protected void initComponent() {
	ModulePanel panel = getComponent();
	panel.getChangeableAggregator().reset();
	panel.init(module);
    }

    //
    // ModuleControl methods
    //

    public Module getModule() {
	return module;
    }

    //
    // Static methods
    //

    /**
     * Validates the entered data in the UI.
     *
     * @exception   ActionFailedException
     *		    if the entered data is invalid (the thrown exception will
     *		    contain a localized error message)
     */
    public static void validate(String name, String file)
	throws ActionFailedException {

	if (name.isEmpty()) {
	    throw new ActionFailedException(Finder.getString(
		"module.error.name.empty", name));
	}

	if (!Module.isValidName(name)) {
	    throw new ActionFailedException(Finder.getString(
		"module.error.name.invalid", name));
	}

	if (file.isEmpty()) {
	    throw new ActionFailedException(Finder.getString(
		"module.error.file.empty", file));
	}
    }
}
