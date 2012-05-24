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

import com.oracle.solaris.vp.panel.common.api.smf_old.Dependency;
import com.oracle.solaris.vp.panel.common.smf.*;

public class DepGroupManagedObject extends DepManagedObject<DepManagedObject>
{
    private Dependency dd_;

    public DepGroupManagedObject(Dependency dd, RepoManagedObject source)
    {
	dd_ = dd;

	for (String t : dd_.getTarget()) {
	    if (t.startsWith("svc:")) {
		SmfManagedObject smo = source.getSMO(t);
		if (smo != null)
		    addChildren(smo);
		else
		    addChildren(new UnknownDepManagedObject(t));
	    } else if (t.startsWith("file:")) {
		addChildren(new FileManagedObject(source, t));
	    } else {
		addChildren(new UnknownDepManagedObject(t));
	    }
	}
    }

    @Override
    public String getDepName()
    {
	return (dd_.getName());
    }

    @Override
    public String getDepType()
    {
	return (dd_.getGrouping() + "/" + dd_.getRestartOn());
    }

    @Override
    public String getDepState()
    {
	return ("");
    }
}
