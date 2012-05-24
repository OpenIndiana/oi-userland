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
import javax.swing.plaf.basic.*;

@SuppressWarnings({"serial"})
public class ExtScrollPane extends JScrollPane {
    //
    // Instance data
    //

    private int defaultUnitInc;

    //
    // Constructors
    //

    public ExtScrollPane() {
	init();
    }

    public ExtScrollPane(Component view) {
	super(view);
	init();
    }

    public ExtScrollPane(Component view, int vsbPolicy, int hsbPolicy) {
	super(view, vsbPolicy, hsbPolicy);
	init();
    }

    public ExtScrollPane(int vsbPolicy, int hsbPolicy) {
	super(vsbPolicy, hsbPolicy);
	init();
    }

    //
    // JComponent methods
    //

    /**
     * Sets the opacity of this {@code JScrollPane} and its {@code JViewport}.
     */
    @Override
    public void setOpaque(boolean opaque) {
	super.setOpaque(opaque);
	getViewport().setOpaque(opaque);
    }

    //
    // JScrollPane methods
    //

    @Override
    protected JViewport createViewport() {
        return new JViewport() {
	    @Override
	    public void setView(Component view) {
		Component oldView = getView();
		if (oldView != view) {
		    super.setView(view);
		    if (view != null) {
			setUnitIncrement();
		    }
		}
	    }
	};
    }

    //
    // ExtScrollPane methods
    //

    public void removeBorder() {
	removeBorder(this);
    }

    public int getDefaultUnitIncrement() {
	if (defaultUnitInc == 0) {
	    defaultUnitInc = GUIUtil.getScrollableUnitIncrement();
	}
	return defaultUnitInc;
    }

    public void setDefaultUnitIncrement(int defaultUnitInc) {
	if (this.defaultUnitInc != defaultUnitInc) {
	    this.defaultUnitInc = defaultUnitInc;
	    setUnitIncrement();
	}
    }

    //
    // Private methods
    //

    private void init() {
	setOpaque(false);
    }

    private void setUnitIncrement() {
	int defaultUnitInc = getDefaultUnitIncrement();
	int hInc = defaultUnitInc;
	JScrollBar hScroll = getHorizontalScrollBar();

	int vInc = defaultUnitInc;
	JScrollBar vScroll = getVerticalScrollBar();

	Component view = getViewport().getView();

	if (view instanceof Scrollable) {
	    Scrollable scrollable = (Scrollable)view;
	    Rectangle r = viewport.getViewRect();

	    hInc = scrollable.getScrollableUnitIncrement(
		r, hScroll.getOrientation(), 1);

	    vInc = scrollable.getScrollableUnitIncrement(
		r, hScroll.getOrientation(), 1);
	}

	getHorizontalScrollBar().setUnitIncrement(hInc);
	getVerticalScrollBar().setUnitIncrement(vInc);
    }

    //
    // Static methods
    //

    /**
     * Removes the border from the given {@code JScrollPane}.  Since some
     * UIs show a border under all circumstances (synth, for example), this is
     * more involved than setting the border to {@code null}.
     */
    public static void removeBorder(JScrollPane scroll) {
	scroll.setUI(new BasicScrollPaneUI());

	// Setting to null would result in a default border
	scroll.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 0));

	scroll.getViewport().setUI(new BasicViewportUI());
    }
}
