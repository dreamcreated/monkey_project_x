#pragma once
#include "../utils/singleton.hpp"
#include <map>
#include <boost/shared_ptr.hpp>
#include "session.h"
#include <string>
#include <list>
#include <boost/thread.hpp>

namespace monkey {
namespace net{

class session_manager : public monkey::utils::singleton<session_manager>
{
public:
	session_manager(void);
	virtual ~session_manager(void);
	void register_session(const std::string& key, boost::shared_ptr<session> p_session);
	void unregister_session(const std::string& key);
	void unregister_session_delay(const std::string& key);
	void gc();
	const std::map<std::string, boost::shared_ptr<session>>& get_session_map() const;
private:
	std::map<std::string, boost::shared_ptr<session>> sessions_;
	std::list<std::string> sessions_delay_remove;
	boost::mutex lock_;
};

};
};

