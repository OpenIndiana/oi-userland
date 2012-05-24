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

package com.oracle.solaris.vp.panel.common.smf.depend;

import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class UnknownDepManagedObject extends DepManagedObject<ManagedObject>
{
    private String name_;

    public UnknownDepManagedObject(String name)
    {
	name_ = name;
    }

    @Override
    public String getDepName()
    {
	return (name_);
    }

    @Override
    public String getDepType()
    {
	return (Finder.getString("smf.depend.type.unknown"));
    }

    @Override
    public String getDepState()
    {
	return (Finder.getString("smf.depend.state.unknown"));
    }
}
