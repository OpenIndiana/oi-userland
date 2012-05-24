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
 * Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.apache.client.swing;

import java.awt.event.*;
import java.beans.PropertyChangeListener;
import java.util.Map;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.smf.SmfEnabledProperty;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.MutableProperty;

public class GlobalControl
    extends SettingsControl<ApachePanelDescriptor, GlobalPanel>
    implements PropertyChangeListener, HasMimeTypes, HasModules {

    //
    // Static data
    //

    public static final String ID = "global";
    public static final String NAME = Finder.getString("global.name");

    //
    // Constructors
    //

    public GlobalControl(ApachePanelDescriptor descriptor) {
	super(ID, NAME, descriptor);
    }

    //
    // HasMimeTypes methods
    //

    @Override
    public MimeTypes getMimeTypes() {
	return getPanelDescriptor().getMimeTypes();
    }

    //
    // HasModules methods
    //

    @Override
    public Modules getModules() {
	return getPanelDescriptor().getModules();
    }

    //
    // Control methods
    //

    @Override
    public String getHelpMapID() {
	return "apache-global";
    }

    @Override
    protected UnsavedChangesAction getUnsavedChangesAction() {
	// Automatically save changes to the ApachePanelDescriptor --
	// let MainControl prompt the user to save them to the repo
	return UnsavedChangesAction.SAVE;
    }

    @Override
    protected boolean isChanged() {
	// Save unconditionally, since a property that reports itself as
	// unchanged in the panel may still be changed from the corresponding
	// property in the ApachePanelDescriptor.  Alternatively, we could
	// compare each panel property to its ApachePanelDescriptor counterpart
	// and save only if there are differences, but this is easier and save()
	// has low overhead.
	return true;
    }

    @Override
    protected void save() {
	setPropertyChangeIgnore(true);

	try {
	    GlobalPanel panel = getComponent();
	    ApachePanelDescriptor descriptor = getPanelDescriptor();

	    MutableProperty<Boolean> customEnabledProperty =
		panel.getCustomEnabledProperty();

	    MutableProperty<String> customFileProperty =
		panel.getCustomFileProperty();

	    descriptor.getCustomEnabledProperty().setFirstValue(
		customEnabledProperty.getValue());

	    descriptor.getCustomFileProperty().setFirstValue(
		customFileProperty.getValue());

	    descriptor.getEnabledProperty().setValue(
		panel.getEnabledProperty().getValue());
	} finally {
	    setPropertyChangeIgnore(false);
	}
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

        setPropertyChangeSource(getPanelDescriptor(), SmfEnabledProperty.NAME,
	    ApachePanelDescriptor.PROPERTY_CUSTOM_ENABLED,
	    ApachePanelDescriptor.PROPERTY_CUSTOM_FILE);

	super.start(navigator, parameters);
    }

    //
    // DefaultControl methods
    //

    @Override
    protected void ensureChildrenCreated() {
	if (children.size() == 0) {
	    ApachePanelDescriptor descriptor = getPanelDescriptor();

            DefaultControl control = new DialogControl<ApachePanelDescriptor>(
		descriptor);
	    control.addChildren(
		new MimeTypesControl(descriptor, this),
		new ModulesControl(descriptor, this));

	    addChildren(control);
	}
    }

    //
    // SwingControl methods
    //

    @Override
    protected GlobalPanel createComponent() {
	GlobalPanel panel = new GlobalPanel();

	panel.getMimeTypesButton().addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    Navigable[] navigables = {
			new SimpleNavigable(DialogControl.ID, null),
			new SimpleNavigable(MimeTypesControl.ID, null),
		    };

		    getNavigator().goToAsync(false, GlobalControl.this,
			navigables);
		}
	    });

	panel.getModulesButton().addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    Navigable[] navigables = {
			new SimpleNavigable(DialogControl.ID, null),
			new SimpleNavigable(ModulesControl.ID, null),
		    };

		    getNavigator().goToAsync(false, GlobalControl.this,
			navigables);
		}
	    });

	return panel;
    }

    @Override
    protected void deinitComponent() {
	ApachePanelDescriptor descriptor = getPanelDescriptor();
	GlobalPanel panel = getComponent();

	descriptor.getMimeTypes().getChangeableAggregator().
	    removeChangeListener(panel.getMimeTypesButton());

	descriptor.getModules().getChangeableAggregator().
	    removeChangeListener(panel.getModulesButton());

	panel.init(null);
    }

    @Override
    protected void initComponent() {
	ApachePanelDescriptor descriptor = getPanelDescriptor();
	GlobalPanel panel = getComponent();

	descriptor.getMimeTypes().getChangeableAggregator().addChangeListener(
	    panel.getMimeTypesButton());

	descriptor.getModules().getChangeableAggregator().addChangeListener(
	    panel.getModulesButton());

	panel.getChangeableAggregator().reset();
	panel.init(descriptor);
    }
}
