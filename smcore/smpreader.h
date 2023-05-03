#ifndef SMPREADER_H
#define SMPREADER_H

#include <filesystem>
#include <fstream>
#include <unordered_map>
#include "project.h"

namespace smos
{
    namespace smcore
    {
        class ArchiveReader
        {
        public:
            ArchiveReader(std::ifstream& p_stream) : m_stream(p_stream) { }
            template<typename T> T Read();
            unsigned int ReadCount();

        private:
            unsigned int ReadStringLength();

            std::ifstream& m_stream;
            unsigned int m_classesIndex = 1;
            std::unordered_map<unsigned int, std::string> m_classes;

        protected:
        };

        class SMLanguageReader
        {
        public:
            SMLanguageReader(ArchiveReader& archiveReader) : m_archiveReader(archiveReader) { }
            void Read();

        private:
            ArchiveReader& m_archiveReader;
        };

        class SMCheckpointsReader
        {
        public:
            SMCheckpointsReader(ArchiveReader& archiveReader) : m_archiveReader(archiveReader) { }
            void Read();

        private:
            ArchiveReader& m_archiveReader;
        };

        class SMPReader
        {
        public:
            SMPReader() = default;
            ~SMPReader();
            bool Open(std::filesystem::path path);
            bool Read(Project& project);

        protected:
            std::ifstream m_stream;
        };

        struct ClassInfo
        {
            std::string m_name;
        };
    }
}

#endif // SMPREADER_H
