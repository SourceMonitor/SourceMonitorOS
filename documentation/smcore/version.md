# The project object

This object contains the program version information.

## Implementation

This is a functionality of `smcore` and located in `smcore/version.*`.

## Internals

### Public API

```c++
namespace smos
{
    namespace smcore
    {
        class Version
        {
        public:
            /**
             * @brief Default constructor
             */
            Version(void);

            /**
             * @brief Default destructor
             */
            ~Version(void);

            /**
             * @brief Copy constructor
             *
             * @param versionObject Version to copy data from
             */
            Version(const Version &versionObject);

            /**
             * @brief Assignment operator
             *
             * @param versionObject
             * @return Version& reference to current object
             */
            Version &operator=(const Version &versionObject);

            /**
             * @brief Equal operator
             *
             * @param versionObject Version to compare with
             * @return bool True on equal, otherwise false
             */
            bool operator==(const Version &versionObject) const;

            /**
             * @brief Non equal operator
             *
             * @param versionObject Version to compare with
             * @return bool True on non equal, otherwise false
             */
            bool operator!=(const Version &versionObject) const;

            /**
             * @brief Get version information as string
             *
             * @return smos::smcore::SMString
             */
            smos::smcore::SMString AsString(void) const;

            /**
             * @brief Set the Version object
             *
             * @param major Major version information
             * @param minor Minor version information
             * @param revision Revision version informationi
             */
            void SetVersion(const short &major, const short &minor, const short &revision);
        };
    }
}

```

### Usage

```c++
smos::smcore::Version verObjectSrc;
smos::smcore::Version verObjectDst(verObjectSrc);
smos::smcore::SMString versionSrc = verObjectSrc.AsString();

verObjectSrc.SetVersion(1, 2, 3);
verObjectDst = verObjectSrc;
```

## Possible issues
