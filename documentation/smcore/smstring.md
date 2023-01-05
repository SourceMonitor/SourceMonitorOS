# The smstring object

WTF?! There are so much possibilities for using strings in C++ - don't know how to do a wise decision for stalbe use. There are a few possibilities

- std::string
- std::wstring
- [ICU][lib_icu]

We have to keep always in mind that the source code could contain comments or variables in local languages. Imagine source code in Arabic (from right to left, from top to bottom), Chinese (from left to right, from top to bottom), Hebrew (from right to left, from top to bottom), Japanese (from right to left, from top to bottom) or Thai (from left to right, from top to bottom) - it will not be easy to deal with such source code.

## Implementation

This is a functionality of `smcore` and located in `smcore/smstring.*`.

The decision of which kind of string handling is moved to the future. To enable the project for working a simple `typedef` on `std::string` is used as placeholder for the future implementation. Of course this is not safe for the future but better than nothing.

### Public API

```c++
namespace smos
{
    namespace smcore
    {
        typedef std::string SMSring;
    }
}
```

### Usage

```c++
#include "smstring.h"

smos::smcore::SMString message = "Hello world";
```

[lib_icu]: https://icu.unicode.org/design/cpp
