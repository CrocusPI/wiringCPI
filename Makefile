DYN_VERS_MAJ=1
DYN_VERS_MIN=0

VERSION=$(DYN_VERS_MAJ).$(DYN_VERS_MIN)
DESTDIR=/usr
PREFIX=/local

STATIC=libwiringCPI.a
DYNAMIC=libwiringCPI.so.$(VERSION)

#DEBUG	= -g -O0
DEBUG	= -O2
CC	= gcc
INCLUDE	= -I.
DEFS	= -D_GNU_SOURCE
CFLAGS	= $(DEBUG) $(DEFS) -Wformat=2 -Wall -Winline $(INCLUDE) -pipe -fPIC

LIBS    =

# Should not alter anything below this line
###############################################################################

SRC	=	wiringCPI.c						\
		wiringSerial.c 	wiringRS485.c				\
		cpiHiPri.c cpiThread.c					\
		wiringSPI.c wiringI2C.c					\
		softPWM.c 
		

OBJ	=	$(SRC:.c=.o)

all:		$(DYNAMIC)

static:		$(STATIC)

$(STATIC):	$(OBJ)
	@echo "[Link (Static)]"
	@ar rcs $(STATIC) $(OBJ)
	@ranlib $(STATIC)
#	@size   $(STATIC)

$(DYNAMIC):	$(OBJ)
	@echo "[Link (Dynamic)]"
	@$(CC) -shared -Wl,-soname,libwiringCPI.so -o libwiringCPI.so.$(VERSION) -lpthread $(OBJ)

.c.o:
	@echo [Compile] $<
	@$(CC) -c $(CFLAGS) $< -o $@

.PHONEY:	clean
clean:
	@echo "[Clean]"
	@rm -f $(OBJ) $(OBJ_I2C) *~ core tags Makefile.bak libwiringCPI.*

.PHONEY:	tags
tags:	$(SRC)
	@echo [ctags]
	@ctags $(SRC)


.PHONEY:	install-headers
install-headers:
	@echo "[Install Headers]"
	@install -m 0755 -d			$(DESTDIR)$(PREFIX)/include
	@install -m 0644 wiringCPI.h		$(DESTDIR)$(PREFIX)/include
	@install -m 0644 wiringSerial.h		$(DESTDIR)$(PREFIX)/include
	@install -m 0644 softPWM.h		$(DESTDIR)$(PREFIX)/include
	@install -m 0644 wiringSPI.h		$(DESTDIR)$(PREFIX)/include
	@install -m 0644 wiringI2C.h		$(DESTDIR)$(PREFIX)/include
	@install -m 0644 wiringRS485.h		$(DESTDIR)$(PREFIX)/include


.PHONEY:	install
install:	$(DYNAMIC) install-headers
	@echo "[Install Dynamic Lib]"
	@install -m 0755 -d						$(DESTDIR)$(PREFIX)/lib
	@install -m 0755 libwiringCPI.so.$(VERSION)			$(DESTDIR)$(PREFIX)/lib/libwiringCPI.so.$(VERSION)
	@ln -sf $(DESTDIR)$(PREFIX)/lib/libwiringCPI.so.$(VERSION)	$(DESTDIR)/lib/libwiringCPI.so
	@ldconfig

.PHONEY:	install-static
install-static:	$(STATIC) install-headers
	@echo "[Install Static Lib]"
	@install -m 0755 -d			$(DESTDIR)$(PREFIX)/lib
	@install -m 0755 libwiringCPI.a		$(DESTDIR)$(PREFIX)/lib

.PHONEY:	uninstall
uninstall:
	@echo "[UnInstall]"
	@rm -f $(DESTDIR)$(PREFIX)/include/wiringCPI.h
	@rm -f $(DESTDIR)$(PREFIX)/include/wiringSerial.h
	@rm -f $(DESTDIR)$(PREFIX)/include/wiringRS485.h
	@rm -f $(DESTDIR)$(PREFIX)/include/softPWM.h
	@rm -f $(DESTDIR)$(PREFIX)/include/wiringSPI.h
	@rm -f $(DESTDIR)$(PREFIX)/include/wiringI2C.h
	@rm -f $(DESTDIR)$(PREFIX)/lib/libwiringCPI.*
	@rm -f $(DESTDIR)/lib/libwiringCPI.*
	@ldconfig


.PHONEY:	depend
depend:
	makedepend -Y $(SRC) $(SRC_I2C)

# DO NOT DELETE

wiringCPI.o: softPWM.h wiringCPI.h
wiringSerial.o: wiringSerial.h
cpiHiPri.o: wiringCPI.h
cpiThread.o: wiringCPI.h
wiringSPI.o: wiringCPI.h wiringSPI.h
wiringI2C.o: wiringCPI.h wiringI2C.h
softPWM.o: wiringCPI.h softPWM.h
wiringRS485.o: wiringCPI.h wiringRS485.h 

