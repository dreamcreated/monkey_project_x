#ifndef __CLIENTUSERDATA_H__
#define __CLIENTUSERDATA_H__
#include <common/userdata/UserData.h>
#include <monkey/utils/singleton.hpp>

class ClientUserData
	: public common::UserData
	, public monkey::utils::singleton<ClientUserData>
{
	
};


#endif