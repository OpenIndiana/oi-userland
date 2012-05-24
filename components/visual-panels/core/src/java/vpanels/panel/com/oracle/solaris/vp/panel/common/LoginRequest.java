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

import java.util.*;
import com.oracle.solaris.vp.util.misc.DialogMessage;

public class LoginRequest {
    //
    // Instance data
    //

    private List<DialogMessage> messages = new LinkedList<DialogMessage>();
    private LoginProperty<String> host;
    private LoginProperty<String> user;
    private LoginProperty<String> role;
    private LoginProperty<Boolean> zonePrompt;
    private LoginProperty<String> zone;
    private LoginProperty<String> zoneUser;
    private LoginProperty<String> zoneRole;

    //
    // Constructors
    //

    /**
     * Constructs a {@code LoginRequest} allowing login to a non-global zone on
     * the given host.	Each editable {@code LoginProperty} may be changed by
     * the user during the login process.
     * <p/>
     * Any {@code null} {@link LoginProperty} argument will be converted to an
     * editable {@link LoginProperty} with a {@code null} value.
     *
     * @param	    host
     *		    the host property
     *
     * @param	    user
     *		    the user property
     *
     * @param	    role
     *		    the role property
     *
     * @param	    zonePrompt
     *		    the property governing whether to log into a non-global
     *		    zone once a connection to {@code host} is established
     *
     * @param	    zone
     *		    the zone property
     *
     * @param	    zoneUser
     *		    the zone user property
     *
     * @param	    zoneRole
     *		    the zone role property
     *
     * @param	    messages
     *		    optional messages to instruct the user
     */
    public LoginRequest(LoginProperty<String> host, LoginProperty<String> user,
	LoginProperty<String> role, LoginProperty<Boolean> zonePrompt,
	LoginProperty<String> zone, LoginProperty<String> zoneUser,
	LoginProperty<String> zoneRole, DialogMessage... messages) {

	this.host = createIfNeeded(host);
	this.user = createIfNeeded(user);
	this.role = createIfNeeded(role);
	this.zonePrompt = createIfNeeded(zonePrompt);
	this.zone = createIfNeeded(zone);
	this.zoneUser = createIfNeeded(zoneUser);
	this.zoneRole = createIfNeeded(zoneRole);

	for (DialogMessage message : messages) {
	    this.messages.add(message);
	}
    }

    /**
     * Constructs a {@code LoginRequest} disallowing login to a non-global zone
     * on the given host.  Each editable {@code LoginProperty} may be changed by
     * the user during the login process.
     * <p/>
     * Any {@code null} {@link LoginProperty} argument will be converted to an
     * editable {@link LoginProperty} with a {@code null} value.
     *
     * @param	    host
     *		    the host property
     *
     * @param	    user
     *		    the user property
     *
     * @param	    role
     *		    the role property
     *
     * @param	    messages
     *		    optional messages to instruct the user
     */
    public LoginRequest(LoginProperty<String> host, LoginProperty<String> user,
	LoginProperty<String> role, DialogMessage... messages) {

	this(host, user, role, new LoginProperty<Boolean>(false, false), null,
	    null, null, messages);
    }

    //
    // LoginRequest methods
    //

    public LoginProperty<String> getHost() {
	return host;
    }

    public List<DialogMessage> getMessages() {
	return messages;
    }

    public LoginProperty<String> getRole() {
	return role;
    }

    public LoginProperty<String> getUser() {
	return user;
    }

    public LoginProperty<String> getZone() {
	return zone;
    }

    public LoginProperty<Boolean> getZonePrompt() {
	return zonePrompt;
    }

    public LoginProperty<String> getZoneRole() {
	return zoneRole;
    }

    public LoginProperty<String> getZoneUser() {
	return zoneUser;
    }

    //
    // Static methods
    //

    private static <T> LoginProperty<T> createIfNeeded(
	LoginProperty<T> property) {

	if (property == null) {
	    property = new LoginProperty<T>(null, true);
	}

	return property;
    }
}
