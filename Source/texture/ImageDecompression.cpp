/*
Heavily based on code written by Igor Pavlov;
see enclosed file "ImageDecompression_original (7zMain).c"
*/

#include "ImageDecompression.h"

#include <iostream>
#include <string>

#include <7z.h>
#include <7zAlloc.h>
#include <7zBuf.h>
#include <7zCrc.h>
#include <7zFile.h>
#include <7zVersion.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void printError(char* sz)
{
	std::cerr << "\nERROR: " << sz << std::endl;
}

#define ERROR_HANDLED -1

unsigned char* extractImageFrom7zFile(char* file, int* width, int* height, GLenum* format)
{
	unsigned char* imageData = nullptr;

	CFileInStream archiveStream;
	CLookToRead lookStream;
	CSzArEx db;
	SRes res;
	ISzAlloc allocImp;
	ISzAlloc allocTempImp;
	UInt16* temp = nullptr;
	size_t tempSize = 0;

#if defined(_WIN32) && !defined(USE_WINDOWS_FILE) && !defined(UNDER_CE)
	g_FileCodePage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;
#endif

	allocImp.Alloc = SzAlloc;
	allocImp.Free = SzFree;

	allocTempImp.Alloc = SzAllocTemp;
	allocTempImp.Free = SzFreeTemp;

	if (InFile_Open(&archiveStream.file, file))
	{
		printError("cannot open input file");
		return nullptr;
	}

	FileInStream_CreateVTable(&archiveStream);
	LookToRead_CreateVTable(&lookStream, False);

	lookStream.realStream = &archiveStream.s;
	LookToRead_Init(&lookStream);

	CrcGenerateTable();

	SzArEx_Init(&db);

	res = SzArEx_Open(&db, &lookStream.s, &allocImp, &allocTempImp);

	if (res != SZ_OK)
		goto cleanup;

	if (db.NumFiles > 1)
	{
		printError("cannot extract an image from an archive containing more than one image file");
		res = ERROR_HANDLED;
		goto cleanup;
	} else if (SzArEx_IsDir(&db, 0))
	{
		printError("no image file found in archive");
		res = ERROR_HANDLED;
		goto cleanup;
	}

	/* [Comment by original author]
	if you need cache, use these 3 variables.
	if you use external function, you can make these variable as static.
	*/
	UInt32 blockIndex = 0xFFFFFFFF;
	Byte* outBuffer = 0;
	size_t outBufferSize = 0;

	size_t offset = 0;
	size_t outSizeProcessed = 0;
	size_t len = SzArEx_GetFileNameUtf16(&db, 0, nullptr);
	if (len > tempSize)
	{
		SzFree(nullptr, temp);
		tempSize = len;
		temp = (UInt16*)SzAlloc(nullptr, tempSize * sizeof(temp[0]));
		if (temp == nullptr)
		{
			res = SZ_ERROR_MEM;
			goto cleanup;
		}
	}

	SzArEx_GetFileNameUtf16(&db, 0, temp);

	if (res != SZ_OK)
		goto cleanup;

	res = SzArEx_Extract(&db, &lookStream.s, 0,
						 &blockIndex, &outBuffer, &outBufferSize,
						 &offset, &outSizeProcessed,
						 &allocImp, &allocTempImp);

	if (res != SZ_OK)
	{
		IAlloc_Free(&allocImp, outBuffer);
		goto cleanup;
	}

	stbi_set_flip_vertically_on_load(true);
	int components;
	imageData = stbi_load_from_memory(outBuffer + offset, (int)outBufferSize, width, height, &components, 0);
	*format = (components == 4) ? GL_RGBA : GL_RGB;

	/* --- File writing code ---

	CSzFile outFile;
	size_t processedSize;
	size_t j;
	UInt16* name = (UInt16*)temp;

	// [Paragraph supplied by me]
	std::string fileDirectory = std::string(fileName);
	fileDirectory = fileDirectory.substr(0, fileDirectory.find_last_of('/') + 1);
	std::wstring destPath_wstring = std::wstring(fileDirectory.begin(), fileDirectory.end()) + std::wstring((const WCHAR*)name);

	const WCHAR* destPath = destPath_wstring.c_str();
	std::cout << std::endl;
	for (j = 0; name[j] != 0; j++)
	//if (name[j] == '/')
	//{
	//	if (fullPaths)
	//	{
	//		name[j] = 0;
	//		MyCreateDir(name);
	//		name[j] = CHAR_PATH_SEPARATOR;
	//	} else
	//		destPath = name + j + 1;
	//}
	std::cout << (WCHAR)(name[j]) << std::flush;

	if (isDir)
	{
	//MyCreateDir(destPath);
	//printf("\n");
	//continue;
	return;
	} else if (OutFile_OpenUtf16(&outFile, destPath))
	{
	printError("cannot open output file");
	res = SZ_ERROR_FAIL;
	break;
	}

	processedSize = outSizeProcessed;

	if (File_Write(&outFile, outBuffer + offset, &processedSize) != 0 || processedSize != outSizeProcessed)
	{
	printError("cannot write output file");
	res = SZ_ERROR_FAIL;
	break;
	}

	if (File_Close(&outFile))
	{
	printError("cannot close output file");
	res = SZ_ERROR_FAIL;
	break;
	}

	#ifdef USE_WINDOWS_FILE
	if (SzBitWithVals_Check(&db.Attribs, i))
	SetFileAttributesW(destPath, db.Attribs.Vals[i]);
	#endif
	printf("\n");

	*/

	IAlloc_Free(&allocImp, outBuffer);

cleanup:
	SzArEx_Free(&db, &allocImp);
	SzFree(nullptr, temp);

	File_Close(&archiveStream.file);

	if (res != SZ_OK)
	{
		if (res == SZ_ERROR_UNSUPPORTED)
			printError("decoder doesn't support this archive");
		else if (res == SZ_ERROR_MEM)
			printError("cannot allocate memory");
		else if (res == SZ_ERROR_CRC)
			printError("CRC error");
		else if (res != ERROR_HANDLED)
			std::cerr << "\nERROR #" << res << std::endl;

		return nullptr;
	}

	return imageData;
}

void freeImageData(unsigned char* imageData)
{
	stbi_image_free(imageData);
}
