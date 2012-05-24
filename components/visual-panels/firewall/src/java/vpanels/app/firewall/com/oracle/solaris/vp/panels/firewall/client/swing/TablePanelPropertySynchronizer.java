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

import java.util.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.*;

/**
 * The {@code TablePanelPropertySynchronizer} class synchronizes a
 * {@link MutableProperty} with a {@code TablePanel} so that changes in
 * one will automatically be reflected in the other.
 */
public class TablePanelPropertySynchronizer<T>
    extends PropertySynchronizer<List<T>, TablePanel> {

    //
    // Instance data
    //

    private TableModelListener listener =
	new TableModelListener() {
	    @Override
	    public void tableChanged(TableModelEvent e) {
		objectChanged();
	    }
	};

    //
    // Constructors
    //

    public TablePanelPropertySynchronizer(
	MutableProperty<List<T>> property, TablePanel panel,
	boolean initFromProp) {

	super(property, panel, initFromProp);
	panel.getTable().getModel().addTableModelListener(listener);
    }

    /**
     * Constructs a {@code EditableTablePanelPropertySynchronizer} with initial
     * synchronization from the property to the {@link EditableTablePanel}.
     */
    public TablePanelPropertySynchronizer(
	MutableProperty<List<T>> property, TablePanel panel) {

	this(property, panel, true);
    }

    //
    // PropertySynchronizer methods
    //

    @Override
    public void desynchronize() {
	super.desynchronize();
	getObject().getTable().getModel().removeTableModelListener(listener);
    }

    @Override
    public List<T> getValue() {
	OpenPortsTableModel model =
	    (OpenPortsTableModel)getObject().getTable().getModel();

	int nRows = model.getRowCount();
	List<T> values = new ArrayList<T>(nRows);

	for (int row = 0; row < nRows; row++) {
	    @SuppressWarnings({"unchecked"})
	    T value = (T)model.getValueAt(row);
	    values.add(value);
	}

	return values;
    }

    @Override
    public void setValue(List<T> values) {
	OpenPortsTableModel model =
	    (OpenPortsTableModel)getObject().getTable().getModel();

	if (values == null) {
	    values = Collections.emptyList();
	}

	int nVals = values.size();
	int nRows = model.getRowCount();

	int row = 0;
	for (Object value : values) {
	    if (row >= nRows) {
		if (model.attemptAddRow(value)) {
		    nRows++;
		    row++;
		}
	    } else {
		model.setValueAt(value, row++);
	    }
	}

	if (nRows > nVals) {
	    for (row = nRows - 1; row >= nVals; row--) {
		model.removeRow(row);
	    }
	}
    }
}
