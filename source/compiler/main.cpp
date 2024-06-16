#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>


#ifdef WINDOWS

#include <windows.h>

std::vector<uint8_t> GetDosHeader()
{
    // DOS .EXE header
    IMAGE_DOS_HEADER dosHeader{};
    std::memset(dosHeader.e_res, 0, sizeof(dosHeader.e_res));   // Reserved words
    std::memset(dosHeader.e_res2, 0, sizeof(dosHeader.e_res2)); // Reserved words

    dosHeader.e_magic       = IMAGE_DOS_SIGNATURE;  // Magic number
    dosHeader.e_cblp        = 144;                  // Bytes on last page of file
    dosHeader.e_cp          = 3;                    // Pages in file
    dosHeader.e_crlc        = 0;                    // Relocations
    dosHeader.e_cparhdr     = 4;                    // Size of header in paragraphs
    dosHeader.e_minalloc    = 0;                    // Minimum extra paragraphs needed
    dosHeader.e_maxalloc    = 65535;                // Maximum extra paragraphs needed
    dosHeader.e_ss          = 0;                    // Initial (relative) SS value
    dosHeader.e_sp          = 184;                  // Initial SP value
    dosHeader.e_csum        = 0;                    // Checksum
    dosHeader.e_ip          = 0;                    // Initial IP value
    dosHeader.e_cs          = 0;                    // Initial (relative) CS value
    dosHeader.e_lfarlc      = 64;                   // File address of relocation table
    dosHeader.e_ovno        = 0;                    // Overlay number
    dosHeader.e_oemid       = 0;                    // OEM identifier (for e_oeminfo)
    dosHeader.e_oeminfo     = 0;                    // OEM information; e_oemid specific
    dosHeader.e_lfanew      = 208;                  // File address of new exe header

    return std::vector<uint8_t>(
        reinterpret_cast<uint8_t*>(&dosHeader),
        reinterpret_cast<uint8_t*>(&dosHeader) + sizeof(IMAGE_DOS_HEADER)
    );
}

std::vector<uint8_t> GetNtHeaders()
{
    IMAGE_NT_HEADERS ntHeaders{};
    ntHeaders.Signature                                     = IMAGE_NT_SIGNATURE;

    // File Header
    ntHeaders.FileHeader.Machine                            = IMAGE_FILE_MACHINE_AMD64;
    ntHeaders.FileHeader.NumberOfSections                   = 5;
    ntHeaders.FileHeader.TimeDateStamp                      = 1716567490;
    ntHeaders.FileHeader.PointerToSymbolTable               = 0;
    ntHeaders.FileHeader.NumberOfSymbols                    = 0;
    ntHeaders.FileHeader.SizeOfOptionalHeader               = sizeof(IMAGE_OPTIONAL_HEADER64);
    ntHeaders.FileHeader.Characteristics                    = 0x22;

    // Optional Header
    ntHeaders.OptionalHeader.Magic                          = IMAGE_NT_OPTIONAL_HDR64_MAGIC;
    ntHeaders.OptionalHeader.MajorLinkerVersion             = 1;
    ntHeaders.OptionalHeader.MinorLinkerVersion             = 0;
    ntHeaders.OptionalHeader.SizeOfCode                     = 1024;         // Taille du code
    ntHeaders.OptionalHeader.SizeOfInitializedData          = 1536;         // Taille des données initialisées
    ntHeaders.OptionalHeader.SizeOfUninitializedData        = 0;
    ntHeaders.OptionalHeader.AddressOfEntryPoint            = 8192;         // Point d'entrée du programme
    ntHeaders.OptionalHeader.ImageBase                      = 0x140000000;  // Adresse de base de l'image
    ntHeaders.OptionalHeader.SectionAlignment               = 4096;         // Alignement de la section
    ntHeaders.OptionalHeader.FileAlignment                  = 512;          // Alignement du fichier
    ntHeaders.OptionalHeader.MajorOperatingSystemVersion    = 6;
    ntHeaders.OptionalHeader.MinorOperatingSystemVersion    = 0;
    ntHeaders.OptionalHeader.MajorImageVersion              = 0;
    ntHeaders.OptionalHeader.MinorImageVersion              = 0;
    ntHeaders.OptionalHeader.MajorSubsystemVersion          = 6;
    ntHeaders.OptionalHeader.MinorSubsystemVersion          = 0;
    ntHeaders.OptionalHeader.Win32VersionValue              = 0;
    ntHeaders.OptionalHeader.SizeOfImage                    = 24576;        // Taille de l'image (3 pages de 4K)
    ntHeaders.OptionalHeader.SizeOfHeaders                  = 1024;         // Taille des en-têtes
    ntHeaders.OptionalHeader.CheckSum                       = 0;
    ntHeaders.OptionalHeader.Subsystem                      = IMAGE_SUBSYSTEM_WINDOWS_CUI;
    ntHeaders.OptionalHeader.DllCharacteristics             = 33120;
    ntHeaders.OptionalHeader.SizeOfStackReserve             = 1048576;
    ntHeaders.OptionalHeader.SizeOfStackCommit              = 4096;
    ntHeaders.OptionalHeader.SizeOfHeapReserve              = 1048576;
    ntHeaders.OptionalHeader.SizeOfHeapCommit               = 4096;
    ntHeaders.OptionalHeader.LoaderFlags                    = 0;
    ntHeaders.OptionalHeader.NumberOfRvaAndSizes            = IMAGE_NUMBEROF_DIRECTORY_ENTRIES;

    ntHeaders.OptionalHeader.DataDirectory[1].VirtualAddress = 3140;
    ntHeaders.OptionalHeader.DataDirectory[1].Size           = 40;

    ntHeaders.OptionalHeader.DataDirectory[5].VirtualAddress = 5000;
    ntHeaders.OptionalHeader.DataDirectory[5].Size           = 12;

    ntHeaders.OptionalHeader.DataDirectory[6].VirtualAddress = 3020;
    ntHeaders.OptionalHeader.DataDirectory[6].Size           = 28;

    ntHeaders.OptionalHeader.DataDirectory[12].VirtualAddress = 3000;
    ntHeaders.OptionalHeader.DataDirectory[12].Size           = 32;

    for (int i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; ++i)
    {
        // ntHeaders.OptionalHeader.DataDirectory[i].VirtualAddress = 0;
        // ntHeaders.OptionalHeader.DataDirectory[i].Size           = 0;
    }

    return std::vector<uint8_t>(
        reinterpret_cast<uint8_t*>(&ntHeaders),
        reinterpret_cast<uint8_t*>(&ntHeaders) + sizeof(IMAGE_NT_HEADERS64)
    );
}

std::vector<uint8_t> GetSectionHeader(const char* name, uint32_t virtualSize, uint32_t virtualAddress, uint32_t sizeOfRawData, uint32_t pointerToRawData, uint32_t characteristics)
{
    IMAGE_SECTION_HEADER sectionHeader{};
    std::memcpy(sectionHeader.Name, name, IMAGE_SIZEOF_SHORT_NAME);

    sectionHeader.Misc.VirtualSize      = virtualSize;
    sectionHeader.VirtualAddress        = virtualAddress;
    sectionHeader.SizeOfRawData         = sizeOfRawData;
    sectionHeader.PointerToRawData      = pointerToRawData;
    sectionHeader.PointerToRelocations  = 0;
    sectionHeader.PointerToLinenumbers  = 0;
    sectionHeader.NumberOfRelocations   = 0;
    sectionHeader.NumberOfLinenumbers   = 0;
    sectionHeader.Characteristics       = characteristics;

    return std::vector<uint8_t>(
        reinterpret_cast<uint8_t*>(&sectionHeader),
        reinterpret_cast<uint8_t*>(&sectionHeader) + sizeof(IMAGE_SECTION_HEADER)
    );
}

std::vector<uint8_t> GetTextSection()
{
    // Code machine pour écrire "7\r\n" sur la sortie standard et quitter.
    // Code assembleur équivalent:
    // mov rcx, -11
    // call GetStdHandle
    // mov [rel stdout_handle], rax
    // mov rcx, [rel stdout_handle]
    // mov rdx, message
    // mov r8, message_length
    // xor r9, r9
    // call WriteFile
    // xor rcx, rcx
    // call ExitProcess

    uint8_t code[] = {
        0x48, 0xC7, 0xC1, 0xF5, 0xFF, 0xFF, 0xFF,                   // mov rcx, -11 (STD_OUTPUT_HANDLE)
        0xFF, 0x15, 0xEA, 0xFF, 0xFF, 0xFF,                         // call GetStdHandle (relative)
        0x48, 0xA3, 0x00, 0x10, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, // mov [0x00400000], rax (stdout_handle)
        0x48, 0x8B, 0x0D, 0xDF, 0xFF, 0xFF, 0xFF,                   // mov rcx, [rel stdout_handle]
        0x48, 0x8D, 0x15, 0xDE, 0xFF, 0xFF, 0xFF,                   // lea rdx, [rel message]
        0x4C, 0x8D, 0x05, 0xDD, 0xFF, 0xFF, 0xFF,                   // lea r8, [rel message_length]
        0x4D, 0x31, 0xC9,                                           // xor r9, r9
        0xFF, 0x15, 0xC1, 0xFF, 0xFF, 0xFF,                         // call WriteFile (relative)
        0x48, 0x31, 0xC9,                                           // xor rcx, rcx
        0xFF, 0x15, 0xC0, 0xFF, 0xFF, 0xFF,                         // call ExitProcess (relative)
    };

    std::vector<uint8_t> textSection(0x200, 0x90); // Remplissage de 0x200 bytes avec NOP
    std::copy(std::begin(code), std::end(code), textSection.begin());

    return textSection;
}

std::vector<uint8_t> GetDataSection()
{
    // Message "7\r\n" avec longueur
    uint8_t message[] = "7\r\n";

    std::vector<uint8_t> dataSection(0x200, 0x00); // Remplissage de 0x200 bytes avec 0
    std::copy(std::begin(message), std::end(message), dataSection.begin());

    return dataSection;
}

void GenerateExecutable(const std::string& filename, const std::vector<uint8_t>& code)
{
    std::ofstream outputFile(filename, std::ios::binary);
    if (outputFile.is_open())
    {
        outputFile.write(reinterpret_cast<const char*>(code.data()), code.size());
        std::cout << "Fichier executable " << filename << " généré avec succès!" << std::endl;
    }
    else
    {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier " << filename << " pour écriture." << std::endl;
    }
}

void Compile(const std::string& filename)
{
    std::vector<uint8_t> dosHeader = GetDosHeader();
    std::vector<uint8_t> ntHeaders = GetNtHeaders();

    std::vector<uint8_t> textSectionHeader = GetSectionHeader(".text", 0x1000, 0x1000, 0x200, 0x200, IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ);
    std::vector<uint8_t> dataSectionHeader = GetSectionHeader(".data", 0x200, 0x2000, 0x200, 0x400, IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE);

    std::vector<uint8_t> textSection = GetTextSection();
    std::vector<uint8_t> dataSection = GetDataSection();

    std::vector<uint8_t> executable;
    executable.insert(executable.end(), dosHeader.begin(), dosHeader.end());
    executable.insert(executable.end(), ntHeaders.begin(), ntHeaders.end());

    executable.insert(executable.end(), textSectionHeader.begin(), textSectionHeader.end());
    executable.insert(executable.end(), dataSectionHeader.begin(), dataSectionHeader.end());

    executable.insert(executable.end(), textSection.begin(), textSection.end());
    executable.insert(executable.end(), dataSection.begin(), dataSection.end());

    GenerateExecutable(filename, executable);
}

void PrintDosHeader(PIMAGE_DOS_HEADER pDosHeader)
{
    std::cout << "IMAGE_DOS_HEADER:" << std::endl;
    std::cout << "  e_magic:                 0x" << std::hex << pDosHeader->e_magic << std::endl;
    std::cout << "  e_cblp:                  " << std::dec << pDosHeader->e_cblp << std::endl;
    std::cout << "  e_cp:                    " << pDosHeader->e_cp << std::endl;
    std::cout << "  e_crlc:                  " << pDosHeader->e_crlc << std::endl;
    std::cout << "  e_cparhdr:               " << pDosHeader->e_cparhdr << std::endl;
    std::cout << "  e_minalloc:              " << pDosHeader->e_minalloc << std::endl;
    std::cout << "  e_maxalloc:              " << pDosHeader->e_maxalloc << std::endl;
    std::cout << "  e_ss:                    " << pDosHeader->e_ss << std::endl;
    std::cout << "  e_sp:                    " << pDosHeader->e_sp << std::endl;
    std::cout << "  e_csum:                  " << pDosHeader->e_csum << std::endl;
    std::cout << "  e_ip:                    " << pDosHeader->e_ip << std::endl;
    std::cout << "  e_cs:                    " << pDosHeader->e_cs << std::endl;
    std::cout << "  e_lfarlc:                " << pDosHeader->e_lfarlc << std::endl;
    std::cout << "  e_ovno:                  " << pDosHeader->e_ovno << std::endl;
    std::cout << "  e_res[0]:                " << pDosHeader->e_res[0] << std::endl;
    std::cout << "  e_res[1]:                " << pDosHeader->e_res[1] << std::endl;
    std::cout << "  e_res[2]:                " << pDosHeader->e_res[2] << std::endl;
    std::cout << "  e_res[3]:                " << pDosHeader->e_res[3] << std::endl;
    std::cout << "  e_oemid:                 " << pDosHeader->e_oemid << std::endl;
    std::cout << "  e_oeminfo:               " << pDosHeader->e_oeminfo << std::endl;
    std::cout << "  e_res2[0]:               " << pDosHeader->e_res2[0] << std::endl;
    std::cout << "  e_res2[1]:               " << pDosHeader->e_res2[1] << std::endl;
    std::cout << "  e_res2[2]:               " << pDosHeader->e_res2[2] << std::endl;
    std::cout << "  e_res2[3]:               " << pDosHeader->e_res2[3] << std::endl;
    std::cout << "  e_res2[4]:               " << pDosHeader->e_res2[4] << std::endl;
    std::cout << "  e_res2[5]:               " << pDosHeader->e_res2[5] << std::endl;
    std::cout << "  e_res2[6]:               " << pDosHeader->e_res2[6] << std::endl;
    std::cout << "  e_res2[7]:               " << pDosHeader->e_res2[7] << std::endl;
    std::cout << "  e_res2[8]:               " << pDosHeader->e_res2[8] << std::endl;
    std::cout << "  e_res2[9]:               " << pDosHeader->e_res2[9] << std::endl;
    std::cout << "  e_lfanew:                " << pDosHeader->e_lfanew << std::endl;
    std::cout << std::endl;
}
void PrintNtHeaders(PIMAGE_NT_HEADERS pNtHeaders)
{
    std::cout << "IMAGE_NT_HEADERS:" << std::endl;
    std::cout << "    Signature:                 0x" << std::hex << pNtHeaders->Signature << std::endl;

    // File header format.
    std::cout << "    FileHeader:              " << std::endl;
    std::cout << "        Machine:               0x" << std::hex << pNtHeaders->FileHeader.Machine << std::endl;
    std::cout << "        NumberOfSections:      " << std::dec << pNtHeaders->FileHeader.NumberOfSections << std::endl;
    std::cout << "        TimeDateStamp:         " << std::dec << pNtHeaders->FileHeader.TimeDateStamp << std::endl;
    std::cout << "        PointerToSymbolTable:  " << std::dec << pNtHeaders->FileHeader.PointerToSymbolTable << std::endl;
    std::cout << "        NumberOfSymbols:       " << std::dec << pNtHeaders->FileHeader.NumberOfSymbols << std::endl;
    std::cout << "        SizeOfOptionalHeader:  " << std::dec << pNtHeaders->FileHeader.SizeOfOptionalHeader << std::endl;
    std::cout << "        Characteristics:       0x" << std::hex << pNtHeaders->FileHeader.Characteristics << std::endl;

    std::cout << "    OptionalHeader:          " << std::endl;
    std::cout << "        Magic:                 0x" << std::hex << pNtHeaders->OptionalHeader.Magic << std::endl;
    std::cout << "        MajorLinkerVersion:    " << std::dec << pNtHeaders->OptionalHeader.MajorLinkerVersion << std::endl;
    std::cout << "        MinorLinkerVersion:    " << std::dec << pNtHeaders->OptionalHeader.MinorLinkerVersion << std::endl;
    std::cout << "        SizeOfCode:            " << std::dec << pNtHeaders->OptionalHeader.SizeOfCode << std::endl;
    std::cout << "        SizeOfInitializedData: " << std::dec << pNtHeaders->OptionalHeader.SizeOfInitializedData << std::endl;
    std::cout << "        SizeOfUninitializedData: " << std::dec << pNtHeaders->OptionalHeader.SizeOfUninitializedData << std::endl;
    std::cout << "        AddressOfEntryPoint:   " << std::dec << pNtHeaders->OptionalHeader.AddressOfEntryPoint << std::endl;
    std::cout << "        BaseOfCode:            " << std::dec << pNtHeaders->OptionalHeader.BaseOfCode << std::endl;
    std::cout << "        ImageBase:             0x" << std::hex << pNtHeaders->OptionalHeader.ImageBase << std::endl;
    std::cout << "        SectionAlignment:      " << std::dec << pNtHeaders->OptionalHeader.SectionAlignment << std::endl;
    std::cout << "        FileAlignment:         " << std::dec << pNtHeaders->OptionalHeader.FileAlignment << std::endl;
    std::cout << "        MajorOperatingSystemVersion: " << std::dec << pNtHeaders->OptionalHeader.MajorOperatingSystemVersion << std::endl;
    std::cout << "        MinorOperatingSystemVersion: " << std::dec << pNtHeaders->OptionalHeader.MinorOperatingSystemVersion << std::endl;
    std::cout << "        MajorImageVersion:     " << std::dec << pNtHeaders->OptionalHeader.MajorImageVersion << std::endl;
    std::cout << "        MinorImageVersion:     " << std::dec << pNtHeaders->OptionalHeader.MinorImageVersion << std::endl;
    std::cout << "        MajorSubsystemVersion: " << std::dec << pNtHeaders->OptionalHeader.MajorSubsystemVersion << std::endl;
    std::cout << "        MinorSubsystemVersion: " << std::dec << pNtHeaders->OptionalHeader.MinorSubsystemVersion << std::endl;
    std::cout << "        Win32VersionValue:     " << std::dec << pNtHeaders->OptionalHeader.Win32VersionValue << std::endl;
    std::cout << "        SizeOfImage:           " << std::dec << pNtHeaders->OptionalHeader.SizeOfImage << std::endl;
    std::cout << "        SizeOfHeaders:         " << std::dec << pNtHeaders->OptionalHeader.SizeOfHeaders << std::endl;
    std::cout << "        CheckSum:              " << std::dec << pNtHeaders->OptionalHeader.CheckSum << std::endl;
    std::cout << "        Subsystem:             " << std::dec << pNtHeaders->OptionalHeader.Subsystem << std::endl;
    std::cout << "        DllCharacteristics:    " << std::dec << pNtHeaders->OptionalHeader.DllCharacteristics << std::endl;
    std::cout << "        SizeOfStackReserve:    " << std::dec << pNtHeaders->OptionalHeader.SizeOfStackReserve << std::endl;
    std::cout << "        SizeOfStackCommit:     " << std::dec << pNtHeaders->OptionalHeader.SizeOfStackCommit << std::endl;
    std::cout << "        SizeOfHeapReserve:     " << std::dec << pNtHeaders->OptionalHeader.SizeOfHeapReserve << std::endl;
    std::cout << "        SizeOfHeapCommit:      " << std::dec << pNtHeaders->OptionalHeader.SizeOfHeapCommit << std::endl;
    std::cout << "        LoaderFlags:           " << std::dec << pNtHeaders->OptionalHeader.LoaderFlags << std::endl;
    std::cout << "        NumberOfRvaAndSizes:   " << std::dec << pNtHeaders->OptionalHeader.NumberOfRvaAndSizes << std::endl;
    
    // DataDirectory
    std::cout << "        DataDirectory:" << std::endl;
    for (int i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; ++i)
    {
        IMAGE_DATA_DIRECTORY dataDirectory = pNtHeaders->OptionalHeader.DataDirectory[i];

        std::cout << "            [" << i << "] VirtualAddress: " << std::hex << dataDirectory.VirtualAddress
            << ", Size: " << std::dec << dataDirectory.Size << std::endl;
    }
    std::cout << std::endl;
}
void PrintExecutable(const std::string& filename)
{
    HANDLE hFile = CreateFileA(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier " << filename << std::endl;
        return;
    }

    HANDLE hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMap == NULL)
    {
        CloseHandle(hFile);
        std::cerr << "Erreur: Impossible de créer la vue cartographique pour le fichier " << filename << std::endl;
        return;
    }

    LPVOID lpBase = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
    if (lpBase == NULL)
    {
        CloseHandle(hMap);
        CloseHandle(hFile);
        std::cerr << "Erreur: Impossible de mapper la vue du fichier " << filename << std::endl;
        return;
    }

    PIMAGE_DOS_HEADER pDosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(lpBase);
    if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
    {
        std::cerr << "Erreur: Fichier DOS incorrect pour " << filename << std::endl;
        UnmapViewOfFile(lpBase);
        CloseHandle(hMap);
        CloseHandle(hFile);
        return;
    }

    PIMAGE_NT_HEADERS pNtHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>((reinterpret_cast<BYTE*>(lpBase)) + pDosHeader->e_lfanew);
    if (pNtHeaders->Signature != IMAGE_NT_SIGNATURE)
    {
        std::cerr << "Erreur: En-têtes NT incorrects pour " << filename << std::endl;
        UnmapViewOfFile(lpBase);
        CloseHandle(hMap);
        CloseHandle(hFile);
        return;
    }

    std::cout << "Informations sur l'exécutable : " << filename << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Taille du fichier: " << GetFileSize(hFile, NULL) << " octets" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << std::endl;

    PrintDosHeader(pDosHeader);
    PrintNtHeaders(pNtHeaders);

    UnmapViewOfFile(lpBase);
    CloseHandle(hMap);
    CloseHandle(hFile);
}

#endif

int main()
{
//     // PrintExecutable("C:\\Users\\PC-Gamer\\Documents\\Projects\\simple-script\\asm\\var_print.exe");
//     Compile("output.exe");
    return EXIT_SUCCESS;
}
