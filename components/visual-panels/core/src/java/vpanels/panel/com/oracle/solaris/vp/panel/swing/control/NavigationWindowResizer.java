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

package com.oracle.solaris.vp.panel.swing.control;

import java.awt.*;
import java.util.*;
import java.util.List;
import javax.swing.SwingUtilities;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.util.swing.*;

public class NavigationWindowResizer implements NavigationListener {
    //
    // NavigationListener methods
    //

    @Override
    public void navigationStarted(NavigationStartEvent e) {
    }

    @Override
    public void navigationStopped(NavigationStopEvent e) {
	final List<Control> controls = getControls(e);

	GUIUtil.invokeAndWait(
	    new Runnable() {
		@Override
		public void run() {
		    resizeWindows(controls);
		}
	    });
    }

    //
    // Private methods
    //

    private List<Control> getControls(NavigationStopEvent e) {
	// Get the Controls to examine (all of the started Controls, or, if none
	// were started, the top of the Control stack (if non-null))
	List<Control> controls = e.getStarted();

	if (controls.isEmpty()) {
	    Control current = e.getSource().getCurrentControl();
	    if (current != null) {
		controls = new ArrayList<Control>(1);
		controls.add(current);
	    }
	}

	return controls;
    }

    private Set<Window> getWindows(List<Control> controls) {
	Set<Window> windows = new HashSet<Window>();

	for (Control control : controls) {
	    if (control instanceof SwingControl) {
		Component comp = ((SwingControl)control).getComponent();
		if (comp != null) {
		    Window window = SwingUtilities.getWindowAncestor(comp);
		    if (window != null) {
			windows.add(window);
		    }
		}
	    }
	}

	return windows;
    }

    private void resizeWindows(List<Control> controls) {
	for (Window window : getWindows(controls)) {
	    Dimension cur = window.getSize();
	    Dimension pref = window.getPreferredSize();

	    // Grow window if necessary, do not shrink
	    Dimension d = new Dimension(Math.max(cur.width, pref.width),
		Math.max(cur.height, pref.height));

	    Dimension screen = Toolkit.getDefaultToolkit().getScreenSize();

	    // Don't exceed screen size
	    d = new Dimension(Math.min(d.width, screen.width),
		Math.min(d.height, screen.height));

	    // Set size -- animate if visible
	    if (window.isVisible()) {
		new ResizeAnimator(window, d);
	    } else {
		window.setSize(d);
	    }
	}
    }
}
