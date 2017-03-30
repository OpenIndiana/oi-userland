# Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.

# Remove current path from @INC. Environment PERL_USE_UNSAFE_INC is override
pop @INC if $INC[-1] eq '.' and !$ENV{PERL_USE_UNSAFE_INC};
