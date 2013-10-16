#include "logic_context.h"
#include <monkey/net/message_queue.h>
#include "session_factory.h"
#include <monkey/service/service_manager.h>
#include "../service/scene_system.h"


logic_context::logic_context(void)
{
}


logic_context::~logic_context(void)
{
}

bool logic_context::init()
{
	boost::shared_ptr<session_factory> pFactory(new session_factory);
	monkey::net::message_queue::get_instance()->register_session_factory(pFactory);
	auto pServiceManager = monkey::service::service_manager::get_instance();

	//////////////////////////////////////////////////////////////////////////
	//开始注册各种service到service_manager
	//////////////////////////////////////////////////////////////////////////
	pServiceManager->register_service(boost::shared_ptr<scene_system>(scene_system::get_instance()));

	return pServiceManager->init();
}
