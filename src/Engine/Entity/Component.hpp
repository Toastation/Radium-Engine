#ifndef RADIUMENGINE_COMPONENT_HPP
#define RADIUMENGINE_COMPONENT_HPP

#include <Engine/RaEngine.hpp>

#include <Core/Math/LinearAlgebra.hpp>
#include <Core/Index/IndexedObject.hpp>

#include <Engine/Entity/EditableProperty.hpp>
#include <Engine/Renderer/RenderObject/RenderObjectManager.hpp>

namespace Ra
{
    namespace Engine
    {
        class System;
        class Entity;
        class RenderObjectManager;
    }
}

namespace Ra
{
    namespace Engine
    {

        /**
         * @brief A component is an element that can be updated by a system.
         * It is also linked to some other components in an entity.
         * Each component share a transform through their entity.
         */
        class RA_ENGINE_API Component : public EditableInterface
        {
        public:
            /// CONSTRUCTOR
            Component( const std::string& name );

            // FIXME (Charly) : Should destructor call something like
            //                  System::removeComponent(this) ?
            /// DESTRUCTOR
            virtual ~Component();

            /**
            * @brief Pure virtual method to be overridden by any component.
            * When this method is called you are guaranteed to know your system and your entity
            */
            virtual void initialize() = 0;
            /**
             * @brief Set entity the component is part of.
             * This method is called by the entity.
             * @param entity The entity the component is part of.
             */
            virtual void setEntity( Entity* entity );

            virtual Entity* getEntity() const;

            virtual const std::string& getName() const;

            virtual void setSystem( System* system );
            virtual System* getSystem() const;

            virtual void addRenderObjectToComponent( RenderObject* renderObject ) final;

            //
            // Editable interface.
            //

            // The base class provides a default implementation with no properties
            // (but maybe this is not the right thing and we should leave it as pure
            // virtual ?)

            /// Get a list of all editable properties.
            virtual void getProperties( Core::AlignedStdVector<EditableProperty>& propsOut ) const override {};

            /// Tell the component to take the new property value into account.
            virtual void setProperty( const EditableProperty& newProp ) override {};

        protected:
            /// Shortcut to access the render object manager.
            static RenderObjectManager* getRoMgr();

        protected:

            std::string m_name;
            Entity* m_entity;
            System* m_system;

            std::vector<Core::Index> m_renderObjects;

        };

    } // namespace Engine
} // namespace Ra

#include <Engine/Entity/Component.inl>

#endif // RADIUMENGINE_COMPONENT_HPP
