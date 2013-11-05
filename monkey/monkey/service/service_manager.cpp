#include "service_manager.h"
#include <iostream>


monkey::service::service_manager::service_manager(void)
{
}


monkey::service::service_manager::~service_manager(void)
{
}

void monkey::service::service_manager::register_service( boost::shared_ptr<system_service> pService )
{
	services_.push_back(pService);
	pService->on_registered();
	std::cout << "----------Service: [" << pService->get_service_name() << "] registered!----------" << std::endl;
}

bool monkey::service::service_manager::init()
{
	for(auto i = services_.begin(); i != services_.end(); ++i) {
		if (!(*i)->init())
			return false;
	}
	return true;
}

void monkey::service::service_manager::fint()
{
	for(auto i = services_.begin(); i != services_.end(); ++i) {
		(*i)->fint();
	}
}

void monkey::service::service_manager::on_user_enter( boost::shared_ptr<monkey::net::session> p_session )
{
	for(auto i = services_.begin(); i != services_.end(); ++i) {
		(*i)->on_user_enter(p_session);
	}
}

void monkey::service::service_manager::on_user_leave( boost::shared_ptr<monkey::net::session> p_session )
{
	for(auto i = services_.begin(); i != services_.end(); ++i) {
		(*i)->on_user_leave(p_session);
	}
}
