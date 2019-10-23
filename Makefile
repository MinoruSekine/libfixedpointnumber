COMPILER := g++

# Parameters which can be specified make command line.
BUILD_TYPE := debug

# Mostly constant parameters for internal use.
INCLUDE_DIR :=
INCLUDE_DIR += fixedpointnumber/include
INCLUDE_DIR_HEADER :=
INCLUDE_DIR_HEADER += $(wildcard $(INCLUDE_DIR)/*.h)

OUT_ROOT_DIR := out
OUT_DIR := $(OUT_ROOT_DIR)/$(BUILD_TYPE)
OBJ_DIR := $(OUT_DIR)/obj
TEST_EXEC := $(OUT_DIR)/fixed_point_test
TEST_SRC_DIR := fixedpointnumber/test
TEST_SRC_CPP := $(wildcard $(TEST_SRC_DIR)/*.cc)
TEST_SRCS := $(TEST_SRC_CPP)
TEST_SRC_HEADER := $(wildcard $(TEST_SRC_DIR)/*.h)
TEST_OBJ_DIR := $(OBJ_DIR)/$(TEST_SRC_DIR)
TEST_OBJS := $(addprefix $(OBJ_DIR)/, $(TEST_SRCS:%.cc=%.o))
TEST_DEPS := $(TEST_OBJS:%.o=%.d)
TEST_INCLUDE_DIR := external/google/googletest/googletest/include/

GTEST_SRC_DIR := external/google/googletest/googletest/src
GTEST_SRCS :=
GTEST_SRCS += $(filter-out %/gtest-all.cc, $(wildcard $(GTEST_SRC_DIR)/*.cc))
GTEST_OBJ_DIR := $(OBJ_DIR)/$(GTEST_SRC_DIR)
GTEST_OBJS := $(addprefix $(OBJ_DIR)/, $(GTEST_SRCS:%.cc=%.o))
GTEST_DEPS := $(GTEST_OBJS:%.o=%.d)
GTEST_INCLUDE_DIR := external/google/googletest/googletest

# Build C++ compiler flags for test.
TEST_CXXFLAGS := $(CXXFLAGS)
TEST_CXXFLAGS += --std=c++11
TEST_CXXFLAGS += $(addprefix -I, $(TEST_INCLUDE_DIR))
TEST_CXXFLAGS += $(addprefix -I, $(INCLUDE_DIR))

GTEST_CXXFLAGS :=
GTEST_CXXFLAGS += $(addprefix -I, $(GTEST_INCLUDE_DIR))

# Cpplint config.
CPPLINT_CMD := external/google/styleguide/cpplint/cpplint.py

CPPLINT_FLAGS :=
CPPLINT_FLAGS += --quiet
CPPLINT_FLAGS += --filter=-build/include

CPPLINT_TARGET_FILES :=
CPPLINT_TARGET_FILES += $(TEST_SRC_CPP)
CPPLINT_TARGET_FILES += $(TEST_SRC_HEADER)
CPPLINT_TARGET_FILES += $(INCLUDE_DIR_HEADER)
CPPLINT_TARGETS := $(addsuffix .cpplint, $(CPPLINT_TARGET_FILES))

# Targets.
all: test cpplint

clean:
	-rm $(TEST_OBJS) $(TEST_DEPS) $(GTEST_OBJS) $(GTEST_DEPS)
	rm -rf $(OUT_ROOT_DIR)

test: run-test

run-test: build-test
	@$(TEST_EXEC)

build-test: $(TEST_EXEC)

cpplint: $(CPPLINT_TARGETS)

$(TEST_EXEC): $(TEST_OBJS) $(GTEST_OBJS)
	mkdir -p $(dir $@)
	$(COMPILER) $(LDFLAGS) -o $(TEST_EXEC) $^

$(TEST_OBJ_DIR)%.o: $(TEST_SRC_DIR)/%.cc
	mkdir -p $(dir $@)
	$(COMPILER) $(TEST_CXXFLAGS) -o $@ -c $< -MMD -MP

$(GTEST_OBJ_DIR)%.o: $(GTEST_SRC_DIR)/%.cc
	mkdir -p $(dir $@)
	$(COMPILER) $(TEST_CXXFLAGS) $(GTEST_CXXFLAGS) -o $@ -c $< -MMD -MP

%.cpplint:
	$(CPPLINT_CMD) $(CPPLINT_FLAGS) $*

ifeq ($(findstring clean,$(MAKECMDGOALS)),)
-include $(TEST_DEPS)
-include $(GTEST_DEPS)
endif

.PHONY: all clean test run-test build-test cpplint
