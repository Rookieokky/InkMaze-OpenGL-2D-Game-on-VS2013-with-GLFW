// RGBpixmap.cpp - routines to read a BMP file
#include "RGBpixmap.h"
typedef unsigned short ushort;
typedef unsigned long ulong;

//<<<<<<<<<<<<<<<<<<<<< getShort >>>>>>>>>>>>>>>>>>>>
inline ushort getShort(fstream &inf) //helper function
{ //BMP format uses little-endian integer types
	// get a 2-byte integer stored in little-endian form
	char ic;
	ushort ip;
	inf.get(ic); ip = ic;  //first byte is little one 
	inf.get(ic);  ip |= ((ushort)ic << 8); // or in high order byte

	return ip;
}
//<<<<<<<<<<<<<<<<<<<< getLong >>>>>>>>>>>>>>>>>>>
ulong getLong(fstream &inf) //helper function
{  //BMP format uses little-endian integer types
	// get a 4-byte integer stored in little-endian form
	ulong ip = 0;
	char ic = 0;
	unsigned char uc = ic;
	inf.get(ic); uc = ic; ip = uc;
	inf.get(ic); uc = ic; ip |= ((ulong)uc << 8);
	inf.get(ic); uc = ic; ip |= ((ulong)uc << 16);
	inf.get(ic); uc = ic; ip |= ((ulong)uc << 24);

	return ip;
}


/* --------------------------------------------------------------------
RGBAPixmap:
-------------------------------------------------------------------- */

bool RGBApixmap::loadTexture(string filename){
	/*
	BMP files [reading, writing]
	Dr. Halo CUT files [reading] *
	DDS files [reading]
	EXR files [reading, writing]
	Raw Fax G3 files [reading]
	GIF files [reading, writing]
	HDR files [reading, writing]
	ICO files [reading, writing]
	IFF files [reading]
	JBIG files [reading, writing] **
	JNG files [reading, writing]
	JPEG/JIF files [reading, writing]
	JPEG-2000 File Format [reading, writing]
	JPEG-2000 codestream [reading, writing]
	JPEG-XR files [reading, writing]
	KOALA files [reading]
	Kodak PhotoCD files [reading]
	MNG files [reading]
	PCX files [reading]
	PBM/PGM/PPM files [reading, writing]
	PFM files [reading, writing]
	PNG files [reading, writing]
	Macintosh PICT files [reading]
	Photoshop PSD files [reading]
	RAW camera files [reading]
	Sun RAS files [reading]
	SGI files [reading]
	TARGA files [reading, writing]
	TIFF files [reading, writing]
	WBMP files [reading, writing]
	WebP files [reading, writing]
	XBM files [reading]
	XPM files [reading, writing]

	* only grayscale
	** only via external plugin, might require a commercial license
	*/
	FreeImage_Initialise();
	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(filename.c_str(), 0);//Automatocally detects the format(from over 20 formats!)
	FIBITMAP* imagen = FreeImage_Load(formato, filename.c_str());

	FIBITMAP* temp = imagen;
	imagen = FreeImage_ConvertTo32Bits(imagen);
	FreeImage_Unload(temp);

	nCols = FreeImage_GetWidth(imagen);
	nRows = FreeImage_GetHeight(imagen);
	//cout << "The size of the image is: " << filename << " es " << w << "*" << h << endl; //Some debugging code

	//textura = new GLubyte[4 * nCols*nRows];
	char* pixeles = (char*)FreeImage_GetBits(imagen);
	//FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR).
	pixel = new mRGBA[nCols*nRows];

	for (int j = 0; j<nCols*nRows; j++){
		pixel[j].r = pixeles[j * 4 + 2];
		pixel[j].g = pixeles[j * 4 + 1];
		pixel[j].b = pixeles[j * 4 + 0];
		pixel[j].a = pixeles[j * 4 + 3];
	}

	needUpdateTex = true;
	return true;

}