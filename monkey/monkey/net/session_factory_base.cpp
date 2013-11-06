#include "session_factory_base.h"
#include "session_manager.h"

namespace monkey{
namespace net{

boost::shared_ptr<session> session_factory_base::create_session( boost::shared_ptr<connection> conn, boost::shared_ptr<google::protobuf::Message> message )
{
	if (verify_connection(conn, message)) {
		boost::shared_ptr<session> pSession = new_session(message);
		conn->session_ = pSession;
		pSession->connection_ = conn;
		conn->session_key_ = on_verify_successed(pSession, message);
		session_manager::get_instance()->register_session(conn->session_key_, pSession);
		return pSession;
	}
	else {
		on_verify_failed(message);
		return nullptr;
	}
}

session_factory_base::session_factory_base()
{

}

session_factory_base::~session_factory_base()
{

}

};
};