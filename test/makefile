EXEC_A=autodetect_a
EXEC_E=autodetect_e
SOURCE=main.c
OBJS_DIR=.obj/
OBJS_A=$(patsubst %.c,$(OBJS_DIR)%.a.o,$(SOURCE))
OBJS_E=$(patsubst %.c,$(OBJS_DIR)%.e.o,$(SOURCE))
SOURCE_LIB=../libtag.c ../libtag.h	

CXX=xlc
DEBUG_OPT=-qdebug=level=9 -qdebug=file=$@.dbg
ASCII=-qascii -D_ENHANCED_ASCII_EXT=0xFFFFFFFF 
CFLAGS=-q64 -qxplink -qlanglvl=extended:extc89:extc99 -I../ -D_POSIX_SOURCE 
LDFLAGS=-qxplink -q64 -L../
LIB=../lib/libtag.d.a

all:$(EXEC_A) $(EXEC_E)
	printf "Done"

$(EXEC_A):$(OBJS_A) $(LIB)
	$(CXX) $(LDFLAGS) -o $@ $^

$(OBJS_DIR)%.a.o:%.c
	$(CXX) $(CFLAGS) $(ASCII) $(DEBUG_OPT) -c $< -o $@

$(EXEC_E):$(OBJS_E) $(LIB)
	$(CXX) $(LDFLAGS) -o $@ $^

$(OBJS_DIR)%.e.o:%.c
	$(CXX) $(CFLAGS) $(DEBUG_OPT) -c $< -o $@

$(LIB):$(SOURCE_LIB)
	make -C ../

.PHONY:clean
clean:
	-rm -f $(EXEC_A) $(EXEC_E) $(OBJS_DIR)*.o $(OBJS_DIR)*.dbg 

# © 2018 Rocket Software, Inc. or its affiliates. All Rights Reserved.
# ROCKET SOFTWARE, INC.

