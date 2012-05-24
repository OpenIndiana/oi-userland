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

package com.oracle.solaris.vp.util.swing.layout;

import java.awt.*;
import javax.swing.Scrollable;

public class SimpleViewportLayout implements LayoutManager {
    private boolean usePreferredAsMinimum;

    //
    // Constructors
    //

    public SimpleViewportLayout(boolean usePreferredAsMinimum) {
	this.usePreferredAsMinimum = usePreferredAsMinimum;
    }

    //
    // LayoutManager methods
    //

    @Override
    public void addLayoutComponent(String name, Component comp) {
    }

    @Override
    public void layoutContainer(Container container) {
	Insets insets = container.getInsets();
	Dimension cSize = container.getSize();

	// The amount of space we have to work with
	int cWidth = cSize.width - insets.left - insets.right;
	int cHeight = cSize.height - insets.top - insets.bottom;

	Component[] comps = container.getComponents();

	for (int i = 0; i < comps.length; i++) {
	    Component c = comps[i];
	    int width = 0;
	    int height = 0;

	    // Assume only a single Component
	    if (i == 0) {
		Dimension d = usePreferredAsMinimum ?
		    c.getPreferredSize() : c.getMinimumSize();

		width = Math.max(cWidth, d.width);
		height = Math.max(cHeight, d.height);

		if (c instanceof Scrollable) {
		    Scrollable s = (Scrollable)c;

		    // Does this Component scroll horizontally?
		    if (s.getScrollableTracksViewportWidth()) {
			width = cWidth;
		    }

		    // Does this Component scroll vertically?
		    if (s.getScrollableTracksViewportHeight()) {
			height = cHeight;
		    }
		}
	    }

	    c.setBounds(insets.left, insets.top, width, height);
	}
    }

    @Override
    public Dimension minimumLayoutSize(Container container) {
	return new Dimension(0, 0);
    }

    @Override
    public Dimension preferredLayoutSize(Container container) {
	Component[] comps = container.getComponents();
	Insets insets = container.getInsets();
	int width = insets.left + insets.right;
	int height = insets.top + insets.bottom;

	if (comps.length > 0) {
	    Dimension d = comps[0].getPreferredSize();
	    width += d.width;
	    height += d.height;
	}

	return new Dimension(width, height);
    }

    @Override
    public void removeLayoutComponent(Component comp) {
    }
}
