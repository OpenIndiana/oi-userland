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

package com.oracle.solaris.vp.util.swing.propinfo;

import java.awt.Component;
import javax.swing.JTable;
import javax.swing.table.*;
import com.oracle.solaris.vp.util.common.propinfo.ReflectionPropInfo;
import com.oracle.solaris.vp.util.misc.DataSizeUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class SizePropInfo<M> extends ReflectionPropInfo<M, Long>
    implements SwingPropInfo<M, Long> {

    //
    // Static data
    //

    /**
     * Available instance to mitigate object creation
     */
    public static final SizePropInfo instance =
	new SizePropInfo();

    @SuppressWarnings({"serial"})
    private static final TableCellRenderer renderer =
	new DefaultTableCellRenderer() {
	    @Override
	    public Component getTableCellRendererComponent(
		JTable table, Object value, boolean isSelected,
		boolean hasFocus, int row, int column) {

		if (value instanceof Long) {
		    long size = (Long)value;

		    value = DataSizeUtil.getHumanReadableDataSize(
			size, 2, false, null, null, true, true);
		}

		return super.getTableCellRendererComponent(
		    table, value, isSelected, hasFocus, row, column);
	    }
	};

    //
    // Constructors
    //

    public SizePropInfo() {
	super(Finder.getString("property.size.label"),
	    Finder.getString("property.size.description"), true, false, "size");
    }

    //
    // SwingPropInfo methods
    //

    @Override
    public TableCellEditor getTableCellEditor() {
	return null;
    }

    @Override
    public TableCellRenderer getTableCellRenderer() {
	return renderer;
    }
}
