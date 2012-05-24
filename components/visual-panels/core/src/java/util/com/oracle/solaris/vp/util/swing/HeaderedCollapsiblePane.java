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

import java.awt.BorderLayout;
import javax.swing.JPanel;

/**
 * The {@code HeaderedCollapsiblePane} class is {@code JPanel} that contains a
 * {@link #getHeaderPane header pane} above a {@code #getContentPane content
 * pane} within a {@link CollapsiblePane #getCollapsiblePane}
 */
@SuppressWarnings({"serial"})
public class HeaderedCollapsiblePane extends JPanel {
    //
    // Instance data
    //

    private CollapsiblePane cPane;
    private JPanel contentPane;
    private JPanel headerPane;

    //
    // Constructors
    //

    public HeaderedCollapsiblePane(int gap) {
	this.cPane = cPane;

	contentPane = new JPanel(new BorderLayout());
	contentPane.setOpaque(false);

	JPanel panel = new JPanel(new BorderLayout(gap, gap));
	panel.setOpaque(false);
	panel.add(new Spacer(), BorderLayout.NORTH);
	panel.add(contentPane, BorderLayout.CENTER);

	cPane = new CollapsiblePane(panel);
	cPane.setOpaque(false);

	setOpaque(false);
	setLayout(new BorderLayout());

	headerPane = new JPanel(new BorderLayout());
	headerPane.setOpaque(false);

	add(headerPane, BorderLayout.NORTH);
	add(cPane, BorderLayout.CENTER);

	setCollapsed(true);
    }

    public HeaderedCollapsiblePane() {
	this(0);
    }

    //
    // HeaderedCollapsiblePane methods
    //

    public CollapsiblePane getCollapsiblePane() {
	return cPane;
    }

    /**
     * Gets a content pane, initialized with a {@code BorderLayout}.
     */
    public JPanel getContentPane() {
	return contentPane;
    }

    /**
     * Gets a header pane, initialized with a {@code BorderLayout}.
     */
    public JPanel getHeaderPane() {
	return headerPane;
    }

    public void setCollapsed(boolean collapsed) {
	cPane.setCollapsed(collapsed);
    }
}
