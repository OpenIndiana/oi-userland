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
import javax.swing.event.DocumentEvent;
import javax.swing.text.*;

/**
 * The {@code AutoHideTextArea} is a {@code JTextArea} whose visibility is
 * automatically set to {@code false} when its text is {@code null} or empty,
 * {@code true} otherwise.
 */
@SuppressWarnings({"serial"})
public class AutoHideTextArea extends JTextArea {
    public static class AutoHideListener extends DocumentAdapter {
	//
	// Instance data
	//

	private JTextComponent comp;

	//
	// DocumentAdapter methods
	//

	@Override
	public void docUpdate(DocumentEvent event) {
	    setVisible();
	}

	//
	// AutoHideListener methods
	//

	public void deinit() {
	    comp.getDocument().removeDocumentListener(this);
	    this.comp = null;
	}

	public void init(JTextComponent comp) {
	    this.comp = comp;
	    comp.getDocument().addDocumentListener(this);
	    setVisible();
	}

	//
	// Private methods
	//

	/**
	 * Sets the visibility of the given {@code JTextComponent} based on
	 * whether it has a non-{@code null}/empty text.
	 */
	private void setVisible() {
	    String text = comp.getText();
	    comp.setVisible(text != null && !text.isEmpty());
	}
    }

    //
    // Static data
    //

    private static final AutoHideListener LISTENER = new AutoHideListener();

    //
    // Constructors
    //

    public AutoHideTextArea() {
	init();
    }

    public AutoHideTextArea(Document doc) {
	super(doc);
	init();
    }

    public AutoHideTextArea(Document doc, String text, int rows, int columns) {
	super(doc, text, rows, columns);
	init();
    }

    public AutoHideTextArea(int rows, int columns) {
	super(rows, columns);
	init();
    }

    public AutoHideTextArea(String text) {
	super(text);
	init();
    }

    public AutoHideTextArea(String text, int rows, int columns)  {
	super(text, rows, columns);
	init();
    }

    //
    // Private methods
    //

    private void init() {
	autoHide(this);
    }

    //
    // Static methods
    //

    /**
     * Add an {@link AutoHideListener} to the given {@code JTextComponent} to
     * automatically set its visibility whenever its text or icon properties
     * change.
     *
     * @return	    the added {@link AutoHideListener}
     */
    public static AutoHideListener autoHide(JTextComponent comp) {
	LISTENER.init(comp);
	return LISTENER;
    }
}
