# Categories layout

Currently we are moving to categories layout, like pkgsrc or FreeBSD ports. Individual components should be moved to corresponding category as they are touched.
In contrast to pkgsrc we use subcategories for related components, for example, library/openssl.

## List of categories

Category       | Description / FMRIs
-------------- | --------------------
archiver       | archiver/\*, compress/\*
closed         | closed source components
database       | database/\*, service/database/\*
developer      | development tools (developer/\*)
desktop        | gnome, mate, enlightenment, common tools (desktop/\*)
editor         | editor/\*
encumbered     | packages which should go to /hipster-encumbered
fonts          | system/font/\*, print/filter/ghostscript/fonts/\*
games          | games/\*
image          | image/\*
inputmethod    | system/input-method/\*
library        | common libraries
mail           | mail/\*
meta-packages  | metapackages
multimedia     | audio/\*, codec/\*,video/\*
network        | service/network/\*, network/\*
openindiana    | illumos and OpenIndiana-specific software
perl           | perl and perl modules
print          | print/\*
python         | python and python modules
runtime        | runtime/\* which have no other dedicated category
ruby           | ruby and ruby modules
shell          | shell/\*
sysutils       | security/\*, backup/\*, test/\*, system/\*, benchmark/\*, etc
text           | text/\*
web            | web/\*
x11            | x11/\*
