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

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.net.UnknownHostException;
import java.util.*;
import java.util.logging.Level;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panel.swing.control.SettingsControl;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class ServiceEditControl
    extends SettingsControl<FirewallPanelDescriptor, ServiceEditPanel> {

    //
    // Static data
    //

    public static final String ID = "edit";
    public static final String PARAM_SVC = "service";

    //
    // Instance data
    //

    private ServiceManagedObject service;

    //
    // Constructors
    //

    public ServiceEditControl(FirewallPanelDescriptor descriptor) {
	super(ID, null, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public String getHelpMapID() {
	return "firewall-service";
    }

    @Override
    public boolean isBrowsable() {
	// This Control requires init parameters
	return false;
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	String param = getParameter(parameters, PARAM_SVC);

	ServiceManagedObject s = getPanelDescriptor().getManagedService(param);
	if (s == null) {
	    throw new InvalidParameterException(getId(), PARAM_SVC, param);
	}

	try {
	    s.refresh();
	} catch (Exception e) {
	    getLog().log(Level.SEVERE, Finder.getString("error.io.repository"));
	    throw new NavigationAbortedException(e);
	}

	service = s;
	setName(service.getName());

	setPropertyChangeSource(service);
	super.start(navigator, parameters);
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	super.stop(isCancel);

	// Remove reference so it can be garbage collected if deleted
	service = null;
    }

    //
    // SwingControl methods
    //

    @Override
    protected ServiceEditPanel createComponent() {
	return new ServiceEditPanel();
    }

    @Override
    protected void initComponent() {
	getComponent().setPanelDescriptor(service.getPanelDescriptor());
	getComponent().init(service);
    }

    //
    // SettingsControl methods
    //

    @Override
    protected void save() throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	ServiceEditPanel component = getComponent();
	AccessPolicy policy = component.getAccessProperty().getValue();
	String locale = Locale.getDefault().getLanguage();

	setPropertyChangeIgnore(true);

	try {
	    service.setModelAccessPolicy(policy);
	    super.save();
	} catch (UnknownHostException e) {
	    getLog().log(Level.SEVERE, e.getMessage());
	    throw new ActionFailedException(e);

	} catch (MissingScfDataException e) {
	    getLog().log(Level.SEVERE, e.getMessage());
	    throw new ActionFailedException(e);

	} catch (InvalidScfDataException e) {
	    getLog().log(Level.SEVERE, e.getMessage());
	    throw new ActionFailedException(e);

	} catch (ScfException e) {
	    SmfUtil.throwActionException(e);

	} catch (SecurityException e) {
	    throw new ActionUnauthorizedException(e);
	} finally {
	    setPropertyChangeIgnore(false);
	}
    }

    public ServiceManagedObject getManagedService() {
	return service;
    }
}
