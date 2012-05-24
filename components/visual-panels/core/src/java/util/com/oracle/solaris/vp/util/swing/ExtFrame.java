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
import java.awt.event.*;
import javax.swing.JFrame;

/**
 * The {@code ExtFrame} class is a {@code JFrame} with the following extras:
 *
 * <h4>Initial placement by platform</h4>
 *
 * Correcting the unfortunate default behavior of {@code JFrame}, the {@code
 * ExtFrame}'s initial position is determined by the platform, rather than by
 * Java.
 *
 * <h4>No focus stealing</h4>
 *
 * Correcting the unfortunate default behavior of {@code JFrame}, the {@code
 * ExtFrame} does NOT automatically request focus when initially mapped.
 *
 * <h4>Auto-resizability</h4>
 *
 * The {@code ExtFrame} utilizes an {@link ExtRootPane} that can be configured
 * to {@link #setAutoResizeEnabled automatically resize} this window whenever
 * its content changes.  This ability is disabled by default.
 *
 * <h4>Auto-set minimum size</h4>
 *
 * The {@code ExtFrame} utilizes an {@link ExtRootPane} that can be configured
 * to automatically set this window's minimum size to its preferred sized
 * whenever its content changes.  This ability is disabled by default.
 *
 * <h4>Initial Component focus</h4>
 *
 * A specific {@code Component} can be {@link #setInitialFocus set} to receive
 * focus the first time this {@code ExtFrame} gains focus.
 */
@SuppressWarnings({"serial"})
public class ExtFrame extends JFrame {
    //
    // Instance data
    //

    private Component initFocus;

    //
    // Constructors
    //

    public ExtFrame() {
	init();
    }

    public ExtFrame(GraphicsConfiguration gc) {
	super(gc);
	init();
    }

    public ExtFrame(String title) {
	super(title);
	init();
    }

    public ExtFrame(String title, GraphicsConfiguration gc) {
	super(title, gc);
	init();
    }

    //
    // JFrame methods
    //

    @Override
    protected ExtRootPane createRootPane() {
	ExtRootPane root = new ExtRootPane();
	root.setAutoMinSizeEnabled(false);
	root.setAutoResizeEnabled(false);
	return root;
    }

    @Override
    public ExtRootPane getRootPane() {
	return (ExtRootPane)super.getRootPane();
    }

    //
    // ExtFrame methods
    //

    /**
     * Gets the {@code Component} to get focus the first time this {@code
     * ExtFrame} gains focus.
     *
     * @return	    a {@code Component}, or {@code null} to use the default
     */
    public Component getInitialFocus() {
	return initFocus;
    }

    /**
     * Gets whether this {@code JFrame} automatically resizes whenever its
     * preferred size changes.
     */
    public boolean isAutoResizeEnabled() {
	return getRootPane().isAutoResizeEnabled();
    }

    /**
     * Sets whether this {@code JFrame} automatically resizes whenever its
     * preferred size changes.	If {@code enabled} is {@code true},
     * {@code setResizable(false)} is called to prevent manual resizing.
     */
    public void setAutoResizeEnabled(boolean enabled) {
	getRootPane().setAutoResizeEnabled(enabled);
	if (enabled) {
	    setResizable(false);
	}
    }

    /**
     * Sets the {@code Component} to get focus the first time this {@code
     * ExtFrame} gains focus.
     *
     * @param	    initFocus
     *		    a {@code Component}, or {@code null} to use the default
     */
    public void setInitialFocus(Component initFocus) {
	this.initFocus = initFocus;
    }

    //
    // Private methods
    //

    private void init() {
	setLocationByPlatform(true);

	// Uncomment for Java 1.7
//	setAutoRequestFocus(false);

	WindowFocusListener initFocusListener =
	    new WindowAdapter() {
		@Override
		public void windowGainedFocus(WindowEvent e) {
		    if (initFocus != null) {
			initFocus.requestFocusInWindow();
		    }
		    removeWindowFocusListener(this);
		}
	    };
	addWindowFocusListener(initFocusListener);
    }
}
