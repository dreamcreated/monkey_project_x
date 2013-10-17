#pragma once
#include <monkey/net/session.h>

class game_session : public monkey::net::session
{
public:
	game_session(void);
	virtual ~game_session(void);
};

