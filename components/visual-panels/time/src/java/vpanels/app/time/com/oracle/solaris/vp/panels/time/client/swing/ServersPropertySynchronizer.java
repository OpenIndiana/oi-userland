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

package com.oracle.solaris.vp.panels.time.client.swing;

import javax.swing.event.*;
import com.oracle.solaris.vp.panels.time.*;
import com.oracle.solaris.vp.util.misc.property.*;

/**
 * The {@code ServersPropertySynchronizer} class synchronizes a {@link
 * MutableProperty} with an {@code ServersModel} so that changes in
 * one will automatically be reflected in the other.
 */
public class ServersPropertySynchronizer
    extends PropertySynchronizer<ServerInfo[], ServersModel> {

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

    public ServersPropertySynchronizer(MutableProperty<ServerInfo[]> property,
	ServersModel model, boolean initFromProp) {

	super(property, model, initFromProp);
	model.addTableModelListener(listener);
    }

    /**
     * Constructs a {@code ServersPropertySynchronizer} with initial
     * synchronization from the property to the {@code ServersModel}.
     */
    public ServersPropertySynchronizer(MutableProperty<ServerInfo[]> property,
	ServersModel model) {

	this(property, model, true);
    }

    //
    // PropertySynchronizer methods
    //

    @Override
    public void desynchronize() {
	super.desynchronize();
	getObject().removeTableModelListener(listener);
    }

    @Override
    public ServerInfo[] getValue() {
	ServersModel model = getObject();
	int n = model.getRowCount();
	ServerInfo[] value = new ServerInfo[n];

	for (int row = 0; row < n; row++) {
	    String server = (String)model.getValueAt(row, 0);
	    Boolean enabled = (Boolean)model.getValueAt(row, 1);
	    value[row] = new ServerInfoImpl(server, enabled);
	}

	return value;
    }

    @Override
    public void setValue(ServerInfo[] value) {
	ServersModel model = getObject();
	int n = value == null ? 0 : value.length;

	for (int row = 0; row < n; row++) {
	    ServerInfo entry = value[row];
	    String server = entry.getServer();
	    Boolean enabled = entry.isEnabled();

	    boolean equal = true;
	    try {
		if (!enabled.equals(model.getValueAt(
		    row, ServersModel.POSITION_ENABLED)) ||
		    !server.equals(model.getValueAt(
		    row, ServersModel.POSITION_SERVER))) {

		    equal = false;
		    model.removeRow(row);
		}

	    // No such row
	    } catch (IndexOutOfBoundsException e) {
		equal = false;
	    }

	    if (!equal) {
		model.insertRow(row, new Object[] {server, enabled});
	    }
	}

	// Trime rows from model, if necessary
	model.setRowCount(n);
    }
}
