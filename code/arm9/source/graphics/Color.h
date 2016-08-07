/**
 * \class Color
 * \brief Represents a four-component color using red, green, blue, and alpha data.
 * \todo Implement setters for the ARGB components.
 */

#pragma once

#include "core/types.h"
#include "fixed.h"

namespace Framework
{
	struct Color
	{
	public:

		/** \brief Creates a new instance of the class. */
		Color();

		/** \brief Creates a new Color from a packed ARGB16 value. 
		 *  \param value A color as a packed ARGB16 value */
		Color(u16 value);

		/** \brief Gets the alpha component value. 
		 *  \returns The alpha component value of this color, range [0-1] */
		int A() const;

		/** \brief Gets the red component value of this Color. 
		 *  \returns The red component value of this color, range [0-31] */
		int R() const;

		/** \brief Gets the green component value of this Color. 
		 *  \returns The green component value of this color, range [0-31] */
		int G() const;

		/** \brief Gets the blue component value of this Color. 
		 *  \returns The blue component value of this color, range [0-31] */
		int B() const;

	public:

		/** \brief Convert this color to a unsigned 16bit integer
		 *  \returns The packed color */
		operator u16() const; 

	public:

		/** \brief Make a color from ARGB values 
		 *  \param a The alpha component, range [0-1]
		 *  \param r The red component, range [0-31]
		 *  \param g The green component, range [0-31] 
		 *  \param b The blue component, range [0-31] 
		 *  \returns The packed color */
		static u16 PackARGB16(int a, int r, int g, int b);

		/** \brief Make a color from continuous ARGB values, ranging from [0-1] 
		 *  \param red The red component, range [0-1]
		 *  \param green The green component, range [0-1] 
		 *  \param blue The blue component, range [0-1] 
		 *  \returns The resulting Color */
		static Color FromRGB(fx24 red, fx24 green, fx24 blue);
		
		/** \brief Make a color from ARGB values 
		 *  \param red The red component, range [0-255]
		 *  \param green The green component, range [0-255] 
		 *  \param blue The blue component, range [0-255] 
		 *  \returns The resulting Color */
		static Color FromRGB(byte red, byte green, byte blue);

	private:

		u16 value;

	public:

		// X11 / CSS3 Colors

		// Pink colors
		static const Color Pink;
		static const Color LightPink;
		static const Color HotPink;
		static const Color DeepPink;
		static const Color PaleVioletRed;
		static const Color MediumVioletRed;

		// Red colors
		static const Color LightSalmon;
		static const Color Salmon;
		static const Color DarkSalmon;
		static const Color LightCoral;
		static const Color IndianRed;
		static const Color Crimson;
		static const Color FireBrick;
		static const Color DarkRed;
		static const Color Red;

		// Orange colors
		static const Color OrangeRed;
		static const Color Tomato;
		static const Color Coral;
		static const Color DarkOrange;
		static const Color Orange;
		static const Color Gold;

		// Yellow colors
		static const Color Yellow;
		static const Color LightYellow;
		static const Color LemonChiffon;
		static const Color LightGoldenrodYellow;
		static const Color PapayaWhip;
		static const Color Moccasin;
		static const Color PeachPuff;
		static const Color PaleGoldenrod;
		static const Color Khaki;
		static const Color DarkKhaki;

		// Brown colors
		static const Color Cornsilk;
		static const Color BlanchedAlmond;
		static const Color Bisque;
		static const Color NavajoWhite;
		static const Color Wheat;
		static const Color BurlyWood;
		static const Color Tan;
		static const Color RosyBrown;
		static const Color SandyBrown;
		static const Color Goldenrod;
		static const Color DarkGoldenrod;
		static const Color Peru;
		static const Color Chocolate;
		static const Color SaddleBrown;
		static const Color Sienna;
		static const Color Brown;
		static const Color Maroon;

		// Green colors
		static const Color DarkOliveGreen;
		static const Color Olive;
		static const Color OliveDrab;
		static const Color YellowGreen;
		static const Color LimeGreen;
		static const Color Lime;
		static const Color LawnGreen;
		static const Color Chartreuse;
		static const Color GreenYellow;
		static const Color SpringGreen;
		static const Color MediumSpringGreen;
		static const Color LightGreen;
		static const Color PaleGreen;
		static const Color DarkSeaGreen;
		static const Color MediumSeaGreen;
		static const Color SeaGreen;
		static const Color ForestGreen;
		static const Color Green;
		static const Color DarkGreen;
		
		// Cyan colors
		static const Color MediumAquamarine;
		static const Color Aqua;
		static const Color Cyan;
		static const Color LightCyan;
		static const Color PaleTurquoise;
		static const Color Aquamarine;
		static const Color Turquoise;
		static const Color MediumTurquoise;
		static const Color DarkTurquoise;
		static const Color LightSeaGreen;
		static const Color CadetBlue;
		static const Color DarkCyan;
		static const Color Teal;

		// Blue colors
		static const Color LightSteelBlue;
		static const Color PowderBlue;
		static const Color LightBlue;
		static const Color SkyBlue;
		static const Color LightSkyBlue;
		static const Color DeepSkyBlue;
		static const Color DodgerBlue;
		static const Color CornflowerBlue;
		static const Color SteelBlue;
		static const Color RoyalBlue;
		static const Color Blue;
		static const Color MediumBlue;
		static const Color DarkBlue;
		static const Color Navy;
		static const Color MidnightBlue;

		// Purple colors
		static const Color Lavender;
		static const Color Thistle;
		static const Color Plum;
		static const Color Violet;
		static const Color Orchid;
		static const Color Fuchsia;
		static const Color Magenta;
		static const Color MediumOrchid;
		static const Color MediumPurple;
		static const Color BlueViolet;
		static const Color DarkViolet;
		static const Color DarkOrchid;
		static const Color DarkMagenta;
		static const Color Purple;
		static const Color Indigo;
		static const Color DarkSlateBlue;
		static const Color SlateBlue;
		static const Color MediumSlateBlue;

		// White colors
		static const Color White;
		static const Color Snow;
		static const Color Honeydew;
		static const Color MintCream;
		static const Color Azure;
		static const Color AliceBlue;
		static const Color GhostWhite;
		static const Color WhiteSmoke;
		static const Color Seashell;
		static const Color Beige;
		static const Color OldLace;
		static const Color FloralWhite;
		static const Color Ivory;
		static const Color AntiqueWhite;
		static const Color Linen;
		static const Color LavenderBlush;
		static const Color MistyRose;

		// Gray/Black colors
		static const Color Gainsboro;
		static const Color LightGray;
		static const Color Silver;
		static const Color DarkGray;
		static const Color Gray;
		static const Color DimGray;
		static const Color LightSlateGray;
		static const Color SlateGray;
		static const Color DarkSlateGray;
		static const Color Black;
	};

	//-------------------------------------------------------------------------------------------------
	inline Color::Color() : Color(0)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline Color::Color(u16 value) : value(value) 
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline int Color::A() const
	{
		return value >> 15;
	}

	//-------------------------------------------------------------------------------------------------
	inline int Color::R() const
	{
		return value & 0x1F; 
	}

	//-------------------------------------------------------------------------------------------------
	inline int Color::G() const
	{
		return (value >> 5 ) & 0x1F;
	}

	//-------------------------------------------------------------------------------------------------
	inline int Color::B() const
	{
		return (value >> 10) & 0x1F;
	}

	//-------------------------------------------------------------------------------------------------
	inline Color::operator u16() const
	{
		return value;
	}

	//-------------------------------------------------------------------------------------------------
	inline u16 Color::PackARGB16(int a, int r, int g, int b)
	{
		return (u16)( (a << 15) | r | (g << 5) | (b << 10));
	}

	//-------------------------------------------------------------------------------------------------
	inline Color Color::FromRGB(fx24 red, fx24 green, fx24 blue)
	{
		int a = 1;
		int r = (int)(red   * 31);
		int g = (int)(green * 31);
		int b = (int)(blue  * 31);

		u16 color = PackARGB16(a, r, g, b);

		return color;
	}

	//-------------------------------------------------------------------------------------------------
	inline Color Color::FromRGB(byte red, byte green, byte blue)
	{
		int a = 1;
		int r = red   * 31 / 255;
		int g = green * 31 / 255;
		int b = blue  * 31 / 255;

		u16 color = PackARGB16(a, r, g, b);

		return color;
	}
}