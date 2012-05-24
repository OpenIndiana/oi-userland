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

import java.awt.*;
import javax.swing.*;

@SuppressWarnings({"serial"})
public class UnidirectionalScrollPane extends ExtScrollPane {
    //
    // Inner classes/enums
    //

    public enum Orientation {
	HORIZONTAL, VERTICAL
    }

    protected static class ScrollablePanel extends JPanel
	implements Scrollable {

	//
	// Instance data
	//

	private Orientation orientation;
	private Component view;

	//
	// Constructors
	//

	public ScrollablePanel(Orientation orientation) {
	    this.orientation = orientation;
	    setLayout(new BorderLayout());
	    setOpaque(false);
	}

	public ScrollablePanel(Orientation orientation, Component view) {
	    this(orientation);
	    setView(view);
	}

	//
	// Scrollable methods
	//

	@Override
	public Dimension getPreferredScrollableViewportSize() {
	    return getPreferredSize();
	}

	@Override
	public int getScrollableBlockIncrement(Rectangle visibleRect,
	    int orientation, int direction) {
	    if (view instanceof Scrollable) {
		return ((Scrollable)view).getScrollableBlockIncrement(
		    visibleRect, orientation, direction);
	    }

	    if (orientation == SwingConstants.VERTICAL) {
		return visibleRect.height;
	    }

	    return visibleRect.width;
	}

	@Override
	public boolean getScrollableTracksViewportHeight() {
	    return orientation != Orientation.VERTICAL;
	}

	@Override
	public boolean getScrollableTracksViewportWidth() {
	    return orientation != Orientation.HORIZONTAL;
	}

	@Override
	public int getScrollableUnitIncrement(Rectangle visibleRect,
	    int orientation, int direction) {
	    if (view instanceof Scrollable) {
		return ((Scrollable)view).getScrollableUnitIncrement(
		    visibleRect, orientation, direction);
	    }
	    return GUIUtil.getScrollableUnitIncrement();
	}

	//
	// ScrollablePanel methods
	//

	public Component getView() {
	    return view;
	}

	public void setView(Component view) {
	    this.view = view;
	    add(view, BorderLayout.CENTER);
	}
    }

    //
    // Instance data
    //

    private Orientation orientation;
    private ScrollablePanel scrollablePanel;

    //
    // Constructors
    //

    public UnidirectionalScrollPane(Orientation orientation) {
	this.orientation = orientation;
	scrollablePanel = new ScrollablePanel(orientation);
    }

    public UnidirectionalScrollPane(Orientation orientation,
	Component view) {
	this(orientation);

	// Stretch the view when the viewport is larger
//	getViewport().setLayout(new SimpleViewportLayout(true));

	setViewportView(view);
    }

    //
    // JScollPane methods
    //

    @Override
    public void setViewportView(Component view) {
	scrollablePanel.setView(view);
	super.setViewportView(scrollablePanel);
    }
}
