#include <RoboCatServerPCH.h>

RoboCatServer::RoboCatServer() :
	mCatControlType( ESCT_Human ),
	mTimeOfNextShot( 0.f ),
	mTimeBetweenShots( 0.2f )
{}

void RoboCatServer::HandleDying()
{
	GameObjectPtr bl;
	BloodPtr blood = std::static_pointer_cast<Blood>(GameObjectRegistry::sInstance->CreateGameObject('BLOD'));
	blood->SetLocation(this->GetLocation());
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
	
	//Old Implementation
	//bl = GameObjectRegistr::sInstance->CreateGameObject('BLOD');
	//bl->SetLocation(this->GetLocation());
}

void RoboCatServer::Update()
{
	RoboCat::Update();
	
	Vector3 oldLocation = GetLocation();
	Vector3 oldVelocity = GetVelocity();
	float oldRotation = GetRotation();

	//are you controlled by a player?
	//if so, is there a move we haven't processed yet?
	if( mCatControlType == ESCT_Human )
	{
		ClientProxyPtr client = NetworkManagerServer::sInstance->GetClientProxy( GetPlayerId() );
		if( client )
		{
			MoveList& moveList = client->GetUnprocessedMoveList();
			for( const Move& unprocessedMove : moveList )
			{
				const InputState& currentState = unprocessedMove.GetInputState();

				float deltaTime = unprocessedMove.GetDeltaTime();

				ProcessInput( deltaTime, currentState );
				SimulateMovement( deltaTime );

				//LOG( "Server Move Time: %3.4f deltaTime: %3.4f left rot at %3.4f", unprocessedMove.GetTimestamp(), deltaTime, GetRotation() );

			}

			moveList.Clear();
		}
	}
	else
	{
		//do some AI stuff
		SimulateMovement( Timing::sInstance.GetDeltaTime() );
	}

	

		HandleShooting();
	

	if( !RoboMath::Is2DVectorEqual( oldLocation, GetLocation() ) ||
		!RoboMath::Is2DVectorEqual( oldVelocity, GetVelocity() ) ||
		oldRotation != GetRotation() )
	{
		NetworkManagerServer::sInstance->SetStateDirty( GetNetworkId(), ECRS_Pose );
	}

}

void RoboCatServer::HandleShooting()
{

	if (RoboCat::GetGunCount() > 0)
	{
		float time = Timing::sInstance.GetFrameStartTime();
		//Eoghan
		if (mIsShooting && Timing::sInstance.GetFrameStartTime() > mTimeOfNextShot)
		{
			//not exact, but okay
			mTimeOfNextShot = time + mTimeBetweenShots;

			//fire!

			YarnPtr yarn = std::static_pointer_cast<Yarn>(GameObjectRegistry::sInstance->CreateGameObject('YARN'));
			yarn->InitFromShooter(this);

			if (RoboCat::GetShootMode() == 2) {
				
				YarnPtr yarn2 = std::static_pointer_cast<Yarn>(GameObjectRegistry::sInstance->CreateGameObject('YARN'));
				yarn2->InitFromShooterShootMode2(this);

			}

			if (RoboCat::GetShootMode() == 3) {

				YarnPtr yarn2 = std::static_pointer_cast<Yarn>(GameObjectRegistry::sInstance->CreateGameObject('YARN'));
				yarn2->InitFromShooterShootMode2(this);
			
				YarnPtr yarn3 = std::static_pointer_cast<Yarn>(GameObjectRegistry::sInstance->CreateGameObject('YARN'));
				yarn3->InitFromShooterShootMode2B(this);
			}

			RoboCat::GetGunCount()--;

		}
	}
}

void RoboCatServer::TakeDamage( int inDamagingPlayerId )
{
	mHealth--;
	if( mHealth <= 0.f )
	{
		//score one for damaging player...
		ScoreBoardManager::sInstance->IncScore( inDamagingPlayerId, 1 );

		//and you want to die
		SetDoesWantToDie( true );

		//tell the client proxy to make you a new cat
		ClientProxyPtr clientProxy = NetworkManagerServer::sInstance->GetClientProxy( GetPlayerId() );
		if( clientProxy )
		{
			clientProxy->HandleCatDied();
		}
	}

	//tell the world our health dropped
	NetworkManagerServer::sInstance->SetStateDirty( GetNetworkId(), ECRS_Health );
}
