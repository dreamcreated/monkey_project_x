#pragma once
#include <string>
namespace common {
class UserData
{
public:
	UserData(void);
	~UserData(void);
	int Pos_x() const { return m_pos_x; }
	void Pos_x(int val) { m_pos_x = val; }
	int Pos_y() const { return m_pos_y; }
	void Pos_y(int val) { m_pos_y = val; }
	std::string User_name() const { return m_user_name; }
	void User_name(std::string val) { m_user_name = val; }
	int Scene_id() const { return m_scene_id; }
	void Scene_id(int val) { m_scene_id = val; }
	unsigned int Player_id() const { return m_player_id; }
	void Player_id(unsigned int val) { m_player_id = val; }
private:
	std::string m_user_name;
	unsigned int m_player_id;
	int m_scene_id;
	int m_pos_x;
	int m_pos_y;
};
};
