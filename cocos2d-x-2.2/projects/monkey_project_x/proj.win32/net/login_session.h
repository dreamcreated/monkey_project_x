#pragma once
#include <monkey/net/session.h>
class login_session : public monkey::net::session
{
public:
	login_session(void);
	virtual ~login_session(void);
};

