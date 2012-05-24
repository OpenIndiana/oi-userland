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

/**
 * The {@code KeyValueWriter} class is a {@link ConfigWriter} that writes
 * key/value lines.
 */
public class KeyValueWriter extends ConfigWriter
{
    private String regex_;
    private String separator_;
    private Map<String, String> defaults_;

    protected KeyValueWriter(String regex, String separator,
	Map<String, String> defaults)
    {
	regex_ = regex;
	separator_ = separator;
	defaults_ = new HashMap<String, String>(defaults);
    }

    private void writeLine(BufferedWriter writer, String key, String value)
	throws IOException
    {
	writer.write(key + separator_ + value);
	writer.newLine();
    }

    @Override
    protected boolean processLine(BufferedWriter writer, String line)
	throws IOException
    {
	String pieces[] = line.split(regex_, 2);

	/*
	 * If there is a matching line, replace the first occurance.
	 * Eliminate subsequent occurances of a match.
	 * Pass non-matching lines through without modification.
	 */
	if (pieces.length != 2 || !defaults_.containsKey(pieces[0]))
	    return (false);

	String replacement = defaults_.get(pieces[0]);
	if (replacement == null)
	    return (true);

	writeLine(writer, pieces[0], replacement);
	defaults_.put(pieces[0], null);

	return (true);
    }

    @Override
    protected void processEOF(BufferedWriter writer)
	throws IOException
    {
	/*
	 * If we haven't yet written any pairs to the file, do so now.
	 */
	for (Map.Entry<String, String> entries : defaults_.entrySet())
	    if (entries.getValue() != null)
		writeLine(writer, entries.getKey(), entries.getValue());
    }
}
