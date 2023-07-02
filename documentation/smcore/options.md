# The options object

There is a need to have persistent options somewhere. For this is this object. Because of the plattform independency the options are stored in an [INI file][wiki_ini_file]. This kind of format is supported by [Qts settings object][qt_qsettings].

## Implementation

This is a functionality of `smcore` and located in `smcore/options.*`.

## Internals

- Section names will be always in uppercase letters.
- Key names will be always in lowercase letters.
- For both the class will take care about.
- On creation of the object a load is performed to initialize the member variables.

### Public API

```c++
namespace smos
{
    namespace smcore
    {
        class Options
        {
        public:
            /**
             * @brief Default constructor
             *
             * @param optionsfile Name of options file
             */
            Options(smos::smcore::SMSring optionsfile);

            /**
             * @brief Default destructor
             *
             */
            ~Options(void);

            /**
             * @brief Get the editor call with filename templated
             *
             * @return smos::smcore::SMSring
             */
            smos::smcore::SMSring codeEditorGet(void);

            /**
             * @brief Get the editor call with filename templated
             *
             * @param codeeditor smos::smcore::SMSring
             */
            void codeEditorSet(smos::smcore::SMSring codeeditor);

            /**
             * @brief Get the absolute path to the logfile
             *
             * @return smos::smcore::SMSring The absolute path to the logfile
             */
            smos::smcore::SMSring logfileNameGet(void);

            /**
             * @brief Set the name (and path) of the logfile
             *
             * @param logfileName Name (and path) of the logfile to use
             */
            void logfileNameSet(smos::smcore::SMSring logfileName);
        };
    }
}
```

### Usage

```c++
#include "settings.h"

smos::smcore::SMSettings settings = smos::smcore::SMSettings("smos_core.ini");

smos::smcore::SMSring logfileOld = settings.logfileNameGet();
settings.logfileNameSet("logfilenew.log");
```

## Possible issues

This object could be a [singleton][wiki_singleton]. But the intention is to create an instance at the top most level and then [inject][wiki_dependency_injection] it into the core.

[qt_qsettings]: https://doc.qt.io/qt-6.2/qsettings.html
[wiki_dependency_injection]: https://en.wikipedia.org/wiki/Dependency_injection
[wiki_ini_file]: https://en.wikipedia.org/wiki/INI_file
[wiki_singleton]: https://en.wikipedia.org/wiki/Singleton_pattern
