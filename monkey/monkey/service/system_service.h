#pragma once
#include <string>
#include <boost/shared_ptr.hpp>
#include "../net/session.h"

namespace monkey{
namespace service{

class system_service
{
public:
	virtual bool init() = 0;
	virtual void fint() = 0;
	virtual void on_user_enter(boost::shared_ptr<monkey::net::session> client_context) = 0;
	virtual void on_user_leave(boost::shared_ptr<monkey::net::session> client_context) = 0;
	virtual void on_registered();
	system_service(const std::string& name) :
		service_name_(name) {}
	virtual ~system_service() {}
	const std::string& get_service_name() {
		return service_name_;
	}
private:
	std::string service_name_;
};

};
};
