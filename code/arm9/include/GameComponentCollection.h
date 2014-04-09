#pragma once

#include "types.h"
// Have to include these because of the implicit casting
#include "GameComponent.h"
#include "DrawableGameComponent.h"

namespace Framework
{
	class GameComponentCollection
	{
	public:

		///
		virtual ~GameComponentCollection() { }

		///
		void Add(Ptr<GameComponent> component);

		///
		void Clear();

		/// 
		void Remove(Ptr<GameComponent> component);

		///
		int Count() const;

	public:

		Set<Ptr<GameComponent>>::iterator Begin();

		Set<Ptr<GameComponent>>::iterator End();

	protected:

		Set<Ptr<GameComponent>> Items;
	};

	//-------------------------------------------------------------------------------------------------
	inline void GameComponentCollection::Add(Ptr<GameComponent> component)
	{
		Items.insert(component);
	}

	//-------------------------------------------------------------------------------------------------
	inline void GameComponentCollection::Clear()
	{
		Items.clear();
	}

	//-------------------------------------------------------------------------------------------------
	inline void GameComponentCollection::Remove(Ptr<GameComponent> component)
	{
		Items.erase(component);
	}

	//-------------------------------------------------------------------------------------------------
	inline int GameComponentCollection::Count() const
	{
		return Items.size();
	}

	//-------------------------------------------------------------------------------------------------
	inline Set<Ptr<GameComponent>>::iterator GameComponentCollection::Begin()
	{
		return Items.begin();
	}

	//-------------------------------------------------------------------------------------------------
	inline Set<Ptr<GameComponent>>::iterator GameComponentCollection::End()
	{
		return Items.end();
	}
}