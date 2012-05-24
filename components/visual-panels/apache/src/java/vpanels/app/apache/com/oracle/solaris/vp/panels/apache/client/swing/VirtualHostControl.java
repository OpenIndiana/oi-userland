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
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.control.TabbedControl;

public class VirtualHostControl extends TabbedControl<ApachePanelDescriptor> {
    //
    // Static data
    //

    public static final String ID = "vhost";
    public static final String PARAM_ID = "id";
    public static final String PARAM_DOMAIN = "domain";

    //
    // Instance data
    //

    private VirtualHost vHost;

    //
    // Constructors
    //

    public VirtualHostControl(ApachePanelDescriptor descriptor) {
	super(ID, null, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public boolean isBrowsable() {
	// This Control requires init parameters
	return false;
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	VirtualHost vHost;

	try {
	    String param = getParameter(parameters, PARAM_ID);
	    vHost = getPanelDescriptor().getVirtualHost(param);
	    if (vHost == null) {
		throw new InvalidParameterException(getId(), PARAM_ID, param);
	    }
	} catch (MissingParameterException e) {
	    try {
		String param = getParameter(parameters, PARAM_DOMAIN);
		vHost = getPanelDescriptor().getVirtualHostByDomain(param);
		if (vHost == null) {
		    throw new InvalidParameterException(getId(), PARAM_DOMAIN,
			param);
		}
	    } catch (MissingParameterException e2) {
		throw e;
	    }
	}

	setVirtualHost(vHost);

	super.start(navigator, parameters);
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	super.stop(isCancel);

	// Remove reference so it can be garbage collected if deleted
	setVirtualHost(null);
    }

    //
    // DefaultControl methods
    //

    @Override
    protected void ensureChildrenCreated() {
	if (children.size() == 0) {
	    addChildren(new VirtualHostGeneralControl(this));
	    addChildren(new VirtualHostSSLControl(this));
	}
    }

    //
    // VirtualHostControl methods
    //

    public VirtualHost getVirtualHost() {
	return vHost;
    }

    //
    // Private methods
    //

    private void setVirtualHost(VirtualHost vHost) {
	this.vHost = vHost;
	setName(vHost == null ? null : vHost.getName());
    }
}
