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

import javax.swing.DefaultListSelectionModel;
import com.oracle.solaris.vp.util.swing.event.*;

/**
 * The {@code ExtListSelectionModel} class provides an event mechanism that
 * reports a higher level of detail about changes in the model than its
 * superclass.
 */
@SuppressWarnings({"serial"})
public class ExtListSelectionModel extends DefaultListSelectionModel {
    //
    // Instance data
    //

    private ExtListSelectionListeners listeners =
	new ExtListSelectionListeners();

    //
    // ListSelectionModel methods
    //

    @Override
    public void addSelectionInterval(int index0, int index1) {
	super.addSelectionInterval(index0, index1);

	ExtListSelectionEvent event = new ExtListSelectionEvent(
	    this, ExtListSelectionEvent.Type.ADD, index0, index1,
	    getValueIsAdjusting());

	fireExtListSelectionEvent(event);
    }

    @Override
    public void clearSelection() {
	super.clearSelection();

	ExtListSelectionEvent event = new ExtListSelectionEvent(
	    this, ExtListSelectionEvent.Type.CLEAR, -1, -1,
	    getValueIsAdjusting());

	fireExtListSelectionEvent(event);
    }

    @Override
    public void insertIndexInterval(int index, int length, boolean before) {
	try {
	    super.insertIndexInterval(index, length, before);
	} catch (IndexOutOfBoundsException e) {
	    clearSelection();
	}
    }

    @Override
    public void removeSelectionInterval(int index0, int index1) {
	super.removeSelectionInterval(index0, index1);

	ExtListSelectionEvent event = new ExtListSelectionEvent(
	    this, ExtListSelectionEvent.Type.REMOVE, index0, index1,
	    getValueIsAdjusting());

	fireExtListSelectionEvent(event);
    }

    @Override
    public void setSelectionInterval(int index0, int index1) {
	super.setSelectionInterval(index0, index1);

	ExtListSelectionEvent event = new ExtListSelectionEvent(
	    this, ExtListSelectionEvent.Type.SET, index0, index1,
	    getValueIsAdjusting());

	fireExtListSelectionEvent(event);
    }

    //
    // ExtListSelectionModel methods
    //

    public void addExtListSelectionListener(
	ExtListSelectionListener listener) {
	listeners.add(listener);
    }

    public void removeExtListSelectionListener(
	ExtListSelectionListener listener) {
	listeners.remove(listener);
    }

    public void fireExtListSelectionEvent(ExtListSelectionEvent e) {
	listeners.selectionChanged(e);
    }
}
