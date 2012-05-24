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
import javax.swing.JDialog;

/**
 * The {@code ExtDialog} class is a {@code JDialog} with the following extras:
 *
 * <h4>Auto-resizability</h4>
 *
 * The {@code ExtDialog} utilizes an {@link ExtRootPane} that can be configured
 * to {@link #setAutoResizeEnabled automatically resize} this window whenever
 * its content changes.  This ability is disabled by default.
 *
 * <h4>Auto-set minimum size</h4>
 *
 * The {@code ExtDialog} utilizes an {@link ExtRootPane} that can be configured
 * to automatically set this window's minimum size to its preferred sized
 * whenever its content changes.  This ability is disabled by default.
 *
 * <h4>Initial Component focus</h4>
 *
 * A specific {@code Component} can be {@link #setInitialFocus set} to receive
 * focus the first time this {@code ExtDialog} gains focus.
 */
@SuppressWarnings({"serial"})
public class ExtDialog extends JDialog {
    //
    // Instance data
    //

    private Component initFocus;

    //
    // Constructors
    //

    public ExtDialog() {
	init();
    }

    public ExtDialog(Dialog owner) {
	super(owner);
	init();
    }

    public ExtDialog(Dialog owner, boolean modal) {
	super(owner, modal);
	init();
    }

    public ExtDialog(Dialog owner, String title) {
	super(owner, title);
	init();
    }

    public ExtDialog(Dialog owner, String title, boolean modal) {
	super(owner, title, modal);
	init();
    }

    public ExtDialog(Dialog owner, String title, boolean modal,
	GraphicsConfiguration gc) {

	super(owner, title, modal, gc);
	init();
    }

    public ExtDialog(Frame owner) {
	super(owner);
	init();
    }

    public ExtDialog(Frame owner, boolean modal) {
	super(owner, modal);
	init();
    }

    public ExtDialog(Frame owner, String title) {
	super(owner, title);
	init();
    }

    public ExtDialog(Frame owner, String title, boolean modal) {
	super(owner, title, modal);
	init();
    }

    public ExtDialog(Frame owner, String title, boolean modal,
	GraphicsConfiguration gc) {

	super(owner, title, modal, gc);
	init();
    }

    public ExtDialog(Window owner) {
	super(owner);
	init();
    }

    public ExtDialog(Window owner, Dialog.ModalityType modalityType) {
	super(owner, modalityType);
	init();
    }

    public ExtDialog(Window owner, String title) {
	super(owner, title);
	init();
    }

    public ExtDialog(Window owner, String title,
	Dialog.ModalityType modalityType) {

	super(owner, title, modalityType);
	init();
    }

    public ExtDialog(Window owner, String title,
	Dialog.ModalityType modalityType, GraphicsConfiguration gc) {

	super(owner, title, modalityType, gc);
	init();
    }

    //
    // JDialog methods
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
    // ExtDialog methods
    //

    /**
     * Gets the {@code Component} to get focus the first time this {@code
     * ExtDialog} gains focus.
     *
     * @return	    a {@code Component}, or {@code null} to use the default
     */
    public Component getInitialFocus() {
	return initFocus;
    }

    /**
     * Gets whether this {@code JDialog} automatically resizes whenever its
     * preferred size changes.
     */
    public boolean isAutoResizeEnabled() {
	return getRootPane().isAutoResizeEnabled();
    }

    /**
     * Sets whether this {@code JDialog} automatically resizes whenever its
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
     * ExtDialog} gains focus.
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
