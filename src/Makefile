####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
CC=gcc
CXX=g++
CXXFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\" 
INCPATH=-I. -I./include 
DEP_INCPATH=

#============ CCP vars ============
CCHECK=@ccheck.py
CCHECK_FLAGS=
PCLINT=@pclint
PCLINT_FLAGS=
CCP=@ccp.py
CCP_FLAGS=
LIB=-lcrypto -lcurl -lpthread


#COMAKE UUID


.PHONY:all
all:test 
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest[0m']"
	@echo "make all done"


.PHONY:ccpclean
ccpclean:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mccpclean[0m']"
	@echo "make ccpclean done"

.PHONY:clean
clean:ccpclean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mclean[0m']"
	rm -rf test 
	rm -rf *.o


.PHONY:love
love:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlove[0m']"
	@echo "make love done"

test: main.o \
  ThreadMgr.o \
  Thread.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest[0m']"
	$(CXX) $(LIB) main.o  ThreadMgr.o\
  	Thread.o -o test 

main.o:main.cpp \
  include/Thread.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mmain.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o main.o main.cpp
	
Thread.o:Thread.cpp \
  include/Thread.h 
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mThread.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o Thread.o Thread.cpp

ThreadMgr.o:ThreadMgr.cpp \
  include/ThreadMgr.h 
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mThreadMgr.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ThreadMgr.o ThreadMgr.cpp
endif #ifeq ($(shell uname -m),x86_64)


