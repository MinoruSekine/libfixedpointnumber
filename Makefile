COMPILER := g++

# Parameters which can be specified make command line.
BUILD_TYPE := debug

# Mostly constant parameters for internal use.
INCLUDE_DIR :=
INCLUDE_DIR += include
INCLUDE_DIR_HEADER :=
INCLUDE_DIR_HEADER += $(wildcard $(INCLUDE_DIR)/*.h)

OUT_ROOT_DIR := out
OUT_DIR := $(OUT_ROOT_DIR)/$(BUILD_TYPE)
OBJ_DIR := $(OUT_DIR)/obj
TEST_EXEC := $(OUT_DIR)/fixed_point_test
TEST_SRC_DIR := test
TEST_SRC_CPP := $(wildcard $(TEST_SRC_DIR)/*.cc)
TEST_SRCS := $(TEST_SRC_CPP)
TEST_SRC_HEADER := $(wildcard $(TEST_SRC_DIR)/*.h)
TEST_OBJ_DIR := $(OBJ_DIR)/$(TEST_SRC_DIR)
TEST_OBJS := $(addprefix $(OBJ_DIR)/, $(TEST_SRCS:%.cc=%.o))
TEST_DEPS := $(TEST_OBJS:%.o=%.d)
TEST_LIBS :=
TEST_LIBS += gtest
TEST_LIBS += gtest_main
TEST_LDFLAGS :=
TEST_LDFLAGS += $(addprefix -l, $(TEST_LIBS))
TEST_LDFLAGS += -pthread

# Build C++ compiler flags for test.
TEST_CXXFLAGS := $(CXXFLAGS)
TEST_CXXFLAGS += --std=c++11
TEST_CXXFLAGS += $(addprefix -I, $(INCLUDE_DIR))

# Cpplint config.
CPPLINT := cpplint.py

CPPLINT_FLAGS :=
CPPLINT_FLAGS += --quiet
CPPLINT_FLAGS += --filter=-build/include

CPPLINT_TARGET_FILES :=
CPPLINT_TARGET_FILES += $(TEST_SRC_CPP)
CPPLINT_TARGET_FILES += $(TEST_SRC_HEADER)
CPPLINT_TARGET_FILES += $(INCLUDE_DIR_HEADER)
CPPLINT_TARGETS := $(addsuffix .cpplint, $(CPPLINT_TARGET_FILES))

# Cppcheck config.
CPPCHECK := cppcheck

CPPCHECK_FLAGS :=
CPPCHECK_FLAGS += --language=c++
CPPCHECK_FLAGS += --std=c++11
CPPCHECK_FLAGS += --quiet
CPPCHECK_FLAGS += --enable=all
CPPCHECK_FLAGS += --error-exitcode=2

CPPCHECK_TARGET_FILES :=
CPPCHECK_TARGET_FILES += $(TEST_SRC_CPP)
CPPCHECK_TARGET_FILES += $(TEST_SRC_HEADER)
CPPCHECK_TARGET_FILES += $(INCLUDE_DIR_HEADER)
CPPCHECK_TARGETS := $(addsuffix .cppcheck, $(CPPCHECK_TARGET_FILES))

# Targets.
all: test cpplint

clean:
	-rm $(TEST_OBJS) $(TEST_DEPS)
	rm -rf $(OUT_ROOT_DIR)

test: run-test

run-test: build-test
	@$(TEST_EXEC)

build-test: $(TEST_EXEC)

check: cpplint cppcheck

cpplint: $(CPPLINT_TARGETS)

cppcheck: $(CPPCHECK_TARGETS)

$(TEST_EXEC): $(TEST_OBJS)
	mkdir -p $(dir $@)
	$(COMPILER) -o $(TEST_EXEC) $^ $(LDFLAGS) $(TEST_LDFLAGS)

$(TEST_OBJ_DIR)%.o: $(TEST_SRC_DIR)/%.cc
	mkdir -p $(dir $@)
	$(COMPILER) $(TEST_CXXFLAGS) -o $@ -c $< -MMD -MP

%.cpplint:
	$(CPPLINT) $(CPPLINT_FLAGS) $*

%.cppcheck:
	$(CPPCHECK) $(CPPCHECK_FLAGS) $*

ifeq ($(findstring clean,$(MAKECMDGOALS)),)
-include $(TEST_DEPS)
endif

.PHONY: all clean test run-test build-test check cpplint cppcheck
