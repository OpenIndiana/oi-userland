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

package com.oracle.solaris.vp.util.swing.time;

import javax.swing.event.*;
import com.oracle.solaris.vp.util.swing.event.ChangeListeners;

@SuppressWarnings({"serial"})
public class SimpleTimeSelectionModel implements TimeSelectionModel {
    //
    // Instance data
    //

    private int selectedField;
    private ChangeListeners listeners = new ChangeListeners();
    private ChangeEvent event = new ChangeEvent(this);

    //
    // Constructors
    //

    /**
     * Constructs a {@code SimpleTimeSelectionModel} with the given selected
     * {@code Calendar} field.
     *
     * @param	    selectedField
     *		    see {@link TimeSelectionModel#setSelectedField}
     */
    public SimpleTimeSelectionModel(int selectedField) {
	setSelectedField(selectedField);
    }

    /**
     * Constructs an unselected {@code SimpleTimeSelectionModel}.
     */
    public SimpleTimeSelectionModel() {
	this(-1);
    }

    //
    // TimeSelectionModel methods
    //

    @Override
    public void addChangeListener(ChangeListener listener) {
	listeners.add(listener);
    }

    @Override
    public int getSelectedField() {
	return selectedField;
    }

    @Override
    public void removeChangeListener(ChangeListener listener) {
	listeners.remove(listener);
    }

    @Override
    public void setSelectedField(int selectedField) {
	if (this.selectedField != selectedField) {
	    this.selectedField = selectedField;
	    fireStateChanged();
	}
    }

    //
    // SimpleTimeSelectionModel methods
    //

    protected void fireStateChanged() {
	listeners.stateChanged(event);
    }
}
