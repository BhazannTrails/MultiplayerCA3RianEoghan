#include <RoboCatServerPCH.h>


MouseServer::MouseServer()
{
}

void MouseServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject( this );
}


bool MouseServer::HandleCollisionWithCat( RoboCat* inCat )
{
	if (inCat->GetGunCount() < 1)
	{
		if (!picked)
		{
			/*if (inCat->GetHealth() <= 15)
				inCat->GetHealth()++;*/
			picked = true;
			for (int i = 0; i < 3; i++)
			{
				inCat->GetGunCount()++;
			}
			// Hacked in here.
			int ECRS_Health = 1 << 3;
			int ECRS_GunCount = 1 << 4;
			NetworkManagerServer::sInstance->SetStateDirty(inCat->GetNetworkId(), ECRS_Health);
			NetworkManagerServer::sInstance->SetStateDirty(inCat->GetNetworkId(), ECRS_GunCount);
		}
		//kill yourself!
		SetDoesWantToDie(true);
		return false;
	}
}


