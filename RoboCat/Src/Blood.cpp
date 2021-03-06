#include <RoboCatPCH.h>
#include <cstdlib>

Blood::Blood()
{
	SetScale(GetScale() * 1.f);
	SetCollisionRadius(0.f);

}

//bool Mouse::HandleCollisionWithCat(RoboCat* inCat)
//{
//	if (inCat->GetGunCount() < 1)
//	{
//		if (!picked)
//		{
//
//			//inCat->SetShootMode(2);
//			//inCat->GetShootMode()++;
//			//		inCat->GetHealth()++;
//			picked = true;
//
//			SoundManager::sInstance->PlaySound(SoundManager::SoundToPlay::STP_Pickup);
//		}
//		(void)inCat;
//
//		return false;
//	}
//}



uint32_t Blood::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & EBRS_Pose)
	{
		inOutputStream.Write((bool)true);

		Vector3 location = GetLocation();
		inOutputStream.Write(location.mX);
		inOutputStream.Write(location.mY);

		inOutputStream.Write(GetRotation());

		writtenState |= EBRS_Pose;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & EBRS_Color)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(GetColor());

		writtenState |= EBRS_Color;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}


	return writtenState;
}

void Blood::Read(InputMemoryBitStream& inInputStream)
{
	bool stateBit;

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		Vector3 location;
		inInputStream.Read(location.mX);
		inInputStream.Read(location.mY);
		SetLocation(location);

		float rotation;
		inInputStream.Read(rotation);
		SetRotation(rotation);
	}


	inInputStream.Read(stateBit);
	if (stateBit)
	{
		Vector3 color;
		inInputStream.Read(color);
		SetColor(color);
	}
}

