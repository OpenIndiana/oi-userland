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

package com.oracle.solaris.vp.panels.sysmon.client.swing;

import java.awt.event.*;
import java.util.List;
import javax.swing.Icon;
import com.oracle.solaris.vp.panel.swing.control.DefaultFrameControl;
import com.oracle.solaris.vp.util.swing.*;

public class SysMonPopupControl
    extends DefaultFrameControl<SysMonPanelDescriptor> implements HasIcons {

    //
    // Static data
    //

    public static final String ID = "frame";

    //
    // Constructors
    //

    public SysMonPopupControl(SysMonPanelDescriptor descriptor) {
	super(ID, null, descriptor);
    }

    //
    // HasIcons methods
    //

    @Override
    public List<? extends Icon> getIcons() {
	return getPanelDescriptor().getIcons();
    }

    //
    // DefaultControl methods
    //

    @Override
    protected void ensureChildrenCreated() {
	if (children.size() == 0) {
	    addChildren(new SysMonListControl(getPanelDescriptor()));
	}
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(final ExtFrame frame) {
	super.configComponent(frame);

	// Do this first, before the HierarchyListener can call pack()
//	frame.setUndecorated(true);

	// Resize window when components are added/removed
	frame.addHierarchyListener(
	    new HierarchyListener() {
		@Override
		public void hierarchyChanged(HierarchyEvent e) {
		    frame.pack();
		}
	    });

	frame.setAutoResizeEnabled(true);

//	// Navigate to parent when window loses focus
//	frame.addWindowFocusListener(
//	    new WindowAdapter() {
//		@Override
//		public void windowLostFocus(WindowEvent e) {
//		    Navigator navigator = getNavigator();
//		    if (navigator != null) {
//			navigator.goToAsync(false, SysMonPopupControl.this,
//			    Navigator.PARENT_NAVIGABLE);
//		    }
//		}
//	    });
    }
}
