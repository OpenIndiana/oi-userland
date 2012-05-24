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

import java.io.File;
import java.net.*;
import java.security.CodeSource;

/**
 * Common functionality for all com.oracle.solaris subpackages.
 */
public class LibraryUtil
{
	public interface LibraryLoader
	{
		/**
		 * A function that calls System.load(filename).
		 * Must be implemented in a class loaded by the
		 * classloader the native library should be loaded by.
		 */
		public void load(String filename);
	}

	/**
	 * If the given class comes from jar file with a path of the
	 * form path/lib/java/jarfile.jar, returns path/lib.  This lets
	 * us cleaning find co-located native libraries (i.e. without
	 * employing a LD_LIBRARY_PATH-setting wrapper script).
	 */
	static private String classdir(Class c)
	{
		try {
			CodeSource cs = c.getProtectionDomain().getCodeSource();
			if (cs == null)
				return (null);
			File f = new File(cs.getLocation().toURI());
			if (!f.getName().endsWith(".jar"))
				return (null);

			/*
			 * We could obtain the absolute file here,
			 * but I don't think we should care about
			 * people setting relative class paths while
			 * running in lib/ or lib/java/.  There's
			 * probably greater hazard in assuming we can
			 * traverse the absolute path.
			 */
			f = f.getParentFile();
			if (f == null || !(f.getName() != "java"))
				return (null);
			f = f.getParentFile();
			if (f == null || !(f.getName() != "lib"))
				return (null);

			/*
			 * We made it.  Return the path.
			 *
			 * XXX: Contrary to the above comment,
			 * Runtime.load() insists that this path be
			 * absolute.
			 */
			return (f.getPath());
		} catch (SecurityException e) {
			/* Couldn't access the protection domain. */
			return (null);
		} catch (IllegalArgumentException e) {
			/* Code source wasn't a file. */
			return (null);
		} catch (URISyntaxException e) {
			/* Code source wasn't a file. */
			return (null);
		}
	}

	static private void loadLibrary(LibraryLoader loader, String paths[],
	    String name, boolean debug)
	{
		StringBuilder buffer = new StringBuilder();
		buffer.append("Unable to find ").append(name).append(':');

		for (String p : paths) {
			try {
				String path = p + "/" + name;
				if (loader != null)
					loader.load(path);
				else
					System.load(path);
				if (debug)
					System.err.println("loaded " + name +
					    " from " + p);
				return;
			} catch (UnsatisfiedLinkError e) {
				/*
				 * Unfortunately, there are many
				 * reasons why we might get an
				 * UnsatisfiedLinkError, but there is
				 * no way to distinguish them other
				 * than to case off of their messages.
				 * (Of particular interest is the
				 * "already loaded" error.)
				 *
				 * Until we are ready to soil our hands
				 * doing so, callers of loadLibrary
				 * will get a single, conflated
				 * exception.  Sigh.
				 */
				buffer.append("\n  ").append(p).append(": ").
				    append(e.getMessage());

			}
		}
		throw (new UnsatisfiedLinkError(buffer.toString()));
	}

	/**
	 * Loads a library.
	 * <p>
	 * System.load() always loads the specified library in the
	 * caller's classloader.  To permit loading native libraries in
	 * classloaders other than LibraryUtil's, the caller may supply
	 * an implementation of LibraryLoader defined by the desired
	 * classloader.
	 */
	static public void loadLibrary(Class c, LibraryLoader loader,
	    String name, boolean debug)
	{
		String path = System.getProperty("java.library.path");
		String classdir	= classdir(c);
		if (classdir != null)
			path = classdir + ":" + classdir + "/64:" + path;
		path = path + ":/usr/lib/64"; /* XXX: Java bug 6254947 */
		String[] paths = path.split(":");

		if (debug) {
			String root = System.getenv("ROOT");
			if (root != null && root.length() > 0) {
				System.err.println(
				    "Prepending $ROOT to library path.");
				String[] npaths = new String[paths.length * 2];
				for (int i = 0; i < paths.length; i++) {
					npaths[i] = root + "/" + paths[i];
					npaths[i + paths.length] = paths[i];
				}
				paths = npaths;
			}
		}

		loadLibrary(loader, paths, name, debug);
	}
}
