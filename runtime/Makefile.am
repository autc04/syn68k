SUBDIRS = native/i386

lib_LIBRARIES = libsyn68k.a
include_HEADERS = ../include/syn68k_public.h

host_native=@HOST_NATIVE@

SYN68K_CFLAGS=@SYN68K_CFLAGS@

AM_CFLAGS = -DRUNTIME -g -Wpointer-to-int-cast -Werror=pointer-to-int-cast

DIST_SOURCES = 68k.defines.scm 68k.scm alloc.c backpatch.c block.c \
               blockinfo.c callback.c checksum.c deathqueue.c destroyblock.c \
	       diagnostics.c dosinterrupts.c fold.pl hash.c \
	       init.c interrupt.c native.c opcode_dummy.c \
               profile.c rangetree.c recompile.c reg sched.pl syn68k_header.c \
	       translate.c trap.c x86_recog.pl \
\
               include/alloc.h \
	       include/backpatch.h include/block.h include/blockinfo.h \
	       include/callback.h include/ccfuncs.h include/checksum.h \
               include/deathqueue.h include/destroyblock.h \
               include/diagnostics.h include/hash.h include/interrupt.h \
	       include/mapping.h include/native.h include/profile.h \
	       include/rangetree.h include/recompile.h include/translate.h \
	       include/trap.h \
\
	       native/i386/analyze.c native/i386/host-native.c \
	       native/i386/host-native.h native/i386/i386-aux.c \
	       native/i386/i386-aux.h native/i386/main.c \
	       native/i386/process.c native/i386/process.h \
	       native/i386/template.c native/i386/template.h \
	       native/i386/xlate-aux.c native/i386/xlate-aux.h \
	       native/i386/xlate.c native/i386/xlate.h \
	       native/i386/xlatemain.c native/i386/xlatetable.c \
\
	       native/null/Makefile native/null/host-native.h \
               native/null/host-xlate.h

LOCAL_INCLUDES =

LOCAL_INCLUDES += -I$(srcdir)/include \
  -I$(srcdir)/../include -I$(srcdir) -I../include

LOCAL_CFLAGS = -DRUNTIME -Iinclude

all: libsyn68k.a

.c.o:
	$(CC) $(AM_CFLAGS) -c $(LOCAL_INCLUDES) $< -o $@

OBJS =	block.o diagnostics.o hash.o rangetree.o translate.o alloc.o	\
	blockinfo.o trap.o destroyblock.o callback.o init.o interrupt.o	\
	profile.o dosinterrupts.o deathqueue.o checksum.o native.o	\
	backpatch.o recompile.o						\
	mapindex.o mapinfo.o syn68k.o opcode_dummy.o

mapinfo.o:	$(host_native)/host-xlate.h

$(host_native)/host-xlate.h:
	$(MAKE) -C $(host_native) host-xlate.h

.PHONY: $(host_native)/subdir-stmp

$(host_native)/subdir-stmp:
	$(MAKE) -C $(host_native) subdir-stmp

libsyn68k.a: $(OBJS) $(host_native)/subdir-stmp
	$(RM) libsyn68k.a
	$(AR) cq $@ $(OBJS) 				\
                    $(addprefix $(host_native)/,		\
                    $(shell cat $(host_native)/subdir-stmp))
	$(RANLIB) $@

syn68k.o: syn68k.c
	$(CC) -c $(SYN68K_CFLAGS) -Wall -static -Wno-unused\
		$(LOCAL_INCLUDES) syn68k.c -g -o ./syn68k.o

syn68k.c mapindex.c mapinfo.c profileinfo.gz:	../syngen/syngen syn68k_header.c 68k.scm 68k.defines.scm\
				../include/syn68k_private.h    \
				../runtime/include/hash.h      \
				../runtime/include/interrupt.h \
				../runtime/include/trap.h
	if [ "$(srcdir)" != "." ]; then \
	  cp -p $(srcdir)/68k.scm $(srcdir)/syn68k_header.c $(srcdir)/68k.defines.scm . ; \
	fi
	../syngen/syngen -v 68k.scm
	gzip -1f profileinfo

clean-local:
	-rm -rf mapinfo.c syn68k.c mapindex.c \
                profileinfo.gz bucket.c native/i386/asmdata.h \
                native/i386/i386-isa.h native/i386/subdir-stmp \
                native/i386/host-xlate.c native/i386/src-stmp \
                native/i386/i386_stubs native/i386/template \
                native/i386/host-xlate.h native/i386/xlate
	if [ "$(srcdir)" != "." ]; then \
	  rm -f 68k.scm syn68k_header.c 68k.defines.scm; \
	fi
