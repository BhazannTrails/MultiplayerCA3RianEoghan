#include <RoboCatServerPCH.h>
#include <stdlib.h>

BloodServer::BloodServer()
{
}

void BloodServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


//bool MouseServer::HandleCollisionWithCat(RoboCat* inCat)
//{
	//if (inCat->GetGunCount() < 1)
	//{
	//	if (!picked)
	//	{
	//		/*if (inCat->GetHealth() <= 15)
	//			inCat->GetHealth()++;*/

	//			//Eoghan
	//		int shootModeInt = rand() % 3 + 1;
	//		uint8_t shootModeRandom = (uint8_t)shootModeInt;
	//		inCat->setShootMode(shootModeRandom);
	//		picked = true;

	//		//Ryan
	//		for (int i = 0; i < 3; i++)
	//		{
	//			inCat->GetGunCount()++;
	//		}
	//		// Hacked in here.
	//		//Eoghan & Ryan
	//		int ECRS_Health = 1 << 3;
	//		int ECRS_GunCount = 1 << 4;
	//		int ECRS_ShootMode = 1 << 5;
	//		NetworkManagerServer::sInstance->SetStateDirty(inCat->GetNetworkId(), ECRS_Health);
	//		NetworkManagerServer::sInstance->SetStateDirty(inCat->GetNetworkId(), ECRS_GunCount);
	//		NetworkManagerServer::sInstance->SetStateDirty(inCat->GetNetworkId(), ECRS_ShootMode);
	//	}
	//	//kill yourself!
	//	SetDoesWantToDie(true);
	//	return false;
	//}
//}


