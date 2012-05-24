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

package com.oracle.solaris.vp.panels.coreadm.client.swing;

import java.util.EnumSet;

/**
 * An enumeration of user-friendly configuration schemes.
 * Associated with each entry in the enumeration is a CoreConfig
 * object holding the actual configuration that entry represents.
 */
public enum CoreScheme {
    NONE {
	{
	    cc_ = new CoreConfig();
	}
    },
    CLASSIC {
	{
	    cc_ = new CoreConfig("", "core", false, false, true, false, false);
	}
    },
    DEVELOPER {
	{
	    cc_ = new CoreConfig("", "core.%f.%p",
		false, false, true, false, false);
	    cc_.getProcessScope().setContent(
		EnumSet.allOf(CoreConfig.ContentType.class));
	}
    },
    SHARED {
	{
	    cc_ = new CoreConfig("/var/cores/core.%f.uid%u.%p@%t", "",
		true, true, false, false, true);
	}
    },
    ADDICT {
	{
	    cc_ = new CoreConfig("/var/cores/core.%f.%p@%t", "core.%f.%p",
		true, true, true, false, true);
	}
    },
    CUSTOM {
	{
	    cc_ = null;
	}
    };

    CoreConfig cc_;

    /**
     * Obtains the scheme's configuration.
     *
     * @return a CoreConfig holding the scheme's configuration, or null
     * in the case of the CUSTOM scheme
     */
    CoreConfig getConfig()
    {
	return (cc_);
    }
}
