#include <RoboCatClientPCH.h>

std::unique_ptr<sf::RenderWindow> SFWindowManager::sInstance;

bool SFWindowManager::StaticInit()
{
	sInstance.reset(new sf::RenderWindow(sf::VideoMode(800, 600), "Notline Miami!"));
	return true;
}