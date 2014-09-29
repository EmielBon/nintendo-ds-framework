#pragma once

#include "types.h"

namespace Graphics
{
	class IndexBuffer
	{
	public:

		const List<u16>& GetData() const;

		void SetData(const List<u16> &indices);

		void SetData(short *begin, short *end);

		// todo: rename to Count
		int IndexCount() const;

		u16& operator[](u32 index);

		const u16& operator[](u32 index) const;

	private:

		List<u16> data;
	};

	//-------------------------------------------------------------------------------------------------
	inline const List<u16>& IndexBuffer::GetData() const
	{
		return data;
	}

	//-------------------------------------------------------------------------------------------------
	inline void IndexBuffer::SetData(const List<u16> &indices)
	{
		data.assign(indices.begin(), indices.end());
	}

	//-------------------------------------------------------------------------------------------------
	inline void IndexBuffer::SetData(short *begin, short* end)
	{
		data.assign(begin, end);
	}

	//-------------------------------------------------------------------------------------------------
	inline int IndexBuffer::IndexCount() const
	{
		return data.size();
	}

	//-------------------------------------------------------------------------------------------------
	inline u16& IndexBuffer::operator[](u32 index)
	{
		return data[index];
	}

	//-------------------------------------------------------------------------------------------------
	inline const u16& IndexBuffer::operator[](u32 index) const
	{
		return data[index];
	}
}