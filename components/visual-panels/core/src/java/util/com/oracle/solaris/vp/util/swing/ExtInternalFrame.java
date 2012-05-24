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

import java.awt.*;
import java.awt.event.MouseMotionListener;
import javax.swing.*;
import javax.swing.plaf.basic.BasicInternalFrameUI;

/**
 * The {@code ExtInternalFrame} class is a {@code JInternalFrame} with the
 * following extras:
 * <ul>
 *   <li>
 *	the ability to {@link #setValidateRoot resize with its content}
 *   </li>
 *   <li>
 *	the ability to {@link #disableMove disable user movement} of the frame
 *   </li>
 * </ul>
 */
@SuppressWarnings({"serial"})
public class ExtInternalFrame extends JInternalFrame {
    //
    // Instance data
    //

    // Default behavior
    private boolean validateRoot = true;

    //
    // Constructors
    //

    public ExtInternalFrame() {
	init();
    }

    public ExtInternalFrame(String title) {
	super(title);
	init();
    }

    public ExtInternalFrame(String title, boolean resizable) {
	super(title, resizable);
	init();
    }

    public ExtInternalFrame(String title, boolean resizable,
	boolean closable) {

	super(title, resizable, closable);
	init();
    }

    public ExtInternalFrame(String title, boolean resizable,
	boolean closable, boolean maximizable) {

	super(title, resizable, closable, maximizable);
	init();
    }

    public ExtInternalFrame(String title, boolean resizable,
	boolean closable, boolean maximizable, boolean iconifiable)  {

	super(title, resizable, closable, maximizable, iconifiable);
	init();
    }

    //
    // ExtInternalFrame methods
    //

    /**
     * Prevents the user from moving this {@code JInternalFrame}.
     */
    public void disableMove() {
	BasicInternalFrameUI ui = (BasicInternalFrameUI)getUI();
	Component north = ui.getNorthPane();
	// Yes, this is a hack, but JInternalFrame forces our hand here
	removeMouseMotionListeners(north);
    }

    /**
     * Sets whether this {@code JInternalFrame}'s {@code JRootPane} is a root of
     * the validation hierarchy.  Setting this to {@code true} (the default is
     * {@code false}) means that this {@code JInternalFrame}'s size can change
     * with its contents.
     */
    public void setValidateRoot(boolean validateRoot) {
	this.validateRoot = validateRoot;
    }

    //
    // Private methods
    //

    private void init() {
	setRootPane(new JRootPane() {
	    @Override
	    public boolean isValidateRoot() {
		return validateRoot;
	    }
	});
    }

    private void removeMouseMotionListeners(Component comp) {
	for (MouseMotionListener listener : comp.getMouseMotionListeners()) {
	    comp.removeMouseMotionListener(listener);
	}

	if (comp instanceof Container) {
	    for (Component child : ((Container)comp).getComponents()) {
		removeMouseMotionListeners(child);
	    }
	}
    }
}
