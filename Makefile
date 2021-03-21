.DEFAULT_GOAL := build

TARGET = $(notdir $(CURDIR))
BUILDDIR = $(abspath $(CURDIR)/build)

TEST_TARGETS := $(basename $(foreach src,$(wildcard test/test_*.c), $(BUILDDIR)/$(src)))
TESTDIR = $(abspath $(CURDIR)/test)

OPTIONS =

INCLUDES = -Isrc \
           -Ideps/Unity/src

OPTIMIZATION=-O3

override CFLAGS += -Wall -Wextra -pedantic -std=gnu11 $(OPTIMIZATION) $(OPTIONS) $(INCLUDES)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
  ECHOFLAGS = -e
  LDFLAGS = -Wl,-Ldeps/Unity/build/
endif
ifeq ($(UNAME_S),Darwin)
  CFLAGS += -Wno-unused-command-line-argument
  LDFLAGS =
endif

CC = gcc

C_FILES := $(wildcard src/*.c)
C_FILES_TEST := $(wildcard test/*.c)
C_FILES_TEST_DEPS := $(wildcard deps/Unity/src/*.c)

SOURCES := $(C_FILES:.c=.o)
SOURCES_TEST := $(C_FILES_TEST:.c=.o)
SOURCES_TEST_DEPS := $(C_FILES_TEST_DEPS:.c=.o)
OBJS := $(foreach src,$(SOURCES), $(BUILDDIR)/$(src))
OBJS_TEST := $(foreach src,$(SOURCES_TEST), $(BUILDDIR)/$(src))
OBJS_NO_MAIN := $(filter-out %main.o, $(OBJS)) \
                $(C_FILES_TEST_DEPS)

.PHONY: test
.PHONY: clean

all: build

build: $(TARGET)

debug: debug_prepare build

debug_prepare:
	$(eval OPTIMIZATION=-g -pg -O0)

gperftools: gperftools_prepare build

gperftools_prepare:
	$(eval OPTIMIZATION=-DWITHGPERFTOOLS -lprofiler -ltcmalloc -g -pg -O2 -DNDEBUG -fno-inline-functions -fno-inline-functions-called-once -fno-optimize-sibling-calls)

callgrind: callgrind_prepare build

callgrind_prepare:
	$(eval OPTIMIZATION=-g -O2 -DNDEBUG -fno-inline-functions -fno-inline-functions-called-once -fno-optimize-sibling-calls -fno-default-inline -fno-inline)

rebuild: clean $(TARGET)

retest: clean test

run: $(TARGET)
	$(CURDIR)/$(TARGET)

gdb: clean debug_prepare $(TARGET)
	gdb $(CURDIR)/$(TARGET)

test: $(TEST_TARGETS)
	$(foreach var,$(TEST_TARGETS),$(var) && ) echo $(ECHOFLAGS) "Everything in order"

$(TEST_TARGETS): $(OBJS_NO_MAIN) $(OBJS_TEST)
	@echo $(ECHOFLAGS) "[LD]\t$@"
	@$(CC) -o "$@" $@.o $(OBJS_NO_MAIN) $(LDFLAGS) $(OPTIMIZATION)

$(BUILDDIR)/%.o: %.c
	@echo $(ECHOFLAGS) "[CC]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(TARGET): $(OBJS)
	@echo $(ECHOFLAGS) "[LD]\t$@"
	@$(CC) -o "$@" $^ $(LDFLAGS) $(OPTIMIZATION)

clean:
	@echo Cleaning...
	@rm -rf "$(BUILDDIR)/src/"
	@rm -rf "$(BUILDDIR)/test/"
	@rm -rf "$(BUILDDIR)/deps/"
	@rm -f "$(TARGET).o"
	@rm -f "$(TARGET)"
