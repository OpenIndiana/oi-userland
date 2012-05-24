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

package com.oracle.solaris.vp.util.swing;

import java.awt.Dimension;
import java.util.Vector;
import javax.swing.*;

@SuppressWarnings({"serial"})
public class ExtList extends JList {
    //
    // Instance data
    //

    private boolean fills = false;
    private boolean tracksWidth = true;
    private boolean visibleRowCountStatic = true;
    private int vWidth = -1;

    //
    // Constructors
    //

    public ExtList() {
    }

    public ExtList(ListModel dataModel) {
	super(dataModel);
    }

    public ExtList(Object[] listData) {
	super(listData);
    }

    public ExtList(Vector<?> listData) {
	super(listData);
    }

    //
    // Scrollable methods
    //

    /**
     * Partially override the hard-coded values returned by the superclass when
     * the model is empty, orientation is {@code VERTICAL}, and no fixed
     * width/height has been set.  In this case, a zero width {@code Dimension}
     * is returned.
     */
    @Override
    public Dimension getPreferredScrollableViewportSize() {
	Dimension d = super.getPreferredScrollableViewportSize();

	if (vWidth != -1) {
	    d.width = vWidth;
	} else if (getLayoutOrientation() == VERTICAL &&
	    getFixedCellWidth() <= 0 &&
	    getFixedCellHeight() <= 0 &&
	    getModel().getSize() == 0) {

	    d.width = 0;
	}

	return d;
    }

    @Override
    public boolean getScrollableTracksViewportHeight() {
	return fills && super.getScrollableTracksViewportHeight();
    }

    @Override
    public boolean getScrollableTracksViewportWidth() {
	return tracksWidth || super.getScrollableTracksViewportWidth();
    }

    //
    // JList methods
    //

    @Override
    public int getVisibleRowCount() {
	int vrc = super.getVisibleRowCount();
	if (vrc > 0 && !isVisibleRowCountStatic()) {
	    return Math.min(getModel().getSize(), vrc);
	}
	return vrc;
    }

    //
    // ExtList methods
    //

    /**
     * Gets whether or not this list is always made large enough to fill the
     * height of an enclosing viewport.  By default this property is {@code
     * false}.
     */
    public boolean getFillsViewportHeight() {
	return fills;
    }

    /**
     * Gets the preferred width of a viewport containing this list, or -1 if the
     * width should be calculated automatically.
     */
    public int getVisibleWidth() {
	return vWidth;
    }

    /**
     * Gets whether the visible row count, if set, should determine the height
     * of an enclosing viewport even if there are fewer rows in the data model.
     * The default value is {@code true}.
     */
    public boolean isVisibleRowCountStatic() {
	return visibleRowCountStatic;
    }

    /**
     * Sets whether or not this list is always made large enough to fill the
     * height of an enclosing viewport.  By default this property is {@code
     * false}.
     */
    public void setFillsViewportHeight(boolean fills) {
	this.fills = fills;
    }

    /**
     * Set whether to resize the list horizontally instead of scrolling, when in
     * a scroll pane.  By default this property is {@code true}.
     *
     * @param	    tracksWidth
     *		    {@code true} to resize, {@code false} otherwise
     */
    public void setScrollableTracksViewportWidth(boolean tracksWidth) {
	this.tracksWidth = tracksWidth;
    }

    /**
     * Sets the preferred width of a viewport containing this list, or -1 if the
     * width should be calculated automatically.
     */
    public void setVisibleWidth(int vWidth) {
	this.vWidth = vWidth;
    }

    /**
     * Sets whether the visible row count, if set, should determine the height
     * of an enclosing viewport even if there are fewer rows in the data model.
     * The default value is {@code true}.
     */
    public void setVisibleRowCountStatic(boolean visibleRowCountStatic) {
	this.visibleRowCountStatic = visibleRowCountStatic;
    }
}
