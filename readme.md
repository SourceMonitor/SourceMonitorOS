# SourceMonitorOS

[Jim Wanner][wannerjim] retired from software development. This project aims to get the original SourceMonitor code of [Campwood Software LTD][campwoodsw] to become open source.

## Motivation

Because of some licensed code and other issues a refactoring of the existing code base will be not done. Instead of this a re-write from scratch is aimed according to the functionality known from the original.

_Getting there is half the fun. - Konfuzius_

_A journey of a thousand miles begins with a single step. - Laotse_

## Definitions for environment

- Programming language: [C++17][cpp17]
- Build system: [CMake][cmake], minimum version 3.5
- License: [MIT][licensemit]
- Framework: [QT][qt] in version 6.2 LTS

### Compiling

To compile the project the following prerequisites must be installed:

- [CMake][cmake], minimum version 3.5
- [QT][qt] in version 6.2 LTS

A compiler should be installed during the installation of [QT][qt]. If you wish to use another compiler, you have to take care about this by yourself.

Once the prerequisites are installed, you have to open the [CMakeLists.txt project][project_file] file of the root folder in [QT Creator][tool_qt_creator], select the kit of your choice and then press `Configure Project`. Then you can compile the code.

## Contribution

This project is open source. Every kind of contribution is welcome. Usually by a fork and a pull request. The team will be happy about any kind of support. See here an incomplete list of possible areas you're able to support:

- [![CPP](https://skillicons.dev/icons?i=cpp)](https://skillicons.dev) - [C++][cpp17], the basic programming language
- [![CMake](https://skillicons.dev/icons?i=cmake)](https://skillicons.dev) - [CMake][cmake], the build system used
- [![git](https://skillicons.dev/icons?i=git)](https://skillicons.dev) - [git][gitscm], the used code versioning system
- [![GitHub](https://skillicons.dev/icons?i=github)](https://skillicons.dev) - [GitHub][github], the hoster of the project code
- [![GitHubActions](https://skillicons.dev/icons?i=githubactions)](https://skillicons.dev) - [GitHubActions][githubactions], used for CI/CD processes and other automations
- [![Markdown](https://skillicons.dev/icons?i=md)](https://skillicons.dev) - [Markdown][markdown], used for documentation, in [GitHub flavor][githubmarkdown]
- [![QT](https://skillicons.dev/icons?i=qt)](https://skillicons.dev) - [QT][qt], the used framework

## Project folder organization

Allthough there are CMake files existing up to know you need to run them using QT Creator.

- In the folder [documentation][folder_documentation] you can find the documentation of SourceMonitorOS
- In the folder [playground][folder_playground] you can find small programs for several tests
- In the folder [smcli][folder_smcli] you can find the command line client of SourceMonitorOS
- In the folder [smcore][folder_smcore] you can find the core functionality of SourceMonitorOS
- In the folder [smgui][folder_smgui] you can find the UI of SourceMonitorOS
- In the folder [smtest][folder_smtest] you can find the tests of at least the [smcore][folder_smcore].

[campwoodsw]: https://www.campwoodsw.com/sourcemonitor.html
[cmake]: https://www.cmake.org
[cpp17]: https://en.wikipedia.org/wiki/C%2B%2B17
[folder_documentation]: ./documentation/readme.md
[folder_playground]: ./playground/readme.md
[folder_smcli]: ./smcli/readme.md
[folder_smcore]: ./smcore/readme.md
[folder_smgui]: ./smgui/readme.md
[folder_smtest]: ./smtest/readme.md
[github]: https://www.github.com
[githubactions]: https://github.com/features/actions
[githubmarkdown]: https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax
[gitscm]: https://git-scm.com/
[licensemit]: https://opensource.org/licenses/MIT
[markdown]: https://daringfireball.net/projects/markdown/
[project_file]: ./CMakeLists.txt
[qt]: https://www.qt.io/
[tool_qt_creator]: https://www.qt.io/product/development-tools
[wannerjim]: https://campwoodsw.com/emcomp/about-us/
