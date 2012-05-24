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

package com.oracle.solaris.vp.panel.common.control;

import java.util.List;

/**
 * The {@code NavigationErrorHandler} class chooses the best path to re-navigate
 * to on navigation error.  If no {@link Control}s were started as a result of
 * the failed navigation, then the navigation is considered a complete failure
 * and a navigation back to the previous path is scheduled asynchronously.
 * Otherwise, a navigation to the current path is scheduled, which will cause
 * any path returned by {@link Navigator#getCurrentControl the current
 * Control}'s {@link Control#getForwardingPath} method to be followed.
 */
public class NavigationErrorHandler implements NavigationListener {
    //
    // NavigationListener methods
    //

    @Override
    public void navigationStarted(NavigationStartEvent e) {
    }

    @Override
    public void navigationStopped(NavigationStopEvent event) {
	if (!event.getNavigationSuccessful()) {
	    Navigator navigator = event.getSource();

	    boolean equal = false;
	    Navigable[] last = event.getPreviousPath();
	    List<Control> current = navigator.getPath();
	    if (last.length == current.size()) {
		equal = true;
		for (int i = 0; i < last.length; i++) {
		    if (!Navigable.Util.equals(last[i], current.get(i))) {
			equal = false;
			break;
		    }
		}
	    }

	    // Only re-navigate if the last path differs from the current path
	    if (!equal) {
                // If any Controls were started as a result of this navigation,
                // assume it was successful enough to stay where we are.
                // Otherwise, go back.
		if (event.getStarted().isEmpty()) {
		    // Go back
		    navigator.goToAsync(true, null, last);
		} else {
		    // Navigate to the current path, which will forward to the
		    // current Control's getForwardingPath, if any
		    navigator.goToAsync(true, navigator.getCurrentControl());
		}
	    }
	}
    }
}
