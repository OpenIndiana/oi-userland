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

import java.awt.event.*;
import javax.swing.*;
import com.oracle.solaris.vp.util.swing.event.ActionListeners;

@SuppressWarnings({"serial"})
public class AggregateAction extends AbstractAction {
    //
    // Instance data
    //

    private ActionListeners listeners = new ActionListeners();

    //
    // Constructors
    //

    public AggregateAction() {
    }

    public AggregateAction(String name) {
	super(name);
    }

    public AggregateAction(String name, Icon icon) {
	super(name, icon);
    }

    //
    // ActionListener methods
    //

    @Override
    public void actionPerformed(ActionEvent e) {
	listeners.actionPerformed(e);
    }

    //
    // AggregateAction methods
    //

    public void addActionListener(ActionListener listener) {
	listeners.add(listener);
    }

    public boolean removeActionListener(ActionListener listener) {
	return listeners.remove(listener);
    }
}
