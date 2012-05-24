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

package com.oracle.solaris.vp.util.misc;

import java.beans.*;
import java.lang.reflect.*;

public class BeanUtil {
    //
    // Static data
    //

    private static final String MUTATOR_PREFIX = "set";

    //
    // Static methods
    //

    public static void setPropertyInBean(Object bean, String property,
	String valueAsText) throws IntrospectionException,
	IllegalAccessException, NoSuchMethodException,
	InvocationTargetException {

	String methodName = getMutatorMethodName(property);
	Method method = null;

//	System.out.println("Bean: " + bean.getClass().getName());

	if (valueAsText == null) {
//	    System.out.println("Looking for null setter: " + methodName);
	    // Find and invoke a mutator method with no parameters
	    try {
		method = bean.getClass().getMethod(methodName);
		method.invoke(bean);
//		System.out.println("Found method: " + method.getName());
	    }
	    catch (NoSuchMethodException ignore) {}
	}

	if (method == null) {
	    // Search for an appropriate mutator method (throws
	    // IntrospectionException)
	    BeanInfo info = Introspector.getBeanInfo(bean.getClass());

	    if (info != null) {
		PropertyDescriptor descriptors[] =
		    info.getPropertyDescriptors();

		for (PropertyDescriptor descriptor : descriptors) {
		    if (descriptor.getName().equals(property)) {
			method = descriptor.getWriteMethod();

			if (method != null) {
			    Class type = descriptor.getPropertyType();

			    // Is there a property editor for this type?
			    PropertyEditor editor = null;
			    Class propEdClass =
				descriptor.getPropertyEditorClass();
			    if (propEdClass != null) {
				try {
				    editor = (PropertyEditor)
					propEdClass.newInstance();
				}
				catch (Exception ignore) {}
			    }

			    // No editor specifically for this
			    // property -- check the PropertyEditorManager
			    if (editor == null) {
				editor = PropertyEditorManager.findEditor(type);
			    }

			    Object value = null;

			    // If an editor was found...
			    if (editor != null) {
				// Use it to convert text to usable value
				editor.setAsText(valueAsText);
				value = editor.getValue();
			    } else {
				// Convert text to usable value
				value = getValueAs(type, valueAsText);
			    }

			    method.invoke(bean, value);
			}
			break;
		    }
		}
	    }
	}

	if (method == null) {
	    throw new NoSuchMethodException(
		bean.getClass().getName() + "." + methodName);
	}
    }

    public static String getMutatorMethodName(String property) {
	if (property == null || property.isEmpty()) {
	    return null;
	}
	return MUTATOR_PREFIX +
	    property.substring(0, 1).toUpperCase() + property.substring(1);
    }

    //
    // Private static methods
    //

    private static Object getValueAs(Class type, String value) {
	if (value == null) {
	    return null;
	}

	if (type.equals(Boolean.class) || type.equals(Boolean.TYPE)) {
	    return new Boolean(value);
	}

	if (type.equals(Byte.class) || type.equals(Byte.TYPE)) {
	    return new Byte(value);
	}

	if (type.equals(Character.class) || type.equals(Character.TYPE)) {
	    return value.isEmpty() ? null : new Character(value.charAt(0));
	}

	if (type.equals(Short.class) || type.equals(Short.TYPE)) {
	    return new Short(value);
	}

	if (type.equals(Integer.class) || type.equals(Integer.TYPE)) {
	    return new Integer(value);
	}

	if (type.equals(Float.class) || type.equals(Float.TYPE)) {
	    return new Float(value);
	}

	if (type.equals(Long.class) || type.equals(Long.TYPE)) {
	    return new Long(value);
	}

	if (type.equals(Double.class) || type.equals(Double.TYPE)) {
	    return new Double(value);
	}

	if (type.isInstance(value)) {
	    return value;
	}

	return null;
    }
}
