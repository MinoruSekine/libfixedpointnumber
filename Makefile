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

# Determine variables by BUILD_TYPE.
BUILD_TYPE_CXXFLAGS :=
ifeq ($(BUILD_TYPE), release)
ifneq ($(findstring coverage,$(MAKECMDGOALS)),)
$(error Use BUILD_TYPE=coverage for target "coverage")
endif
BUILD_TYPE_CXXFLAGS += -Ofast
BUILD_TYPE_CXXFLAGS += -DNDEBUG
else ifeq ($(BUILD_TYPE), debug)
ifneq ($(findstring coverage,$(MAKECMDGOALS)),)
$(error Use BUILD_TYPE=coverage for target "coverage")
endif
BUILD_TYPE_CXXFLAGS += -O0
BUILD_TYPE_CXXFLAGS += -g
else ifeq ($(BUILD_TYPE), coverage)
BUILD_TYPE_CXXFLAGS += -O0
BUILD_TYPE_CXXFLAGS += -g
BUILD_TYPE_CXXFLAGS += -fprofile-arcs
BUILD_TYPE_CXXFLAGS += -ftest-coverage
BUILD_TYPE_CXXFLAGS += -fPIC
else
$(error Unknown BUILD_TYPE "$(BUILD_TYPE)")
endif

# CXXFLAGS for warning level.
WARNING_CXXFLAGS :=
WARNING_CXXFLAGS += -Wcast-qual
WARNING_CXXFLAGS += -Wconversion
WARNING_CXXFLAGS += -Wdisabled-optimization
WARNING_CXXFLAGS += -Wdouble-promotion
WARNING_CXXFLAGS += -Weffc++
WARNING_CXXFLAGS += -Wfloat-equal
WARNING_CXXFLAGS += -Winit-self
WARNING_CXXFLAGS += -Winline
WARNING_CXXFLAGS += -Wmissing-declarations
WARNING_CXXFLAGS += -Wmultichar
WARNING_CXXFLAGS += -Wold-style-cast
WARNING_CXXFLAGS += -Woverloaded-virtual
WARNING_CXXFLAGS += -Wpedantic
WARNING_CXXFLAGS += -Wpointer-arith
WARNING_CXXFLAGS += -Wredundant-decls
WARNING_CXXFLAGS += -Wreorder
WARNING_CXXFLAGS += -Wshadow
WARNING_CXXFLAGS += -Wsign-promo
WARNING_CXXFLAGS += -Wswitch-default
WARNING_CXXFLAGS += -Wwrite-strings
WARNING_CXXFLAGS += -Wzero-as-null-pointer-constant
WARNING_CXXFLAGS += -Wall
WARNING_CXXFLAGS += -Wextra
WARNING_CXXFLAGS += -Werror
# Following warning options are valid for C/Obj-C but not for C++ on gcc.
# WARNING_CXXFLAGS += -Wc++-compat
# WARNING_CXXFLAGS += -Wmissing-prototypes
# WARNING_CXXFLAGS += -Wold-style-definition
# WARNING_CXXFLAGS += -Wstrict-prototypes

# Build C++ compiler flags for test.
TEST_CXXFLAGS := $(CXXFLAGS)
TEST_CXXFLAGS += --std=c++11
TEST_CXXFLAGS += $(addprefix -I, $(INCLUDE_DIR))
TEST_CXXFLAGS += $(BUILD_TYPE_CXXFLAGS)
TEST_CXXFLAGS += $(WARNING_CXXFLAGS)

# Coverage config.
GCOVR := gcovr
GCOVR_FLAGS :=
GCOVR_FLAGS += --html
GCOVR_FLAGS += --html-details
GCOVR_FLAGS += --exclude $(TEST_SRC_DIR)
COVERAGE_OUT_DIR := $(OUT_ROOT_DIR)/coverage_report
COVERAGE_HTML_FILE := $(COVERAGE_OUT_DIR)/libfixedpointnumber-coverage.html

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
CPPCHECK_FLAGS += --suppress=missingInclude
CPPCHECK_FLAGS += --error-exitcode=2

CPPCHECK_TARGET_FILES :=
CPPCHECK_TARGET_FILES += $(TEST_SRC_CPP)
CPPCHECK_TARGET_FILES += $(TEST_SRC_HEADER)
CPPCHECK_TARGET_FILES += $(INCLUDE_DIR_HEADER)
CPPCHECK_TARGETS := $(addsuffix .cppcheck, $(CPPCHECK_TARGET_FILES))

# Doxygen config.
DOXYGEN := doxygen
DOXYGEN_OUT_DIR := $(OUT_ROOT_DIR)/doc
DOXYGEN_INDEX_HTML := $(DOXYGEN_OUT_DIR)/html/index.html
DOXYFILE := Doxyfile
DOXYGEN_TARGET_SRCS := $(INCLUDE_DIR_HEADER)

# Targets.
all: test

clean:
	-rm $(TEST_OBJS) $(TEST_DEPS)
	rm -rf $(OUT_ROOT_DIR)

clean-doc:
	-rm $(DOXYGEN_INDEX_HTML)
	rm -rf $(DOXYGEN_OUT_DIR)

test: run-test

run-test: build-test
	@$(TEST_EXEC)

build-test: $(TEST_EXEC)

$(COVERAGE_OUT_DIR):
	mkdir -p $@

coverage: run-test $(COVERAGE_OUT_DIR)
	$(GCOVR) -r . $(GCOVR_FLAGS) -o $(COVERAGE_HTML_FILE)

check: cpplint cppcheck

cpplint: $(CPPLINT_TARGETS)

cppcheck: $(CPPCHECK_TARGETS)

doc: $(DOXYGEN_INDEX_HTML)

$(TEST_EXEC): $(TEST_OBJS)
	@mkdir -p $(dir $@)
	$(COMPILER) -o $(TEST_EXEC) $^ $(LDFLAGS) $(TEST_LDFLAGS) $(TEST_CXXFLAGS)

$(TEST_OBJ_DIR)%.o: $(TEST_SRC_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(COMPILER) $(TEST_CXXFLAGS) -o $@ -c $< -MMD -MP

%.cpplint:
	$(CPPLINT) $(CPPLINT_FLAGS) $*

%.cppcheck:
	$(CPPCHECK) $(CPPCHECK_FLAGS) $*

$(DOXYGEN_INDEX_HTML): $(DOXYGEN_TARGET_SRCS) $(DOXYFILE)
	mkdir -p $(DOXYGEN_OUT_DIR)
	$(DOXYGEN)

ifeq ($(findstring clean,$(MAKECMDGOALS)),)
-include $(TEST_DEPS)
endif

.PHONY: all clean test run-test build-test check cpplint cppcheck doc
