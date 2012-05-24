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

package com.oracle.solaris.vp.panels.smf.client.swing;

import java.net.URISyntaxException;
import java.util.Map;
import com.oracle.solaris.scf.common.FMRI;
import com.oracle.solaris.vp.panel.common.control.*;

/**
 * A control that, given an fmri, redirects to the panel corresponding to
 * that service or instance.
 */
public class FmriControl extends DefaultControl<SmfPanelDescriptor> {

    //
    // Static data
    //

    public static final String ID = "fmri";
    public static final String PARAM_FMRI = "fmri";

    //
    // Instance data
    //

    private Navigable[] newPath;

    //
    // Constructors
    //

    public FmriControl(SmfPanelDescriptor descriptor) {
	super(ID, null, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public Navigable[] getForwardingPath(boolean childStopped) {
	return newPath;
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

	super.start(navigator, parameters);

	String path = getParameter(parameters, PARAM_FMRI);

	FMRI fmri;
	try {
	    fmri = new FMRI(path);
	} catch (URISyntaxException ex) {
	    throw new InvalidParameterException(ID, PARAM_FMRI, path);
	}

	Navigable last;
	switch (fmri.getSvcType()) {
	case SERVICE:
	    last = ServiceTabbedControl.NAVIGABLE;
	    break;
	case INSTANCE:
	    last = new SimpleNavigable(InstanceTabbedControl.ID, null,
		InstanceTabbedControl.PARAM_INSTANCE, fmri.getInstance());
	    break;
	default:
	    throw new InvalidParameterException(ID, PARAM_FMRI, path);
	}

	newPath = new Navigable[] {
	    Navigator.PARENT_NAVIGABLE,

	    new SimpleNavigable(MainControl.ID, null,
		MainControl.PARAM_SERVICE, fmri.getService()),

	    last
	};
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	super.stop(isCancel);
	newPath = null;
    }
}
