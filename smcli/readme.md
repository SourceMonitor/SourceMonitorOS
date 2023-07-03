# smcli
In this directory the Command Line Client (CLI) of SourceMonitorOS is located.

- Influence the software via XML files
  - Settings
  - Options
  - Language
  - Logging
- Project handling
  - Read project file
  - Write project file
  - Create checkpoints

The functionality called is located in [smcore][smcore].

## Technical information
- The classes of `smcli` are prefixed with `sc` to avoid complications with the classes of `smcore`

[smcore]: ./../smcore/readme.md
