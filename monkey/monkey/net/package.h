#pragma once
namespace monkey {
namespace net{

class package
{
public:
	package() : buffer_(nullptr){}
	package(size_t size)
	:buffer_(new unsigned char[size])
	, size_(size) {

	}
	~package() {
		if (buffer_) {
			delete[] buffer_;
		}
	}
	size_t size() const {
		return size_;
	}

	operator unsigned char*() {
		return buffer_;
	}

private:
	unsigned char* buffer_;
	size_t size_;
};

};};