#include "net_helper.h"


extern size_t monkey::net::net_helper::get_protobuf_package_len( const google::protobuf::Message* message )
{
	size_t nameLen = message->GetTypeName().length();
	size_t protobufLen = message->ByteSize();
	size_t len = 
		sizeof(nameLen)			//类型名长度值长度 
		+ nameLen				//类型名长度
		+ sizeof(protobufLen)	//protobuflen的长度
		+ protobufLen			//message本身长度
		+ sizeof(int);			//checksum长度
	return len;
}
