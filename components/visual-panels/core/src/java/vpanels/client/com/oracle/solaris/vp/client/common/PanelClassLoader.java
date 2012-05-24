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

package com.oracle.solaris.vp.client.common;

import java.io.*;
import java.lang.reflect.InvocationTargetException;
import java.net.*;
import java.security.*;
import java.util.*;
import java.util.regex.*;

public class PanelClassLoader extends URLClassLoader {
    //
    // Static data
    //

    private static Set<Permission> permSet = new HashSet<Permission>();
    private static Class[] ARGS_NAME = { String.class };
    private static Class[] ARGS_NAME_ACTIONS = { String.class, String.class };

    //
    // Constructors
    //

    public PanelClassLoader(URL[] urls) {
	super(urls);
    }

    //
    // SecureClassLoader methods
    //

    @Override
    protected PermissionCollection getPermissions(CodeSource codeSource) {
	PermissionCollection perms = super.getPermissions(codeSource);
	for (Permission perm : permSet) {
	    perms.add(perm);
	}
	return perms;
    }

    //
    // Static methods
    //

    public static void loadPermissions(URL url) throws IOException,
	PermissionParseException {

	BufferedReader in = new BufferedReader(new InputStreamReader(
	    url.openStream()));
	String line;
	Pattern ignore = Pattern.compile("^\\s*(//.*)?$");
	Pattern valid = Pattern.compile("^\\s*permission\\s+(\\S+)" +
	    "(\\s+\"([^\"]*)\"(,\\s+\"([^\"]*)\")?)?;$");

	Set<Permission> perms = new HashSet<Permission>();

	while ((line = in.readLine()) != null) {
	    if (ignore.matcher(line).matches()) {
		continue;
	    }

	    Matcher matcher = valid.matcher(line);
	    if (!matcher.matches()) {
                throw new PermissionParseException("invalid syntax: " + line);
	    }

	    int nGroups = matcher.groupCount();
	    String type = matcher.group(1);
	    String name = expand(nGroups >= 3 ? matcher.group(3) : null);
	    String actions = expand(nGroups >= 5 ? matcher.group(5) : null);

	    try {
		Permission perm = getPermission(type, name, actions);
		perms.add(perm);
	    } catch (Throwable e) {
		String message = String.format(
		    "could not instantiate permission: " +
		    "type=%s name=%s actions=", type, name, actions);
		throw new PermissionParseException(message, e);
	    }
	}

	in.close();

	permSet.addAll(perms);
    }

    //
    // Private static methods
    //

    private static String expand(String str) {
	if (str == null) {
	    return null;
	}

	StringBuilder result = new StringBuilder();
	Pattern re = Pattern.compile("^(.*?)\\$\\{([^}]*)\\}(.*)");
	while (true) {
	    Matcher matcher = re.matcher(str);
	    if (matcher.matches()) {
		result.append(matcher.group(1));
		String property = matcher.group(2);
		if (property.equals("/")) {
		    property = "file.separator";
		}
		String value = System.getProperty(property);
		if (value != null) {
		    result.append(value);
		}
		str = matcher.group(3);
	    } else {
		result.append(str);
		break;
	    }
	}
	return result.toString();
    }

    @SuppressWarnings({"fallthrough"})
    private static Permission getPermission(String type, String name,
        String actions) throws ClassNotFoundException, InstantiationException,
        IllegalAccessException, NoSuchMethodException, InvocationTargetException
    {
        Class<?> clazz = Class.forName(type);
	int nArgs = actions != null ? 2 : name != null ? 1 : 0;

	switch (nArgs) {
	    case 0:
		try {
		    return (Permission)clazz.getConstructor().newInstance();
		} catch (NoSuchMethodException e) {
		}

	    case 1:
		try {
		    return (Permission)clazz.getConstructor(ARGS_NAME).
			newInstance(name);
		} catch (NoSuchMethodException e) {
		}

	    case 2:
		return (Permission)clazz.getConstructor(ARGS_NAME_ACTIONS).
		    newInstance(name, actions);
	}

	assert false;
	return null;
    }
}
