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

package com.oracle.solaris.vp.panels.browser.client.swing;

import java.util.Map;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.control.SwingControl;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class PanelControl
    extends SwingControl<BrowserPanelDescriptor, PanelPanel> {

    /*
     * Static data
     */

    public static final String ID = "panel";
    public static final String PARAM_PANEL = "panel";
    private static final String NAME = Finder.getString("browser.panel.title");

    /*
     * Instance data
     */
    private PanelManagedObject panel_ = null;

    /*
     * Constructors
     */

    public PanelControl(BrowserPanelDescriptor descriptor)
    {
	super(ID, NAME, descriptor);
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

	String param = getParameter(parameters, PARAM_PANEL);

	PanelManagedObject panel = getPanelDescriptor().getPanel(param);
	if (panel == null)
	    throw new InvalidParameterException(getId(), PARAM_PANEL, param);

	panel_ = panel;
	setName(panel.getName());

	super.start(navigator, parameters);
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	super.stop(isCancel);

	panel_ = null;
    }

    /*
     * SwingControl methods
     */

    @Override
    protected PanelPanel createComponent()
    {
	return (new PanelPanel());
    }

    @Override
    protected void initComponent()
    {
	getComponent().init(panel_);
    }

    public PanelManagedObject getManagedObject()
    {
	return (panel_);
    }
}
