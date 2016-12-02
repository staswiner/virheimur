#pragma once
class Item_Base_Class
{
public:
	Item_Base_Class();
	~Item_Base_Class();
	void Equip();
	void Pick();
	void Delete();
	void DropFromMonster();
	void DropFromChampion();

	

	// Item States
	enum{
		e_onGround,
		e_inInventory,
		e_equiped,
		e_inTrade
	};

private:
	unsigned int state;
	const unsigned int lifeTimeOnGround;
};

