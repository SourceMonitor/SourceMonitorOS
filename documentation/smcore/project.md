# The project object

This object contains the project data. This means the project name, the checkpoints, the metrics and much more.

## Implementation

This is a functionality of `smcore` and located in `smcore/project.*`.

## Internals

- The `loadProject` and `saveProject` methods are static.

### Public API

```c++
namespace smos
{
    namespace smcore
    {
        class Project
        {
        public:
            /**
             * @brief Construct a new Project object
             */
            Project(void);

            /**
             * @brief Destroy the Project object
             */
            ~Project(void);

            /**
             * @brief Load project data
             *
             * @param filename Name of project file
             * @param project Pointer to project object
             *
             * @return smos::smcore::Error::ErrorCode
             */
            static smos::smcore::Error::ErrorCode loadProject(const smos::smcore::SMString &filename, Project &project);

            /**
             * @brief Save project data
             *
             * @param filename Name of project file
             * @param project Pointer to project object
             * @param force Force saving in case project file already exist
             *
             * @return smos::smcore::Error::ErrorCode
             */
            static smos::smcore::Error::ErrorCode saveProject(const smos::smcore::SMString &filename, Project &project, bool force = false);

            /**
             * @brief Get the Project Name
             *
             * @return smos::smcore::SMString
             */
            smos::smcore::SMString getProjectName(void) const;

            /**
             * @brief Set the Project Name
             *
             * @param projectName
             */
            void setProjectName(smos::smcore::SMString projectName);

            /**
             * @brief Enable writing to stream
             *
             * @param os Outputstream to write to
             * @param obj Project object to write to stream
             *
             * @return std::ostream&
             */
            friend std::ostream &operator<<(std::ostream &os, const Project &obj);

            /**
             * @brief Enable reading from stream
             *
             * @param is Inputstream to read from
             * @param obj Project object to read from stream
             *
             * @return std::istream&
             */
            friend std::istream &operator>>(std::istream &is, Project &obj);
        };
    }
}
```

### Usage

```c++
#include "project.h"

// Creation of project
smos::smcore::SMString projectNameSet = smos::smcore::SMString("ProjectName");
smos::smcore::Project objProject;

// Change project name
objProject.setProjectName(projectNameSet);
smos::smcore::SMString projectNameGet = objProject.getProjectName();

// Save and load project
smos::smcore::SMString filename = smos::smcore::SMString("project.dat");
smos::smcore::Error::ErrorCode result = smos::smcore::Project::saveProject(filename, objProject);
result = smos::smcore::Project::loadProject(filename, objProject);
```

## Possible issues
