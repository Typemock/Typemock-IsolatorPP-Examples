## Typemock Isolator++ C++ Examples

Welcome to the official example repository for Typemock Isolator++, the most advanced mocking framework for C++.

This repository contains real-world and minimal examples that demonstrate how to write unit tests for hard-to-test C++ code, including global functions, constructors, legacy code, and inline and virtual methods, using Typemock’s native C++ engine.

🚀 About Typemock Isolator++
Typemock Isolator++ is a powerful mocking framework for C++ that enables complete isolation and mocking of any function, including those traditionally considered unmockable.

It allows you to:
* Mock global and static functions
* Control constructor behavior
* Intercept inline and virtual methods
* Test legacy code without modifying it
* Mock code in static libraries and external binaries

📚 Learn more in the online documentation

📁 Folder Structure
``` plaintext
├── Isolator++.Examples.VS2022/                    # Visual Studio and MSVC-based examples
└── Isolator++.Examples.GCC/                       # GCC-based examples for WSL or native Linux
├── Common/                                        # Source files
    └── ClassesUnderTest/                          # Classes Under Test
    └── GoogleTest/                                # GTest Testing Framework Test Files
    └── MSTest/                                    # MsTest Testing Framework Test Files
    └── gtest_files/                               # Pre Compiled GTest Libs & Headers
```

🧪 Running Tests

🪟 Windows (Visual Studio / MSVC)

✅ Step 1: Install Typemock Isolator++

🔗 [Installation Guide](https://www.typemock.com/docs/?book=Ipp&page=windows_installation.htm)

👉 [Download Isolator++](https://www.typemock.com/download-isolator-plus-plus/?utm_source=github&utm_medium=readme&utm_campaign=isolatorpp_examples)


✅ Step 2: Clone the Repository
``` plaintext
git clone https://github.com/typemock/Typemock-IsolatorPP-Examples.git
cd Typemock-IsolatorPP-Examples
```

✅ Step 3: Open and Run Tests in Visual Studio

Open Isolator++.Examples.VS2022\Isolator++.Examples.VS2022.sln

Build the solution.

Run the tests using Test Explorer:

![image](https://github.com/user-attachments/assets/cedbf6e7-0d51-47f4-a919-e0931ab9db02)





## 🐧 Linux (GCC / WSL / Ubuntu / Centos)

✅ Step 1: Install Typemock Isolator++ for Linux

🔗 [Installation Guide](https://www.typemock.com/docs/?book=Ipp&page=setting_up_linux.htm)

👉 [Download Isolator++](https://www.typemock.com/download-isolator-plus-plus/?utm_source=github&utm_medium=readme&utm_campaign=isolatorpp_examples)

Install the .deb or .rpm package, depending on your system.

✅ Step 2: Clone the Repository

``` plaintext
git clone https://github.com/typemock/Typemock-IsolatorPP-Examples.git
cd Typemock-IsolatorPP-Examples/Examples/Linux/filesystem_example
```

✅ Step 3: Build and Run Tests
Go to Isolator++.Examples.GCC.

Build the project:
Run
``` plaintext
make
```

📘 Running on Linux

Go to LinuxBuild/Debug64 (by default):
Run 
``` plaintext
export LD_BIND_NOW=1
./IsolatorExamplesGCC_UsingDynamicLib
```
![image](https://github.com/user-attachments/assets/7205202e-438d-4ebf-8aa5-b728be988081)

