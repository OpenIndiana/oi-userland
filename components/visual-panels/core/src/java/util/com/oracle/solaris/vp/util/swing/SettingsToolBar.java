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
import javax.swing.*;
import javax.swing.border.Border;
import com.oracle.solaris.vp.util.swing.layout.*;

/**
 * The {@code SettingsToolBar} class is a tool bar initialized with a {@code
 * RowLayout}, a {@link #getDefaultConstraint}, and containing a greedy {@code
 * #getSpacerIndex spacer component}.  Components added before the spacer will
 * be left-justified; those added after will be right-justtified.
 */
@SuppressWarnings({"serial"})
public class SettingsToolBar extends JPanel {
    //
    // Instance data
    //

    private Spacer spacer = new Spacer();

    private ContainerListener setVisibleOnAdd =
	new ContainerListener() {
	    @Override
	    public void componentAdded(ContainerEvent e) {
		setVisible();
	    }

	    @Override
	    public void componentRemoved(ContainerEvent e)  {
		setVisible();
	    }
	};

    //
    // Constructors
    //

    public SettingsToolBar() {
	RowLayout layout = new RowLayout(HorizontalAnchor.FILL);

	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.CENTER, GUIUtil.getButtonGap());

	layout.setDefaultConstraint(r);
	setLayout(layout);

	// Add spacer
	add(spacer, r.clone().setWeight(1));

	int gap = GUIUtil.getButtonGap();
	Border border = BorderFactory.createEmptyBorder(gap, gap, gap, gap);
	setBorder(border);

	// By default, make invisible until Components are added to it
	setVisible(false);
	addContainerListener(setVisibleOnAdd);
    }

    /**
     * Gets the default constraint of the RowLayout used by this {@code
     * SettingsToolBar}.
     */
    public RowLayoutConstraint getDefaultConstraint() {
	return ((RowLayout)getLayout()).getDefaultConstraint();
    }

    /**
     * Returns the index of the spacer component of this tool bar, or -1 if the
     * spacer has been removed.
     */
    public int getSpacerIndex() {
	Component[] comps = getComponents();
	for (int i = 0; i < comps.length; i++) {
	    if (comps[i] == spacer) {
		return i;
	    }
	}
	return -1;
    }

    /**
     * Sets the visibility of this {@code SettingsToolBar} based on its contents
     * or other criteria.  Automatically called when a child {@code Component}
     * is added.
     * <p/>
     * This default implementation sets this {@code SettingsToolBar} to be
     * visible if some {@code Component} other than the {@link Spacer} has been
     * added, or invisble otherwise.
     */
    protected void setVisible() {
	Component[] comps = getComponents();
	setVisible(comps.length > 1 || (comps.length == 1 &&
	    comps[0] != spacer));
    }
}
