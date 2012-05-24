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

import java.util.concurrent.*;

/**
 * The {@code NamedThreadFactory} class adds a prefix to the names of the {@code
 * Thread}s produced by a wrapped {@code ThreadFactory}.
 */
public class NamedThreadFactory implements ThreadFactory {
    //
    // Instance data
    //

    private ThreadFactory factory;
    private String prefix;

    //
    // Constructors
    //

    /**
     * Constructs a {@code NamedThreadFactory} using the given prefix and thread
     * factory.
     */
    public NamedThreadFactory(String prefix, ThreadFactory factory) {
	this.prefix = prefix;
	this.factory = factory;
    }

    /**
     * Constructs a {@code NamedThreadFactory} using the given prefix and the
     * default thread factory.
     */
    public NamedThreadFactory(String prefix) {
	this(prefix, Executors.defaultThreadFactory());
    }

    //
    // ThreadFactory methods
    //

    @Override
    public Thread newThread(Runnable r) {
	Thread thread = factory.newThread(r);

	String prefix = this.prefix;
	if (prefix != null) {
	    thread.setName(prefix + thread.getName());
	}

	return thread;
    }

    //
    // NamedThreadFactory methods
    //

    public ThreadFactory getFactory() {
	return factory;
    }

    public void setFactory(ThreadFactory factory) {
	this.factory = factory;
    }

    public String getPrefix() {
	return prefix;
    }

    public void setPrefix(String prefix) {
	this.prefix = prefix;
    }
}
