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

import javax.swing.event.*;

/**
 * A {@code ListDataListenerAdapter} is a {@code TableModelListener} that
 * converts incoming {@code TableModelEvent}s to {@code ListDataEvent}s and
 * passes them on to a given {@code ListDataListener}.
 */
@SuppressWarnings({"serial"})
public class ListDataListenerAdapter implements TableModelListener {
    //
    // Instance data
    //

    private ListDataListener listener;

    //
    // Constructors
    //

    public ListDataListenerAdapter(ListDataListener listener) {
	this.listener = listener;
    }

    //
    // TableModelListener methods
    //

    @Override
    public void tableChanged(TableModelEvent e) {
	Object source = e.getSource();
	int first = e.getFirstRow();
	int last = e.getLastRow();
	ListDataEvent listEvent;

	switch (e.getType()) {
	    case TableModelEvent.DELETE:
		listEvent = new ListDataEvent(
		    source, ListDataEvent.INTERVAL_REMOVED, first, last);
		listener.intervalRemoved(listEvent);
		break;

	    case TableModelEvent.INSERT:
		listEvent = new ListDataEvent(
		    source, ListDataEvent.INTERVAL_ADDED, first, last);
		listener.intervalAdded(listEvent);
		break;

	    default:
	    case TableModelEvent.UPDATE:
		listEvent = new ListDataEvent(
		    source, ListDataEvent.CONTENTS_CHANGED, first, last);
		listener.contentsChanged(listEvent);
		break;
	}
    }

    //
    // ListDataListenerAdapter methods
    //

    public ListDataListener getListener() {
	return listener;
    }
}
