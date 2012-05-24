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

package com.oracle.solaris.vp.panels.apache.client.swing;

import java.util.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.converter.DualConverter;
import com.oracle.solaris.vp.util.misc.property.*;

/**
 * The {@code MimeTypePropertySynchronizer} class synchronizes a {@link
 * MutableProperty}{@code <List<String>>} with a {@code MimeType}'s {@link
 * MutableProperty}s so that changes in one will automatically be reflected in
 * the other.
 */
public class MimeTypePropertySynchronizer
    extends PropertySynchronizer<List<String>, MimeType> {

    //
    // Static data
    //

    public static final String SMF_VALUE_PREFIX = "MIME:";

    //
    // Instance data
    //

    private ChangeListener listener =
	new ChangeListener() {
	    @Override
	    public void stateChanged(ChangeEvent e) {
		objectChanged();
	    }
	};

    //
    // Constructors
    //

    public MimeTypePropertySynchronizer(MutableProperty<List<String>> property,
	MimeType mimeType, boolean initFromProp) {

	super(property, mimeType, initFromProp);

	mimeType.getTypeProperty().addChangeListener(listener);
	mimeType.getSubtypeProperty().addChangeListener(listener);
	mimeType.getExtensionsProperty().addChangeListener(listener);
    }

    /**
     * Constructs a {@code MimeTypePropertySynchronizer} with initial
     * synchronization from {@code property} to {@code mimeType}.
     */
    public MimeTypePropertySynchronizer(MutableProperty<List<String>> property,
	MimeType mimeType) {

	this(property, mimeType, true);
    }

    //
    // PropertySynchronizer methods
    //

    @Override
    protected boolean differ() {
	return super.differ() || !ObjectUtil.equals(getSavedValue(),
	    getProperty().getSavedValue());
    }

    @Override
    public void desynchronize() {
	super.desynchronize();

	MimeType mimeType = getObject();
	mimeType.getTypeProperty().removeChangeListener(listener);
	mimeType.getSubtypeProperty().removeChangeListener(listener);
	mimeType.getExtensionsProperty().removeChangeListener(listener);
    }

    @Override
    public List<String> getValue() {
	return getValue(false);
    }

    @Override
    protected void syncObjectChanges() {
	super.syncObjectChanges();
	List<String> value = getSavedValue();
	getProperty().setSavedValue(value);
    }

    @Override
    protected void syncPropertyChanges() {
	super.syncPropertyChanges();
	List<String> value = getProperty().getSavedValue();
	setSavedValue(value);
    }

    @Override
    public void setValue(List<String> value) {
	setValue(value, false);
    }

    //
    // MimeTypePropertySynchronizer methods
    //

    public List<String> getSavedValue() {
	return getValue(true);
    }

    public void setSavedValue(List<String> value) {
	setValue(value, true);
    }

    //
    // Private methods
    //

    private List<String> getValue(boolean saved) {
	List<String> value = new ArrayList<String>(2);

	MimeType mimeType = getObject();

	MutableProperty<String> typeProperty = mimeType.getTypeProperty();
	String type = saved ? typeProperty.getSavedValue() :
	    typeProperty.getValue();

	MutableProperty<String> subtypeProperty = mimeType.getSubtypeProperty();
	String subtype = saved ? subtypeProperty.getSavedValue() :
	    subtypeProperty.getValue();

	MutableProperty<String[]> extensionsProperty =
	    mimeType.getExtensionsProperty();
	String[] extensions = saved ? extensionsProperty.getSavedValue() :
	    extensionsProperty.getValue();

	String id = SMF_VALUE_PREFIX + type + MimeType.SEPARATOR + subtype;
	value.add(id);

	if (extensions != null && extensions.length > 0) {
	    DualConverter<String, String[]> converter =
		extensionsProperty.getConverter();

	    String sValue = converter.revert(extensions);
	    value.add(sValue);
	}

	return value;
    }

    private void setValue(List<String> value, boolean saved) {
	MimeType mimeType = getObject();
	MutableProperty<String[]> extensionsProperty =
	    mimeType.getExtensionsProperty();

	String type = null;
	String subtype = null;
	String[] extensions = null;

	if (value != null) {
	    for (String sValue : value) {
		if (sValue.startsWith(SMF_VALUE_PREFIX)) {
		    sValue = sValue.substring(SMF_VALUE_PREFIX.length());

		    int index = sValue.indexOf(MimeType.SEPARATOR);
		    if (index == -1) {
			type = sValue;
			subtype = null;
		    } else {
			type = sValue.substring(0, index);
			subtype = sValue.substring(
			    index + MimeType.SEPARATOR.length());
		    }

		    if (type.isEmpty()) {
			type = null;
		    }

		    if (subtype.isEmpty()) {
			subtype = null;
		    }
		} else {
		    extensions = extensionsProperty.getConverter().convert(
			sValue);
		}
	    }
	}

	MutableProperty<String> typeProperty = mimeType.getTypeProperty();
	if (saved) {
	    typeProperty.setSavedValue(type);
	} else {
	    typeProperty.setValue(type);
	}

	MutableProperty<String> subtypeProperty = mimeType.getSubtypeProperty();
	if (saved) {
	    subtypeProperty.setSavedValue(subtype);
	} else {
	    subtypeProperty.setValue(subtype);
	}

	if (saved) {
	    extensionsProperty.setSavedValue(extensions);
	} else {
	    extensionsProperty.setValue(extensions);
	}
    }
}
