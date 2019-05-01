/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   documentnew_svg;
    const int            documentnew_svgSize = 15964;

    extern const char*   documentsave_svg;
    const int            documentsave_svgSize = 47666;

    extern const char*   runverify_svg;
    const int            runverify_svgSize = 4477;

    extern const char*   documentsaveas_svg;
    const int            documentsaveas_svgSize = 50117;

    extern const char*   runstop_svg;
    const int            runstop_svgSize = 10198;

    extern const char*   runinitialize_svg;
    const int            runinitialize_svgSize = 9105;

    extern const char*   runstart_svg;
    const int            runstart_svgSize = 10258;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 7;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
