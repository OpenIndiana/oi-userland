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

package com.oracle.solaris.vp.panels.coreadm.client.swing;

import java.awt.Component;
import java.util.*;
import com.oracle.solaris.vp.panel.common.action.StructuredAction;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class CoresTab
    extends SettingsControl<CoreAdmPanelDescriptor, CoresPanel> {

    //
    // Static data
    //

    private static final String ID = "activity";

    private static final String NAME = Finder.getString("core.objects.title");

    //
    // Instance data
    //

    protected UpdateCoreAction updateAction = new UpdateCoreAction(this);

    @SuppressWarnings({"unchecked"})
    protected StructuredAction<List<CoreManagedObject>, ?, ?>[] actions =
	new StructuredAction[] {
	    updateAction
	};

    //
    // Constructors
    //

    public CoresTab(CoreAdmPanelDescriptor descriptor) {
	super(ID, NAME, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public String getHelpMapID() {
	return "coreadm-selector";
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	super.start(navigator, parameters);
	getPanelDescriptor().updateCoreConfig();
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(CoresPanel panel) {
	super.configComponent(panel);
	addDefaultHelpAction();
    }

    @Override
    protected CoresPanel createComponent() {
	return new CoresPanel(getPanelDescriptor(), actions, null);
    }
}
