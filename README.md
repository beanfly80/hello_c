# hello_c

c/c++ test console app with gtest

### Directory & Files
```
+- .vscode/                     // develop with VSCode
+- src
    +- sample
        +- sample_doc_title.h   // test data
        +- sample_doc.cpp       // main function
        +- shared.hpp           // utilities
    +- thirdparty
        +- googletest
+- hello.sln
```

### Prerequisite

- Windows only
- VSCode (Use this IDE)
- MSVC2019
    - C++ 17 should be supported.
    - Verify that v142 toolchain path in .vscode\settings.json
- cmake (for gtest)

### Build & Run
- VSCode - F5(launch hello)
- Directory after build
    ```
    +- .vscode/
    +- src/
    +- x64/Debug/           // out directory
        +- lib/gtest.lib
        +- hello.exe        // executable file
    ```
------
### How to add [gtest](https://google.github.io/googletest)
- [License](src\thirdparty\googletest\LICENSE)
- get code
    ```
    git submodule add git@github.com:google/googletest.git src/thirdparty/googletest
    # Verify .gitmodules
    ```
- Generate related project files by cmake
    ```
    cmake -Hsrc\thirdparty\googletest -Bx64\Debug
    ```
    See 'VSCode - [tasks.json](.vscode/tasks.json) - generate_googletest'

- Add static library to hello.sln
    - Configuration Properties
        - C/C++ > General > Additional Include Directories: 
            >$(SolutionDir)\src\thirdparty\googletest\googletest\include
        - C/C++ > Code Generation > Runtime Library: 
            >Multi-threaded Debug (/MTd).
        - Linker > General > Additional Library Directories
            >%(TargetDir)\lib (depending on the location of gtest.lib)
        - Linker > Input > Additional Dependencies
            >gtest.lib

- Add test code : ref. https://google.github.io/googletest/primer.html
- Run
    - VSCode - F5(launch hello)
