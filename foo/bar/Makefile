# Makefile for B+tree project.

MAIN=btree

CC=g++

CFLAGS= -DUNIX -Wall -g

SRCS =  bt_main.cpp\
	bt_driver.cpp\
	bt_builder.cpp\
	bt_node.cpp\
	bt_index.cpp\
	bt_leaf.cpp\
	bt_scan.cpp 

#OBJS = $(SRCS:.cpp=.o)
OBJS = $(patsubst %.cpp, %.o, $(filter %.cpp,$(SRCS)))

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN):  $(OBJS)
	 $(CC) $(CFLAGS) $(OBJS) -o $(MAIN) 

clean:
	rm -f *.o *~ $(MAIN)
