class RoboCat : public GameObject
{
public:
	CLASS_IDENTIFICATION( 'RCAT', GameObject )

	enum ECatReplicationState
	{
		ECRS_Pose = 1 << 0,
		ECRS_Color = 1 << 1,
		ECRS_PlayerId = 1 << 2,
		ECRS_Health = 1 << 3,
		ECRS_GunCount = 1 << 4,
		ECRS_ShootMode = 1 << 5,

		ECRS_AllState = ECRS_Pose | ECRS_Color | ECRS_PlayerId | ECRS_Health | ECRS_GunCount | ECRS_ShootMode
	};


	static	GameObject*	StaticCreate()			{ return new RoboCat(); }

	virtual uint32_t GetAllStateMask()	const override	{ return ECRS_AllState; }

	virtual	RoboCat*	GetAsCat()	{ return this; }

	virtual void Update()	override;

	void ProcessInput( float inDeltaTime, const InputState& inInputState );
	void SimulateMovement( float inDeltaTime );

	void ProcessCollisions();

	void		SetPlayerId( uint32_t inPlayerId )			{ mPlayerId = inPlayerId; }
	uint32_t	GetPlayerId()						const 	{ return mPlayerId; }

	void			SetVelocity( const Vector3& inVelocity )	{ mVelocity = inVelocity; }
	const Vector3&	GetVelocity()						const	{ return mVelocity; }

	uint8_t& GetHealth() { return mHealth; };
	uint8_t& GetGunCount() { return mGunCount; };
	uint8_t& GetShootMode() { return mShootMode; };
	void setShootMode(uint8_t newShootMode) { mShootMode = newShootMode; };

	virtual uint32_t	Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const override;

protected:
	RoboCat();

private:

	void TryMove(Vector3 p_move);


	void	AdjustVelocityByThrust( float inDeltaTime );

	Vector3				mVelocity;


	float				mMaxLinearSpeed;
	float				mMaxRotationSpeed;

	//bounce fraction when hitting various things
	float				mWallRestitution;
	float				mCatRestitution;


	uint32_t			mPlayerId;

protected:

	///move down here for padding reasons...
	
	float				mLastMoveTimestamp;

	sf::Vector2f		mThrustDir;
	uint8_t					mHealth;
	uint8_t					mGunCount;
	uint8_t				mShootMode;

	bool				mIsShooting;

	



};

typedef shared_ptr< RoboCat >	RoboCatPtr;