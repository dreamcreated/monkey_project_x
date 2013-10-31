#include "message_dispatcher.h"
#include <iostream>

namespace monkey{
namespace net{


extern void discard_protobuf_message( boost::shared_ptr<session> pSession, boost::shared_ptr<google::protobuf::Message> message )
{
	std::cout << "Discarding: " << message->GetTypeName() << std::endl;
}

};
};