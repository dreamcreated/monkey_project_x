#pragma once
#include "message_dispatcher.h"
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <queue>
#include <google/protobuf/message.h>
#include "../utils/singleton.hpp"
#include "connection.h"
#include "session_factory_base.h"

namespace monkey{
namespace net{

class message_queue : public monkey::utils::singleton<message_queue>
{
public:
	message_queue(void);
	~message_queue(void);
	void push(boost::shared_ptr<connection> conn, boost::shared_ptr<google::protobuf::Message> message);
	void async_run();
	void async_stop();
	void register_session_factory(boost::shared_ptr<session_factory_base> factory);
	message_dispatcher& get_dispatcher();
	void update();
private:
	void run();
	std::queue<std::pair<boost::shared_ptr<connection>, boost::shared_ptr<google::protobuf::Message>>> messages_;
	boost::mutex lock_;
	message_dispatcher dispatcher_;
	boost::shared_ptr<session_factory_base> session_factory_;
	boost::shared_ptr<boost::thread> work_thread_;
	bool is_running_;
};

};
};
