#include "session_manager.h"

namespace monkey {
namespace net {

session_manager::session_manager(void)
{
}


session_manager::~session_manager(void)
{
}

const std::map<std::string, boost::shared_ptr<session>>& session_manager::get_session_map() const
{
	return sessions_;
}

void session_manager::unregister_session_delay( const std::string& key )
{
	boost::lock_guard<boost::mutex> guard(lock_);
	sessions_delay_remove.push_back(key);
}

void session_manager::gc()
{
	boost::lock_guard<boost::mutex> guard(lock_);
	for(auto i = sessions_delay_remove.begin(); i != sessions_delay_remove.end(); ++i) {
		unregister_session(*i);
	}
	sessions_delay_remove.clear();
}

void monkey::net::session_manager::register_session( const std::string& key, boost::shared_ptr<session> p_session )
{
	auto ret = sessions_.insert(std::make_pair(key, p_session));
	assert(ret.second);
}

void monkey::net::session_manager::unregister_session( const std::string& key )
{
	auto ret = sessions_.erase(key);
	assert(ret == 1);
}

};
};