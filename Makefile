
NAME := lib/liblogger.a
PROJDIR := .

SRCS := src/Logger.cpp src/htmlencode.cpp
LIBS := 

CC := gcc
CXX := g++
LD := $(CXX)
CFLAGS := -O3
CXXFLAGS := -O3
INCLUDE := -I include
AR := ar

OBJS := $(SRCS:%.c=%.o)
OBJS := $(OBJS:%.cpp=%.o)
OBJS := $(OBJS:%.cc=%.o)
DEPS := $(SRCS:%.c=%.d)
DEPS := $(DEPS:%.cpp=%.d)
DEPS := $(DEPS:%.cc=%.d)

all: bin $(NAME) bin/send

bin:
	mkdir bin

$(NAME): $(OBJS)
	$(AR) -r $(NAME) $(OBJS)

bin/send:
	g++ -I include main.cpp bin/liblogger.a -o bin/send

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -MMD -MP -MF $(<:%.c=%.d) -c $< -o $(<:%.c=%.o)

.cc.o:
	$(CXX) $(CXXFLAGS) $(INCLUDE) -MMD -MP -MF $(<:%.cc=%.d) -c $< -o $(<:%.cc=%.o)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDE) -MMD -MP -MF $(<:%.cpp=%.d) -c $< -o $(<:%.cpp=%.o)

.PHONY: clean
clean:
	rm -fr bin
	find $(PROJDIR) -name "*.o" -exec rm {} \;
	find $(PROJDIR) -name "*.d" -exec rm {} \;

-include $(DEPS)

