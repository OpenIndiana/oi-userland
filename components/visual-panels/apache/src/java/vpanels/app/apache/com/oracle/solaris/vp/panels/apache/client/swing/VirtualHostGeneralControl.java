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
import java.util.Map;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.MutableProperty;

public class VirtualHostGeneralControl
    extends SettingsControl<ApachePanelDescriptor, VirtualHostGeneralPanel>
    implements HasMimeTypes {

    //
    // Static data
    //

    public static final String ID = "general";
    public static final String NAME = Finder.getString("vhost.general.name");

    //
    // Instance data
    //

    private VirtualHostControl parent;

    //
    // Constructors
    //

    public VirtualHostGeneralControl(VirtualHostControl parent) {
	super(ID, NAME, parent.getPanelDescriptor());
	this.parent = parent;
    }

    //
    // HasMimeTypes methods
    //

    @Override
    public MimeTypes getMimeTypes() {
	return parent.getVirtualHost().getMimeTypes();
    }

    //
    // Control methods
    //

    @Override
    public String getHelpMapID() {
	return "apache-vhosts-general";
    }

    @Override
    protected UnsavedChangesAction getUnsavedChangesAction() {
	// Automatically save changes to the VirtualHost -- let MainControl
	// prompt the user to save them to the repo
	return UnsavedChangesAction.SAVE;
    }

    @Override
    protected boolean isChanged() {
	// Save unconditionally, since a property that reports itself as
	// unchanged in the panel may still be changed from the corresponding
	// property in the VirtualHost.  Alternatively, we could compare each
	// panel property to its VirtualHost counterpart and save only if there
	// are differences, but this is easier and save() has low overhead.
	return true;
    }

    @Override
    protected void save() {
	setPropertyChangeIgnore(true);

	try {
	    VirtualHost vHost = parent.getVirtualHost();
	    VirtualHostGeneralPanel panel = getComponent();

	    vHost.getDomainProperty().setFirstValue(
		panel.getDomainProperty().getValue());

	    vHost.getEnabledProperty().setFirstValue(
		panel.getEnabledProperty().getValue());

	    vHost.getPortProperty().setFirstValue(
		panel.getPortProperty().getValue());

	    vHost.getDocRootProperty().setFirstValue(
		panel.getDocRootProperty().getValue());

	    vHost.getServeHomeDirsProperty().setFirstValue(
		panel.getServeHomeDirsProperty().getValue());

	    vHost.getCustomEnabledProperty().setFirstValue(
		panel.getCustomEnabledProperty().getValue());

	    vHost.getCustomFileProperty().setFirstValue(
		panel.getCustomFileProperty().getValue());

	} finally {
	    setPropertyChangeIgnore(false);
	}
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	setPropertyChangeSource(parent.getVirtualHost(),
	    VirtualHost.PROPERTY_ENABLED, VirtualHost.PROPERTY_PORT,
	    VirtualHost.PROPERTY_DOMAIN, VirtualHost.PROPERTY_DOCROOT,
	    VirtualHost.PROPERTY_SERVE_HOME_DIRS,
	    VirtualHost.PROPERTY_CUSTOM_ENABLED,
	    VirtualHost.PROPERTY_CUSTOM_FILE);

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
	    control.addChildren(new MimeTypesControl(descriptor, this));

	    addChildren(control);
	}
    }

    //
    // SwingControl methods
    //

    @Override
    protected VirtualHostGeneralPanel createComponent() {
	VirtualHostGeneralPanel panel = new VirtualHostGeneralPanel();

	panel.getMimeTypesButton().addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    Navigable[] navigables = {
			new SimpleNavigable(DialogControl.ID, null),
			new SimpleNavigable(MimeTypesControl.ID, null),
		    };

		    getNavigator().goToAsync(false,
			VirtualHostGeneralControl.this, navigables);
		}
	    });

	return panel;
    }

    @Override
    protected void deinitComponent() {
	VirtualHost vHost = parent.getVirtualHost();
	VirtualHostGeneralPanel panel = getComponent();

	vHost.getMimeTypes().getChangeableAggregator().removeChangeListener(
	    panel.getMimeTypesButton());

	panel.init(null);
    }

    @Override
    protected void initComponent() {
	VirtualHost vHost = parent.getVirtualHost();
	VirtualHostGeneralPanel panel = getComponent();

	vHost.getMimeTypes().getChangeableAggregator().addChangeListener(
	    panel.getMimeTypesButton());

	panel.getChangeableAggregator().reset();
	panel.init(vHost);
    }
}
