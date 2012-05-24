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

package com.oracle.solaris.vp.panel.swing.control;

import java.awt.*;
import javax.swing.*;
import javax.swing.border.Border;
import com.oracle.solaris.vp.panel.common.control.Navigator;
import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;
import com.oracle.solaris.vp.util.swing.*;

public class DialogControl<P extends PanelDescriptor>
    extends WindowControl<P, JDialog> {

    //
    // Static data
    //

    public static final String ID = "dialog";

    //
    // Constructors
    //

    public DialogControl(String id, String name, P descriptor) {
	super(id, name, descriptor);
    }

    public DialogControl(P descriptor) {
	this(ID, null, descriptor);
    }

    //
    // SwingControl methods
    //

    @Override
    protected JDialog createComponent() {
	// Modality can be changed by subclasses before dialog is shown
	JDialog dialog = new JDialog(getOwner(),
	    Dialog.ModalityType.DOCUMENT_MODAL);

	ReplacingStackPanel stack = new ReplacingStackPanel();
	stack.setBorder(getDefaultBorder());

	Container cont = dialog.getContentPane();
	cont.setLayout(new BorderLayout());
	cont.add(stack, BorderLayout.CENTER);

	dialog.setTitle(getName());
	dialog.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
	dialog.pack();

	setComponentStack(stack);
	return dialog;
    }

    //
    // WindowControl methods
    //

    @Override
    protected String getWindowTitle() {
	return getComponent().getTitle();
    }

    @Override
    protected void setVisible() {
	JDialog dialog = getComponent();
	Window owner = dialog.getOwner();
	if (owner != null) {
	    dialog.setLocationRelativeTo(owner);
	}

	super.setVisible();
    }

    @Override
    protected void setWindowTitle(String title) {
	getComponent().setTitle(title);
    }

    //
    // DialogControl methods
    //

    /**
     * Gets the owner of the this {@code DialogControl}'s {@code JDialog}.  This
     * default implementation searches backwards through the navigation stack
     * for a {@link SwingControl} with a {@code Component} in a mapped {@code
     * Window}.
     *
     * @return	    a {@code Window}, or {@code null} if the {@code JDialog} has
     *		    no owner
     */
    public Window getOwner() {
	Window owner = null;
	Navigator navigator = getNavigator();
	if (navigator != null) {
	    owner = SwingNavigator.getLastWindow(navigator);
	}
	return owner;
    }

    /**
     * Returns a {@code Border} to use on the outermost {@code Containter}
     * within the {@code Dialog}, or {@code null} to use no {@code Border}.
     * </p>
     * This default implementation returns {@link GUIUtil#getEmptyBorder}.
     */
    protected Border getDefaultBorder() {
	return GUIUtil.getEmptyBorder();
    }
}
