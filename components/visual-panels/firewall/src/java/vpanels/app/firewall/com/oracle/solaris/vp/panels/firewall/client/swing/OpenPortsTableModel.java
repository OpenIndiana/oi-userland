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

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.util.Vector;
import javax.swing.table.DefaultTableModel;

@SuppressWarnings({"serial"})
public class OpenPortsTableModel extends DefaultTableModel {

    private static final String TCP_PREFIX = "tcp:";
    private static final String UDP_PREFIX = "udp:";
    private static final String TCP_UDP_PREFIX = ":";

    //
    // Constructors
    //

    public OpenPortsTableModel() {
	this(new String[0]);
    }

    public OpenPortsTableModel(Object[] values, String[] columns) {
	for (String col : columns) {
	    addColumn(col);
	}

	for (Object v : values) {
	    String data[] = ((String) v).split("\\:");
	    addRow(data);
	}
    }

    public OpenPortsTableModel(Object[] values) {
	this(values, new String[] {"", "", ""});
    }

    //
    // TableModel methods
    //

    @Override
    public Class<?> getColumnClass(int columnIndex) {
	return (columnIndex <= 1 ? Boolean.class : String.class);
    }

    //
    // DefaultTableModel methods
    //

    @Override
    public boolean isCellEditable(int row, int column) {
	return false;
    }

    //
    // OpenPortsTableModel methods
    //

    public void setValueAt(Object aValue, int row) {
	Object vals[] = valueToArray(aValue);
	super.setValueAt(vals[0], row, 0);
	super.setValueAt(vals[1], row, 1);
	super.setValueAt(vals[2], row, 2);
    }

    //
    // Transform a {proto}:port tuple to a three columns array of data
    //
    public Object[] valueToArray(Object value) {
	int idx = ((String) value).indexOf(":");

	Object values[];
	if (idx == -1) {
	    //
	    // This is an error case
	    //
	    values = new Object[] { new Boolean("false"),
		new Boolean("false"), ((String) value)};
	} else if (idx == 0) {
	    values = new Object[] { new Boolean("true"),
		new Boolean("true"), ((String) value).substring(idx + 1)};
	} else {
	    if (((String)value).startsWith(TCP_PREFIX))
		values = new Object[] {new Boolean("true"),
		    new Boolean("false"), ((String) value).substring(idx + 1)};
	    else
		values = new Object[] {new Boolean("false"),
		    new Boolean("true"), ((String) value).substring(idx + 1)};
	}

	return values;
    }

    //
    // Inverse-transformation a three columns array of data to a
    // {proto}:port tuple
    //
    public Object getValueAt(int row) {
	Boolean tcp = ((Boolean) super.getValueAt(row, 0));
	Boolean udp = ((Boolean) super.getValueAt(row, 1));
	String port = ((String) super.getValueAt(row, 2));

	if (tcp == null || udp == null)
	    return null;

	// This is an error case
	if (tcp.booleanValue() == false && udp.booleanValue() == false)
	    return (port);

	if (tcp.booleanValue() == true && udp.booleanValue() == true)
	    return TCP_UDP_PREFIX.concat(port);

	return (tcp.booleanValue() == true ? TCP_PREFIX.concat(port) :
	    UDP_PREFIX.concat(port));
    }

    public boolean attemptAddRow(Object rowData) {
	Object vals[] = valueToArray(rowData);
	addRow(vals);
	return true;
    }

    public boolean attemptInsertRow(int row, Object rowData) {
	Object vals[] = valueToArray(rowData);
	insertRow(row, vals);
	return true;
    }

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
