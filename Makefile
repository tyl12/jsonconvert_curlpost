##sudo apt-get install libcurl4-openssl-dev
#
#CXXFLAGS = -std=c++11 -Wall -Wno-strict-aliasing -Wno-unused-variable
#
##包含头文件路径
#SUBDIR   = $(shell ls ./ -R | grep /)
#SUBDIRS  = $(subst :,/,$(SUBDIR))
#INCPATHS += -I./include -I./
#SOURCE = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)*.cpp))
#
#VPATH = $(subst : ,:,$(SUBDIR))./
#OBJS = $(patsubst %.cpp,%.o,$(SOURCE))
#OBJFILE  = $(foreach dir,$(OBJS),$(notdir $(dir)))
#OBJSPATH = $(addprefix obj/,$(OBJFILE)) 
#
#LDFLAGS += -pthread  -L/usr/lib/x86_64-linux-gnu -lboost_regex
#
#EXE = ./jsonAPI
#
#$(EXE): $(SOURCE)
#	g++ -std=c++11  -DUSE_BOOST -o $(EXE) $(SOURCE)  $(INCPATHS) $(LDFLAGS)
#
#.PHONY:clean all
#clean:
#	rm -rf $(OBJFILE)
#	rm -rf $(EXE)
#
#all: $(EXE)

all:
	g++ -std=c++11 jsonAPI.cpp curlPost.cpp test.cpp -o test -lcurl
