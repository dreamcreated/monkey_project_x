#pragma once
#include <monkey/net/session.h>
class client_context : public monkey::net::session
{
public:
	client_context(void);
	virtual ~client_context(void);
};

