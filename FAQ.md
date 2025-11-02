# 🧠 Typemock Isolator++ FAQ (C and C++) — Complete v5 Edition

This FAQ includes setup, runtime issues, faking examples, and advanced topics like threading, linking, and CI/CD deployment.

---

## 🔧 Common Errors & Setup

<details>
<summary><strong>Why don’t my fakes apply at runtime?</strong></summary>

Checks to make first:
- **Headers & libs**: include the v5 headers and link the Isolator++ runtime (e.g., `isolator5.h` and `isolator.dll` / `isolator.so`).
- **Symbols**: build your tests with debug symbols so hooks can resolve (GCC/Clang: `-g`, MSVC: `/Zi` + PDBs).
- **Toolchain**: use a supported compiler (GCC ≥ 5.4, Clang ≥ 10, MSVC 2015+), with C++11+.
- **Runtime search paths**: ensure the dynamic library is discoverable (`LD_LIBRARY_PATH`).
- **Optimizations**: very aggressive LTO/IPO can inline/remove targets; reduce these for test builds.

📘 [Setup Guide →](https://www.typemock.com/docs/?book=Ipp&page=setup.htm)
</details>

---

<details>
<summary><strong>What does “Isolator++ is a runtime library” mean?</strong></summary>

You link the Typemock runtime into your test binary; **there is no separate “mocking exe”**.  
At runtime, Isolator++ intercepts function/method calls and applies your configured behaviors.

📘 [Getting Started →](https://www.typemock.com/docs/?book=Ipp&page=getting_started.htm)
</details>

---

## 🧱 v5 Mocking Techniques (Fluent)

<details>
<summary><strong>How do I fake a global/free function?</strong></summary>

```cpp
#include "isolator5.h"

int GlobalFunc();

TEST(Fakes, GlobalFunction_v5)
{
    auto a = Isolator();
    a.CallTo(::GlobalFunc).WillReturn(42);

    EXPECT_EQ(42, GlobalFunc());
}
```
📘 [Fake Global Functions →](https://www.typemock.com/docs/?book=Ipp&page=faking_static_and_global_functions.htm)
</details>

---

<details>
<summary><strong>How do I fake a static method?</strong></summary>

```cpp
auto a = Isolator();
a.CallTo(UserStore::Connect).WillReturn(true);
```
📘 [Fake Static methods →](https://www.typemock.com/docs/?book=Ipp&page=faking_static_and_global_functions.htm)
</details>

---

<details>
<summary><strong>How do I fake a member method for all instances vs a specific instance?</strong></summary>

```cpp
auto a = Isolator();

// All instances
auto futureHandle = a.Fake.All<Calculator>();
a.CallTo(futureHandle.Add(A::Any())).WillReturn(99);

// Specific object
Calculator c;
a.CallTo(c.Add(A::Any())).WillReturn(7);
```
📘 [Faking Member Methods →](https://www.typemock.com/docs/?book=Ipp&page=faking_concrete_classes.htm)
</details>

---

<details>
<summary><strong>How do I control future constructor calls (objects created later)?</strong></summary>

```cpp
auto a = Isolator();
auto handle = a.Fake.All<Calculator>();
a.CallTo(handle.Add()).WillReturn(5);
RunProductionCode();
```
📘 [Faking Future Instances →](https://www.typemock.com/docs/?book=Ipp&page=faking_future_and_all_instance.htm)
</details>

---

<details>
<summary><strong>How do I limit fakes to a scope (During filters)?</strong></summary>

This is an **Enterprise feature**.

```cpp
auto a = Isolator();
a.CallTo(::LookupUser()).During(
  A::Call(DoExpensiveOperation)
).WillReturn("eli");
```
📘 [During Filters →](https://www.typemock.com/docs/?book=Ipp&page=during_filters.htm)
</details>

---

## ⚙️ Integration & Frameworks

<details>
<summary><strong>Which C++ test frameworks can I use?</strong></summary>

**Google Test**, **Catch2**, **Boost.Test**, **CppUnit**, and **MSTest for C++** are supported.

📘 [Framework Compatibility →](https://www.typemock.com/docs/?book=Ipp&page=supported_test_frameworks.htm)
</details>

---

<details>
<summary><strong>How do I add Isolator++ to my build?</strong></summary>

```cmake
find_library(ISOLATOR_LIB isolator REQUIRED PATHS /opt/typemock/lib)
include_directories(/opt/typemock/include)

add_executable(mytests tests.cpp)
target_link_libraries(mytests PRIVATE ${ISOLATOR_LIB} pthread)
```
📘 [Setup Windows →](https://www.typemock.com/docs/?book=Ipp&page=configuring_a_project_for_firs.htm)
📘 [Setup Linux →](https://www.typemock.com/docs/?book=Ipp&page=setting_up_linux_test.htm)
</details>

---

## 🐧 Linux / Toolchain Notes

<details>
<summary><strong>Any special flags for Linux or Clang/GCC?</strong></summary>

- Build with `-g` for symbols.  
- Disable LTO/IPO for test builds.  
- Use `-fPIC` for shared libs.  

</details>

---

## ⚡ Performance & Coverage

<details>
<summary><strong>Will faking slow my suite?</strong></summary>

Overhead is low.  
Fake only what you need.
Disable logs and verbose/

</details>

---

<details>
<summary><strong>Can I use coverage tools with Isolator++?</strong></summary>

Yes — works with **gcov**, **lcov**, **llvm-cov**, and Windows coverage tools.

📘 [Code Coverage →](https://www.typemock.com/docs/?book=Ipp&page=code_coverage_tool_integration.htm)
</details>

---

## ☁️ CI/CD & Licensing

<details>
<summary><strong>How do I run on CI and build agents?</strong></summary>

Enterprise feature — configure license via:
```bash
IsolatorConfigurator [key] [license]
```
or include in header.

📘 [Enterprise License →](https://www.typemock.com/docs/?book=Ipp&page=setting_the_enterprise_license.htm)
</details>

---

## 🧩 Advanced Scenarios

<details>
<summary><strong>How do I stub I/O, sockets, or file system access?</strong></summary>

```cpp
auto a = Isolator();
a.CallTo(::ReadFile).WillReturn(std::string{"mock-data"});
```
</details>

---

<details>
<summary><strong>How do I verify that a behavior occurred?</strong></summary>

Use your test framework assertions or fake spies to verify calls.
```cpp
auto a = Isolator();
auto fake = a.Fake.Instance<Calculator>();
// use fake...

// verify 
a.CallTo(fake.Add(A::Eq(1))).VerifyWasCalled();
```

📘 [Verifying Calls →](https://www.typemock.com/docs/?book=Ipp&page=asserting_that_a_method_was_ca.ht)
</details>

---

## 🧰 Additional Troubleshooting Topics

### Linking & Runtime Loading
Link `isolator.lib` or `libisolator.so` correctly.  
Add library path using `-L` or `Linker → Additional Library Directories`.

📘 [Build and Link Guide →](https://www.typemock.com/docs/?book=Ipp&page=installation.htm)

---

### Object Lifetime and Destructors
Keep the `Isolator()` object alive while tests run. Avoid faking destructors directly.

---

### Virtual vs Non-Virtual Methods
Fakes apply to both; non-virtual fakes don’t require refactoring.

📘 [Faking Non-Virtual →](https://www.typemock.com/docs/?book=Ipp&page=faking_abstract_classes.htm)

---

### Templates and Inline Functions
Ensure instantiations are visible; disable LTO for inline symbols.

---

### Thread Safety
Typemock Isolator++ is Thread-safe and fakes can be fakes across threads.
to limit a fake to a single thead use 

```cpp
During(A::Thread(GetCurrentThreadId())));
```

📘 [During Thread Safety →](https://www.typemock.com/docs/?book=Ipp&page=builtin_during_filters.htm)

---

### Exceptions
```cpp
a.CallTo(&Service::Connect).WillThrow(std::runtime_error("fail"));
```
📘 [Faking with Exceptions →](https://www.typemock.com/docs/?book=Ipp&page=throw_behavior.htms)

---

### Mocking C Functions
```cpp
int LegacyFunc(const char*);
auto a = Isolator();
a.CallTo(::LegacyFunc()).WillReturn(0);
```
📘 [Mocking C Functions →](https://www.typemock.com/docs/?book=Ipp&page=faking_global_methods.htm)

---

### Architecture Compatibility
Use correct runtime for 32/64-bit; don’t mix.
the 32bit libs are in /bin directory under the installation and the 64bit libs are in the /bin/64 diretory

---

### Debugging Crashes or Unresolved Fakes
use Configuration.exe --log_enable or on windows run the Configurator

for *During* use 
```cpp
IsolatorConfig::VerboseLogging
```

📘 [Troubleshooting →](https://www.typemock.com/docs/?book=Ipp&page=suppressing_additional_message.htm)

---

## 🧭 Summary

Typemock Isolator++ v5 enables you to:
- ✅ Mock any function, static, or method (virtual or not)  
- ✅ Scope and verify calls with clean syntax  
- ✅ Test legacy code on Windows and Linux  
- ✅ Integrate into CI/CD securely  
- ✅ Use AI-based suggestions via LLM API

---

### 📚 Helpful Links
- [Isolator++ Cookbook](https://www.typemock.com/docs/?book=Ipp&page=cookbook.htm)
- [Download Isolator++](https://www.typemock.com/download-isolator-plus-plus/)
- [Setting Enterprise License](https://www.typemock.com/docs/?book=Ipp&page=setting_the_enterprise_license.htm)
- [Typemock Blog & Release Notes](https://www.typemock.com/blog/)
