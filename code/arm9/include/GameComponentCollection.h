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
		virtual ~GameComponentCollection() = default;

		///
		void Add(GameComponent *component);

		///
		void Clear();

		/// 
		void Remove(GameComponent *component);

		///
		int Count() const;

	public:

		Set<GameComponent*>::iterator Begin();

		Set<GameComponent*>::iterator End();

	protected:

		Set<GameComponent*> Items;
	};

	//-------------------------------------------------------------------------------------------------
	inline void GameComponentCollection::Add(GameComponent *component)
	{
		Items.insert(component);
	}

	//-------------------------------------------------------------------------------------------------
	inline void GameComponentCollection::Clear()
	{
		Items.clear();
	}

	//-------------------------------------------------------------------------------------------------
	inline void GameComponentCollection::Remove(GameComponent *component)
	{
		Items.erase(component);
	}

	//-------------------------------------------------------------------------------------------------
	inline int GameComponentCollection::Count() const
	{
		return Items.size();
	}

	//-------------------------------------------------------------------------------------------------
	inline Set<GameComponent*>::iterator GameComponentCollection::Begin()
	{
		return Items.begin();
	}

	//-------------------------------------------------------------------------------------------------
	inline Set<GameComponent*>::iterator GameComponentCollection::End()
	{
		return Items.end();
	}
}