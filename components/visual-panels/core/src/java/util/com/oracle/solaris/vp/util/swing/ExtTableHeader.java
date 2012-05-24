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

import java.awt.Component;
import javax.swing.JTable;
import javax.swing.table.*;

/**
 * The {@code ExtTableHeader} class amends {@code JTableHeader} to provide more
 * complete visual rendering/behavior in a disabled state.
 */
public class ExtTableHeader extends JTableHeader {
    //
    // Constructors
    //

    public ExtTableHeader() {
	init();
    }

    public ExtTableHeader(TableColumnModel model) {
	super(model);
	init();
    }

    //
    // Component methods
    //

    /**
     * Overridden to disable column reordering when disabled.
     */
    @Override
    public void setEnabled(boolean enabled) {
	if (enabled != isEnabled()) {
	    super.setEnabled(enabled);
	    setReorderingAllowed(enabled);
	}
    }

    //
    // Private methods
    //

    private void init() {
	// Hack to make the cell renderer appear disabled when the header itself
	// is disabled
	final TableCellRenderer renderer = getDefaultRenderer();
	setDefaultRenderer(
	    new TableCellRenderer() {
		@Override
		public Component getTableCellRendererComponent(
		    JTable table, Object value, boolean isSelected,
		    boolean hasFocus, int row, int column) {

		    Component comp =
			renderer.getTableCellRendererComponent(table,
			value, isSelected, hasFocus, row, column);

		    comp.setEnabled(ExtTableHeader.this.isEnabled());

		    return comp;
		}
	    });
    }
}
