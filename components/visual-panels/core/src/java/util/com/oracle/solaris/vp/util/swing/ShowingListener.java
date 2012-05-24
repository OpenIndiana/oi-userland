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

package com.oracle.solaris.vp.util.swing;

import java.awt.Component;
import java.awt.event.*;

/**
 * When added as a {@code HierarchyListener}, the {@code ShowingListener} class
 * listens for changes in the showing property of a single {@code Component}.  A
 * single {@code ShowingListener} should NOT be added as a listener to more than
 * one {@code Component}.
 */
public class ShowingListener implements HierarchyListener {
    //
    // Instance data
    //

    private Boolean showing;

    //
    // HierarchyListener methods
    //

    @Override
    public void hierarchyChanged(HierarchyEvent e) {
	updateShowing(e.getComponent());
    }

    //
    // ShowingListener methods
    //

    /**
     * Calls {@link #componentHidden} or {@link #componentShown} if the
     * listening {@code Component}'s showing status has changed (or if neither
     * method has been called since this listener was registered).
     *
     * @param	    comp
     *		    the listening {@code Component}
     */
    public void updateShowing(Component comp) {
	boolean showing = comp.isShowing();
	if (this.showing == null || showing != this.showing) {
	    this.showing = showing;

	    if (showing) {
		componentShown();
	    } else {
		componentHidden();
	    }
	}
    }

    /**
     * Called when the listening {@code Component}'s showing status changes to
     * {@code false}.
     * </p>
     * This default implementation does nothing.
     */
    public void componentHidden() {
    }

    /**
     * Called when the listening {@code Component}'s showing status changes to
     * {@code true}.
     * </p>
     * This default implementation does nothing.
     */
    public void componentShown() {
    }
}
