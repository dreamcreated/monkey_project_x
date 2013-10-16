#include "net_helper.h"


extern size_t monkey::net::net_helper::get_protobuf_package_len( const google::protobuf::Message* message )
{
	size_t nameLen = message->GetTypeName().length();
	size_t protobufLen = message->ByteSize();
	size_t len = 
		sizeof(nameLen)			//����������ֵ���� 
		+ nameLen				//����������
		+ sizeof(protobufLen)	//protobuflen�ĳ���
		+ protobufLen			//message������
		+ sizeof(int);			//checksum����
	return len;
}
