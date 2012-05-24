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

/**
 * A generic configuration writing class, used for adding, removing, or
 * updating lines in a #-commented line-based configuration file while
 * maintaining existing comments.
 */
public abstract class ConfigWriter
{
    /**
     * Called for each existing non-comment line if the default
     * {@link #processFile} implementation is used.  Should be overridden by
     * subclasses that don't override {@link #processFile}.
     *
     * @param writer the writer to which new configuration should be emitted
     * @param line the input line being processed
     * @return {@code true} if the line was processed, {@code false} if the
     * caller should emit the line
     * @throws java.io.IOException
     */
    protected boolean processLine(BufferedWriter writer, String line)
	throws IOException
    {
	return (false);
    }

    /**
     * Called when the end of the configuration file is reached if the
     * default {@link #processFile} implementation is used.  Default
     * implementation does nothing.
     *
     * @param writer the writer to which new configuration should be emitted
     * @throws java.io.IOException
     */
    protected void processEOF(BufferedWriter writer)
	throws IOException
    {
    }

    /**
     * Reads the configuration found in the old configuration file and writes
     * the updated configuration to the new configuration file.  The default
     * implementation copies each comment line and line for which
     * {@link #processLine} returns {@code false}, and calls {@link #processEOF}
     * when the end of the input file is reached.
     *
     * @param reader the old configuration file
     * @param writer the new configuration file
     * @throws java.io.IOException
     */
    protected void processFile(BufferedReader reader, BufferedWriter writer)
	throws IOException
    {
	String line;
	while ((line = reader.readLine()) != null) {
	    if (line.startsWith("#") || !processLine(writer, line)) {
		writer.write(line);
		writer.newLine();
	    }
	}

	processEOF(writer);
    }

    /**
     * Transforms the configuration of the specified file.  Creates a
     * temporary file, passes it and the original to {@link #processFile},
     * and renames it over the original.
     *
     * @param filename the file to transform
     * @throws java.io.IOException
     */
    protected void writeConfig(String filename) throws IOException
    {
	/*
	 * Assume we're dealing with a trusted location.
	 */
	String tmpfile = filename + ".tmp";
	BufferedReader reader = new BufferedReader(new FileReader(filename));
	BufferedWriter writer = new BufferedWriter(new FileWriter(tmpfile));

	try {
	    processFile(reader, writer);
	} finally {
	    /*
	     * Close files and move temporary file over the original.
	     */
	    reader.close();
	    writer.close();
	    (new File(tmpfile)).renameTo(new File(filename));
	}
    }
}
