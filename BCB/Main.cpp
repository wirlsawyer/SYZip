//---------------------------------------------------------------------------

#include <vcl.h>
#include <string>
#pragma hdrstop

#include "Main.h"
#include "zip.h"
#include "unzip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	std::wstring m_appPath = ExtractFilePath(Application->ExeName).c_str();
	//ZWZipCompress( (m_appPath+L"SYZip.exe").c_str(),  (m_appPath+L"Compress.Zip").c_str(), false );
	HZIP hz = CreateZip((m_appPath+L"Compress.Zip").c_str(), NULL);
	//ZipAdd(hz, L"SYZip.exe", (m_appPath+L"SYZip.exe").c_str());
	ZipAdd(hz, L"新文字文件.txt", (m_appPath+L"新文字文件.txt").c_str());

	CloseZip(hz);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	std::wstring m_appPath = ExtractFilePath(Application->ExeName).c_str();

	SetCurrentDirectory(m_appPath.c_str());
	HZIP hz = OpenZip((m_appPath+L"Compress.Zip").c_str(), NULL);
	ZIPENTRY ze;
	GetZipItem(hz,-1,&ze);
	int numitems = ze.index;
	for (int i=0; i<numitems; i++)
	{
		GetZipItem(hz,i,&ze);
		UnzipItem(hz,i,ze.name);
	}
	CloseZip(hz);
}
//---------------------------------------------------------------------------
