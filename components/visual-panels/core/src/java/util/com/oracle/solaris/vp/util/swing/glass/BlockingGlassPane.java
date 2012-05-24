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

import java.awt.*;
import java.awt.event.*;

@SuppressWarnings({"serial"})
public class BlockingGlassPane extends SimpleGlassPane {
    //
    // Static data
    //

    public static final KeyListener LISTENER_CONSUME_KEY =
	new KeyAdapter() {
	    @Override
	    public void keyPressed(KeyEvent e) {
		e.consume();
	    }
	};

    public static final MouseListener LISTENER_CONSUME_MOUSE =
	new MouseAdapter() {
	    @Override
	    public void mousePressed(MouseEvent e) {
		e.consume();
	    }
	};

    //
    // Instance data
    //

    private Component prevFocusComp;
    private boolean restoreFocus = true;

    //
    // Constructors
    //

    public BlockingGlassPane() {
	prepareBlockingGlassPane(this);
	setFocusCycleRoot(true);
    }


    /**
     * Create an instance of this object.
     *
     * @param restoreFocus A value of true indicates component focus should be
     * restored when invoking {@link #componentHidden}.
     */
    public BlockingGlassPane(boolean restoreFocus) {
	this();
	this.restoreFocus = restoreFocus;
    }

    //
    // SimpleGlassPane methods
    //

    @Override
    public void componentHidden() {
	super.componentHidden();
	Component comp = prevFocusComp;
	if (comp != null) {
	    comp.requestFocusInWindow();
	}
    }

    @Override
    public void componentShown() {
	super.componentShown();
	if (restoreFocus) {
	    prevFocusComp = KeyboardFocusManager.
		getCurrentKeyboardFocusManager().getFocusOwner();
	}
	requestFocusInWindow();
    }

    //
    // Static methods
    //

    public static void addConsumeEventListeners(Component c) {
	// Make sure listeners are only added once
	removeConsumeEventListeners(c);

	c.addKeyListener(LISTENER_CONSUME_KEY);
	c.addMouseListener(LISTENER_CONSUME_MOUSE);
    }

    public static void prepareBlockingGlassPane(Component glassPane) {
	addConsumeEventListeners(glassPane);
	glassPane.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
    }

    public static void removeConsumeEventListeners(Component c) {
	c.removeKeyListener(LISTENER_CONSUME_KEY);
	c.removeMouseListener(LISTENER_CONSUME_MOUSE);
    }
}
