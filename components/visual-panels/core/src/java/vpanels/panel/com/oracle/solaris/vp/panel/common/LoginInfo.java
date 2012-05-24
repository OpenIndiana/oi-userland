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
 * Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panel.common;

/**
 * The {@code LoginInfo} interface encapsulates common
 * login attributes.
 */
public interface LoginInfo {
    /**
     * Gets the host for this login.
     */
    String getHost();

    /**
     * Gets the role for this login.
     */
    String getRole();

    /**
     * Gets the user for this login.
     */
    String getUser();

    /**
     * Gets the zone for this login.
     */
    String getZone();

    /**
     * Gets the zone role for this login.
     */
    String getZoneRole();

    /**
     * Gets the zone user for this login.
     */
    String getZoneUser();

    /**
     * Test if given properties match this instance.
     */
    boolean matches(String host, String user, String role, String zone,
	String zoneUser, String zoneRole);

    /**
     * Test if given {@link LoginInfo} matches this instance.
     */
    boolean matches(LoginInfo info);
}
