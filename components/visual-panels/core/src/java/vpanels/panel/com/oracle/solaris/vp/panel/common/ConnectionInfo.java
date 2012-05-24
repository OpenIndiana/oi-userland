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

import java.net.*;
import javax.management.remote.JMXConnector;
import com.oracle.solaris.vp.util.misc.*;

/**
 * The {@code ConnectionInfo} class encapsulate an open {@code JMXConnector} and
 * some of its attributes.
 */
public class ConnectionInfo implements LoginInfo {
    //
    // Instance data
    //

    private String host;
    private String user;
    private String role;
    private String zone;
    private String zoneUser;
    private String zoneRole;
    private JMXConnector connector;
    private InetAddress[] addrs;
    private Boolean isLocalAddress;

    //
    // Constructors
    //

    public ConnectionInfo(String host, String user, String role,
	String zone, String zoneUser, String zoneRole, JMXConnector connector) {

	this.host = host;
	this.user = user;
	this.role = role;
	this.zone = zone;
	this.zoneUser = zoneUser;
	this.zoneRole = zoneRole;
	this.connector = connector;
    }

    public ConnectionInfo(String host, String user, String role,
	JMXConnector connector) {

	this(host, user, role, null, null, null, connector);
    }

    //
    // LoginInfo methods
    //

    @Override
    public String getHost() {
	return host;
    }

    @Override
    public String getRole() {
	return role;
    }

    @Override
    public String getUser() {
	return user;
    }

    @Override
    public String getZone() {
	return zone;
    }

    @Override
    public String getZoneUser() {
	return zoneUser;
    }

    @Override
    public String getZoneRole() {
	return zoneRole;
    }

    @Override
    public boolean matches(String host, String user, String role, String zone,
	String zoneUser, String zoneRole) {

	// Defer matchesHost to last
        return matchesUser(user) && matchesRole(role) && matchesZone(zone) &&
            (zone == null || matchesZoneUser(zoneUser)) &&
            (zone == null || matchesZoneRole(zoneRole)) &&
            matchesHost(host);
    }

    @Override
    public boolean matches(LoginInfo info) {
	return matches(info.getHost(), info.getUser(), info.getRole(),
	    info.getZone(), info.getZoneUser(), info.getZoneRole());
    }

    //
    // Object methods
    //

    @Override
    public void finalize() throws Throwable {
	IOUtil.closeIgnore(connector);
	super.finalize();
    }

    @Override
    public String toString() {
	StringBuilder buffer = new StringBuilder();
	if (zone != null) {
	    buffer.append(toString(zone, zoneUser, zoneRole)).append(", via ");
	}
	buffer.append(toString(host, user, role));
        return buffer.toString();
    }

    //
    // ConnectionInfo methods
    //

    public JMXConnector getConnector() {
	return connector;
    }

    public synchronized InetAddress[] getInetAddresses() {
	if (addrs == null) {
	    try {
		addrs = NetUtil.getAllByName(getHost());
	    } catch (UnknownHostException e) {
		addrs = new InetAddress[0];
	    }
	}
	return addrs;
    }

    public boolean matchesHost(String host) {
	// Avoid IP resolution if possible
	if (ObjectUtil.equals(host, getHost())) {
	    return true;
	}

	// Test for localhost
	if (isLocalAddress == null) {
	    isLocalAddress = NetUtil.isLocalAddress(getHost());
	}
	if (isLocalAddress && NetUtil.isLocalAddress(host)) {
	    return true;
	}

	try {
	    InetAddress[] addrs = getInetAddresses();
	    InetAddress[] addrs2 = NetUtil.getAllByName(host);

	    for (InetAddress addr : addrs) {
		for (InetAddress addr2 : addrs2) {
		    if (addr.equals(addr2)) {
			return true;
		    }
		}
	    }
	} catch (UnknownHostException stop) {
	}
	return false;
    }

    public boolean matchesRole(String role) {
	return ObjectUtil.equals(role, getRole());
    }

    public boolean matchesUser(String user) {
	return ObjectUtil.equals(user, getUser());
    }

    public boolean matchesZone(String zone) {
	return ObjectUtil.equals(zone, getZone());
    }

    public boolean matchesZoneRole(String zoneRole) {
	return ObjectUtil.equals(zoneRole, getZoneRole());
    }

    public boolean matchesZoneUser(String zoneUser) {
	return ObjectUtil.equals(zoneUser, getZoneUser());
    }

    //
    // Static methods
    //

    private static String toString(String host, String user, String role) {
	String fmt = role == null ?
	    "%2$s@%1$s" : "%3$s@%1$s (%2$s)";
	return String.format(fmt, host, user, role);
    }
}
