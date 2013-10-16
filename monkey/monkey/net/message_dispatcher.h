#pragma once
#include <google/protobuf/message.h>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include "session.h"
#include <map>

using namespace std;

namespace monkey{
namespace net{


class callback : boost::noncopyable {
public:
	virtual ~callback() {};
	virtual void on_message(boost::shared_ptr<session> pSession, boost::shared_ptr<google::protobuf::Message> message) const = 0;
};

template<typename T>
class callbackT: public callback {
public:
	typedef boost::function<void (boost::shared_ptr<session> pSession, boost::shared_ptr<T> message)> protobuf_message_calllback;
	callbackT(const protobuf_message_calllback& callback)
	: callback_(callback) {

	}
	virtual void on_message(boost::shared_ptr<session> pSession, boost::shared_ptr<google::protobuf::Message> message) const {
		auto t = boost::dynamic_pointer_cast<T>(message);
		assert(t != NULL);
		callback_(pSession, t);
	}
private:
	protobuf_message_calllback callback_;
};

extern void discard_protobuf_message(boost::shared_ptr<session> pSession, boost::shared_ptr<google::protobuf::Message> message);

class message_dispatcher
{
public:
	message_dispatcher()
		: default_callback_(discard_protobuf_message) {

	}
	void on_message(boost::shared_ptr<session> pSession, boost::shared_ptr<google::protobuf::Message> message) const {
		callback_map::const_iterator it = callbacks_.find(message->GetDescriptor());
		if (it != callbacks_.end()) {
			it->second->on_message(pSession, message);
		}
		else {
			default_callback_(pSession, message);
		}
	}

	template<typename T>
	void register_message_callback(const typename callbackT<T>::protobuf_message_calllback& cb) {
		boost::shared_ptr<callbackT<T>> pd(new callbackT<T>(cb));
		callbacks_[T::descriptor()] = pd;
	}
private:
	typedef std::map<const google::protobuf::Descriptor*, boost::shared_ptr<callback>>	callback_map;
	callback_map callbacks_;
	boost::function<void (boost::shared_ptr<session> pSession, boost::shared_ptr<google::protobuf::Message>)> default_callback_;
};

};
};