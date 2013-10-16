#include "message_dispatcher.h"

namespace monkey{
namespace net{


extern void discard_protobuf_message( boost::shared_ptr<session> pSession, boost::shared_ptr<google::protobuf::Message> message )
{
	cout << "Discarding: " << message->GetTypeName() << endl;
}

};
};