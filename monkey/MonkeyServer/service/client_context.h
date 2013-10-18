#pragma once
#include <monkey/net/session.h>
#include <common/userdata/UserData.h>
class client_context : public monkey::net::session
{
public:
	client_context(void);
	virtual ~client_context(void);
	common::UserData& User_data() { return m_user_data; }
private:
	common::UserData m_user_data;
};

