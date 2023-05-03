#include "smpreader.h"
#include <iostream>
#include <map>
#include <assert.h>
#include "version.h"

using namespace smos::smcore;

SMPReader::~SMPReader()
{
    if (m_stream.is_open())
        m_stream.close();
}

bool SMPReader::Open(std::filesystem::path path)
{
    m_stream.exceptions(std::ifstream::failbit);
    m_stream.open(path, std::ios_base::in | std::ios_base::binary);
    return m_stream.is_open();
}

template<typename T> T ArchiveReader::Read()
{
    T t;
    m_stream.read(reinterpret_cast<char*>(&t), sizeof(T));
    return t;
}

template<> std::vector<std::uint32_t> ArchiveReader::Read()
{
    unsigned int size = ReadCount();
    std::vector<std::uint32_t> vec(size, 0);
    m_stream.read(reinterpret_cast<char*>(vec.data()), size * sizeof(std::uint32_t));
    return vec;
}

template<> std::time_t ArchiveReader::Read()
{
    __time32_t time_32;
    m_stream.read(reinterpret_cast<char*>(&time_32), sizeof(__time32_t));
    const std::int32_t cTime64Mark = INT_MIN + 10;
    if (static_cast<std::int32_t>(time_32) == cTime64Mark)
    {
        __time64_t time_64;
        m_stream.read(reinterpret_cast<char*>(&time_64), sizeof(__time64_t));
        return std::time_t(time_64);
    }
    else
        return std::time_t(time_32);
}

template<> Version ArchiveReader::Read()
{

    std::int16_t major = Read<std::int16_t>();
    short minor = Read<short>();
    std::time_t time = Read<std::time_t>();
    Version version = {major, minor, 0, time};
    return version;
}

template<> std::string ArchiveReader::Read()
{
    unsigned int length = ReadStringLength();
    std::string t(length, '\0');
    m_stream.read(t.data(), length);
    return t;
}

template<> std::vector<std::string> ArchiveReader::Read()
{
    unsigned int size = ReadCount();
    std::vector<std::string> vec(size);
    for (unsigned int i = 0; i < size; ++i)
    {
        std::string sValue = Read<std::string>();
        vec[i] = sValue;
    }
    return vec;
}

template<> std::map<std::string, std::string> ArchiveReader::Read()
{
    unsigned int size = ReadCount();
    std::map<std::string, std::string> t;
    while (size--)
    {
        std::string sKey = Read<std::string>();
        std::string sValue = Read<std::string>();
        t[sKey] = sValue;
    }
    return t;
}

template<> ClassInfo ArchiveReader::Read()
{
    std::uint16_t wTag = Read<std::uint16_t>();
    const std::uint16_t wNewClassTag = (std::uint16_t)0xFFFF;
    if (wTag == wNewClassTag)
    {
        std::uint16_t wTemp = Read<std::uint16_t>();
        (void)wTemp;

        std::uint16_t nLen = Read<std::uint16_t>();
        (void)nLen;

        std::string name(nLen, '\0');
        m_stream.read(name.data(), nLen);

        m_classes[m_classesIndex] = name;
        m_classesIndex++;
        ClassInfo classInfo = {name};
        return classInfo;
    }
    else
    {
        const std::uint16_t wClassTag = (std::uint16_t)0x8000;
        std::uint32_t obTag = ((wTag & wClassTag) << 16) | (wTag & ~wClassTag);
        const std::uint32_t dwBigClassTag = (std::uint32_t)0x80000000;
        std::uint32_t nClassIndex = (obTag & ~dwBigClassTag);
        ClassInfo classInfo = {m_classes[nClassIndex]};
        return classInfo;
    }
}

template<typename T> void printVector(const std::vector<T>& vec, std::string sep = " ")
{
    for (auto elem : vec)
    {
        std::cout << elem << sep;
    }
    std::cout << std::endl;
}

void SMLanguageReader::Read()
{
    ClassInfo classInfo = m_archiveReader.Read<ClassInfo>();
    std::cout << "class name: " << classInfo.m_name << std::endl;
    if (classInfo.m_name.empty())
        return;

    if (classInfo.m_name == "SMCpp" || classInfo.m_name == "SMCs" || classInfo.m_name == "SMJava" || classInfo.m_name == "SMVBNET")
    {
        std::vector<std::string> m_saComplexMetrics = m_archiveReader.Read<std::vector<std::string>>();
        std::cout << "m_saComplexMetrics: size = " << m_saComplexMetrics.size() << " skip" << std::endl;

        std::vector<std::uint32_t> m_iCounts = m_archiveReader.Read<std::vector<std::uint32_t>>();
        std::cout << "m_iCounts: size = " << m_iCounts.size() << " elements: " << std::endl;
        printVector(m_iCounts);

        std::map<std::string, std::string> m_oClassList = m_archiveReader.Read<std::map<std::string, std::string>>();
        std::cout << "m_oClassList: size = " << m_oClassList.size() << " elements: " << std::endl;
    }
    else if (classInfo.m_name == "SMC")
    {
        std::vector<std::string> m_saComplexMetrics = m_archiveReader.Read<std::vector<std::string>>();
        std::cout << "m_saComplexMetrics: size = " << m_saComplexMetrics.size() << " skip" << std::endl;

        std::vector<std::uint32_t> m_iCounts = m_archiveReader.Read<std::vector<std::uint32_t>>();
        std::cout << "m_iCounts: size = " << m_iCounts.size() << " elements: " << std::endl;
        printVector(m_iCounts);

        //m_oFunctionList.Serialize(ar);
        std::map<std::string, std::string> m_oFunctionList = m_archiveReader.Read<std::map<std::string, std::string>>();
        std::cout << "m_oFunctionList: size = " << m_oFunctionList.size() << " elements: " << std::endl;
    }
    else if (classInfo.m_name == "SMDelphi")
    {
        std::string m_sSubroutineName = m_archiveReader.Read<std::string>();
        std::cout << "m_sSubroutineName: " << m_sSubroutineName << std::endl;

        std::vector<std::string> m_saComplexMetrics = m_archiveReader.Read<std::vector<std::string>>();
        std::cout << "m_saComplexMetrics: size = " << m_saComplexMetrics.size() << " skip" << std::endl;

        std::vector<std::uint32_t> m_iCounts = m_archiveReader.Read<std::vector<std::uint32_t>>();
        std::cout << "m_iCounts: size = " << m_iCounts.size() << " elements: " << std::endl;
        printVector(m_iCounts);

        std::map<std::string, std::string> m_oClassList = m_archiveReader.Read<std::map<std::string, std::string>>();
        std::cout << "m_oClassList: size = " << m_oClassList.size() << " elements: " << std::endl;
    }
    else if (classInfo.m_name == "SMHTML")
    {
        std::vector<std::string> m_saComplexMetrics = m_archiveReader.Read<std::vector<std::string>>();
        std::cout << "m_saComplexMetrics: size = " << m_saComplexMetrics.size() << " skip" << std::endl;

        std::vector<std::uint32_t> m_iCounts = m_archiveReader.Read<std::vector<std::uint32_t>>();
        std::cout << "m_iCounts: size = " << m_iCounts.size() << " elements: " << std::endl;
        printVector(m_iCounts);
    }
    else if (classInfo.m_name == "SMVisualBasic")
    {
        std::string m_sSubroutineName = m_archiveReader.Read<std::string>();
        std::cout << "m_sSubroutineName: " << m_sSubroutineName << std::endl;

        std::int32_t m_iSubroutineStatements = m_archiveReader.Read<std::int32_t>();
        std::cout << "m_iSubroutineStatements: " << m_iSubroutineStatements << std::endl;

        std::vector<std::string> m_saComplexMetrics = m_archiveReader.Read<std::vector<std::string>>();
        std::cout << "m_saComplexMetrics: size = " << m_saComplexMetrics.size() << " skip" << std::endl;

        std::vector<std::uint32_t> m_iCounts = m_archiveReader.Read<std::vector<std::uint32_t>>();
        std::cout << "m_iCounts: size = " << m_iCounts.size() << " elements: " << std::endl;
        printVector(m_iCounts);
    }
}

bool SMPReader::Read(Project& project)
{
    try
    {
        ArchiveReader archiveReader(m_stream);

        Version versionProject = archiveReader.Read<Version>();
        std::cout << "Version: " << versionProject.AsString() << std::endl;

        std::string name = archiveReader.Read<std::string>();
        std::cout << "m_sName: " << name << std::endl;
        project.setProjectName(name);

        std::int32_t includeSubdirectories = archiveReader.Read<std::int32_t>();
        std::cout << "m_fIncludeSubdirectories: " << includeSubdirectories << std::endl;

        std::cout << "read SMLanguage" << std::endl;
        SMLanguageReader languageReader(archiveReader);
        languageReader.Read();

        if (versionProject >= Version(1, 2))
        {
            std::string m_sDirectory = archiveReader.Read<std::string>();
            std::cout << "m_sDirectory: " << m_sDirectory << std::endl;
        }

        if (versionProject >= Version(2, 0))
        {
            std::int32_t m_eOptionFlags = archiveReader.Read<std::int32_t>();
            std::cout << "m_eOptionFlags: " << m_eOptionFlags << std::endl;
        }

        if (!(versionProject >= Version(2, 0)))
        {
            languageReader.Read();
        }

        SMCheckpointsReader checkpointsReader(archiveReader);
        checkpointsReader.Read();

        m_stream.exceptions(std::ifstream::goodbit);
        char c;
        while (m_stream.get(c)) //checking if we missed any data, only for debug
        {
            //assert(0);
            std::cout << c;
        }
    }
    catch (const std::ios_base::failure& fail)
    {
        std::cout << fail.what() << std::endl;
        return false;
    }
    catch (...)
    {
        return false;
    }
    return true;
}

unsigned int ArchiveReader::ReadStringLength()
{
    unsigned char byteLength = Read<unsigned char>();
    if (byteLength < 0xff)
        return byteLength;

    unsigned short shortLength = Read<unsigned short>();
    if (shortLength == 0xfffe)
    {
        // UNICODE string prefix (length will follow)
        return (unsigned int)-1;
    }
    else if (shortLength == 0xffff)
    {
        // read DWORD of length
        unsigned long longLength = Read<unsigned long>();
        return (unsigned int)longLength;
    }
    else
        return shortLength;
}

unsigned int ArchiveReader::ReadCount()
{
    std::uint16_t nCount = Read<std::uint16_t>();
    if (nCount != 0xFFFF)
        return nCount;

    std::uint32_t dwCount = Read<std::uint32_t>();
    return dwCount;
}

void SMCheckpointsReader::Read()
{
    unsigned int sizeCheckpoints = m_archiveReader.ReadCount();
    std::cout << "sizeCheckpoints: " << sizeCheckpoints << std::endl;
    for (unsigned int i = 0; i < sizeCheckpoints; i++)
    {
        Version versionCheckpoint = m_archiveReader.Read<Version>();
        std::cout << "Checkpoint version: " << versionCheckpoint.AsString() << std::endl;

        //ar >> m_sName >> m_oDate >> m_fUseModifiedComplexity >> m_poLanguage;
        std::string nameSMCheckpoint = m_archiveReader.Read<std::string>();
        std::cout << "nameSMCheckpoint: " << nameSMCheckpoint << std::endl;
        std::time_t t64_checkpointSMCheckpoint = m_archiveReader.Read<std::time_t>();
        std::cout << "Checkpoint time: " << t64_checkpointSMCheckpoint << std::endl;

        std::int32_t m_fUseModifiedComplexity = m_archiveReader.Read<std::int32_t>();
        std::cout << "m_fUseModifiedComplexity: " << m_fUseModifiedComplexity << std::endl;

        std::cout << "read SMLanguage" << std::endl;
        SMLanguageReader languageReader(m_archiveReader);
        languageReader.Read();

        if (versionCheckpoint >= Version(3, 1))
        {
            std::string m_sBaseDirectory = m_archiveReader.Read<std::string>();
            std::cout << "m_sBaseDirectory: " << m_sBaseDirectory << std::endl;
        }

        //if (!m_oVersion.IsOKVersion(2, 0))
        if (!(versionCheckpoint >= Version(2, 0)))
        {
            //m_poLanguage->Serialize(ar); // include redundant copy for older versions only
            languageReader.Read();
        }

        unsigned int m_iFileCount = m_archiveReader.ReadCount();
        std::cout << "m_iFileCount: " << m_iFileCount << std::endl;
        //m_oFiles.Serialize(ar);

        for (unsigned int f = 0; f < m_iFileCount; f++)
        {
            //void SMFile::Serialize(CArchive &ar)
            std::string m_sPathname = m_archiveReader.Read<std::string>();
            std::cout << "m_sPathname: " << m_sPathname << std::endl;
            std::cout << "read SMLanguage" << std::endl;
            SMLanguageReader languageReaderFile(m_archiveReader);
            languageReaderFile.Read();
        }
    }
}
