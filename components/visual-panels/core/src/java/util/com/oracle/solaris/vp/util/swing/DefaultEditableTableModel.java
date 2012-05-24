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

import java.util.Vector;
import javax.swing.table.DefaultTableModel;

@SuppressWarnings({"serial"})
public class DefaultEditableTableModel extends DefaultTableModel
    implements EditableTableModel {

    //
    // Constructors
    //

    public DefaultEditableTableModel() {
	this(new String[0]);
    }

    public DefaultEditableTableModel(Object[] values, String columnName) {
	addColumn(columnName);
	for (int i = 0; i < values.length; i++) {
	    addRow(new Object[] {values[0]});
	}
    }

    public DefaultEditableTableModel(Object[] values) {
	this(values, "");
    }

    public DefaultEditableTableModel(int rowCount, int columnCount) {
	super(rowCount, columnCount);
    }

    public DefaultEditableTableModel(Object[][] data, Object[] columnNames) {
	super(data, columnNames);
    }

    public DefaultEditableTableModel(Object[] columnNames, int rowCount) {
	super(columnNames, rowCount);
    }

    public DefaultEditableTableModel(Vector columnNames, int rowCount) {
	super(columnNames, rowCount);
    }

    public DefaultEditableTableModel(Vector data, Vector columnNames) {
	super(data, columnNames);
    }

    //
    // TableModel methods
    //

    @Override
    public Class<?> getColumnClass(int columnIndex) {
	try {
	    return getValueAt(0, columnIndex).getClass();
	}

	// Most likely NullPointerException or IndexOutOfBoundsException
	catch (Throwable e) {
	    return String.class;
	}
    }

    //
    // EditableTableModel methods
    //

    @Override
    public boolean attemptAddRow(Object[] rowData) {
	if (!canAddRow(rowData)) {
	    return false;
	}

	addRow(rowData);
	return true;
    }

    @Override
    public boolean attemptInsertRow(int row, Object[] rowData) {
	if (!canAddRow(rowData)) {
	    return false;
	}

	insertRow(row, rowData);
	return true;
    }

    /**
     * Default implementation that returns {@code true} iff {@code rowData} is
     * non-{@code null}.
     */
    @Override
    public boolean canAddRow(Object[] rowData) {
	return rowData != null;
    }

    /**
     * Default implementation that returns 0;
     */
    @Override
    public int getAutoEditedColumn() {
	return 0;
    }

    @Override
    public Object[] getTemplateRow() {
	Object[] row = new Object[getColumnCount()];
	for (int col = 0; col < row.length; col++) {
	    try {
		row[col] = getColumnClass(col).newInstance();
	    } catch (Throwable e) {
		row[col] = null;
	    }
	}
	return row;
    }
}
