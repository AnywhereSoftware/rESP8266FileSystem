#include "B4RDefines.h"

namespace B4R {
	B4RFileSystem::B4RFileSystem(){
		stream.wrappedStream = &b4rfile.file;
	}
	bool B4RFileSystem::Initialize() {
		return SPIFFS.begin();
	}
	bool B4RFileSystem::Format() {
		return SPIFFS.format();
	}
	bool B4RFileSystem::open (B4RString* FileName, const char* mode) {
		b4rfile.file.close();
		b4rfile.file = SPIFFS.open(FileName->data, mode);
		if (b4rfile.file == true) {
			b4rfile.file.seek(0, SeekSet);
			return true;
		}
		return false;
	}
	bool B4RFileSystem::OpenRead(B4RString* FileName) {
		return open(FileName, "r");
	}
	bool B4RFileSystem::OpenReadWrite (B4RString* FileName) {
		if (Exists(FileName))
			return open(FileName, "r+");
		else
			return open(FileName, "w+");
	}
	bool B4RFileSystem::Exists(B4RString* FileName) {
		return SPIFFS.exists(FileName->data);
	}
	B4RStream* B4RFileSystem::getStream() {
		return &stream;
	}
	ULong B4RFileSystem::getPosition() {
		return b4rfile.file.position();
	}
	void B4RFileSystem::setPosition(ULong p) {
		b4rfile.file.seek(p, SeekSet);
	}
	B4RFile* B4RFileSystem::getCurrentFile() {
		return &b4rfile;
	}
	void B4RFileSystem::Close() {
		return b4rfile.file.close();
	}
	bool B4RFileSystem::Remove (B4RString* FileName) {
		return SPIFFS.remove(FileName->data);
	}
	ULong B4RFileSystem::getTotalSize() {
		FSInfo f;
		SPIFFS.info(f);
		return f.totalBytes;
	}
	ULong B4RFileSystem::getUsedSize() {
		FSInfo f;
		SPIFFS.info(f);
		return f.usedBytes;
	}
	FileIterator* B4RFileSystem::ListFiles(B4RString* DirName) {
		FileIterator* it = CreateStackMemoryObject (FileIterator);
		it->dir = SPIFFS.openDir(DirName->data);
		it->current = new (it->backend) B4RFile();
		it->o.wrapPointer(it->current);
		return it;
	}
	
	ULong B4RFile::getSize() {
		return file.size();
	}
	B4RString* B4RFile::getName() {
		stringBackend.wrap(file.name());
		return &stringBackend;
	}
	
	bool FileIterator::MoveNext() {
		current->file.close();
		if (dir.next()) {
			current->file = dir.openFile("r");
			return true;
		} else {
			return false;
		}
	}
	Object* FileIterator::Get() {
		return &o;
	}
	
	
}