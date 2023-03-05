15+24 was tagged after the solaris/sparc removal but didn't actually
include it, it was based on a slightly earlier commit.

However, this is a set of notes on how the removal is being addressed
http://cr.openjdk.java.net/~mikael/webrevs/8244224/webrev.final/open/webrev/
it's therefore relatively trivial to revert the removal at this point

The patch there was:

wc java-solaris-sparc.patch
  143793  691143 5454385 java-solaris-sparc.patch

And there are 953 files affected by the patch

grep '^---' java-solaris-sparc.patch | awk '{print $2}' | wc -l
     953

297 of those are under test, we probably don't want them (for now, at
any rate)

214 are sparc, which again we don't want

There are some mac/bsd/linux patches left after that

Overall, we want less that half the files in the patch, based on
filename alone.

It turns out that gpatch couldn't cope with the original
patch. Rebuilt it as 64-bit and it was much happier.

For 15+26, I've trimmed about 2/3 of java-solaris-sparc.patch
This is mostly about not restoring SPARC, there's still quite a lot
more cleanup we could do. Also, we shouldn't have to separately patch
the files we created by applying the main patch.
