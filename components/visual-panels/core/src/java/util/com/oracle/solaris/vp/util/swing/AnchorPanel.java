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
import javax.swing.JPanel;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class AnchorPanel extends JPanel {
    //
    // Instance data
    //

    private SimpleHasAnchors constraint = new SimpleHasAnchors();

    //
    // Constructors
    //

    public AnchorPanel() {
	super(new TableLayout(1, 1));
	setOpaque(false);
    }

    public AnchorPanel(Component comp, HorizontalAnchor hAnchor,
	VerticalAnchor vAnchor) {

	this();
	setContent(comp, hAnchor, vAnchor);
    }

    //
    // AnchorPanel methods
    //

    public void setContent(Component comp, HorizontalAnchor hAnchor,
	VerticalAnchor vAnchor) {

	constraint.setHorizontalAnchor(hAnchor);
	constraint.setVerticalAnchor(vAnchor);

	removeAll();
	add(comp, constraint);
    }

    public void setContent(Component comp) {
	setContent(comp, HorizontalAnchor.FILL, VerticalAnchor.FILL);
    }
}
