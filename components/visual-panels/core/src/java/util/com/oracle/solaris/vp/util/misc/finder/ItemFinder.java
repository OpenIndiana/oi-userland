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

package com.oracle.solaris.vp.util.misc.finder;

import java.security.*;

public class ItemFinder implements FindingClass {
    //
    // Inner classes
    //

    // A number of classes in the JDK return the current thread's class stack
    // as a Class array, but none exposes this functionality publicly.  The
    // closest is SecurityManager, whose getClassContext method has protected
    // access.  Thus this hack.
    //
    // Note that java.lang.StackTraceElement is insufficient as it does not
    // return the actual Class objects in the stack, which are necessary to
    // retrieve each class's ClassLoader.
    //
    // An alternate approach would be to implement getClassContext() as a native
    // method.
    private static class MySecurityManager extends SecurityManager {
	@Override
	public Class[] getClassContext() {
	    return super.getClassContext();
	}
    }

    //
    // Static data
    //

    private static final MySecurityManager sManager = new MySecurityManager();
    private static final String className = ItemFinder.class.getName();

    //
    // Static methods
    //

    public static Class[] getClassContext() {
	return sManager.getClassContext();
    }

    /**
     * Gets the first class under the last {@link FindingClass} in the class
     * stack.
     */
    public static Class getCallerClass() {
	return AccessController.doPrivileged(
	    new PrivilegedAction<Class>() {
		@Override
		public Class run() {
		    return getCallerClassImp();
		}
	    });
    }

    //
    // Private static methods
    //

    private static Class getCallerClassImp() {
	Class[] stack = getClassContext();
	for (int i = stack.length - 2; i >= 0; i--) {
	    if (FindingClass.class.isAssignableFrom(stack[i])) {
		return stack[i + 1];
	    }
	}
	return null;
    }
}
