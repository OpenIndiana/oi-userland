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
import javax.swing.JTabbedPane;

public class TabbedPaneOverlayLayout extends
    UniqueConstrainedLayout<TabbedPaneOverlayLayout.Constraint> {

    //
    // Enums
    //

    public enum Constraint {
	TABS, OVERLAY
    }

    //
    // Constructors
    //

    public TabbedPaneOverlayLayout() {
	super(Constraint.TABS);
    }

    //
    // LayoutManager methods
    //

    /**
     * Lay out Components in the given Container.  Assume a column-stacked
     * anchor, which can be overridden in this class's abstract methods.
     */
    @Override
    public void layoutContainer(Container container) {
	Insets insets = container.getInsets();
	Dimension cSize = container.getSize();

	// The amount of space we have to work with
	int aWidth = cSize.width - insets.left - insets.right;
	int aHeight = cSize.height - insets.top - insets.bottom;

	// The amount the tabs must be shifted down to accomodate the component
	int tOffsetY = 0;

	Dimension tabsPreferred = null;

	JTabbedPane tabs = (JTabbedPane)constToComp.get(Constraint.TABS);
	if (tabs != null && tabs.isVisible()) {
	    tabsPreferred = tabs.getPreferredSize();
	}

	Component comp = constToComp.get(Constraint.OVERLAY);
	if (comp != null && comp.isVisible()) {
	    Dimension compPreferred = comp.getPreferredSize();

	    int cWidth = compPreferred.width;
	    int cHeight = compPreferred.height;

	    if (tabsPreferred != null) {
		// Both tabs and comp are visible
		int tHeight = getTabsHeight(tabs);

		if (tHeight > cHeight) {
		    cHeight = tHeight;
		} else {
		    tOffsetY = cHeight - tHeight;
		}

		container.setComponentZOrder(comp, 0);
		container.setComponentZOrder(tabs, 1);
	    }

	    comp.setBounds(
		insets.left + aWidth - cWidth, insets.top, cWidth, cHeight);
	}

	if (tabsPreferred != null) {
	    tabs.setBounds(
		insets.left, insets.top + tOffsetY, aWidth, aHeight - tOffsetY);
	}
    }

    //
    // AbstractLayout methods
    //

    @Override
    protected Dimension getLayoutSize(Container container, boolean preferred) {
	boolean tabsVisible = false;
	boolean compVisible = false;

	int width = 0;
	int height = 0;

	JTabbedPane tabs = (JTabbedPane)constToComp.get(Constraint.TABS);
	if (tabs != null && tabs.isVisible()) {
	    tabsVisible = true;

	    Dimension d = preferred ?
		tabs.getPreferredSize() : tabs.getMinimumSize();

	    width = d.width;
	    height = d.height;
	}

	Component comp = constToComp.get(Constraint.OVERLAY);
	if (comp != null && comp.isVisible()) {
	    compVisible = true;

	    Dimension d = preferred ?
		comp.getPreferredSize() : comp.getMinimumSize();

	    if (tabsVisible) {
		int tHeight = getTabsHeight(tabs);
		int tWidth = getTabsWidth(tabs);

		d.width += tWidth;
		width = Math.max(width, d.width);

		if (tHeight < d.height) {
		    height += d.height - tHeight;
		}
	    }
	}

	Insets insets = container.getInsets();
	width += insets.left + insets.right;
	height += insets.top + insets.bottom;

	return new Dimension(width, height);
    }

    //
    // Private methods
    //

    private int getTabsHeight(JTabbedPane tabs) {
	int highestBottom = -1;

	// Find the tab whose bottom edge is closest to the top
	for (int i = 0, n = tabs.getTabCount(); i < n; i++) {
	    Rectangle bounds = tabs.getBoundsAt(i);
	    if (bounds != null) {
		int bottom = bounds.y + bounds.height;

		if (highestBottom < 0 || bottom < highestBottom) {
		    highestBottom = bottom;
		}
	    }
	}

	return highestBottom < 0 ? 0 : highestBottom;
    }

    private int getTabsWidth(JTabbedPane tabs) {
	int width = 0;

	for (int i = 0, n = tabs.getTabCount(); i < n; i++) {
	    Rectangle bounds = tabs.getBoundsAt(i);
	    if (bounds != null) {
		width = Math.max(width, bounds.x + bounds.width);
	    }
	}

	return width;
    }
}
