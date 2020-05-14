class BloodClient : public Blood
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new BloodClient()); }

protected:
	BloodClient();

private:
	SFSpriteComponentPtr m_sprite;
};