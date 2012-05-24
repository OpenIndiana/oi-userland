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
 * Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.awt.Component;
import javax.swing.*;
import javax.swing.table.*;
import com.oracle.solaris.vp.util.swing.InfoLabel;

@SuppressWarnings({"serial"})
public class PolicyEditPanel extends JPanel {

    //
    // Instance data
    //

    private InfoLabel info;
    private PolicyTablePanel applyList;
    private PolicyTablePanel exceptionList;

    //
    // Constructors
    //

    public PolicyEditPanel(String applyTitle) {
        applyList = new PolicyTablePanel(applyTitle);
    	add(applyList);
    	setOpaque(false);
    }

    public PolicyEditPanel(String applyTitle, String exceptionsTitle) {
	this(applyTitle);

	exceptionList = new PolicyTablePanel(exceptionsTitle);
	add(exceptionList);
    }

    //
    // PolicyEditPanel methods
    //

    public void adjustSize() {

	JTable table = applyList.getTable();
	TableColumnModel model = table.getColumnModel();
	TableColumn column = model.getColumn(0);

	// A datum of maximum width
	String value = "000.000.000.000/00   ";

	TableCellRenderer tableRenderer = column.getCellRenderer();
	if (tableRenderer == null) {
	    tableRenderer = new DefaultTableCellRenderer();
	}

	Component renderer = tableRenderer.getTableCellRendererComponent(
	    table, value, false, false, 0, 0);

	// Preferred width: datum + icon size + gap
	int width = renderer.getPreferredSize().width + 16 + 6;
	column.setPreferredWidth(width);

	if (exceptionList != null) {
	    exceptionList.getTable().getColumnModel().getColumn(0).
		setPreferredWidth(width);
	}
    }

    public PolicyTablePanel getApplyList() {
	return applyList;
    }

    public PolicyTablePanel getExceptionList() {
	return exceptionList;
    }

    public void setVisibleRowCount(int visRow) {
	applyList.getTable().setVisibleRowCount(visRow);

	if (exceptionList != null)
	    exceptionList.getTable().setVisibleRowCount(visRow);
    }

    public void setPanelDescriptor(FirewallPanelDescriptor descriptor) {
	applyList.setPanelDescriptor(descriptor);

	if (exceptionList != null)
	    exceptionList.setPanelDescriptor(descriptor);
    }
}
