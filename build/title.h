
//{{BLOCK(title)

//======================================================================
//
//	title, 256x128@4, 
//	+ palette 256 entries, not compressed
//	+ bitmap not compressed
//	Total size: 512 + 16384 = 16896
//
//	Time-stamp: 2022-09-07, 22:02:55
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.1
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TITLE_H
#define GRIT_TITLE_H

#define titleBitmapLen 16384
extern const unsigned int titleBitmap[4096];

#define titlePalLen 512
extern const unsigned short titlePal[256];

#endif // GRIT_TITLE_H

//}}BLOCK(title)
