# The used license

This is a static function to get the license text to display. Actually this is a hardcoded MIT license. There was the idea about reading the text from a file. But what to display in case the file does not exist?

## Implementation

This is a functionality of `smcore` and located in `smcore/license.*`.

### Public API

```c++
namespace smos
{
    namespace smcore
    {
        class SMCORE_EXPORT SMLicense
        {
        public:
            /**
             * @brief Get the license text
             *
             * @return QString
             */
            static QString getLicense(void);
        }
    }
}
```

### Usage

```c++
#include <license.h>

QString license = smos::smcore::SMLicense::getLicense();
```

## Possible issues

At the moment the project uses the [MIT][license_mit]. Unfortunately QT proposes other [licenses][license_qt], e. g. the [LGPL][license_lgpl]. This needs further investigation.

[license_lgpl]: https://en.wikipedia.org/wiki/GNU_Lesser_General_Public_License
[license_mit]: https://en.wikipedia.org/wiki/MIT_License
[license_qt]: https://www.qt.io/download-open-source#consider
