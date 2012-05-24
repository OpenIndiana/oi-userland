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
 * Copyright (c) 2008, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.util.common.propinfo;

import java.beans.*;
import java.lang.reflect.Method;
import java.util.*;

/**
 * The {@code ReflectionPropInfo<T>} class uses reflection to manage a
 * Java-Beans-style property of an object.
 */
public class ReflectionPropInfo<M, T> extends AbstractPropInfo<M, T> {
    //
    // Instance data
    //

    private String propName;
    private Map<String, PropertyDescriptor> map =
	new HashMap<String, PropertyDescriptor>();

    //
    // Constructors
    //

    public ReflectionPropInfo(String label, String description,
	boolean sortable, boolean editable, String propName) {

	super(label, description, sortable, editable);
	this.propName = propName;
    }

    //
    // PropInfo methods
    //

    @Override
    @SuppressWarnings({"unchecked"})
    public T getValue(M o) {
	PropertyDescriptor descriptor = getPropertyDescriptor(o);
	if (descriptor != null) {
	    Method method = descriptor.getReadMethod();
	    try {
		return (T)method.invoke(o);
	    } catch (Throwable e) {
		// XXX Log
//		System.err.printf("%s\n", e.getMessage());
	    }
	}

	return null;
    }

    @Override
    public boolean isEditable(M o) {
	boolean editable = super.isEditable(o);

	if (editable) {
	    PropertyDescriptor descriptor = getPropertyDescriptor(o);
	    if (descriptor != null) {
		editable = descriptor.getWriteMethod() != null;
	    }
	}

	return editable;
    }

    @Override
    public void setValue(M o, T value) {
	PropertyDescriptor descriptor = getPropertyDescriptor(o);
	if (descriptor != null) {
	    Method method = descriptor.getWriteMethod();
	    try {
		method.invoke(o, value);
	    } catch (Throwable e) {
		// XXX Log
//		System.err.printf("%s\n", e.getMessage());
	    }
	}
    }

    //
    // ReflectionPropInfo methods
    //

    public String getPropertyName() {
	return propName;
    }

    //
    // Private methods
    //

    private PropertyDescriptor getPropertyDescriptor(M o) {
	synchronized (map) {
	    Class c = o.getClass();
	    String cName = o.getClass().getName();
	    if (map.containsKey(cName)) {
		return map.get(cName);
	    }

	    try {
		BeanInfo info = Introspector.getBeanInfo(c);
		for (PropertyDescriptor d : info.getPropertyDescriptors()) {
		    if (d.getName().equals(propName)) {
			map.put(cName, d);
			return d;
		    }
		}
	    } catch (IntrospectionException e) {
	    }

	    return null;
	}
    }
}
