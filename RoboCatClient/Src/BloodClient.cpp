#include <RoboCatClientPCH.h>

BloodClient::BloodClient()
{
	m_sprite.reset(new SFSpriteComponent(this));
	m_sprite->SetTexture(SFTextureManager::sInstance->GetTexture("ResizedBlood"));


}