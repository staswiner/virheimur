#include "Item_Base_Class.h"



Item_Base_Class::Item_Base_Class()
	:lifeTimeOnGround(60000) // 1 minute
{

}


Item_Base_Class::~Item_Base_Class()
{
}

void Item_Base_Class::Equip()
{
	// TODO: assign to clientID's equipment uppon action
	this->state = e_equiped;
}

void Item_Base_Class::Pick()
{
	// TODO: put item in inventory of clientIDS
	this->state = e_inInventory;
}
