SRCDIR = src
OBJECTNAMES = $(shell ls src)
BUILDDIR = build/Release

EXT = mxo
win: EXT = mxe

ARCHIVE_EXT = tgz
STAGING_DIR = CNMAT_Externals

OBJECTS = $(foreach f, $(OBJECTNAMES), $(BUILDDIR)/$(f).$(EXT))
CFILES = $(foreach f, $(OBJECTNAMES), $(SRCDIR)/$(f)/$(f).c)

all: $(CFILES) include/current_version.h
	xcodebuild -target CNMAT-Externs -project CNMAT-Externs.xcodeproj -configuration Release

include/current_version.h:
	echo "#define CNMAT_EXT_VERSION \""`git describe --tags --long`"\"" > include/current_version.h
	echo "#define CNMAT_EXT_COMPILE_DATE \""`date`"\"" >> include/current_version.h

archive: $(STAGING_DIR).$(ARCHIVE_EXT)

$(STAGING_DIR).$(ARCHIVE_EXT):
	$(shell if test ! -d $(STAGING_DIR); then mkdir $(STAGING_DIR); fi)
	cp -r $(BUILDDIR)/*.$(EXT) $(STAGING_DIR)/
	$(shell cd $(SRCDIR) && for f in `ls`; do cp $$f/$$f.maxhelp ../$(STAGING_DIR); done)
	tar zcf $(STAGING_DIR).$(ARCHIVE_EXT) $(STAGING_DIR)

.PHONY: clean
clean:
	rm -f include/current_version.h
	rm -rf build
	xcodebuild clean
	rm -rf $(STAGING_DIR) $(STAGING_DIR).$(ARCHIVE_EXT)
