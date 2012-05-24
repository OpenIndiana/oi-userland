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

import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.DefaultEditableTableModel;

public class ServersModel extends DefaultEditableTableModel {
    //
    // Static data
    //

    protected static final int POSITION_ENABLED = 1;
    protected static final int POSITION_SERVER = 0;

    private static final String NAME_ENABLED = Finder.getString(
	"ntp.table.enabled");

    private static final String NAME_SERVER = Finder.getString(
	"ntp.table.server");

    //
    // TableModel methods
    //

    @Override
    public Class<?> getColumnClass(int col) {
	switch (col) {
	    case POSITION_SERVER:
		return String.class;

	    case POSITION_ENABLED:
		return Boolean.class;
	}

	throw new IndexOutOfBoundsException();
    }

    @Override
    public int getColumnCount() {
        return 2;
    }

    @Override
    public String getColumnName(int col) {
	switch (col) {
	    case POSITION_SERVER:
		return NAME_SERVER;

	    case POSITION_ENABLED:
		return NAME_ENABLED;
	}

	throw new IndexOutOfBoundsException();
    }

    //
    // ServersModel methods
    //

    @Override
    public Object[] getTemplateRow() {
	return getTemplateRow("", Boolean.TRUE);
    }

    @Override
    public int getAutoEditedColumn() {
	return POSITION_SERVER;
    }

    //
    // ServersModel methods
    //

    public Object[] getTemplateRow(String server, boolean enabled) {
	return new Object[] {
	    server, enabled
	};
    }
}
