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

package com.oracle.solaris.vp.util.swing.property;

import javax.swing.JPasswordField;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.DocumentAdapter;

/**
 * The {@code PasswordFieldPropertySynchronizer} class synchronizes a {@link
 * MutableProperty} with a {@code JPasswordField} so that changes in one will
 * automatically be reflected in the other.
 */
public class PasswordFieldPropertySynchronizer
    extends PropertySynchronizer<char[], JPasswordField> {

    //
    // Instance data
    //

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

    public PasswordFieldPropertySynchronizer(MutableProperty<char[]> property,
	JPasswordField field, boolean initFromProp) {

	super(property, field, initFromProp);
	field.getDocument().addDocumentListener(listener);
    }

    /**
     * Constructs a {@code PasswordFieldPropertySynchronizer} with initial
     * synchronization from the property to the {@code JPasswordField}.
     */
    public PasswordFieldPropertySynchronizer(MutableProperty<char[]> property,
	JPasswordField field) {

	this(property, field, true);
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
    public char[] getValue() {
	return getObject().getPassword();
    }

    @Override
    public void setValue(char[] value) {
	String text = value == null ? "" : new String(value);
	getObject().setText(text);
    }
}
