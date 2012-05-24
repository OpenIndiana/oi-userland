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

package com.oracle.solaris.vp.panel.common.control;

import java.util.*;
import java.util.concurrent.*;
import java.util.regex.Pattern;
import com.oracle.solaris.vp.util.misc.*;

public class Navigator {
    //
    // Static data
    //

    public static final String PATH_SEPARATOR = "/";
    public static final String PARENT_ID = "..";

    public static final Navigable PARENT_NAVIGABLE =
	new SimpleNavigable(PARENT_ID, null);

    private static int instanceCounter = 0;

    //
    // Instance data
    //

    private Thread dispatchThread;
    private ThreadPoolExecutor threadPool;
    private LinkedList<Control> stack = new LinkedList<Control>();
    private List<Control> roStack = Collections.unmodifiableList(stack);
    private NavigationListeners listeners = new NavigationListeners();
    private UITransitionManager manager = new UITransitionManager();

    //
    // Constructors
    //

    public Navigator() {
	String tName = String.format("%s-%d-", TextUtil.getBaseName(getClass()),
	    instanceCounter++);

	ThreadFactory factory =
	    new NamedThreadFactory(tName) {
		@Override
		public Thread newThread(Runnable r) {
		    dispatchThread = super.newThread(r);
		    return dispatchThread;
		}
	    };

	// Unbounded
	BlockingQueue<Runnable> queue = new LinkedBlockingQueue<Runnable>();

	// Use a thread pool with a single core thread to automatically handle
	// uncaught exceptions and queued requests.  Use a minuscule timeout so
	// that threads herein don't hold up shutdown of the JVM.
	threadPool = new ThreadPoolExecutor(
	    1, 1, 1, TimeUnit.NANOSECONDS, queue, factory);

	threadPool.allowCoreThreadTimeOut(true);

	addNavigationListener(manager);
    }

    //
    // Navigator methods
    //

    /**
     * Adds a {@link NavigationListener} to be notified when navigation is
     * stopped and started.
     */
    public void addNavigationListener(NavigationListener l) {
	listeners.add(l);
    }

    /**
     * Runs the given {@code Runnable} asynchronously on this {@code
     * Navigator}'s navigation thread.	This thread is intended to be used
     * specifically for navigation; the given {@code Runnable} should thus be
     * limited to calling {@link #goTo(boolean,Control,Navigable...)} and
     * (briefly) handling any thrown exceptions.
     * <p/>
     * Note: If this method is called when the navigation thread is busy, the
     * given {@code Runnable} will be queued and run when the thread is
     * available.
     *
     * @param	    r
     *		    the {@code Runnable} to run and handle any resulting
     *		    exceptions
     */
    public void asyncExec(Runnable r) {
	threadPool.execute(r);
    }

    /**
     * Runs the given {@link NavRunnable} on this {@code Navigator}'s navigation
     * thread and waits for it to complete.  Any exceptions thrown by {@code r}
     * are thrown here.
     * <p/>
     * See {@link #asyncExec}.
     *
     * @param	    r
     *		    the {@link NavRunnable} to run
     */
    public void asyncExecAndWait(final NavRunnable r)
	throws NavigationAbortedException, InvalidAddressException,
	MissingParameterException, InvalidParameterException,
        NavigationFailedException, EmptyNavigationStackException,
        RootNavigableNotControlException {

	if (isDispatchThread()) {
	    r.run();
	    return;
	}

	final boolean[] done = {false};
	final Throwable[] throwable = {null};

	asyncExec(
	    new Runnable() {
		@Override
		public void run() {
		    try {
			r.run();
		    } catch (Throwable t) {
			throwable[0] = t;
		    }
		    synchronized (done) {
			done[0] = true;
			done.notify();
		    }
		}
	    });

	// Sleep until nav thread is done
	synchronized (done) {
	    while (!done[0]) {
		try {
		    done.wait();
		} catch (InterruptedException ignore) {
		}
	    }
	}

	Throwable t = throwable[0];
	if (t != null) {
	    ThrowableUtil.appendStackTrace(t);

	    if (t instanceof NavigationAbortedException)
		throw (NavigationAbortedException)t;

	    if (t instanceof InvalidAddressException)
		throw (InvalidAddressException)t;

	    if (t instanceof MissingParameterException)
		throw (MissingParameterException)t;

	    if (t instanceof InvalidParameterException)
		throw (InvalidParameterException)t;

	    if (t instanceof NavigationFailedException)
		throw (NavigationFailedException)t;

	    if (t instanceof EmptyNavigationStackException)
		throw (EmptyNavigationStackException)t;

	    if (t instanceof RootNavigableNotControlException)
		throw (RootNavigableNotControlException)t;

	    if (t instanceof RuntimeException)
		throw (RuntimeException)t;

	    if (t instanceof Error)
		throw (Error)t;

	    // All Throwables should be accounted for
	    assert false;
	}
    }

    /**
     * Notifies all registered {@link NavigationListener}s that a navigation has
     * begun.
     */
    protected void fireNavigationStarted(NavigationStartEvent e) {
	listeners.navigationStarted(e);
    }

    /**
     * Notifies all registered {@link NavigationListener}s that a navigation has
     * stopped.
     */
    protected void fireNavigationStopped(NavigationStopEvent e) {
	listeners.navigationStopped(e);
    }

    /**
     * Returns the current {@link Control}, or {@code null} if the root element
     * of the navigation stack has not yet been set.
     */
    public Control getCurrentControl() {
	synchronized (stack) {
	    return stack.peekLast();
	}
    }

    /**
     * Gets a read-only wrapper around the list of elements of the current path,
     * with the root element at the beginning of the list.  The contents of the
     * returned list are live, and will change with subsequent navigations.
     */
    public List<Control> getPath() {
	return roStack;
    }

    /**
     * Gets the current path as a {@code String}.
     */
    public String getPathString() {
	return getPathString(stack);
    }

    /**
     * Navigates to the {@link Control} identified by the given path.
     *
     * @param	    cancel
     *		    {@code true} if the {@code Control}s, if any, that are
     *		    stopped as part of this navigation should be cancelled,
     *		    {@code false} otherwise; this parameter is passed along to
     *		    the {@link Control#stop} method
     *
     * @param	    relativeTo
     *		    a {@link Control} within the navigation stack to which
     *		    {@code path} is relative, or {@code null} if {@code path} is
     *		    absolute
     *
     * @param	    path
     *		    the path (relative to {@code relativeTo}), or unspecified to
     *		    navigate up the stack to {@code relativeTo}; if the root of
     *		    this {@code Navigator} has not yet been set, the first
     *		    element of this path <strong>must</strong> be a {@link
     *		    Control}
     *
     * @return	    a {@link Navigable} array that can be used to return to the
     *		    previously current {@link #getPath path} (with the first
     *		    element a {@link Control}, as required by the {@code path}
     *		    parameter of this method)
     *
     * @exception   NavigationAbortedException
     *		    if the navigation is vetoed
     *
     * @exception   InvalidAddressException
     *		    if some {@link Navigable} in {@code path} does not refer to
     *		    a valid {@link Control}
     *
     * @exception   MissingParameterException
     *		    if some {@link Control} in the process of navigation could
     *		    not be {@link Control#start started} due to a missing
     *		    initialization parameter
     *
     * @exception   InvalidParameterException
     *		    if some {@link Control} in the process of navigation could
     *		    not be {@link Control#start started} due to an invalid
     *		    initialization parameter
     *
     * @exception   NavigationFailedException
     *		    if a {@link Control} could not be started for some other
     *		    reason
     *
     * @exception   EmptyNavigationStackException
     *		    if the navigation stack is empty and the next {@link
     *		    Navigable} in {@code path} has an ID of {@link #PARENT_ID}
     *
     * @exception   RootNavigableNotControlException
     *		    if the navigation stack is empty and the next {@link
     *		    Navigable} in {@code path} is not a {@link Control}
     *
     * @exception   IllegalArgumentException
     *		    if {@code relativeTo} is not in the navigation stack
     */
    public Navigable[] goTo(boolean cancel, Control relativeTo,
	Navigable... path) throws NavigationAbortedException,
	InvalidAddressException, MissingParameterException,
	InvalidParameterException, NavigationFailedException,
	EmptyNavigationStackException, RootNavigableNotControlException {

	assert isDispatchThread();

	synchronized (stack) {
	    // The original path, before navigation
	    int n = stack.size();
	    Navigable[] last = new Navigable[n];
	    for (int i = 0; i < n; i++) {
		Control c = stack.get(i);
		last[i] = i == 0 ? c : new SimpleNavigable(
		    c.getId(), c.getName(), c.getParameters());
	    }

	    List<Control> stopped = new ArrayList<Control>();
	    List<Control> started = new ArrayList<Control>();
	    NavigationException exception = null;
	    boolean needStopEvent = false;

	    try {
		boolean done = false;
		while (!done) {
		    // Destination path (absolute)
		    LinkedList<Navigable> dPath = new LinkedList<Navigable>();

		    if (relativeTo != null) {
			dPath.addAll(stack);
			try {
			    // Remove path elements until relativeTo is at top
			    while (!((HasControl)dPath.getLast()).getControl().
				equals(relativeTo)) {
				dPath.removeLast();
			    }
			} catch (NoSuchElementException e) {
			    throw new IllegalArgumentException(String.format(
				"Control not in navigation path: %s (%s)",
				relativeTo.getClass().getName(),
				relativeTo.getId()));
			}
		    }

		    if (path.length != 0) {
			CollectionUtil.addAll(dPath, path);

			// Remove unnecessary ".." segments
			normalize(dPath);
		    }

		    List<Navigable> relPath = getRelativePath(stack, dPath);
		    if (!relPath.isEmpty()) {

			List<Navigable> roRelPath =
			    Collections.unmodifiableList(relPath);
			List<Navigable> roDPath =
			    Collections.unmodifiableList(dPath);
			NavigationStartEvent event =
			    new NavigationStartEvent(this, roDPath,
			    roRelPath);

			fireNavigationStarted(event);
			needStopEvent = true;

			// Iterate through relPath, adding/removing elements
			// to/from stack as appropriate
			for (Navigable nav : relPath) {
			    Control curControl = getCurrentControl();

			    if (nav.getId().equals(PARENT_ID)) {
				if (curControl == null) {
				    throw new EmptyNavigationStackException();
				}

				curControl.stop(cancel);
				stopped.add(curControl);
				stack.removeLast();
				descendantStopped(curControl);
			    } else {
				Control newControl;

				if (curControl == null) {
				    try {
					newControl = (Control)nav;
				    } catch (ClassCastException e) {
					throw new
					    RootNavigableNotControlException(
					    nav);
				    }
				} else {
				    String id = nav.getId();
				    newControl = curControl.getChildControl(id);

				    if (newControl == null) {
					Navigable[] array = stack.toArray(
					    new Navigable[stack.size()]);

					throw new InvalidAddressException(array,
					    nav);
				    }
				}

				Map<String, String> parameters =
				    nav.getParameters();
				if (parameters == null) {
				    parameters = Collections.emptyMap();
				}
				newControl.start(this, parameters);
				started.add(newControl);
				stack.add(newControl);
				descendantStarted();
			    }

			    if (System.getProperty("vpanels.debug.navigator") !=
				null) {
				System.out.printf("%s\n", getPathString());
			    }
			}
		    }

		    // Navigation is complete.	However, if the current
		    // Control's getForwardingPath returns a non-null value,
		    // invoke another round of navigation.
		    done = true;
		    Control curControl = getCurrentControl();
		    if (curControl != null) {
			Navigable[] forward = curControl.getForwardingPath(
			    !started.contains(curControl));
			if (forward != null && forward.length != 0) {
			    // Is this path absolute?
			    if (forward[0] == null) {
				relativeTo = null;
				path = new Navigable[forward.length - 1];
				System.arraycopy(forward, 1, path, 0,
				    path.length);
			    } else {
				relativeTo = curControl;
				path = forward;
			    }
			    done = false;
			}
		    }
		}
	    } catch (NavigationAbortedException e) {
		exception = e;
		throw e;

	    } catch (InvalidAddressException e) {
		exception = e;
		throw e;

	    } catch (MissingParameterException e) {
		exception = e;
		throw e;

	    } catch (InvalidParameterException e) {
		exception = e;
		throw e;

	    } catch (NavigationFailedException e) {
		exception = e;
		throw e;

	    } catch (EmptyNavigationStackException e) {
		exception = e;
		throw e;

	    } catch (RootNavigableNotControlException e) {
		exception = e;
		throw e;

	    } finally {
		if (needStopEvent) {
		    Navigable[] copy = Arrays.copyOf(last, last.length);
		    NavigationStopEvent event = new NavigationStopEvent(this,
			copy, Collections.unmodifiableList(stopped),
			Collections.unmodifiableList(started), exception);
		    fireNavigationStopped(event);
		}
	    }

	    return last;
	}
    }

    /**
     * Asynchronously navigates to the {@link Control} identified by the
     * given path.  A wrapper around {@link #goTo(boolean,Control,Navigable...)}
     * that is run asynchronously using {@link #asyncExec}.
     */
    public void goToAsync(final boolean cancel, final Control relativeTo,
	final Navigable... path) {
	asyncExec(
	    new Runnable() {
		@Override
		public void run() {
		    try {
			goTo(cancel, relativeTo, path);
		    } catch (NavigationException ignore) {
		    }
		}
	    });
    }

    /**
     * Asynchronously navigates to the {@link Control} identified by the given
     * path, returning only when navigation is complete.  A wrapper around
     * {@link #goTo(boolean,Control,Navigable...)} that is run asynchronously
     * using {@link #asyncExecAndWait}.
     */
    public void goToAsyncAndWait(final boolean cancel, final Control relativeTo,
	final Navigable... path) throws NavigationAbortedException,
	InvalidAddressException, MissingParameterException,
        InvalidParameterException, NavigationFailedException,
        EmptyNavigationStackException, RootNavigableNotControlException {

	asyncExecAndWait(
	    new NavRunnable() {
		@Override
		public void run()
		    throws NavigationAbortedException, InvalidAddressException,
		    MissingParameterException, InvalidParameterException,
		    NavigationFailedException, EmptyNavigationStackException,
		    RootNavigableNotControlException {

		    goTo(cancel, relativeTo, path);
		}
	    });
    }

    /**
     * Gets the {@link UITransitionManager} for this {@code Navigator}.
     */
    public UITransitionManager getUITransitionManager() {
	return manager;
    }

    /**
     * Determines whether the current thread is the navigation dispatch thread.
     * The navigation dispatch thread may change over time, but only one is
     * alive at a time.
     */
    public boolean isDispatchThread() {
	return Thread.currentThread() == dispatchThread;
    }

    /**
     * Removes a {@link NavigationListener} from notification of when navigation
     * is stopped and started.
     */
    public boolean removeNavigationListener(NavigationListener l) {
	return listeners.remove(l);
    }

    //
    // Private methods
    //

    private void descendantStarted() {
	int n = stack.size();
	for (int i = n - 2; i >= 0; i--) {
	    Control alert = stack.get(i);
	    Control[] path = new Control[n - i - 1];
	    for (int j = i + 1; j < n; j++) {
		path[j - i - 1] = stack.get(j);
	    }
	    alert.descendantStarted(path);
	}
    }

    private void descendantStopped(Control control) {
	int n = stack.size();
	for (int i = n - 1; i >= 0; i--) {
	    Control alert = stack.get(i);
	    Control[] path = new Control[n - i];
	    path[path.length - 1] = control;
	    for (int j = i + 1; j < n; j++) {
		path[j - i - 1] = stack.get(j);
	    }
	    alert.descendantStopped(path);
	}
    }

    /**
     * Gets the relative path between the given absolute paths.
     *
     * @param	    fromPath
     *		    an absolute source path
     *
     * @param	    toPath
     *		    an absolute destination path
     *
     * @return	    a relative path from the current path to the given path
     */
    private List<Navigable> getRelativePath(
	List<? extends Navigable> fromPath,
	List<? extends Navigable> toPath) {

	List<Navigable> rPath = new ArrayList<Navigable>();

	// Determine branching index
	int branch = 0;
	while (branch < fromPath.size() && branch < toPath.size() &&
	    Navigable.Util.equals(fromPath.get(branch), toPath.get(branch))) {

	    branch++;
	}

	for (int i = fromPath.size() - 1; i >= branch; i--) {
	    rPath.add(PARENT_NAVIGABLE);
	}

	for (int i = branch; i < toPath.size(); i++) {
	    rPath.add(toPath.get(i));
	}

	return rPath;
    }

    /**
     * Removes each ".." segment and preceding non-".." segment the given path.
     */
    private void normalize(List<? extends HasId> path) {
	for (int i = 1; i < path.size(); i++) {
	    if (path.get(i).getId().equals(PARENT_ID) &&
		!path.get(i - 1).getId().equals(PARENT_ID)) {
		path.remove(i--);
		path.remove(i--);
	    }
	}
    }

    //
    // Static methods
    //

    /**
     * Gets the given path as a {@code String}.
     */
    public static String getPathString(Iterable<? extends Navigable> path) {
	StringBuilder buffer = new StringBuilder();

	for (Navigable nav : path) {
	    buffer.append(PATH_SEPARATOR).append(Control.encode(
		nav.getId(), nav.getParameters()));
	}

	return buffer.toString();
    }

    /**
     * Determines whether the given path is absolute.  If the given path starts
     * with PATH_SEPARATOR, it is considered absolute.
     */
    public static boolean isAbsolute(String path) {
	return path.startsWith(PATH_SEPARATOR);
    }

    public static SimpleNavigable[] toArray(String path) {
	path = path.replaceFirst(
	    "^(" + Pattern.quote(PATH_SEPARATOR) + ")+", "");

	String[] parts = path.split(PATH_SEPARATOR, 0);
	SimpleNavigable[] elements = new SimpleNavigable[parts.length];

	for (int i = 0; i < parts.length; i++) {
	    elements[i] = Control.decode(parts[i]);
	}

	return elements;
    }
}
