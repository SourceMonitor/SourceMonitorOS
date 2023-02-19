# smcore

In this directory the core functionality of SourceMonitorOS is located.

- Influence the software
  - Settings
  - Options
  - Language
  - Logging
- Project handling
  - Read project file
  - Write project file
  - Create checkpoints
- Plugin system
  - Each language should be a dynamic library. Just drop the file to the SourceMonitor directory and it should work.
  - Each dynamic library must satisfy an interface for data exchange.

See how this is used in [smgui][smgui] and [smcli][smcli]. The corresponding tests are located in [smtest][smtest].

## Technical information

- `smcore` is a designed as a library which is statically linked to [smgui][smgui], [smcli][smcli] and [smtest][smtest].
- Each class is named without any prefix.
- `Project` class will be serialized, see [here][serialization] for details

[smcli]: ./../smcli/readme.md
[smgui]: ./../smgui/readme.md
[smtest]: ./../smtest/readme.md
[serialization]: https://stackoverflow.com/questions/37038909/c-read-write-class-from-to-binary-file
