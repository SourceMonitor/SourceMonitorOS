# The about dialog

The help menu offers an entry named "About SourceMonitorOS". This will fire up a dialog with rough information about the Software. In the original software the dialog looks like this:

![SourceMonitor About Dialog][smabout]

## Implementation

This is a functionality of `smcore` and located in `smcore/about.*`.

### Public API

```c++
namespace smos
{
    namespace smcore
    {
        class SMCORE_EXPORT About
        {
        public:
            /**
             * @brief Get the about text
             *
             * @return QString
             */
            static QString getAbout(void);
        };
    }
}

```

### Usage

```c++
#include "about.h"

QString about = smos::smcore::About::getAbout();
```

[smabout]: ./About%20SourceMonitor.png
