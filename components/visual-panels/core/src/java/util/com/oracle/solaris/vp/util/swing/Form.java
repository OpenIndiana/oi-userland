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

import java.awt.*;
import javax.swing.JPanel;
import com.oracle.solaris.vp.util.swing.layout.*;

public class Form {
    //
    // Instance data
    //

    private Container container;
    private JPanel curRow;

    //
    // Constructors
    //

    public Form(Container container, VerticalAnchor vAnchor) {
	this.container = container;
	container.setLayout(new ColumnLayout(vAnchor));
    };

    //
    // Form methods
    //

    public JPanel addTable(
	int cols, int hGap, int vGap, HorizontalAnchor hAnchor,
	ColumnLayoutConstraint c) {

	TableLayout layout = new TableLayout(1, cols, hGap, vGap);
	layout.setHorizontalAnchor(hAnchor);

	curRow = new JPanel(layout);
	curRow.setOpaque(false);
	container.add(curRow, c);

	return curRow;
    }

    public JPanel addRow(HorizontalAnchor hAnchor, ColumnLayoutConstraint c) {
	RowLayout layout = new RowLayout(hAnchor);
	curRow = new JPanel(layout);
	curRow.setOpaque(false);
	container.add(curRow, c);

	return curRow;
    }

    public void add(Component c) {
	curRow.add(c);
    }

    public void add(Component c, Object constraint) {
	curRow.add(c, constraint);
    }

    public Container getContainer() {
	return container;
    }
}
