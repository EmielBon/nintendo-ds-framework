#pragma once

#include "core/types.h"
#include "graphics/TextRenderer.h"

namespace System
{
	class Console : public Graphics::TextRenderer
	{
	private:

		using super = Graphics::TextRenderer;

	public:

		/// 
		Console(Graphics::Background *background);
		
		/// 
		void Update(const Framework::GameTime &gameTime);

		/// 
		void Draw(const Framework::GameTime &gameTime);

		/// 
		void WriteLine(const String& entry);

		/// 
		void Write(const String& entry);

		/// 
		void Clear();

		///
		void Redraw();

		///
		int EntryCount() const;

	protected:

		List<String> entries;

	private:

		int startEntry;
	};

	//-------------------------------------------------------------------------------------------------
	inline void Console::WriteLine(const String &entry)
	{
		entries.push_back(entry);
		Redraw();
	}

	//-------------------------------------------------------------------------------------------------
	inline void Console::Write(const String &entry)
	{
		entries.back() += entry;
		Redraw();
	}

	//-------------------------------------------------------------------------------------------------
	inline void Console::Clear()
	{
		entries.clear();
	}

	//-------------------------------------------------------------------------------------------------
	inline void Console::Redraw()
	{
		startEntry = -1;
	}
	
	//-------------------------------------------------------------------------------------------------
	inline int Console::EntryCount() const
	{
		return entries.size();
	}
}