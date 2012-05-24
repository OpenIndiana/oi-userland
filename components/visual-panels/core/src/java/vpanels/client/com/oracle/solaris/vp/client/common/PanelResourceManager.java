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

package com.oracle.solaris.vp.client.common;

import java.io.*;
import java.net.*;
import java.security.*;
import java.util.*;
import com.oracle.solaris.rad.jmx.IncompatibleVersionException;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.action.ActionAbortedException;
import com.oracle.solaris.vp.panel.common.api.panel.*;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public abstract class PanelResourceManager {
    //
    // PanelResourceManager methods
    //

    /**
     * Returns the PanelResourceManager subclass -determined user
     * directory.
     */
    abstract protected String getUserDir();

    /**
     * Checks to see if the download process has been cancelled.  Subclasses
     * should override this method if they provide a method for the user to
     * cancel the login process.  This default implementation does nothing.
     *
     * @exception   ActionAbortedException
     *		    if the action has been cancelled
     */
    protected void checkForCancel() throws ActionAbortedException {
    }

    /**
     * Downloads all resources needed by a particular {@link CustomPanel}.
     *
     * @param	    info
     *		    the connection information
     *
     * @param	    panel
     *		    the {@link CustomPanel} that requires resources downloaded
     *
     * @return	    the {@code URL}s pointing to local copies of the downloaded
     *		    resources for the given panel, or {@code null} if an error
     *		    occurred
     *
     * @exception   ActionAbortedException
     *		    if the download is aborted before it is complete
     *
     * @exception   PanelResourceException
     *		    if a resource could not be downloaded
     */
    protected URL[] downloadAll(ConnectionInfo info, CustomPanel panel)
	throws ActionAbortedException, PanelResourceException
    {
	List<URL> urls = new ArrayList<URL>();
	boolean isLocal = NetUtil.isLocalAddress(info.getHost());

	PanelMXBeanTracker tracker = null;
	PanelMXBean bean = null;

	// Download each resource
	for (ResourceDescriptor descriptor : panel.getResourceDescriptors()) {
	    checkForCancel();

	    InputStream in = null;
	    String fileName = null;
	    String remoteFile = descriptor.getFile();

	    try {
		fileName = isLocal ? remoteFile :
		    getLocalCacheName(info, remoteFile);

		final File file = new File(fileName);
		URI uri = AccessController.doPrivileged(
		    new PrivilegedAction<URI>() {
			@Override
			public URI run() {
			    return file.toURI();
			}
		    });
		urls.add(uri.toURL());

		if (!isLocal) {
		    boolean download = true;

		    if (file.exists()) {
			byte[] sHash = descriptor.getHash();
			if (sHash != null) {
			    byte[] cHash = FileUtil.getHash(
				fileName, descriptor.getHashAlgorithm());

			    if (Arrays.equals(sHash, cHash)) {
				download = false;
			    }
			}
		    }

		    if (download) {
			final File parent = file.getParentFile();
			if (parent != null && !parent.exists()) {
			    String path = parent.getCanonicalPath();
			    showStatus(Finder.getString("download.status.mkdir",
				path));

			    if (!AccessController.doPrivileged(
				new PrivilegedAction<Boolean>() {
				    @Override
				    public Boolean run() {
					return parent.mkdirs();
				    }
				})) {
				throw new IOException(
				    Finder.getString("download.error.mkdir",
				    path));
			    }

			    checkForCancel();
			}

			showStatus(Finder.getString(
			    "download.status.download", fileName));

			if (bean == null) {
			    if (tracker == null) {
				tracker = createTracker(info);
			    }
			    bean = tracker.getBean();
			}

			final byte[] resource = bean.getResource(
			    descriptor.getToken());

			AccessController.doPrivileged(
			    new PrivilegedExceptionAction<Object>() {
				@Override
				public Object run() throws IOException {
				    OutputStream out =
					new FileOutputStream(file);
				    out.write(resource);
				    out.close();
				    return null;
				}
			    });
		    }
		}
	    }

	    catch (Exception e) {
		throw new PanelResourceException(Finder.getString(
		    "download.error.download", panel.getName(), info.getHost(),
		    remoteFile), e);
	    }

	    finally  {
		IOUtil.closeIgnore(in);
		if (tracker != null) {
		    tracker.dispose();
		}
	    }
	}

	return urls.toArray(new URL[urls.size()]);
    }

    /**
     * Returns the file name of the locally cached version of the given remote
     * file, mapped to {@link PanelResourceManager#getUserDir
     * userdir}/cache/<i>host</i>/<i>path</i>.
     */
    public String getLocalCacheName(ConnectionInfo info, String remoteFile) {
	return TextUtil.join(File.separator,
	    getUserDir(), "cache", info.getHost(), remoteFile);
    }

    /**
     * Displays the user-friendly status of this {@code PanelResourceManager}.
     * Subclasses may wish to override this method -- this default
     * implementation does nothing.
     */
    protected void showStatus(String status) {
    }

    //
    // Private methods
    //

    private PanelMXBeanTracker createTracker(ConnectionInfo info)
	throws PanelResourceException {

	PanelMXBeanTracker tracker;

	try {
	    tracker = new PanelMXBeanTracker();
	    tracker.setConnectionInfo(info);

	} catch (TrackerException e) {
	    Throwable cause = e.getCause();
	    String message;

	    if (cause instanceof IncompatibleVersionException) {
		IncompatibleVersionException ive =
		    (IncompatibleVersionException)cause;

		message = Finder.getString("proxy.error.version",
		    ive.getClientVersion(), ive.getServerVersion(),
		    ive.getInterfaceClass().getSimpleName());
	    } else {
		message = Finder.getString("download.error.general",
		    info.getHost());
	    }

	    throw new PanelResourceException(message, cause);
	}

	return tracker;
    }
}
