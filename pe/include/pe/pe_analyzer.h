#pragma once

#include <string>

#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>

// Define a macro to specify export/import
#ifdef DLL_EXPORT
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport)
#endif

#else
#define LIBRARY_API
#endif


namespace pe {

// Define a struct to hold import information
struct ImportInfo
{
    // Name of DLL where you import from
    std::string dllName;

    // Use empty string if imported by ordinal
    std::string functionName;

    // Use 0 if imported by name
    uint16_t ordinal{};
};

class LIBRARY_API PEAnalyzer
{
public:

    //
    PEAnalyzer(const char* filePath);

    //
    ~PEAnalyzer();


private: 
    size_t peBufferSize {};
};

} // namespace pe

