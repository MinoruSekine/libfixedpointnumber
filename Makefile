export

# Parameters which can be specified make command line.
BUILD_TYPE := debug

# Mostly constant parameters for internal use.
BUILD_FILES_DIR := build
INCLUDE_DIR :=
INCLUDE_DIR += include
INCLUDE_DIR_HEADER :=
INCLUDE_DIR_HEADER += $(wildcard $(INCLUDE_DIR)/*.h)

# Set C++ compiler for variable CXX
ifeq (, $(shell which $(CXX)))  # In GNU Make, default CXX should be g++
  CXX := clang++
  ifeq (, $(shell which $(CXX)))
    CXX := c++
  endif
endif

# Check C++ compiler instance.
CXX_VERSION := $(shell $(CXX) --version)
ifneq (, $(shell echo "$(CXX_VERSION)" | grep clang))
  CXX_INSTANCE := clang++
else ifneq (, $(shell echo "$(CXX_VERSION)" | grep "Free Software Foundation"))
  CXX_INSTANCE := g++
else
  CXX_INSTANCE := uknown
endif

SYSTEM_INCLUDE_DIRS :=
SYSTEM_INCLUDE_DIRS += /usr/local/include

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
TEST_LIB_DIR :=
TEST_LIB_DIR += /usr/local/lib
TEST_LIBS :=
TEST_LIBS += gtest
TEST_LIBS += gtest_main
TEST_LDFLAGS :=
TEST_LDFLAGS += $(addprefix -L, $(TEST_LIB_DIR))
TEST_LDFLAGS += $(addprefix -l, $(TEST_LIBS))
TEST_LDFLAGS += -pthread

SAMPLE_SRC_ROOT_DIR := sample
SAMPLE_SRC_DIRS := $(wildcard $(SAMPLE_SRC_ROOT_DIR)/*)
SAMPLE_OUT_ROOT_DIR := $(OUT_DIR)/sample
SAMPLE_EXECS := $(subst $(SAMPLE_SRC_ROOT_DIR), $(SAMPLE_OUT_ROOT_DIR), $(SAMPLE_SRC_DIRS))
SAMPLES_CLEAN := $(addsuffix -clean, $(SAMPLE_SRC_DIRS))
ALL_SAMPLE_SRC_CPP := $(foreach dir, $(SAMPLE_SRC_DIRS), $(wildcard $(dir)/*.cc))
ALL_SAMPLE_SRC_HEADER := $(foreach dir, $(SAMPLE_SRC_DIRS), $(wildcard $(dir)/*.h))

ALL_SRC_CPP :=
ALL_SRC_CPP += $(TEST_SRC_CPP)
ALL_SRC_CPP += $(ALL_SAMPLE_SRC_CPP)
ALL_SRC_HEADER :=
ALL_SRC_HEADER += $(TEST_SRC_HEADER)
ALL_SRC_HEADER += $(ALL_SAMPLE_SRC_HEADER)

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
BUILD_TYPE_CXXFLAGS += -DNDEBUG
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
WARNING_CXXFLAGS += -Wno-error=inline
# Following warning options are valid for C/Obj-C but not for C++ on gcc.
# WARNING_CXXFLAGS += -Wc++-compat
# WARNING_CXXFLAGS += -Wmissing-prototypes
# WARNING_CXXFLAGS += -Wold-style-definition
# WARNING_CXXFLAGS += -Wstrict-prototypes

# Build C++ compiler flags for test.
MY_CXXFLAGS := $(CXXFLAGS)
MY_CXXFLAGS += --std=c++11
MY_CXXFLAGS += $(addprefix -I, $(INCLUDE_DIR))
MY_CXXFLAGS += $(addprefix -I, $(SYSTEM_INCLUDE_DIRS))
MY_CXXFLAGS += $(BUILD_TYPE_CXXFLAGS)
MY_CXXFLAGS += $(WARNING_CXXFLAGS)

# Build C++ compiler flags for sample.
SAMPLE_CXXFLAGS := $(CXXFLAGS)
SAMPLE_CXXFLAGS += --std=c++11
SAMPLE_CXXFLAGS += $(addprefix -I, $(INCLUDE_DIR))
SAMPLE_CXXFLAGS += $(BUILD_TYPE_CXXFLAGS)
SAMPLE_CXXFLAGS += $(WARNING_CXXFLAGS)

# Precompiled header.
ifeq ($(CXX_INSTANCE), clang++)
TEST_PRECOMPILED_HEADER := $(TEST_OBJ_DIR)/gtest_compat.h.pch
TEST_PCHXXFLAGS := $(MY_CXXFLAGS) -x c++-header
MY_CXXFLAGS += -include-pch $(TEST_PRECOMPILED_HEADER)
else ifeq ($(CXX_INSTANCE), g++)
TEST_PRECOMPILED_HEADER := $(TEST_OBJ_DIR)/gtest_compat.h.gch
TEST_PCHXXFLAGS := $(MY_CXXFLAGS)
MY_CXXFLAGS += -I $(OBJ_DIR)
endif

ifneq ($(TEST_PRECOMPILED_HEADER), )
$(TEST_PRECOMPILED_HEADER): $(TEST_SRC_DIR)/gtest_compat.h
	@mkdir -p $(dir $@)
	$(CXX) $(TEST_PCHXXFLAGS) -o $@ $<
endif

# Site config.
SITE_SRC_DIR := site_src
SITE_OUT_DIR := $(OUT_ROOT_DIR)/site
SITE_OUT_INDEX_HTML := $(SITE_OUT_DIR)/index.html
SITE_SRC_INDEX_HTML := $(SITE_SRC_DIR)/index.html

# Coverage config.
GCOVR := gcovr
GCOVR_FLAGS :=
GCOVR_FLAGS += --html
GCOVR_FLAGS += --html-details
GCOVR_FLAGS += --exclude $(TEST_SRC_DIR)
GCOVR_FLAGS += --exclude-unreachable-branches
COVERAGE_OUT_DIR := $(SITE_OUT_DIR)/coverage_report
COVERAGE_HTML_FILE := $(COVERAGE_OUT_DIR)/libfixedpointnumber-coverage.html

# Cpplint config.
CPPLINT := cpplint.py

CPPLINT_FLAGS :=
CPPLINT_FLAGS += --quiet
CPPLINT_FLAGS += --filter=-build/include

CPPLINT_TARGET_FILES :=
CPPLINT_TARGET_FILES += $(ALL_SRC_CPP)
CPPLINT_TARGET_FILES += $(ALL_SRC_HEADER)
CPPLINT_TARGET_FILES += $(INCLUDE_DIR_HEADER)
CPPLINT_TARGETS := $(addsuffix .cpplint, $(CPPLINT_TARGET_FILES))

# Cppcheck config.
CPPCHECK := cppcheck
CPPCHECK_SUPPRESION_LIST_TXT := $(BUILD_FILES_DIR)/cppcheck_suppression.txt

CPPCHECK_FLAGS :=
CPPCHECK_FLAGS += --language=c++
CPPCHECK_FLAGS += --std=c++11
CPPCHECK_FLAGS += --quiet
CPPCHECK_FLAGS += --enable=all
CPPCHECK_FLAGS += --inline-suppr
CPPCHECK_FLAGS += --suppressions-list=$(CPPCHECK_SUPPRESION_LIST_TXT)
CPPCHECK_FLAGS += --error-exitcode=2

CPPCHECK_TARGET_FILES :=
CPPCHECK_TARGET_FILES += $(ALL_SRC_CPP)
CPPCHECK_TARGET_FILES += $(ALL_SRC_HEADER)
CPPCHECK_TARGET_FILES += $(INCLUDE_DIR_HEADER)
CPPCHECK_TARGETS := $(addsuffix .cppcheck, $(CPPCHECK_TARGET_FILES))

# Doxygen config.
DOXYGEN := doxygen
DOXYGEN_OUT_DIR := $(SITE_OUT_DIR)/Doxygen
DOXYGEN_INDEX_HTML := $(DOXYGEN_OUT_DIR)/html/index.html
DOXYFILE := $(BUILD_FILES_DIR)/Doxyfile
DOXYFILE_FOR_LATEX := $(OUT_ROOT_DIR)/Doxyfile_LaTeX
DOXYGEN_LATEX := $(DOXYGEN_OUT_DIR)/latex/refman.tex
DOXYGEN_PDF := $(addsuffix .pdf, $(basename $(DOXYGEN_LATEX)))
DOXYGEN_TARGET_SRCS := $(INCLUDE_DIR_HEADER)

# Targets.
all: build-all

build-all: build-test build-sample

run-all: run-test run-sample

clean: clean-sample
	- rm $(TEST_OBJS) $(TEST_DEPS)
	- rm -r $(OUT_ROOT_DIR)

run-test: build-test
	@$(TEST_EXEC)

build-test: $(TEST_EXEC)

$(SITE_OUT_DIR):
	mkdir -p $@

$(COVERAGE_OUT_DIR): $(SITE_OUT_DIR)
	mkdir -p $@

coverage: run-test $(COVERAGE_OUT_DIR)
	$(GCOVR) -r . $(GCOVR_FLAGS) -o $(COVERAGE_HTML_FILE)

check: cpplint cppcheck

cpplint: $(CPPLINT_TARGETS)

cppcheck: $(CPPCHECK_TARGETS)

doxygen: $(DOXYGEN_INDEX_HTML)

doc: doxygen coverage

site: $(SITE_OUT_INDEX_HTML) doxygen coverage

$(TEST_EXEC): $(TEST_OBJS)
	@mkdir -p $(dir $@)
	$(CXX) -o $(TEST_EXEC) $^ $(LDFLAGS) $(TEST_LDFLAGS) $(MY_CXXFLAGS)

$(TEST_OBJ_DIR)%.o: $(TEST_SRC_DIR)/%.cc $(TEST_PRECOMPILED_HEADER)
	@mkdir -p $(dir $@)
	$(CXX) $(MY_CXXFLAGS) -o $@ -c $< -MMD -MP

build-sample: $(SAMPLE_EXECS)

run-sample: run-calc_half run-calc_pi run-dump_range

run-calc_half: $(SAMPLE_OUT_ROOT_DIR)/calc_half/calc_half
	$^ 3.1

run-calc_pi: $(SAMPLE_OUT_ROOT_DIR)/calc_pi/calc_pi
	$^

run-dump_range: $(SAMPLE_OUT_ROOT_DIR)/dump_range/dump_range
	$^ 6 3.0 3.5

clean-sample: $(SAMPLES_CLEAN)

$(SAMPLE_OUT_ROOT_DIR)/%: .FORCE
	$(MAKE) OUT_DIR=$(SAMPLE_OUT_ROOT_DIR)/$(notdir $@) -f $(SAMPLE_SRC_ROOT_DIR)/$(notdir $@)/Makefile

%-clean: .FORCE
	$(MAKE) OUT_DIR=$(SAMPLE_OUT_ROOT_DIR)/$(notdir $(subst -clean,,$@)) -f $(subst -clean,,$@)/Makefile clean

%.cpplint: .FORCE
	$(CPPLINT) $(CPPLINT_FLAGS) $*

%.cppcheck: .FORCE
	$(CPPCHECK) $(CPPCHECK_FLAGS) $*

$(DOXYGEN_OUT_DIR): $(SITE_OUT_DIR)
	mkdir -p $@

$(DOXYGEN_INDEX_HTML): $(DOXYGEN_TARGET_SRCS) $(DOXYFILE) $(DOXYGEN_OUT_DIR)
	$(DOXYGEN) $(DOXYFILE)

$(SITE_OUT_INDEX_HTML): $(SITE_OUT_DIR) $(SITE_SRC_INDEX_HTML)
	cp -f $(SITE_SRC_INDEX_HTML) $@

latex: $(DOXYGEN_LATEX)

$(DOXYGEN_LATEX): $(DOXYGEN_TARGET_SRCS) $(DOXYFILE_FOR_LATEX) $(DOXYGEN_OUT_DIR)
	$(DOXYGEN) $(DOXYFILE_FOR_LATEX)

$(DOXYFILE_FOR_LATEX): $(DOXYFILE)
	@mkdir -p $(dir $(DOXYFILE_FOR_LATEX))
	sed -e "s/^\([^#]*GENERATE_LATEX *= *\)NO/\1YES/g" -e "s/^\([^#]*GENERATE_HTML *= *\)YES/\1NO/g" $(DOXYFILE) > $@

pdf: $(DOXYGEN_PDF)

$(DOXYGEN_PDF): $(DOXYGEN_LATEX)
	$(MAKE) -C $(dir $^) pdf

ifeq ($(findstring clean,$(MAKECMDGOALS)),)
-include $(TEST_DEPS)
endif

.FORCE:
.PHONY: all clean build-sample build-test run-test check cpplint cppcheck doc doxygen site latex
