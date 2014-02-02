#ifndef __KTEVENT_HPP__
#define __KTEVENT_HPP__

#include "Build.hpp"

#include <vector>
#include <list>
#include <algorithm>

namespace kT
{
	// Forward declaration.
	template< typename Event>
    class KT_API EventEmitter;

    /**
     * \ingroup ktgui_module
     * \brief Base class for classes that want to receive events from an emitter.
     */
	template< typename Event >
    class KT_API EventListener
    {
        public:

            /**
             * \brief Default virtual destructor.
             */
            virtual ~EventListener()
			{
				typename std::list< EventEmitter<Event>* >::iterator begin = myEmitters.begin(), end = myEmitters.end(), it;

				for ( it = begin; it != end; it++ )
					(*it)->RemoveListener( this );
			}

            /**
             * \brief Listens an emitter.
             */
            void Listen( EventEmitter<Event>* emitter )
			{
				emitter->AddListener( this );
				myEmitters.push_back( emitter );
			}

            /**
             * \brief Removes the connection to the emitter.
             */
            void DontListenAnymore( EventEmitter<Event>* emitter )
			{
				typename std::list< EventEmitter<Event>* >::iterator begin = myEmitters.begin(), end = myEmitters.end(), it = find( begin, end, emitter );

				if ( it != end )
				{
					myEmitters.erase( it );
					emitter->RemoveListener( this );
				}
			}

            /**
             * \brief Pure abstract function to override.
             */
            virtual void OnEvent( const EventEmitter<Event>* emitter, const Event* event ) = 0;

        private:

            /**
             * \brief Needed to removes at destruction time any reference to this.
             */
            std::list< EventEmitter<Event>* > myEmitters;
    };

	/**
     * \ingroup ktgui_module
     * \brief Base class for classes that want to send events.
     */
	template< typename Event >
    class KT_API EventEmitter
    {
        public:

            /**
             * \brief Adds a new listener.
             *
             * The listener will be noticed of the next sent events.
             */
            void AddListener( EventListener<Event>* listener )
			{
				myListeners.push_back( listener );
			}

            /**
             * \brief removes a listener.
             *
             * The listener won't be noticed of the sent events anymore.
             */
            void RemoveListener( EventListener<Event>* listener )
			{
				typename std::vector< EventListener<Event>* >::iterator it = std::find( myListeners.begin(), myListeners.end(), listener );

				if ( it != myListeners.end() )
					myListeners.erase( it );
			}

            /**
             * \brief Sends an event to the listeners.
             */
            void SendEvent( const Event* event )
			{
				for( typename std::vector< EventListener<Event>* >::iterator it = myListeners.begin(); it != myListeners.end(); it++ )
					(*it)->OnEvent( this, event );
			}

			const std::vector< EventListener<Event>* >& GetListeners() const {return myListeners;}

			std::vector< EventListener<Event>* >& GetListeners() {return myListeners;}

        protected:

            std::vector< EventListener<Event>* > myListeners;///< Listeners.
    };
}


#endif /* __KTEVENT_HPP__ */