# Current tasks

oi-userland is subject to constant improvement.

Whenever you modify or update a component, please review the list of tasks, below, and apply any of the improvements that are relevant to the component you have modified.  Theses are organized with the easiest changes at the beginning of the list and the more complicated changes near the end:

1.  Use `$(WS_MAKE_RULES)` when including `prep.mk`, `configure.mk`, `ips.mk`, etc., instead of `../make-rules` or `$(WS_TOP)/make-rules`.

    Example: Change occurrences of
    ```Makefile
    include ../../make-rules/prep.mk
    include ../../make-rules/configure.mk
    include ../../make-rules/ips.mk
    ```
    or
    ```Makefile
    include $(WS_TOP)/make-rules/prep.mk
    include $(WS_TOP)/make-rules/configure.mk
    include $(WS_TOP)/make-rules/ips.mk
    ```
    to:
    ```Makefile
    include $(WS_MAKE_RULES)/prep.mk
    include $(WS_MAKE_RULES)/configure.mk
    include $(WS_MAKE_RULES)/ips.mk
    ```

    **Note:** This does not apply to the initial `include` for `shared-macros.mk`.  That file sets up many of the macros that can be used later, including `$(WS_MAKE_RULES)`, so it cannot be referenced via `$(WS_MAKE_RULES)`.
    
2.  Remove `COMPONENT_BUGDB`, if present.

    If the component's `Makefile` includes a line for `COMPONENT_BUGDB`, remove it.  That setting was used by Sun/Oracle and is not relevant to OpenIndiana.

3.  Use `PATH=$(PATH.gnu)` instead of `PATH=/usr/gnu/bin:/usr/bin` in `Makefile`.

    If the component's `Makefile` overrides `PATH` to have `/usr/gnu/bin` at the beginning, the PATH should be set  via the `$(PATH.gnu)` macro.
    
    Example: Change occurrences of
    ```Makefile
    PATH=/usr/gnu/bin:/usr/bin
    ```
    to:
    ```Makefile
    PATH=$(PATH.gnu)
    ```

4.  If there are missing build dependencies, add them in a separate list before the auto-generated runtime dependencies in the `Makefile`.

    You should always run `gmake env-prep` before attempting to build each component, to install all listed dependencies.  If the component fails to build because of e.g a missing header file, it may mean that there are additional build dependencies for the component. You can use `pkg search -r` to identify which component provides the missing file(s).
    
    For software that uses `configure`, you could also check `configure.ac` for software that might be a build dependency.
    
    Once you've identified the missing build dependency, it should be added to the `Makefile`, just before the auto-generated runtime dependencies.
    
    Example: The pkgconfig files `pygtk-2.0.pc` and `pygobject-2.0.pc` are needed to build `image/gimp` but are not needed at runtime, so `gmake REQUIRED_PACKGES` does not detect the dependency.  The components containing them should be added to the Makefile, just before the auto-generated dependencies:
    ```Makefile
    # Build dependencies
    REQUIRED_PACKAGES += library/python/pygobject
    REQUIRED_PACKAGES += library/python/pygtk2

    # Auto-generated dependencies
    ```

5.  For component depending on JPEG libraries switch dependency to libjpeg8-turbo.

6.  Doxygen update:

    After updating to 1.8.13 the HTML documentation is generated differently.

7.  Move binaries to 64-bit only:

    Libraries should still be delivered as 32- and 64-bit, but binaries are converted to 64-bit only.

    For autotools-based components set:
    ```
    PREFERRED_BITS=64
    ```

Feel free to ask for help on the IRC or developer mailing-list.
