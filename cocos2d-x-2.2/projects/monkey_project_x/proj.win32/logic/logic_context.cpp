#include "logic_context.h"
#include "system/scene_system.h"
#include <monkey/service/service_manager.h>


logic_context::logic_context(void)
{
}


logic_context::~logic_context(void)
{
}

bool logic_context::init()
{
	using namespace monkey::service;
	auto p_service_manager = service_manager::get_instance();
	p_service_manager->register_service(boost::shared_ptr<scene_system>(scene_system::get_instance()));

	return p_service_manager->init();
}
