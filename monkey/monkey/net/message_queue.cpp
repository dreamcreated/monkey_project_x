#include "message_queue.h"
#include "session_manager.h"

namespace monkey{
namespace net{

message_queue::message_queue(void)
	: is_running_(false)
{
}


message_queue::~message_queue(void)
{
}

void message_queue::push( boost::shared_ptr<connection> conn, boost::shared_ptr<google::protobuf::Message> message )
{
	boost::lock_guard<boost::mutex> guard(lock_);
	messages_.push(std::make_pair(conn, message));
}

void message_queue::run()
{
	while(is_running_) {
		update();
		//休眠,防止CPU占用过高
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
}

void message_queue::update()
{
	if (!messages_.empty()) {
		lock_.lock();
		auto pMessage = messages_.front();
		messages_.pop();
		lock_.unlock();
		auto pSession = pMessage.first->get_session();
		if (pSession) {
			dispatcher_.on_message(pSession, pMessage.second);
		}
		else {
			if (session_factory_) {
				pSession = session_factory_->create_session(pMessage.first, pMessage.second);
				if (!pSession) {
					pMessage.first->close();
				}
			}
			else {
				throw runtime_error("session factory not set, please call function message_queue::get_instance()->register_session_factory set session factory");
			}
		}
	}
	session_manager::get_instance()->gc();
}

void message_queue::register_session_factory( boost::shared_ptr<session_factory_base> factory )
{
	boost::lock_guard<boost::mutex> guard(lock_);
	session_factory_ = factory;
}

message_dispatcher& message_queue::get_dispatcher()
{
	return dispatcher_;
}

void message_queue::async_run()
{
	is_running_ = true;
	work_thread_.reset(new boost::thread(boost::bind(&message_queue::run, this)));
}

void message_queue::async_stop()
{
	is_running_ = false;
	work_thread_->join();
}

};
};