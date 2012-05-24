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

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.util.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.panels.firewall.client.swing.AccessPolicy.Type;

public class AccessPolicyUtil {

    public static final String DENY_POLICY = "deny";
    public static final String ALLOW_POLICY = "allow";
    public static final String NONE_POLICY = "none";
    public static final String USE_GLOBAL_POLICY = "use_global";
    public static final String CUSTOM_POLICY = "custom";

    public static final String VALID_CHARS = "[\\d\\./]*";
    public static final String PORT_REGEX = "\\d{1,5}(\\s*-\\s*\\d{1,5})?";
    public static final String HOST_REGEX = "(([\\d ]{1,3})\\.){3}[\\d ]{1,3}";
    public static final String NET_REGEX =
	    "(([\\d ]{1,3})\\.){3}[\\d ]{1,3}(/[\\d ]{0,2})?";

    public static final int PORT_MAX = 65535;

    //
    // Policy to property value map
    //
    public static EnumMap<Type, String> policy2prop;
    static {
	policy2prop = new EnumMap<Type, String>(Type.class);

	policy2prop.put(Type.NONE, NONE_POLICY);
	policy2prop.put(Type.DENY, DENY_POLICY);
	policy2prop.put(Type.ALLOW, ALLOW_POLICY);
	policy2prop.put(Type.USE_GLOBAL, USE_GLOBAL_POLICY);
	policy2prop.put(Type.CUSTOM, CUSTOM_POLICY);
    }

    // Property value to policy map
    public static Map<String, Type> prop2policy;
    static {
	prop2policy = new HashMap<String, Type>();

	prop2policy.put(NONE_POLICY, Type.NONE);
	prop2policy.put(DENY_POLICY, Type.DENY);
	prop2policy.put(ALLOW_POLICY, Type.ALLOW);
	prop2policy.put(USE_GLOBAL_POLICY, Type.USE_GLOBAL);
	prop2policy.put(CUSTOM_POLICY, Type.CUSTOM);
    }

    public static String toString(Type type, boolean verbose) {
	String resource = "access.value." +
	    (verbose ? "long" : "short") + "." + type;
	return Finder.getString(resource);
    }

    public static String toString(AccessPolicy policy, boolean verbose) {
	Type type = policy == null ? null : policy.getType();
	return toString(type, verbose);
    }

    public static String toPropValue(Type type) {
	return policy2prop.get(type);
    }

    public static Type toType(String value) {
	return prop2policy.get(value);
    }

    /**
     * Return a list of non-emmpty strings.
     *
     * Called from getAccessPolicy to filter out empty values from
     * repository properties.
     *
     */
    public static List<String> cleanList(List<String> list) {
	if (list == null)
	    return Collections.emptyList();

	List<String> nList = new ArrayList<String>(list.size());
	for (String s : list) {
	    if (!s.isEmpty())
		nList.add(s);
	}

	return nList;
    }

    //
    // Validate a string of port range in the form:
    //   port1 - port2
    //
    public static boolean validatePort(String addr) {
	if (addr == null)
	    return false;

	//
	// Confirm pattern
	//
	if (!addr.matches(PORT_REGEX))
	    return false;

	//
	// Check each port
	//
	String array[] = addr.split("\\s*-\\s*");

	if (array.length > 2)
	    return false;

	try {
	    if (array.length == 2) {
		int p1 = Integer.parseInt(array[0].trim());
		int p2 = Integer.parseInt(array[1].trim());

		if (p1 > PORT_MAX || p2 > PORT_MAX || p1 == 0 || p2 == 0 ||
		    p1 == p2)
		    return false;

	    } else {
		int n = Integer.parseInt(array[0].trim());
		if (n > PORT_MAX || n == 0)
		    return false;
	    }
	} catch (NumberFormatException e) {
	    return false;
	}

	return true;
    }

    //
    // Validate format for an IPv4 host address
    //
    public static boolean validateIP(String addr) {
	if (addr == null)
	    return false;

	//
	// Confirm pattern
	//
	if (!addr.matches(HOST_REGEX))
	    return false;

	//
	// Check each "octet"
	//
	String array[] = addr.split("\\.");
	try {
	    for (String octet : array) {
		if (Integer.parseInt(octet.trim()) > 254)
		    return false;
	    }
	} catch (NumberFormatException e) {
	    return false;
	}

	return true;
    }

    //
    // Validate format for an IPv4 subnet address
    //
    public static boolean validateSubnetIP(String addr) {
	if (addr == null)
	    return false;

	if (!addr.matches(NET_REGEX)) {
	    return false;
	}

	String mask = subnetGetMask(addr);
	if (mask != null) {
	    if (mask.isEmpty())
		return false;

	    try {
		//
		// What are reasonable max/min value for subnet mask?
		//
		if (Integer.parseInt(mask) > 32)
		    return false;

	    } catch (NumberFormatException e) {
		return false;
	    }
	}

	return validateIP(subnetGetIP(addr));
    }

    //
    // Remove leading zeros in each octet for input address.
    //
    public static String cleanIP(String addr) {
	if (!validateIP(addr))
	    return null;

	String octs[] = addr.split("\\.");
	for (int i = 0; i < octs.length; i++) {
	    octs[i] = String.valueOf(Integer.parseInt(octs[i].trim()));
	}

	return (octs[0] + "." + octs[1] + "." + octs[2] + "." + octs[3]);
    }

    public static String cleanSubnet(String addr) {
	if (!validateSubnetIP(addr))
	    return null;

	String mask = subnetGetMask(addr);
	String ip = cleanIP(subnetGetIP(addr));

	return (mask == null ? ip : ip + "/" + mask);
    }

    private static String subnetGetIP(String addr) {
	int index = addr.indexOf("/");
	return (index > 0 ? addr.substring(0, index) : addr);
    }

    private static String subnetGetMask(String addr) {
	int index = addr.indexOf("/");
	return (index > 0 ? addr.substring(index + 1).trim() : null);
    }
}
