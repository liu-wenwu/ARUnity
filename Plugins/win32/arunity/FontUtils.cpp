#include "stdafx.h"
#include "FontUtils.h"


FontUtils::FontUtils()
{

	FT_Error bError = FT_Init_FreeType(&library);
	if (bError != FT_Err_Ok)
	{

	}

	bError = FT_New_Face(library, "C:\\WINDOWS\\Fonts\\simhei.ttf", 0, &face);
	if (bError == FT_Err_Unknown_File_Format)
	{
		// 表示可以打开和读此文件，但不支持此字体格式
	}
	else if (bError)
	{
		// 其他错误
	}

	// 设定为UNICODE，默认也是
	FT_Select_Charmap(face, FT_ENCODING_UNICODE);
	// 设定字体字符宽高和分辨率
	bError = FT_Set_Char_Size(face, 10 << 6, 10 << 6, 200, 200);

}


FontUtils::~FontUtils()
{
}

std::wstring ANSIToUnicode(const std::string& str)
{
	int len = 0;
	len = str.length();
	int unicodeLen = ::MultiByteToWideChar(CP_ACP,
		0,
		str.c_str(),
		-1,
		NULL,
		0);
	wchar_t * pUnicode;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1)*sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP,
		0,
		str.c_str(),
		-1,
		(LPWSTR)pUnicode,
		unicodeLen);
	std::wstring rt;
	rt = (wchar_t*)pUnicode;
	delete pUnicode;
	return rt;
}



void FontUtils::putChar(cv::Mat & img, wchar_t onechar, cv::Point &point, const cv::Scalar &color)
{
	int fontX = point.x;
	int fontY = point.y;


	FT_Error bError;



	FT_UInt glyph_index = FT_Get_Char_Index(face, onechar);

	bError = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);


	if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
	{

		bError = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);


		unsigned char *imgData = face->glyph->bitmap.buffer;
		unsigned int imgWidth = face->glyph->bitmap.width;
		unsigned int imgHeight = face->glyph->bitmap.rows;

		uchar* image_ptr = img.data;
		int image_width = img.cols;
		int image_channels = img.channels();

		img.ptr<uchar>(0);

		for (int i = 0; i < imgHeight; ++i)
		{
			for (int j = 0; j < imgWidth; ++j)
			{
				int off = i * imgWidth + j;

				uchar* color_ptr = image_ptr + ((fontY + i + (40 - imgHeight))*image_width + fontX + j)*image_channels;

				if (face->glyph->bitmap.buffer[off]>0)
				{
					*color_ptr = color[0];

					if (image_channels >= 3)
					{

						*(color_ptr + 1) = color[1];
						*(color_ptr + 2) = color[2];
					}
				}
				else
				{
				}

			}

		}

		point.x += imgWidth;

	}

}



void FontUtils::putText(cv::Mat & img, const std::string text, const cv::Point &org, const cv::Scalar &color)
{

	cv::Point point = org;

	std::wstring  str = ANSIToUnicode(text);

	for (int i = 0; i < str.size(); ++i)
	{
		putChar(img, str[i], point, color);
		if (point.x>img.cols)
		{
			printf("---------------\n");
			point.x = org.x;
			point.y += 50;
		}

	}

}