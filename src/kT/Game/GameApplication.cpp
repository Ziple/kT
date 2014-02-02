#include <kT/Game/GameApplication.hpp>
#include <kT/Game/GameComponent.hpp>

#include <algorithm>

namespace kT
{
	void KT_API GameApplication::Run()
	{
		// We reset the clock so that it works
		// albeit the initialization was too long.
		myClock.Reset();

		while( !myIsExited )
		{
            kT::Scalar time = kT::Scalar( myClock.GetTimeElapsedReset().AsSeconds() );
            Update( time );

            if( !SkipDrawing )
                Draw( time );
		}
	}

    void KT_API GameApplication::RemoveComponent( GameComponent* comp )
    {
        std::vector<kT::GameComponent*>::iterator it = std::find( myGamesComponents.begin(), myGamesComponents.end(), comp );
        if( it != myGamesComponents.end() )
            myGamesComponents.erase( it );
    }

	void KT_API GameApplication::Update( kT::Scalar dt )
	{
        for( std::vector<GameComponent*>::reverse_iterator it = myGamesComponents.rbegin();
            it != myGamesComponents.rend();
            it++ )
            if( (*it)->ActiveUpdate )
                (*it)->Update( dt );
	}

	void KT_API GameApplication::Draw( kT::Scalar dt )
	{
        for( std::vector<GameComponent*>::reverse_iterator it = myGamesComponents.rbegin();
            it != myGamesComponents.rend();
            it++ )
            if( (*it)->ActiveDraw )
                (*it)->Draw( dt );
	}

	void KT_API GameApplication::Exit()
	{
		myIsExited = true;
	}
}