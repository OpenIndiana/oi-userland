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
 * Copyright (c) 2009, 2013, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panel.common.smf;

import com.oracle.solaris.scf.common.ScfException;

public class SimpleSmfPropertyInfo implements SmfPropertyInfo {
    //
    // Instance data
    //

    private SmfPropertyGroupInfo info;
    private String name;

    //
    // Constructors
    //

    public SimpleSmfPropertyInfo(SmfPropertyGroupInfo info, String name) {
	this.info = info;
	this.name = name;
    }

    public SimpleSmfPropertyInfo(HasService info, String group, String name)
    {
	this(new SimpleSmfPropertyGroupInfo(info, group), name);
    }

    public SimpleSmfPropertyInfo(ServiceBean service, String group,
	String name) {
	this(new SimpleHasService(service), group, name);
    }

    //
    // HasService methods
    //

    @Override
    public ServiceBean getService() {
	return info.getService();
    }

    //
    // SmfPropertyGroupInfo methods
    //

    @Override
    public String getPropertyGroupName() throws ScfException {
	return info.getPropertyGroupName();
    }

    //
    // SmfPropertyInfo methods
    //

    @Override
    public String getPropertyName() {
	return name;
    }
}
