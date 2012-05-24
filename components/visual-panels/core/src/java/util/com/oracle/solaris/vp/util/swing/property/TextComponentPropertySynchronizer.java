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

import javax.swing.event.*;
import javax.swing.text.JTextComponent;
import com.oracle.solaris.vp.util.misc.converter.StringConverter;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.DocumentAdapter;

/**
 * The {@code TextComponentPropertySynchronizer} class synchronizes a {@link
 * MutableProperty} with a {@code JTextComponent} so that changes in one will
 * automatically be reflected in the other.
 */
public class TextComponentPropertySynchronizer<T, C extends JTextComponent>
    extends PropertySynchronizer<T, C> {

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

    public TextComponentPropertySynchronizer(MutableProperty<T> property,
	C comp, boolean initFromProp) {

	super(property, comp, initFromProp);
	comp.getDocument().addDocumentListener(listener);
    }

    /**
     * Constructs a {@code TextComponentPropertySynchronizer} with initial
     * synchronization from the property to the {@code JTextComponent}.
     */
    public TextComponentPropertySynchronizer(MutableProperty<T> property,
	C comp) {

	this(property, comp, true);
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
	return getProperty().getConverter().convert(text);
    }

    @Override
    public void setValue(T value) {
	String text = getProperty().getConverter().revert(value);
	getObject().setText(text);
    }
}
