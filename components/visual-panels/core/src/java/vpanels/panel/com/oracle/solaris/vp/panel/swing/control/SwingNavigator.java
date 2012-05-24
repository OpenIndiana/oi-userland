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

package com.oracle.solaris.vp.panel.swing.control;

import java.awt.*;
import java.util.*;
import java.util.List;
import javax.swing.SwingUtilities;
import com.oracle.solaris.vp.panel.common.control.*;

@SuppressWarnings({"serial"})
public class SwingNavigator extends Navigator {
    //
    // Constructors
    //

    public SwingNavigator() {
	// Resize windows on each navigation
	addNavigationListener(new NavigationWindowResizer());

	// Display a dialog on error
	addNavigationListener(new SwingNavigationErrorHandler());
    }

    //
    // SwingNavigator methods
    //

    public Window getFirstWindow() {
	return getFirstWindow(this);
    }

    public Window getLastWindow() {
	return getLastWindow(this);
    }

    public List<Window> getWindows() {
	return getWindows(this);
    }

    //
    // Static methods
    //

    /**
     * Searches forward through the navigation stack for a {@link SwingControl}
     * with a {@code Component} in a {@code Window}, then returns that {@code
     * Window}.
     */
    public static Window getFirstWindow(Navigator navigator) {
	for (Control control : navigator.getPath()) {
	    if (control instanceof SwingControl) {
		Component comp = ((SwingControl)control).getComponent();
		if (comp != null) {
		    Window window = SwingUtilities.getWindowAncestor(comp);
		    if (window != null) {
			return window;
		    }
		}
	    }
	}
	return null;
    }

    /**
     * Searches backward through the navigation stack for a {@link SwingControl}
     * with a {@code Component} in a {@code Window}, then returns that {@code
     * Window}.
     */
    public static Window getLastWindow(Navigator navigator) {
	List<Control> controls = navigator.getPath();
	for (int i = controls.size() - 1; i >= 0; i--) {
	    Control control = controls.get(i);
	    if (control instanceof SwingControl) {
		Component comp = ((SwingControl)control).getComponent();
		if (comp != null) {
		    Window window = SwingUtilities.getWindowAncestor(comp);
		    if (window != null) {
			return window;
		    }
		}
	    }
	}
	return null;
    }

    /**
     * Searches forward through the navigation stack for all {@link
     * SwingControl}s with a {@code Component} in a {@code Window}, then returns
     * a {@code List} of those {@code Window}s.
     */
    public static List<Window> getWindows(Navigator navigator) {
	List<Window> windows = new LinkedList<Window>();
	for (Control control : navigator.getPath()) {
	    if (control instanceof SwingControl) {
		Component comp = ((SwingControl)control).getComponent();
		if (comp != null) {
		    Window window = SwingUtilities.getWindowAncestor(comp);
		    if (window != null && !windows.contains(window)) {
			windows.add(window);
		    }
		}
	    }
	}
	return windows;
    }
}
