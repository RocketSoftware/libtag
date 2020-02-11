
HEADER=libtag.h
SOURCE=libtag.c
OBJ_DIR=.obj

OBJ_A_64_R=$(OBJ_DIR)/libtag.a.64.o
OBJ_A_64_D=$(OBJ_DIR)/libtag.a.64.d.o
OBJ_A_32_R=$(OBJ_DIR)/libtag.a.32.o
OBJ_A_32_D=$(OBJ_DIR)/libtag.a.32.d.o
OBJ_A_32_R_NX=$(OBJ_DIR)/libtag.a.32.nx.o
OBJ_A_32_D_NX=$(OBJ_DIR)/libtag.a.32.d.nx.o

OBJ_E_64_R=$(OBJ_DIR)/libtag.e.64.o
OBJ_E_64_D=$(OBJ_DIR)/libtag.e.64.d.o
OBJ_E_32_R=$(OBJ_DIR)/libtag.e.32.o
OBJ_E_32_D=$(OBJ_DIR)/libtag.e.32.d.o
OBJ_E_32_R_NX=$(OBJ_DIR)/libtag.e.32.nx.o
OBJ_E_32_D_NX=$(OBJ_DIR)/libtag.e.32.d.nx.o

CXX=xlc
AR=ar
RELEASE=-O
DEBUG=-g 
ASCII=-qascii -D_ENHANCED_ASCII_EXT=0xFFFFFFFF 
CFLAGS=-qlanglvl=extc99:extc89 -I. -D_POSIX_SOURCE \
       -D_OPEN_SYS_FILE_EXT=1 -D_OPEN_SYS\
       -qcsect=libtag
LDFLAGS=-qxplink 
LIB_DIR=lib
LIB_64_R=$(LIB_DIR)/libtag.a
LIB_64_D=$(LIB_DIR)/libtag.d.a
LIB_32_R=$(LIB_DIR)/libtag32.a
LIB_32_D=$(LIB_DIR)/libtag32.d.a
LIB_32_R_NX=$(LIB_DIR)/libtag32.nx.a
LIB_32_D_NX=$(LIB_DIR)/libtag32.d.nx.a

.PHONY:all release debug

all:debug
	@echo ".Done"

debug:$(LIB_64_D) $(LIB_32_D) $(LIB_32_D_NX)
	@echo "Debug"
	
$(LIB_64_D):$(OBJ_A_64_D) $(OBJ_E_64_D) 
	$(AR) cr $@ $^

$(OBJ_A_64_D):$(SOURCE) $(HEADER) 
	$(CXX) -q64 -qxplink $(DEBUG) $(CFLAGS) $(ASCII) -qdebug=file=$(OBJ_A_64_D).dbg -c $(SOURCE) -o $@
$(OBJ_E_64_D):$(SOURCE) $(HEADER) 
	$(CXX) -q64 -qxplink $(DEBUG) $(CFLAGS) -qdebug=file=$(OBJ_E_64_D).dbg -c $(SOURCE) -o $@

$(LIB_32_D):$(OBJ_A_32_D) $(OBJ_E_32_D)
	$(AR) cr $@ $^

$(OBJ_A_32_D):$(SOURCE) $(HEADER) 
	$(CXX) -qxplink $(DEBUG) $(CFLAGS) $(ASCII) -qdebug=file=$(OBJ_A_32_D).dbg -c $(SOURCE) -o $@
$(OBJ_E_32_D):$(SOURCE) $(HEADER) 
	$(CXX) -qxplink $(DEBUG) $(CFLAGS) -qdebug=file=$(OBJ_E_32_D).dbg -c $(SOURCE) -o $@

$(LIB_32_D_NX):$(OBJ_A_32_D_NX) $(OBJ_E_32_D_NX)
	$(AR) cr $@ $^

$(OBJ_A_32_D_NX):$(SOURCE) $(HEADER) 
	$(CXX) $(DEBUG) $(CFLAGS) $(ASCII) -qdebug=file=$(OBJ_A_32_D_NX).dbg -c $(SOURCE) -o $@
$(OBJ_E_32_D_NX):$(SOURCE) $(HEADER) 
	$(CXX) $(DEBUG) $(CFLAGS) -qdebug=file=$(OBJ_E_32_D_NX).dbg -c $(SOURCE) -o $@


release:$(LIB_64_R) $(LIB_32_R) $(LIB_32_R_NX)
	@echo "Release"

$(LIB_64_R):$(OBJ_A_64_R) $(OBJ_E_64_R)
	$(AR) cr $@ $^

$(OBJ_A_64_R):$(SOURCE) $(HEADER) 
	$(CXX) $(RELEASE) -q64 -qxplink $(CFLAGS) $(ASCII) -c $(SOURCE) -o $@
$(OBJ_E_64_R):$(SOURCE) $(HEADER) 
	$(CXX) $(RELEASE) -q64 -qxplink $(CFLAGS) -c $(SOURCE) -o $@

$(LIB_32_R):$(OBJ_A_32_R) $(OBJ_E_32_R)
	$(AR) cr $@ $^

$(OBJ_A_32_R):$(SOURCE) $(HEADER) 
	$(CXX) $(RELEASE) -qxplink $(CFLAGS) $(ASCII) -c $(SOURCE) -o $@
$(OBJ_E_32_R):$(SOURCE) $(HEADER) 
	$(CXX) $(RELEASE) -qxplink $(CFLAGS) -c $(SOURCE) -o $@

$(LIB_32_R_NX):$(OBJ_A_32_R_NX) $(OBJ_E_32_R_NX)
	$(AR) cr $@ $^

$(OBJ_A_32_R_NX):$(SOURCE) $(HEADER)
	$(CXX) $(RELEASE) $(CFLAGS) $(ASCII) -c $(SOURCE) -o $@
$(OBJ_E_32_R_NX):$(SOURCE) $(HEADER) 
	$(CXX) $(RELEASE) $(CFLAGS) -c $(SOURCE) -o $@


.PHONY:clean

clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/*.dbg $(LIB_DIR)/*.a

install:
	@mkdir -p $(PREFIX)/include && cp $(HEADER) $(PREFIX)/include/
	@mkdir -p $(PREFIX)/lib && cp $(LIB_DIR)/*.a $(PREFIX)/lib/

# © 2017-2018 Rocket Software, Inc. or its affiliates. All Rights Reserved.
# ROCKET SOFTWARE, INC.

