#pragma once
#include "B4RDefines.h"
#include "FS.h"
namespace B4R {
	//~version: 1.00
	//~shortname: File
	class B4RFile {
		private:
			B4RString stringBackend;
		public:
			//~hide
			File file;
			//Returns the file size (number of bytes).
			ULong getSize();
			//Returns the file name.
			B4RString* getName();
	};
	//~hide
	class FileIterator : public Iterator{
		public:
			Object o;
			B4RFile* current;
			uint8_t backend[sizeof(B4RFile)];
			Dir dir;
			virtual bool MoveNext() override;
			virtual Object* Get() override;
						
	};
	
	//~shortname: ESP8266FileSystem
	class B4RFileSystem {
		private:
			B4RFile b4rfile;
			B4RStream stream;
			bool open (B4RString* FileName, const char* mode);
		public:
			//~hide
			B4RFileSystem();
			//Initializes the file system. Returns True if successful.
			bool Initialize();
			//Formats the file system. Note that this can take more than a minute to complete.
			//Returns True if successful.
			bool Format();
			//Opens a file in read only mode. Returns true if the file was opened successfully.
			bool OpenRead (B4RString* FileName);
			//Opens a file in read and write mode. Returns true if the file was opened successfully.
			bool OpenReadWrite (B4RString* FileName);
			//Returns the current open file.
			B4RFile* getCurrentFile();
			//Returns the stream of the current open file.
			B4RStream* getStream();
			//Gets or sets the position in the current open file.
			ULong getPosition();
			void setPosition(ULong p);
			//Closes the current open file.
			void Close();
			//Checks whether the given file or directory exist.
			bool Exists(B4RString* FileName);
			//Deletes the given file. Returns true if the file was successfully deleted.
			bool Remove(B4RString* FileName);
			/**
			*Can be used in a For Each loop to iterate over the files in the folder.
			*Example:<code>
			 *For Each f As File In fs.ListFiles("/")
			 *	Log("Name: ", f.Name, ", Size: ", f.Size)
			 *Next</code>
			*/
			FileIterator* ListFiles(B4RString* DirName);
			ULong getTotalSize();
			ULong getUsedSize();
	};
}