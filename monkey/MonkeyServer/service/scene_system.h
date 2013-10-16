#pragma once
#include <monkey/service/system_service.h>
#include <monkey/utils/singleton.hpp>
#include <common/messages/Login.pb.h>
#include <common/messages/scene_messages.pb.h>

class scene_system
	: public monkey::service::system_service
	, public monkey::utils::singleton<scene_system>
{
public:
	scene_system(void);
	virtual ~scene_system(void);

	static void on_scene_enter(boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::scene_enter> msg);
	static void on_scene_move(boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::scene_move> msg);

	virtual void on_user_enter(boost::shared_ptr<monkey::net::session> client_context);
	virtual void on_user_leave(boost::shared_ptr<monkey::net::session> client_context);
	virtual bool init();
	virtual void fint();

};

