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

package com.oracle.solaris.vp.panel.swing.view;

import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.DocumentEvent;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.predicate.Predicate;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

/**
 * The {@code SearchFilter} is a {@link CustomObjectsFilter} that filters based
 * on whether a user-specified string appears in the {@link ManagedObject}'s
 * name.
 */
public class SearchFilter<C extends ManagedObject>
    extends CustomObjectsFilter<C> {

    //
    // Static data
    //

    private static final String text = Finder.getString(
	"objects.header.filter.search.label");

    //
    // Instance data
    //

    private Predicate<C> predicate =
	new Predicate<C>() {
	    @Override
	    public boolean test(C o) {
		String text = field.getText();
		String name = o.getName();

		if (!caseCheckBox.isSelected()) {
		    text = text.toLowerCase();
		    name = name.toLowerCase();
		}

		return name.indexOf(text) != -1;
	    }
	};

    //
    // Instance data
    //

    private JTextField field;
    private JCheckBox caseCheckBox;
    private boolean updateImmediately;
    private String lastText;

    //
    // Constructors
    //

    /**
     * Constructs a {@code SearchFilter}.
     *
     * @param	    text
     *		    the text to display for this {@code SearchFilter}
     *
     * @param	    updateImmediately
     *		    whether to update the filter as the user types (may have a
     *		    performance cost for large data sets)
     */
    public SearchFilter(String text, boolean updateImmediately) {
	super(text, null);

	this.updateImmediately = updateImmediately;

	field = new JTextField(GUIUtil.getTextFieldWidth());
	field.getDocument().addDocumentListener(
	    new DocumentAdapter() {
		@Override
		public void docUpdate(DocumentEvent e) {
		    doApplyIfImmediate();
		}
	    });

	caseCheckBox = new JCheckBox(Finder.getString(
	    "objects.header.filter.search.matchcase"));

	caseCheckBox.addItemListener(
	    new ItemListener() {
		@Override
		public void itemStateChanged(ItemEvent e) {
		    doApplyIfImmediate();
		}
	    });

	JPanel panel = new JPanel(new RowLayout());
	panel.setOpaque(false);

	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.CENTER, GUIUtil.getHalfGap());

	panel.add(field, r);
	panel.add(caseCheckBox, r);

	setComponent(panel);
    }

    /**
     * Constructs a {@code SearchFilter} with a default text string.
     *
     * @param	    updateImmediately
     *		    see {@link #SearchFilter(String,boolean)}
     */
    public SearchFilter(boolean updateImmediately) {
	this(text, updateImmediately);
    }

    //
    // ObjectsFilter methods
    //

    @Override
    public Predicate<C> getPredicate() {
	return predicate;
    }

    //
    // CustomObjectsFilter methods
    //

    @Override
    public void start(CustomObjectsFilterAction action) {
	super.start(action);
	field.setText(lastText);
	field.selectAll();
	field.requestFocusInWindow();
	doApplyIfImmediate();
    }

    @Override
    public void stop(boolean applied) {
	super.stop(applied);

	if (applied) {
	    saveText();
	}
    }

    //
    // SearchFilter methods
    //

    public boolean getUpdateImmediately() {
	return updateImmediately;
    }

    //
    // Private methods
    //

    private void doApplyIfImmediate() {
	if (updateImmediately) {
	    saveText();
	    CustomObjectsFilterAction action = getObjectsFilterAction();
	    if (action != null) {
		action.doApply();
	    }
	}
    }

    private void saveText() {
	lastText = field.getText();
    }
}
