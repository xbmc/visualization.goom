SUBDIRS=src

INSTALLDIRS=addon

clean-local:
	make -C lib/goom2k4-0 clean

install-data-local:
	@for dir in $(INSTALLDIRS); do \
	  cp -r $$dir/* $(prefix); \
        done
