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
import java.lang.reflect.UndeclaredThrowableException;
import java.util.*;
import javax.swing.*;
import javax.swing.filechooser.FileSystemView;
import com.oracle.solaris.adr.Stability;
import com.oracle.solaris.rad.ObjectException;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.util.misc.IOUtil;

public class RemoteFileSystemView extends FileSystemView {
    //
    // Instance data
    //

    private MXBeanTracker<FileBrowserMXBean> tracker;

    //
    // Constructors
    //

    public RemoteFileSystemView(ClientContext context)
	throws TrackerException {

	tracker = new MXBeanTracker<FileBrowserMXBean>(
            FileBrowserUtil.OBJECT_NAME, FileBrowserMXBean.class,
            Stability.PRIVATE, context);
    }

    //
    // FileSystemView methods
    //

    @Override
    public RemoteFile createFileObject(File dir, String fileName) {
	if (dir != null) {
	    fileName = dir.getAbsolutePath() + File.separator + fileName;
	}
	return createFileObject(fileName);
    }

    @Override
    public RemoteFile createFileObject(String path) {
	try {
	    FileBrowserMXBean browser = tracker.getBean();
	    FileSnapshot snap = browser.getFile(path);
	    return snap != null ?
		new RemoteFile(browser, browser.getFile(path)) : null;
	} catch (ObjectException ex) {
	    return null;
	}
    }

    @Override
    protected RemoteFile createFileSystemRoot(File file) {
	return toRemoteFile(file);
    }

    @Override
    public RemoteFile createNewFolder(File containingDir) throws IOException {
	throw new IOException("operation not supported");
    }

    @Override
    public RemoteFile getChild(File parent, String fileName) {
	return createFileObject(parent, fileName);
    }

    @Override
    public RemoteFile getDefaultDirectory() {
	RemoteFile home = getHomeDirectory();
	if (home.exists()) {
	    return home;
	}

	return getRoots()[0];
    }

    @Override
    public RemoteFile[] getFiles(File dir, boolean useFileHiding) {
	List<RemoteFile> files = new ArrayList<RemoteFile>();

	FileBrowserMXBean browser = tracker.getBean();
	List<FileSnapshot> snapshots;
	try {
		snapshots = browser.getFiles(dir.getAbsolutePath());
	} catch (ObjectException e) {
		return (new RemoteFile[0]);
	} catch (java.lang.reflect.UndeclaredThrowableException e) {
		/*
		 * Our caller, BasicDirectoryModel, may interrupt us at
		 * any time.  This can cause exceptions to be thrown.
		 * In our case, our transport may throw an exception
		 * which is mapped by the MBean proxy to a
		 * UndeclaredThrowableException.
		 *
		 * Unfortunately, the FileSystemView interface doesn't
		 * allow us to throw exceptions, and letting an
		 * unchecked exception by results in noise to the
		 * user's terminal.  BasicDirectoryModel does check to
		 * see if the thread has been interrupted, though, so
		 * we mark ourselves as such and return an empty list
		 * of files.
		 */
		Thread.currentThread().interrupt();
		return (new RemoteFile[0]);
	}
	for (FileSnapshot ss : snapshots) {
	    if (!useFileHiding || !ss.isHidden()) {
		files.add(new RemoteFile(browser, ss));
	    }
	}

	return files.toArray(new RemoteFile[files.size()]);
    }

    @Override
    public RemoteFile getHomeDirectory() {
	return createFileObject(System.getProperty("user.home"));
    }

    @Override
    public RemoteFile getParentDirectory(File dir) {
	return toRemoteFile(dir).getParentFile();
    }

    public RemoteFile[] getRoots() {
	FileBrowserMXBean browser = tracker.getBean();
	List<FileSnapshot> snapshots = browser.getroots();
	return RemoteFile.toFiles(browser, snapshots);
    }

    @Override
    public String getSystemDisplayName(File file) {
	return file.getName();
    }

    @Override
    public Icon getSystemIcon(File file) {
	return UIManager.getIcon(file.isDirectory() ?
	    "FileView.directoryIcon" : "FileView.fileIcon");
    }

    @Override
    public String getSystemTypeDescription(File file) {
	return null;
    }

    @Override
    public boolean isComputerNode(File dir) {
	return false;
    }

    @Override
    public boolean isDrive(File dir) {
	return isFileSystemRoot(dir);
    }

    @Override
    public boolean isFileSystem(File file) {
	return true;
    }

    @Override
    public boolean isFileSystemRoot(File dir) {
	String fullName = IOUtil.getFullName(dir);

	RemoteFile[] roots = getRoots();
	for (RemoteFile root : roots) {
	    if (fullName.equals(IOUtil.getFullName(root))) {
		return true;
	    }
	}

	return false;
    }

    @Override
    public boolean isFloppyDrive(File dir) {
	return false;
    }

    @Override
    public boolean isHiddenFile(File file) {
	return toRemoteFile(file).isHidden();
    }

    @Override
    public boolean isParent(File dir, File file) {
	boolean retVal = dir.equals(file.getParentFile());
	return retVal;
    }

    @Override
    public boolean isRoot(File file) {
	return isFileSystemRoot(file);
    }

    @Override
    public Boolean isTraversable(File file) {
	return file.isDirectory();
    }

    //
    // RemoteFileSystemView methods
    //

    /**
     * Stops monitoring the connection to the remote host.
     */
    public void dispose() {
	tracker.dispose();
    }

    //
    // Private methods
    //

    private RemoteFile toRemoteFile(File file) {
	if (file instanceof RemoteFile) {
	    RemoteFile rFile = (RemoteFile)file;
	    if (rFile.getBrowser() == tracker.getBean()) {
		return rFile;
	    }
	}
	return createFileObject(file.getAbsolutePath());
    }
}
