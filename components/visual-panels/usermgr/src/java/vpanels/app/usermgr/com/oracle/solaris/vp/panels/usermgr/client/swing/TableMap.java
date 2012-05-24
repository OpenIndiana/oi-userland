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
 * Copyright (c) 1998, 2012, Oracle and/or its affiliates. All rights reserved.
 */


package com.oracle.solaris.vp.panels.usermgr.client.swing;

import javax.swing.table.*;
import javax.swing.event.TableModelListener;
import javax.swing.event.TableModelEvent;

/**
 * SMC code adapted for Visual Panels
 *
 * In a chain of data manipulators some behaviour is common. TableMap
 * provides most of this behavour and can be subclassed by filters
 * that only need to override a handful of specific methods. TableMap
 * implements TableModel by routing all requests to its model, and
 * TableModelListener by routing all events to its listeners. Inserting
 * a TableMap which has not been subclassed into a chain of table filters
 * should have no effect.
 *
 * (This code taken from the Swing table examples.)
 *
 */
public class TableMap extends AbstractTableModel implements TableModelListener {

	protected TableModel model;

	public TableModel  getModel() {
		return model;
	}

	public void  setModel(TableModel model) {
		this.model = model;
		model.addTableModelListener(this);
	}

	// By default, Implement TableModel by forwarding all messages
	// to the model.

	public Object getValueAt(int aRow, int aColumn) {
		return model.getValueAt(aRow, aColumn);
	}

	public void setValueAt(Object aValue, int aRow, int aColumn) {
		model.setValueAt(aValue, aRow, aColumn);
	}

	public int getRowCount() {
		return (model == null) ? 0 : model.getRowCount();
	}

	public int getColumnCount() {
		return (model == null) ? 0 : model.getColumnCount();
	}

	public String getColumnName(int aColumn) {
		return model.getColumnName(aColumn);
	}

	public Class getColumnClass(int aColumn) {
		return model.getColumnClass(aColumn);
	}

	public boolean isCellEditable(int row, int column) {
		return model.isCellEditable(row, column);
	}


	//
	// Implementation of the TableModelListener interface,
	//

	// By default forward all events to all the listeners.
	public void tableChanged(TableModelEvent e) {
		fireTableChanged(e);
	}

}
