#pragma once
#include "network.h"
#include <monkey/utils/singleton.hpp>

enum SESSION_TYPE {
	LOGIN_SESSION,
	GAME_SESSION
};

class game_network 
	: public network
	, public monkey::utils::singleton<game_network>
{
public:
	virtual void on_connected( boost::shared_ptr<connection_client> connection);
	game_network(void);
	virtual ~game_network(void);
};

