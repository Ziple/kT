/**
 * \file Core/Singleton.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 * \brief Contains the definition of the Singleton class.
 */
#ifndef __KTSINGLETON_HPP__
#define __KTSINGLETON_HPP__

#include "NonCopyable.hpp"

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Utility base class for singleton objects (just one instance).
     *
     * Just inherit from this class to get a singletonized-class so that
     * there just can be one object of this class at the time.
     */
    template< typename T >
    class Singleton: public NonCopyable
    {
        public:

            /**
             * \brief Returns a pointer to the instance.
             */
            static T* GetInstance();

            /**
             * \brief Releases the instance of the object.
             */
            static void Release();

        private:

            static T* instance;///< Instance.
    };

    template< typename T >
    T* Singleton< T >::instance = 0;

    template< typename T >
    T* Singleton< T >::GetInstance()
    {
        if ( instance == 0 )
        {
            instance = new T;
        }

        return instance;
    }

    template< typename T >
    void Singleton< T >::Release()
    {
        if ( instance )
        {
            delete instance;
            instance = 0;
        }
    }

    /**
     * \brief Utility macro letting the  Singleton class to create the instance.
     */
    #define KT_SINGLETON_DECLS( className ) friend className* Singleton<className>::GetInstance();\
                                               friend void Singleton<className>::Release();

}
#endif /* __KTSINGLETON_HPP__ */
