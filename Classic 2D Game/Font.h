#ifndef __ftgl__
#define __ftgl__

/* We need the Freetype headers */
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H

/* Floating point types used by the library */
typedef double   FTGL_DOUBLE;
typedef float    FTGL_FLOAT;

/* Macros used to declare C-linkage types and symbols */
#ifdef __cplusplus
#   define FTGL_BEGIN_C_DECLS extern "C" { namespace FTGL {
#   define FTGL_END_C_DECLS } }
#else
#   define FTGL_BEGIN_C_DECLS
#   define FTGL_END_C_DECLS
#endif

#ifdef __cplusplus
namespace FTGL
{
	typedef enum
	{
		RENDER_FRONT = 0x0001,
		RENDER_BACK = 0x0002,
		RENDER_SIDE = 0x0004,
		RENDER_ALL = 0xffff
	} RenderMode;

	typedef enum
	{
		ALIGN_LEFT = 0,
		ALIGN_CENTER = 1,
		ALIGN_RIGHT = 2,
		ALIGN_JUSTIFY = 3
	} TextAlignment;
}
#else
#   define FTGL_RENDER_FRONT 0x0001
#   define FTGL_RENDER_BACK  0x0002
#   define FTGL_RENDER_SIDE  0x0004
#   define FTGL_RENDER_ALL   0xffff

#   define FTGL_ALIGN_LEFT    0
#   define FTGL_ALIGN_CENTER  1
#   define FTGL_ALIGN_RIGHT   2
#   define FTGL_ALIGN_JUSTIFY 3
#endif

// Compiler-specific conditional compilation
#ifdef _MSC_VER // MS Visual C++

// Disable various warning.
// 4786: template name too long
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)
#pragma warning(disable : 4786)

// The following definitions control how symbols are exported.
// If the target is a static library ensure that FTGL_LIBRARY_STATIC
// is defined. If building a dynamic library (ie DLL) ensure the
// FTGL_LIBRARY macro is defined, as it will mark symbols for
// export. If compiling a project to _use_ the _dynamic_ library
// version of the library, no definition is required.
#ifdef FTGL_LIBRARY_STATIC      // static lib - no special export required
#  define FTGL_EXPORT
#elif FTGL_LIBRARY              // dynamic lib - must export/import symbols appropriately.
#  define FTGL_EXPORT   __declspec(dllexport)
#else
#  define FTGL_EXPORT   __declspec(dllimport)
#endif

#else
// Compiler that is not MS Visual C++.
// Ensure that the export symbol is defined (and blank)
#define FTGL_EXPORT
#endif

#include <ftgl/FTGL/FTPoint.h>
#include <ftgl/FTGL/FTBBox.h>
#include <ftgl/FTGL/FTBuffer.h>

#include <ftgl/FTGL/FTGlyph.h>
#include <ftgl/FTGL/FTBitmapGlyph.h>
#include <ftgl/FTGL/FTBufferGlyph.h>
#include <ftgl/FTGL/FTExtrdGlyph.h>
#include <ftgl/FTGL/FTOutlineGlyph.h>
#include <ftgl/FTGL/FTPixmapGlyph.h>
#include <ftgl/FTGL/FTPolyGlyph.h>
#include <ftgl/FTGL/FTTextureGlyph.h>

#include <ftgl/FTGL/FTFont.h>
#include <ftgl/FTGL/FTGLBitmapFont.h>
#include <ftgl/FTGL/FTBufferFont.h>
#include <ftgl/FTGL/FTGLExtrdFont.h>
#include <ftgl/FTGL/FTGLOutlineFont.h>
#include <ftgl/FTGL/FTGLPixmapFont.h>
#include <ftgl/FTGL/FTGLPolygonFont.h>
#include <ftgl/FTGL/FTGLTextureFont.h>

#include <ftgl/FTGL/FTLayout.h>
#include <ftgl/FTGL/FTSimpleLayout.h>

#endif  //  __ftgl__


#include <ftgl/FTGL/ftgl.h>
#include <glew.h>

class Text
{
public:
	Text(const char* fontpath,int size)
	{
		font = new FTExtrudeFont(fontpath);
		if (font->Error())
			fprintf(stderr, "Could not load font `%s'\n", fontpath);
		
		font->FaceSize(size);
		font->CharMap(ft_encoding_unicode);
	}

	~Text()
	{
		delete font;
	}

	void changeFontSize(int size)
	{
		font->FaceSize(size);
	}

	//Left down corner (x,y)
	void Render(const char* text,int x,int y)
	{
		glPushMatrix();
		glTranslatef(x, y, 0);
		glColor3ub(255, 255, 255);
		font->Render(text);
		glPopMatrix();
	}

private:
	FTFont *font;
};