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
import java.awt.event.*;
import javax.swing.*;
import com.oracle.solaris.vp.util.swing.HyperlinkLabel.UnderlinePolicy;

/**
 * The {@code LinkCollapsiblePane} class is a {@link HeaderedCollapsiblePane}
 * that provides an uninitialized {@link HyperlinkLabel} as a header.
 */
@SuppressWarnings({"serial"})
public class LinkCollapsiblePane extends HeaderedCollapsiblePane {
    //
    // Instance data
    //

    private HyperlinkLabel link;

    //
    // Constructors
    //

    public LinkCollapsiblePane(int gap) {
	super(gap);

	link = new HyperlinkLabel();
	link.setUnderlinePolicy(UnderlinePolicy.NEVER);

	link.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    setCollapsed(!getCollapsiblePane().isCollapsed());
		}
	    });

	getHeaderPane().add(link, BorderLayout.WEST);

	setCollapsed(true);
    }

    public LinkCollapsiblePane() {
	this(0);
    }

    //
    // HeaderedCollapsiblePane methods
    //

    @Override
    public void setCollapsed(boolean collapsed) {
	super.setCollapsed(collapsed);

	if (link != null) {
	    String text = getLinkText(collapsed);
	    if (text != null) {
		link.setText(text);
	    }

	    Icon icon = UIManager.getIcon(collapsed ?
		"Tree.collapsedIcon" : "Tree.expandedIcon");

	    link.setIcon(icon);
	}
    }

    //
    // LinkCollapsiblePane methods
    //

    public HyperlinkLabel getLink() {
	return link;
    }

    /**
     * Gets the text to place in the link, dependent on the state of the
     * {@link CollapsiblePane}.
     *
     * @return      the text to set in the {@link HyperlinkLabel}, or {@code
     *              null} to keep the existing text
     */
    public String getLinkText(boolean collapsed) {
	// Don't change link text by default
	return null;
    }
}
