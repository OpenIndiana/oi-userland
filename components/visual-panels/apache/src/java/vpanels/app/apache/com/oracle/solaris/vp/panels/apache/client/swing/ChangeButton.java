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

package com.oracle.solaris.vp.panels.apache.client.swing;

import javax.swing.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.panel.swing.view.ChangeIndicator;
import com.oracle.solaris.vp.util.misc.Changeable;

@SuppressWarnings({"serial"})
public class ChangeButton extends JButton implements ChangeListener {
    //
    // Constructors
    //

    public ChangeButton() {
	init();
    }

    public ChangeButton(Action a) {
	super(a);
	init();
    }

    public ChangeButton(Icon icon) {
	super(icon);
	init();
    }

    public ChangeButton(String text) {
	super(text);
	init();
    }

    public ChangeButton(String text, Icon icon) {
	super(text, icon);
	init();
    }

    //
    // ChangeListener methods
    //

    @Override
    public void stateChanged(ChangeEvent e) {
	Changeable source = (Changeable)e.getSource();
	setChanged(source.isChanged());
    }

    //
    // ChangeButton methods
    //

    public void setChanged(boolean changed) {
	setIcon(changed ? ChangeIndicator.ICON_CHANGED : null);
	setToolTipText(changed ? ChangeIndicator.TEXT : null);
    }

    //
    // Private methods
    //

    private void init() {
	setChanged(false);
    }
}
