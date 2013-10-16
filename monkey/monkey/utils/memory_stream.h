#pragma once
#include <google/protobuf/message.h>
#include <boost/shared_ptr.hpp>
//TODO 别忘了大小尾问题
namespace monkey {
namespace utils{

class memory_stream
{
public:
	explicit memory_stream(size_t size);
	explicit memory_stream(unsigned char* buf, size_t size);
	memory_stream(void);
	~memory_stream(void);

	void WriteInt32(int i);
	void WriteInt64(long long i);
	void WriteByte(unsigned char c);
	void WriteString(std::string str);
	void WriteProtobufMessage(const google::protobuf::Message * message);
	int ReadInt32();
	long long ReadInt64();
	unsigned char ReadByte();
	std::string ReadString();
	boost::shared_ptr<google::protobuf::Message> ReadProtobufMessage(size_t package_len);
	template<typename T> void WriteInteralTypeValue(T &v);
	template<typename T> T ReadInternalTypeValue();

private:
	unsigned char* mem_buffer_;
	size_t buf_len_;
	int read_index_;
	int write_index_;
	bool buf_need_delete;
};

template<typename T>
T memory_stream::ReadInternalTypeValue()
{
	T v;
	memcpy(&v, mem_buffer_ + read_index_, sizeof(v));
	read_index_ += sizeof(v);
	return v;
}

template<typename T>
void memory_stream::WriteInteralTypeValue( T &v )
{
	memcpy(mem_buffer_ + write_index_, &v, sizeof(v));
	write_index_ += sizeof(v);
}

};
};