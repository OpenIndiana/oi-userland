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

package com.oracle.solaris.vp.panel.common.smf;

import java.util.List;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.util.common.propinfo.AbstractPropInfo;
import com.oracle.solaris.vp.util.misc.converter.DualConverter;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class PropertyValuePropInfo
    extends AbstractPropInfo<ManagedObject, String> {

    //
    // Static data
    //

    /**
     * Available instance to mitigate object creation
     */
    public static final PropertyValuePropInfo instance =
	new PropertyValuePropInfo();

    //
    // Constructors
    //

    public PropertyValuePropInfo() {
	super(Finder.getString("property.value.label"),
	    Finder.getString("property.value.description"), true, false);
    }

    //
    // PropInfo methods
    //

    @Override
    public String getValue(ManagedObject o) {
	if (o instanceof PropertyManagedObject) {
	    BasicSmfMutableProperty<?> property =
		((PropertyManagedObject)o).getProperty();
	    return toStringValue(property);
	}
	return null;
    }

    //
    // Private methods
    //

    private <T> String toStringValue(BasicSmfMutableProperty<T> property) {
	DualConverter<String, List<T>> converter = property.getConverter();
	return converter.revert(property.getValue());
    }
}
