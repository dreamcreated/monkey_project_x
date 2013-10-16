#pragma once
#include <boost/shared_ptr.hpp>
namespace monkey{
namespace net{

class connection;
class session_factory_base;
class session
{
	friend class session_factory_base;
public:
	session(void);
	virtual ~session(void);
	boost::shared_ptr<connection> get_connection();
private:
	boost::shared_ptr<connection> connection_;
};

};
};