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

import javax.swing.JToggleButton;
import javax.swing.JToggleButton.ToggleButtonModel;

/**
 * The {@code UneditableToggleButtonModel} allows a {@code JToggleButton} to be
 * uneditable (read-only), without looking disabled.
 */
@SuppressWarnings({"serial"})
public class UneditableToggleButtonModel extends ToggleButtonModel {
    //
    // Instance data
    //

    private boolean editable;

    //
    // UneditableToggleButtonModel methods
    //

    public boolean isEditable() {
	return editable;
    }

    public void setEditable(boolean editable) {
	this.editable = editable;
    }

    //
    // ButtonModel methods
    //

    /**
     * Calls the superclass implementation iff this {@code
     * UneditableToggleButtonModel} is editable.
     */
    @Override
    public void setSelected(boolean b) {
	if (editable) {
	    super.setSelected(b);
	}
    }

    /**
     * Forcibly changes the state of the toggle button.
     */
    public void setSelectedForced(boolean b) {
	super.setSelected(b);
    }
}
