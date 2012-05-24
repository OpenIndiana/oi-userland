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

import java.awt.Component;
import java.util.Map;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.control.SettingsControl;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.MutableProperty;

public class VirtualHostSSLControl
    extends SettingsControl<ApachePanelDescriptor, VirtualHostSSLPanel> {

    //
    // Static data
    //

    public static final String ID = "ssl";
    public static final String NAME = Finder.getString("vhost.ssl.name");

    //
    // Instance data
    //

    private VirtualHostControl parent;

    //
    // Constructors
    //

    public VirtualHostSSLControl(VirtualHostControl parent) {
	super(ID, NAME, parent.getPanelDescriptor());
	this.parent = parent;
    }

    //
    // Control methods
    //

    @Override
    public String getHelpMapID() {
	return "apache-vhosts-ssl";
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
	    VirtualHostSSLPanel panel = getComponent();

	    vHost.getSslEnabledProperty().setFirstValue(
		panel.getEnabledProperty().getValue());

	    vHost.getSslIpProperty().setFirstValue(
		panel.getIpProperty().getValue());

	    vHost.getSslCertProperty().setFirstValue(
		panel.getCertProperty().getValue());

	    vHost.getSslKeyProperty().setFirstValue(
		panel.getKeyProperty().getValue());

	    vHost.getSslPortProperty().setFirstValue(
		panel.getPortProperty().getValue());
	} finally {
	    setPropertyChangeIgnore(false);
	}
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	setPropertyChangeSource(parent.getVirtualHost(),
	    VirtualHost.PROPERTY_SSL_ENABLED,
	    VirtualHost.PROPERTY_SSL_IP,
	    VirtualHost.PROPERTY_SSL_PORT,
	    VirtualHost.PROPERTY_SSL_CERT,
	    VirtualHost.PROPERTY_SSL_KEY);

	super.start(navigator, parameters);
    }

    //
    // SwingControl methods
    //

    @Override
    protected VirtualHostSSLPanel createComponent() {
	VirtualHostSSLPanel panel = new VirtualHostSSLPanel();
	return panel;
    }

    @Override
    protected void deinitComponent() {
	getComponent().init(null);
    }

    @Override
    protected void initComponent() {
	VirtualHost vHost = parent.getVirtualHost();
	VirtualHostSSLPanel panel = getComponent();
	panel.getChangeableAggregator().reset();
	panel.init(vHost);
    }
}
