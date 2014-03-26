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

		List<Ptr<GameComponent>>::iterator Begin();

		List<Ptr<GameComponent>>::iterator End();

	protected:

		List<Ptr<GameComponent>> Items;
	};

	//-------------------------------------------------------------------------------------------------
	inline void GameComponentCollection::Add(Ptr<GameComponent> component)
	{
		Items.push_back(component);
	}

	//-------------------------------------------------------------------------------------------------
	inline void GameComponentCollection::Clear()
	{
		Items.clear();
	}

	//-------------------------------------------------------------------------------------------------
	inline void GameComponentCollection::Remove(Ptr<GameComponent> component)
	{
		ASSERT(false, "Unimplemented");
		//Items.erase(component);
	}

	//-------------------------------------------------------------------------------------------------
	inline int GameComponentCollection::Count() const
	{
		return Items.size();
	}

	//-------------------------------------------------------------------------------------------------
	inline List<Ptr<GameComponent>>::iterator GameComponentCollection::Begin()
	{
		return Items.begin();
	}

	//-------------------------------------------------------------------------------------------------
	inline List<Ptr<GameComponent>>::iterator GameComponentCollection::End()
	{
		return Items.end();
	}
}