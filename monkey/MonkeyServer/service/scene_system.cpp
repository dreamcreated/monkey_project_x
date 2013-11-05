#include "scene_system.h"
#include <monkey/net/message_queue.h>
#include <monkey/net/session_manager.h>
#include "client_context.h"
#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>

using namespace monkey::net;


scene_system::scene_system(void)
	: system_service("scene_system")
{
}


scene_system::~scene_system(void)
{
}

bool scene_system::init()
{
	 auto &message_dispatcher = message_queue::get_instance()->get_dispatcher();
	 message_dispatcher.register_message_callback<common::scene_enter>(&scene_system::on_scene_enter);
	 message_dispatcher.register_message_callback<common::scene_move>(&scene_system::on_scene_move);
	 //TODO 初始化场景相关数据
	 m_scene_player.insert(std::make_pair(1, std::set<int>()));
	 return true;
}

void scene_system::fint()
{

}

void scene_system::on_user_enter( boost::shared_ptr<monkey::net::session> pSession )
{

}

void scene_system::on_user_leave( boost::shared_ptr<monkey::net::session> pSession )
{
	auto pClientContext = boost::dynamic_pointer_cast<client_context>(pSession);

	auto& playerSet = m_scene_player.at(pClientContext->User_data().Scene_id());
	auto playerIter = playerSet.find(pClientContext->User_data().Player_id());
	if (playerIter != playerSet.end()) {
		playerSet.erase(playerIter);
	}
}

void scene_system::on_scene_enter( boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::scene_enter> msg )
{
	std::cout << "on_enter scene" << std::endl;
	msg->PrintDebugString();
	auto pClientContext = boost::dynamic_pointer_cast<client_context>(pSession);
	pClientContext->User_data().Scene_id(msg->scene_id());
	//TODO 进入场景的初始位置
	pClientContext->User_data().Pos_x(10);
	pClientContext->User_data().Pos_y(10);
	msg->mutable_player_info()->CopyFrom(pClientContext->User_data().Player_info());

	auto pThis = scene_system::get_instance();

	//广播给场景内的所有玩家
	auto& playerSet = pThis->m_scene_player.at(msg->scene_id());
	auto playerIter = playerSet.find(pClientContext->User_data().Player_id());
	if (playerIter == playerSet.end()) {
		playerSet.insert(pClientContext->User_data().Player_id());
	}
	auto &sessions = session_manager::get_instance()->get_session_map();
	boost::shared_ptr<common::player_list> playerList(new common::player_list); //= boost::make_shared<common::player_list>();
	for(auto i = playerSet.begin(); i != playerSet.end(); ++i) {
		auto sessionIter = sessions.find(boost::lexical_cast<std::string>(*i));
		if (sessionIter != sessions.end()) {
			auto otherClientContext = boost::dynamic_pointer_cast<client_context>(sessionIter->second);
			otherClientContext->get_connection()->send_protobuf(msg);

			//构造player_list消息
 			auto pAddedPlayer = playerList->add_players();
			pAddedPlayer->CopyFrom(otherClientContext->User_data().Player_info());
		}
	}

	//把场景内所有玩家发送给当前进入的玩家
	pClientContext->get_connection()->send_protobuf(playerList);
}

void scene_system::on_scene_move( boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::scene_move> msg )
{
	std::cout << "on_scene_move" << std::endl;
	msg->PrintDebugString();

	auto pClientContext = boost::dynamic_pointer_cast<client_context>(pSession);
	pClientContext->User_data().Pos_x(msg->target_x());
	pClientContext->User_data().Pos_y(msg->target_y());
	auto &sessions = session_manager::get_instance()->get_session_map();

	auto pThis = scene_system::get_instance();
	auto& playerSet = pThis->m_scene_player.at(pClientContext->User_data().Scene_id());
	for(auto i = playerSet.begin(); i != playerSet.end(); ++i) {
		auto sessionIter = sessions.find(boost::lexical_cast<std::string>(*i));
		if (sessionIter != sessions.end()) {
			sessionIter->second->get_connection()->send_protobuf(msg);
		}
	}
}
