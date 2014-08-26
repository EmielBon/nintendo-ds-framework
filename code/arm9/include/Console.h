#pragma once

#include "types.h"
#include "TextRenderer.h"

namespace System
{
	class Console : public Graphics::TextRenderer
	{
	private:

		using super = Graphics::TextRenderer;

	public:

		/// 
		Console(Ptr<Graphics::Background> background, int x, int y, int width, int height);
		
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
		int X, Y, Width, Height;

	private:

		bool redraw;
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
		redraw = true;
	}
	
	//-------------------------------------------------------------------------------------------------
	inline int Console::EntryCount() const
	{
		return entries.size();
	}
}