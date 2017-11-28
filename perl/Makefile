#
# Makefile for perl support modules and routine
#
# This Makefile generates "perl.mak", which contains the actual build and
# installation directions.
#
# PERL_PATH must be defined to be the path of the Perl interpreter to use.
#
# prefix must be defined as the Git installation prefix.
#
# localedir must be defined as the path to the locale data.
#
# perllibdir may be optionally defined to override the default Perl module
# installation directory, which is relative to prefix. If perllibdir is not
# absolute, it will be treated as relative to prefix.
#
# NO_PERL_MAKEMAKER may be defined to use a built-in Makefile generation method
# instead of Perl MakeMaker.

makfile:=perl.mak
modules =

PERL_PATH_SQ = $(subst ','\'',$(PERL_PATH))
prefix_SQ = $(subst ','\'',$(prefix))
localedir_SQ = $(subst ','\'',$(localedir))

ifndef V
	QUIET = @
endif

# If a library directory is provided, and it is not an absolute path, resolve
# it relative to prefix.
ifneq ($(perllibdir),)
ifneq ($(filter /%,$(firstword $(perllibdir))),)
perllib_instdir = $(perllibdir)
else
perllib_instdir = $(prefix)/$(perllibdir)
endif
endif

all install instlibdir: $(makfile)
	$(QUIET)$(MAKE) -f $(makfile) $@

clean:
	$(QUIET)test -f $(makfile) && $(MAKE) -f $(makfile) $@ || exit 0
	$(RM) ppport.h
	$(RM) $(makfile)
	$(RM) $(makfile).old
	$(RM) PM.stamp

$(makfile): PM.stamp

ifdef NO_PERL_MAKEMAKER

ifeq ($(perllib_instdir),)
perllib_instdir = $(prefix)/lib
endif

instdir_SQ = $(subst ','\'',$(perllib_instdir))

modules += Git
modules += Git/I18N
modules += Git/IndexInfo
modules += Git/Packet
modules += Git/SVN
modules += Git/SVN/Memoize/YAML
modules += Git/SVN/Fetcher
modules += Git/SVN/Editor
modules += Git/SVN/GlobSpec
modules += Git/SVN/Log
modules += Git/SVN/Migration
modules += Git/SVN/Prompt
modules += Git/SVN/Ra
modules += Git/SVN/Utils

$(makfile): ../GIT-CFLAGS ../GIT-PERL-DEFINES Makefile
	echo all: private-Error.pm Git.pm Git/I18N.pm > $@
	set -e; \
	for i in $(modules); \
	do \
		if test $$i = $${i%/*}; \
		then \
			subdir=; \
		else \
			subdir=/$${i%/*}; \
		fi; \
		echo '	$(RM) blib/lib/'$$i'.pm' >> $@; \
		echo '	mkdir -p blib/lib'$$subdir >> $@; \
		echo '	cp '$$i'.pm blib/lib/'$$i'.pm' >> $@; \
	done
	echo '	$(RM) blib/lib/Error.pm' >> $@
	'$(PERL_PATH_SQ)' -MError -e 'exit($$Error::VERSION < 0.15009)' || \
	echo '	cp private-Error.pm blib/lib/Error.pm' >> $@
	echo install: >> $@
	set -e; \
	for i in $(modules); \
	do \
		if test $$i = $${i%/*}; \
		then \
			subdir=; \
		else \
			subdir=/$${i%/*}; \
		fi; \
		echo '	$(RM) "$$(DESTDIR)$(instdir_SQ)/'$$i'.pm"' >> $@; \
		echo '	mkdir -p "$$(DESTDIR)$(instdir_SQ)'$$subdir'"' >> $@; \
		echo '	cp '$$i'.pm "$$(DESTDIR)$(instdir_SQ)/'$$i'.pm"' >> $@; \
	done
	echo '	$(RM) "$$(DESTDIR)$(instdir_SQ)/Error.pm"' >> $@
	'$(PERL_PATH_SQ)' -MError -e 'exit($$Error::VERSION < 0.15009)' || \
	echo '	cp private-Error.pm "$$(DESTDIR)$(instdir_SQ)/Error.pm"' >> $@
	echo instlibdir: >> $@
	echo '	echo $(instdir_SQ)' >> $@

else

# This may be empty if perllibdir was empty.
instdir_SQ = $(subst ','\'',$(perllib_instdir))

$(makfile): Makefile.PL ../GIT-CFLAGS ../GIT-PERL-DEFINES
	$(PERL_PATH) $< \
	  PREFIX='$(prefix_SQ)' INSTALL_BASE='' \
	  LIB='$(instdir_SQ)' \
	  --localedir='$(localedir_SQ)'

endif

# this is just added comfort for calling make directly in perl dir
# (even though GIT-CFLAGS aren't used yet. If ever)
../GIT-CFLAGS ../GIT-PERL-DEFINES:
	$(MAKE) -C .. $(@F)
