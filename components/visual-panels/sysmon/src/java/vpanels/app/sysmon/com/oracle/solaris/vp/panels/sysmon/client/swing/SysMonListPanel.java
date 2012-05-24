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

package com.oracle.solaris.vp.panels.sysmon.client.swing;

import java.awt.*;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.panel.swing.view.ManagedObjectCellRenderer;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;

public class SysMonListPanel extends SettingsPanel {
    //
    // Static data
    //

    private static final String TITLE = Finder.getString("list.title");

    //
    // Instance data
    //

    private ExtList list;

    //
    // Constructors
    //

    public SysMonListPanel(ListModel model) {
	getTitleLabel().setText(TITLE);

	list = new ExtList(model);
	list.setScrollableTracksViewportWidth(true);
	list.setVisibleRowCount(8);
	list.setVisibleRowCountStatic(false);
	list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

	SimpleCellRenderer renderer =
	    new ManagedObjectCellRenderer<ManagedObject>();
	renderer.configureFor(list);
	list.setCellRenderer(renderer);

	ExtScrollPane scroll = new ExtScrollPane(list);
	JViewport viewport = scroll.getViewport();
	viewport.setOpaque(true);
	viewport.setBackground(list.getBackground());

	Container contentPane = getContentPane();
	contentPane.setLayout(new BorderLayout());
	contentPane.add(scroll, BorderLayout.CENTER);
    }

    //
    // SysMonListPanel methods
    //

    public ExtList getList() {
	return list;
    }
}
