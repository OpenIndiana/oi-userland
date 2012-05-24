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

package com.oracle.solaris.vp.util.swing.glass;

import java.awt.Component;
import javax.swing.JPanel;
import com.oracle.solaris.vp.util.swing.ShowingListener;

@SuppressWarnings({"serial"})
public class SimpleGlassPane extends JPanel {
    //
    // Instance data
    //

    private ShowingListener showingListener;

    //
    // Constructors
    //

    public SimpleGlassPane() {
	setOpaque(false);

	addHierarchyListener(
	    new ShowingListener() {
		@Override
		public void componentHidden() {
		    SimpleGlassPane.this.componentHidden();
		}

		@Override
		public void componentShown() {
		    SimpleGlassPane.this.componentShown();
		}
	    });
    }

    //
    // Component methods
    //

    /**
     * Calls {@link #componentToBeVisible} or {@link #componentToBeInvisible} as
     * appropriate, then forwards to superclass.
     */
    @Override
    public void setVisible(boolean visible) {
	if (visible != isVisible()) {
	    if (visible) {
		componentToBeVisible();
	    } else {
		componentToBeInvisible();
	    }
	    super.setVisible(visible);
	}
    }

    //
    // SimpleGlassPane methods
    //

    /**
     * Called when this {@code SimpleGlassPane}'s {@link #isShowing showing}
     * status changes to {@code false}.
     * </p>
     * This default implementation does nothing.
     */
    public void componentHidden() {
    }

    /**
     * Called when this {@code SimpleGlassPane}'s {@link #isShowing showing}
     * status changes to {@code true}.
     * </p>
     * This default implementation does nothing.
     */
    public void componentShown() {
    }

    /**
     * Called when this {@code SimpleGlassPane}'s {@link #isVisible visibility}
     * is about to be set to {@code true}.
     * </p>
     * This default implementation does nothing.
     */
    public void componentToBeVisible() {
    }

    /**
     * Called when this {@code SimpleGlassPane}'s {@link #isVisible visibility}
     * is about to be set to {@code false}.
     * </p>
     * This default implementation does nothing.
     */
    public void componentToBeInvisible() {
    }

    protected ShowingListener getShowingListener() {
	return showingListener;
    }
}
