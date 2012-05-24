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

package com.oracle.solaris.vp.util.misc.property;

import com.oracle.solaris.vp.util.misc.converter.DualConverter;

public class MutablePropertyUtil {
    public static <T> String getSavedValueAsString(MutableProperty<T> property)
    {
	T value = property.getSavedValue();
	return property.getConverter().revert(value);
    }

    public static <T> String getValueAsString(MutableProperty<T> property) {
	T value = property.getValue();
	return property.getConverter().revert(value);
    }

    public static <T> void setSavedValueAsString(MutableProperty<T> property,
	String sValue) {

	T value = property.getConverter().convert(sValue);
	property.setSavedValue(value);
    }

    public static <T> void setValueAsString(MutableProperty<T> property,
	String sValue) {

	T value = property.getConverter().convert(sValue);
	property.setValue(value);
    }
}
