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
 * Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.usermgr.client.swing;

import javax.swing.UIManager;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.*;

/**
 * The {@code HintTextComponentPropertySynchronizer} class synchronizes a {@link
 * MutableProperty} with a {@code HintTextField} so that changes in one will
 * automatically be reflected in the other.
 */
public class HintTextPropertySynchronizer<T>
    extends PropertySynchronizer<T, HintTextField> {
    //
    // Static data
    //
    private static final String HINT = Finder.getString(
	"usermgr.advanced.value.auto");

    //
    // Instance data
    //

    private T hintValue;
    private DocumentListener listener =
	new DocumentAdapter() {
	    @Override
	    public void docUpdate(DocumentEvent e) {
		objectChanged();
	    }
	};

    //
    // Constructors
    //

    public HintTextPropertySynchronizer(MutableProperty<T> property,
	HintTextField field, T hintValue, boolean initFromProp) {

	super(property, field, initFromProp);
	this.hintValue = hintValue;
	field.getDocument().addDocumentListener(listener);
    }

    /**
     * Constructs a {@code TextComponentPropertySynchronizer} with initial
     * synchronization from the property to the {@code HintTextField}.
     */
    public HintTextPropertySynchronizer(MutableProperty<T> property,
	HintTextField field, T hintValue) {

	this(property, field, hintValue, true);
    }

    //
    // PropertySynchronizer methods
    //

    @Override
    public void desynchronize() {
	super.desynchronize();
	getObject().getDocument().removeDocumentListener(listener);
    }

    @Override
    public T getValue() {
	String text = getObject().getText();
	if (text == null || text.isEmpty() || text.equals(HINT))
	    return this.hintValue;
	else {
	    T t = this.hintValue;
	    try {
		t = getProperty().getConverter().convert(text);
	    } catch (NumberFormatException nme) {
		UIManager.getLookAndFeel().provideErrorFeedback(getObject());
	    }
	    return t;
	}
    }

    @Override
    public void setValue(T t) {
	String text;
	if (t == this.hintValue ||
	    (text = getProperty().getConverter().revert(t)) == null ||
	    text.isEmpty()) {
	    getObject().setText("");
	} else {
	    getObject().setText(text);
	}
    }
}
