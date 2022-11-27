# The settings object

There is a need to have persistent settings somewhere. For this is this object. Because of the plattform independency the settings are stored in an [INI file][wiki_ini_file]. This kind of format is supported by [Qts settings object][qt_qsettings].

## Implementation

This is a functionality of `smcore` and located in `smcore/settings.*`.

## Internals

- Section names will be always in uppercase letters.
- Key names will be always in lowercase letters.
- For both the class will take care about.

### Public API

```c++
namespace smos
{
    namespace smcore
    {
        class SMCORE_EXPORT SMSettings
        {
        public:
            /**
             * @brief Default constructor
             *
             * @param settingsfile Name of settings file
             */
            SMSettings(QString settingsfile);
            /**
             * @brief Default destructor
             *
             */
            ~SMSettings(void);
            /**
             * @brief Load settings from INI file
             */
            void settingsLoad(void);
            /**
             * @brief Save settings to INI file
             */
            void settingsSave(void);
            /**
             * @brief Get the absolute path to the logfile
             *
             * @return QString The absolute path to the logfile
             */
            QString logfileNameGet(void);
            /**
             * @brief Set the name (and path) of the logfile
             *
             * @param logfileName Name (and path) of the logfile to use
             */
            void logfileNameSet(QString logfileName);
        }
    }
}
```

### Usage

```c++
#include <settings.h>

smos::smcore::SMSettings settings = smos::smcore::SMSettings("smos_core.ini");

QString logfileOld = settings.logfileNameGet();
settings.logfileNameSet("logfilenew.log");
```

## Possible issues

This object could be a [singleton][wiki_singleton]. But the intention is to create an instance at the top most level and then [inject][wiki_dependency_injection] it into the core.

[qt_qsettings]: https://doc.qt.io/qt-6.2/qsettings.html
[wiki_dependency_injection]: https://en.wikipedia.org/wiki/Dependency_injection
[wiki_ini_file]: https://en.wikipedia.org/wiki/INI_file
[wiki_singleton]: https://en.wikipedia.org/wiki/Singleton_pattern
