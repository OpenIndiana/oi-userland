# Current tasks

oi-userland is subject to constant improvement.

Whenever you modify or update a components, please look through the following ongoing tasks:

1.  Fix paths to make rules:

    Use macros for paths: $(WS_TOP)/make-rules and explicit paths should be replaced with $(WS_MAKE_RULES).

2.  Some build dependencies are not detected by the build system, look for instance in configure.ac and add the packages for REQUIRED_PACKAGES manually in a separate list.

3.  For component depending on JPEG libraries switch dependency to to libjpeg8-turbo.

4.  Doxygen update:

    After updating to 1.8.13 the HTML documentation is generated differently.

5.  Move binaries to 64-bit only:

    Libraries should still be delivered as 32- and 64-bit, but binaries are converted to 64-bit only. 

    For autotools-based components set:
```
    PREFERRED_BITS=64
```

Feel free to ask for help on the IRC or developer mailing-list.
