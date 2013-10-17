#pragma once
#include <monkey/service/system_service.h>
#include <monkey/utils/singleton.hpp>
#include <common/messages/scene_messages.pb.h>
#include <boost/shared_ptr.hpp>

class scene_system
	: public monkey::service::system_service
	, public monkey::utils::singleton<scene_system>
{
public:

	static void on_scene_enter(boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::scene_enter> msg);

	bool init();
	void fint();
	void on_user_enter(boost::shared_ptr<monkey::net::session> client_context);
	void on_user_leave(boost::shared_ptr<monkey::net::session> client_context);

	scene_system(void);
	~scene_system(void);
};

