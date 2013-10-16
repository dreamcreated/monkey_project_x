#include "memory_stream.h"
#include <string>
#include <boost/crc.hpp>
#include "../net/net_helper.h"
namespace monkey {
namespace utils{

memory_stream::memory_stream( size_t size )
	: mem_buffer_ (new unsigned char[size])
	, buf_len_(size)
	, buf_need_delete(true)
	, read_index_(0)
	, write_index_(0)
{
}

memory_stream::memory_stream( unsigned char* buf, size_t size )
	: mem_buffer_(buf)
	, buf_len_(size)
	, buf_need_delete(false)
	, read_index_(0)
	, write_index_(0)
{
}

memory_stream::~memory_stream( void )
{
	if (buf_need_delete && mem_buffer_){
		delete[] mem_buffer_;
	}
}

void memory_stream::WriteInt32( int i )
{
	WriteInteralTypeValue(i);
}

void memory_stream::WriteInt64( long long i )
{
	WriteInteralTypeValue(i);
}

void memory_stream::WriteByte( unsigned char c )
{
	WriteInteralTypeValue(c);
}

int memory_stream::ReadInt32()
{
	return ReadInternalTypeValue<int>();
}

long long memory_stream::ReadInt64()
{
	return ReadInternalTypeValue<long long>();
}

unsigned char memory_stream::ReadByte()
{
	return ReadInternalTypeValue<unsigned char>();
}

void monkey::utils::memory_stream::WriteString( std::string str )
{
	WriteInt32(str.length());
	memcpy(mem_buffer_ + write_index_, str.c_str(), str.length());
	write_index_ += str.length();
}

std::string monkey::utils::memory_stream::ReadString()
{
	size_t length = ReadInt32();
	char *str = new char[length];
	memcpy(str, mem_buffer_ + read_index_, length);
	read_index_ += length;
	std::string stdstr(str, length);
	delete[] str;
	return stdstr;
}

void monkey::utils::memory_stream::WriteProtobufMessage( const google::protobuf::Message * message )
{
	size_t nameLen = message->GetTypeName().length();
	size_t protobufLen = message->ByteSize();
	size_t len = monkey::net::net_helper::get_protobuf_package_len(message);
	WriteInt32(len);
	int startIndex = write_index_;
	WriteString(message->GetTypeName());
	WriteInt32(protobufLen);
	message->SerializeToArray(mem_buffer_ + write_index_, protobufLen);
	write_index_ += protobufLen;
	boost::crc_32_type crcRet;
	crcRet.process_bytes(mem_buffer_ + startIndex, write_index_ - startIndex);
	WriteInt32(crcRet.checksum());
}

boost::shared_ptr<google::protobuf::Message> memory_stream::ReadProtobufMessage( size_t package_len )
{
	int packageLen = package_len;
	int checkSum = 0;
	memcpy(&checkSum, mem_buffer_ + read_index_ + packageLen - sizeof(checkSum), sizeof(checkSum));
	boost::crc_32_type crcRet;
	crcRet.process_bytes(mem_buffer_ + read_index_, packageLen - sizeof(checkSum));
	boost::shared_ptr<google::protobuf::Message> message;
	if (crcRet.checksum() != checkSum) 
		return message;

	std::string typeName = ReadString();
	const google::protobuf::Descriptor* descriptor = 
		google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(typeName);
	if (descriptor) {
		const google::protobuf::Message* prototype =
			google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
		if (prototype) {
			message.reset(prototype->New());
			if (message) {
				int protobufLen = ReadInt32();
				if (message->ParseFromArray(mem_buffer_ + read_index_, protobufLen)) {
					read_index_ += protobufLen + sizeof(checkSum);
					return message;
				}
				else {
					message.reset();
				}
			}
		}
	}
	return message;
}

};
};