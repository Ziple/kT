#ifndef __KTGAMEAPPLICATION_HPP__
#define __KTGAMEAPPLICATION_HPP__

#include "../Core/Types.hpp"
#include "../Core/Clock.hpp"

#include <vector>

namespace kT
{
    class GameComponent;

	/**
	 * \brief Instance of the running game.
	 */
	class KT_API GameApplication
	{
		public:

            /**
             * \brief Wether or not the game should skip drawing.S
             */
            bool SkipDrawing;

			/**
			 * \brief Default constructor.
			 */
			GameApplication():
             myIsExited(false),
             SkipDrawing( false )
	        {
	        }

			/**
			 * \brief Destructor.
			 */
            virtual ~GameApplication() {}

			/**
			 * \brief Performs the game loop.
			 */
			void Run();

			/**
			 * \brief Makes the game exit by stopping the game loop.
			 */
			void Exit();

            /**
             * \brief Add a component to the list.
             */
            void AddComponent( GameComponent* comp )
            {
                myGamesComponents.push_back( comp );
            }

            /**
             * \brief Remove a component from the list.
             */
            void RemoveComponent( GameComponent* comp );

		private:

			bool myIsExited;//< The game stops when equal to true.
			Clock myClock;//< Clock used to provide the time information while updating/drawing.
            std::vector< GameComponent * > myGamesComponents;//< Currently registered game components.

			/**
			 * \brief Updates the game and the game components that must be updated.
			 * \param time Time elapsed since the last frame (in seconds).
			 */
            virtual void Update( kT::Scalar time );

			/**
			 * \brief Draw the game on screen and the game components that must be.
			 * \param time Time elapsed since the last frame (in seconds).
			 */
			virtual void Draw( kT::Scalar time );
	};
}

#endif