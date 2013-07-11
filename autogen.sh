#! /bin/bash

# $Id: autogen.sh 65 2004-12-24 19:51:17Z ctm $

set -o errexit -o nounset -o noclobber

test -z "$LIBTOOL" && for LIBTOOL in glibtool libtool; do
  ($LIBTOOL --version) < /dev/null > /dev/null 2>&1 && break
done
test -z "$LIBTOOLIZE" && for LIBTOOLIZE in glibtoolize libtoolize; do
  ($LIBTOOLIZE --version) < /dev/null > /dev/null 2>&1 && break
done

$LIBTOOLIZE
aclocal
autoheader
automake --add-missing
autoconf
