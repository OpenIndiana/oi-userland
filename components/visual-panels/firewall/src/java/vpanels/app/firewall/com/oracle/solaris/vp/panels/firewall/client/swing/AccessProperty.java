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
 *
 */

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.beans.PropertyChangeListener;
import java.util.*;
import javax.swing.JTextField;
import com.oracle.solaris.vp.panels.firewall.client.swing.AccessPolicy.Type;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.misc.converter.StringConverter;
import com.oracle.solaris.vp.util.misc.event.PropertyChangeListeners;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.property.*;

@SuppressWarnings({"serial"})
public class AccessProperty extends ChangeableAggregator
    implements MutableProperty<AccessPolicy> {

    //
    // Instance data
    //

    private AccessPanel panel;

    private MutableProperty<Type> typeProperty =
	new BasicMutableProperty<Type>();

    private MutableProperty<List<String>> applyAListProperty =
	new BasicMutableProperty<List<String>>();

    private MutableProperty<List<String>> applyDListProperty =
	new BasicMutableProperty<List<String>>();

    private MutableProperty<List<String>> exceptionAListProperty;
    private MutableProperty<List<String>> exceptionDListProperty;
    private MutableProperty<String> customFileProperty;

    private PropertyChangeListeners propListeners =
	new PropertyChangeListeners();

    //
    // Constructors
    //

    public AccessProperty(AccessPanel panel) {
	this.panel = panel;

	new RadioButtonPropertySynchronizer<Type>(typeProperty, panel.getMap());

	BrowsableFilePanel filePanel = panel.getCustomFilePanel();
	if (filePanel != null) {
	    customFileProperty = new StringProperty();
	    new TextComponentPropertySynchronizer<String, JTextField>(
		customFileProperty, filePanel.getField());
	}

	//
	// Exception lists are not supported in Global Override policy.
	// Thus, makes sure the EditableTablePanel exists before
	// initializing the corresponding EditableTablePanelWrapper.
	//
	EditableTablePanel p = panel.getAllowPanel().getExceptionList();
	if (p != null) {
	    p.setOrderable(false);
	    exceptionAListProperty = new BasicMutableProperty<List<String>>();
	    new EditableTablePanelPropertySynchronizer<String>(
		exceptionAListProperty, p);
	}

	p = panel.getDenyPanel().getExceptionList();
	if (p != null) {
	    p.setOrderable(false);
	    exceptionDListProperty = new BasicMutableProperty<List<String>>();
	    new EditableTablePanelPropertySynchronizer<String>(
		exceptionDListProperty, p);
	}

	p = panel.getAllowPanel().getApplyList();
	p.setOrderable(false);
	new EditableTablePanelPropertySynchronizer<String>(
	    applyAListProperty, p);

	p = panel.getDenyPanel().getApplyList();
	p.setOrderable(false);
	new EditableTablePanelPropertySynchronizer<String>(
	    applyDListProperty, p);

	if (customFileProperty == null && exceptionAListProperty == null)
	    addChangeables(typeProperty, applyAListProperty,
		applyDListProperty);

	else if (customFileProperty == null && exceptionAListProperty != null)
	    addChangeables(typeProperty, applyAListProperty, applyDListProperty,
		exceptionAListProperty, exceptionDListProperty);

	else
	    addChangeables(typeProperty, customFileProperty,
		applyAListProperty, applyDListProperty,
		exceptionAListProperty, exceptionDListProperty);
    }

    public AccessProperty(Type... types) {
	this(new AccessPanel(true, types));
    }

    public AccessProperty(boolean hasException, Type... types) {
	this(new AccessPanel(hasException, types));
    }

    //
    // MutableProperty methods
    //

    @Override
    public void addPropertyChangeListener(PropertyChangeListener listener) {
	propListeners.add(listener);
    }

    @Override
    public StringConverter<AccessPolicy> getConverter() {
	return null;
    }

    @Override
    public String getPropertyName() {
	return "access";
    }

    @Override
    public AccessPolicy getSavedValue() {
	Type type = typeProperty.getSavedValue();

	if (type == null) {
	    return null;
	}

	if (type == Type.ALLOW)
	    return new SimpleAccessPolicy(type, customFileProperty == null ?
		null : customFileProperty.getSavedValue(),
		applyAListProperty.getSavedValue(),
		exceptionAListProperty == null ?  null :
		exceptionAListProperty.getSavedValue());
	else if (type == Type.DENY)
	    return new SimpleAccessPolicy(type, customFileProperty == null ?
		null : customFileProperty.getSavedValue(),
		applyDListProperty.getSavedValue(),
		exceptionDListProperty == null ?  null :
		exceptionDListProperty.getSavedValue());
	else
	    return new SimpleAccessPolicy(type, customFileProperty == null ?
		null : customFileProperty.getSavedValue(),
		applyAListProperty == null ? null :
		applyAListProperty.getSavedValue(),
		exceptionDListProperty == null ?  null :
		exceptionDListProperty.getSavedValue());
    }

    @Override
    public AccessPolicy getValue() {
	Type type = typeProperty.getValue();

	if (type == null) {
	    return null;
	}

	//
	// Return an AccesPolicy that reflects settings current policy
	// settings in a panel. For example, a deny/allow policy should
	// return current apply and exception lists but non deny/allow
	// policy should return saved values.
	//
	if (type == Type.ALLOW)
	    return new SimpleAccessPolicy(type, customFileProperty == null ?
		null : customFileProperty.getSavedValue(),
		applyAListProperty.getValue(),
		exceptionAListProperty == null ?  null :
		exceptionAListProperty.getValue());
	else if (type == Type.DENY)
	    return new SimpleAccessPolicy(type, customFileProperty == null ?
		null : customFileProperty.getValue(),
		applyDListProperty.getValue(),
		exceptionDListProperty == null ?  null :
		exceptionDListProperty.getValue());
	else {
	    return new SimpleAccessPolicy(type, customFileProperty == null ?
		null : customFileProperty.getValue(),
		applyAListProperty.getSavedValue(),
		exceptionAListProperty == null ?  null :
		exceptionAListProperty.getSavedValue());
	}
    }

    @Override
    public boolean removePropertyChangeListener(PropertyChangeListener listener)
    {
	return propListeners.remove(listener);
    }

    @Override
    public void setSavedValue(AccessPolicy policy) {
	SimpleAccessPolicy p = (policy == null ? null :
	    (SimpleAccessPolicy) policy);

	typeProperty.setSavedValue(p == null ? null : p.getSavedType());
	if (p == null) {
	    List<String> empty = Collections.emptyList();
	    applyAListProperty.setSavedValue(empty);
	    applyDListProperty.setSavedValue(empty);

	    if (exceptionAListProperty != null) {
		exceptionAListProperty.setSavedValue(empty);
		exceptionDListProperty.setSavedValue(empty);
	    }
	} else {
	    applyAListProperty.setSavedValue(p.getSavedApplyToList());
	    applyDListProperty.setSavedValue(p.getSavedApplyToList());

	    if (exceptionAListProperty != null) {
		exceptionAListProperty.setSavedValue(
		    p.getSavedExceptionsList());
		exceptionDListProperty.setSavedValue(
		    p.getSavedExceptionsList());
	    }
	}

	if (customFileProperty != null) {
	    customFileProperty.setSavedValue(p == null ?  "" :
		p.getSavedCustomFile());
	}
    }

    @Override
    public void setValue(AccessPolicy policy) {
	typeProperty.setValue(policy == null ? null : policy.getType());

	if (policy == null) {
	    List<String> empty = Collections.emptyList();
	    applyAListProperty.setValue(empty);
	    applyDListProperty.setValue(empty);

	    if (exceptionAListProperty != null) {
		exceptionAListProperty.setValue(empty);
		exceptionDListProperty.setValue(empty);
	    }
	} else {
	    applyAListProperty.setValue(policy.getApplyToList());
	    applyDListProperty.setValue(policy.getApplyToList());

	    if (exceptionAListProperty != null) {
		exceptionAListProperty.setValue(policy.getExceptionsList());
		exceptionDListProperty.setValue(policy.getExceptionsList());
	    }
	}

	if (customFileProperty != null)
	    customFileProperty.setValue(policy == null ?  "" :
		policy.getCustomFile());
    }

    @Override
    public void update(AccessPolicy value, boolean force) {
	boolean changed = isChanged();
	setSavedValue(value);
	if (force || !changed) {
	    reset();
	}
    }

    //
    // AccessProperty methods
    //

    public AccessPanel getPanel() {
	return panel;
    }

    public void setPanelDescriptor(FirewallPanelDescriptor descriptor) {
	panel.setPanelDescriptor(descriptor);
    }
}
