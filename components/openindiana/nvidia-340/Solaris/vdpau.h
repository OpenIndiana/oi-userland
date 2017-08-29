/*
 * This source file is documented using Doxygen markup.
 * See http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * This copyright notice applies to this header file:
 *
 * Copyright (c) 2008-2010 NVIDIA Corporation
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * \mainpage Video Decode and Presentation API for Unix
 *
 * \section intro Introduction
 *
 * The Video Decode and Presentation API for Unix (VDPAU) provides
 * a complete solution for decoding, post-processing, compositing,
 * and displaying compressed or uncompressed video streams. These
 * video streams may be combined (composited) with bitmap content,
 * to implement OSDs and other application user interfaces.
 *
 * \section api_partitioning API Partitioning
 *
 * VDPAU is split into two distinct modules:
 * - \ref api_core
 * - \ref api_winsys
 *
 * The intent is that most VDPAU functionality exists and
 * operates identically across all possible Windowing Systems.
 * This functionality is the \ref api_core.
 *
 * However, a small amount of functionality must be included that
 * is tightly coupled to the underlying Windowing System. This
 * functionality is the \ref api_winsys. Possibly examples
 * include:
 * - Creation of the initial VDPAU \ref VdpDevice "VdpDevice"
 *   handle, since this act requires intimate knowledge of the
 *   underlying Window System, such as specific display handle or
 *   driver identification.
 * - Conversion of VDPAU surfaces to/from underlying Window
 *   System surface types, e.g. to allow manipulation of
 *   VDPAU-generated surfaces via native Window System APIs.
 *
 * \section objects Object Types
 *
 * VDPAU is roughly object oriented; most functionality is
 * exposed by creating an object (handle) of a certain class
 * (type), then executing various functions against that handle.
 * The set of object classes supported, and their purpose, is
 * discussed below.
 *
 * \subsection device_type Device Type
 *
 * A \ref VdpDevice "VdpDevice" is the root object in VDPAU's
 * object system. The \ref api_winsys allows creation of a \ref
 * VdpDevice "VdpDevice" object handle, from which all other API
 * entry points can be retrieved and invoked.
 *
 * \subsection surface_types Surface Types
 *
 * A surface stores pixel information. Various types of surfaces
 * existing for different purposes:
 *
 * - \ref VdpVideoSurface "VdpVideoSurface"s store decompressed
 *   YCbCr video frames in an implementation-defined internal
 *   format.
 * - \ref VdpOutputSurface "VdpOutputSurface"s store RGB 4:4:4
 *   data. They are legal render targets for video
 *   post-processing and compositing operations.
 * - \ref VdpBitmapSurface "VdpBitmapSurface"s store RGB 4:4:4
 *   data. These surfaces are designed to contain read-only
 *   bitmap data, to be used for OSD or application UI
 *   compositing.
 *
 * \subsection transfer_types Transfer Types
 *
 * A data transfer object reads data from a surface (or
 * surfaces), processes it, and writes the result to another
 * surface. Various types of processing are possible:
 *
 * - \ref VdpDecoder "VdpDecoder" objects process compressed video
 *   data, and generate decompressed images.
 * - \ref VdpOutputSurface "VdpOutputSurface"s have their own \ref
 *   VdpOutputSurfaceRender "rendering functionality".
 * - \ref VdpVideoMixer "VdpVideoMixer" objects perform video
 *   post-processing, de-interlacing, and compositing.
 * - \ref VdpPresentationQueue "VdpPresentationQueue" is
 *   responsible for timestamp-based display of surfaces.
 *
 * \section data_flow Data Flow
 *
 * Compressed video data originates in the application's memory
 * space. This memory is typically obtained using \c malloc, and
 * filled via regular file or network read system calls.
 * Alternatively, the application may \c mmap a file.
 *
 * The compressed data is then processed using a \ref VdpDecoder
 * "VdpDecoder", which will decompress the field or frame,
 * and write the result into a \ref VdpVideoSurface
 * "VdpVideoSurface". This action may require reading pixel data
 * from some number of other \ref VdpVideoSurface "VdpVideoSurface"
 * objects, depending on the type of compressed data and
 * field/frame in question.
 *
 * If the application wishes to display any form of OSD or
 * user-interface, this must be created in a \ref
 * VdpOutputSurface "VdpOutputSurface".
 *
 * This process begins with the creation of \ref VdpBitmapSurface
 * "VdpBitmapSurface" objects to contain the OSD/UI's static data,
 * such as individual glyphs.
 *
 * \ref VdpOutputSurface "VdpOutputSurface" \ref
 * VdpOutputSurfaceRender "rendering functionality" may be used
 * to composite together various \ref VdpBitmapSurface
 * "VdpBitmapSurface"s and \ref VdpOutputSurface
 * "VdpOutputSurface"s, into another VdpOutputSurface
 * "VdpOutputSurface".
 *
 * Once video has been decoded, it must be post-processed. This
 * involves various steps such as color space conversion,
 * de-interlacing, and other video adjustments. This step is
 * performed using an \ref VdpVideoMixer "VdpVideoMixer" object.
 * This object can not only perform the aforementioned video
 * post-processing, but also composite the video with a number of
 * \ref VdpOutputSurface "VdpOutputSurface"s, thus allowing complex
 * user interfaces to be built. The final result is written into
 * another \ref VdpOutputSurface "VdpOutputSurface".
 *
 * Note that at this point, the resultant \ref VdpOutputSurface
 * "VdpOutputSurface" may be fed back through the above path,
 * either using \ref VdpOutputSurface "VdpOutputSurface" \ref
 * VdpOutputSurfaceRender "rendering functionality",
 * or as input to the \ref VdpVideoMixer "VdpVideoMixer" object.
 *
 * Finally, the resultant \ref VdpOutputSurface
 * "VdpOutputSurface" must be displayed on screen. This is the job
 * of the \ref VdpPresentationQueue "VdpPresentationQueue" object.
 *
 * \image html vdpau_data_flow.png
 *
 * \section entry_point_retrieval Entry Point Retrieval
 *
 * VDPAU is designed so that multiple implementations can be
 * used without application changes. For example, VDPAU could be
 * hosted on X11, or via direct GPU access.
 *
 * The key technology behind this is the use of function
 * pointers and a "get proc address" style API for all entry
 * points. Put another way, functions are not called directly
 * via global symbols set up by the linker, but rather through
 * pointers.
 *
 * In practical terms, the \ref api_winsys provides factory
 * functions which not only create and return \ref VdpDevice
 * "VdpDevice" objects, but also a function pointer to a \ref
 * VdpGetProcAddress function, through which all entry point
 * function pointers will be retrieved.
 *
 * \subsection entry_point_philosophy Philosophy
 *
 * It is entirely possible to envisage a simpler scheme whereby
 * such function pointers are hidden. That is, the application
 * would link against a wrapper library that exposed "real"
 * functions. The application would then call such functions
 * directly, by symbol, like any other function. The wrapper
 * library would handle loading the appropriate back-end, and
 * implementing a similar "get proc address" scheme internally.
 *
 * However, the above scheme does not work well in the context
 * of separated \ref api_core and \ref api_winsys. In this
 * scenario, one would require a separate wrapper library per
 * Window System, since each Window System would have a
 * different function name and prototype for the main factory
 * function. If an application then wanted to be Window System
 * agnostic (making final determination at run-time via some
 * form of plugin), it may then need to link against two
 * wrapper libraries, which would cause conflicts for all
 * symbols other than the main factory function.
 *
 * Another disadvantage of the wrapper library approach is the
 * extra level of function call required; the wrapper library
 * would internally implement the existing "get proc address"
 * and "function pointer" style dispatch anyway. Exposing this
 * directly to the application is slightly more efficient.
 *
 * \section threading Multi-threading
 *
 * All VDPAU functionality is fully thread-safe; any number of
 * threads may call into any VDPAU functions at any time. VDPAU
 * may not be called from signal-handlers.
 *
 * Note, however, that this simply guarantees that internal
 * VDPAU state will not be corrupted by thread usage, and that
 * crashes and deadlocks will not occur. Completely arbitrary
 * thread usage may not generate the results that an application
 * desires. In particular, care must be taken when multiple
 * threads are performing operations on the same VDPAU objects.
 *
 * VDPAU implementations guarantee correct flow of surface
 * content through the rendering pipeline, but only when
 * function calls that read from or write to a surface return to
 * the caller prior to any thread calling any other function(s)
 * that read from or write to the surface. Invoking multiple
 * reads from a surface in parallel is OK.
 *
 * Note that this restriction is placed upon VDPAU function
 * invocations, and specifically not upon any back-end
 * hardware's physical rendering operations. VDPAU
 * implementations are expected to internally synchronize such
 * hardware operations.
 *
 * In a single-threaded application, the above restriction comes
 * naturally; each function call completes before it is possible
 * to begin a new function call.
 *
 * In a multi-threaded application, threads may need to be
 * synchronized. For example, consider the situation where:
 *
 * - Thread 1 is parsing compressed video data, passing them
 *   through a \ref VdpDecoder "VdpDecoder" object, and filling a
 *   ring-buffer of \ref VdpVideoSurface "VdpVideoSurface"s
 * - Thread 2 is consuming those \ref VdpVideoSurface
 *   "VdpVideoSurface"s, and using a \ref VdpVideoMixer
 *   "VdpVideoMixer" to process them and composite them with UI.
 *
 * In this case, the threads must synchronize to ensure that
 * thread 1's call to \ref VdpDecoderRender has returned prior to
 * thread 2's call(s) to \ref VdpVideoMixerRender that use that
 * specific surface. This could be achieved using the following
 * pseudo-code:
 *
 * \code
 * Queue<VdpVideoSurface> q_full_surfaces;
 * Queue<VdpVideoSurface> q_empty_surfaces;
 *
 * thread_1() {
 *     for (;;) {
 *         VdpVideoSurface s = q_empty_surfaces.get();
 *         // Parse compressed stream here
 *         VdpDecoderRender(s, ...);
 *         q_full_surfaces.put(s);
 *     }
 * }
 *
 * // This would need to be more complex if
 * // VdpVideoMixerRender were to be provided with more
 * // than one field/frame at a time.
 * thread_2() {
 *     for (;;) {
 *         // Possibly, other rendering operations to mixer
 *         // layer surfaces here.
 *         VdpOutputSurface t = ...;
 *         VdpPresentationQueueBlockUntilSurfaceIdle(t);
 *         VdpVideoSurface s = q_full_surfaces.get();
 *         VdpVideoMixerRender(s, t, ...);
 *         q_empty_surfaces.put(s);
 *         // Possibly, other rendering operations to "t" here
 *         VdpPresentationQueueDisplay(t, ...);
 *     }
 * }
 * \endcode
 *
 * Finally, note that VDPAU makes no guarantees regarding any
 * level of parallelism in any given implementation. Put another
 * way, use of multi-threading is not guaranteed to yield any
 * performance gain, and in theory could even slightly reduce
 * performance due to threading/synchronization overhead.
 *
 * However, the intent of the threading requirements is to allow
 * for e.g. video decoding and video mixer operations to proceed
 * in parallel in hardware. Given a (presumably multi-threaded)
 * application that kept each portion of the hardware busy, this
 * would yield a performance increase.
 *
 * \section endianness Surface Endianness
 *
 * When dealing with surface content, i.e. the input/output of
 * Put/GetBits functions, applications must take care to access
 * memory in the correct fashion, so as to avoid endianness
 * issues.
 *
 * By established convention in the 3D graphics world, RGBA data
 * is defined to be an array of 32-bit pixels containing packed
 * RGBA components, not as an array of bytes or interleaved RGBA
 * components. VDPAU follows this convention. As such,
 * applications are expected to access such surfaces as arrays
 * of 32-bit components (i.e. using a 32-bit pointer), and not
 * as interleaved arrays of 8-bit components (i.e. using an
 * 8-bit pointer.) Deviation from this convention will lead to
 * endianness issues, unless appropriate care is taken.
 *
 * The same convention is followed for some packed YCbCr formats
 * such as \ref VDP_YCBCR_FORMAT_Y8U8V8A8; i.e. they are
 * considered arrays of 32-bit pixels, and hence should be
 * accessed as such.
 *
 * For YCbCr formats with chroma decimation and/or planar
 * formats, however, this convention is awkward. Therefore,
 * formats such as \ref VDP_YCBCR_FORMAT_NV12 are defined as
 * arrays of (potentially interleaved) byte-sized components.
 * Hence, applications should manipulate such data 8-bits at a
 * time, using 8-bit pointers.
 *
 * Note that one common usage for the input/output of
 * Put/GetBits APIs is file I/O. Typical file I/O APIs treat all
 * memory as a simple array of 8-bit values. This violates the
 * rule requiring surface data to be accessed in its true native
 * format. As such, applications may be required to solve
 * endianness issues. Possible solutions include:
 *
 * - Authoring static UI data files according to the endianness
 *   of the target execution platform.
 * - Conditionally byte-swapping Put/GetBits data buffers at
 *   run-time based on execution platform.
 *
 * Note: Complete details regarding each surface format's
 * precise pixel layout is included with the documentation of
 * each surface type. For example, see \ref
 * VDP_RGBA_FORMAT_B8G8R8A8.
 *
 * \section video_decoder_usage Video Decoder Usage
 *
 * VDPAU is a slice-level API. Put another way, VDPAU implementations accept
 * "slice" data from the bitstream, and perform all required processing of
 * those slices (e.g VLD decoding, IDCT, motion compensation, in-loop
 * deblocking, etc.).
 *
 * The client application is responsible for:
 *
 * - Extracting the slices from the bitstream (e.g. parsing/demultiplexing
 *   container formats, scanning the data to determine slice start positions
 *   and slice sizes).
 * - Parsing various bitstream headers/structures (e.g. sequence header,
 *   sequence parameter set, picture parameter set, entry point structures,
 *   etc.) Various fields from the parsed header structures needs to be
 *   provided to VDPAU alongside the slice bitstream in a "picture info"
 *   structure.
 * - Surface management (e.g. H.264 DPB processing, display re-ordering)
 *
 * It is recommended that applications pass solely the slice data to VDPAU;
 * specifically that any header data structures be excluded from the portion
 * of the bitstream passed to VDPAU. VDPAU implementations must operate
 * correctly if non-slice data is included, at least for formats employing
 * start codes to delimit slice data. However, any extra data may need
 * to be uploaded to hardware for parsing thus lowering performance, and/or,
 * in the worst case, may even overflow internal buffers that are sized solely
 * for slice data.
 *
 * The exact data that should be passed to VDPAU is detailed below for each
 * supported format:
 *
 * \subsection bitstream_mpeg1_mpeg2 MPEG-1 and MPEG-2
 *
 * Include all slices beginning with start codes 0x00000101 through
 * 0x000001AF. The slice start code must be included for all slices.
 *
 * \subsection bitstream_h264 H.264
 *
 * Include all NALs with nal_unit_type of 1 or 5 (coded slice of non-IDR/IDR
 * picture respectively). The complete slice start code (including 0x000001
 * prefix) must be included for all slices, even when the prefix is not
 * included in the bitstream.
 *
 * Note that if desired:
 *
 * - The slice start code prefix may be included in a separate bitstream
 *   buffer array entry to the actual slice data extracted from the bitstream.
 * - Multiple bitstream buffer array entries (e.g. one per slice) may point at
 *   the same physical data storage for the slice start code prefix.
 *
 * \subsection bitstream_vc1_sp_mp VC-1 Simple and Main Profile
 *
 * VC-1 simple/main profile bitstreams always consist of a single slice per
 * picture, and do not use start codes to delimit pictures. Instead, the
 * container format must indicate where each picture begins/ends.
 *
 * As such, no slice start codes should be included in the data passed to
 * VDPAU; simply pass in the exact data from the bitstream.
 *
 * Header information contained in the bitstream should be parsed by the
 * application and passed to VDPAU using the "picture info" data structure;
 * this header information explicitly must not be included in the bitstream
 * data passed to VDPAU for this encoding format.
 *
 * \subsection bitstream_vc1_ap VC-1 Advanced Profile
 *
 * Include all slices beginning with start codes 0x0000010D (frame),
 * 0x0000010C (field) or 0x0000010B (slice). The slice start code should be
 * included in all cases.
 *
 * Some VC-1 advanced profile streams do not contain slice start codes; again,
 * the container format must indicate where picture data begins and ends. In
 * this case, pictures are assumed to be progressive and to contain a single
 * slice. It is highly recommended that applications detect this condition,
 * and add the missing start codes to the bitstream passed to VDPAU. However,
 * VDPAU implementations must allow bitstreams with missing start codes, and
 * act as if a 0x0000010D (frame) start code had been present.
 *
 * Note that pictures containing multiple slices, or interlace streams, must
 * contain a complete set of slice start codes in the original bitstream;
 * without them, it is not possible to correctly parse and decode the stream.
 *
 * The bitstream passed to VDPAU should contain all original emulation
 * prevention bytes present in the original bitstream; do not remove these
 * from the bitstream.
 *
 * \subsection bitstream_mpeg4part2 MPEG-4 Part 2 and DivX
 *
 * Include all slices beginning with start codes 0x000001B6. The slice start
 * code must be included for all slices.
 *
 * \section video_mixer_usage Video Mixer Usage
 *
 * \subsection video_surface_content VdpVideoSurface Content
 *
 * Each \ref VdpVideoSurface "VdpVideoSurface" is expected to contain an
 * entire frame's-worth of data, irrespective of whether an interlaced of
 * progressive sequence is being decoded.
 *
 * Depending on the exact encoding structure of the compressed video stream,
 * the application may need to call \ref VdpDecoderRender twice to fill a
 * single \ref VdpVideoSurface "VdpVideoSurface". When the stream contains an
 * encoded progressive frame, or a "frame coded" interlaced field-pair, a
 * single \ref VdpDecoderRender call will fill the entire surface. When the
 * stream contains separately encoded interlaced fields, two
 * \ref VdpDecoderRender calls will be required; one for the top field, and
 * one for the bottom field.
 *
 * Implementation note: When \ref VdpDecoderRender renders an interlaced
 * field, this operation must not disturb the content of the other field in
 * the surface.
 *
 * \subsection vm_surf_list VdpVideoMixer Surface List
 *
 * An video stream is logically composed of a sequence of fields. An
 * example is shown below, in display order, assuming top field first:
 *
 * <pre>t0 b0 t1 b1 t2 b2 t3 b3 t4 b4 t5 b5 t6 b6 t7 b7 t8 b8 t9 b9</pre>
 *
 * The canonical usage is to call \ref VdpVideoMixerRender once for decoded
 * field, in display order, to yield one post-processed frame for display.
 *
 * For each call to \ref VdpVideoMixerRender, the field to be processed should
 * be provided as the \b video_surface_current parameter.
 *
 * To enable operation of advanced de-interlacing algorithms and/or
 * post-processing algorithms, some past and/or future surfaces should be
 * provided as context. These are provided in the \b video_surface_past and
 * \b video_surface_future lists. In general, these lists may contain any
 * number of surfaces. Specific implementations may have specific requirements
 * determining the minimum required number of surfaces for optimal operation,
 * and the maximum number of useful surfaces, beyond which surfaces are not
 * used. It is recommended that in all cases other than plain bob/weave, at
 * least 2 past and 1 future frame be provided.
 *
 * Note that it is entirely possible, in general, for any of the
 * \ref VdpVideoMixer "VdpVideoMixer" post-processing steps other than
 * de-interlacing to require access to multiple input fields/frames. For
 * example, an motion-sensitive noise-reduction algorithm.
 *
 * For example, when processing field t4, the \ref VdpVideoMixerRender
 * parameters may contain the following values, if the application chose to
 * provide 3 fields of context for both the past and future:
 *
 * <pre>
 * current_picture_structure: VDP_VIDEO_MIXER_PICTURE_STRUCTURE_TOP_FIELD
 * past:    [b3, t3, b2]
 * current: t4
 * future:  [b4, t5, b5]
 * </pre>
 *
 * Note that for both the past/future lists, array index 0 represents the
 * field temporally closest to current, in display order.
 *
 * The \ref VdpVideoMixerRender parameter \b current_picture_structure applies
 * to \b video_surface_current. The picture structure for the other surfaces
 * will be automatically derived from that for the current picture. The
 * derivation algorithm is extremely simple; the concatenated list
 * past/current/future is simply assumed to have an alternating top/bottom
 * pattern throughout.
 *
 * Continuing the example above, subsequent calls to \ref VdpVideoMixerRender
 * would provide the following sets of parameters:
 *
 * <pre>
 * current_picture_structure: VDP_VIDEO_MIXER_PICTURE_STRUCTURE_BOTTOM_FIELD
 * past:    [t4, b3, t3]
 * current: b4
 * future:  [t5, b5, t6]
 * </pre>
 *
 * then:
 *
 * <pre>
 * current_picture_structure: VDP_VIDEO_MIXER_PICTURE_STRUCTURE_TOP_FIELD
 * past:    [b4, t4, b3]
 * current: t5
 * future:  [b5, t6, b7]
 * </pre>
 *
 * In other words, the concatenated list of past/current/future frames simply
 * forms a window that slides through the sequence of decoded fields.
 *
 * It is syntactically legal for an application to choose not to provide a
 * particular entry in the past or future lists. In this case, the "slot" in
 * the surface list must be filled with the special value
 * \ref VDP_INVALID_HANDLE, to explicitly indicate that the picture is
 * missing; do not simply shuffle other surfaces together to fill in the gap.
 * Note that entries should only be omitted under special circumstances, such
 * as failed decode due to bitstream error during picture header parsing,
 * since missing entries will typically cause advanced de-interlacing
 * algorithms to experience significantly degraded operation.
 *
 * Specific examples for different de-interlacing types are presented below.
 *
 * \subsection deint_weave Weave De-interlacing
 *
 * Weave de-interlacing is the act of interleaving the lines of two temporally
 * adjacent fields to form a frame for display.
 *
 * To disable de-interlacing for progressive streams, simply specify
 * \b current_picture_structure as \ref VDP_VIDEO_MIXER_PICTURE_STRUCTURE_FRAME;
 * no de-interlacing will be applied.
 *
 * Weave de-interlacing for interlaced streams is identical to disabling
 * de-interlacing, as describe immediately above, because each
 * \ref VdpVideoSurface already contains an entire frame's worth (i.e. two
 * fields) of picture data.
 *
 * Inverse telecine is disabled when using weave de-interlacing.
 *
 * Weave de-interlacing produces one output frame for each input frame. The
 * application should make one \ref VdpVideoMixerRender call per pair of
 * decoded fields, or per decoded frame.
 *
 * Weave de-interlacing requires no entries in the past/future lists.
 *
 * All implementations must support weave de-interlacing.
 *
 * \subsection deint_bob Bob De-interlacing
 *
 * Bob de-interlacing is the act of vertically scaling a single field to the
 * size of a single frame.
 *
 * To achieve bob de-interlacing, simply provide a single field as
 * \b video_surface_current, and set \b current_picture_structure
 * appropriately, to indicate whether a top or bottom field was provided.
 *
 * Inverse telecine is disabled when using bob de-interlacing.
 *
 * Bob de-interlacing produces one output frame for each input field. The
 * application should make one \ref VdpVideoMixerRender call per decoded
 * field.
 *
 * Bob de-interlacing requires no entries in the past/future lists.
 *
 * Bob de-interlacing is the default when no advanced method is requested and
 * enabled. Advanced de-interlacing algorithms may fall back to bob e.g. when
 * required past/future fields are missing.
 *
 * All implementations must support bob de-interlacing.
 *
 * \subsection deint_adv Advanced De-interlacing
 *
 * Operation of both temporal and temporal-spatial de-interlacing is
 * identical; the only difference is the internal processing the algorithm
 * performs in generating the output frame.
 *
 * These algorithms use various advanced processing on the pixels of both the
 * current and various past/future fields in order to determine how best to
 * de-interlacing individual portions of the image.
 *
 * Inverse telecine may be enabled when using advanced de-interlacing.
 *
 * Advanced de-interlacing produces one output frame for each input field. The
 * application should make one \ref VdpVideoMixerRender call per decoded
 * field.
 *
 * Advanced de-interlacing requires entries in the past/future lists.
 *
 * Availability of advanced de-interlacing algorithms is implementation
 * dependent.
 *
 * \subsection deint_rate De-interlacing Rate
 *
 * For all de-interlacing algorithms except weave, a choice may be made to
 * call \ref VdpVideoMixerRender for either each decoded field, or every
 * second decoded field.
 *
 * If \ref VdpVideoMixerRender is called for every decoded field, the
 * generated post-processed frame rate is equal to the decoded field rate.
 * Put another way, the generated post-processed nominal field rate is equal
 * to 2x the decoded field rate. This is standard practice.
 *
 * If \ref VdpVideoMixerRender is called for every second decoded field (say
 * every top field), the generated post-processed frame rate is half to the
 * decoded field rate. This mode of operation is thus referred to as
 * "half-rate".
 *
 * Implementations may choose whether to support half-rate de-interlacing
 * or not. Regular full-rate de-interlacing should be supported by any
 * supported advanced de-interlacing algorithm.
 *
 * The descriptions of de-interlacing algorithms above assume that regular
 * (not half-rate) operation is being performed, when detailing the number of
 * VdpVideoMixerRender calls.
 *
 * Recall that the concatenation of past/current/future surface lists simply
 * forms a window into the stream of decoded fields. To achieve standard
 * de-interlacing, the window is slid through the list of decoded fields one
 * field at a time, and a call is made to \ref VdpVideoMixerRender for each
 * movement of the window. To achieve half-rate de-interlacing, the window is
 * slid through the* list of decoded fields two fields at a time, and a
 * call is made to \ref VdpVideoMixerRender for each movement of the window.
 *
 * \subsection invtc Inverse Telecine
 *
 * Assuming the implementation supports it, inverse telecine may be enabled
 * alongside any advanced de-interlacing algorithm. Inverse telecine is never
 * active for bob or weave.
 *
 * Operation of \ref VdpVideoMixerRender with inverse telecine active is
 * identical to the basic operation mechanisms describe above in every way;
 * all inverse telecine processing is performed internally to the
 * \ref VdpVideoMixer "VdpVideoMixer".
 *
 * In particular, there is no provision way for \ref VdpVideoMixerRender to
 * indicate when identical input fields have been observed, and consequently
 * identical output frames may have been produced.
 *
 * De-interlacing (and inverse telecine) may be applied to streams that are
 * marked as being progressive. This will allow detection of, and correct
 * de-interlacing of, mixed interlace/progressive streams, bad edits, etc.
 * To implement de-interlacing/inverse-telecine on progressive material,
 * simply treat the stream of decoded frames as a stream of decoded fields,
 * apply any telecine flags (see the next section), and then apply
 * de-interlacing to those fields as described above.
 *
 * Implementations are free to determine whether inverse telecine operates
 * in conjunction with half-rate de-interlacing or not. It should always
 * operate with regular de-interlacing, when advertized.
 *
 * \subsection tcflags Telecine (Pull-Down) Flags
 *
 * Some media delivery formats, e.g. DVD-Video, include flags that are
 * intended to modify the decoded field sequence before display. This allows
 * e.g. 24p content to be encoded at 48i, which saves space relative to a 60i
 * encoded stream, but still displayed at 60i, to match target consumer
 * display equipment.
 *
 * If the inverse telecine option is not activated in the
 * \ref VdpVideoMixer "VdpVideoMixer", these flags should be ignored, and the
 * decoded fields passed directly to \ref VdpVideoMixerRender as detailed
 * above.
 *
 * However, to make full use of the inverse telecine feature, these flags
 * should be applied to the field stream, yielding another field stream with
 * some repeated fields, before passing the field stream to
 * \ref VdpVideoMixerRender. In this scenario, the sliding window mentioned
 * in the descriptions above applies to the field stream after application of
 * flags.
 *
 * \section extending Extending the API
 *
 * \subsection extend_enums Enumerations and Other Constants
 *
 * VDPAU defines a number of enumeration types.
 *
 * When modifying VDPAU, existing enumeration constants must
 * continue to exist (although they may be deprecated), and do
 * so in the existing order.
 *
 * The above discussion naturally applies to "manually" defined
 * enumerations, using pre-processor macros, too.
 *
 * \subsection extend_structs Structures
 *
 * In most case, VDPAU includes no provision for modifying existing
 * structure definitions, although they may be deprecated.
 *
 * New structures may be created, together with new API entry
 * points or feature/attribute/parameter values, to expose new
 * functionality.
 *
 * A few structures are considered plausible candidates for future extension.
 * Such structures include a version number as the first field, indicating the
 * exact layout of the client-provided data. Such structures may only be
 * modified by adding new fields to the end of the structure, so that the
 * original structure definition is completely compatible with a leading
 * subset of fields of the extended structure.
 *
 * \subsection extend_functions Functions
 *
 * Existing functions may not be modified, although they may be
 * deprecated.
 *
 * New functions may be added at will. Note the enumeration
 * requirements when modifying the enumeration that defines the
 * list of entry points.
 *
 * \section preemption_note Display Preemption
 *
 * Please note that the display may be preempted away from
 * VDPAU at any time. See \ref display_preemption for more
 * details.
 *
 * \subsection trademarks Trademarks
 *
 * VDPAU is a trademark of NVIDIA Corporation. You may freely use the
 * VDPAU trademark, as long as trademark ownership is attributed to
 * NVIDIA Corporation.
 */

/**
 * \file vdpau.h
 * \brief The Core API
 *
 * This file contains the \ref api_core "Core API".
 */

#ifndef _VDPAU_H
#define _VDPAU_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup api_core Core API
 *
 * The core API encompasses all VDPAU functionality that operates
 * in the same fashion across all Window Systems.
 *
 * @{
 */

/**
 * \defgroup base_types Basic Types
 *
 * VDPAU primarily uses ISO C99 types from \c stdint.h.
 *
 * @{
 */

/** \brief A true \ref VdpBool value */
#define VDP_TRUE 1
/** \brief A false \ref VdpBool value */
#define VDP_FALSE 0
/**
 * \brief A boolean value, holding \ref VDP_TRUE or \ref
 * VDP_FALSE.
 */
typedef int VdpBool;

/*@}*/

/**
 * \defgroup misc_types Miscellaneous Types
 *
 * @{
 */

/**
 * \brief An invalid object handle value.
 *
 * This value may be used to represent an invalid, or
 * non-existent, object (\ref VdpDevice "VdpDevice",
 * \ref VdpVideoSurface "VdpVideoSurface", etc.)
 *
 * Note that most APIs require valid object handles in all
 * cases, and will fail when presented with this value.
 */
#define VDP_INVALID_HANDLE 0xffffffffU

/**
 * \brief The set of all chroma formats for \ref VdpVideoSurface
 * "VdpVideoSurface"s.
 */
typedef uint32_t VdpChromaType;

/** \hideinitializer \brief 4:2:0 chroma format. */
#define VDP_CHROMA_TYPE_420 (VdpChromaType)0
/** \hideinitializer \brief 4:2:2 chroma format. */
#define VDP_CHROMA_TYPE_422 (VdpChromaType)1
/** \hideinitializer \brief 4:4:4 chroma format. */
#define VDP_CHROMA_TYPE_444 (VdpChromaType)2

/**
 * \brief The set of all known YCbCr surface formats.
 */
typedef uint32_t VdpYCbCrFormat;

/**
 * \hideinitializer
 * \brief The "NV12" YCbCr surface format.
 *
 * This format has a two planes, a Y plane and a UV plane.
 *
 * The Y plane is an array of byte-sized Y components.
 * Applications should access this data via a uint8_t pointer.
 *
 * The UV plane is an array of interleaved byte-sized U and V
 * components, in the order U, V, U, V. Applications should
 * access this data via a uint8_t pointer.
 */
#define VDP_YCBCR_FORMAT_NV12     (VdpYCbCrFormat)0
/**
 * \hideinitializer
 * \brief The "YV12" YCbCr surface format.
 *
 * This format has a three planes, a Y plane, a V plane, and a U
 * plane.
 *
 * Each of the planes is an array of byte-sized components.
 *
 * Applications should access this data via a uint8_t pointer.
 */
#define VDP_YCBCR_FORMAT_YV12     (VdpYCbCrFormat)1
/**
 * \hideinitializer
 * \brief The "UYVY" YCbCr surface format.
 *
 * This format may also be known as Y422, UYNV, HDYC.
 *
 * This format has a single plane.
 *
 * This plane is an array of interleaved byte-sized Y, U, and V
 * components, in the order U, Y, V, Y, U, Y, V, Y.
 *
 * Applications should access this data via a uint8_t pointer.
 */
#define VDP_YCBCR_FORMAT_UYVY     (VdpYCbCrFormat)2
/**
 * \hideinitializer
 * \brief The "YUYV" YCbCr surface format.
 *
 * This format may also be known as YUY2, YUNV, V422.
 *
 * This format has a single plane.
 *
 * This plane is an array of interleaved byte-sized Y, U, and V
 * components, in the order Y, U, Y, V, Y, U, Y, V.
 *
 * Applications should access this data via a uint8_t pointer.
 */
#define VDP_YCBCR_FORMAT_YUYV     (VdpYCbCrFormat)3
/**
 * \hideinitializer
 * \brief A packed YCbCr format.
 *
 * This format has a single plane.
 *
 * This plane is an array packed 32-bit pixel data. Within each
 * 32-bit pixel, bits [31:24] contain A, bits [23:16] contain V,
 * bits [15:8] contain U, and bits [7:0] contain Y.
 *
 * Applications should access this data via a uint32_t pointer.
 */
#define VDP_YCBCR_FORMAT_Y8U8V8A8 (VdpYCbCrFormat)4
/**
 * \hideinitializer
 * \brief A packed YCbCr format.
 *
 * This format has a single plane.
 *
 * This plane is an array packed 32-bit pixel data. Within each
 * 32-bit pixel, bits [31:24] contain A, bits [23:16] contain Y,
 * bits [15:8] contain U, and bits [7:0] contain V.
 *
 * Applications should access this data via a uint32_t pointer.
 */
#define VDP_YCBCR_FORMAT_V8U8Y8A8 (VdpYCbCrFormat)5

/**
 * \brief  The set of all known RGB surface formats.
 */
typedef uint32_t VdpRGBAFormat;

/**
 * \hideinitializer
 * \brief A packed RGB format.
 *
 * This format has a single plane.
 *
 * This plane is an array packed 32-bit pixel data. Within each
 * 32-bit pixel, bits [31:24] contain A, bits [23:16] contain R,
 * bits [15:8] contain G, and bits [7:0] contain B.
 *
 * Applications should access this data via a uint32_t pointer.
 */
#define VDP_RGBA_FORMAT_B8G8R8A8    (VdpRGBAFormat)0
/**
 * \hideinitializer
 * \brief A packed RGB format.
 *
 * This format has a single plane.
 *
 * This plane is an array packed 32-bit pixel data. Within each
 * 32-bit pixel, bits [31:24] contain A, bits [23:16] contain B,
 * bits [15:8] contain G, and bits [7:0] contain R.
 *
 * Applications should access this data via a uint32_t pointer.
 */
#define VDP_RGBA_FORMAT_R8G8B8A8    (VdpRGBAFormat)1
/**
 * \hideinitializer
 * \brief A packed RGB format.
 *
 * This format has a single plane.
 *
 * This plane is an array packed 32-bit pixel data. Within each
 * 32-bit pixel, bits [31:30] contain A, bits [29:20] contain B,
 * bits [19:10] contain G, and bits [9:0] contain R.
 *
 * Applications should access this data via a uint32_t pointer.
 */
#define VDP_RGBA_FORMAT_R10G10B10A2 (VdpRGBAFormat)2
/**
 * \hideinitializer
 * \brief A packed RGB format.
 *
 * This format has a single plane.
 *
 * This plane is an array packed 32-bit pixel data. Within each
 * 32-bit pixel, bits [31:30] contain A, bits [29:20] contain R,
 * bits [19:10] contain G, and bits [9:0] contain B.
 *
 * Applications should access this data via a uint32_t pointer.
 */
#define VDP_RGBA_FORMAT_B10G10R10A2 (VdpRGBAFormat)3
/**
 * \hideinitializer
 * \brief An alpha-only surface format.
 *
 * This format has a single plane.
 *
 * This plane is an array of byte-sized components.
 *
 * Applications should access this data via a uint8_t pointer.
 */
#define VDP_RGBA_FORMAT_A8          (VdpRGBAFormat)4

/**
 * \brief  The set of all known indexed surface formats.
 */
typedef uint32_t VdpIndexedFormat;

/**
 * \hideinitializer
 * \brief A 4-bit indexed format, with alpha.
 *
 * This format has a single plane.
 *
 * This plane is an array of byte-sized components. Within each
 * byte, bits [7:4] contain I (index), and bits [3:0] contain A.
 *
 * Applications should access this data via a uint8_t pointer.
 */
#define VDP_INDEXED_FORMAT_A4I4 (VdpIndexedFormat)0
/**
 * \hideinitializer
 * \brief A 4-bit indexed format, with alpha.
 *
 * This format has a single plane.
 *
 * This plane is an array of byte-sized components. Within each
 * byte, bits [7:4] contain A, and bits [3:0] contain I (index).
 *
 * Applications should access this data via a uint8_t pointer.
 */
#define VDP_INDEXED_FORMAT_I4A4 (VdpIndexedFormat)1
/**
 * \hideinitializer
 * \brief A 8-bit indexed format, with alpha.
 *
 * This format has a single plane.
 *
 * This plane is an array of interleaved byte-sized A and I
 * (index) components, in the order A, I, A, I.
 *
 * Applications should access this data via a uint8_t pointer.
 */
#define VDP_INDEXED_FORMAT_A8I8 (VdpIndexedFormat)2
/**
 * \hideinitializer
 * \brief A 8-bit indexed format, with alpha.
 *
 * This format has a single plane.
 *
 * This plane is an array of interleaved byte-sized A and I
 * (index) components, in the order I, A, I, A.
 *
 * Applications should access this data via a uint8_t pointer.
 */
#define VDP_INDEXED_FORMAT_I8A8 (VdpIndexedFormat)3

/**
 * \brief A location within a surface.
 *
 * The VDPAU co-ordinate system has its origin at the top-left
 * of a surface, with x and y components increasing right and
 * down.
 */
typedef struct {
    /** X co-ordinate. */
    uint32_t x;
    /** Y co-ordinate. */
    uint32_t y;
} VdpPoint;

/**
 * \brief A rectangular region of a surface.
 *
 * The co-ordinates are top-left inclusive, bottom-right
 * exclusive.
 *
 * The VDPAU co-ordinate system has its origin at the top-left
 * of a surface, with x and y components increasing right and
 * down.
 */
typedef struct {
    /** Left X co-ordinate. Inclusive. */
    uint32_t x0;
    /** Top Y co-ordinate. Inclusive. */
    uint32_t y0;
    /** Right X co-ordinate. Exclusive. */
    uint32_t x1;
    /** Bottom Y co-ordinate. Exclusive. */
    uint32_t y1;
} VdpRect;

/**
 * A constant RGBA color.
 *
 * Note that the components are stored as float values in the
 * range 0.0...1.0 rather than format-specific integer values.
 * This allows VdpColor values to be independent from the exact
 * surface format(s) in use.
 */
typedef struct {
    float red;
    float green;
    float blue;
    float alpha;
} VdpColor;

/*@}*/

/**
 * \defgroup error_handling Error Handling
 *
 * @{
 */

/**
 * \hideinitializer
 * \brief The set of all possible error codes.
 */
typedef enum {
    /** The operation completed successfully; no error. */
    VDP_STATUS_OK = 0,
    /**
     * No backend implementation could be loaded.
     */
    VDP_STATUS_NO_IMPLEMENTATION,
    /**
     * The display was preempted, or a fatal error occurred.
     *
     * The application must re-initialize VDPAU.
     */
    VDP_STATUS_DISPLAY_PREEMPTED,
    /**
     * An invalid handle value was provided.
     *
     * Either the handle does not exist at all, or refers to an object of an
     * incorrect type.
     */
    VDP_STATUS_INVALID_HANDLE,
    /**
     * An invalid pointer was provided.
     *
     * Typically, this means that a NULL pointer was provided for an "output"
     * parameter.
     */
    VDP_STATUS_INVALID_POINTER,
    /**
     * An invalid/unsupported \ref VdpChromaType value was supplied.
     */
    VDP_STATUS_INVALID_CHROMA_TYPE,
    /**
     * An invalid/unsupported \ref VdpYCbCrFormat value was supplied.
     */
    VDP_STATUS_INVALID_Y_CB_CR_FORMAT,
    /**
     * An invalid/unsupported \ref VdpRGBAFormat value was supplied.
     */
    VDP_STATUS_INVALID_RGBA_FORMAT,
    /**
     * An invalid/unsupported \ref VdpIndexedFormat value was supplied.
     */
    VDP_STATUS_INVALID_INDEXED_FORMAT,
    /**
     * An invalid/unsupported \ref VdpColorStandard value was supplied.
     */
    VDP_STATUS_INVALID_COLOR_STANDARD,
    /**
     * An invalid/unsupported \ref VdpColorTableFormat value was supplied.
     */
    VDP_STATUS_INVALID_COLOR_TABLE_FORMAT,
    /**
     * An invalid/unsupported \ref VdpOutputSurfaceRenderBlendFactor value was
     * supplied.
     */
    VDP_STATUS_INVALID_BLEND_FACTOR,
    /**
     * An invalid/unsupported \ref VdpOutputSurfaceRenderBlendEquation value
     * was supplied.
     */
    VDP_STATUS_INVALID_BLEND_EQUATION,
    /**
     * An invalid/unsupported flag value/combination was supplied.
     */
    VDP_STATUS_INVALID_FLAG,
    /**
     * An invalid/unsupported \ref VdpDecoderProfile value was supplied.
     */
    VDP_STATUS_INVALID_DECODER_PROFILE,
    /**
     * An invalid/unsupported \ref VdpVideoMixerFeature value was supplied.
     */
    VDP_STATUS_INVALID_VIDEO_MIXER_FEATURE,
    /**
     * An invalid/unsupported \ref VdpVideoMixerParameter value was supplied.
     */
    VDP_STATUS_INVALID_VIDEO_MIXER_PARAMETER,
    /**
     * An invalid/unsupported \ref VdpVideoMixerAttribute value was supplied.
     */
    VDP_STATUS_INVALID_VIDEO_MIXER_ATTRIBUTE,
    /**
     * An invalid/unsupported \ref VdpVideoMixerPictureStructure value was
     * supplied.
     */
    VDP_STATUS_INVALID_VIDEO_MIXER_PICTURE_STRUCTURE,
    /**
     * An invalid/unsupported \ref VdpFuncId value was supplied.
     */
    VDP_STATUS_INVALID_FUNC_ID,
    /**
     * The size of a supplied object does not match the object it is being
     * used with.
     *
     * For example, a \ref VdpVideoMixer "VdpVideoMixer" is configured to
     * process \ref VdpVideoSurface "VdpVideoSurface" objects of a specific
     * size. If presented with a \ref VdpVideoSurface "VdpVideoSurface" of a
     * different size, this error will be raised.
     */
    VDP_STATUS_INVALID_SIZE,
    /**
     * An invalid/unsupported value was supplied.
     *
     * This is a catch-all error code for values of type other than those
     * with a specific error code.
     */
    VDP_STATUS_INVALID_VALUE,
    /**
     * An invalid/unsupported structure version was specified in a versioned
     * structure. This implies that the implementation is older than the
     * header file the application was built against.
     */
    VDP_STATUS_INVALID_STRUCT_VERSION,
    /**
     * The system does not have enough resources to complete the requested
     * operation at this time.
     */
    VDP_STATUS_RESOURCES,
    /**
     * The set of handles supplied are not all related to the same VdpDevice.
     *
     * When performing operations that operate on multiple surfaces, such as
     * \ref  VdpOutputSurfaceRenderOutputSurface or \ref VdpVideoMixerRender,
     * all supplied surfaces must have been created within the context of the
     * same \ref VdpDevice "VdpDevice" object. This error is raised if they were
     * not.
     */
    VDP_STATUS_HANDLE_DEVICE_MISMATCH,
    /**
     * A catch-all error, used when no other error code applies.
     */
    VDP_STATUS_ERROR,
} VdpStatus;

/**
 * \brief Retrieve a string describing an error code.
 * \param[in] status The error code.
 * \return A pointer to the string. Note that this is a
 *       statically allocated read-only string. As such, the
 *       application must not free the returned pointer. The
 *       pointer is valid as long as the VDPAU implementation is
 *       present within the application's address space.
 */
typedef char const * VdpGetErrorString(
    VdpStatus status
);

/*@}*/

/**
 * \defgroup versioning Versioning
 *
 *
 * @{
 */

/**
 * \brief The VDPAU interface version described by this header file.
 *
 * This version will only increase if a major incompatible change is made.
 * For example, if the parameters passed to an existing function are modified,
 * rather than simply adding new functions/enumerations), or if the mechanism
 * used to load the backend driver is modified incompatibly. Such changes are
 * unlikely.
 *
 * This value also represents the DSO version of VDPAU-related
 * shared-libraries.
 *
 * VDPAU version numbers are simple integers that increase monotonically
 * (typically by value 1).
 */
#define VDPAU_INTERFACE_VERSION 1

/**
 * \brief The VDPAU version described by this header file.
 *
 * This version will increase whenever any non-documentation change is made to
 * vdpau.h, or related header files such as vdpau_x11.h. Such changes
 * typically involve the addition of new functions, constants, or features.
 * Such changes are expected to be completely backwards-compatible.
 *
 * VDPAU version numbers are simple integers that increase monotonically
 * (typically by value 1).
 */
#define VDPAU_VERSION 1

/**
 * \brief Retrieve the VDPAU version implemented by the backend.
 * \param[out] api_version The API version.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpGetApiVersion(
    /* output parameters follow */
    uint32_t * api_version
);

/**
 * \brief Retrieve an implementation-specific string description
 *        of the implementation. This typically includes detailed version
 *        information.
 * \param[out] information_string A pointer to the information
 *       string. Note that this is a statically allocated
 *       read-only string. As such, the application must not
 *       free the returned pointer. The pointer is valid as long
 *       as the implementation is present within the
 *       application's address space.
 * \return VdpStatus The completion status of the operation.
 *
 * Note that the returned string is useful for information
 * reporting. It is not intended that the application should
 * parse this string in order to determine any information about
 * the implementation.
 */
typedef VdpStatus VdpGetInformationString(
    /* output parameters follow */
    char const * * information_string
);

/*@}*/

/**
 * \defgroup VdpDevice VdpDevice; Primary API object
 *
 * The VdpDevice is the root of the VDPAU object system. Using a
 * VdpDevice object, all other object types may be created. See
 * the sections describing those other object types for details
 * on object creation.
 *
 * Note that VdpDevice objects are created using the \ref
 * api_winsys.
 *
 * @{
 */

/**
 * \brief  An opaque handle representing a VdpDevice object.
 */
typedef uint32_t VdpDevice;

/**
 * \brief Destroy a VdpDevice.
 * \param[in] device The device to destroy.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpDeviceDestroy(
    VdpDevice device
);

/*@}*/

/**
 * \defgroup VdpCSCMatrix VdpCSCMatrix; CSC Matrix Manipulation
 *
 * When converting from YCbCr to RGB data formats, a color space
 * conversion operation must be performed. This operation is
 * parameterized using a "color space conversion matrix". The
 * VdpCSCMatrix is a data structure representing this
 * information.
 *
 * @{
 */

/**
 * \brief Storage for a color space conversion matrix.
 *
 * Note that the application may choose to construct the matrix
 * content by either:
 * - Directly filling in the fields of the CSC matrix
 * - Using the \ref VdpGenerateCSCMatrix helper function.
 *
 * The color space conversion equation is as follows:
 *
 * \f[
 * \left( \begin{array}{c} R \\ G \\ B \end{array} \right)
 * =
 * \left( \begin{array}{cccc}
 * m_{0,0} & m_{0,1} & m_{0,2} & m_{0,3} \\
 * m_{1,0} & m_{1,1} & m_{1,2} & m_{1,3} \\
 * m_{2,0} & m_{2,1} & m_{2,2} & m_{2,3}
 * \end{array}
 * \right)
 * *
 * \left( \begin{array}{c} Y \\ Cb \\ Cr \\ 1.0 \end{array}
 *      \right)
 * \f]
 */
typedef float VdpCSCMatrix[3][4];

#define VDP_PROCAMP_VERSION 0

/**
 * \brief Procamp operation parameterization data.
 *
 * When performing a color space conversion operation, various
 * adjustments can be performed at the same time, such as
 * brightness and contrast. This structure defines the level of
 * adjustments to make.
 */
typedef struct {
    /**
     * This field must be filled with VDP_PROCAMP_VERSION
     */
    uint32_t struct_version;
    /**
     * Brightness adjustment amount. A value clamped between
     * -1.0 and 1.0. 0.0 represents no modification.
     */
    float brightness;
    /**
     * Contrast adjustment amount. A value clamped between
     * 0.0 and 10.0. 1.0 represents no modification.
     */
    float contrast;
    /**
     * Saturation adjustment amount. A value clamped between 0.0 and
     * 10.0. 1.0 represents no modification.
     */
    float saturation;
    /**
     * Hue adjustment amount. A value clamped between
     * -PI and PI. 0.0 represents no modification.
     */
    float hue;
} VdpProcamp;

/**
 * \brief YCbCr color space specification.
 *
 * A number of YCbCr color spaces exist. This enumeration
 * defines the specifications known to VDPAU.
 */
typedef uint32_t VdpColorStandard;

/** \hideinitializer \brief ITU-R BT.601 */
#define VDP_COLOR_STANDARD_ITUR_BT_601 (VdpColorStandard)0
/** \hideinitializer \brief ITU-R BT.709 */
#define VDP_COLOR_STANDARD_ITUR_BT_709 (VdpColorStandard)1
/** \hideinitializer \brief SMPTE-240M */
#define VDP_COLOR_STANDARD_SMPTE_240M  (VdpColorStandard)2

/**
 * \brief Generate a color space conversion matrix
 * \param[in] procamp The procamp adjustments to make. If NULL,
 *        no adjustments will be made.
 * \param[in] standard The YCbCr color space to convert from.
 * \param[out] csc_matrix The CSC matrix to initialize.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpGenerateCSCMatrix(
    VdpProcamp *     procamp,
    VdpColorStandard standard,
    /* output parameters follow */
    VdpCSCMatrix *   csc_matrix
);

/*@}*/

/**
 * \defgroup VdpVideoSurface VdpVideoSurface; Video Surface object
 *
 * A VdpVideoSurface stores YCbCr data in an internal format,
 * with a variety of possible chroma sub-sampling options.
 *
 * A VdpVideoSurface may be filled with:
 * - Data provided by the CPU via \ref
 *   VdpVideoSurfacePutBitsYCbCr (i.e. software decode.)
 * - The result of applying a \ref VdpDecoder "VdpDecoder" to
 *   compressed video data.
 *
 * VdpVideoSurface content may be accessed by:
 * - The application via \ref VdpVideoSurfaceGetBitsYCbCr
 * - The Hardware that implements \ref VdpOutputSurface
 *   "VdpOutputSurface" \ref VdpOutputSurfaceRender
 *   "rendering functionality".
 * - The Hardware the implements \ref VdpVideoMixer
 *   "VdpVideoMixer" functionality.
 *
 * VdpVideoSurfaces are not directly displayable. They must be
 * converted into a displayable format using \ref VdpVideoMixer
 * "VdpVideoMixer" objects.
 *
 * See \ref video_mixer_usage for additional information.
 *
 * @{
 */

/**
 * \brief Query the implementation's VdpVideoSurface
 *        capabilities.
 * \param[in] device The device to query.
 * \param[in] surface_chroma_type The type of chroma type for
 *       which information is requested.
 * \param[out] is_supported Is this chroma type supported?
 * \param[out] max_width The maximum supported surface width for
 *       this chroma type.
 * \param[out] max_height The maximum supported surface height
 *       for this chroma type.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoSurfaceQueryCapabilities(
    VdpDevice     device,
    VdpChromaType surface_chroma_type,
    /* output parameters follow */
    VdpBool *     is_supported,
    uint32_t *    max_width,
    uint32_t *    max_height
);

/**
 * \brief Query the implementation's VdpVideoSurface
 *        GetBits/PutBits capabilities.
 * \param[in] device The device to query.
 * \param[in] surface_chroma_type The type of chroma type for
 *       which information is requested.
 * \param[in] bits_ycbcr_format The format of application "bits"
 *       buffer for which information is requested.
 * \param[out] is_supported Is this chroma type supported?
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoSurfaceQueryGetPutBitsYCbCrCapabilities(
    VdpDevice      device,
    VdpChromaType  surface_chroma_type,
    VdpYCbCrFormat bits_ycbcr_format,
    /* output parameters follow */
    VdpBool *      is_supported
);

/**
 * \brief An opaque handle representing a VdpVideoSurface
 *        object.
 */
typedef uint32_t VdpVideoSurface;

/**
 * \brief Create a VdpVideoSurface.
 * \param[in] device The device that will contain the surface.
 * \param[in] chroma_type The chroma type of the new surface.
 * \param[in] width The width of the new surface.
 * \param[in] height The height of the new surface.
 * \param[out] surface The new surface's handle.
 * \return VdpStatus The completion status of the operation.
 *
 * The memory backing the surface may not be initialized during
 * creation. Applications are expected to initialize any region
 * that they use, via \ref VdpDecoderRender or \ref
 * VdpVideoSurfacePutBitsYCbCr.
 *
 * Note that certain widths/heights are impossible for specific values of
 * chroma_type. For example, the definition of VDP_CHROMA_TYPE_420 implies
 * that the width must be even, since each single chroma sample covers two
 * luma samples horizontally. A similar argument applies to surface heights,
 * although doubly so, since interlaced pictures must be supported; each
 * field's height must itself be a multiple of 2. Hence the overall surface's
 * height must be a multiple of 4.
 *
 * Similar rules apply to other chroma_type values.
 *
 * Implementations may also impose additional restrictions on the surface
 * sizes they support, potentially requiring additional rounding of actual
 * surface sizes.
 *
 * In most cases, this is not an issue, since:
 * - Video streams are encoded as an array of macro-blocks, which typically
 *   have larger size alignment requirements than video surfaces do.
 * - APIs such as \ref VdpVideoMixerRender allow specification of a sub-region
 *   of the surface to read, which allows the padding data to be clipped away.
 *
 * However, other APIs such as \ref VdpVideoSurfaceGetBitsYCbCr and
 * \ref VdpVideoSurfacePutBitsYCbCr do not allow a sub-region to be specified,
 * and always operate on surface size that was actually allocated, rather
 * than the surface size that was requested. In this case, applications need
 * to be aware of the actual surface size, in order to allocate appropriately
 * sized buffers for the get-/put-bits operations.
 *
 * For this reason, applications may need to call
 * \ref VdpVideoSurfaceGetParameters after creation, in order to retrieve the
 * actual surface size.
 */
typedef VdpStatus VdpVideoSurfaceCreate(
    VdpDevice         device,
    VdpChromaType     chroma_type,
    uint32_t          width,
    uint32_t          height,
    /* output parameters follow */
    VdpVideoSurface * surface
);

/**
 * \brief Destroy a VdpVideoSurface.
 * \param[in] surface The surface's handle.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoSurfaceDestroy(
    VdpVideoSurface surface
);

/**
 * \brief Retrieve the parameters used to create a
 *        VdpVideoSurface.
 * \param[in] surface The surface's handle.
 * \param[out] chroma_type The chroma type of the surface.
 * \param[out] width The width of the surface.
 * \param[out] height The height of the surface.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoSurfaceGetParameters(
    VdpVideoSurface surface,
    /* output parameters follow */
    VdpChromaType * chroma_type,
    uint32_t *      width,
    uint32_t *      height
);

/**
 * \brief Copy image data from a VdpVideoSurface to application
 *        memory in a specified YCbCr format.
 * \param[in] surface The surface's handle.
 * \param[in] destination_ycbcr_format The format of the
 *       application's data buffers.
 * \param[in] destination_data Pointers to the application data
 *       buffers into which the image data will be written. Note
 *       that this is an array of pointers, one per plane. The
 *       destination_format parameter will define how many
 *       planes are required.
 * \param[in] destination_pitches Pointers to the pitch values
 *       for the application data buffers. Note that this is an
 *       array of pointers, one per plane. The
 *       destination_format parameter will define how many
 *       planes are required.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoSurfaceGetBitsYCbCr(
    VdpVideoSurface  surface,
    VdpYCbCrFormat   destination_ycbcr_format,
    void * const *   destination_data,
    uint32_t const * destination_pitches
);

/**
 * \brief Copy image data from application memory in a specific
 *        YCbCr format to a VdpVideoSurface.
 * \param[in] surface The surface's handle.
 * \param[in] source_ycbcr_format The format of the
 *       application's data buffers.
 * \param[in] source_data Pointers to the application data
 *       buffers from which the image data will be copied. Note
 *       that this is an array of pointers, one per plane. The
 *       source_format parameter will define how many
 *       planes are required.
 * \param[in] source_pitches Pointers to the pitch values
 *       for the application data buffers. Note that this is an
 *       array of pointers, one per plane. The
 *       source_format parameter will define how many
 *       planes are required.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoSurfacePutBitsYCbCr(
    VdpVideoSurface      surface,
    VdpYCbCrFormat       source_ycbcr_format,
    void const * const * source_data,
    uint32_t const *     source_pitches
);

/*@}*/

/**
 * \defgroup VdpOutputSurface VdpOutputSurface; Output Surface \
 * object
 *
 * A VdpOutputSurface stores RGBA data in a defined format.
 *
 * A VdpOutputSurface may be filled with:
 * - Data provided by the CPU via the various
 *   VdpOutputSurfacePutBits functions.
 * - Using the VdpOutputSurface \ref VdpOutputSurfaceRender
 *   "rendering functionality".
 * - Using a \ref VdpVideoMixer "VdpVideoMixer" object.
 *
 * VdpOutputSurface content may be accessed by:
 * - The application via the various VdpOutputSurfaceGetBits
 *   functions.
 * - The Hardware that implements VdpOutputSurface
 *   \ref VdpOutputSurfaceRender "rendering functionality".
 * - The Hardware the implements \ref VdpVideoMixer
 *   "VdpVideoMixer" functionality.
 * - The Hardware that implements \ref VdpPresentationQueue
 *   "VdpPresentationQueue" functionality,
 *
 * VdpVideoSurfaces are directly displayable using a \ref
 * VdpPresentationQueue "VdpPresentationQueue" object.
 *
 * @{
 */

/**
 * \brief The set of all known color table formats, for use with
 * \ref VdpOutputSurfacePutBitsIndexed.
 */
typedef uint32_t VdpColorTableFormat;

/**
 * \hideinitializer
 * \brief 8-bit per component packed into 32-bits
 *
 * This format is an array of packed 32-bit RGB color values.
 * Bits [31:24] are unused, bits [23:16] contain R, bits [15:8]
 * contain G, and bits [7:0] contain B. Note: The format is
 * physically an array of uint32_t values, and should be accessed
 * as such by the application in order to avoid endianness
 * issues.
 */
#define VDP_COLOR_TABLE_FORMAT_B8G8R8X8 (VdpColorTableFormat)0

/**
 * \brief Query the implementation's VdpOutputSurface
 *        capabilities.
 * \param[in] device The device to query.
 * \param[in] surface_rgba_format The surface format for
 *       which information is requested.
 * \param[out] is_supported Is this surface format supported?
 * \param[out] max_width The maximum supported surface width for
 *       this chroma type.
 * \param[out] max_height The maximum supported surface height
 *       for this chroma type.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpOutputSurfaceQueryCapabilities(
    VdpDevice     device,
    VdpRGBAFormat surface_rgba_format,
    /* output parameters follow */
    VdpBool *     is_supported,
    uint32_t *    max_width,
    uint32_t *    max_height
);

/**
 * \brief Query the implementation's capability to perform a
 *        PutBits operation using application data matching the
 *        surface's format.
 * \param[in] device The device to query.
 * \param[in] surface_rgba_format The surface format for
 *       which information is requested.
 * \param[out] is_supported Is this surface format supported?
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpOutputSurfaceQueryGetPutBitsNativeCapabilities(
    VdpDevice     device,
    VdpRGBAFormat surface_rgba_format,
    /* output parameters follow */
    VdpBool *     is_supported
);

/**
 * \brief Query the implementation's capability to perform a
 *        PutBits operation using application data in a specific
 *        indexed format.
 * \param[in] device The device to query.
 * \param[in] surface_rgba_format The surface format for
 *       which information is requested.
 * \param[in] bits_indexed_format The format of the application
 *       data buffer.
 * \param[in] color_table_format The format of the color lookup
 *       table.
 * \param[out] is_supported Is this surface format supported?
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpOutputSurfaceQueryPutBitsIndexedCapabilities(
    VdpDevice           device,
    VdpRGBAFormat       surface_rgba_format,
    VdpIndexedFormat    bits_indexed_format,
    VdpColorTableFormat color_table_format,
    /* output parameters follow */
    VdpBool *           is_supported
);

/**
 * \brief Query the implementation's capability to perform a
 *        PutBits operation using application data in a specific
 *        YCbCr/YUB format.
 * \param[in] device The device to query.
 * \param[in] surface_rgba_format The surface format for which
 *       information is requested.
 * \param[in] bits_ycbcr_format The format of the application
 *       data buffer.
 * \param[out] is_supported Is this surface format supported?
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpOutputSurfaceQueryPutBitsYCbCrCapabilities(
    VdpDevice      device,
    VdpRGBAFormat  surface_rgba_format,
    VdpYCbCrFormat bits_ycbcr_format,
    /* output parameters follow */
    VdpBool *      is_supported
);

/**
 * \brief An opaque handle representing a VdpOutputSurface
 *        object.
 */
typedef uint32_t VdpOutputSurface;

/**
 * \brief Create a VdpOutputSurface.
 * \param[in] device The device that will contain the surface.
 * \param[in] rgba_format The format of the new surface.
 * \param[in] width The width of the new surface.
 * \param[in] height The height of the new surface.
 * \param[out] surface The new surface's handle.
 * \return VdpStatus The completion status of the operation.
 *
 * The memory backing the surface will be initialized to 0 color
 * and 0 alpha (i.e. black.)
 */
typedef VdpStatus VdpOutputSurfaceCreate(
    VdpDevice          device,
    VdpRGBAFormat      rgba_format,
    uint32_t           width,
    uint32_t           height,
    /* output parameters follow */
    VdpOutputSurface * surface
);

/**
 * \brief Destroy a VdpOutputSurface.
 * \param[in] surface The surface's handle.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpOutputSurfaceDestroy(
    VdpOutputSurface surface
);

/**
 * \brief Retrieve the parameters used to create a
 *        VdpOutputSurface.
 * \param[in] surface The surface's handle.
 * \param[out] rgba_format The format of the surface.
 * \param[out] width The width of the surface.
 * \param[out] height The height of the surface.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpOutputSurfaceGetParameters(
    VdpOutputSurface surface,
    /* output parameters follow */
    VdpRGBAFormat *  rgba_format,
    uint32_t *       width,
    uint32_t *       height
);

/**
 * \brief Copy image data from a VdpOutputSurface to application
 *        memory in the surface's native format.
 * \param[in] surface The surface's handle.
 * \param[in] source_rect The sub-rectangle of the source
 *       surface to copy. If NULL, the entire surface will be
 *       retrieved.
 * \param[in] destination_data Pointers to the application data
 *       buffers into which the image data will be written. Note
 *       that this is an array of pointers, one per plane. The
 *       destination_format parameter will define how many
 *       planes are required.
 * \param[in] destination_pitches Pointers to the pitch values
 *       for the application data buffers. Note that this is an
 *       array of pointers, one per plane. The
 *       destination_format parameter will define how many
 *       planes are required.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpOutputSurfaceGetBitsNative(
    VdpOutputSurface surface,
    VdpRect const *  source_rect,
    void * const *   destination_data,
    uint32_t const * destination_pitches
);

/**
 * \brief Copy image data from application memory in the
 *        surface's native format to a VdpOutputSurface.
 * \param[in] surface The surface's handle.
 * \param[in] source_data Pointers to the application data
 *       buffers from which the image data will be copied. Note
 *       that this is an array of pointers, one per plane. The
 *       source_format parameter will define how many
 *       planes are required.
 * \param[in] source_pitches Pointers to the pitch values
 *       for the application data buffers. Note that this is an
 *       array of pointers, one per plane. The
 *       source_format parameter will define how many
 *       planes are required.
 * \param[in] destination_rect The sub-rectangle of the surface
 *       to fill with application data. If NULL, the entire
 *       surface will be updated.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpOutputSurfacePutBitsNative(
    VdpOutputSurface     surface,
    void const * const * source_data,
    uint32_t const *     source_pitches,
    VdpRect const *      destination_rect
);

/**
 * \brief Copy image data from application memory in a specific
 *        indexed format to a VdpOutputSurface.
 * \param[in] surface The surface's handle.
 * \param[in] source_indexed_format The format of the
 *       application's data buffers.
 * \param[in] source_data Pointers to the application data
 *       buffers from which the image data will be copied. Note
 *       that this is an array of pointers, one per plane. The
 *       source_indexed_format parameter will define how many
 *       planes are required.
 * \param[in] source_pitches Pointers to the pitch values
 *       for the application data buffers. Note that this is an
 *       array of pointers, one per plane. The
 *       source_indexed_format parameter will define how many
 *       planes are required.
 * \param[in] destination_rect The sub-rectangle of the surface
 *       to fill with application data. If NULL, the entire
 *       surface will be updated.
 * \param[in] color_table_format The format of the color_table.
 * \param[in] color_table A table that maps between source index
 *       and target color data. See \ref VdpColorTableFormat for
 *       details regarding the memory layout.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpOutputSurfacePutBitsIndexed(
    VdpOutputSurface     surface,
    VdpIndexedFormat     source_indexed_format,
    void const * const * source_data,
    uint32_t const *     source_pitch,
    VdpRect const *      destination_rect,
    VdpColorTableFormat  color_table_format,
    void const *         color_table
);

/**
 * \brief Copy image data from application memory in a specific
 *        YCbCr format to a VdpOutputSurface.
 * \param[in] surface The surface's handle.
 * \param[in] source_ycbcr_format The format of the
 *       application's data buffers.
 * \param[in] source_data Pointers to the application data
 *       buffers from which the image data will be copied. Note
 *       that this is an array of pointers, one per plane. The
 *       source_ycbcr_format parameter will define how many
 *       planes are required.
 * \param[in] source_pitches Pointers to the pitch values
 *       for the application data buffers. Note that this is an
 *       array of pointers, one per plane. The
 *       source_ycbcr_format parameter will define how many
 *       planes are required.
 * \param[in] destination_rect The sub-rectangle of the surface
 *       to fill with application data. If NULL, the entire
 *       surface will be updated.
 * \param[in] csc_matrix The color space conversion matrix used
 *       by the copy operation. If NULL, a default matrix will
 *       be used internally. Th default matrix is equivalent to
 *       ITU-R BT.601 with no procamp changes.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpOutputSurfacePutBitsYCbCr(
    VdpOutputSurface     surface,
    VdpYCbCrFormat       source_ycbcr_format,
    void const * const * source_data,
    uint32_t const *     source_pitches,
    VdpRect const *      destination_rect,
    VdpCSCMatrix const * csc_matrix
);

/*@}*/

/**
 * \defgroup VdpBitmapSurface VdpBitmapSurface; Bitmap Surface \
 * object
 *
 * A VdpBitmapSurface stores RGBA data in a defined format.
 *
 * A VdpBitmapSurface may be filled with:
 * - Data provided by the CPU via the \ref
 *   VdpBitmapSurfacePutBitsNative function.
 *
 * VdpBitmapSurface content may be accessed by:
 * - The Hardware that implements \ref VdpOutputSurface
 *   "VdpOutputSurface" \ref VdpOutputSurfaceRender
 *   "rendering functionality"
 *
 * VdpBitmapSurface objects are intended to store static read-only data, such
 * as font glyphs, and the bitmaps used to compose an applications'
 * user-interface.
 *
 * The primary differences between VdpBitmapSurfaces and
 * \ref VdpOutputSurface "VdpOutputSurface"s are:
 *
 * - You cannot render to a VdpBitmapSurface, just upload native data via
 *   the PutBits API.
 *
 * - The read-only nature of a VdpBitmapSurface gives the implementation more
 *   flexibility in its choice of data storage location for the bitmap data.
 *   For example, some implementations may choose to store some/all
 *   VdpBitmapSurface objects in system memory to relieve GPU memory pressure.
 *
 * - VdpBitmapSurface and VdpOutputSurface may support different subsets of all
 *   known RGBA formats.
 *
 * @{
 */

/**
 * \brief Query the implementation's VdpBitmapSurface
 *        capabilities.
 * \param[in] device The device to query.
 * \param[in] surface_rgba_format The surface format for
 *       which information is requested.
 * \param[out] is_supported Is this surface format supported?
 * \param[out] max_width The maximum supported surface width for
 *       this chroma type.
 * \param[out] max_height The maximum supported surface height
 *       for this chroma type.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpBitmapSurfaceQueryCapabilities(
    VdpDevice     device,
    VdpRGBAFormat surface_rgba_format,
    /* output parameters follow */
    VdpBool *     is_supported,
    uint32_t *    max_width,
    uint32_t *    max_height
);

/**
 * \brief An opaque handle representing a VdpBitmapSurface
 *        object.
 */
typedef uint32_t VdpBitmapSurface;

/**
 * \brief Create a VdpBitmapSurface.
 * \param[in] device The device that will contain the surface.
 * \param[in] rgba_format The format of the new surface.
 * \param[in] width The width of the new surface.
 * \param[in] height The height of the new surface.
 * \param[in] frequently_accessed Is this bitmap used
 *       frequently, or infrequently, by compositing options?
 *       Implementations may use this as a hint to determine how
 *       to allocate the underlying storage for the surface.
 * \param[out] surface The new surface's handle.
 * \return VdpStatus The completion status of the operation.
 *
 * The memory backing the surface may not be initialized
 * during creation. Applications are expected initialize any
 * region that they use, via \ref VdpBitmapSurfacePutBitsNative.
 */
typedef VdpStatus VdpBitmapSurfaceCreate(
    VdpDevice          device,
    VdpRGBAFormat      rgba_format,
    uint32_t           width,
    uint32_t           height,
    VdpBool            frequently_accessed,
    /* output parameters follow */
    VdpBitmapSurface * surface
);

/**
 * \brief Destroy a VdpBitmapSurface.
 * \param[in] surface The surface's handle.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpBitmapSurfaceDestroy(
    VdpBitmapSurface surface
);

/**
 * \brief Retrieve the parameters used to create a
 *        VdpBitmapSurface.
 * \param[in] surface The surface's handle.
 * \param[out] rgba_format The format of the surface.
 * \param[out] width The width of the surface.
 * \param[out] height The height of the surface.
 * \param[out] frequently_accessed The frequently_accessed state
 *       of the surface.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpBitmapSurfaceGetParameters(
    VdpBitmapSurface surface,
    /* output parameters follow */
    VdpRGBAFormat *  rgba_format,
    uint32_t *       width,
    uint32_t *       height,
    VdpBool *        frequently_accessed
);

/**
 * \brief Copy image data from application memory in the
 *        surface's native format to a VdpBitmapSurface.
 * \param[in] surface The surface's handle.
 * \param[in] source_data Pointers to the application data
 *       buffers from which the image data will be copied. Note
 *       that this is an array of pointers, one per plane. The
 *       source_format parameter will define how many
 *       planes are required.
 * \param[in] source_pitches Pointers to the pitch values
 *       for the application data buffers. Note that this is an
 *       array of pointers, one per plane. The
 *       source_format parameter will define how many
 *       planes are required.
 * \param[in] destination_rect The sub-rectangle of the surface
 *       to fill with application data. If NULL, the entire
 *       surface will be updated.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpBitmapSurfacePutBitsNative(
    VdpBitmapSurface     surface,
    void const * const * source_data,
    uint32_t const *     source_pitches,
    VdpRect const *      destination_rect
);

/*@}*/

/**
 * \defgroup VdpOutputSurfaceRender VdpOutputSurface Rendering \
 *           Functionality
 *
 * \ref VdpOutputSurface "VdpOutputSurface" objects
 * directly provide some rendering/compositing operations. These
 * are described below.
 *
 * @{
 */

/**
 * \hideinitializer
 * \brief The blending equation factors.
 */
typedef enum {
    VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_ZERO                     = 0,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_ONE                      = 1,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_SRC_COLOR                = 2,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_ONE_MINUS_SRC_COLOR      = 3,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_SRC_ALPHA                = 4,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA      = 5,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_DST_ALPHA                = 6,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_ONE_MINUS_DST_ALPHA      = 7,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_DST_COLOR                = 8,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_ONE_MINUS_DST_COLOR      = 9,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_SRC_ALPHA_SATURATE       = 10,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_CONSTANT_COLOR           = 11,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR = 12,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_CONSTANT_ALPHA           = 13,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA = 14,
} VdpOutputSurfaceRenderBlendFactor;

/**
 * \hideinitializer
 * \brief The blending equations.
 */
typedef enum {
    VDP_OUTPUT_SURFACE_RENDER_BLEND_EQUATION_SUBTRACT         = 0,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_EQUATION_REVERSE_SUBTRACT = 1,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_EQUATION_ADD              = 2,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_EQUATION_MIN              = 3,
    VDP_OUTPUT_SURFACE_RENDER_BLEND_EQUATION_MAX              = 4,
} VdpOutputSurfaceRenderBlendEquation;

#define VDP_OUTPUT_SURFACE_RENDER_BLEND_STATE_VERSION 0

/**
 * \brief Complete blending operation definition.
 *
 * A "blend state" operation controls the math behind certain rendering
 * operations.
 *
 * The blend math is the familiar OpenGL blend math:
 *     \f[
 *     dst.a = equation(blendFactorDstAlpha*dst.a,
 *     blendFactorSrcAlpha*src.a);
 *     \f]
 *     \f[
 *     dst.rgb = equation(blendFactorDstColor*dst.rgb,
 *     blendFactorSrcColor*src.rgb);
 *     \f]
 *
 * Note that when equation is MIN or MAX, the blend factors and constants
 * are ignored, and are treated as if they were 1.0.
 */
typedef struct {
    /**
     * This field must be filled with VDP_OUTPUT_SURFACE_RENDER_BLEND_STATE_VERSIION
     */
    uint32_t struct_version;
    VdpOutputSurfaceRenderBlendFactor   blend_factor_source_color;
    VdpOutputSurfaceRenderBlendFactor   blend_factor_destination_color;
    VdpOutputSurfaceRenderBlendFactor   blend_factor_source_alpha;
    VdpOutputSurfaceRenderBlendFactor   blend_factor_destination_alpha;
    VdpOutputSurfaceRenderBlendEquation blend_equation_color;
    VdpOutputSurfaceRenderBlendEquation blend_equation_alpha;
    VdpColor                            blend_constant;
} VdpOutputSurfaceRenderBlendState;

/**
 * \hideinitializer
 * \brief Do not rotate source_surface prior to compositing.
 */
#define VDP_OUTPUT_SURFACE_RENDER_ROTATE_0   0

/**
 * \hideinitializer
 * \brief Rotate source_surface 90 degrees clockwise prior to
 *        compositing.
 */
#define VDP_OUTPUT_SURFACE_RENDER_ROTATE_90  1

/**
 * \hideinitializer
 * \brief Rotate source_surface 180 degrees prior to
 *        compositing.
 */
#define VDP_OUTPUT_SURFACE_RENDER_ROTATE_180 2

/**
 * \hideinitializer
 * \brief Rotate source_surface 270 degrees clockwise prior to
 *        compositing.
 */
#define VDP_OUTPUT_SURFACE_RENDER_ROTATE_270 3

/**
 * \hideinitializer
 * \brief A separate color is used for each vertex of the
 *        smooth-shaded quad. Hence, colors array contains 4
 *        elements rather than 1. See description of colors
 *        array.
 */
#define VDP_OUTPUT_SURFACE_RENDER_COLOR_PER_VERTEX (1 << 2)

/**
 * \brief Composite a sub-rectangle of a \ref VdpOutputSurface
 *        "VdpOutputSurface" into a sub-rectangle of another
 *        \ref VdpOutputSurface VdpOutputSurface.
 * \param[in] destination_surface The destination surface of the
 *       compositing operation.
 * \param[in] destination_rect The sub-rectangle of the
 *       destination surface to update. If NULL, the entire
 *       destination surface will be updated.
 * \param[in] source_surface The source surface for the
 *       compositing operation. The surface is treated as having
 *       four components: red, green, blue and alpha. Any
 *       missing components are treated as 1.0. For example, for
 *       an A8 VdpOutputSurface, alpha will come from the surface
 *       but red, green and blue will be treated as 1.0. If
 *       source_surface is NULL, all components will be treated
 *       as 1.0. Note that destination_surface and
 *       source_surface must have been allocated via the same
 *       \ref VdpDevice "VdpDevice".
 * \param[in] source_rect The sub-rectangle of the source
 *       surface to read from. If NULL, the entire
 *       source_surface will be read. Left/right and/or top/bottom
 *       co-ordinates may be swapped to flip the source. Any
 *       flip occurs prior to any requested rotation. Values
 *       from outside the source surface are valid and samples
 *       at those locations will be taken from the nearest edge.
 * \param[in] colors A pointer to an array of \ref VdpColor
 *      "VdpColor" objects. If the flag
 *      VDP_OUTPUT_SURFACE_RENDER_COLOR_PER_VERTEX is set,
 *      VDPAU will four entries from the array, and treat them
 *      as the colors corresponding to the upper-left,
 *      upper-right, lower-right and lower-left corners of the
 *      post-rotation source (i.e. indices 0, 1, 2 and 3 run
 *      clockwise from the upper left corner). If the flag
 *      VDP_OUTPUT_SURFACE_RENDER_COLOR_PER_VERTEX is not
 *      set, VDPAU will use the single VdpColor for all four
 *      corners. If colors is NULL then red, green, blue and
 *      alpha values of 1.0 will be used.
 * \param[in] blend_state If a blend state is provided, the
 *     blend state will be used for the composite operation. If
 *     NULL, blending is effectively disabled, which is
 *     equivalent to a blend equation of ADD, source blend
 *     factors of ONE and destination blend factors of ZERO.
 *     See \ref VdpOutputSurfaceRenderBlendState for details
 *     regarding the mathematics of the blending operation.
 * \param[in] flags A set of flags influencing how the
 *       compositing operation works.
 * \arg \ref VDP_OUTPUT_SURFACE_RENDER_ROTATE_0
 * \arg \ref VDP_OUTPUT_SURFACE_RENDER_ROTATE_90
 * \arg \ref VDP_OUTPUT_SURFACE_RENDER_ROTATE_180
 * \arg \ref VDP_OUTPUT_SURFACE_RENDER_ROTATE_270
 * \arg \ref VDP_OUTPUT_SURFACE_RENDER_COLOR_PER_VERTEX
 * \return VdpStatus The completion status of the operation.
 *
 * The general compositing pipeline is as follows.
 *
 * -# Extract source_rect from source_surface.
 *
 * -# The extracted source is rotated 0, 90, 180 or 270 degrees
 *    according to the flags.
 *
 * -# The rotated source is component-wise multiplied by a
 *    smooth-shaded quad with a (potentially) different color at
 *    each vertex.
 *
 * -# The resulting rotated, smooth-shaded quad is scaled to the
 *    size of destination_rect and composited with
 *    destination_surface using the provided blend state.
 *
 */
typedef VdpStatus VdpOutputSurfaceRenderOutputSurface(
    VdpOutputSurface                         destination_surface,
    VdpRect const *                          destination_rect,
    VdpOutputSurface                         source_surface,
    VdpRect const *                          source_rect,
    VdpColor const *                         colors,
    VdpOutputSurfaceRenderBlendState const * blend_state,
    uint32_t                                 flags
);

/**
 * \brief Composite a sub-rectangle of a \ref VdpBitmapSurface
 *        "VdpBitmapSurface" into a sub-rectangle of a
 *        \ref VdpOutputSurface VdpOutputSurface.
 * \param[in] destination_surface The destination surface of the
 *       compositing operation.
 * \param[in] destination_rect The sub-rectangle of the
 *       destination surface to update. If NULL, the entire
 *       destination surface will be updated.
 * \param[in] source_surface The source surface for the
 *       compositing operation. The surface is treated as having
 *       four components: red, green, blue and alpha. Any
 *       missing components are treated as 1.0. For example, for
 *       an A8 VdpBitmapSurface, alpha will come from the surface
 *       but red, green and blue will be treated as 1.0. If
 *       source_surface is NULL, all components will be treated
 *       as 1.0. Note that destination_surface and
 *       source_surface must have been allocated via the same
 *       \ref VdpDevice "VdpDevice".
 * \param[in] source_rect The sub-rectangle of the source
 *       surface to read from. If NULL, the entire
 *       source_surface will be read. Left/right ot top/bottom
 *       co-ordinates may be swapped to flip the source. Any
 *       flip occurs prior to any requested rotation. Values
 *       from outside the source surface are valid and samples
 *       at those locations will be taken from the nearest edge.
 * \param[in] colors A pointer to an array of \ref VdpColor
 *      "VdpColor" objects. If the flag
 *      VDP_OUTPUT_SURFACE_RENDER_COLOR_PER_VERTEX is set,
 *      VDPAU will four entries from the array, and treat them
 *      as the colors corresponding to the upper-left,
 *      upper-right, lower-right and lower-left corners of the
 *      post-rotation source (i.e. indices 0, 1, 2 and 3 run
 *      clockwise from the upper left corner). If the flag
 *      VDP_OUTPUT_SURFACE_RENDER_COLOR_PER_VERTEX is not
 *      set, VDPAU will use the single VdpColor for all four
 *      corners. If colors is NULL then red, green, blue and
 *      alpha values of 1.0 will be used.
 * \param[in] blend_state If a blend state is provided, the
 *     blend state will be used for the composite operation. If
 *     NULL, blending is effectively disabled, which is
 *     equivalent to a blend equation of ADD, source blend
 *     factors of ONE and destination blend factors of ZERO.
 *     See \ref VdpOutputSurfaceRenderBlendState for details
 *     regarding the mathematics of the blending operation.
 * \param[in] flags A set of flags influencing how the
 *       compositing operation works.
 * \arg \ref VDP_OUTPUT_SURFACE_RENDER_ROTATE_0
 * \arg \ref VDP_OUTPUT_SURFACE_RENDER_ROTATE_90
 * \arg \ref VDP_OUTPUT_SURFACE_RENDER_ROTATE_180
 * \arg \ref VDP_OUTPUT_SURFACE_RENDER_ROTATE_270
 * \arg \ref VDP_OUTPUT_SURFACE_RENDER_COLOR_PER_VERTEX
 * \return VdpStatus The completion status of the operation.
 *
 * The general compositing pipeline is as follows.
 *
 * -# Extract source_rect from source_surface.
 *
 * -# The extracted source is rotated 0, 90, 180 or 270 degrees
 *   according to the flags.
 *
 * -# The rotated source is component-wise multiplied by a
 *    smooth-shaded quad with a (potentially) different color at
 *    each vertex.
 *
 * -# The resulting rotated, smooth-shaded quad is scaled to the
 *    size of destination_rect and composited with
 *    destination_surface using the provided blend state.
 *
 */
typedef VdpStatus VdpOutputSurfaceRenderBitmapSurface(
    VdpOutputSurface                         destination_surface,
    VdpRect const *                          destination_rect,
    VdpBitmapSurface                         source_surface,
    VdpRect const *                          source_rect,
    VdpColor const *                         colors,
    VdpOutputSurfaceRenderBlendState const * blend_state,
    uint32_t                                 flags
);

/*@}*/

/**
 * \defgroup VdpDecoder VdpDecoder; Video Decoding object
 *
 * The VdpDecoder object decodes compressed video data, writing
 * the results to a \ref VdpVideoSurface "VdpVideoSurface".
 *
 * A specific VDPAU implementation may support decoding multiple
 * types of compressed video data. However, VdpDecoder objects
 * are able to decode a specific type of compressed video data.
 * This type must be specified during creation.
 *
 * @{
 */

/**
 * \brief The set of all known compressed video formats, and
 *        associated profiles, that may be decoded.
 */
typedef uint32_t VdpDecoderProfile;

/** \hideinitializer */
#define VDP_DECODER_PROFILE_MPEG1                       (VdpDecoderProfile)0
/** \hideinitializer */
#define VDP_DECODER_PROFILE_MPEG2_SIMPLE                (VdpDecoderProfile)1
/** \hideinitializer */
#define VDP_DECODER_PROFILE_MPEG2_MAIN                  (VdpDecoderProfile)2
/** \hideinitializer */
/** \brief MPEG 4 part 10 == H.264 == AVC */
#define VDP_DECODER_PROFILE_H264_BASELINE               (VdpDecoderProfile)6
/** \hideinitializer */
#define VDP_DECODER_PROFILE_H264_MAIN                   (VdpDecoderProfile)7
/** \hideinitializer */
#define VDP_DECODER_PROFILE_H264_HIGH                   (VdpDecoderProfile)8
/** \hideinitializer */
#define VDP_DECODER_PROFILE_VC1_SIMPLE                  (VdpDecoderProfile)9
/** \hideinitializer */
#define VDP_DECODER_PROFILE_VC1_MAIN                    (VdpDecoderProfile)10
/** \hideinitializer */
#define VDP_DECODER_PROFILE_VC1_ADVANCED                (VdpDecoderProfile)11
/** \hideinitializer */
#define VDP_DECODER_PROFILE_MPEG4_PART2_SP              (VdpDecoderProfile)12
/** \hideinitializer */
#define VDP_DECODER_PROFILE_MPEG4_PART2_ASP             (VdpDecoderProfile)13
/** \hideinitializer */
#define VDP_DECODER_PROFILE_DIVX4_QMOBILE               (VdpDecoderProfile)14
/** \hideinitializer */
#define VDP_DECODER_PROFILE_DIVX4_MOBILE                (VdpDecoderProfile)15
/** \hideinitializer */
#define VDP_DECODER_PROFILE_DIVX4_HOME_THEATER          (VdpDecoderProfile)16
/** \hideinitializer */
#define VDP_DECODER_PROFILE_DIVX4_HD_1080P              (VdpDecoderProfile)17
/** \hideinitializer */
#define VDP_DECODER_PROFILE_DIVX5_QMOBILE               (VdpDecoderProfile)18
/** \hideinitializer */
#define VDP_DECODER_PROFILE_DIVX5_MOBILE                (VdpDecoderProfile)19
/** \hideinitializer */
#define VDP_DECODER_PROFILE_DIVX5_HOME_THEATER          (VdpDecoderProfile)20
/** \hideinitializer */
#define VDP_DECODER_PROFILE_DIVX5_HD_1080P              (VdpDecoderProfile)21

/** \hideinitializer */
#define VDP_DECODER_LEVEL_MPEG1_NA 0

/** \hideinitializer */
#define VDP_DECODER_LEVEL_MPEG2_LL   0
/** \hideinitializer */
#define VDP_DECODER_LEVEL_MPEG2_ML   1
/** \hideinitializer */
#define VDP_DECODER_LEVEL_MPEG2_HL14 2
/** \hideinitializer */
#define VDP_DECODER_LEVEL_MPEG2_HL   3

/** \hideinitializer */
#define VDP_DECODER_LEVEL_H264_1     10
/** \hideinitializer */
#define VDP_DECODER_LEVEL_H264_1b    9
/** \hideinitializer */
#define VDP_DECODER_LEVEL_H264_1_1   11
/** \hideinitializer */
#define VDP_DECODER_LEVEL_H264_1_2   12
/** \hideinitializer */
#define VDP_DECODER_LEVEL_H264_1_3   13
/** \hideinitializer */
#define VDP_DECODER_LEVEL_H264_2     20
/** \hideinitializer */
#define VDP_DECODER_LEVEL_H264_2_1   21
/** \hideinitializer */
#define VDP_DECODER_LEVEL_H264_2_2   22
/** \hideinitializer */
#define VDP_DECODER_LEVEL_H264_3     30
/** \hideinitializer */
#define VDP_DECODER_LEVEL_H264_3_1   31
/** \hideinitializer */
#define VDP_DECODER_LEVEL_H264_3_2   32
/** \hideinitializer */
#define VDP_DECODER_LEVEL_H264_4     40
/** \hideinitializer */
#define VDP_DECODER_LEVEL_H264_4_1   41
/** \hideinitializer */
#define VDP_DECODER_LEVEL_H264_4_2   42
/** \hideinitializer */
#define VDP_DECODER_LEVEL_H264_5     50
/** \hideinitializer */
#define VDP_DECODER_LEVEL_H264_5_1   51

/** \hideinitializer */
#define VDP_DECODER_LEVEL_VC1_SIMPLE_LOW    0
/** \hideinitializer */
#define VDP_DECODER_LEVEL_VC1_SIMPLE_MEDIUM 1

/** \hideinitializer */
#define VDP_DECODER_LEVEL_VC1_MAIN_LOW    0
/** \hideinitializer */
#define VDP_DECODER_LEVEL_VC1_MAIN_MEDIUM 1
/** \hideinitializer */
#define VDP_DECODER_LEVEL_VC1_MAIN_HIGH   2

/** \hideinitializer */
#define VDP_DECODER_LEVEL_VC1_ADVANCED_L0 0
/** \hideinitializer */
#define VDP_DECODER_LEVEL_VC1_ADVANCED_L1 1
/** \hideinitializer */
#define VDP_DECODER_LEVEL_VC1_ADVANCED_L2 2
/** \hideinitializer */
#define VDP_DECODER_LEVEL_VC1_ADVANCED_L3 3
/** \hideinitializer */
#define VDP_DECODER_LEVEL_VC1_ADVANCED_L4 4

/** \hideinitializer */
#define VDP_DECODER_LEVEL_MPEG4_PART2_SP_L0 0
/** \hideinitializer */
#define VDP_DECODER_LEVEL_MPEG4_PART2_SP_L1 1
/** \hideinitializer */
#define VDP_DECODER_LEVEL_MPEG4_PART2_SP_L2 2
/** \hideinitializer */
#define VDP_DECODER_LEVEL_MPEG4_PART2_SP_L3 3

/** \hideinitializer */
#define VDP_DECODER_LEVEL_MPEG4_PART2_ASP_L0 0
/** \hideinitializer */
#define VDP_DECODER_LEVEL_MPEG4_PART2_ASP_L1 1
/** \hideinitializer */
#define VDP_DECODER_LEVEL_MPEG4_PART2_ASP_L2 2
/** \hideinitializer */
#define VDP_DECODER_LEVEL_MPEG4_PART2_ASP_L3 3
/** \hideinitializer */
#define VDP_DECODER_LEVEL_MPEG4_PART2_ASP_L4 4
/** \hideinitializer */
#define VDP_DECODER_LEVEL_MPEG4_PART2_ASP_L5 5

/** \hideinitializer */
#define VDP_DECODER_LEVEL_DIVX_NA 0

/**
 * \brief Query the implementation's VdpDecoder capabilities.
 * \param[in] device The device to query.
 * \param[in] profile The decoder profile for which information is requested.
 * \param[out] is_supported Is this profile supported?
 * \param[out] max_level The maximum specification level supported for this
 *       profile.
 * \param[out] max_macroblocks The maximum supported surface size in
 *       macroblocks. Note that this could be greater than that dictated by
 *       the maximum level.
 * \param[out] max_width The maximum supported surface width for this profile.
 *       Note that this could be greater than that dictated by the maximum
 *       level.
 * \param[out] max_height The maximum supported surface height for this
 *       profile. Note that this could be greater than that dictated by the
 *       maximum level.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpDecoderQueryCapabilities(
    VdpDevice         device,
    VdpDecoderProfile profile,
    /* output parameters follow */
    VdpBool *         is_supported,
    uint32_t *        max_level,
    uint32_t *        max_macroblocks,
    uint32_t *        max_width,
    uint32_t *        max_height
);

/**
 * \brief An opaque handle representing a VdpDecoder object.
 */
typedef uint32_t VdpDecoder;

/**
 * \brief Create a VdpDecoder.
 * \param[in] device The device that will contain the surface.
 * \param[in] profile The video format the decoder will decode.
 * \param[in] width The width of the new surface.
 * \param[in] height The height of the new surface.
 * \param[in] max_references The maximum number of references that may be
 *       used by a single frame in the stream to be decoded. This parameter
 *       exists mainly for formats such as H.264, where different streams
 *       may use a different number of references. Requesting too many
 *       references may waste memory, but decoding should still operate
 *       correctly. Requesting too few references will cause decoding to
 *       fail.
 * \param[out] decoder The new decoder's handle.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpDecoderCreate(
    VdpDevice         device,
    VdpDecoderProfile profile,
    uint32_t          width,
    uint32_t          height,
    uint32_t          max_references,
    /* output parameters follow */
    VdpDecoder *      decoder
);

/**
 * \brief Destroy a VdpDecoder.
 * \param[in] surface The decoder's handle.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpDecoderDestroy(
    VdpDecoder decoder
);

/**
 * \brief Retrieve the parameters used to create a
 *        VdpDecoder.
 * \param[in] surface The surface's handle.
 * \param[out] profile The video format used to create the
 *       decoder.
 * \param[out] width The width of surfaces decode by the
 *       decoder.
 * \param[out] height The height of surfaces decode by the
 *       decoder
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpDecoderGetParameters(
    VdpDecoder          decoder,
    /* output parameters follow */
    VdpDecoderProfile * profile,
    uint32_t *          width,
    uint32_t *          height
);

#define VDP_BITSTREAM_BUFFER_VERSION 0

/**
 * \brief Application data buffer containing compressed video
 *        data.
 */
typedef struct {
    /**
     * This field must be filled with VDP_BITSTREAM_BUFFER_VERSION
     */
    uint32_t     struct_version;
    /** A pointer to the bitstream data bytes */
    void const * bitstream;
    /** The number of data bytes */
    uint32_t     bitstream_bytes;
} VdpBitstreamBuffer;

/**
 * \brief A generic "picture information" pointer type.
 *
 * This type serves solely to document the expected usage of a
 * generic (void *) function parameter. In actual usage, the
 * application is expected to physically provide a pointer to an
 * instance of one of the "real" VdpPictureInfo* structures,
 * picking the type appropriate for the decoder object in
 * question.
 */
typedef void * VdpPictureInfo;

/**
 * \brief Picture parameter information for an MPEG 1 or MPEG 2
 *        picture.
 *
 * Note: References to "copy of bitstream field" in the field descriptions
 * may refer to data literally parsed from the bitstream, or derived from
 * the bitstream using a mechanism described in the specification.
 */
typedef struct {
    /**
     * Reference used by B and P frames.
     * Set to VDP_INVALID_HANDLE when not used.
     */
    VdpVideoSurface forward_reference;
    /**
     * Reference used by B frames.
     * Set to VDP_INVALID_HANDLE when not used.
     */
    VdpVideoSurface backward_reference;
    /** Number of slices in the bitstream provided. */
    uint32_t        slice_count;

    /** Copy of the MPEG bitstream field. */
    uint8_t picture_structure;
    /** Copy of the MPEG bitstream field. */
    uint8_t picture_coding_type;
    /** Copy of the MPEG bitstream field. */
    uint8_t intra_dc_precision;
    /** Copy of the MPEG bitstream field. */
    uint8_t frame_pred_frame_dct;
    /** Copy of the MPEG bitstream field. */
    uint8_t concealment_motion_vectors;
    /** Copy of the MPEG bitstream field. */
    uint8_t intra_vlc_format;
    /** Copy of the MPEG bitstream field. */
    uint8_t alternate_scan;
    /** Copy of the MPEG bitstream field. */
    uint8_t q_scale_type;
    /** Copy of the MPEG bitstream field. */
    uint8_t top_field_first;
    /** Copy of the MPEG-1 bitstream field. For MPEG-2, set to 0. */
    uint8_t full_pel_forward_vector;
    /** Copy of the MPEG-1 bitstream field. For MPEG-2, set to 0. */
    uint8_t full_pel_backward_vector;
    /**
     * Copy of the MPEG bitstream field.
     * For MPEG-1, fill both horizontal and vertical entries.
     */
    uint8_t f_code[2][2];
    /** Copy of the MPEG bitstream field, converted to raster order. */
    uint8_t intra_quantizer_matrix[64];
    /** Copy of the MPEG bitstream field, converted to raster order. */
    uint8_t non_intra_quantizer_matrix[64];
} VdpPictureInfoMPEG1Or2;

/**
 * \brief Information about an H.264 reference frame
 *
 * Note: References to "copy of bitstream field" in the field descriptions
 * may refer to data literally parsed from the bitstream, or derived from
 * the bitstream using a mechanism described in the specification.
 */
typedef struct {
    /**
     * The surface that contains the reference image.
     * Set to VDP_INVALID_HANDLE for unused entries.
     */
    VdpVideoSurface surface;
    /** Is this a long term reference (else short term). */
    VdpBool         is_long_term;
    /**
     * Is the top field used as a reference.
     * Set to VDP_FALSE for unused entries.
     */
    VdpBool         top_is_reference;
    /**
     * Is the bottom field used as a reference.
     * Set to VDP_FALSE for unused entries.
     */
    VdpBool         bottom_is_reference;
    /** [0]: top, [1]: bottom */
    int32_t         field_order_cnt[2];
    /**
     * Copy of the H.264 bitstream field:
     * frame_num from slice_header for short-term references,
     * LongTermPicNum from decoding algorithm for long-term references.
     */
    uint16_t        frame_idx;
} VdpReferenceFrameH264;

/**
 * \brief Picture parameter information for an H.264 picture.
 *
 * Note: The \ref referenceFrames array must contain the "DPB" as
 * defined by the H.264 specification. In particular, once a
 * reference frame has been decoded to a surface, that surface must
 * continue to appear in the DPB until no longer required to predict
 * any future frame. Once a surface is removed from the DPB, it can
 * no longer be used as a reference, unless decoded again.
 *
 * Also note that only surfaces previously generated using \ref
 * VdpDecoderRender may be used as reference frames. In particular,
 * surfaces filled using any "put bits" API will not work.
 *
 * Note: References to "copy of bitstream field" in the field descriptions
 * may refer to data literally parsed from the bitstream, or derived from
 * the bitstream using a mechanism described in the specification.
 */
typedef struct {
    /** Number of slices in the bitstream provided. */
    uint32_t slice_count;
    /** [0]: top, [1]: bottom */
    int32_t  field_order_cnt[2];
    /** Will the decoded frame be used as a reference later. */
    VdpBool  is_reference;

    /** Copy of the H.264 bitstream field. */
    uint16_t frame_num;
    /** Copy of the H.264 bitstream field. */
    uint8_t  field_pic_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  bottom_field_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  num_ref_frames;
    /** Copy of the H.264 bitstream field. */
    uint8_t  mb_adaptive_frame_field_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  constrained_intra_pred_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  weighted_pred_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  weighted_bipred_idc;
    /** Copy of the H.264 bitstream field. */
    uint8_t  frame_mbs_only_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  transform_8x8_mode_flag;
    /** Copy of the H.264 bitstream field. */
    int8_t   chroma_qp_index_offset;
    /** Copy of the H.264 bitstream field. */
    int8_t   second_chroma_qp_index_offset;
    /** Copy of the H.264 bitstream field. */
    int8_t   pic_init_qp_minus26;
    /** Copy of the H.264 bitstream field. */
    uint8_t  num_ref_idx_l0_active_minus1;
    /** Copy of the H.264 bitstream field. */
    uint8_t  num_ref_idx_l1_active_minus1;
    /** Copy of the H.264 bitstream field. */
    uint8_t  log2_max_frame_num_minus4;
    /** Copy of the H.264 bitstream field. */
    uint8_t  pic_order_cnt_type;
    /** Copy of the H.264 bitstream field. */
    uint8_t  log2_max_pic_order_cnt_lsb_minus4;
    /** Copy of the H.264 bitstream field. */
    uint8_t  delta_pic_order_always_zero_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  direct_8x8_inference_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  entropy_coding_mode_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  pic_order_present_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  deblocking_filter_control_present_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  redundant_pic_cnt_present_flag;

    /** Copy of the H.264 bitstream field, converted to raster order. */
    uint8_t scaling_lists_4x4[6][16];
    /** Copy of the H.264 bitstream field, converted to raster order. */
    uint8_t scaling_lists_8x8[2][64];

    /** See \ref VdpPictureInfoH264 for instructions regarding this field. */
    VdpReferenceFrameH264 referenceFrames[16];
} VdpPictureInfoH264;

/**
 * \brief Picture parameter information for a VC1 picture.
 *
 * Note: References to "copy of bitstream field" in the field descriptions
 * may refer to data literally parsed from the bitstream, or derived from
 * the bitstream using a mechanism described in the specification.
 */
typedef struct {
    /**
     * Reference used by B and P frames.
     * Set to VDP_INVALID_HANDLE when not used.
     */
    VdpVideoSurface forward_reference;
    /**
     * Reference used by B frames.
     * Set to VDP_INVALID_HANDLE when not used.
     */
    VdpVideoSurface backward_reference;

    /** Number of slices in the bitstream provided. */
    uint32_t slice_count;
    /** I=0, P=1, B=3, BI=4  from 7.1.1.4. */
    uint8_t  picture_type;
    /** Progressive=0, Frame-interlace=2, Field-interlace=3; see VC-1 7.1.1.15. */
    uint8_t  frame_coding_mode;

    /** Copy of the VC-1 bitstream field. See VC-1 6.1.5. */
    uint8_t postprocflag;
    /** Copy of the VC-1 bitstream field. See VC-1 6.1.8. */
    uint8_t pulldown;
    /** Copy of the VC-1 bitstream field. See VC-1 6.1.9. */
    uint8_t interlace;
    /** Copy of the VC-1 bitstream field. See VC-1 6.1.10. */
    uint8_t tfcntrflag;
    /** Copy of the VC-1 bitstream field. See VC-1 6.1.11. */
    uint8_t finterpflag;
    /** Copy of the VC-1 bitstream field. See VC-1 6.1.3. */
    uint8_t psf;
    /** Copy of the VC-1 bitstream field. See VC-1 6.2.8. */
    uint8_t dquant;
    /** Copy of the VC-1 bitstream field. See VC-1 6.2.3. */
    uint8_t panscan_flag;
    /** Copy of the VC-1 bitstream field. See VC-1 6.2.4. */
    uint8_t refdist_flag;
    /** Copy of the VC-1 bitstream field. See VC-1 6.2.11. */
    uint8_t quantizer;
    /** Copy of the VC-1 bitstream field. See VC-1 6.2.7. */
    uint8_t extended_mv;
    /** Copy of the VC-1 bitstream field. See VC-1 6.2.14. */
    uint8_t extended_dmv;
    /** Copy of the VC-1 bitstream field. See VC-1 6.2.10. */
    uint8_t overlap;
    /** Copy of the VC-1 bitstream field. See VC-1 6.2.9. */
    uint8_t vstransform;
    /** Copy of the VC-1 bitstream field. See VC-1 6.2.5. */
    uint8_t loopfilter;
    /** Copy of the VC-1 bitstream field. See VC-1 6.2.6. */
    uint8_t fastuvmc;
    /** Copy of the VC-1 bitstream field. See VC-1 6.12.15. */
    uint8_t range_mapy_flag;
    /** Copy of the VC-1 bitstream field. */
    uint8_t range_mapy;
    /** Copy of the VC-1 bitstream field. See VC-1 6.2.16. */
    uint8_t range_mapuv_flag;
    /** Copy of the VC-1 bitstream field. */
    uint8_t range_mapuv;

    /**
     * Copy of the VC-1 bitstream field. See VC-1 J.1.10.
     * Only used by simple and main profiles.
     */
    uint8_t multires;
    /**
     * Copy of the VC-1 bitstream field. See VC-1 J.1.16.
     * Only used by simple and main profiles.
     */
    uint8_t syncmarker;
    /**
     * VC-1 SP/MP range reduction control.
     * Only used by simple and main profiles.
     * Bit 0: Copy of rangered VC-1 bitstream field; See VC-1 J.1.17.
     * Bit 1: Copy of rangeredfrm VC-1 bitstream fiels; See VC-1 7.1.13.
     */
    uint8_t rangered;
    /**
     * Copy of the VC-1 bitstream field. See VC-1 J.1.17.
     * Only used by simple and main profiles.
     */
    uint8_t maxbframes;

    /**
     * Out-of-loop deblocking enable.
     * Bit 0 of POSTPROC from VC-1 7.1.1.27
     * Note that bit 1 of POSTPROC (dering enable) should not be included.
     */
    uint8_t deblockEnable;
    /**
     * Parameter used by VC-1 Annex H deblocking algorithm. Note that VDPAU
     * implementations may choose which deblocking algorithm to use.
     * See VC-1 7.1.1.6
     */
    uint8_t pquant;
} VdpPictureInfoVC1;

/**
 * \brief Picture parameter information for an MPEG-4 Part 2 picture.
 *
 * Note: References to "copy of bitstream field" in the field descriptions
 * may refer to data literally parsed from the bitstream, or derived from
 * the bitstream using a mechanism described in the specification.
 */
typedef struct {
    /**
     * Reference used by B and P frames.
     * Set to VDP_INVALID_HANDLE when not used.
     */
    VdpVideoSurface forward_reference;
    /**
     * Reference used by B frames.
     * Set to VDP_INVALID_HANDLE when not used.
     */
    VdpVideoSurface backward_reference;

    /** Copy of the bitstream field. */
    int32_t trd[2];
    /** Copy of the bitstream field. */
    int32_t trb[2];
    /** Copy of the bitstream field. */
    uint16_t vop_time_increment_resolution;
    /** Copy of the bitstream field. */
    uint8_t vop_coding_type;
    /** Copy of the bitstream field. */
    uint8_t vop_fcode_forward;
    /** Copy of the bitstream field. */
    uint8_t vop_fcode_backward;
    /** Copy of the bitstream field. */
    uint8_t resync_marker_disable;
    /** Copy of the bitstream field. */
    uint8_t interlaced;
    /** Copy of the bitstream field. */
    uint8_t quant_type;
    /** Copy of the bitstream field. */
    uint8_t quarter_sample;
    /** Copy of the bitstream field. */
    uint8_t short_video_header;
    /** Derived from vop_rounding_type bitstream field. */
    uint8_t rounding_control;
    /** Copy of the bitstream field. */
    uint8_t alternate_vertical_scan_flag;
    /** Copy of the bitstream field. */
    uint8_t top_field_first;
    /** Copy of the bitstream field. */
    uint8_t intra_quantizer_matrix[64];
    /** Copy of the bitstream field. */
    uint8_t non_intra_quantizer_matrix[64];
} VdpPictureInfoMPEG4Part2;

/**
 * \brief Picture parameter information for a DivX 4 picture.
 *
 * Due to similarites between MPEG-4 Part 2 and DivX 4, the picture
 * parameter structure is re-used.
 */
typedef VdpPictureInfoMPEG4Part2 VdpPictureInfoDivX4;

/**
 * \brief Picture parameter information for a DivX 5 picture.
 *
 * Due to similarites between MPEG-4 Part 2 and DivX 5, the picture
 * parameter structure is re-used.
 */
typedef VdpPictureInfoMPEG4Part2 VdpPictureInfoDivX5;

/**
 * \brief Decode a compressed field/frame and render the result
 *        into a \ref VdpVideoSurface "VdpVideoSurface".
 * \param[in] decoder The decoder object that will perform the
 *       decode operation.
 * \param[in] target The video surface to render to.
 * \param[in] picture_info A (pointer to a) structure containing
 *       information about the picture to be decoded. Note that
 *       the appropriate type of VdpPictureInfo* structure must
 *       be provided to match to profile that the decoder was
 *       created for.
 * \param[in] bitstream_buffer_count The number of bitstream
 *       buffers containing compressed data for this picture.
 * \param[in] bitstream_buffers An array of bitstream buffers.
 * \return VdpStatus The completion status of the operation.
 *
 * See \ref video_mixer_usage for additional information.
 */
typedef VdpStatus VdpDecoderRender(
    VdpDecoder                 decoder,
    VdpVideoSurface            target,
    VdpPictureInfo const *     picture_info,
    uint32_t                   bitstream_buffer_count,
    VdpBitstreamBuffer const * bitstream_buffers
);

/*@}*/

/**
 * \defgroup VdpVideoMixer VdpVideoMixer; Video Post-processing \
 *           and Compositing object
 *
 * VdpVideoMixer can perform some subset of the following
 * post-processing steps on video:
 * - De-interlacing
 *   - Various types, with or without inverse telecine
 * - Noise-reduction
 * - Sharpness adjustment
 * - Color space conversion to RGB
 * - Chroma format upscaling to 4:4:4
 *
 * A VdpVideoMixer takes a source \ref VdpVideoSurface
 * "VdpVideoSurface" VdpVideoSurface and performs various video
 * processing steps on it (potentially using information from
 * past or future video surfaces). It scales the video and
 * converts it to RGB, then optionally composites it with
 * multiple auxiliary \ref VdpOutputSurface "VdpOutputSurface"s
 * before writing the result to the destination \ref
 * VdpOutputSurface "VdpOutputSurface".
 *
 * The video mixer compositing model is as follows:
 *
 * - A rectangle will be rendered on an output surface. No
 *   pixels will be rendered outside of this output rectangle.
 *   The contents of this rectangle will be a composite of many
 *   layers.
 *
 * - The first layer is the background color. The background
 *   color will fill the entire rectangle.
 *
 * - The second layer is the processed video which has been
 *   converted to RGB. These pixels will overwrite the
 *   background color of the first layer except where the second
 *   layer's rectangle does not completely cover the output
 *   rectangle. In those regions the background color will
 *   continue to show. If any portion of the second layer's
 *   output rectangle is outside of the output rectangle, those
 *   portions will be clipped.
 *
 * - The third layer contains some number of auxiliary layers
 *   (in the form of \ref VdpOutputSurface "VdpOutputSurface"s)
 *   which will be composited using the alpha value from the
 *   those surfaces. The compositing operations are equivalent
 *   to rendering with \ref VdpOutputSurfaceRenderOutputSurface
 *   using a source blend factor of SOURCE_ALPHA, a destination
 *   blend factor of ONE_MINUS_SOURCE_ALPHA and an equation of
 *   ADD.
 *
 * @{
 */

/**
 * \brief A VdpVideoMixer feature that must be requested at
 *        creation time to be used.
 *
 * Certain advanced VdpVideoMixer features are optional, and the
 * ability to use those features at all must be requested when
 * the VdpVideoMixer object is created. Each feature is named via
 * a specific VdpVideoMixerFeature value.
 *
 * Once requested, these features are permanently available
 * within that specific VdpVideoMixer object. All features that
 * are not explicitly requested at creation time default to
 * being permanently unavailable.
 *
 * Even when requested, all features default to being initially
 * disabled. However, applications can subsequently enable and
 * disable features at any time. See \ref
 * VdpVideoMixerSetFeatureEnables.
 *
 * Some features allow configuration of their operation. Each
 * configurable item is an \ref VdpVideoMixerAttribute. These
 * attributes may be manipulated at any time using \ref
 * VdpVideoMixerSetAttributeValues.
 */
typedef uint32_t VdpVideoMixerFeature;

/**
 * \hideinitializer
 * \brief A VdpVideoMixerFeature.
 *
 * When requested and enabled, motion adaptive temporal
 * deinterlacing will be used on interlaced content.
 *
 * When multiple de-interlacing options are requested and
 * enabled, the back-end implementation chooses the best
 * algorithm to apply.
 */
#define VDP_VIDEO_MIXER_FEATURE_DEINTERLACE_TEMPORAL         (VdpVideoMixerFeature)0
/**
 * \hideinitializer
 * \brief A VdpVideoMixerFeature.
 *
 * When requested and enabled, this enables a more advanced
 * version of temporal de-interlacing, that additionally uses
 * edge-guided spatial interpolation.
 *
 * When multiple de-interlacing options are requested and
 * enabled, the back-end implementation chooses the best
 * algorithm to apply.
 */
#define VDP_VIDEO_MIXER_FEATURE_DEINTERLACE_TEMPORAL_SPATIAL (VdpVideoMixerFeature)1
/**
 * \hideinitializer
 * \brief A VdpVideoMixerFeature.
 *
 * When requested and enabled, cadence detection will be enabled
 * on interlaced content and the video mixer will try to extract
 * progressive frames from pull-down material.
 */
#define VDP_VIDEO_MIXER_FEATURE_INVERSE_TELECINE             (VdpVideoMixerFeature)2
/**
 * \hideinitializer
 * \brief A VdpVideoMixerFeature.
 *
 * When requested and enabled, a noise reduction algorithm will
 * be applied to the video.
 */
#define VDP_VIDEO_MIXER_FEATURE_NOISE_REDUCTION              (VdpVideoMixerFeature)3
/**
 * \hideinitializer
 * \brief A VdpVideoMixerFeature.
 *
 * When requested and enabled, a sharpening algorithm will be
 * applied to the video.
 */
#define VDP_VIDEO_MIXER_FEATURE_SHARPNESS                    (VdpVideoMixerFeature)4
/**
 * \hideinitializer
 * \brief A VdpVideoMixerFeature.
 *
 * When requested and enabled, the alpha of the rendered
 * surface, which is normally set to the alpha of the background
 * color, will be forced to 0.0 on pixels corresponding to
 * source video surface luminance values in the range specified
 * by attributes \ref VDP_VIDEO_MIXER_ATTRIBUTE_LUMA_KEY_MIN_LUMA
 * to \ref VDP_VIDEO_MIXER_ATTRIBUTE_LUMA_KEY_MAX_LUMA. This
 * keying is performed after scaling and de-interlacing.
 */
#define VDP_VIDEO_MIXER_FEATURE_LUMA_KEY                     (VdpVideoMixerFeature)5
/**
 * \hideinitializer
 * \brief A VdpVideoMixerFeature.
 *
 * A VDPAU implementation may support multiple scaling algorithms of
 * differing quality, and may potentially support a different subset
 * of algorithms on different hardware.
 *
 * In some cases, higher quality algorithms may require more resources
 * (memory size, memory bandwidth, etc.) to operate. Hence, these high
 * quality algorithms must be explicitly requested and enabled by the client
 * application. This allows applications operating in a resource-constrained
 * environment to have some level of control over resource usage.
 *
 * Basic scaling is always built into any video mixer, and is known as
 * level 0. Scaling quality increases beginning with optional level 1,
 * through optional level 9.
 *
 * If an application requests and enables multiple high quality scaling
 * algorithms, the highest level enabled scaling algorithm will be used.
 */
#define VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L1      (VdpVideoMixerFeature)11
/**
 * \hideinitializer
 * \brief A VdpVideoMixerFeature.
 *
 * See \ref VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L1 for details.
 */
#define VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L2      (VdpVideoMixerFeature)12
/**
 * \hideinitializer
 * \brief A VdpVideoMixerFeature.
 *
 * See \ref VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L1 for details.
 */
#define VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L3      (VdpVideoMixerFeature)13
/**
 * \hideinitializer
 * \brief A VdpVideoMixerFeature.
 *
 * See \ref VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L1 for details.
 */
#define VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L4      (VdpVideoMixerFeature)14
/**
 * \hideinitializer
 * \brief A VdpVideoMixerFeature.
 *
 * See \ref VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L1 for details.
 */
#define VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L5      (VdpVideoMixerFeature)15
/**
 * \hideinitializer
 * \brief A VdpVideoMixerFeature.
 *
 * See \ref VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L1 for details.
 */
#define VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L6      (VdpVideoMixerFeature)16
/**
 * \hideinitializer
 * \brief A VdpVideoMixerFeature.
 *
 * See \ref VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L1 for details.
 */
#define VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L7      (VdpVideoMixerFeature)17
/**
 * \hideinitializer
 * \brief A VdpVideoMixerFeature.
 *
 * See \ref VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L1 for details.
 */
#define VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L8      (VdpVideoMixerFeature)18
/**
 * \hideinitializer
 * \brief A VdpVideoMixerFeature.
 *
 * See \ref VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L1 for details.
 */
#define VDP_VIDEO_MIXER_FEATURE_HIGH_QUALITY_SCALING_L9      (VdpVideoMixerFeature)19

/**
 * \brief A VdpVideoMixer creation parameter.
 *
 * When a VdpVideoMixer is created, certain parameters may be
 * supplied. Each parameter is named via a specific
 * VdpVideoMixerParameter value.
 *
 * Each parameter has a specific type, and specific default
 * value if not specified at VdpVideoMixer creation time. The
 * application may query the legal supported range for some
 * parameters.
 */
typedef uint32_t VdpVideoMixerParameter;

/**
 * \hideinitializer
 * \brief The exact width of input video surfaces.
 *
 * This parameter's type is uint32_t.
 *
 * This parameter defaults to 0 if not specified, which entails
 * that it must be specified.
 *
 * The application may query this parameter's supported
 * range.
 */
#define VDP_VIDEO_MIXER_PARAMETER_VIDEO_SURFACE_WIDTH  (VdpVideoMixerParameter)0
/**
 * \hideinitializer
 * \brief The exact height of input video surfaces.
 *
 * This parameter's type is uint32_t.
 *
 * This parameter defaults to 0 if not specified, which entails
 * that it must be specified.
 *
 * The application may query this parameter's supported
 * range.
 */
#define VDP_VIDEO_MIXER_PARAMETER_VIDEO_SURFACE_HEIGHT (VdpVideoMixerParameter)1
/**
 * \hideinitializer
 * \brief The chroma type of the input video surfaces the will
 *        process.
 *
 * This parameter's type is VdpChromaType.
 *
 * If not specified, this parameter defaults to
 * VDP_CHROMA_TYPE_420.
 *
 * The application may not query this application's supported
 * range, since it is a potentially disjoint enumeration.
 */
#define VDP_VIDEO_MIXER_PARAMETER_CHROMA_TYPE          (VdpVideoMixerParameter)2
/**
 * \hideinitializer
 * \brief The number of auxiliary layers in the mixer's
 *        compositing model.
 *
 * Note that this indicates the maximum number of layers that
 * may be processed by a given \ref VdpVideoMixer "VdpVideoMixer"
 * object. Each individual \ref VdpVideoMixerRender invocation
 * may choose to use a different number of actual layers, from 0
 * up to this limit.
 *
 * This attribute's type is uint32_t.
 *
 * If not specified, this parameter defaults to 0.
 *
 * The application may query this parameter's supported
 * range.
 */
#define VDP_VIDEO_MIXER_PARAMETER_LAYERS               (VdpVideoMixerParameter)3

/**
 * \brief An adjustable attribute of VdpVideoMixer operation.
 *
 * Various attributes of VdpVideoMixer operation may be adjusted
 * at any time. Each attribute is named via a specific
 * VdpVideoMixerAttribute value.
 *
 * Each attribute has a specific type, and specific default
 * value if not specified at VdpVideoMixer creation time. The
 * application may query the legal supported range for some
 * attributes.
 */
typedef uint32_t VdpVideoMixerAttribute;

/**
 * \hideinitializer
 * \brief The background color in the VdpVideoMixer's compositing
 *        model.
 *
 * This attribute's type is VdpColor.
 *
 * This parameter defaults to black (all color components 0.0
 * and alpha 1.0).
 *
 * The application may not query this parameter's supported
 * range, since the type is not scalar.
 */
#define VDP_VIDEO_MIXER_ATTRIBUTE_BACKGROUND_COLOR      (VdpVideoMixerAttribute)0
/**
 * \hideinitializer
 * \brief The color-space conversion matrix used by the
 *        VdpVideoMixer.
 *
 * This attribute's type is \ref VdpCSCMatrix.
 *
 * Note: When using \ref VdpVideoMixerGetAttributeValues to retrieve the
 * current CSC matrix, the attribute_values array must contain a pointer to
 * a pointer a VdpCSCMatrix (VdpCSCMatrix** as a void *). The get function will
 * either initialize the referenced CSC matrix to the current value, *or*
 * clear the supplied pointer to NULL, if the previous set call supplied a
 * value of NULL in parameter_values, to request the default matrix.
 *
 * \code
 * VdpCSCMatrix   matrix;
 * VdpCSCMatrix * matrix_ptr;
 * void * attribute_values[] = {&matrix_ptr};
 * VdpStatus st = vdp_video_mixer_get_attribute_values(..., attribute_values, ...);
 * \endcode
 *
 * This parameter defaults to a matrix suitable for ITU-R BT.601
 * input surfaces, with no procamp adjustments.
 *
 * The application may not query this parameter's supported
 * range, since the type is not scalar.
 */
#define VDP_VIDEO_MIXER_ATTRIBUTE_CSC_MATRIX            (VdpVideoMixerAttribute)1
/**
 * \hideinitializer
 * \brief The amount of noise reduction algorithm to apply.
 *
 * This attribute's type is float.
 *
 * This parameter defaults to 0.0, which equates to no noise
 * reduction.
 *
 * The application may query this parameter's supported range.
 * However, the range is fixed as 0.0...1.0.
 */
#define VDP_VIDEO_MIXER_ATTRIBUTE_NOISE_REDUCTION_LEVEL (VdpVideoMixerAttribute)2
/**
 * \hideinitializer
 * \brief The amount of sharpening, or blurring, to apply.
 *
 * This attribute's type is float.
 *
 * This parameter defaults to 0.0, which equates to no
 * sharpening.
 *
 * Positive values request sharpening. Negative values request
 * blurring.
 *
 * The application may query this parameter's supported range.
 * However, the range is fixed as -1.0...1.0.
 */
#define VDP_VIDEO_MIXER_ATTRIBUTE_SHARPNESS_LEVEL       (VdpVideoMixerAttribute)3
/**
 * \hideinitializer
 * \brief The minimum luma value for the luma key algorithm.
 *
 * This attribute's type is float.
 *
 * This parameter defaults to 0.0.
 *
 * The application may query this parameter's supported range.
 * However, the range is fixed as 0.0...1.0.
 */
#define VDP_VIDEO_MIXER_ATTRIBUTE_LUMA_KEY_MIN_LUMA     (VdpVideoMixerAttribute)4
/**
 * \hideinitializer
 * \brief The maximum luma value for the luma key algorithm.
 *
 * This attribute's type is float.
 *
 * This parameter defaults to 1.0.
 *
 * The application may query this parameter's supported range.
 * However, the range is fixed as 0.0...1.0.
 */
#define VDP_VIDEO_MIXER_ATTRIBUTE_LUMA_KEY_MAX_LUMA     (VdpVideoMixerAttribute)5
/**
 * \hideinitializer
 * \brief Whether de-interlacers should operate solely on luma, and bob chroma.
 *
 * Note: This attribute only affects advanced de-interlacing algorithms, not
 * bob or weave.
 *
 * This attribute's type is uint8_t.
 *
 * This parameter defaults to 0.
 *
 * The application may query this parameter's supported range.
 * However, the range is fixed as 0 (no/off) ... 1 (yes/on).
 */
#define VDP_VIDEO_MIXER_ATTRIBUTE_SKIP_CHROMA_DEINTERLACE (VdpVideoMixerAttribute)6

/**
 * \brief Query the implementation's support for a specific
 *        feature.
 * \param[in] device The device to query.
 * \param[in] feature The feature for which support is to be
 *       queried.
 * \param[out] is_supported Is the specified feature supported?
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoMixerQueryFeatureSupport(
    VdpDevice            device,
    VdpVideoMixerFeature feature,
    /* output parameters follow */
    VdpBool *            is_supported
);

/**
 * \brief Query the implementation's support for a specific
 *        parameter.
 * \param[in] device The device to query.
 * \param[in] parameter The parameter for which support is to be
 *       queried.
 * \param[out] is_supported Is the specified parameter
 *       supported?
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoMixerQueryParameterSupport(
    VdpDevice              device,
    VdpVideoMixerParameter parameter,
    /* output parameters follow */
    VdpBool *              is_supported
);

/**
 * \brief Query the implementation's support for a specific
 *        attribute.
 * \param[in] device The device to query.
 * \param[in] feature The feature for which support is to be
 *       queried.
 * \param[out] is_supported Is the specified feature supported?
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoMixerQueryAttributeSupport(
    VdpDevice              device,
    VdpVideoMixerAttribute attribute,
    /* output parameters follow */
    VdpBool *              is_supported
);

/**
 * \brief Query the implementation's supported for a specific
 *        parameter.
 * \param[in] device The device to query.
 * \param[in] parameter The parameter for which support is to be
 *       queried.
 * \param[out] min_value The minimum supported value.
 * \param[out] max_value The maximum supported value.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoMixerQueryParameterValueRange(
    VdpDevice              device,
    VdpVideoMixerParameter parameter,
    /* output parameters follow */
    void *                min_value,
    void *                max_value
);

/**
 * \brief Query the implementation's supported for a specific
 *        attribute.
 * \param[in] device The device to query.
 * \param[in] attribute The attribute for which support is to be
 *       queried.
 * \param[out] min_value The minimum supported value.
 * \param[out] max_value The maximum supported value.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoMixerQueryAttributeValueRange(
    VdpDevice              device,
    VdpVideoMixerAttribute attribute,
    /* output parameters follow */
    void *                min_value,
    void *                max_value
);

/**
 * \brief An opaque handle representing a VdpVideoMixer object.
 */
typedef uint32_t VdpVideoMixer;

/**
 * \brief Create a VdpVideoMixer.
 * \param[in] device The device that will contain the mixer.
 * \param[in] feature_count The number of features to request.
 * \param[in] features The list of features to request.
 * \param[in] parameter_count The number of parameters to set.
 * \param[in] parameters The list of parameters to set.
 * \param[in] parameter_values The values for the parameters. Note that each
 *     entry in the value array is a pointer to the actual value. In other
 *     words, the values themselves are not cast to "void *" and passed
 *     "inside" the array.
 * \param[out] mixer The new mixer's handle.
 * \return VdpStatus The completion status of the operation.
 *
 * Initially, all requested features will be disabled. They can
 * be enabled using \ref VdpVideoMixerSetFeatureEnables.
 *
 * Initially, all attributes will have default values. Values
 * can be changed using \ref VdpVideoMixerSetAttributeValues.
 */
typedef VdpStatus VdpVideoMixerCreate(
    VdpDevice                      device,
    // The set of features to request
    uint32_t                       feature_count,
    VdpVideoMixerFeature const *   features,
    // The parameters used during creation
    uint32_t                       parameter_count,
    VdpVideoMixerParameter const * parameters,
    void const * const *           parameter_values,
    /* output parameters follow */
    VdpVideoMixer *                mixer
);

/**
 * \brief Enable or disable features.
 * \param[in] mixer The mixer to manipulate.
 * \param[in] feature_count The number of features to
 *       enable/disable.
 * \param[in] features The list of features to enable/disable.
 * \param[in] feature_enables The list of new feature enable
 *       values.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoMixerSetFeatureEnables(
    VdpVideoMixer                mixer,
    uint32_t                     feature_count,
    VdpVideoMixerFeature const * features,
    VdpBool const *              feature_enables
);

/**
 * \brief Set attribute values
 * \param[in] mixer The mixer to manipulate.
 * \param[in] attribute_count The number of attributes to set.
 * \param[in] attributes The list of attributes to set.
 * \param[in] attribute_values The values for the attributes. Note that each
 *     entry in the value array is a pointer to the actual value. In other
 *     words, the values themselves are not cast to "void *" and passed
 *     "inside" the array. A NULL pointer requests that the default value be
 *     set for that attribute.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoMixerSetAttributeValues(
    VdpVideoMixer                  mixer,
    uint32_t                       attribute_count,
    VdpVideoMixerAttribute const * attributes,
    void const * const *           attribute_values
);

/**
 * \brief Retrieve whether features were requested at creation
 *        time.
 * \param[in] mixer The mixer to query.
 * \param[in] feature_count The number of features to query.
 * \param[in] features The list of features to query.
 * \param[out] feature_supported A list of values indicating
 *       whether the feature was requested, and hence is
 *       available.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoMixerGetFeatureSupport(
    VdpVideoMixer                mixer,
    uint32_t                     feature_count,
    VdpVideoMixerFeature const * features,
    /* output parameters follow */
    VdpBool *                    feature_supports
);

/**
 * \brief Retrieve whether features are enabled.
 * \param[in] mixer The mixer to manipulate.
 * \param[in] feature_count The number of features to query.
 * \param[in] features The list of features to query.
 * \param[out] feature_enabled A list of values indicating
 *       whether the feature is enabled.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoMixerGetFeatureEnables(
    VdpVideoMixer                mixer,
    uint32_t                     feature_count,
    VdpVideoMixerFeature const * features,
    /* output parameters follow */
    VdpBool *                    feature_enables
);

/**
 * \brief Retrieve parameter values given at creation time.
 * \param[in] mixer The mixer to manipulate.
 * \param[in] parameter_count The number of parameters to query.
 * \param[in] parameters The list of parameters to query.
 * \param[out] parameter_values The list of current values for
 *     the parameters. Note that each entry in the value array is a pointer to
 *     storage that will receive the actual value. If the attribute's type is
 *     a pointer itself, please closely read the documentation for that
 *     attribute type for any other data passing requirements.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoMixerGetParameterValues(
    VdpVideoMixer                  mixer,
    uint32_t                       parameter_count,
    VdpVideoMixerParameter const * parameters,
    /* output parameters follow */
    void * const *                 parameter_values
);

/**
 * \brief Retrieve current attribute values.
 * \param[in] mixer The mixer to manipulate.
 * \param[in] attribute_count The number of attributes to query.
 * \param[in] attributes The list of attributes to query.
 * \param[out] attribute_values The list of current values for
 *     the attributes. Note that each entry in the value array is a pointer to
 *     storage that will receive the actual value. If the attribute's type is
 *     a pointer itself, please closely read the documentation for that
 *     attribute type for any other data passing requirements.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoMixerGetAttributeValues(
    VdpVideoMixer                  mixer,
    uint32_t                       attribute_count,
    VdpVideoMixerAttribute const * attributes,
    /* output parameters follow */
    void * const *                 attribute_values
);

/**
 * \brief Destroy a VdpVideoMixer.
 * \param[in] device The device to destroy.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpVideoMixerDestroy(
    VdpVideoMixer mixer
);

/**
 * \hideinitializer
 * \brief The structure of the picture present in a \ref
 *        VdpVideoSurface "VdpVideoSurface".
 */
typedef enum {
    /**
     * The picture is a field, and is the top field of the surface.
     */
    VDP_VIDEO_MIXER_PICTURE_STRUCTURE_TOP_FIELD,
    /**
     * The picture is a field, and is the bottom field of the
     * surface.
     */
    VDP_VIDEO_MIXER_PICTURE_STRUCTURE_BOTTOM_FIELD,
    /**
     * The picture is a frame, and hence is the entire surface.
     */
    VDP_VIDEO_MIXER_PICTURE_STRUCTURE_FRAME,
} VdpVideoMixerPictureStructure;

#define VDP_LAYER_VERSION 0

/**
 * \brief Definition of an additional \ref VdpOutputSurface
 *        "VdpOutputSurface" layer in the composting model.
 */
typedef struct {
    /**
     * This field must be filled with VDP_LAYER_VERSION
     */
    uint32_t struct_version;
    /**
     * The surface to composite from.
     */
    VdpOutputSurface source_surface;
    /**
     * The sub-rectangle of the source surface to use. If NULL, the
     * entire source surface will be used.
     */
    VdpRect const *  source_rect;
    /**
     * The sub-rectangle of the destination surface to map
     * this layer into. This rectangle is relative to the entire
     * destination surface. This rectangle will be clipped by \ref
     * VdpVideoMixerRender's \b destination_rect. If NULL, the
     * destination rectangle will be sized to match the source
     * rectangle, and will be located at the origin.
     */
     VdpRect const * destination_rect;
} VdpLayer;

/**
 * \brief Perform a video post-processing and compositing
 *        operation.
 * \param[in] mixer The mixer object that will perform the
 *       mixing/rendering operation.
 * \param[in] background_surface A background image. If set to any value other
 *       than VDP_INVALID_HANDLE, the specific surface will be used instead of
 *       the background color as the first layer in the mixer's compositing
 *       process.
 * \param[in] background_source_rect When background_surface is specified,
 *       this parameter indicates the portion of background_surface that will
 *       be used as the background layer. The specified region will be
 *       extracted and scaled to match the size of destination_rect. If NULL,
 *       the entire background_surface will be used.
 * \param[in] current_picture_structure The picture structure of
 *       the field/frame to be processed. This field/frame is
 *       presented in the \b video_surface_current parameter. If
 *       frame, then all \b video_surface_* parameters are
 *       assumed to be frames. If field, then all
 *       video_surface_* parameters are assumed to be fields,
 *       with alternating top/bottom-ness derived from
 *       video_surface_current.
 * \param[in] video_surfaces_past_count The number of provided
 *       fields/frames prior to the current picture.
 * \param[in] video_surfaces_past The fields/frames prior to the
 *       current field/frame. Note that array index 0 is the
 *       field/frame temporally nearest to the current
 *       field/frame, with increasing array indices used for
 *       older frames. Unavailable entries may be set to
 *       \ref VDP_INVALID_HANDLE.
 * \param[in] video_surface_current The field/frame to be
 *       processed.
 * \param[in] video_surfaces_future_count The number of provided
 *       fields/frames following the current picture.
 * \param[in] video_surfaces_future The fields/frames that
 *       follow the current field/frame. Note that array index 0
 *       is the field/frame temporally nearest to the current
 *       field/frame, with increasing array indices used for
 *       newer frames. Unavailable entries may be set to \ref
 *       VDP_INVALID_HANDLE.
 * \param[in] video_source_rect The sub-rectangle of the source
 *       video surface to extract and process. If NULL, the
 *       entire surface will be used. Left/right and/or top/bottom
 *       co-ordinates may be swapped to flip the source. Values
 *       from outside the video surface are valid and samples
 *       at those locations will be taken from the nearest edge.
 * \param[in] destination_surface
 * \param[in] destination_rect The sub-rectangle of the
 *       destination surface to modify. Note that rectangle clips
 *       all other actions.
 * \param[in] destination_video_rect The sub-rectangle of the
 *       destination surface that will contain the processed
 *       video. This rectangle is relative to the entire
 *       destination surface. This rectangle is clipped by \b
 *       destination_rect. If NULL, the destination rectangle
 *       will be sized to match the source rectangle, and will
 *       be located at the origin.
 * \param[in] layer_count The number of additional layers to
 *       composite above the video.
 * \param[in] layers The array of additional layers to composite
 *       above the video.
 * \return VdpStatus The completion status of the operation.
 *
 * For a complete discussion of how to use this API, please see
 * \ref video_mixer_usage.
 */
typedef VdpStatus VdpVideoMixerRender(
    VdpVideoMixer                 mixer,
    VdpOutputSurface              background_surface,
    VdpRect const *               background_source_rect,
    VdpVideoMixerPictureStructure current_picture_structure,
    uint32_t                      video_surface_past_count,
    VdpVideoSurface const *       video_surface_past,
    VdpVideoSurface               video_surface_current,
    uint32_t                      video_surface_future_count,
    VdpVideoSurface const *       video_surface_future,
    VdpRect const *               video_source_rect,
    VdpOutputSurface              destination_surface,
    VdpRect const *               destination_rect,
    VdpRect const *               destination_video_rect,
    uint32_t                      layer_count,
    VdpLayer const *              layers
);

/*@}*/

/**
 * \defgroup VdpPresentationQueue VdpPresentationQueue; Video \
 *           presentation (display) object
 *
 * The VdpPresentationQueue manages a queue of surfaces and
 * associated timestamps. For each surface in the queue, once
 * the associated timestamp is reached, the surface is displayed
 * to the user. This timestamp-based approach yields high
 * quality video delivery.
 *
 * The exact location of the displayed content is Window System
 * specific. For this reason, the \ref api_winsys provides an
 * API to create a \ref VdpPresentationQueueTarget object (e.g.
 * via \ref VdpPresentationQueueTargetCreateX11) which
 * encapsulates this information.
 *
 * Note that the presentation queue performs no scaling of
 * surfaces to match the display target's size, aspect ratio,
 * etc.
 *
 * Surfaces that are too large to fit into the display target
 * will be clipped. Surfaces that are too small to fill the
 * display target will be aligned to the top-left corner of the
 * display target, with the balance of the display target being
 * filled with a constant configurable "background" color.
 *
 * Note that the presentation queue operates in a manner that is
 * semantically equivalent to an overlay surface, with any
 * required color key painting hidden internally. However,
 * implementations are free to use whatever semantically
 * equivalent technique they wish. Note that implementations
 * that actually use color-keyed overlays will typically use
 * the "background" color as the overlay color key value, so
 * this color should be chosen with care.
 *
 * @{
 */

/**
 * \brief The representation of a point in time.
 *
 * VdpTime timestamps are intended to be a high-precision timing
 * system, potentially independent from any other time domain in
 * the system.
 *
 * Time is represented in units of nanoseconds. The origin
 * (i.e. the time represented by a value of 0) is implementation
 * dependent.
 */
typedef uint64_t VdpTime;

/**
 * \brief An opaque handle representing the location where
 *        video will be presented.
 *
 * VdpPresentationQueueTarget are created using a \ref api_winsys
 * specific API, such as \ref
 * VdpPresentationQueueTargetCreateX11.
 */
typedef uint32_t VdpPresentationQueueTarget;

/**
 * \brief Destroy a VdpPresentationQueueTarget.
 * \param[in] presentation_queue_target The target to destroy.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpPresentationQueueTargetDestroy(
    VdpPresentationQueueTarget presentation_queue_target
);

/**
 * \brief An opaque handle representing a presentation queue
 *        object.
 */
typedef uint32_t VdpPresentationQueue;

/**
 * \brief Create a VdpPresentationQueue.
 * \param[in] device The device that will contain the queue.
 * \param[in] presentation_queue_target The location to display
 *       the content.
 * \param[out] presentation_queue The new queue's handle.
 * \return VdpStatus The completion status of the operation.
 *
 * Note: The initial value for the background color will be set to
 * an implementation-defined value.
 */
typedef VdpStatus VdpPresentationQueueCreate(
    VdpDevice                  device,
    VdpPresentationQueueTarget presentation_queue_target,
    /* output parameters follow */
    VdpPresentationQueue *     presentation_queue
);

/**
 * \brief Destroy a VdpPresentationQueue.
 * \param[in] presentation_queue The queue to destroy.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpPresentationQueueDestroy(
    VdpPresentationQueue presentation_queue
);

/**
 * \brief Configure the background color setting.
 * \param[in] presentation_queue The queue to manipulate.
 * \param[in] background_color The new background color.
 *
 * Note: Implementations may choose whether to apply the
 * new background color value immediately, or defer it until
 * the next surface is presented.
 */
typedef VdpStatus VdpPresentationQueueSetBackgroundColor(
    VdpPresentationQueue presentation_queue,
    VdpColor * const     background_color
);

/**
 * \brief Retrieve the current background color setting.
 * \param[in] presentation_queue The queue to query.
 * \param[out] background_color The current background color.
 */
typedef VdpStatus VdpPresentationQueueGetBackgroundColor(
    VdpPresentationQueue presentation_queue,
    VdpColor *           background_color
);

/**
 * \brief Retrieve the presentation queue's "current" time.
 * \param[in] presentation_queue The queue to query.
 * \param[out] current_time The current time, which may
 *       represent a point between display VSYNC events.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpPresentationQueueGetTime(
    VdpPresentationQueue presentation_queue,
    /* output parameters follow */
    VdpTime *            current_time
);

/**
 * \brief Enter a surface into the presentation queue.
 * \param[in] presentation_queue The queue to query.
 * \param[in] surface The surface to enter into the queue.
 * \param[in] clip_width If set to a non-zero value, the presentation queue
 *       will display only clip_width pixels of the surface (anchored to the
 *       top-left corner of the surface.
 * \param[in] clip_height If set to a non-zero value, the presentation queue
 *       will display only clip_height lines of the surface (anchored to the
 *       top-left corner of the surface.
 * \param[in] earliest_presentation_time The timestamp
 *       associated with the surface. The presentation queue
 *       will not display the surface until the presentation
 *       queue's current time is at least this value.
 * \return VdpStatus The completion status of the operation.
 *
 * Applications may choose to allow resizing of the presentation queue target
 * (which may be e.g. a regular Window when using an X11-based
 * implementation).
 *
 * \b clip_width and \b clip_height may be used to limit the size of the
 * displayed region of a surface, in order to match the specific region that
 * was rendered to.
 *
 * In turn, this allows the application to allocate over-sized (e.g.
 * screen-sized) surfaces, but render to a region that matches the current
 * size of the video window.
 *
 * Using this technique, an application's response to window resizing may
 * simply be to render to, and display, a different region of the surface,
 * rather than de-/re-allocation of surfaces to match the updated window size.
 *
 * Implementations may impose an upper bound on the number of entries
 * contained by the presentation queue at a given time. This limit is likely
 * different to the number of \ref VdpOutputSurface "VdpOutputSurface"s that
 * may be allocated at a given time. This limit applies to entries in the
 * QUEUED or VISIBLE state only. In other words, entries that have
 * transitioned from a QUEUED or VISIBLE state to an IDLE state do not count
 * toward this limit.
 */
typedef VdpStatus VdpPresentationQueueDisplay(
    VdpPresentationQueue presentation_queue,
    VdpOutputSurface     surface,
    uint32_t             clip_width,
    uint32_t             clip_height,
    VdpTime              earliest_presentation_time
);

/**
 * \brief Wait for a surface to finish being displayed.
 * \param[in] presentation_queue The queue to query.
 * \param[in] surface The surface to wait for.
 * \param[out] first_presentation_time The timestamp of the
 *       VSYNC at which this surface was first displayed. Note
 *       that 0 means the surface was never displayed.
 * \return VdpStatus The completion status of the operation.
 *
 * Note that this API would block forever if queried about the surface most
 * recently added to a presentation queue. That is because there would be no
 * other surface that could possibly replace that surface as the currently
 * displayed surface, and hence that surface would never become idle. For
 * that reason, this function will return an error in that case.
 */
typedef VdpStatus VdpPresentationQueueBlockUntilSurfaceIdle(
    VdpPresentationQueue presentation_queue,
    VdpOutputSurface     surface,
    /* output parameters follow */
    VdpTime *            first_presentation_time
);

/**
 * \hideinitializer
 * \brief The status of a surface within a presentation queue.
 */
typedef enum {
    /** The surface is no queued or currently visible. */
    VDP_PRESENTATION_QUEUE_STATUS_IDLE,
    /** The surface is in the queue, and not currently visible. */
    VDP_PRESENTATION_QUEUE_STATUS_QUEUED,
    /** The surface is the currently visible surface. */
    VDP_PRESENTATION_QUEUE_STATUS_VISIBLE,
} VdpPresentationQueueStatus;

/**
 * \brief Poll the current queue status of a surface.
 * \param[in] presentation_queue The queue to query.
 * \param[in] surface The surface to query.
 * \param[out] status The current status of the surface within
 *       the queue.
 * \param[out] first_presentation_time The timestamp of the
 *       VSYNC at which this surface was first displayed. Note
 *       that 0 means the surface was never displayed.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpPresentationQueueQuerySurfaceStatus(
    VdpPresentationQueue         presentation_queue,
    VdpOutputSurface             surface,
    /* output parameters follow */
    VdpPresentationQueueStatus * status,
    VdpTime *                    first_presentation_time
);

/*@}*/

/**
 * \defgroup display_preemption Display Preemption
 *
 * The Window System may operate within a frame-work (such as
 * Linux's VT switching) where the display is shared between the
 * Window System (e.g. X) and some other output mechanism (e.g.
 * the VT.) Given this scenario, the Window System's control of
 * the display could be preempted, and restored, at any time.
 *
 * VDPAU does not mandate that implementations hide such
 * preemptions from VDPAU client applications; doing so may
 * impose extreme burdens upon VDPAU implementations. Equally,
 * however, implementations are free to hide such preemptions
 * from client applications.
 *
 * VDPAU allows implementations to inform the client application
 * when such a preemption has occurred, and then refuse to
 * continue further operation.
 *
 * Similarly, some form of fatal hardware error could prevent further
 * operation of the VDPAU implementation, without a complete
 * re-initialization.
 *
 * The following discusses the behavior of implementations that
 * choose not to hide preemption from client applications.
 *
 * When preemption occurs, VDPAU internally destroys all
 * objects; the client application need not do this. However, if
 * the client application wishes to continue operation, it must
 * recreate all objects that it uses. It is probable that this
 * recreation will not succeed until the display ownership is
 * restored to the Window System.
 *
 * Once preemption has occurred, all VDPAU entry points will
 * return the specific error code \ref
 * VDP_STATUS_DISPLAY_PREEMPTED.
 *
 * VDPAU client applications may also be notified of such
 * preemptions and fatal errors via a callback. See \ref
 * VdpPreemptionCallbackRegister for more details.
 *
 * @{
 */

/**
 * \brief A callback to notify the client application that a
 *        device's display has been preempted.
 * \param[in] device The device that had its display preempted.
 * \param[in] context The client-supplied callback context
 *       information.
 * \return void No return value
 */
typedef void VdpPreemptionCallback(
    VdpDevice device,
    void *   context
);

/**
 * \brief Configure the display preemption callback.
 * \param[in] device The device to be monitored for preemption.
 * \param[in] callback The client application's callback
 *       function. If NULL, the callback is unregistered.
 * \param[in] context The client-supplied callback context
 *       information. This information will be passed to the
 *       callback function if/when invoked.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpPreemptionCallbackRegister(
    VdpDevice             device,
    VdpPreemptionCallback callback,
    void *               context
);

/*@}*/

/**
 * \defgroup get_proc_address Entry Point Retrieval
 *
 * In order to facilitate multiple implementations of VDPAU
 * co-existing within a single process, all functionality is
 * available via function pointers. The mechanism to retrieve
 * those function pointers is described below.
 *
 * @{
 */

/**
 * \brief A type suitable for \ref VdpGetProcAddress
 *        "VdpGetProcAddress"'s \b function_id parameter.
 */
typedef uint32_t VdpFuncId;

/** \hideinitializer */
#define VDP_FUNC_ID_GET_ERROR_STRING                                            (VdpFuncId)0
/** \hideinitializer */
#define VDP_FUNC_ID_GET_PROC_ADDRESS                                            (VdpFuncId)1
/** \hideinitializer */
#define VDP_FUNC_ID_GET_API_VERSION                                             (VdpFuncId)2
/** \hideinitializer */
#define VDP_FUNC_ID_GET_INFORMATION_STRING                                      (VdpFuncId)4
/** \hideinitializer */
#define VDP_FUNC_ID_DEVICE_DESTROY                                              (VdpFuncId)5
/** \hideinitializer */
#define VDP_FUNC_ID_GENERATE_CSC_MATRIX                                         (VdpFuncId)6
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_SURFACE_QUERY_CAPABILITIES                            (VdpFuncId)7
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_SURFACE_QUERY_GET_PUT_BITS_Y_CB_CR_CAPABILITIES       (VdpFuncId)8
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_SURFACE_CREATE                                        (VdpFuncId)9
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_SURFACE_DESTROY                                       (VdpFuncId)10
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_SURFACE_GET_PARAMETERS                                (VdpFuncId)11
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_SURFACE_GET_BITS_Y_CB_CR                              (VdpFuncId)12
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_SURFACE_PUT_BITS_Y_CB_CR                              (VdpFuncId)13
/** \hideinitializer */
#define VDP_FUNC_ID_OUTPUT_SURFACE_QUERY_CAPABILITIES                           (VdpFuncId)14
/** \hideinitializer */
#define VDP_FUNC_ID_OUTPUT_SURFACE_QUERY_GET_PUT_BITS_NATIVE_CAPABILITIES       (VdpFuncId)15
/** \hideinitializer */
#define VDP_FUNC_ID_OUTPUT_SURFACE_QUERY_PUT_BITS_INDEXED_CAPABILITIES          (VdpFuncId)16
/** \hideinitializer */
#define VDP_FUNC_ID_OUTPUT_SURFACE_QUERY_PUT_BITS_Y_CB_CR_CAPABILITIES          (VdpFuncId)17
/** \hideinitializer */
#define VDP_FUNC_ID_OUTPUT_SURFACE_CREATE                                       (VdpFuncId)18
/** \hideinitializer */
#define VDP_FUNC_ID_OUTPUT_SURFACE_DESTROY                                      (VdpFuncId)19
/** \hideinitializer */
#define VDP_FUNC_ID_OUTPUT_SURFACE_GET_PARAMETERS                               (VdpFuncId)20
/** \hideinitializer */
#define VDP_FUNC_ID_OUTPUT_SURFACE_GET_BITS_NATIVE                              (VdpFuncId)21
/** \hideinitializer */
#define VDP_FUNC_ID_OUTPUT_SURFACE_PUT_BITS_NATIVE                              (VdpFuncId)22
/** \hideinitializer */
#define VDP_FUNC_ID_OUTPUT_SURFACE_PUT_BITS_INDEXED                             (VdpFuncId)23
/** \hideinitializer */
#define VDP_FUNC_ID_OUTPUT_SURFACE_PUT_BITS_Y_CB_CR                             (VdpFuncId)24
/** \hideinitializer */
#define VDP_FUNC_ID_BITMAP_SURFACE_QUERY_CAPABILITIES                           (VdpFuncId)25
/** \hideinitializer */
#define VDP_FUNC_ID_BITMAP_SURFACE_CREATE                                       (VdpFuncId)26
/** \hideinitializer */
#define VDP_FUNC_ID_BITMAP_SURFACE_DESTROY                                      (VdpFuncId)27
/** \hideinitializer */
#define VDP_FUNC_ID_BITMAP_SURFACE_GET_PARAMETERS                               (VdpFuncId)28
/** \hideinitializer */
#define VDP_FUNC_ID_BITMAP_SURFACE_PUT_BITS_NATIVE                              (VdpFuncId)29
/** \hideinitializer */
#define VDP_FUNC_ID_OUTPUT_SURFACE_RENDER_OUTPUT_SURFACE                        (VdpFuncId)33
/** \hideinitializer */
#define VDP_FUNC_ID_OUTPUT_SURFACE_RENDER_BITMAP_SURFACE                        (VdpFuncId)34
/** \hideinitializer */
#define VDP_FUNC_ID_OUTPUT_SURFACE_RENDER_VIDEO_SURFACE_LUMA                    (VdpFuncId)35
/** \hideinitializer */
#define VDP_FUNC_ID_DECODER_QUERY_CAPABILITIES                                  (VdpFuncId)36
/** \hideinitializer */
#define VDP_FUNC_ID_DECODER_CREATE                                              (VdpFuncId)37
/** \hideinitializer */
#define VDP_FUNC_ID_DECODER_DESTROY                                             (VdpFuncId)38
/** \hideinitializer */
#define VDP_FUNC_ID_DECODER_GET_PARAMETERS                                      (VdpFuncId)39
/** \hideinitializer */
#define VDP_FUNC_ID_DECODER_RENDER                                              (VdpFuncId)40
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_MIXER_QUERY_FEATURE_SUPPORT                           (VdpFuncId)41
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_MIXER_QUERY_PARAMETER_SUPPORT                         (VdpFuncId)42
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_MIXER_QUERY_ATTRIBUTE_SUPPORT                         (VdpFuncId)43
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_MIXER_QUERY_PARAMETER_VALUE_RANGE                     (VdpFuncId)44
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_MIXER_QUERY_ATTRIBUTE_VALUE_RANGE                     (VdpFuncId)45
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_MIXER_CREATE                                          (VdpFuncId)46
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_MIXER_SET_FEATURE_ENABLES                             (VdpFuncId)47
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_MIXER_SET_ATTRIBUTE_VALUES                            (VdpFuncId)48
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_MIXER_GET_FEATURE_SUPPORT                             (VdpFuncId)49
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_MIXER_GET_FEATURE_ENABLES                             (VdpFuncId)50
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_MIXER_GET_PARAMETER_VALUES                            (VdpFuncId)51
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_MIXER_GET_ATTRIBUTE_VALUES                            (VdpFuncId)52
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_MIXER_DESTROY                                         (VdpFuncId)53
/** \hideinitializer */
#define VDP_FUNC_ID_VIDEO_MIXER_RENDER                                          (VdpFuncId)54
/** \hideinitializer */
#define VDP_FUNC_ID_PRESENTATION_QUEUE_TARGET_DESTROY                           (VdpFuncId)55
/** \hideinitializer */
#define VDP_FUNC_ID_PRESENTATION_QUEUE_CREATE                                   (VdpFuncId)56
/** \hideinitializer */
#define VDP_FUNC_ID_PRESENTATION_QUEUE_DESTROY                                  (VdpFuncId)57
/** \hideinitializer */
#define VDP_FUNC_ID_PRESENTATION_QUEUE_SET_BACKGROUND_COLOR                     (VdpFuncId)58
/** \hideinitializer */
#define VDP_FUNC_ID_PRESENTATION_QUEUE_GET_BACKGROUND_COLOR                     (VdpFuncId)59
/** \hideinitializer */
#define VDP_FUNC_ID_PRESENTATION_QUEUE_GET_TIME                                 (VdpFuncId)62
/** \hideinitializer */
#define VDP_FUNC_ID_PRESENTATION_QUEUE_DISPLAY                                  (VdpFuncId)63
/** \hideinitializer */
#define VDP_FUNC_ID_PRESENTATION_QUEUE_BLOCK_UNTIL_SURFACE_IDLE                 (VdpFuncId)64
/** \hideinitializer */
#define VDP_FUNC_ID_PRESENTATION_QUEUE_QUERY_SURFACE_STATUS                     (VdpFuncId)65
/** \hideinitializer */
#define VDP_FUNC_ID_PREEMPTION_CALLBACK_REGISTER                                (VdpFuncId)66

#define VDP_FUNC_ID_BASE_WINSYS 0x1000

/**
 * \brief Retrieve a VDPAU function pointer.
 * \param[in] device The device that the function will operate
 *       against.
 * \param[in] function_id The specific function to retrieve.
 * \param[out] function_pointer The actual pointer for the
 *       application to call.
 * \return VdpStatus The completion status of the operation.
 */
typedef VdpStatus VdpGetProcAddress(
    VdpDevice device,
    VdpFuncId function_id,
    /* output parameters follow */
    void * *  function_pointer
);

/*@}*/
/*@}*/

/**
 * \defgroup api_winsys Window System Integration Layer
 *
 * The set of VDPAU functionality specific to an individual
 * Windowing System.
 */

#ifdef __cplusplus
}
#endif

#endif

