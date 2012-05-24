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

package com.oracle.solaris.vp.util.swing;

import javax.swing.JTextArea;
import javax.swing.text.Document;

/**
 * The {@code FlowTextArea} is a non-opaque, uneditable {@code JTextArea} that
 * displays multi-line text, wrapping words at whitespace.
 */
@SuppressWarnings({"serial"})
public class FlowTextArea extends JTextArea {
    //
    // Constructors
    //

    public FlowTextArea() {
	init();
    }

    public FlowTextArea(Document doc) {
	super(doc);
	init();
    }

    public FlowTextArea(Document doc, String text, int rows, int columns) {
	super(doc, text, rows, columns);
	init();
    }

    public FlowTextArea(int rows, int columns) {
	super(rows, columns);
	init();
    }

    public FlowTextArea(String text) {
	super(text);
	init();
    }

    public FlowTextArea(String text, int rows, int columns) {
	super(text, rows, columns);
	init();
    }

    //
    // Private methods
    //

    private void init() {
	setOpaque(false);
	setEditable(false);
	setLineWrap(true);
	setWrapStyleWord(true);
    }
}
