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

package com.oracle.solaris.vp.panel.common.action;

import java.awt.event.ActionEvent;
import java.util.concurrent.*;
import javax.swing.*;
import com.oracle.solaris.vp.util.misc.*;

/**
 * The {@code StructuredAction} encapsulates an action that {@link #work
 * produces} an output ({@code O}) based optionally on {@link #getPresetInput
 * preset} ({@code P}) and {@link #getRuntimeInput runtime} ({@code I}) input.
 * <p/>
 * Invocation flow is as follows:
 * <p/>
 * <table>
 *   <tr><td align='center' colspan='3'>{@link #actionPerformed}</td></tr>
 *   <tr><td align='center' colspan='3'>&darr;</td></tr>
 *   <tr><td align='center' colspan='3'>{@link #asyncInvoke}</td></tr>
 *   <tr><td align='center' colspan='3'>&darr;</td></tr>
 *   <tr>
 *     <td align='center' colspan='3'>{@link #invoke(Object) invoke(I)}</td>
 *   </tr>
 *   <tr><td align='center' colspan='3'>&darr;</td></tr>
 *   <tr valign='top'>
 *     <td>
 *	 <table>
 *	   <tr><td align='center'>&darr;&uarr;</td></tr>
 *	   <tr><td align='center'>{@link #getPresetInput}</td></tr>
 *	 </table>
 *     </td>
 *     <td>
 *	 <table>
 *	   <tr><td align='center'>&darr;&uarr;</td></tr>
 *	   <tr><td align='center'>{@link #getRuntimeInput}</td></tr>
 *	 </table>
 *     </td>
 *     <td>
 *	 <table>
 *	   <tr><td align='center'>&darr;</td></tr>
 *	   <tr><td align='center'>{@link #work}</td></tr>
 *	 </table>
 *     </td>
 *   </tr>
 * </table>
 * <p/>
 * See the summaries of each to for a description of the features that each
 * method provides.
 * <p/>
 * A typical subclass will implement {@link #work}, and optionally {@link
 * #getRuntimeInput} if it needs to create or retrieve run-time data (like user
 * input) prior to running.
 * <p/>
 * Simpler implementations that don't require runtime input may override {@link
 * #invoke(Object) invoke(I)} instead.
 */
public class StructuredAction<P, I, O> extends AbstractAction {
    //
    // Instance data
    //

    private boolean loops;
    private P pInput;

    // Use a thread pool to invoke actions outside of the AWT event thread, and
    // to autmatically handle uncaught exceptions and queued requests
    protected final ThreadPoolExecutor threadPool;
    {
	String name = TextUtil.getBaseName(getClass()) + "-";
	ThreadFactory factory = new NamedThreadFactory(name);

	// Unbounded
	BlockingQueue<Runnable> queue = new LinkedBlockingQueue<Runnable>();

	// Use a thread pool with a single core thread to automatically handle
	// uncaught exceptions and queued requests.  Use a minuscule timeout so
	// that threads herein don't hold up shutdown of the JVM.
	threadPool = new ThreadPoolExecutor(
	    1, 1, 1, TimeUnit.NANOSECONDS, queue, factory);

	threadPool.allowCoreThreadTimeOut(true);
    }

    //
    // Constructors
    //

    /**
     * Constructs a {@code StructuredAction} with the given name and initial
     * preset input.
     */
    public StructuredAction(String text, P pInput) {
	putValue(Action.NAME, text);
	setPresetInput(pInput);
    }

    /**
     * Constructs a {@code StructuredAction} with the given name {@code null}
     * preset input.
     */
    public StructuredAction(String text) {
	this(text, null);
    }

    //
    // Action methods
    //

    /**
     * Calls {@link #asyncInvoke}.
     */
    @Override
    public void actionPerformed(ActionEvent e) {
	asyncInvoke();
    }

    //
    // StructuredAction methods
    //

    /**
     * Runs the given {@code Runnable} in this {@code
     * StructuredAction}'s thread pool.
     *
     * @param	    r
     *		    the {@code Runnable} to run
     */
    public void asyncExec(Runnable r) {
	threadPool.execute(r);
    }

    /**
     * Schedules a call to {@link #invoke(Object) invoke(I)} in this
     * {@code StructuredAction}'s thread pool, ignoring any resulting
     * {@link ActionAbortedException} or {@link ActionFailedException}.
     */
    public void asyncInvoke() {
	asyncInvoke(null);
    }

    protected void asyncInvoke(final I rtInput) {
	asyncExec(
	    new Runnable() {
		@Override
		public void run() {
		    try {
			invoke(rtInput);
		    } catch (ActionAbortedException ignore) {
		    } catch (ActionFailedException ignore) {
		    }
		}
	    });
    }

    /**
     * Gets whether this action loops repeatedly until cancelled or successful.
     * See {@link #invoke(Object) invoke(I)}.
     * <p\>
     * The default value is {@code false}.
     */
    public boolean getLoops() {
	return loops;
    }

    /**
     * Gets the preset input for this action.
     */
    public P getPresetInput() {
	return pInput;
    }

    /**
     * Retrieves any runtime data needed to perform this action.  In most cases
     * this input will come from the user.  This object is passed to {@link
     * #work} and its ilk.
     * <p\>
     * This default implementation does nothing and returns {@code null}.
     *
     * @param	    pInput
     *		    the preset input, set prior to the invocation of this action
     *
     * @param	    rtInput
     *		    the result from any previous invocations of this method
     *		    (from the context of a single invocation of {@link
     *		    #invoke}), or {@code null} if this method has not been
     *		    called yet
     *
     * @exception   ActionAbortedException
     *		    if this action is cancelled, presumably by the user
     */
    public I getRuntimeInput(P pInput, I rtInput)
	throws ActionAbortedException {

	return null;
    }

    /**
     * Calls {@link #invoke(Object) invoke(null)}.
     */
    public O invoke() throws ActionAbortedException, ActionFailedException {
	return invoke(null);
    }

    /**
     * Invokes this {@link StructuredAction} with the given initial input.  The
     * behavior of this method when this {@link StructuredAction} is not enabled
     * may be undefined.
     * <p/>
     * This implementation retrieves input from {@link #getRuntimeInput}, then
     * passes it on to {@link #work}.
     * <p/>
     * If the latter throws an {@link ActionFailedException} and {@link
     * #getLoops} returns:
     * <ul>
     *	 <li>
     *	   {@code true}: this process is repeated until cancelled via (an
     *	   {@link ActionAbortedException}) or successful
     *	 </li>
     *	 <li>
     *	   {@code false}: the {@link ActionFailedException} is rethrown
     *	 </li>
     * </ul>
     *
     * @param	    rtInput
     *		    an initial runtime input
     *
     * @return	    the value returned by {@link #work}
     *
     * @exception   ActionAbortedException
     *		    thrown by {@link #getRuntimeInput} or {@link #work}
     *
     * @exception   ActionFailedException
     *		    thrown by {@link #work}
     */
    protected O invoke(I rtInput)
	throws ActionAbortedException, ActionFailedException {

	P pInput = this.pInput;

	while (true) {
	    rtInput = getRuntimeInput(pInput, rtInput);

	    try {
		return work(pInput, rtInput);
	    } catch (ActionFailedException e) {
		if (!getLoops()) {
		    throw e;
		}
	    }
	}
    }

    /**
     * Updates this action's properties based on the preset input or other
     * criteria.  This default implementation does nothing.
     */
    public void refresh() {
    }

    /**
     * Sets whether this action loops repeatedly until cancelled or successful.
     * See {@link #invoke(Object) invoke(I)}.
     * <p\>
     * The default value is {@code false}.
     */
    protected void setLoops(boolean loops) {
	this.loops = loops;
    }

    /**
     * Sets the preset input for this action.  This value is passed by {@code
     * #invoke(Object) invoke(I)} to {@link #getRuntimeInput} and {@link #work}.
     */
    public void setPresetInput(P pInput) {
	this.pInput = pInput;
	refresh();
    }

    /**
     * Does the core work of this action.
     * <p\>
     * This default implementation does nothing and returns {@code null}.
     *
     * @param	    pInput
     *		    the preset input, set prior to the invocation of this action
     *
     * @param	    rtInput
     *		    data retrieved from {@link #getRuntimeInput}
     *
     * @return	    the output of this action, if any
     *
     * @exception   ActionAbortedException
     *		    if the action is cancelled
     *
     * @exception   ActionFailedException
     *		    if an error occurs
     */
    public O work(P pInput, I rtInput) throws ActionAbortedException,
	ActionFailedException {

	return null;
    }
}
