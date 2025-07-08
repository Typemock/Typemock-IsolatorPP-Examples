VPATH = .:src:../Common/ClassesUnderTest:../Common/GoogleTest

ifdef BITS_32
SRCS = \
main.cpp
endif

ifdef BITS_64
SRCS = \
main.cpp \
Address.cpp \
GPSLocation.cpp \
Person.cpp \
Apocalypse.cpp \
GlobalCMethodTests.cpp \
ArgumentsTests.cpp \
AssertingInteractionTests.cpp \
AssertingNonPublicInteractionTests.cpp \
BehaviorChaining.cpp \
BehaviorSequencingTests.cpp \
CallConstructorTests.cpp \
CallOriginalBehaviorTests.cpp \
ChangeReturnValueTests.cpp \
ConditionalTests.cpp \
CreateRecursiveFakeTests.cpp \
DoInsteadTests.cpp \
FakingAnOutParams.cpp \
FakingNonPublicMethods.cpp \
FakingStaticMethodTests.cpp \
FutureObjectTests.cpp \
IgnoreCallTests.cpp \
InvokeMemberTests.cpp \
LiveObjectsTests.cpp \
PureVirtualTests.cpp \
ReturnByValueTests.cpp \
SettingMembersTests.cpp \
ThrowExceptionTests.cpp 
endif

# application generation flags
C_FLAGS += -fPIC $(CFLAGS)
CXX_FLAGS += -fPIC $(CPPFLAGS)
LD_FLAGS += $(LDFLAGS)

# target (application)

ifdef ARC
TARGET = IsolatorExamplesGCC_UsingStaticLib 
else
TARGET = IsolatorExamplesGCC_UsingDynamicLib
endif



