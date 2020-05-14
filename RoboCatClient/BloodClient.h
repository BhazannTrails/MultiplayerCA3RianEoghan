class BloodClient : public Blood
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new MouseClient()); }

protected:
	BloodClient();

private:
	SFSpriteComponentPtr m_sprite;
}; 
