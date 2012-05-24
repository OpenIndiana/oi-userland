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

package com.oracle.solaris.vp.panel.common.api.file;

import java.io.*;
import java.util.List;
import com.oracle.solaris.rad.ObjectException;

@SuppressWarnings({"serial"})
public class RemoteFile extends File {
    //
    // Instance data
    //

    private FileBrowserMXBean browser;
    private FileSnapshot snapshot;

    //
    // Constructors
    //

    public RemoteFile(FileBrowserMXBean browser, FileSnapshot snapshot) {
	super(snapshot.getPath());
	this.browser = browser;
	this.snapshot = snapshot;
    }

    //
    // File methods
    //

    @Override
    public boolean canExecute() {
	// Operation not supported
	return false;
    }

    @Override
    public boolean canRead() {
	return snapshot.isReadable();
    }

    @Override
    public boolean canWrite() {
	return snapshot.isWritable();
    }

    @Override
    public boolean createNewFile() throws IOException {
	throw new IOException("operation not supported");
    }

    @Override
    public boolean delete() {
	// Operation not supported
	return false;
    }

    @Override
    public void deleteOnExit() {
	// Operation not supported
    }

    @Override
    public boolean exists() {
	return snapshot.isExists();
    }

    @Override
    public RemoteFile getAbsoluteFile() {
	// RemoteFiles are based on FileSnapshots which are always absolute
	return this;
    }

    @Override
    public String getAbsolutePath() {
	return snapshot.getAbsolutePath();
    }

    @Override
    public RemoteFile getCanonicalFile() throws IOException {
	if (snapshot.isCanonical()) {
	    return this;
	}
	String path = snapshot.getCanonicalPath();
	try {
	    return new RemoteFile(browser, browser.getFile(path));
	} catch (ObjectException e) {
	    throw new IOException(e);
	}
    }

    @Override
    public String getCanonicalPath() throws IOException {
	String path = snapshot.getCanonicalPath();
	if (path == null) {
	    // FileSnapshot could not canonicalize path
	    throw new IOException(
		"unable to canonicalize path: " + getAbsolutePath());
	}

	return path;
    }

    @Override
    public long getFreeSpace() {
	return snapshot.getFreeSpace();
    }

    @Override
    public RemoteFile getParentFile() {
	String parent = getParent();
	try {
	    return parent == null ? null :
		new RemoteFile(browser, browser.getFile(parent));
	} catch (ObjectException e) {
	    /* Not correct, but our choices are limited */
	    return null;
	}
    }

    @Override
    public long getTotalSpace() {
	return snapshot.getTotalSpace();
    }

    @Override
    public long getUsableSpace() {
	return snapshot.getUsableSpace();
    }

    @Override
    public boolean isAbsolute() {
	return snapshot.isAbsolute();
    }

    @Override
    public boolean isDirectory() {
	return snapshot.isDirectory();
    }

    @Override
    public boolean isFile() {
	return snapshot.isFile();
    }

    @Override
    public boolean isHidden() {
	return snapshot.isHidden();
    }

    @Override
    public long lastModified() {
	return snapshot.getLastModified().getTime();
    }

    @Override
    public long length() {
	return snapshot.getLength();
    }

    @Override
    public String[] list() {
	try {
	    List<FileSnapshot> snapshots = browser.getFiles(getAbsolutePath());
	    String[] names = new String[snapshots.size()];

	    int i = 0;
	    for (FileSnapshot ss : snapshots)
		names[i++] = ss.getBaseName();

	    return names;
	} catch (ObjectException e) {
	    return null;
	}
    }

    @Override
    public RemoteFile[] listFiles() {
	try {
	    List<FileSnapshot> snapshots = browser.getFiles(getAbsolutePath());
	    return toFiles(snapshots);
	} catch (ObjectException e) {
	    return null;
	}
    }

    @Override
    public boolean mkdir() {
	// Operation not supported
	return false;
    }

    @Override
    public boolean mkdirs() {
	// Operation not supported
	return false;
    }

    @Override
    public boolean renameTo(File dest) {
	// Operation not supported
	return false;
    }

    @Override
    public boolean setExecutable(boolean executable) {
	// Operation not supported
	return false;
    }

    @Override
    public boolean setExecutable(boolean executable, boolean ownerOnly) {
	// Operation not supported
	return false;
    }

    @Override
    public boolean setLastModified(long time) {
	// Operation not supported
	return false;
    }

    @Override
    public boolean setReadable(boolean readable) {
	// Operation not supported
	return false;
    }

    @Override
    public boolean setReadable(boolean readable, boolean ownerOnly) {
	// Operation not supported
	return false;
    }

    @Override
    public boolean setReadOnly() {
	// Operation not supported
	return false;
    }

    @Override
    public boolean setWritable(boolean writable) {
	// Operation not supported
	return false;
    }

    @Override
    public boolean setWritable(boolean writable, boolean ownerOnly) {
	// Operation not supported
	return false;
    }

    //
    // RemoteFile methods
    //

    public FileBrowserMXBean getBrowser() {
	return browser;
    }

    public FileSnapshot getSnapshot() {
	return snapshot;
    }

    protected RemoteFile[] toFiles(List<FileSnapshot> snapshots) {
	return toFiles(browser, snapshots);
    }

    //
    // Static methods
    //

    public static RemoteFile[] toFiles(
	FileBrowserMXBean browser, List<FileSnapshot> snapshots) {

	RemoteFile[] files = new RemoteFile[snapshots.size()];

	int i = 0;
	for (FileSnapshot ss : snapshots)
	    files[i++] = new RemoteFile(browser, ss);

	return files;
    }

}
