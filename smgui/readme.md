# smgui

In this directory the UI of SourceMonitorOS is located.

- User interaction for
  - Settings
  - Options
  - Language
  - Logging
- Project handling
  - Read project file
  - Write project file
  - Create checkpoints
  - Displaying the grids for
    - Checkpoints (all files)
    - Functions/methods (specific file)
  - Displaying the graphics
    - Checkpoints (all files)
    - Functions/methods (specific file)

The functionality called is located in [smcore][smcore].

## Technical information

- The classes of `smgui` are prefixed with `sg` to avoid complications with the classes of `smcore`

[smcore]: ./../smcore/readme.md
