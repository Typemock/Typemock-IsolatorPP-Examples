# This is an automaticly generated makefile
# operation:
# make -f Makefile <def-flags>
# where <def-flags> are one or more of the following:
# MAKEDEPS=MKD     # for generating dependencies only
#
# ARC=1 to use static lib
# COVERAGE=1 to add coverage

.SILENT:

#
# Defs List include area (compiler, linker, assembler def section + their default command line settings)
# $CC should hold the compiler command line
# $LD should hold the linker command line
include ToolDefList.mk

# the variables below may be overridden from the command line, then the definitions below are ignored
ISOLATOR_INCDIR = /usr/include/typemock
ISOLATOR_LIBDIR = /usr/lib64/typemock
GTEST_FILES_DIR = ../Common/gtest_files

GTEST_INCDIR = $(GTEST_FILES_DIR)
GTEST_LIBDIR = $(GTEST_FILES_DIR)/lib64

BUILD_DIR = LinuxBuild

# BITS_32 is not supported, compilation to be 64 bits only
ifndef BITS_32
ifndef 	BITS_64
BITS_64 = 64
endif
endif

#
# global rules
DEPDIR = $(BUILD_DIR)/.d
OBJDIR = $(BUILD_DIR)/.objs

INC_FLAGS = -I. -I$(ISOLATOR_INCDIR) -I$(GTEST_INCDIR) -I../Common/ClassesDll -I../Common/ClassesUnderTest -I./src

# In GCC6 and above, the flag enable-default-pie has been added. If the GCC version is > 6, we link with -no-pie flag.
GCCVERSIONGTEQ6 := $(shell expr `gcc -dumpversion | cut -f1 -d.` \>= 6)
ifeq "$(GCCVERSIONGTEQ6)" "1"
	NO_PIE := -no-pie
endif

C_FLAGS := -w -O0 -g3 $(INC_FLAGS)
CXX_FLAGS := -w -O0 -g3 $(INC_FLAGS)
TARGET_DIR = ../$(BUILD_DIR)/Debug


LD_FLAGS :=

ifdef BITS_32
TARGET_DIR := $(TARGET_DIR)32
C_FLAGS += -m32
CXX_FLAGS += -m32
OBJDIR := $(OBJDIR)32
DEPDIR := $(DEPDIR)32
LD_FLAGS += -m32
else
TARGET_DIR := $(TARGET_DIR)64
C_FLAGS += -m64
CXX_FLAGS += -m64
OBJDIR := $(OBJDIR)64
DEPDIR := $(DEPDIR)64
LD_FLAGS += -m64
endif

ifdef COVERAGE
C_FLAGS += -Wall -fprofile-arcs -ftest-coverage
CXX_FLAGS += -Wall -fprofile-arcs -ftest-coverage
LD_FLAGS += -Wall -fprofile-arcs -ftest-coverage
endif

$(shell mkdir -p $(DEPDIR) >/dev/null)

ifdef MAKEDEPS
# dependencies only
DEPFLAGS = -MM -MT $(@) -MP -MF $(DEPDIR)/$*.TMPd
else
# full compilation
DEPFLAGS = -MMD -MT $(@) -MP -MF $(DEPDIR)/$*.TMPd
endif

$(shell mkdir -p $(OBJDIR) >/dev/null)
$(shell mkdir -p $(TARGET_DIR) >/dev/null)

POSTCOMPILE = mv -f $(DEPDIR)/$*.TMPd $(DEPDIR)/$*.d

ifdef MAKEDEPS
OUTPUT_OPTION =
else
OUTPUT_OPTION = -o $@
endif

# this include should define SRCS, LIBS, TARGET, and additions to CXX_FLAGS, C_FLAGS and LD_FLAGS:
# It should define C_FLAGS, CXX_FLAGS
include TargetList.mk

OBJS = $(patsubst %,$(OBJDIR)/%.o,$(basename $(SRCS)))

ifdef ARC
LIBS += $(ISOLATOR_LIBDIR)/libisolator.a
else
LIBS += -L$(ISOLATOR_LIBDIR) -l:libisolator.so
endif
LIBS += -L $(GTEST_LIBDIR) -lgtest 


LD_FLAGS += $(NO_PIE)

#%.o: %.c 
#%.o: %.c $(DEPDIR)/%.d
$(OBJDIR)/%.o: %.c $(DEPDIR)/%.d
	echo Compiling $<: $(CC) $(DEPFLAGS) $(CXX_FLAGS) -c $(OUTPUT_OPTION) $<
	$(CC) $(DEPFLAGS) $(C_FLAGS) -c $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)
	
$(OBJDIR)/%.o: %.cpp $(DEPDIR)/%.d
	echo Compiling $<: $(CC) $(DEPFLAGS) $(CXX_FLAGS) -c $(OUTPUT_OPTION) $<
	$(CC) $(DEPFLAGS) $(CXX_FLAGS) -c $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)
	
# derivations for generating preprocessed files
%.i: %.c $(DEPDIR)/%.d
	echo PreProcessing $<: $(CC) $(DEPFLAGS) $(CXX_FLAGS) $(OUTPUT_OPTION) $<
	$(CC) $(DEPFLAGS) $(C_FLAGS) -E $(OUTPUT_OPTION) $<
	
%.i: %.cpp $(DEPDIR)/%.d
	echo PreProcessing $<: $(CC) -E $(DEPFLAGS) $(CXX_FLAGS) $(OUTPUT_OPTION) $<
	$(CC) $(DEPFLAGS) $(CXX_FLAGS) -E $(OUTPUT_OPTION) $<
	
#
# Main Targets Area
#

# the all: target
all: announce $(TARGET_DIR)/$(TARGET)


# cleanup target
clean: announce
	echo Cleaning...
	rm -f $(DEPDIR)/*.TMPd
	rm -f $(DEPDIR)/*.d
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/$(TARGET)
	rm -f $(OBJDIR)/*.gcno
	rm -f $(OBJDIR)/*.gcda
	rm -f $(OBJDIR)/*.gcov
	rm -f $(TARGET_DIR)/$(TARGET)

# ReBuild Target
BuildAll: announce clean all

ReBuild: announce clean all

# The final link
# The libisolator.so must be in LD_LIBRARY_PATH or use -rpath=$(ISOLATOR_LIBDIR)
$(TARGET_DIR)/$(TARGET): $(OBJS)
ifndef MAKEDEPS
	echo Linking $@: $(LD) $(LD_FLAGS) $^ -o $(@) $(LIBS)
	$(LD) $(LD_FLAGS) $^ -o $(@) $(LIBS) -pthread -lrt -ldl -Wl,-rpath=$(ISOLATOR_LIBDIR)
endif

announce:
ifndef ANNOUNCED
        $(eval ANNOUNCED := "Make Parameters: ")
ifdef BITS_32
        $(eval ANNOUNCED += BITS_32)
else
        $(eval ANNOUNCED += BITS_64)
endif
ifdef MAKEDEPS
        $(eval ANNOUNCED += MAKEDEPS)
endif
endif
        echo $(ANNOUNCED)


#
# Dependencies Area
#
## Handle the dependencies directory and include the deps files
$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))

