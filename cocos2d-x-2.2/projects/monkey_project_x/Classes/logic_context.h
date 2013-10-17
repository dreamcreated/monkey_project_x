#pragma once
#include <monkey/utils/singleton.hpp>
class logic_context 
	: public monkey::utils::singleton<logic_context>
{
public:
	bool init();
	logic_context(void);
	~logic_context(void);
};

