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

package com.oracle.solaris.vp.util.misc;

import java.net.*;
import java.security.*;
import java.util.Enumeration;

public class NetUtil {
    public static InetAddress[] getAllByName(final String host)
	throws UnknownHostException {

	final UnknownHostException[] uhe = new UnknownHostException[1];

	InetAddress[] addrs = AccessController.doPrivileged(
	    new PrivilegedAction<InetAddress[]>() {
		@Override
		public InetAddress[] run() {
		    try {
			return InetAddress.getAllByName(host);
		    } catch (UnknownHostException e) {
			uhe[0] = e;
			return null;
		    }
		}
	    });

	if (uhe[0] != null) {
	    throw uhe[0];
	}

	return addrs;
    }

    /**
     * Gets the name of the local host.
     *
     * @return	    the hostname, or {@code null} if no IP address for the host
     *		    could be found.
     */
    public static String getHostName() {
	return AccessController.doPrivileged(
	    new PrivilegedAction<String>() {
		@Override
		public String run() {
		    try {
			return InetAddress.getLocalHost().getHostName();
		    } catch (UnknownHostException e) {
		    }
		    return null;
		}
	    });
    }

    public static boolean isLoopbackAddress(final String host) {
	return AccessController.doPrivileged(
	    new PrivilegedAction<Boolean>() {
		@Override
		public Boolean run() {
		    try {
			InetAddress addr = InetAddress.getByName(host);
			return addr.isLoopbackAddress();
		    } catch (UnknownHostException ignore) {
		    }
		    return false;
		}
	    });
    }

    public static boolean isLocalAddress(final String host) {
	return AccessController.doPrivileged(
	    new PrivilegedAction<Boolean>() {
		@Override
		public Boolean run() {
		    try {
			InetAddress[] addrs = InetAddress.getAllByName(host);

			Enumeration<NetworkInterface> localNics =
			    NetworkInterface.getNetworkInterfaces();

			while (localNics.hasMoreElements()) {

			    NetworkInterface nic = localNics.nextElement();
			    Enumeration<InetAddress> localAddrs =
				nic.getInetAddresses();

			    while (localAddrs.hasMoreElements()) {
				InetAddress localAddr =
				    localAddrs.nextElement();

				for (InetAddress addr : addrs) {
				    if (addr.equals(localAddr)) {
					return true;
				    }
				}
			    }
			}
		    } catch (UnknownHostException e) {
		    } catch (SocketException e) {
		    }

		    return false;
		}
	    });
    }
}
