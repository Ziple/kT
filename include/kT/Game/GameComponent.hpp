#ifndef __KTGAMECOMPONENT_HPP__
#define __KTGAMECOMPONENT_HPP__

#include "../Core/Types.hpp"
#include "../Core/Clock.hpp"

namespace kT
{

	/**
	 * \brief Base class for game components.
	 */
	class KT_API GameComponent
	{
		public:

            /**
             * \brief Wether or not the component should be updated
             */
            bool ActiveUpdate;

            /**
             * \brief Wether or not the component should be drawn.
             */
            bool ActiveDraw;

            /**
             * \brief Constructor. Basically activate update and drawing.
             */
            GameComponent():
                ActiveUpdate( true ),
                ActiveDraw( true )
            {}

            virtual ~GameComponent() {}

			/**
			 * \brief Updates the game and the game components that must be updated.
			 * \param time Time elapsed since the last frame (in seconds).
			 */
            virtual void Update( kT::Scalar time ) = 0;

			/**
			 * \brief Draw the game on screen and the game components that must be.
			 * \param time Time elapsed since the last frame (in seconds).
			 */
			virtual void Draw( kT::Scalar time ) = 0;
	};
}

#endif