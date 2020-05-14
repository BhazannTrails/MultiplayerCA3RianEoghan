class Blood : public GameObject
{
public:
	CLASS_IDENTIFICATION('BLOD', GameObject)

		enum EBloodReplicationState
	{
		EBRS_Pose = 1 << 0,
		EBRS_Color = 1 << 1,

		EBRS_AllState = EBRS_Pose | EBRS_Color
	};

	static	GameObject*	StaticCreate() { return new Blood(); }

	virtual uint32_t	GetAllStateMask()	const override { return EBRS_AllState; }

	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;
	virtual void		Read(InputMemoryBitStream& inInputStream) override;

	//virtual bool HandleCollisionWithCat(RoboCat* inCat) override;

protected:
	Blood();
	bool picked;
}; 

typedef shared_ptr< Blood >	BloodPtr;
