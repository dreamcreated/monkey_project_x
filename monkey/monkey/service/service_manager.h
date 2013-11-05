#pragma once
#include <boost/shared_ptr.hpp>
#include <list>

#include "system_service.h"
#include "../utils/singleton.hpp"
namespace monkey{
namespace service{

class service_manager : public monkey::utils::singleton<service_manager>
{
public:
	service_manager(void);
	virtual ~service_manager(void);
	void register_service(boost::shared_ptr<system_service> pService);
	bool init();
	void fint();
	void on_user_enter(boost::shared_ptr<monkey::net::session> p_session);
	void on_user_leave(boost::shared_ptr<monkey::net::session> p_session);
private:
	std::list<boost::shared_ptr<system_service>> services_;
};

};
};
