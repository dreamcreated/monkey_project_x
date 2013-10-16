#pragma once
#include <google/protobuf/message.h>
namespace monkey{
namespace net{
namespace net_helper{
	extern size_t get_protobuf_package_len(const google::protobuf::Message* message);
};
};
};
