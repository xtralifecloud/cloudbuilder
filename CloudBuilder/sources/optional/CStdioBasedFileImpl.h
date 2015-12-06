//
//  CStdioBasedFileImpl.h
//  CloudBuilder
//
//  Default implementation of the File structures defined in the CFilesystemManager class
//  using stdio's FILE structure as an underlying functionality. If your platform supports
//  this libc feature, then you should include this source file.
//
//  Created by Florian B on 13/08/14.
//  Copyright 2014 Clan of the Cloud. All rights reserved.
//

#ifndef CloudBuilder_CStdioBasedFileImpl_h
#define CloudBuilder_CStdioBasedFileImpl_h

#include <stdio.h>
#include "CFilesystem.h"

namespace CloudBuilder {
	class CInputFileStdio: public CInputFile {
		FILE *underlyingFile;

		virtual void Close();
		virtual size_t Tell();
		virtual bool IsOpen();
		virtual size_t Read(void *destBuffer, size_t numBytes);
		virtual bool Seek(long offset, int whence);

	public:
		CInputFileStdio(const char *fileName);
		~CInputFileStdio();
	};

	class COutputFileStdio: public COutputFile {
		FILE *underlyingFile;

		virtual void Close();
		virtual bool IsOpen();
		virtual size_t Write(const void *sourceBuffer, size_t numBytes);

	public:
		COutputFileStdio(const char *fileName);
		~COutputFileStdio();
	};
}

#endif
