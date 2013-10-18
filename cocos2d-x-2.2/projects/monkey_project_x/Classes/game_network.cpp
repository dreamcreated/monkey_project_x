#include "game_network.h"
#include <common/messages/Login.pb.h>
#include <common/messages/scene_messages.pb.h>
#include "cocos2d.h"
#include <boost/lexical_cast.hpp>
#include "MainScene.h"


game_network::game_network(void)
{
}


game_network::~game_network(void)
{
}

void game_network::on_connected( boost::shared_ptr<connection_client> connection )
{
	std::string session_type = boost::lexical_cast<std::string>(connection->tag());
	auto iter = m_pre_messages.find(session_type);
	if (iter != m_pre_messages.end()) {
		for(auto i = iter->second.begin(); i != iter->second.end(); ++i) {
			connection->send_protobuf(*i);
		}
	}
	if (connection->tag() == LOGIN_SESSION) {
	}
	else if (connection->tag() == GAME_SESSION)  {
		CCLOG("connected!");
		boost::shared_ptr<common::scene_enter> pSceneEnter(new common::scene_enter);
		pSceneEnter->set_scene_id(1);
		connection->send_protobuf(pSceneEnter);
	}
}

void game_network::send_message_after_connected_send( const std::string session_type, boost::shared_ptr<google::protobuf::Message> message )
{
	auto iter = m_pre_messages.find(session_type);
	if (iter == m_pre_messages.end()) {
		auto ret = m_pre_messages.insert(std::make_pair(session_type, std::list<boost::shared_ptr<google::protobuf::Message>>()));
		assert (ret.second);
		ret.first->second.push_back(message);
	}
	else{
		iter->second.push_back(message);
	}
}
