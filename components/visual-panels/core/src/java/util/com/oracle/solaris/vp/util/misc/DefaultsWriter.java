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

import java.io.*;
import java.util.*;
import com.oracle.solaris.vp.util.misc.*;

/**
 * The {@code DefaultsWriter} class is a {@link KeyValueWriter} for the
 * /etc/default/init file.
 */
public class DefaultsWriter extends KeyValueWriter
{
    public static final String CONFIG_INIT = "/etc/default/init";

    public static Map<String, String> readDefaults(String filename)
	throws IOException
    {
	Map<String, String> result = new HashMap<String, String>();
	BufferedReader reader = new ConfigReader(filename);
	String line;

	while ((line = reader.readLine()) != null) {
	    String pieces[] = line.split("=");
	    if (pieces.length != 2)
		continue;

	    result.put(pieces[0], pieces[1]);
	}

	return (result);
    }

    public static void writeDefaults(String filename,
	Map<String, String> defaults) throws IOException
    {
	(new DefaultsWriter(defaults)).writeConfig(filename);
    }

    private DefaultsWriter(Map<String, String> defaults)
    {
	super("=", "=", defaults);
    }
}
