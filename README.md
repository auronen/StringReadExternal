# Reading spell names
Gothic ZenGin has some quirks in the department of reading strings.

I do quite a lot of translations and recently I got sick of translating all spell names 3 times. Traditionally, the scripts need to have a string array called `TXT_SPELLS`, that contains names of the spells indexed by the spell index. Now, wouldn't it be great if you could just use these strings as names for runes and magic scrolls to save you the hassle of translating the same thing many times? Yes, yes it would.

This is a part of the array from G2A:

```c++
const string TXT_SPELLS[MAX_SPELL] =
{
	"Light",						// SPL_LIGHT			=	0;
	"Fire ball",					// SPL_FIREBALL			=	1;
	"Fear",							// SPL_FEAR				=	2;
	"Heal",							// SPL_HEAL				=	3;
//  and so on
// 	...
};
```
But in the spell item instance definitions you still have to either type out the name again, or specify a new set of `const string` name constants.
```c++
INSTANCE ItArRuneLight (C_Item)
{
	name 				=	NAME_Rune;

	mainflag 			=	ITEM_KAT_RUNE;
	flags 				=	0;

	value 				=	300;

	visual				=	"ItAr_Rune_42.3ds";
	material			=	MAT_STONE;

	spell				= 	SPL_LIGHT;
	mag_circle 			= 	1;

	description			=	"Light";
	
	TEXT	[0]			=	NAME_Mag_Circle;		COUNT	[0]		=	mag_circle;
	TEXT	[1]			=	NAME_Manakosten;		COUNT	[1]		=	SPL_SENDCAST_LIGHT;

	TEXT	[5]			=	NAME_Value;				COUNT	[5]		=	value;
};
```

There are ways how to do it, with [Ikarus](https://forum.worldofplayers.de/forum/threads/1299679-Skriptpaket-Ikarus-4) you can use `MEM_ReadStatStringArr (TXT_SPELLS, index);` to read a string from the array, that is, of course, superb, but the thing is Ikarus gets initialized on world startup and if you have these functions in spell item definitions, and those item instances are placed in the world, you get a empty string, since the function is not initialized yet.

So I wrote this quick and dirty external function, that fixes this.

# Usage
```c++
INSTANCE ItArRuneLight (C_Item)
{
	name 				=	NAME_Rune;

	mainflag 			=	ITEM_KAT_RUNE;
	flags 				=	0;

	value 				=	300;

	visual				=	"ItAr_Rune_42.3ds";
	material			=	MAT_STONE;

	spell				= 	SPL_LIGHT;
	mag_circle 			= 	1;

//	description			=	"Light";
	description			=	STR_GetSpellName(spell);

	
	TEXT	[0]			=	NAME_Mag_Circle;		COUNT	[0]		=	mag_circle;
	TEXT	[1]			=	NAME_Manakosten;		COUNT	[1]		=	SPL_SENDCAST_LIGHT;

	TEXT	[5]			=	NAME_Value;				COUNT	[5]		=	value;
};
```



