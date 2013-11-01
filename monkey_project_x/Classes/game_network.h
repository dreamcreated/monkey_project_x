#pragma once
#include "network.h"
#include <monkey/utils/singleton.hpp>
#include <string>
#include <map>
#include <list>
#include <boost/shared_ptr.hpp>
#include <google/protobuf/message.h>

enum SESSION_TYPE {
	LOGIN_SESSION,
	GAME_SESSION
};

namespace SESSIONS {
	const std::string LOGIN_SESSION = "0";
	const std::string GAME_SESSION = "1";
}

class game_network 
	: public network
	, public monkey::utils::singleton<game_network>
{
public:
	virtual void on_connected( boost::shared_ptr<connection_client> connection);
	game_network(void);
	virtual ~game_network(void);
	std::map<std::string, std::list<boost::shared_ptr<google::protobuf::Message>>> m_pre_messages;
	//添加一条消息,该消息将在连接成功后发送
	void send_message_after_connected_send(const std::string session_type, boost::shared_ptr<google::protobuf::Message> message);
};

