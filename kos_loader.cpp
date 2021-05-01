#define _CRT_SECURE_NO_WARNINGS
//#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include "WindowsToLinuxDefine.h"
#include "glMath.h"
#include "kos_loader.h"
//#include <codecvt>
#include "utf8.h"
#include <ctime>


#ifndef _MSC_VER
void strcpy_s(char* des, int src_len, const char* src)
{
	strcpy(des, src);
}
#endif



int WideCharToMultiByte(int codePage,
	int dwFlags,
	wchar_t* wstr,
	int wstr_size,
	char** str,
	int str_size,
	void* p1,
	void* p2
)
{
	wstring wstring(wstr);
	vector<char> utf8result;

	utf8::utf16to8(wstring.begin(), wstring.end(), back_inserter(utf8result));
	int len = utf8result.size();

	if (str != NULL)
	{
		*str = new char[len + 1];
		for (int i = 0; i < len; ++i)
			(*str)[i] = utf8result.at(i);
		(*str)[len] = '\0';
	}

	return len;
	//// convert ����
	//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> con;

	//// byte�� ��ȯ
	//std::string strtmp = con.to_bytes(wstr);
	//int len = strtmp.length();
	//if (str != NULL)
	//{
	//	*str = new char[len];
	//	strcpy(*str, strtmp.c_str());
	//}

	//return len;

}

int MultiByteToWideChar(int codePage,
	int dwFlags,
	const char* str,
	int str_size,
	wchar_t** wstr,
	int wstr_size
)
{
	size_t ret_size = 0;
	if (str_size == -1)
		str_size = MAX_CODEPAGE_CONVERT_LENGTH;

	wchar_t wstr_tmp[MAX_CODEPAGE_CONVERT_LENGTH];
	wstr_size = sizeof(wstr_tmp);
	setlocale(LC_ALL, "Korean");//������ ����
	ret_size = mbstowcs(wstr_tmp, str, str_size);

	if (wstr != NULL)
	{
		*wstr = new wchar_t[ret_size];
		wcscpy(*wstr, wstr_tmp);

	}

	return ret_size;
}

#define MAX_LINE_KOS 10000000

typedef struct _Point {
	double x;
	double y;
} kPoint;

kPoint RotateCoordinate(kPoint p, double theta, kPoint base) {
	kPoint ret;

	ret.x = (p.x - base.x) * cos(theta * Pi / 180) - (p.y - base.y) * sin(theta * Pi / 180) + base.x;
	ret.y = (p.x - base.x) * sin(theta * Pi / 180) + (p.y - base.y) * cos(theta * Pi / 180) + base.y;

	return ret;
}
kPoint MultiCoordinate(kPoint p, double theta) {
	kPoint ret;

	ret.x = p.x * theta;
	ret.y = p.y * theta;

	return ret;
}
kPoint AddCoordinate(kPoint p1, kPoint p2) {
	kPoint ret;

	ret.x = p1.x + p2.x;
	ret.y = p1.y + p2.y;

	return ret;
}
float CalAngleXbase(float xx, float yy) {




	return atan2f(yy, xx) / Pi * 180.0f;
}
// ���� ���� �ʿ�


void kos_loader::XmlPropertyExport()
{
	TiXmlDocument doc;
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "UTF-8", "");
	doc.LinkEndChild(pDecl);


	TiXmlElement* pnode1;
	TiXmlElement* pnode2;
	TiXmlElement* pnode3;


	pnode1 = new TiXmlElement("Drawing_administration_information");
	doc.LinkEndChild(pnode1);
	pnode2 = new TiXmlElement("Project_Information");
	for (int ii = 0; ii < m_PIarr.size(); ii++)
	{
		pnode3 = new TiXmlElement("Data1");
		//CString  sss = m_PIarr[ii].c_str();
		//sss += "\0";
		pnode3->LinkEndChild(new TiXmlText(MultiByte2utfs8(m_PIarr[ii].c_str())));
		pnode2->LinkEndChild(pnode3);
	}
	pnode1->LinkEndChild(pnode2);


	pnode2 = new TiXmlElement("Project_Additional_Information");
	for (int ii = 0; ii < m_PAarr.size(); ii++)
	{
		pnode3 = new TiXmlElement("Data2");
		pnode3->LinkEndChild(new TiXmlText(MultiByte2utfs8(m_PAarr[ii].c_str())));
		pnode2->LinkEndChild(pnode3);
	}
	pnode1->LinkEndChild(pnode2);


	pnode2 = new TiXmlElement("Employer_Information");
	for (int ii = 0; ii < m_EIarr.size(); ii++)
	{
		pnode3 = new TiXmlElement("Data3");
		pnode3->LinkEndChild(new TiXmlText(MultiByte2utfs8(m_EIarr[ii].c_str())));
		pnode2->LinkEndChild(pnode3);
	}
	pnode1->LinkEndChild(pnode2);


	pnode2 = new TiXmlElement("Contractor_Information");
	for (int ii = 0; ii < m_CIarr.size(); ii++)
	{
		pnode3 = new TiXmlElement("Data4");
		pnode3->LinkEndChild(new TiXmlText(MultiByte2utfs8(m_CIarr[ii].c_str())));
		pnode2->LinkEndChild(pnode3);
	}
	pnode1->LinkEndChild(pnode2);


	pnode2 = new TiXmlElement("Drawing_Preview_Information");
	for (int ii = 0; ii < m_DParr.size(); ii++)
	{
		pnode3 = new TiXmlElement("Data5");
		pnode3->LinkEndChild(new TiXmlText(MultiByte2utfs8(m_DParr[ii].c_str())));
		pnode2->LinkEndChild(pnode3);
	}
	pnode1->LinkEndChild(pnode2);


	pnode2 = new TiXmlElement("Drawing_Index_Information");
	for (int ii = 0; ii < m_DIarr.size(); ii++)
	{
		pnode3 = new TiXmlElement("Data6");
		pnode3->LinkEndChild(new TiXmlText(MultiByte2utfs8(m_DIarr[ii].c_str())));
		pnode2->LinkEndChild(pnode3);
	}
	pnode1->LinkEndChild(pnode2);


	pnode2 = new TiXmlElement("Drawing_Additional_Information");
	for (int ii = 0; ii < m_DAarr.size(); ii++)
	{
		pnode3 = new TiXmlElement("Data7");
		pnode3->LinkEndChild(new TiXmlText(MultiByte2utfs8(m_DAarr[ii].c_str())));
		pnode2->LinkEndChild(pnode3);
	}
	pnode1->LinkEndChild(pnode2);


	pnode2 = new TiXmlElement("Drawing_Change_Information");
	for (int ii = 0; ii < m_DCarr.size(); ii++)
	{
		pnode3 = new TiXmlElement("Data8");
		pnode3->LinkEndChild(new TiXmlText(MultiByte2utfs8(m_DCarr[ii].c_str())));
		pnode2->LinkEndChild(pnode3);
	}
	pnode1->LinkEndChild(pnode2);


	pnode2 = new TiXmlElement("Facility_Information");
	for (int ii = 0; ii < m_FIarr.size(); ii++)
	{
		pnode3 = new TiXmlElement("Data9");
		pnode3->LinkEndChild(new TiXmlText(MultiByte2utfs8(m_FIarr[ii].c_str())));
		pnode2->LinkEndChild(pnode3);
	}
	pnode1->LinkEndChild(pnode2);


	pnode2 = new TiXmlElement("User_Defined_Information");
	for (int ii = 0; ii < m_UDarr.size(); ii++)
	{
		pnode3 = new TiXmlElement("Data0");
		pnode3->LinkEndChild(new TiXmlText(MultiByte2utfs8(m_UDarr[ii].c_str())));
		pnode2->LinkEndChild(pnode3);
	}
	pnode1->LinkEndChild(pnode2);

	doc.SaveFile(m_FileNameOnly + ".xml");


}
// ��Ʈ���� �����ڷ� ������ �Լ�
int Split(CString Source, CString Ret[], char Discre)
{
	int OldPos = 0, rcnt = 0;
	int i;
	for (i = 0; i < Source.GetLength(); i++) {
		if (Source.GetAt(i) == Discre) {
			Ret[rcnt++] = Source.Mid(OldPos, i - OldPos);
			OldPos = i + 1;
		}
	}
	if (i == 0)
		return 0;
	Ret[rcnt++] = Source.Mid(OldPos, i - OldPos);

	return rcnt;
}

// ��Ʈ���� �����ڷ� ��� ��������� �� Ȯ���ϴ� �Լ�
int Counting(CString Source, char Discre)
{
	if (1 >= Source.GetLength())
		return 0;


	int rcnt = 0;

	for (int i = 0; i < Source.GetLength(); i++) {
		if (Source.GetAt(i) == Discre) {
			rcnt++;
		}
	}

	return rcnt + 1;
}
//
long getStrNumInt(char* aaaa)
{
	char* bbbb = aaaa;
	long ii = -1;
	long dd = 0;

	while (1) {
		if (bbbb[dd] == ' ' || bbbb[dd] == '#') {
			dd++;
		}
		else {
			ii = (long)(atoi(&(bbbb[dd])));
			break;
		}
	}
	return ii;
}

char* timeToString(struct tm* t) {
	static char s[20];

	sprintf(s, "%04d-%02d-%02d %02d:%02d:%02d",
		t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
		t->tm_hour, t->tm_min, t->tm_sec
	);

	return s;
}

kos_loader::kos_loader()
{

	m_pBuffer = NULL;
	m_IndexBuffer = 0;
	//m_hMem = HeapCreate(0, 0, 0);
}

kos_loader::~kos_loader()
{
	if (m_pBuffer != NULL)
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}
}

int kos_loader::Run(CString filename, CString pathonly, CString filename_only)
{
#ifdef _MSC_VER
	CString FileNameOnly = pathonly + "\\" + filename_only;
#else
	CString FileNameOnly = pathonly + "/" + filename_only;
#endif
	clock_t startTime, endTime;
	startTime = clock();
	TRACE("ok\n");

	cnt_TEXT = 0;
	cnt_COMPOSITE_CURVE = 0;
	cnt_TRIMMED_CURVE = 0;
	cnt_ELLIPSE = 0;
	cnt_CIRCLE = 0;
	cnt_POLYLINE = 0;

	int nRetVal = 0;

	TRACE("if (!ReadFile(filename))\n");
	if (!ReadFile(filename))
	{
		TRACE("return -1;\n");
		return -1;
	}

	m_FileNameOnly = FileNameOnly;
	//AfxMessageBox("ReadFile ok");

	m_pBufferLine = new char[MAX_LINE_KOS];
	if (NULL == m_pBufferLine)
	{
		return -1;
	}

	TRACE("if (!CheckVersion())\n");
	if (!CheckVersion())
		return -2;

	//XmlPropertyExport();

	if (!CountDef())
		return -1;
	TRACE("CountDef ok\n");


	float* screendata = getPresentation_view(Presentation_view);


	m_doc = new TiXmlDocument();

	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "UTF-8", "");
	m_doc->LinkEndChild(pDecl);

	m_pnode1 = new TiXmlElement("svg");
	m_pnode1->SetAttribute("xmlns", "http://www.w3.org/2000/svg");

	//CString buf00;
	//buf00.Format("%f %f %f %f", screendata[2], screendata[3], screendata[0], screendata[1]);
	//m_pnode1->SetAttribute("viewbox", buf00);

	if (screendata[2] < -90000000 || screendata[2] > 90000000)
		screendata[2] = 0;
	if (screendata[3] < -90000000 || screendata[3] > 90000000)
		screendata[3] = 0;

	m_doc->LinkEndChild(m_pnode1);

	CString buf1;
	CString buf2;

	buf1.Format("%f", screendata[2] * -1.0f);
	buf2.Format("%f", screendata[3] * -1.0f * -1.0f);

	TiXmlElement* node00 = NULL;


	node00 = new TiXmlElement("g");
	node00->SetAttribute("transform", "translate(" + buf1 + "," + buf2 + ")");
	m_pnode1->LinkEndChild(node00);



	m_pnode2 = new TiXmlElement("g");
	m_pnode2->SetAttribute("id", "line_layer");
	m_pnode2->SetAttribute("transform", "translate(0,0)");
	//m_pnode2->SetAttribute("fill", "blue");
	node00->LinkEndChild(m_pnode2);

	m_pnode_Text = new TiXmlElement("g");
	m_pnode_Text->SetAttribute("id", "text_layer");
	m_pnode_Text->SetAttribute("transform", "translate(0,0)");
	//m_pnode2->SetAttribute("fill", "blue");
	node00->LinkEndChild(m_pnode_Text);










	cnt_PRESENTATION_STYLE_ASSIGNMENT = 0;


	//
	Placement* tmpplace = new Placement();
	TempLine_width = 0;

	SubLevel_item(Presentation_size, 0, m_pnode2, tmpplace, 0);

	SubLevel(Presentation_size, 0, m_pnode2, tmpplace, 0);
	SubLeveltext(Presentation_size, 0, m_pnode_Text, tmpplace, 0);
	//int tmp = -1;
	//multimap<long, long>::iterator iter;
	//for (iter = DRAUGHTING_CALLOUT_RELATIONSHIP.begin(); iter != DRAUGHTING_CALLOUT_RELATIONSHIP.end(); ++iter)
	//{
	//	SubLevel(iter->first, 0, m_pnode2, tmpplace, 0);
	//	SubLevel(iter->second, 0, m_pnode2, tmpplace, 0);
	//}

	//get_layer();
	/*

	map<long, kos_Polyline*>::iterator itormapPolyline;
	for (itormapPolyline = Polyline_List.begin(); itormapPolyline != Polyline_List.end(); ++itormapPolyline)
	{
		kos_Polyline* tmpgeo = itormapPolyline->second;
	//	if (tmpgeo->checkflag != 2)
		if (tmpgeo->checkflag > 3)
			continue;
		CString buf1;
		CString buf2;
		TiXmlElement* nownode0;

		buf1.Format("%f", tmpgeo->transform[0]);
		buf2.Format("%f", tmpgeo->transform[1] * -1.0f);
		TiXmlElement* node01 = new TiXmlElement("g");
		node01->SetAttribute("transform", "translate(" + buf1 + "," + buf2 + ")");
		m_pnode2->LinkEndChild(node01);

		nownode0 = node01;

		TiXmlElement* node02 = new TiXmlElement("g");
		float fff = tmpgeo->transform[2];
		buf1.Format("rotate(%f)", fff);
		node02->SetAttribute("transform", buf1);
		nownode0->LinkEndChild(node02);
		nownode0 = node02;

		TiXmlElement* node03 = new TiXmlElement("g");
		buf1.Format("scale(%f,%f)", tmpgeo->transform[3], tmpgeo->transform[4]);
		node03->SetAttribute("transform", buf1);
		nownode0->LinkEndChild(node03);
		nownode0 = node03;


		CString tmps = "";
		CString tmps1 = "";
		CString tmps2 = "";
		CString tmps3 = "";

		for (int iia = 0; iia < tmpgeo->Vertex.size(); iia += 2) {
			if (iia == 0)
				tmps1.Format("%f,%f", tmpgeo->Vertex[iia], tmpgeo->Vertex[iia + 1] * -1.0f);
			else
				tmps1.Format(" %f,%f", tmpgeo->Vertex[iia], tmpgeo->Vertex[iia + 1] * -1.0f);
			tmps = tmps + tmps1;
		}

		TiXmlElement* node04 = new TiXmlElement("polyline ");
		node04->SetAttribute("points", tmps);

		tmps2.Format("rgb(%d,%d,%d)", (int)(tmpgeo->Line_colour[0] * 255), (int)(tmpgeo->Line_colour[1] * 255), (int)(tmpgeo->Line_colour[2] * 255));
		tmps3.Format("%f", (tmpgeo->width)*10.0 + 1);
		// <polygon id = "s1" points = "60,0 120,0 180,60 180,120 120,180 60,180 0,120 0,60" fill = "none" stroke = "black" stroke-width = "3"/>
		node04->SetAttribute("fill", "none");
		node04->SetAttribute("stroke", tmps2);
		node04->SetAttribute("stroke-width", tmps3);
		node04->SetAttribute("vector-effect", "non-scaling-stroke");

		//CString tmps4 = "";
		//CString tmps5 = "";
		//for (int iia = 0; iia < tmpgeo->line_type_Segment; iia += 2) {
		//	if (iia == 0)
		//		tmps4.Format("%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
		//	else
		//		tmps4.Format(",%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
		//	tmps5 = tmps5 + tmps4;
		//}
		//if (tmpgeo->line_type_Pitch[0] != 0)
		//	node04->SetAttribute("stroke-dasharray", tmps5);
		nownode0->LinkEndChild(node04);


	}

	map<long, kos_Circle*>::iterator itormapCircle;
	for (itormapCircle = Circle_List.begin(); itormapCircle != Circle_List.end(); ++itormapCircle)
	{
		kos_Circle* tmpgeo = itormapCircle->second;
		if (tmpgeo->checkflag != 3)
			continue;
		CString buf1;
		CString buf2;
		TiXmlElement* nownode0;

		buf1.Format("%f", tmpgeo->transform[0]);
		buf2.Format("%f", tmpgeo->transform[1] * -1.0f);
		TiXmlElement* node01 = new TiXmlElement("g");
		node01->SetAttribute("transform", "translate(" + buf1 + "," + buf2 + ")");
		m_pnode2->LinkEndChild(node01);

		nownode0 = node01;

		TiXmlElement* node02 = new TiXmlElement("g");
		float fff = tmpgeo->transform[2];
		buf1.Format("rotate(%f)", fff);
		node02->SetAttribute("transform", buf1);
		nownode0->LinkEndChild(node02);
		nownode0 = node02;

		TiXmlElement* node03 = new TiXmlElement("g");
		buf1.Format("scale(%f,%f)", tmpgeo->transform[3], tmpgeo->transform[4]);
		node03->SetAttribute("transform", buf1);
		nownode0->LinkEndChild(node03);
		nownode0 = node03;


		CString tmps = "";
		CString tmps1 = "";
		CString tmps2 = "";
		CString tmps3 = "";

		TiXmlElement* node04 = new TiXmlElement("circle");
		node04->SetAttribute("cx", tmpgeo->Center_point[0]);
		node04->SetAttribute("cy", tmpgeo->Center_point[1] * -1.0f);
		node04->SetAttribute("r", tmpgeo->Radius);


		tmps2.Format("rgb(%d,%d,%d)", (int)(tmpgeo->Line_colour[0] * 255), (int)(tmpgeo->Line_colour[1] * 255), (int)(tmpgeo->Line_colour[2] * 255));
		tmps3.Format("%f", (tmpgeo->width)*10.0 + 1);
		// <polygon id = "s1" points = "60,0 120,0 180,60 180,120 120,180 60,180 0,120 0,60" fill = "none" stroke = "black" stroke-width = "3"/>
		node04->SetAttribute("fill", "none");
		node04->SetAttribute("stroke", tmps2);
		node04->SetAttribute("stroke-width", tmps3);
		node04->SetAttribute("vector-effect", "non-scaling-stroke");
		CString tmps4 = "";
		CString tmps5 = "";
		for (int iia = 0; iia < tmpgeo->line_type_Segment; iia += 2) {
			if (iia == 0)
				tmps4.Format("%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
			else
				tmps4.Format(",%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
			tmps5 = tmps5 + tmps4;
		}
		if (tmpgeo->line_type_Pitch[0] != 0)
			node04->SetAttribute("stroke-dasharray", tmps5);

		nownode0->LinkEndChild(node04);
	}

	map<long, kos_Ellipse*>::iterator itormapEllipse;
	for (itormapEllipse = Ellipse_List.begin(); itormapEllipse != Ellipse_List.end(); ++itormapEllipse)
	{
		kos_Ellipse* tmpgeo = itormapEllipse->second;
		if (tmpgeo->checkflag != 3)
			continue;
		CString buf1;
		CString buf2;
		TiXmlElement* nownode0;

		buf1.Format("%f", tmpgeo->transform[0]);
		buf2.Format("%f", tmpgeo->transform[1] * -1.0f);
		TiXmlElement* node01 = new TiXmlElement("g");
		node01->SetAttribute("transform", "translate(" + buf1 + "," + buf2 + ")");
		m_pnode2->LinkEndChild(node01);

		nownode0 = node01;

		TiXmlElement* node02 = new TiXmlElement("g");
		float fff = tmpgeo->transform[2];
		buf1.Format("rotate(%f)", fff);
		node02->SetAttribute("transform", buf1);
		nownode0->LinkEndChild(node02);
		nownode0 = node02;

		TiXmlElement* node03 = new TiXmlElement("g");
		buf1.Format("scale(%f,%f)", tmpgeo->transform[3], tmpgeo->transform[4]);
		node03->SetAttribute("transform", buf1);
		nownode0->LinkEndChild(node03);
		nownode0 = node03;


		CString tmps = "";
		CString tmps1 = "";
		CString tmps2 = "";
		CString tmps3 = "";


		TiXmlElement* node04 = new TiXmlElement("ellipse ");
		node04->SetAttribute("cx", tmpgeo->Center_point[0]);
		node04->SetAttribute("cy", tmpgeo->Center_point[1] * -1.0f);
		node04->SetAttribute("rx", tmpgeo->Radius_x);
		node04->SetAttribute("ry", tmpgeo->Radius_y);

		tmps1.Format("rotate(%f,%f,%f)", tmpgeo->Rotation *-1.0f, tmpgeo->Center_point[0], tmpgeo->Center_point[1] * -1.0f);

		node04->SetAttribute("transform", tmps1);


		tmps2.Format("rgb(%d,%d,%d)", (int)(tmpgeo->Line_colour[0] * 255), (int)(tmpgeo->Line_colour[1] * 255), (int)(tmpgeo->Line_colour[2] * 255));
		tmps3.Format("%f", (tmpgeo->width)*10.0 + 1);
		// <polygon id = "s1" points = "60,0 120,0 180,60 180,120 120,180 60,180 0,120 0,60" fill = "none" stroke = "black" stroke-width = "3"/>
		node04->SetAttribute("fill", "none");
		node04->SetAttribute("stroke", tmps2);
		node04->SetAttribute("stroke-width", tmps3);
		node04->SetAttribute("vector-effect", "non-scaling-stroke");
		CString tmps4 = "";
		CString tmps5 = "";
		for (int iia = 0; iia < tmpgeo->line_type_Segment; iia += 2) {
			if (iia == 0)
				tmps4.Format("%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
			else
				tmps4.Format(",%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
			tmps5 = tmps5 + tmps4;
		}
		if (tmpgeo->line_type_Pitch[0] != 0)
			node04->SetAttribute("stroke-dasharray", tmps5);

		nownode0->LinkEndChild(node04);

	}


	map<long, kos_Arc*>::iterator itormapArc;
	for (itormapArc = ArcList.begin(); itormapArc != ArcList.end(); ++itormapArc)
	{
		kos_Arc* tmpgeo = itormapArc->second;
	//	if (tmpgeo->checkflag != 2)
		if (tmpgeo->checkflag > 3)
			continue;

		CString buf1;
		CString buf2;
		TiXmlElement* nownode0;

		buf1.Format("%f", tmpgeo->transform[0]);
		buf2.Format("%f", tmpgeo->transform[1] * -1.0f);
		TiXmlElement* node01 = new TiXmlElement("g");
		node01->SetAttribute("transform", "translate(" + buf1 + "," + buf2 + ")");
		m_pnode2->LinkEndChild(node01);

		nownode0 = node01;

		TiXmlElement* node02 = new TiXmlElement("g");
		float fff = tmpgeo->transform[2];
		buf1.Format("rotate(%f)", fff);
		node02->SetAttribute("transform", buf1);
		nownode0->LinkEndChild(node02);
		nownode0 = node02;

		TiXmlElement* node03 = new TiXmlElement("g");
		buf1.Format("scale(%f,%f)", tmpgeo->transform[3], tmpgeo->transform[4]);
		node03->SetAttribute("transform", buf1);
		nownode0->LinkEndChild(node03);
		nownode0 = node03;


		kPoint kpos;
		kpos.x = tmpgeo->Rotation[1];
		kpos.y = tmpgeo->Rotation[2];
		kPoint base;
		base.x = 0;
		base.y = 0;
		kPoint pp1 = RotateCoordinate(kpos, tmpgeo->Start_angle, base);
		kPoint pp2 = RotateCoordinate(kpos, tmpgeo->End_angle, base);

		pp1 = MultiCoordinate(pp1, tmpgeo->Radius);
		pp2 = MultiCoordinate(pp2, tmpgeo->Radius);


		pp1.x += tmpgeo->Center_point[0];
		pp1.y += tmpgeo->Center_point[1];
		pp2.x += tmpgeo->Center_point[0];
		pp2.y += tmpgeo->Center_point[1];

		CString tmps = "";
		tmps.Format("M%f,%f a%f,%f %f", pp1.x, pp1.y* -1.0f, tmpgeo->Radius, tmpgeo->Radius, tmpgeo->Rotation[0]);
		CString tmps1 = "";
		CString tmps2 = "";
		CString tmps3 = "";
		int largev = 0;
		if (tmpgeo->LArraw == 0) {
			if (tmpgeo->End_angle > tmpgeo->Start_angle) {
				largev = ((tmpgeo->End_angle - tmpgeo->Start_angle) > 180) ? 1 : 0;
			}
			else
			{
				largev = ((tmpgeo->End_angle + 360 - tmpgeo->Start_angle) > 180) ? 1 : 0;
			}
		}
		else
		{
			if (tmpgeo->End_angle < tmpgeo->Start_angle) {
				largev = ((tmpgeo->Start_angle - tmpgeo->End_angle) > 180) ? 1 : 0;
			}
			else
			{
				largev = ((tmpgeo->Start_angle + 360 - tmpgeo->End_angle) > 180) ? 1 : 0;

			}
		}


		tmps1.Format(" %d,%d %f,%f", largev, tmpgeo->LArraw, pp2.x - pp1.x, (pp2.y - pp1.y)* -1.0f);
		TiXmlElement* node04 = new TiXmlElement("path");
		node04->SetAttribute("d", tmps + tmps1);


		tmps2.Format("rgb(%d,%d,%d)", (int)(tmpgeo->Line_colour[0] * 255), (int)(tmpgeo->Line_colour[1] * 255), (int)(tmpgeo->Line_colour[2] * 255));
		tmps3.Format("%f", (tmpgeo->width)*10.0 + 1);
		// <polygon id = "s1" points = "60,0 120,0 180,60 180,120 120,180 60,180 0,120 0,60" fill = "none" stroke = "black" stroke-width = "3"/>
		node04->SetAttribute("fill", "none");
		node04->SetAttribute("stroke", tmps2);
		node04->SetAttribute("stroke-width", tmps3);
		node04->SetAttribute("vector-effect", "non-scaling-stroke");
		CString tmps4 = "";
		CString tmps5 = "";
		for (int iia = 0; iia < tmpgeo->line_type_Segment; iia += 2) {
			if (iia == 0)
				tmps4.Format("%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
			else
				tmps4.Format(",%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
			tmps5 = tmps5 + tmps4;
		}
		if (tmpgeo->line_type_Pitch[0] != 0)
			node04->SetAttribute("stroke-dasharray", tmps5);
		nownode0->LinkEndChild(node04);

	}

*/



	m_doc->SaveFile(m_FileNameOnly + ".svg");

	writeFile.close();

	delete m_doc;
	delete[] m_pBufferLine;
	m_pBufferLine = NULL;

	write_log.open(FileNameOnly + ".log");

	CString str00 = "";
	CString str01 = "";

	struct tm* t;
	time_t timer;

	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

	str01.Format("%s \n", filename_only.GetBuffer().c_str());
	str00 += str01;
	str01.Format("TIME: %s \n", timeToString(t));
	str00 += str01;
	str01.Format("POLYLINE count:  %d \n", cnt_POLYLINE);
	str00 += str01;
	str01.Format("CIRCLE count:  %d \n", cnt_CIRCLE);
	str00 += str01;
	str01.Format("ELLIPSE count:  %d \n", cnt_ELLIPSE);
	str00 += str01;
	str01.Format("TRIMMED_CURVE count:  %d \n", cnt_TRIMMED_CURVE);
	str00 += str01;
	str01.Format("COMPOSITE_CUR count:  %d \n", cnt_COMPOSITE_CURVE);
	str00 += str01;
	str01.Format("TEXT count:  %d \n", cnt_TEXT);
	str00 += str01;

	endTime = clock();
	str01.Format("Execution time : %fsec\n", ((double)(endTime - startTime)) / CLOCKS_PER_SEC);
	str00 += str01;

	write_log.write(str00, str00.GetLength());
	write_log.close();

	return 0;
}

int kos_loader::CheckVersion()
{
	TRACE("  check version ...");

	bool indata = false;
	do {
		ReadLine();
		if (strstr(m_pBufferLine, "FILE_SCHEMA (('KOSDIC'));") != NULL)
		{
			indata = true;
			continue;
		}

		if (strstr(m_pBufferLine, "ENDSEC;") != NULL && indata == true)
		{
			TRACE("ok\n");
			return 1;;
		}
		else
			if (strstr(m_pBufferLine, "ENDSEC;") != NULL)
			{
				break;
			}

		if (indata == true)
		{
			CString tempstr0 = m_pBufferLine;
			CString tempstrA[10];
			CString tempstrD[10];
			CString tempstrB[3];
			CString tempstrC[3];
			Split(m_pBufferLine, tempstrA, '(');
			//Split(tempstrA[1], tempstrB, ')');
			int startn = -1;
			int endn = -1;
			tempstrB[0] = "";
			for (int ii = 0; ii < tempstr0.GetLength(); ii++)
			{
				if (startn == -1 && tempstr0.GetAt(ii) == '(')
					startn = ii + 1;
				if (tempstr0.GetAt(ii) == ')')
					endn = ii;
			}

			tempstrB[1] = tempstr0.Mid(startn, endn - startn);
			int strn = Split(tempstrB[1], tempstrD, ',');
			if (strn > 2)
			{
				Split(tempstrD[0], tempstrC, '\'');
				tempstrB[0] += tempstrC[1];
				tempstrB[0] += " : ";
				Split(tempstrD[1], tempstrC, '\'');
				tempstrB[0] += tempstrC[1];
				tempstrB[0] += "\0";
			}


			if (strstr(tempstrA[0], "PI") != NULL)
			{
				m_PIarr.push_back(tempstrB[0].GetBuffer());
			}
			else
				if (strstr(tempstrA[0], "PA") != NULL)
				{
					m_PAarr.push_back(tempstrB[0].GetBuffer());
				}
				else
					if (strstr(tempstrA[0], "EI") != NULL)
					{
						m_EIarr.push_back(tempstrB[0].GetBuffer());
					}
					else
						if (strstr(tempstrA[0], "CI") != NULL)
						{
							m_CIarr.push_back(tempstrB[0].GetBuffer());
						}
						else
							if (strstr(tempstrA[0], "DP") != NULL)
							{
								m_DParr.push_back(tempstrB[0].GetBuffer());
							}
							else
								if (strstr(tempstrA[0], "DI") != NULL)
								{
									m_DIarr.push_back(tempstrB[0].GetBuffer());
								}
								else
									if (strstr(tempstrA[0], "DA") != NULL)
									{
										m_DAarr.push_back(tempstrB[0].GetBuffer());
									}
									else
										if (strstr(tempstrA[0], "DC") != NULL)
										{
											m_DCarr.push_back(tempstrB[0].GetBuffer());
										}
										else
											if (strstr(tempstrA[0], "FI") != NULL)
											{
												m_FIarr.push_back(tempstrB[0].GetBuffer());
											}
											else
												if (strstr(tempstrA[0], "UD") != NULL)
												{
													m_UDarr.push_back(tempstrB[0].GetBuffer());
												}

		}


	} while (m_IndexBuffer < m_SizeFile);

	//MessageBox(NULL, _T("IFC2X3 ������ ������ �ƴմϴ�."), _T("���� �ε� ����"), MB_OK | MB_ICONSTOP);
	TRACE("invalid\n");

	return 0;
}

int kos_loader::ReadFile(CString filename)
{
	m_FileName = filename;

	std::ifstream file(m_FileName, std::ios_base::ate);
	if (!file.is_open())
	{
		return 0;
	}


	int nBigSize = file.tellg();
	file.seekg(0);
	//assert(nBigSize < 2147483648);	// ���� ���� ������ ��å���δ� 2GB(2^31)�� ���� ���ƾ� �Ѵ�.
	m_SizeFile = int(nBigSize);

	if (m_pBuffer != NULL)
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}
	m_pBuffer = new char[m_SizeFile];

	try
	{
		file.read(m_pBuffer, m_SizeFile);
	}
	catch (...)
	{

	}

	file.close();
	return 1;

	//CFile file;
	//CFileException ex;
	//
	//// Opening
	///*TRACE*/("  opening...");
	//if (!file.Open(m_FileName, CFile::modeRead, &ex))
	//{
	//	/*TRACE*/("unable to open file for reading->%s\n", filename.GetBuffer());
	//	return 0;
	//}
	////TRACE("ok\n");

	//// Size file
	//
	//uint64_t/*ULONGLONG */nBigSize = file.GetLength();
	//assert(nBigSize < 2147483648);	// ���� ���� ������ ��å���δ� 2GB(2^31)�� ���� ���ƾ� �Ѵ�.
	//m_SizeFile = int(nBigSize);

	////TRACE("  length : %d bytes\n", m_SizeFile);

	//// Alloc
	////TRACE("  alloc...");

	//if (NULL != m_pBuffer)
	//	HeapFree(m_hMem, 0, m_pBuffer);

	//HeapCompact(m_hMem, 0);
	//m_pBuffer = (char *)HeapAlloc(m_hMem, 0, sizeof(char)*m_SizeFile);
	//if (NULL == m_pBuffer)
	//{

	//	return 0;
	//}

	////TRACE("ok\n");
	//// Reading
	////TRACE("  reading...");

	//try
	//{
	//	file.Read(m_pBuffer, m_SizeFile);
	//}
	//catch (CFileException* /*e*/)
	//{
	//	//TRACE("error during reading\n");
	//	file.Close();
	//	return 0;
	//}

	////TRACE("ok\n");

	//// Closing
	//file.Close();

	return 1;
}

int kos_loader::ReadLine()
{

	m_pBufferLine[0] = '\0';
	int i = 0;
	int k = 0; //"'"�� ��

	do {
		m_pBufferLine[i] = m_pBuffer[m_IndexBuffer];
		if (m_pBufferLine[i] == '\'')
		{
			if (i > 1 && k % 2 == 1)
			{
				if (m_pBufferLine[i] == '\\')
				{
					k--;
				}
			}
			k++;
		}
		if (k % 2 == 0 && m_pBufferLine[i] == ';')
			break;

		i++;
		m_IndexBuffer++;

	} while (i < MAX_LINE_KOS - 2 && m_IndexBuffer < m_SizeFile);

	m_pBufferLine[i + 1] = '\0';
	m_IndexBuffer++;

	m_IndexBuffer2 = 0;
	//TRACE("  line : %s\n",m_pBufferLine);

	return 1;
}

int kos_loader::CountDef()
{

	do {
		ReadLine();
		if (strstr(m_pBufferLine, "DATA;") != NULL)
		{
			TRACE("DATA;ok\n");
			break;
		}
	} while (m_IndexBuffer < m_SizeFile);


	int tmp = m_IndexBuffer;
	int nb = 0;

	float linestate = 0;
	int markN = 0;
	m_IndexBuffer2 = 0;

	char* tmpchar = new char[7000];
	if (NULL == tmpchar)
	{

		return 0;
	}

	kosEntityVV* pEntityVV = NULL;
	kosCVV* pCVV = NULL;
	kosEntityVVA* pEntityVVA = NULL;
	kosCVVA* pCVVA = NULL;
	int passkey = 0;
	int lineN = 0;
	int exflag = 0;

	while (m_IndexBuffer < m_SizeFile)
	{
		if (linestate == 0)
		{
			if (m_pBuffer[m_IndexBuffer] == '#')
			{

				m_IndexBuffer++;
				linestate++;
				m_IndexBuffer2 = 0;

			}
			else
			{

				m_IndexBuffer++;
				continue;
			}
		}
		else if (linestate == 1)
		{
			if (m_pBuffer[m_IndexBuffer] == '=')
			{
				tmpchar[m_IndexBuffer2] = '\0';

				pEntityVV = new kosEntityVV;
				if (NULL == pEntityVV)
				{

					return 0;
				}

				pEntityVV->bChecked = FALSE;

				lineN = atoi(tmpchar);

				m_IndexBuffer++;
				m_IndexBuffer2 = 0;
				linestate++;
				linestate++;
			}
			else
			{
				tmpchar[m_IndexBuffer2] = m_pBuffer[m_IndexBuffer];
				m_IndexBuffer2++;
				m_IndexBuffer++;

				continue;
			}
		}
		//		else
		//		if(linestate ==2){
		//			if(m_pBuffer[m_IndexBuffer] == ' '){
		//				m_IndexBuffer++;
		//				linestate++;
		//				m_IndexBuffer2=0;
		//			}else{
		////				m_IndexBuffer++;
		//				linestate++;
		//				continue;
		//			}
		//		}
		else if (linestate == 3)
		{
			if (m_pBuffer[m_IndexBuffer - 1] == '=' && m_pBuffer[m_IndexBuffer] == '(')
			{
				m_IndexBuffer2 = 0;

				string strstr01 = string("etc");
				long lCount = m_EntityNamevector.size();
				map<string, long>::iterator itormap00;
				itormap00 = m_EntityNameMapSL.find(strstr01);
				if (itormap00 == m_EntityNameMapSL.end())
				{
					pEntityVV->dvalue = lCount;
					m_EntityNamevector.push_back(strstr01);
					m_EntityNameMapSL.insert(pair<string, long>(strstr01, lCount));
				}
				else
				{
					pEntityVV->dvalue = itormap00->second;
				}

				char tmp_char2[1000];
				int tmp_char2_index = 0;
				while (!(m_pBuffer[m_IndexBuffer - 1] == ')' && m_pBuffer[m_IndexBuffer] == ';'))
				{
					tmp_char2[tmp_char2_index] = m_pBuffer[m_IndexBuffer];
					tmp_char2_index++;

					if (m_pBuffer[m_IndexBuffer] == '#' || m_pBuffer[m_IndexBuffer] == '-' || isdigit(m_pBuffer[m_IndexBuffer]) != 0)
					{
						tmpchar[m_IndexBuffer2] = m_pBuffer[m_IndexBuffer];
						m_IndexBuffer2++;
					}
					else
					{
						if (m_IndexBuffer2 > 0)
						{
							tmpchar[m_IndexBuffer2] = '\0';
							pCVV = new kosCVV;
							pCVV->cvalue = new char[m_IndexBuffer2 + 1];
							if (NULL == pCVV->cvalue)
							{

								return 0;
							}
							strcpy_s(pCVV->cvalue, m_IndexBuffer2 + 1, tmpchar);
							pEntityVV->cvvec.push_back(pCVV);
							m_IndexBuffer2 = 0;
						}
						else
						{
							m_IndexBuffer2 = 0;
						}
					}
					m_IndexBuffer++;
				}
				tmp_char2[tmp_char2_index] = '\0';
				tmp_char2_index++;
				CString tmpCstr;
				tmpCstr.Format("%s", tmp_char2);
				CString tempstrA[10];
				CString tempstrB[10];
				CString tempstrC[20];
				int tempstrAN = Split(tmpCstr, tempstrA, '\n');

				for (int iii = 0; iii < tempstrAN; iii++)
				{
					Split(tempstrA[iii], tempstrB, '(');

					pEntityVV->ect_content.push_back(tempstrB[0].GetBuffer(tempstrB[0].GetLength()));


					int tempstrCN = Split(tempstrB[1], tempstrC, ',');

					for (int jjj = 0; jjj < tempstrCN; jjj++)
					{
						pEntityVV->ect_content.push_back(tempstrC[jjj].GetBuffer(tempstrC[jjj].GetLength()));
					}
				}

				pEntityVVA = new kosEntityVVA;
				if (NULL == pEntityVVA)
				{
					return 0;
				}

				pEntityVVA->dvalue = pEntityVV->dvalue;
				pEntityVVA->cvvecNum = pEntityVV->cvvec.size();
				for (int iii = 0; iii < pEntityVV->ect_content.size(); iii++)
				{
					pEntityVVA->ect_content.push_back(pEntityVV->ect_content[iii]);
				}
				pEntityVVA->cvvec = new kosCVVA[pEntityVVA->cvvecNum];


				for (int iii = 0; iii < pEntityVVA->cvvecNum; iii++)
				{
					pEntityVVA->cvvec[iii].ccvecNum = pEntityVV->cvvec[iii]->ccvec.size();
					if (pEntityVVA->cvvec[iii].ccvecNum)
					{
						pEntityVVA->cvvec[iii].ccvec = new charP[pEntityVVA->cvvec[iii].ccvecNum];
						for (int jjj = 0; jjj < pEntityVVA->cvvec[iii].ccvecNum; jjj++)
						{
							pEntityVVA->cvvec[iii].ccvec[jjj] = pEntityVV->cvvec[iii]->ccvec[jjj];
							//TRACE("- %s  \n",pEntityVVA->cvvec[iii].ccvec[jjj]);
						}
					}
					else
					{
						//							strcpy(pEntityVVA->cvvec[iii].cvalue , pEntityVV->cvvec[iii]->cvalue )
						pEntityVVA->cvvec[iii].cvalue = pEntityVV->cvvec[iii]->cvalue;
						//TRACE("- %s  \n",pEntityVVA->cvvec[iii].cvalue);
					}
				}

				m_EntityMapA.insert(pair<long, kosEntityVVA*>(lineN, pEntityVVA));



				tmpchar[m_IndexBuffer2] = '\0';

				passkey = 0;
				linestate = 0;
				m_IndexBuffer++;
				m_IndexBuffer2 = 0;
				markN = 0;
				continue;
			}

			if (m_pBuffer[m_IndexBuffer] == '(')
			{
				tmpchar[m_IndexBuffer2] = '\0';

				string strstr01 = string(tmpchar);
				long lCount = m_EntityNamevector.size();
				map<string, long>::iterator itormap00;
				itormap00 = m_EntityNameMapSL.find(strstr01);

				if (itormap00 == m_EntityNameMapSL.end())
				{
					pEntityVV->dvalue = lCount;
					m_EntityNamevector.push_back(strstr01);
					m_EntityNameMapSL.insert(pair<string, long>(strstr01, lCount));
				}
				else
				{
					pEntityVV->dvalue = itormap00->second;
				}


				m_IndexBuffer++;
				m_IndexBuffer2 = 0;

				markN = 0;
				linestate = 4.0f;

			}
			else if (m_pBuffer[m_IndexBuffer] == ' ')
			{

				m_IndexBuffer++;
			}
			else
			{
				tmpchar[m_IndexBuffer2] = m_pBuffer[m_IndexBuffer];
				m_IndexBuffer2++;
				m_IndexBuffer++;

				continue;
			}
		}
		else if (linestate >= 4 && linestate < 5)
		{
			// \n
			if (m_pBuffer[m_IndexBuffer] == 10)//LF NEWLINE
			{

				m_IndexBuffer++;
			}
			else if (m_pBuffer[m_IndexBuffer] == 13)//CR first linecursor
			{

				m_IndexBuffer++;
			}
			////////////////
			else
				if (m_pBuffer[m_IndexBuffer] == 39 && m_pBuffer[m_IndexBuffer + 1] == ')') {  //'\''=39 '\\'=92             "'"
					markN++;             // "'" ó���� ����
					m_IndexBuffer++;

				}
				else
					if (m_pBuffer[m_IndexBuffer] == 39 && m_pBuffer[m_IndexBuffer + 1] == ',') {  //'\''=39 '\\'=92             "'"
						markN++;             // "'" ó���� ����
						m_IndexBuffer++;

					}
			////////////////
					else if (m_pBuffer[m_IndexBuffer] == 39 && m_pBuffer[m_IndexBuffer - 1] != 92)	// ' ó��
					{  //'\''=39 '\\'=92             "'"
						markN++;             // "'" ó���� ����
						m_IndexBuffer++;

					}
					else if (m_pBuffer[m_IndexBuffer] == 39 && m_pBuffer[m_IndexBuffer - 1] == 92 && m_pBuffer[m_IndexBuffer - 2] == 92 && m_pBuffer[m_IndexBuffer - 3] != 92)
					{  //'\\''=39
						markN++;
						m_IndexBuffer++;

					}
					else if (m_pBuffer[m_IndexBuffer] == ' ' && markN % 2 == 0)		// " " ó��
					{
						m_IndexBuffer++;

					}
					else if (m_pBuffer[m_IndexBuffer] == ',' && markN % 2 == 0)		// , ó��
					{
						if (linestate == 4)
						{
							if (!passkey)
							{
								pCVV = new kosCVV;
								if (NULL == pCVV)
								{

									return 0;
								}

								tmpchar[m_IndexBuffer2] = '\0';

								pCVV->cvalue = new char[m_IndexBuffer2 + 1];
								if (NULL == pCVV->cvalue)
								{

									return 0;
								}

								strcpy_s(pCVV->cvalue, m_IndexBuffer2 + 1, tmpchar);
								pEntityVV->cvvec.push_back(pCVV);

								if (strlen(tmpchar) == 22 && pEntityVV->cvvec.size() == 1)
								{
									string strstr01 = tmpchar;
									//m_UidIndexMap.insert(pair<string,long>(strstr01, lineN));
									//TRACE("            - %s _ %d \n",pCVV->cvalue,strlen(pCVV->cvalue));
								}
							}
							passkey = 0;

							m_IndexBuffer++;
							m_IndexBuffer2 = 0;
						}
						else
						{
							tmpchar[m_IndexBuffer2] = '\0';
							char* psss = new char[m_IndexBuffer2 + 1];
							if (NULL == psss)
							{

								return 0;
							}

							strcpy_s(psss, m_IndexBuffer2 + 1, tmpchar);
							pCVV->ccvec.push_back(psss);
							//					TRACE("            -------- %s\n",psss);


							m_IndexBuffer++;
							m_IndexBuffer2 = 0;
						}
					}
					else if (m_pBuffer[m_IndexBuffer] == ')' && markN % 2 == 0)
					{
						if (exflag)
						{
							tmpchar[m_IndexBuffer2] = m_pBuffer[m_IndexBuffer];
							m_IndexBuffer2++;
							m_IndexBuffer++;

							exflag = 0;
							continue;
						}
						if (linestate == 4)
						{
							if (m_pBuffer[m_IndexBuffer] == '\n')
							{

								m_IndexBuffer++;
								//						TRACE("nnnnnnn---  %d\n",lineN);
							}
							if (m_pBuffer[m_IndexBuffer] == '\0')
							{

								m_IndexBuffer++;
								//						TRACE("0000000---  %d\n",lineN);
							}
							//if(m_pBuffer[m_IndexBuffer] == ';')

							if (!passkey)
							{
								pCVV = new kosCVV;
								if (NULL == pCVV)
								{

									return 0;
								}

								tmpchar[m_IndexBuffer2] = '\0';

								pCVV->cvalue = new char[m_IndexBuffer2 + 1];
								if (NULL == pCVV->cvalue)
								{

									return 0;
								}

								strcpy_s(pCVV->cvalue, m_IndexBuffer2 + 1, tmpchar);
								pEntityVV->cvvec.push_back(pCVV);

								if (strlen(tmpchar) == 22 && pEntityVV->cvvec.size() == 1)
								{
									string strstr01 = tmpchar;
									//m_UidIndexMap.insert(pair<string, long>(strstr01, lineN));
									//TRACE("            - %s _ %d \n",pCVV->cvalue,strlen(pCVV->cvalue));
								}
								//TRACE("            - %s\n",pCVV->cvalue);
							}

							pEntityVVA = new kosEntityVVA;
							if (NULL == pEntityVVA)
							{

								return 0;
							}
							pEntityVVA->dvalue = pEntityVV->dvalue;
							pEntityVVA->cvvecNum = pEntityVV->cvvec.size();
							pEntityVVA->cvvec = new kosCVVA[pEntityVVA->cvvecNum];
							for (int iii = 0; iii < pEntityVVA->cvvecNum; iii++)
							{
								pEntityVVA->cvvec[iii].ccvecNum = pEntityVV->cvvec[iii]->ccvec.size();
								if (pEntityVVA->cvvec[iii].ccvecNum)
								{
									pEntityVVA->cvvec[iii].ccvec = new charP[pEntityVVA->cvvec[iii].ccvecNum];
									for (int jjj = 0; jjj < pEntityVVA->cvvec[iii].ccvecNum; jjj++)
									{
										pEntityVVA->cvvec[iii].ccvec[jjj] = pEntityVV->cvvec[iii]->ccvec[jjj];
										//TRACE("- %s  \n",pEntityVVA->cvvec[iii].ccvec[jjj]);
									}
								}
								else
								{
									//							strcpy(pEntityVVA->cvvec[iii].cvalue , pEntityVV->cvvec[iii]->cvalue )
									pEntityVVA->cvvec[iii].cvalue = pEntityVV->cvvec[iii]->cvalue;
									//TRACE("- %s  \n",pEntityVVA->cvvec[iii].cvalue);
								}
							}

							m_EntityMapA.insert(pair<long, kosEntityVVA*>(lineN, pEntityVVA));


							passkey = 0;
							linestate = 0;
							m_IndexBuffer++;
							m_IndexBuffer2 = 0;
							markN = 0;

							if (!strcmp(m_EntityNamevector[pEntityVV->dvalue].c_str(), "LAYER_STYLE_ASSIGNMENT")) {
								for (int iia = 0; iia < pEntityVV->cvvec[1]->ccvec.size(); iia++) {
									Layer_style_assignment.insert(pair<long, long>(getStrNumInt(pEntityVV->cvvec[0]->cvalue), getStrNumInt(pEntityVV->cvvec[1]->ccvec[iia])));
								}
							}
							else
								if (!strcmp(m_EntityNamevector[pEntityVV->dvalue].c_str(), "DRAUGHTING_CALLOUT_RELATIONSHIP")) {
									for (int iia = 0; iia < pEntityVV->cvvec[1]->ccvec.size(); iia++) {
										DRAUGHTING_CALLOUT_RELATIONSHIP.insert(pair<long, long>(getStrNumInt(pEntityVV->cvvec[2]->cvalue), getStrNumInt(pEntityVV->cvvec[3]->ccvec[iia])));
									}
								}
								else
									if (!strcmp(m_EntityNamevector[pEntityVV->dvalue].c_str(), "PRESENTATION_LAYER_ASSIGNMENT")) {
										for (int iia = 0; iia < pEntityVV->cvvec[2]->ccvec.size(); iia++) {
											Presentation_layer_assignment.insert(pair<long, long>(lineN, getStrNumInt(pEntityVV->cvvec[2]->ccvec[iia])));
										}
									}
									else
										if (!strcmp(m_EntityNamevector[pEntityVV->dvalue].c_str(), "LAYER_PROPERTIES")) {
											Layer_properties.insert(pair<long, long>(getStrNumInt(pEntityVV->cvvec[3]->cvalue), lineN));

										}
										else
											if (!strcmp(m_EntityNamevector[pEntityVV->dvalue].c_str(), "TEXT_LITERAL_WITH_EXTENT")) {
												Text_literal_with_extent.push_back(lineN);
											}
											else
												if (!strcmp(m_EntityNamevector[pEntityVV->dvalue].c_str(), "PRESENTATION_SIZE")) {
													m_EntityNamevector[pEntityVV->dvalue].c_str();
													Presentation_size = lineN;
												}
												else
													if (!strcmp(m_EntityNamevector[pEntityVV->dvalue].c_str(), "PRESENTATION_VIEW")) {
														m_EntityNamevector[pEntityVV->dvalue].c_str();
														Presentation_view = lineN;
													}

							delete pEntityVV;

						}
						else
						{
							tmpchar[m_IndexBuffer2] = '\0';
							char* psss = new char[m_IndexBuffer2 + 1];
							if (NULL == psss)
							{
								return 0;
							}

							strcpy_s(psss, m_IndexBuffer2 + 1, tmpchar);
							pCVV->ccvec.push_back(psss);
							//					TRACE("            -------- %s\n",psss);

							m_IndexBuffer++;
							m_IndexBuffer2 = 0;
							linestate = linestate - 0.1f;
							passkey = 1;

						}
					}
					else if (m_pBuffer[m_IndexBuffer] == '(' && markN % 2 == 0)
					{
						//m_IndexBuffer

						exflag = 0;
						if (m_IndexBuffer > 5)
						{
							for (int iii = 1; iii < 3; iii++)
							{
								if (m_pBuffer[m_IndexBuffer - iii] == 10)
								{
									continue;
								}
								else if (m_pBuffer[m_IndexBuffer - iii] == 13)
								{
									continue;
								}
								else if (m_pBuffer[m_IndexBuffer - iii] == ' ')
								{
									continue;
								}
								else if (m_pBuffer[m_IndexBuffer - iii] == ',')
								{
									break;
								}
								else if (m_pBuffer[m_IndexBuffer - iii] == '(')
								{
									break;
								}
								else
								{
									exflag = 1;
									break;
								}
							}
						}
						if (!exflag)
						{
							pCVV = new kosCVV;
							if (NULL == pCVV)
							{
								return 0;
							}

							pCVV->cvalue = NULL;
							pEntityVV->cvvec.push_back(pCVV);

							m_IndexBuffer++;
							linestate = linestate + 0.1f;
							m_IndexBuffer2 = 0;
						}
						else
						{
							tmpchar[m_IndexBuffer2] = m_pBuffer[m_IndexBuffer];
							m_IndexBuffer2++;
							m_IndexBuffer++;
							continue;
						}
					}
					else
					{
						tmpchar[m_IndexBuffer2] = m_pBuffer[m_IndexBuffer];
						m_IndexBuffer2++;
						m_IndexBuffer++;
						continue;
					}
		}
	}

	delete[] tmpchar;

	return 1;
}


bool  kos_loader::get_CURVE_STYLE(int nnn)
{
	map<long, kosEntityVVA*>::iterator itormap;
	itormap = m_EntityMapA.find(nnn);
	if (itormap == m_EntityMapA.end())
		return false;
	if (!strcmp(m_EntityNamevector[itormap->second->dvalue].c_str(), "CURVE_STYLE"))
	{
		TempLine_width = atoi(itormap->second->cvvec[2].cvalue);
		return true;
	}
	return false;
}
bool  kos_loader::get_PRE_DEFINED_COLOUR(int nnn)
{
	map<long, kosEntityVVA*>::iterator itormap;
	itormap = m_EntityMapA.find(nnn);
	if (itormap == m_EntityMapA.end())
		return false;
	if (!strcmp(m_EntityNamevector[itormap->second->dvalue].c_str(), "PRE_DEFINED_COLOUR"))
	{
		if (!strcmp(itormap->second->cvvec[0].cvalue, "white"))
		{
			//TempLine_colour[0] = 1; TempLine_colour[1] = 1; TempLine_colour[2] = 1;
			TempLine_colour[0] = 0; TempLine_colour[1] = 0; TempLine_colour[2] = 0;
			return true;
		}
		else
			if (!strcmp(itormap->second->cvvec[0].cvalue, "cyan"))
			{
				TempLine_colour[0] = 0; TempLine_colour[1] = 1; TempLine_colour[2] = 1;
				return true;
			}
			else
				if (!strcmp(itormap->second->cvvec[0].cvalue, "magenta"))
				{
					TempLine_colour[0] = 1; TempLine_colour[1] = 0; TempLine_colour[2] = 1;
					return true;
				}
				else
					if (!strcmp(itormap->second->cvvec[0].cvalue, "yellow"))
					{
						TempLine_colour[0] = 1; TempLine_colour[1] = 1; TempLine_colour[2] = 0;
						return true;
					}
					else
						if (!strcmp(itormap->second->cvvec[0].cvalue, "blue"))
						{
							TempLine_colour[0] = 0; TempLine_colour[1] = 0; TempLine_colour[2] = 1;
							return true;
						}
						else
							if (!strcmp(itormap->second->cvvec[0].cvalue, "green"))
							{
								TempLine_colour[0] = 0; TempLine_colour[1] = 1; TempLine_colour[2] = 0;
								return true;
							}
							else
								if (!strcmp(itormap->second->cvvec[0].cvalue, "red"))
								{
									TempLine_colour[0] = 1; TempLine_colour[1] = 0; TempLine_colour[2] = 0;
									return true;
								}
								else
									if (!strcmp(itormap->second->cvvec[0].cvalue, "black"))
									{
										TempLine_colour[0] = 0; TempLine_colour[1] = 0; TempLine_colour[2] = 0;
										return true;
									}
									else
										if (!strcmp(itormap->second->cvvec[0].cvalue, "bylayer"))
										{
											TempLine_colour[0] = 0; TempLine_colour[1] = 1; TempLine_colour[2] = 0;
											return true;
										}
	}
	else
		if (!strcmp(m_EntityNamevector[itormap->second->dvalue].c_str(), "COLOUR_RGB"))
		{
			TempLine_colour[0] = atof(itormap->second->cvvec[1].cvalue);
			TempLine_colour[1] = atof(itormap->second->cvvec[2].cvalue);
			TempLine_colour[2] = atof(itormap->second->cvvec[3].cvalue);
			if (TempLine_colour[0] == 1 && TempLine_colour[1] == 1 && TempLine_colour[2] == 1)
			{
				TempLine_colour[0] = 0;
				TempLine_colour[1] = 0;
				TempLine_colour[2] = 0;
			}

			return true;
		}
	return false;
}

float* kos_loader::getpoint(int nnn)
{
	map<long, kosEntityVVA*>::iterator itormap;
	itormap = m_EntityMapA.find(nnn);
	if (itormap == m_EntityMapA.end())
		return NULL;

	float* ret = new float[itormap->second->cvvec[1].ccvecNum];
	for (int iia = 0; iia < (itormap->second->cvvec[1]).ccvecNum; iia++) {
		ret[iia] = atof(itormap->second->cvvec[1].ccvec[iia]);
	}

	return ret;
}


bool  kos_loader::get_PRE_DEFINED_CURVE_FONT(int nnn)
{
	map<long, kosEntityVVA*>::iterator itormap;
	itormap = m_EntityMapA.find(nnn);
	if (itormap == m_EntityMapA.end())
		return false;

	kos_User_defined_line_type* ltype = new kos_User_defined_line_type();

	if (!strcmp(m_EntityNamevector[itormap->second->dvalue].c_str(), "PRE_DEFINED_CURVE_FONT"))
	{
		float gijun = 1.25;
		if (!strcmp(itormap->second->cvvec[0].cvalue, "continuous"))
		{
			ltype->Name = "continuous";
			ltype->Segment = 2;
			ltype->Pitch[0] = 0;
			ltype->Pitch[1] = gijun;
			TempLine_ltype = ltype;
			return true;
		}
		else
			if (!strcmp(itormap->second->cvvec[0].cvalue, "dotted"))
			{
				ltype->Name = "dotted";
				ltype->Segment = 2;
				ltype->Pitch[0] = gijun;
				ltype->Pitch[1] = gijun * 2;
				TempLine_ltype = ltype;
				return true;
			}
			else
				if (!strcmp(itormap->second->cvvec[0].cvalue, "dashed"))
				{
					ltype->Name = "dashed";
					ltype->Segment = 2;
					ltype->Pitch[0] = gijun;
					ltype->Pitch[1] = gijun * 4;
					TempLine_ltype = ltype;
					return true;
				}
				else
					if (!strcmp(itormap->second->cvvec[0].cvalue, "chain"))
					{
						ltype->Name = "chain";
						ltype->Segment = 4;
						ltype->Pitch[0] = gijun;
						ltype->Pitch[1] = gijun * 4;
						ltype->Pitch[2] = gijun;
						ltype->Pitch[3] = gijun / 2;
						TempLine_ltype = ltype;
						return true;
					}
					else
						if (!strcmp(itormap->second->cvvec[0].cvalue, "chain double dash"))
						{
							ltype->Name = "chain double dash";
							ltype->Segment = 6;
							ltype->Pitch[0] = gijun;
							ltype->Pitch[1] = gijun * 4;
							ltype->Pitch[2] = gijun;
							ltype->Pitch[3] = gijun / 2;
							ltype->Pitch[4] = gijun;
							ltype->Pitch[5] = gijun / 2;
							TempLine_ltype = ltype;
							return true;
						}
						else
							if (!strcmp(itormap->second->cvvec[0].cvalue, "bylayer"))
							{
								ltype->Name = "bylayer";
								ltype->Segment = 2;
								ltype->Pitch[0] = 0;
								ltype->Pitch[1] = 1;
								TempLine_ltype = ltype;
								return true;
							}
	}
	else
		if (!strcmp(m_EntityNamevector[itormap->second->dvalue].c_str(), "CURVE_STYLE_FONT"))
		{
			ltype->Name = itormap->second->cvvec[0].cvalue;
			ltype->Segment = 0;

			map<long, kosEntityVVA*>::iterator itormap01;
			for (int iia = 0; iia < (itormap->second->cvvec[1]).ccvecNum; iia++) {
				itormap01 = m_EntityMapA.find(getStrNumInt((itormap->second->cvvec[1]).ccvec[iia]));

				ltype->Pitch[ltype->Segment] = atof(itormap01->second->cvvec[0].cvalue);
				ltype->Segment++;
				ltype->Pitch[ltype->Segment] = atof(itormap01->second->cvvec[1].cvalue);
				ltype->Segment++;
			}
			TempLine_ltype = ltype;
			return true;
		}

	return false;
}

int kos_loader::get_PRESENTATION_STYLE_ASSIGNMENT(long nnn, TiXmlElement* nownode, Placement* currpos, long oldlevel)
{
	map<long, kosEntityVVA*>::iterator itormap0;
	itormap0 = m_EntityMapA.find(oldlevel);
	if (itormap0 == m_EntityMapA.end())
		return 0;


	map<long, kosEntityVVA*>::iterator itormap1;
	itormap1 = m_EntityMapA.find(nnn);
	if (itormap1 == m_EntityMapA.end())
		return 0;
	//if (!strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "POLYLINE"))
	//	 TRACE("        %s  _  %d_  %d \n", m_EntityNamevector[itormap0->second->dvalue].c_str(), nnn, oldlevel);


	if (!strcmp(m_EntityNamevector[itormap0->second->dvalue].c_str(), "STYLED_ITEM") || !strcmp(m_EntityNamevector[itormap0->second->dvalue].c_str(), "etc"))
	{

		if (!strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "LINE"))
		{

			kos_Polyline* tmpgeo = NULL;

			map<long, kos_Polyline*>::iterator itormapPolyline;
			itormapPolyline = Line_List.find(nnn);
			if (itormapPolyline == Line_List.end())
			{
				tmpgeo = new kos_Polyline();
				Line_List.insert(pair<long, kos_Polyline*>(nnn, tmpgeo));
				tmpgeo->lineN = nnn;
				tmpgeo->checkflag = 0;
			}
			else
			{
				tmpgeo = itormapPolyline->second;
			}

			//tmpgeo->checkflag += 1;
			tmpgeo->Line_colour[0] = TempLine_colour[0];
			tmpgeo->Line_colour[1] = TempLine_colour[1];
			tmpgeo->Line_colour[2] = TempLine_colour[2];
			tmpgeo->width = TempLine_width;
			tmpgeo->line_type_Segment = TempLine_ltype->Segment;
			for (int iia = 0; iia < tmpgeo->line_type_Segment; iia++)
				tmpgeo->line_type_Pitch[iia] = TempLine_ltype->Pitch[iia];
			return 1;
		}
		if (!strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "POLYLINE"))
		{

			kos_Polyline* tmpgeo = NULL;

			map<long, kos_Polyline*>::iterator itormapPolyline;
			itormapPolyline = Polyline_List.find(nnn);
			if (itormapPolyline == Polyline_List.end())
			{
				tmpgeo = new kos_Polyline();
				Polyline_List.insert(pair<long, kos_Polyline*>(nnn, tmpgeo));
				tmpgeo->lineN = nnn;
				tmpgeo->checkflag = 0;
			}
			else
			{
				tmpgeo = itormapPolyline->second;
			}

			//tmpgeo->checkflag += 1;
			tmpgeo->Line_colour[0] = TempLine_colour[0];
			tmpgeo->Line_colour[1] = TempLine_colour[1];
			tmpgeo->Line_colour[2] = TempLine_colour[2];
			tmpgeo->width = TempLine_width;
			tmpgeo->line_type_Segment = TempLine_ltype->Segment;
			for (int iia = 0; iia < tmpgeo->line_type_Segment; iia++)
				tmpgeo->line_type_Pitch[iia] = TempLine_ltype->Pitch[iia];
			return 1;
		}
		if (!strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "CIRCLE"))
		{
			kos_Circle* tmpgeo = NULL;

			map<long, kos_Circle*>::iterator itormapCircle;
			itormapCircle = Circle_List.find(nnn);
			if (itormapCircle == Circle_List.end())
			{
				tmpgeo = new kos_Circle();
				Circle_List.insert(pair<long, kos_Circle*>(nnn, tmpgeo));
				tmpgeo->lineN = nnn;
				tmpgeo->checkflag = 0;
			}
			else
			{
				tmpgeo = itormapCircle->second;
			}

			//tmpgeo->checkflag += 2;
			tmpgeo->Line_colour[0] = TempLine_colour[0];
			tmpgeo->Line_colour[1] = TempLine_colour[1];
			tmpgeo->Line_colour[2] = TempLine_colour[2];
			tmpgeo->width = TempLine_width;
			tmpgeo->line_type_Segment = TempLine_ltype->Segment;
			for (int iia = 0; iia < tmpgeo->line_type_Segment; iia++)
				tmpgeo->line_type_Pitch[iia] = TempLine_ltype->Pitch[iia];

			return 1;

		}
		if (!strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "ELLIPSE"))
		{
			kos_Ellipse* tmpgeo = NULL;

			map<long, kos_Ellipse*>::iterator itormapCircle;
			itormapCircle = Ellipse_List.find(nnn);
			if (itormapCircle == Ellipse_List.end())
			{
				tmpgeo = new kos_Ellipse();
				Ellipse_List.insert(pair<long, kos_Ellipse*>(nnn, tmpgeo));
				tmpgeo->lineN = nnn;
				tmpgeo->checkflag = 0;
			}
			else
			{
				tmpgeo = itormapCircle->second;
			}

			tmpgeo->Line_colour[0] = TempLine_colour[0];
			tmpgeo->Line_colour[1] = TempLine_colour[1];
			tmpgeo->Line_colour[2] = TempLine_colour[2];
			tmpgeo->width = TempLine_width;
			tmpgeo->line_type_Segment = TempLine_ltype->Segment;
			for (int iia = 0; iia < tmpgeo->line_type_Segment; iia++)
				tmpgeo->line_type_Pitch[iia] = TempLine_ltype->Pitch[iia];

			return 1;
		}

		//Arc
		if (!strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "TRIMMED_CURVE"))
		{

			map<long, kosEntityVVA*>::iterator itormap4;
			itormap4 = m_EntityMapA.find(getStrNumInt((itormap1->second->cvvec[1]).cvalue));
			CString str01 = (itormap1->second->cvvec[2]).ccvec[0];
			CString str02 = (itormap1->second->cvvec[3]).ccvec[0];

			CString tempstrA[6];
			CString tempstrB[3];
			Split(str01, tempstrA, '(');
			Split(tempstrA[1], tempstrB, ')');
			float ff1 = atof(tempstrB[0]) / Pi * 180.0f;

			Split(str02, tempstrA, '(');
			Split(tempstrA[1], tempstrB, ')');
			float ff2 = atof(tempstrB[0]) / Pi * 180.0f;

			int LArraw = 1;

			if (!strcmp((itormap1->second->cvvec[4]).cvalue, ".T."))
			{
				LArraw = 0;
			}

			if (!strcmp(m_EntityNamevector[itormap4->second->dvalue].c_str(), "CIRCLE"))
			{
				kos_Arc* tmpgeo = NULL;
				//kos_Arc* tmpgeo = new kos_Arc();

				map<long, kos_Arc*>::iterator itormapCircle;
				itormapCircle = ArcList.find(nnn);
				if (itormapCircle == ArcList.end())
				{
					tmpgeo = new kos_Arc();
					ArcList.insert(pair<long, kos_Arc*>(nnn, tmpgeo));
					tmpgeo->lineN = nnn;
					tmpgeo->checkflag = 0;
				}
				else
				{
					tmpgeo = itormapCircle->second;
				}

				tmpgeo->Line_colour[0] = TempLine_colour[0];
				tmpgeo->Line_colour[1] = TempLine_colour[1];
				tmpgeo->Line_colour[2] = TempLine_colour[2];
				tmpgeo->width = TempLine_width;
				tmpgeo->line_type_Segment = TempLine_ltype->Segment;
				for (int iia = 0; iia < tmpgeo->line_type_Segment; iia++)
					tmpgeo->line_type_Pitch[iia] = TempLine_ltype->Pitch[iia];
			}
			if (!strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "ELLIPSE"))
			{
				AfxMessageBox("ELLIPSE");

			}
			return 1;
		}

		if (!strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "COMPOSITE_CURVE")) //#42=COMPOSITE_CURVE('',(#17,#18,#19,#20,#21,#22),.U.);
		{

			map<long, kosEntityVVA*>::iterator itormap2;
			for (int iia = 0; iia < (itormap1->second->cvvec[1]).ccvecNum; iia++)
			{
				if ((itormap1->second->cvvec[1]).ccvecNum == 1)
					if (!strcmp((itormap1->second->cvvec[1]).ccvec[iia], ""))
						break;
				itormap2 = m_EntityMapA.find(getStrNumInt((itormap1->second->cvvec[1]).ccvec[iia]));

				map<long, kosEntityVVA*>::iterator itormap3;
				itormap3 = m_EntityMapA.find(getStrNumInt((itormap2->second->cvvec[2]).cvalue));
				int nn1 = getStrNumInt((itormap1->second->cvvec[1]).ccvec[iia]);
				if (!strcmp(m_EntityNamevector[itormap3->second->dvalue].c_str(), "POLYLINE"))
				{
					kos_Polyline* tmpgeo = NULL;

					map<long, kos_Polyline*>::iterator itormapPolyline;
					itormapPolyline = Polyline_List.find(nn1);
					if (itormapPolyline == Polyline_List.end())
					{
						tmpgeo = new kos_Polyline();
						Polyline_List.insert(pair<long, kos_Polyline*>(nn1, tmpgeo));
						tmpgeo->lineN = nnn;
						tmpgeo->checkflag = 0;
					}
					else
					{
						tmpgeo = itormapPolyline->second;
					}
					//tmpgeo->checkflag += 2;
					tmpgeo->Line_colour[0] = TempLine_colour[0];
					tmpgeo->Line_colour[1] = TempLine_colour[1];
					tmpgeo->Line_colour[2] = TempLine_colour[2];
					tmpgeo->width = TempLine_width;
					tmpgeo->line_type_Segment = TempLine_ltype->Segment;
					for (int iia = 0; iia < tmpgeo->line_type_Segment; iia++)
						tmpgeo->line_type_Pitch[iia] = TempLine_ltype->Pitch[iia];
				}
				//arc
				int nn2 = getStrNumInt((itormap1->second->cvvec[1]).ccvec[iia]);
				if (!strcmp(m_EntityNamevector[itormap3->second->dvalue].c_str(), "TRIMMED_CURVE"))
				{

					map<long, kosEntityVVA*>::iterator itormap4;
					itormap4 = m_EntityMapA.find(getStrNumInt((itormap3->second->cvvec[1]).cvalue));

					CString str01 = (itormap3->second->cvvec[2]).ccvec[0];
					CString str02 = (itormap3->second->cvvec[3]).ccvec[0];

					CString tempstrA[6];
					CString tempstrB[3];
					Split(str01, tempstrA, '(');
					Split(tempstrA[1], tempstrB, ')');
					float ff1 = atof(tempstrB[0]) / Pi * 180.0f;

					Split(str02, tempstrA, '(');
					Split(tempstrA[1], tempstrB, ')');
					float ff2 = atof(tempstrB[0]) / Pi * 180.0f;

					int LArraw = 1;

					if (!strcmp((itormap3->second->cvvec[4]).cvalue, ".T."))
					{
						LArraw = 0;
					}

					if (!strcmp(m_EntityNamevector[itormap4->second->dvalue].c_str(), "CIRCLE"))
					{
						kos_Arc* tmpgeo = NULL;

						map<long, kos_Arc*>::iterator itormapCircle;
						itormapCircle = ArcList.find(nn2);
						if (itormapCircle == ArcList.end())
						{
							tmpgeo = new kos_Arc();
							ArcList.insert(pair<long, kos_Arc*>(nn2, tmpgeo));
							tmpgeo->lineN = nnn;
							tmpgeo->checkflag = 0;
						}
						else
						{
							tmpgeo = itormapCircle->second;
						}
						tmpgeo->Line_colour[0] = TempLine_colour[0];
						tmpgeo->Line_colour[1] = TempLine_colour[1];
						tmpgeo->Line_colour[2] = TempLine_colour[2];
						tmpgeo->width = TempLine_width;
						tmpgeo->line_type_Segment = TempLine_ltype->Segment;
						for (int iia = 0; iia < tmpgeo->line_type_Segment; iia++)
							tmpgeo->line_type_Pitch[iia] = TempLine_ltype->Pitch[iia];
					}
				}
			}
		}
		return 1;
	}

	return 0;
}

int kos_loader::get_GEOMETRIC_CURVE_SET(long nnn, TiXmlElement* nownode, Placement* currpos, long oldlevel)
{
	map<long, kosEntityVVA*>::iterator itormap0;
	itormap0 = m_EntityMapA.find(oldlevel);
	if (itormap0 == m_EntityMapA.end())
		return 0;

	map<long, kosEntityVVA*>::iterator itormap1;
	itormap1 = m_EntityMapA.find(nnn);
	if (itormap1 == m_EntityMapA.end())
		return 0;

	if (!strcmp(m_EntityNamevector[itormap0->second->dvalue].c_str(), "GEOMETRIC_CURVE_SET") || !strcmp(m_EntityNamevector[itormap0->second->dvalue].c_str(), "etc"))
	{
		if (!strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "LINE"))
		{
			cnt_POLYLINE++;
			kos_Polyline* tmpgeo = NULL;

			map<long, kos_Polyline*>::iterator itormapPolyline;
			itormapPolyline = Line_List.find(nnn);
			if (itormapPolyline == Line_List.end())
			{
				//tmpgeo = new kos_Polyline();
				//Polyline_List.insert(pair<long, kos_Polyline*>(nnn, tmpgeo));
				//tmpgeo->lineN = nnn;
				//tmpgeo->checkflag = 0;
				return 0;
			}
			else
			{
				tmpgeo = itormapPolyline->second;
			}
			tmpgeo->Vertex.clear();
			{
				long ddddd = getStrNumInt((itormap1->second->cvvec[1]).cvalue);
				float* abc = getpoint(ddddd);
				tmpgeo->Vertex.push_back(abc[0]);
				tmpgeo->Vertex.push_back(abc[1]);
			}
			{
				long ddddd = getStrNumInt((itormap1->second->cvvec[2]).cvalue);
				float* abc = getpoint(ddddd);
				tmpgeo->Vertex.push_back(abc[0]);
				tmpgeo->Vertex.push_back(abc[1]);
			}

			tmpgeo->checkflag += 1;
			tmpgeo->transform[0] = currpos->position[0];
			tmpgeo->transform[1] = currpos->position[1];
			tmpgeo->transform[2] = currpos->rotation;
			tmpgeo->transform[3] = currpos->scale[0];
			tmpgeo->transform[4] = currpos->scale[1];

			CString buf1;
			CString buf2;
			TiXmlElement* nownode0;

			buf1.Format("%f", tmpgeo->transform[0]);
			buf2.Format("%f", tmpgeo->transform[1] * -1.0f);
			TiXmlElement* node01 = new TiXmlElement("g");
			node01->SetAttribute("transform", "translate(" + buf1 + "," + buf2 + ")");
			m_pnode2->LinkEndChild(node01);

			nownode0 = node01;

			TiXmlElement* node02 = new TiXmlElement("g");
			float fff = tmpgeo->transform[2];
			buf1.Format("rotate(%f)", fff);
			node02->SetAttribute("transform", buf1);
			nownode0->LinkEndChild(node02);
			nownode0 = node02;

			TiXmlElement* node03 = new TiXmlElement("g");
			buf1.Format("scale(%f,%f)", tmpgeo->transform[3], tmpgeo->transform[4]);
			node03->SetAttribute("transform", buf1);
			nownode0->LinkEndChild(node03);
			nownode0 = node03;


			CString tmps = "";
			CString tmps1 = "";
			CString tmps2 = "";
			CString tmps3 = "";

			for (int iia = 0; iia < tmpgeo->Vertex.size(); iia += 2) {
				if (iia == 0)
					tmps1.Format("%f,%f", tmpgeo->Vertex[iia], tmpgeo->Vertex[iia + 1] * -1.0f);
				else
					tmps1.Format(" %f,%f", tmpgeo->Vertex[iia], tmpgeo->Vertex[iia + 1] * -1.0f);
				tmps = tmps + tmps1;
			}

			TiXmlElement* node04 = new TiXmlElement("polyline ");
			node04->SetAttribute("points", tmps);

			tmps2.Format("rgb(%d,%d,%d)", (int)(tmpgeo->Line_colour[0] * 255), (int)(tmpgeo->Line_colour[1] * 255), (int)(tmpgeo->Line_colour[2] * 255));
			tmps3.Format("%f", (tmpgeo->width) * 10.0 + 1);
			// <polygon id = "s1" points = "60,0 120,0 180,60 180,120 120,180 60,180 0,120 0,60" fill = "none" stroke = "black" stroke-width = "3"/>
			node04->SetAttribute("fill", "none");
			node04->SetAttribute("stroke", tmps2);
			node04->SetAttribute("stroke-width", tmps3);
			node04->SetAttribute("vector-effect", "non-scaling-stroke");

			CString tmps4 = "";
			CString tmps5 = "";
			for (int iia = 0; iia < tmpgeo->line_type_Segment; iia += 2) {
				if (iia == 0)
					tmps4.Format("%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
				else
					tmps4.Format(",%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
				tmps5 = tmps5 + tmps4;
			}
			if (tmpgeo->line_type_Pitch[0] != 0)
				node04->SetAttribute("stroke-dasharray", tmps5);
			nownode0->LinkEndChild(node04);

			cnt_PRESENTATION_STYLE_ASSIGNMENT++;
			return 1;


		}
		if (!strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "POLYLINE"))
		{
			cnt_POLYLINE++;
			kos_Polyline* tmpgeo = NULL;

			map<long, kos_Polyline*>::iterator itormapPolyline;
			itormapPolyline = Polyline_List.find(nnn);
			if (itormapPolyline == Polyline_List.end())
			{
				//tmpgeo = new kos_Polyline();
				//Polyline_List.insert(pair<long, kos_Polyline*>(nnn, tmpgeo));
				//tmpgeo->lineN = nnn;
				//tmpgeo->checkflag = 0;
				return 0;
			}
			else
			{
				tmpgeo = itormapPolyline->second;
			}
			tmpgeo->Vertex.clear();
			map<long, kosEntityVVA*>::iterator itormap2;
			for (int iia = 0; iia < (itormap1->second->cvvec[1]).ccvecNum; iia++) {
				long ddddd = getStrNumInt((itormap1->second->cvvec[1]).ccvec[iia]);
				//itormap2 = m_EntityMapA.find(ddddd);
				float* abc = getpoint(ddddd);
				tmpgeo->Vertex.push_back(abc[0]);
				tmpgeo->Vertex.push_back(abc[1]);
			}

			tmpgeo->checkflag += 1;
			tmpgeo->transform[0] = currpos->position[0];
			tmpgeo->transform[1] = currpos->position[1];
			tmpgeo->transform[2] = currpos->rotation;
			tmpgeo->transform[3] = currpos->scale[0];
			tmpgeo->transform[4] = currpos->scale[1];

			CString buf1;
			CString buf2;
			TiXmlElement* nownode0;

			buf1.Format("%f", tmpgeo->transform[0]);
			buf2.Format("%f", tmpgeo->transform[1] * -1.0f);
			TiXmlElement* node01 = new TiXmlElement("g");
			node01->SetAttribute("transform", "translate(" + buf1 + "," + buf2 + ")");
			m_pnode2->LinkEndChild(node01);

			nownode0 = node01;

			TiXmlElement* node02 = new TiXmlElement("g");
			float fff = tmpgeo->transform[2];
			buf1.Format("rotate(%f)", fff);
			node02->SetAttribute("transform", buf1);
			nownode0->LinkEndChild(node02);
			nownode0 = node02;

			TiXmlElement* node03 = new TiXmlElement("g");
			buf1.Format("scale(%f,%f)", tmpgeo->transform[3], tmpgeo->transform[4]);
			node03->SetAttribute("transform", buf1);
			nownode0->LinkEndChild(node03);
			nownode0 = node03;


			CString tmps = "";
			CString tmps1 = "";
			CString tmps2 = "";
			CString tmps3 = "";

			for (int iia = 0; iia < tmpgeo->Vertex.size(); iia += 2) {
				if (iia == 0)
					tmps1.Format("%f,%f", tmpgeo->Vertex[iia], tmpgeo->Vertex[iia + 1] * -1.0f);
				else
					tmps1.Format(" %f,%f", tmpgeo->Vertex[iia], tmpgeo->Vertex[iia + 1] * -1.0f);
				tmps = tmps + tmps1;
			}

			TiXmlElement* node04 = new TiXmlElement("polyline ");
			node04->SetAttribute("points", tmps);

			tmps2.Format("rgb(%d,%d,%d)", (int)(tmpgeo->Line_colour[0] * 255), (int)(tmpgeo->Line_colour[1] * 255), (int)(tmpgeo->Line_colour[2] * 255));
			tmps3.Format("%f", (tmpgeo->width) * 10.0 + 1);
			// <polygon id = "s1" points = "60,0 120,0 180,60 180,120 120,180 60,180 0,120 0,60" fill = "none" stroke = "black" stroke-width = "3"/>
			node04->SetAttribute("fill", "none");
			node04->SetAttribute("stroke", tmps2);
			node04->SetAttribute("stroke-width", tmps3);
			node04->SetAttribute("vector-effect", "non-scaling-stroke");

			CString tmps4 = "";
			CString tmps5 = "";
			for (int iia = 0; iia < tmpgeo->line_type_Segment; iia += 2) {
				if (iia == 0)
					tmps4.Format("%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
				else
					tmps4.Format(",%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
				tmps5 = tmps5 + tmps4;
			}
			if (tmpgeo->line_type_Pitch[0] != 0)
				node04->SetAttribute("stroke-dasharray", tmps5);
			nownode0->LinkEndChild(node04);

			cnt_PRESENTATION_STYLE_ASSIGNMENT++;
			return 1;


		}

		if (!strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "CIRCLE"))
		{
			cnt_CIRCLE++;
			kos_Circle* tmpgeo = NULL;

			map<long, kos_Circle*>::iterator itormapCircle;
			itormapCircle = Circle_List.find(nnn);
			if (itormapCircle == Circle_List.end())
			{
			}
			else
			{
				tmpgeo = itormapCircle->second;
			}

			tmpgeo->checkflag += 1;
			tmpgeo->transform[0] = currpos->position[0];
			tmpgeo->transform[1] = currpos->position[1];
			tmpgeo->transform[2] = currpos->rotation;
			tmpgeo->transform[3] = currpos->scale[0];
			tmpgeo->transform[4] = currpos->scale[1];
			tmpgeo->Radius = atof(itormap1->second->cvvec[2].cvalue);

			map<long, kosEntityVVA*>::iterator itormap2;
			itormap2 = m_EntityMapA.find(getStrNumInt((itormap1->second->cvvec[1]).cvalue));
			float* abc = getpoint(getStrNumInt((itormap2->second->cvvec[1]).cvalue));
			tmpgeo->Center_point = new float[2];
			tmpgeo->Center_point[0] = abc[0];
			tmpgeo->Center_point[1] = abc[1];

			CString buf1;
			CString buf2;
			TiXmlElement* nownode0;

			buf1.Format("%f", tmpgeo->transform[0]);
			buf2.Format("%f", tmpgeo->transform[1] * -1.0f);
			TiXmlElement* node01 = new TiXmlElement("g");
			node01->SetAttribute("transform", "translate(" + buf1 + "," + buf2 + ")");
			m_pnode2->LinkEndChild(node01);

			nownode0 = node01;

			TiXmlElement* node02 = new TiXmlElement("g");
			float fff = tmpgeo->transform[2];
			buf1.Format("rotate(%f)", fff);
			node02->SetAttribute("transform", buf1);
			nownode0->LinkEndChild(node02);
			nownode0 = node02;

			TiXmlElement* node03 = new TiXmlElement("g");
			buf1.Format("scale(%f,%f)", tmpgeo->transform[3], tmpgeo->transform[4]);
			node03->SetAttribute("transform", buf1);
			nownode0->LinkEndChild(node03);
			nownode0 = node03;


			CString tmps = "";
			CString tmps1 = "";
			CString tmps2 = "";
			CString tmps3 = "";

			TiXmlElement* node04 = new TiXmlElement("circle");
			node04->SetAttribute("cx", tmpgeo->Center_point[0]);
			node04->SetAttribute("cy", tmpgeo->Center_point[1] * -1.0f);
			node04->SetAttribute("r", tmpgeo->Radius);


			tmps2.Format("rgb(%d,%d,%d)", (int)(tmpgeo->Line_colour[0] * 255), (int)(tmpgeo->Line_colour[1] * 255), (int)(tmpgeo->Line_colour[2] * 255));
			tmps3.Format("%f", (tmpgeo->width) * 10.0 + 1);
			// <polygon id = "s1" points = "60,0 120,0 180,60 180,120 120,180 60,180 0,120 0,60" fill = "none" stroke = "black" stroke-width = "3"/>
			node04->SetAttribute("fill", "none");
			node04->SetAttribute("stroke", tmps2);
			node04->SetAttribute("stroke-width", tmps3);
			node04->SetAttribute("vector-effect", "non-scaling-stroke");
			CString tmps4 = "";
			CString tmps5 = "";
			for (int iia = 0; iia < tmpgeo->line_type_Segment; iia += 2) {
				if (iia == 0)
					tmps4.Format("%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
				else
					tmps4.Format(",%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
				tmps5 = tmps5 + tmps4;
			}
			if (tmpgeo->line_type_Pitch[0] != 0)
				node04->SetAttribute("stroke-dasharray", tmps5);

			nownode0->LinkEndChild(node04);

			return 1;

		}
		if (!strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "ELLIPSE"))
		{
			cnt_ELLIPSE++;
			kos_Ellipse* tmpgeo = NULL;

			map<long, kos_Ellipse*>::iterator itormapCircle;
			itormapCircle = Ellipse_List.find(nnn);
			if (itormapCircle == Ellipse_List.end())
			{
			}
			else
			{
				tmpgeo = itormapCircle->second;
			}


			tmpgeo->transform[0] = currpos->position[0];
			tmpgeo->transform[1] = currpos->position[1];
			tmpgeo->transform[2] = currpos->rotation;
			tmpgeo->transform[3] = currpos->scale[0];
			tmpgeo->transform[4] = currpos->scale[1];

			tmpgeo->Radius_x = atof(itormap1->second->cvvec[2].cvalue);
			tmpgeo->Radius_y = atof(itormap1->second->cvvec[3].cvalue);

			map<long, kosEntityVVA*>::iterator itormap2;
			itormap2 = m_EntityMapA.find(getStrNumInt((itormap1->second->cvvec[1]).cvalue));
			float* pos = getpoint(getStrNumInt((itormap2->second->cvvec[1]).cvalue));
			float* dir = getpoint(getStrNumInt((itormap2->second->cvvec[2]).cvalue));
			tmpgeo->Center_point = new float[2];
			tmpgeo->Center_point[0] = pos[0];
			tmpgeo->Center_point[1] = pos[1];

			float ang_d = CalAngleXbase(dir[0], dir[1]);
			// ���� ���� �ʿ�
			tmpgeo->Rotation = ang_d;
			tmpgeo->Center_point[0] = pos[0];
			tmpgeo->Center_point[1] = pos[1];

			CString buf1;
			CString buf2;
			TiXmlElement* nownode0;

			buf1.Format("%f", tmpgeo->transform[0]);
			buf2.Format("%f", tmpgeo->transform[1] * -1.0f);
			TiXmlElement* node01 = new TiXmlElement("g");
			node01->SetAttribute("transform", "translate(" + buf1 + "," + buf2 + ")");
			m_pnode2->LinkEndChild(node01);

			nownode0 = node01;

			TiXmlElement* node02 = new TiXmlElement("g");
			float fff = tmpgeo->transform[2];
			buf1.Format("rotate(%f)", fff);
			node02->SetAttribute("transform", buf1);
			nownode0->LinkEndChild(node02);
			nownode0 = node02;

			TiXmlElement* node03 = new TiXmlElement("g");
			buf1.Format("scale(%f,%f)", tmpgeo->transform[3], tmpgeo->transform[4]);
			node03->SetAttribute("transform", buf1);
			nownode0->LinkEndChild(node03);
			nownode0 = node03;


			CString tmps = "";
			CString tmps1 = "";
			CString tmps2 = "";
			CString tmps3 = "";


			TiXmlElement* node04 = new TiXmlElement("ellipse ");
			node04->SetAttribute("cx", tmpgeo->Center_point[0]);
			node04->SetAttribute("cy", tmpgeo->Center_point[1] * -1.0f);
			node04->SetAttribute("rx", tmpgeo->Radius_x);
			node04->SetAttribute("ry", tmpgeo->Radius_y);

			tmps1.Format("rotate(%f,%f,%f)", tmpgeo->Rotation * -1.0f, tmpgeo->Center_point[0], tmpgeo->Center_point[1] * -1.0f);

			node04->SetAttribute("transform", tmps1);


			tmps2.Format("rgb(%d,%d,%d)", (int)(tmpgeo->Line_colour[0] * 255), (int)(tmpgeo->Line_colour[1] * 255), (int)(tmpgeo->Line_colour[2] * 255));
			tmps3.Format("%f", (tmpgeo->width) * 10.0 + 1);
			// <polygon id = "s1" points = "60,0 120,0 180,60 180,120 120,180 60,180 0,120 0,60" fill = "none" stroke = "black" stroke-width = "3"/>
			node04->SetAttribute("fill", "none");
			node04->SetAttribute("stroke", tmps2);
			node04->SetAttribute("stroke-width", tmps3);
			node04->SetAttribute("vector-effect", "non-scaling-stroke");
			CString tmps4 = "";
			CString tmps5 = "";
			for (int iia = 0; iia < tmpgeo->line_type_Segment; iia += 2) {
				if (iia == 0)
					tmps4.Format("%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
				else
					tmps4.Format(",%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
				tmps5 = tmps5 + tmps4;
			}
			if (tmpgeo->line_type_Pitch[0] != 0)
				node04->SetAttribute("stroke-dasharray", tmps5);

			nownode0->LinkEndChild(node04);

			return 1;
		}
		//Arc
		if (!strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "TRIMMED_CURVE"))
		{
			cnt_TRIMMED_CURVE++;
			map<long, kosEntityVVA*>::iterator itormap4;
			itormap4 = m_EntityMapA.find(getStrNumInt((itormap1->second->cvvec[1]).cvalue));
			CString str01 = (itormap1->second->cvvec[2]).ccvec[0];
			CString str02 = (itormap1->second->cvvec[3]).ccvec[0];

			CString tempstrA[6];
			CString tempstrB[3];
			Split(str01, tempstrA, '(');
			Split(tempstrA[1], tempstrB, ')');
			float ff1 = atof(tempstrB[0]) / Pi * 180.0f;

			Split(str02, tempstrA, '(');
			Split(tempstrA[1], tempstrB, ')');
			float ff2 = atof(tempstrB[0]) / Pi * 180.0f;

			int LArraw = 1;

			if (!strcmp((itormap1->second->cvvec[4]).cvalue, ".T."))
			{
				LArraw = 0;
			}

			if (!strcmp(m_EntityNamevector[itormap4->second->dvalue].c_str(), "CIRCLE"))
			{
				kos_Arc* tmpgeo = NULL;

				map<long, kos_Arc*>::iterator itormapCircle;
				itormapCircle = ArcList.find(nnn);
				if (itormapCircle == ArcList.end())
				{
					tmpgeo = new kos_Arc();
					ArcList.insert(pair<long, kos_Arc*>(nnn, tmpgeo));
					tmpgeo->lineN = nnn;
					tmpgeo->checkflag = 0;
				}
				else
				{
					tmpgeo = itormapCircle->second;
				}

				tmpgeo->transform[0] = currpos->position[0];
				tmpgeo->transform[1] = currpos->position[1];
				tmpgeo->transform[2] = currpos->rotation;
				tmpgeo->transform[3] = currpos->scale[0];
				tmpgeo->transform[4] = currpos->scale[1];

				tmpgeo->Radius = atof(itormap4->second->cvvec[2].cvalue);

				map<long, kosEntityVVA*>::iterator itormap5;
				itormap5 = m_EntityMapA.find(getStrNumInt((itormap4->second->cvvec[1]).cvalue));
				float* pos = getpoint(getStrNumInt((itormap5->second->cvvec[1]).cvalue));
				float* dir = getpoint(getStrNumInt((itormap5->second->cvvec[2]).cvalue));
				tmpgeo->Center_point = new float[2];
				tmpgeo->Center_point[0] = pos[0];
				tmpgeo->Center_point[1] = pos[1];
				tmpgeo->Start_angle = ff1;
				tmpgeo->End_angle = ff2;
				tmpgeo->LArraw = LArraw;

				tmpgeo->Rotation[1] = dir[0];
				tmpgeo->Rotation[2] = dir[1];

				float ang_d = CalAngleXbase(tmpgeo->Rotation[1], tmpgeo->Rotation[2]);
				tmpgeo->Rotation[0] = ang_d;

				CString buf1;
				CString buf2;
				TiXmlElement* nownode0;

				buf1.Format("%f", tmpgeo->transform[0]);
				buf2.Format("%f", tmpgeo->transform[1] * -1.0f);
				TiXmlElement* node01 = new TiXmlElement("g");
				node01->SetAttribute("transform", "translate(" + buf1 + "," + buf2 + ")");
				m_pnode2->LinkEndChild(node01);

				nownode0 = node01;

				TiXmlElement* node02 = new TiXmlElement("g");
				float fff = tmpgeo->transform[2];
				buf1.Format("rotate(%f)", fff);
				node02->SetAttribute("transform", buf1);
				nownode0->LinkEndChild(node02);
				nownode0 = node02;

				TiXmlElement* node03 = new TiXmlElement("g");
				buf1.Format("scale(%f,%f)", tmpgeo->transform[3], tmpgeo->transform[4]);
				node03->SetAttribute("transform", buf1);
				nownode0->LinkEndChild(node03);
				nownode0 = node03;

				kPoint kpos;
				kpos.x = tmpgeo->Rotation[1];
				kpos.y = tmpgeo->Rotation[2];
				kPoint base;
				base.x = 0;
				base.y = 0;
				kPoint pp1 = RotateCoordinate(kpos, tmpgeo->Start_angle, base);
				kPoint pp2 = RotateCoordinate(kpos, tmpgeo->End_angle, base);

				pp1 = MultiCoordinate(pp1, tmpgeo->Radius);
				pp2 = MultiCoordinate(pp2, tmpgeo->Radius);


				pp1.x += tmpgeo->Center_point[0];
				pp1.y += tmpgeo->Center_point[1];
				pp2.x += tmpgeo->Center_point[0];
				pp2.y += tmpgeo->Center_point[1];

				CString tmps = "";
				tmps.Format("M%f,%f a%f,%f %f", pp1.x, pp1.y * -1.0f, tmpgeo->Radius, tmpgeo->Radius, tmpgeo->Rotation[0]);
				CString tmps1 = "";
				CString tmps2 = "";
				CString tmps3 = "";
				int largev = 0;
				if (tmpgeo->LArraw == 0) {
					if (tmpgeo->End_angle > tmpgeo->Start_angle) {
						largev = ((tmpgeo->End_angle - tmpgeo->Start_angle) > 180) ? 1 : 0;
					}
					else
					{
						largev = ((tmpgeo->End_angle + 360 - tmpgeo->Start_angle) > 180) ? 1 : 0;
					}
				}
				else
				{
					if (tmpgeo->End_angle < tmpgeo->Start_angle) {
						largev = ((tmpgeo->Start_angle - tmpgeo->End_angle) > 180) ? 1 : 0;
					}
					else
					{
						largev = ((tmpgeo->Start_angle + 360 - tmpgeo->End_angle) > 180) ? 1 : 0;

					}
				}

				tmps1.Format(" %d,%d %f,%f", largev, tmpgeo->LArraw, pp2.x - pp1.x, (pp2.y - pp1.y) * -1.0f);
				TiXmlElement* node04 = new TiXmlElement("path");
				node04->SetAttribute("d", tmps + tmps1);

				tmps2.Format("rgb(%d,%d,%d)", (int)(tmpgeo->Line_colour[0] * 255), (int)(tmpgeo->Line_colour[1] * 255), (int)(tmpgeo->Line_colour[2] * 255));
				tmps3.Format("%f", (tmpgeo->width) * 10.0 + 1);
				// <polygon id = "s1" points = "60,0 120,0 180,60 180,120 120,180 60,180 0,120 0,60" fill = "none" stroke = "black" stroke-width = "3"/>
				node04->SetAttribute("fill", "none");
				node04->SetAttribute("stroke", tmps2);
				node04->SetAttribute("stroke-width", tmps3);
				node04->SetAttribute("vector-effect", "non-scaling-stroke");
				CString tmps4 = "";
				CString tmps5 = "";
				for (int iia = 0; iia < tmpgeo->line_type_Segment; iia += 2) {
					if (iia == 0)
						tmps4.Format("%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
					else
						tmps4.Format(",%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
					tmps5 = tmps5 + tmps4;
				}
				if (tmpgeo->line_type_Pitch[0] != 0)
					node04->SetAttribute("stroke-dasharray", tmps5);
				nownode0->LinkEndChild(node04);


			}
			if (!strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "ELLIPSE"))
			{
				AfxMessageBox("ELLIPSE");

			}
			return 1;
		}

		if (!strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "COMPOSITE_CURVE")) //#42=COMPOSITE_CURVE('',(#17,#18,#19,#20,#21,#22),.U.);
		{
			cnt_COMPOSITE_CURVE++;
			map<long, kosEntityVVA*>::iterator itormap2;
			for (int iia = 0; iia < (itormap1->second->cvvec[1]).ccvecNum; iia++)
			{
				if ((itormap1->second->cvvec[1]).ccvecNum == 1)
					if (!strcmp((itormap1->second->cvvec[1]).ccvec[iia], ""))
						break;
				itormap2 = m_EntityMapA.find(getStrNumInt((itormap1->second->cvvec[1]).ccvec[iia]));

				map<long, kosEntityVVA*>::iterator itormap3;
				itormap3 = m_EntityMapA.find(getStrNumInt((itormap2->second->cvvec[2]).cvalue));
				int nn1 = getStrNumInt((itormap1->second->cvvec[1]).ccvec[iia]);
				if (!strcmp(m_EntityNamevector[itormap3->second->dvalue].c_str(), "POLYLINE"))
				{
					kos_Polyline* tmpgeo = NULL;

					map<long, kos_Polyline*>::iterator itormapPolyline;
					itormapPolyline = Polyline_List.find(nn1);
					if (itormapPolyline == Polyline_List.end())
					{
						//tmpgeo = new kos_Polyline();
						//Polyline_List.insert(pair<long, kos_Polyline*>(nn1, tmpgeo));
						//tmpgeo->lineN = nnn;
						//tmpgeo->checkflag = 0;
					}
					else
					{
						tmpgeo = itormapPolyline->second;
					}
					tmpgeo->Vertex.clear();
					map<long, kosEntityVVA*>::iterator itormap4;
					for (int iia = 0; iia < (itormap3->second->cvvec[1]).ccvecNum; iia++) {
						long ddddd = getStrNumInt((itormap3->second->cvvec[1]).ccvec[iia]);
						//itormap2 = m_EntityMapA.find(ddddd);
						float* abc = getpoint(ddddd);
						tmpgeo->Vertex.push_back(abc[0]);
						tmpgeo->Vertex.push_back(abc[1]);
					}

					tmpgeo->transform[0] = currpos->position[0];
					tmpgeo->transform[1] = currpos->position[1];
					tmpgeo->transform[2] = currpos->rotation;
					tmpgeo->transform[3] = currpos->scale[0];
					tmpgeo->transform[4] = currpos->scale[1];

					CString buf1;
					CString buf2;
					TiXmlElement* nownode0;

					buf1.Format("%f", tmpgeo->transform[0]);
					buf2.Format("%f", tmpgeo->transform[1] * -1.0f);
					TiXmlElement* node01 = new TiXmlElement("g");
					node01->SetAttribute("transform", "translate(" + buf1 + "," + buf2 + ")");
					m_pnode2->LinkEndChild(node01);

					nownode0 = node01;

					TiXmlElement* node02 = new TiXmlElement("g");
					float fff = tmpgeo->transform[2];
					buf1.Format("rotate(%f)", fff);
					node02->SetAttribute("transform", buf1);
					nownode0->LinkEndChild(node02);
					nownode0 = node02;

					TiXmlElement* node03 = new TiXmlElement("g");
					buf1.Format("scale(%f,%f)", tmpgeo->transform[3], tmpgeo->transform[4]);
					node03->SetAttribute("transform", buf1);
					nownode0->LinkEndChild(node03);
					nownode0 = node03;


					CString tmps = "";
					CString tmps1 = "";
					CString tmps2 = "";
					CString tmps3 = "";

					for (int iia = 0; iia < tmpgeo->Vertex.size(); iia += 2) {
						if (iia == 0)
							tmps1.Format("%f,%f", tmpgeo->Vertex[iia], tmpgeo->Vertex[iia + 1] * -1.0f);
						else
							tmps1.Format(" %f,%f", tmpgeo->Vertex[iia], tmpgeo->Vertex[iia + 1] * -1.0f);
						tmps = tmps + tmps1;
					}

					TiXmlElement* node04 = new TiXmlElement("polyline ");
					node04->SetAttribute("points", tmps);

					tmps2.Format("rgb(%d,%d,%d)", (int)(tmpgeo->Line_colour[0] * 255), (int)(tmpgeo->Line_colour[1] * 255), (int)(tmpgeo->Line_colour[2] * 255));
					tmps3.Format("%f", (tmpgeo->width) * 10.0 + 1);
					// <polygon id = "s1" points = "60,0 120,0 180,60 180,120 120,180 60,180 0,120 0,60" fill = "none" stroke = "black" stroke-width = "3"/>
					node04->SetAttribute("fill", "none");
					node04->SetAttribute("stroke", tmps2);
					node04->SetAttribute("stroke-width", tmps3);
					node04->SetAttribute("vector-effect", "non-scaling-stroke");

					CString tmps4 = "";
					CString tmps5 = "";
					for (int iia = 0; iia < tmpgeo->line_type_Segment; iia += 2) {
						if (iia == 0)
							tmps4.Format("%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
						else
							tmps4.Format(",%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
						tmps5 = tmps5 + tmps4;
					}
					if (tmpgeo->line_type_Pitch[0] != 0)
						node04->SetAttribute("stroke-dasharray", tmps5);
					nownode0->LinkEndChild(node04);

					cnt_PRESENTATION_STYLE_ASSIGNMENT++;


				}
				//arc
				int nn2 = getStrNumInt((itormap1->second->cvvec[1]).ccvec[iia]);
				if (!strcmp(m_EntityNamevector[itormap3->second->dvalue].c_str(), "TRIMMED_CURVE"))
				{

					map<long, kosEntityVVA*>::iterator itormap4;
					itormap4 = m_EntityMapA.find(getStrNumInt((itormap3->second->cvvec[1]).cvalue));


					CString str01 = (itormap3->second->cvvec[2]).ccvec[0];
					CString str02 = (itormap3->second->cvvec[3]).ccvec[0];

					CString tempstrA[6];
					CString tempstrB[3];
					Split(str01, tempstrA, '(');
					Split(tempstrA[1], tempstrB, ')');
					float ff1 = atof(tempstrB[0]) / Pi * 180.0f;

					Split(str02, tempstrA, '(');
					Split(tempstrA[1], tempstrB, ')');
					float ff2 = atof(tempstrB[0]) / Pi * 180.0f;

					int LArraw = 1;

					if (!strcmp((itormap3->second->cvvec[4]).cvalue, ".T."))
					{
						LArraw = 0;
					}

					if (!strcmp(m_EntityNamevector[itormap4->second->dvalue].c_str(), "CIRCLE"))
					{
						kos_Arc* tmpgeo = NULL;

						map<long, kos_Arc*>::iterator itormapCircle;
						itormapCircle = ArcList.find(nn2);
						if (itormapCircle == ArcList.end())
						{
							//tmpgeo = new kos_Arc();
							//ArcList.insert(pair<long, kos_Arc*>(nn2, tmpgeo));
							//tmpgeo->lineN = nnn;
							//tmpgeo->checkflag = 0;
						}
						else
						{
							tmpgeo = itormapCircle->second;
						}

						tmpgeo->transform[0] = currpos->position[0];
						tmpgeo->transform[1] = currpos->position[1];
						tmpgeo->transform[2] = currpos->rotation;
						tmpgeo->transform[3] = currpos->scale[0];
						tmpgeo->transform[4] = currpos->scale[1];

						tmpgeo->Radius = atof(itormap4->second->cvvec[2].cvalue);

						map<long, kosEntityVVA*>::iterator itormap5;
						itormap5 = m_EntityMapA.find(getStrNumInt((itormap4->second->cvvec[1]).cvalue));
						float* pos = getpoint(getStrNumInt((itormap5->second->cvvec[1]).cvalue));
						float* dir = getpoint(getStrNumInt((itormap5->second->cvvec[2]).cvalue));
						tmpgeo->Center_point = new float[2];
						tmpgeo->Center_point[0] = pos[0];
						tmpgeo->Center_point[1] = pos[1];
						tmpgeo->Start_angle = ff1;
						tmpgeo->End_angle = ff2;
						tmpgeo->LArraw = LArraw;

						tmpgeo->Rotation[1] = dir[0];
						tmpgeo->Rotation[2] = dir[1];

						float ang_d = CalAngleXbase(tmpgeo->Rotation[1], tmpgeo->Rotation[2]);
						tmpgeo->Rotation[0] = ang_d;

						CString buf1;
						CString buf2;
						TiXmlElement* nownode0;

						buf1.Format("%f", tmpgeo->transform[0]);
						buf2.Format("%f", tmpgeo->transform[1] * -1.0f);
						TiXmlElement* node01 = new TiXmlElement("g");
						node01->SetAttribute("transform", "translate(" + buf1 + "," + buf2 + ")");
						m_pnode2->LinkEndChild(node01);

						nownode0 = node01;

						TiXmlElement* node02 = new TiXmlElement("g");
						float fff = tmpgeo->transform[2];
						buf1.Format("rotate(%f)", fff);
						node02->SetAttribute("transform", buf1);
						nownode0->LinkEndChild(node02);
						nownode0 = node02;

						TiXmlElement* node03 = new TiXmlElement("g");
						buf1.Format("scale(%f,%f)", tmpgeo->transform[3], tmpgeo->transform[4]);
						node03->SetAttribute("transform", buf1);
						nownode0->LinkEndChild(node03);
						nownode0 = node03;

						kPoint kpos;
						kpos.x = tmpgeo->Rotation[1];
						kpos.y = tmpgeo->Rotation[2];
						kPoint base;
						base.x = 0;
						base.y = 0;
						kPoint pp1 = RotateCoordinate(kpos, tmpgeo->Start_angle, base);
						kPoint pp2 = RotateCoordinate(kpos, tmpgeo->End_angle, base);

						pp1 = MultiCoordinate(pp1, tmpgeo->Radius);
						pp2 = MultiCoordinate(pp2, tmpgeo->Radius);


						pp1.x += tmpgeo->Center_point[0];
						pp1.y += tmpgeo->Center_point[1];
						pp2.x += tmpgeo->Center_point[0];
						pp2.y += tmpgeo->Center_point[1];

						CString tmps = "";
						tmps.Format("M%f,%f a%f,%f %f", pp1.x, pp1.y * -1.0f, tmpgeo->Radius, tmpgeo->Radius, tmpgeo->Rotation[0]);
						CString tmps1 = "";
						CString tmps2 = "";
						CString tmps3 = "";
						int largev = 0;
						if (tmpgeo->LArraw == 0) {
							if (tmpgeo->End_angle > tmpgeo->Start_angle) {
								largev = ((tmpgeo->End_angle - tmpgeo->Start_angle) > 180) ? 1 : 0;
							}
							else
							{
								largev = ((tmpgeo->End_angle + 360 - tmpgeo->Start_angle) > 180) ? 1 : 0;
							}
						}
						else
						{
							if (tmpgeo->End_angle < tmpgeo->Start_angle) {
								largev = ((tmpgeo->Start_angle - tmpgeo->End_angle) > 180) ? 1 : 0;
							}
							else
							{
								largev = ((tmpgeo->Start_angle + 360 - tmpgeo->End_angle) > 180) ? 1 : 0;

							}
						}

						tmps1.Format(" %d,%d %f,%f", largev, tmpgeo->LArraw, pp2.x - pp1.x, (pp2.y - pp1.y) * -1.0f);
						TiXmlElement* node04 = new TiXmlElement("path");
						node04->SetAttribute("d", tmps + tmps1);

						tmps2.Format("rgb(%d,%d,%d)", (int)(tmpgeo->Line_colour[0] * 255), (int)(tmpgeo->Line_colour[1] * 255), (int)(tmpgeo->Line_colour[2] * 255));
						tmps3.Format("%f", (tmpgeo->width) * 10.0 + 1);
						// <polygon id = "s1" points = "60,0 120,0 180,60 180,120 120,180 60,180 0,120 0,60" fill = "none" stroke = "black" stroke-width = "3"/>
						node04->SetAttribute("fill", "none");
						node04->SetAttribute("stroke", tmps2);
						node04->SetAttribute("stroke-width", tmps3);
						node04->SetAttribute("vector-effect", "non-scaling-stroke");
						CString tmps4 = "";
						CString tmps5 = "";
						for (int iia = 0; iia < tmpgeo->line_type_Segment; iia += 2) {
							if (iia == 0)
								tmps4.Format("%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
							else
								tmps4.Format(",%f,%f", tmpgeo->line_type_Pitch[iia + 0], tmpgeo->line_type_Pitch[iia + 1]);
							tmps5 = tmps5 + tmps4;
						}
						if (tmpgeo->line_type_Pitch[0] != 0)
							node04->SetAttribute("stroke-dasharray", tmps5);
						nownode0->LinkEndChild(node04);
					}
				}
			}
			return 1;

		}
	}
	return 0;

}

void kos_loader::get_layer()
{
	int tmp = -1;
	multimap<long, long>::iterator iter;
	for (iter = Presentation_layer_assignment.begin(); iter != Presentation_layer_assignment.end(); ++iter)
	{

		if (tmp == iter->first)
			continue;
		tmp = iter->first;

		kos_layer* tmp_layer = new kos_layer();

		map<long, kosEntityVVA*>::iterator itormap;
		itormap = m_EntityMapA.find(tmp);
		if (itormap == m_EntityMapA.end())
			return;
		tmp_layer->Name = itormap->second->cvvec[0].cvalue;


		map<long, long>::iterator iterm1;
		for (iterm1 = Layer_properties.begin(); iterm1 != Layer_properties.end(); ++iterm1) {
			if (tmp == iterm1->first)
				break;
		}
		int tmp1 = iterm1->second;

		map<long, kosEntityVVA*>::iterator itormap1;
		itormap1 = m_EntityMapA.find(tmp1);
		if (itormap1 == m_EntityMapA.end())
			return;
		tmp_layer->Blocked = (itormap1->second->cvvec[0].cvalue == ".T.") ? true : false;
		tmp_layer->On = (itormap1->second->cvvec[4].cvalue == ".T.") ? true : false;
		tmp_layer->On_in_all_views = (itormap1->second->cvvec[5].cvalue == ".T.") ? true : false;
		tmp_layer->Layer_number = getStrNumInt(itormap1->second->cvvec[5].cvalue);
		///

		multimap<long, long>::iterator itorSSmap2;
		for (itorSSmap2 = Layer_style_assignment.lower_bound(tmp1); itorSSmap2 != Layer_style_assignment.upper_bound(tmp1); ++itorSSmap2)
		{
			int tmp2 = itorSSmap2->second;
			map<long, kosEntityVVA*>::iterator itormap2;
			itormap2 = m_EntityMapA.find(tmp2);
			if (itormap2 == m_EntityMapA.end())
				return;
			if (!strcmp(m_EntityNamevector[itormap2->second->dvalue].c_str(), "CURVE_STYLE"))
			{
				//CString nameN=itormap2->second->cvvec[0];
				//int curve_fontN=
				//int curve_widthN=
				int curve_style = getStrNumInt(itormap2->second->cvvec[1].cvalue);
				//	kos_User_defined_line_type *ltype = get_linetype(curve_style);

				//	tmp_layer->line_type_Name = ltype->Name;
				//	tmp_layer->line_type_Segment = ltype->Segment;
				//	for (int iia = 0; iia < ltype->Segment; iia++) {
				//		tmp_layer->line_type_Pitch[iia] = ltype->Pitch[iia];
				//	}
				//	int curve_colorN = getStrNumInt(itormap2->second->cvvec[3].cvalue);
				//	tmp_layer->Line_colour = get_Color(curve_colorN);
			}
		}
	}
}

int kos_loader::get_TEXT_LITERAL(long nnn, int levelN, TiXmlElement* nownode, Placement* oldpos, long oldlevel)
{
	if (nnn == 1154)
		nnn = 1154;
	map<long, kosEntityVVA*>::iterator itormap1;
	itormap1 = m_EntityMapA.find(nnn);
	if (itormap1 == m_EntityMapA.end())
		return 0;
	if (strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "etc"))
		return 0;

	for (int inn = 0; inn < itormap1->second->ect_content.size(); inn++)
	{

		if (!strcmp(itormap1->second->ect_content[inn].c_str(), "TEXT_LITERAL"))
		{
			cnt_TEXT++;

			kos_Text_string* ktstr = new kos_Text_string();

			//	ktstr->Str = itormap1->second->cvvec[1].cvalue;

			if (!strcmp(itormap1->second->cvvec[1].cvalue, ""))
				ktstr->Str = "";
			else {
				convXC(itormap1->second->cvvec[1].cvalue);
				ktstr->Str.Format("%s", itormap1->second->cvvec[1].cvalue);
				//		tempTreeData->sFBSName=_T(itormap->second->cvvec[2].cvalue);
			}

			ktstr->Adjust = itormap1->second->cvvec[3].cvalue;

			CString alignment = "baseline";
			if (ktstr->Adjust.Find("baseline") > -1)
				alignment = "baseline";
			if (ktstr->Adjust.Find("middleline") > -1)
				alignment = "middleline";

			CString anchor = "start";
			if (ktstr->Adjust.Find("left") > -1)
				anchor = "start";
			if (ktstr->Adjust.Find("centre") > -1)
				anchor = "middle";
			if (ktstr->Adjust.Find("right") > -1)
				anchor = "end";

			ktstr->Path = itormap1->second->cvvec[4].cvalue;

			map<long, kosEntityVVA*>::iterator itormap2;
			itormap2 = m_EntityMapA.find(getStrNumInt((itormap1->second->cvvec[6]).cvalue));
			float boxsize[2];
			boxsize[0] = atof((itormap2->second->cvvec[1]).cvalue);
			boxsize[1] = atof((itormap2->second->cvvec[2]).cvalue);


			itormap2 = m_EntityMapA.find(getStrNumInt((itormap1->second->cvvec[2]).cvalue));
			float* pos = getpoint(getStrNumInt((itormap2->second->cvvec[1]).cvalue));
			float* dir = getpoint(getStrNumInt((itormap2->second->cvvec[2]).cvalue));
			ktstr->Location[0] = pos[0];
			ktstr->Location[1] = pos[1];
			ktstr->Rotation = CalAngleXbase(dir[0], dir[1]) * -1.0f;

			m_pnode3 = new TiXmlElement("text");
			convXC(ktstr->Str);
			m_pnode3->LinkEndChild(new TiXmlText(ktstr->Str));
			m_pnode3->SetAttribute("x", ktstr->Location[0]);
			m_pnode3->SetAttribute("y", ktstr->Location[1] * -1.0f);

			CString tmps1 = "";
			//		 tmps1.Format("translate(%f,%f)",ktstr->Location[0]*-1, ktstr->Location[1]*-1);
			//		 m_pnode3->SetAttribute("transform", tmps1);
			tmps1.Format("rotate(%f,%f,%f)", ktstr->Rotation, ktstr->Location[0], ktstr->Location[1] * -1.0f);
			m_pnode3->SetAttribute("transform", tmps1);
			//		 m_pnode3->SetAttribute("transform","scale(1 -1)");
			CString tmps2 = "";
			tmps2.Format("%f", boxsize[1] * 1.2);
			m_pnode3->SetAttribute("font-size", tmps2);
			//m_pnode3->SetAttribute("text-anchor", anchor);
			//m_pnode3->SetAttribute("alignment-baseline", alignment);
			m_pnode3->SetAttribute("font-family", "Gulim");

			tmps2.Format("rgb(%d,%d,%d)", (int)(TempLine_colour[0] * 255), (int)(TempLine_colour[1] * 255), (int)(TempLine_colour[2] * 255));
			m_pnode3->SetAttribute("fill", tmps2);
			//node04->SetAttribute("stroke", tmps2);

			nownode->LinkEndChild(m_pnode3);


			CString str00 = "";
			CString str01 = "";
			for (int ii = 0; ii < levelN - 1; ii++) {
				str00 += "    ";
			}
			str01.Format("-text- %s POS %f,%f DIR %f,%f SCALE %f \n", ktstr->Str.GetBuffer().c_str(), pos[0], pos[1], dir[0], dir[1], boxsize[1]);
			str00 += str01;
			writeFile.write(str00, str00.GetLength());
			break;
		}
	}
	return 0;
}



int kos_loader::get_TEXT_LITERAL_WITH_EXTENT(long nnn, int levelN, TiXmlElement* nownode, Placement* oldpos, long oldlevel)
{

	map<long, kosEntityVVA*>::iterator itormap1;
	itormap1 = m_EntityMapA.find(nnn);
	if (itormap1 == m_EntityMapA.end())
		return 0;
	if (strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "TEXT_LITERAL_WITH_EXTENT"))
		return 0;

	cnt_TEXT++;

	//for (int ii0 = 0; ii0 < (itormap0->second->cvvec[1]).ccvecNum; ii0++)
	{

		kos_Text_string* ktstr = new kos_Text_string();

		//	ktstr->Str = itormap1->second->cvvec[1].cvalue;

		if (!strcmp(itormap1->second->cvvec[1].cvalue, ""))
			ktstr->Str = "";
		else {
			convXC(itormap1->second->cvvec[1].cvalue);
			ktstr->Str.Format("%s", itormap1->second->cvvec[1].cvalue);
			//		tempTreeData->sFBSName=_T(itormap->second->cvvec[2].cvalue);
		}

		ktstr->Adjust = itormap1->second->cvvec[3].cvalue;

		CString alignment = "baseline";
		if (ktstr->Adjust.Find("baseline") > -1)
			alignment = "baseline";
		if (ktstr->Adjust.Find("middleline") > -1)
			alignment = "middleline";

		CString anchor = "start";
		if (ktstr->Adjust.Find("left") > -1)
			anchor = "start";
		if (ktstr->Adjust.Find("centre") > -1)
			anchor = "middle";
		if (ktstr->Adjust.Find("right") > -1)
			anchor = "end";

		ktstr->Path = itormap1->second->cvvec[4].cvalue;

		map<long, kosEntityVVA*>::iterator itormap2;
		itormap2 = m_EntityMapA.find(getStrNumInt((itormap1->second->cvvec[6]).cvalue));
		float boxsize[2];
		boxsize[0] = atof((itormap2->second->cvvec[1]).cvalue);
		boxsize[1] = atof((itormap2->second->cvvec[2]).cvalue);


		itormap2 = m_EntityMapA.find(getStrNumInt((itormap1->second->cvvec[2]).cvalue));
		float* pos = getpoint(getStrNumInt((itormap2->second->cvvec[1]).cvalue));
		float* dir = getpoint(getStrNumInt((itormap2->second->cvvec[2]).cvalue));
		ktstr->Location[0] = pos[0];
		ktstr->Location[1] = pos[1];
		ktstr->Rotation = CalAngleXbase(dir[0], dir[1]) * -1.0f;

		m_pnode3 = new TiXmlElement("text");
		convXC(ktstr->Str);
		m_pnode3->LinkEndChild(new TiXmlText(ktstr->Str));
		m_pnode3->SetAttribute("x", ktstr->Location[0]);
		m_pnode3->SetAttribute("y", ktstr->Location[1] * -1.0f);

		CString tmps1 = "";
		//		 tmps1.Format("translate(%f,%f)",ktstr->Location[0]*-1, ktstr->Location[1]*-1);
		//		 m_pnode3->SetAttribute("transform", tmps1);
		tmps1.Format("rotate(%f,%f,%f)", ktstr->Rotation, ktstr->Location[0], ktstr->Location[1] * -1.0f);
		m_pnode3->SetAttribute("transform", tmps1);
		//		 m_pnode3->SetAttribute("transform","scale(1 -1)");
		CString tmps2 = "";
		tmps2.Format("%f", boxsize[1] * 1.2);
		m_pnode3->SetAttribute("font-size", tmps2);
		m_pnode3->SetAttribute("text-anchor", anchor);
		m_pnode3->SetAttribute("alignment-baseline", alignment);
		m_pnode3->SetAttribute("font-family", "Gulim");

		tmps2.Format("rgb(%d,%d,%d)", (int)(TempLine_colour[0] * 255), (int)(TempLine_colour[1] * 255), (int)(TempLine_colour[2] * 255));
		m_pnode3->SetAttribute("fill", tmps2);
		//node04->SetAttribute("stroke", tmps2);

		nownode->LinkEndChild(m_pnode3);


		CString str00 = "";
		CString str01 = "";
		for (int ii = 0; ii < levelN - 1; ii++) {
			str00 += "    ";
		}
		str01.Format("-text- %s POS %f,%f DIR %f,%f SCALE %f \n", ktstr->Str.GetBuffer().c_str(), pos[0], pos[1], dir[0], dir[1], boxsize[1]);
		str00 += str01;
		writeFile.write(str00, str00.GetLength());

	}
	return 0;
}


void kos_loader::convX2C(char* ssrc, char* res) {
	/*strcpy(res, ssrc);
	return;*/

	int strN = strlen(ssrc);
	wchar_t unichar;
	int wcharN = (strN) / 4;
	int countN = 0;
	wchar_t* wstr = new wchar_t[wcharN + 1];
	for (int ii = 0; ii < strN; ii += 4) {
		char stra01[5];
		char stra02[5];
		int hexx1[2];
		stra01[0] = '0'; stra01[1] = 'x'; stra01[2] = ssrc[ii + 0]; stra01[3] = ssrc[ii + 1]; stra01[4] = '\0';
		stra02[0] = '0'; stra02[1] = 'x'; stra02[2] = ssrc[ii + 2]; stra02[3] = ssrc[ii + 3]; stra02[4] = '\0';
		hexx1[1] = strtol(stra01, NULL, 16);
		hexx1[0] = strtol(stra02, NULL, 16);
		byte aaaa[2];
		aaaa[0] = hexx1[0];
		aaaa[1] = hexx1[1];
		int iii = sizeof(wchar_t);
		memcpy(&unichar, aaaa, iii);
		wstr[countN] = unichar;
		countN++;

	}
	wstr[countN] = '\0';

	char* szStr = NULL;

	//int nSize = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, NULL, NULL, NULL);
	//szStr = new char[nSize];
	//memset(szStr, 0x00, nSize);
	//WideCharToMultiByte(CP_ACP, 0, wstr, -1, szStr, nSize, NULL, NULL);

	int nSize = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, NULL, NULL, NULL);
	szStr = new char[nSize];
	memset(szStr, 0x00, nSize);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &szStr, nSize, NULL, NULL);

	if (wstr)
	{
		strcpy(res, szStr);
		delete[] wstr;
		wstr = NULL;
	}

}
void kos_loader::convXC(char* ssrc)
{
	int strN = strlen(ssrc);
	int newN = 0;

	char* sstr = new char[strN + 2];
	if (NULL == sstr)
	{
		//	PopupErrorReport();
		return;
	}
	for (int ii = 0; ii < strN; ii++) {

		if (ii < strN - 8) {
			char tmpchr[1024];
			char tmpchr2[1024];

			if (ssrc[ii + 0] == '\\' && ssrc[ii + 1] == '\\' && ssrc[ii + 2] == 'X' && ssrc[ii + 3] == '2' && ssrc[ii + 4] == '\\' && ssrc[ii + 5] == '\\') {
				int cntN = 0;
				for (int kk = ii + 6; kk < strN - 5; kk++) {
					//				for(int kk = ii+4; kk <ii; kk++){
					if (ssrc[kk + 0] == '\\' && ssrc[kk + 1] == '\\' && ssrc[kk + 2] == 'X' && ssrc[kk + 3] == '0' && ssrc[kk + 4] == '\\' && ssrc[kk + 5] == '\\') {
						tmpchr[cntN] = '\0';
						convX2C(tmpchr, tmpchr2);
						sstr[newN] = '\0';
						int strlN = strlen(tmpchr2);
						strcat(sstr, tmpchr2);
						newN += strlN;
						ii = kk + 5;
						//ii = kk + 3;
						break;
					}
					tmpchr[cntN] = ssrc[kk];
					cntN++;

				}
				continue;
			}

		}
		else
			if (ii < strN - 3) {
				if (ssrc[ii] == '\\') {
					if (ssrc[ii + 1] == 'S') {
						if (ssrc[ii + 2] == '\\') {
							int hexx1 = 0;
							hexx1 = ssrc[ii + 3] + 128;
							ii += 3;
							sstr[newN++] = hexx1;
							continue;
						}
					}
				}
			}
			else
				if (ii < strN - 4) {
					if (ssrc[ii] == '\\') {
						if (ssrc[ii + 1] == 'X') {
							if (ssrc[ii + 2] == '\\') {
								int hexx1 = 0;
								int hexx2 = 0;
								if (ssrc[ii + 3] < 65) {
									hexx1 = ssrc[ii + 3] - 48;
								}
								else {
									hexx1 = ssrc[ii + 3] - 65 + 10;
								}
								if (ssrc[ii + 4] < 65) {
									hexx2 = ssrc[ii + 4] - 48;
								}
								else {
									hexx2 = ssrc[ii + 4] - 65 + 10;
								}
								ii += 4;
								sstr[newN++] = hexx1 * 16 + hexx2;

								continue;
							}
						}
					}
				}
		sstr[newN++] = ssrc[ii];
	}
	sstr[newN++] = '\0';

	strcpy_s(ssrc, strN + 1, sstr);
	delete[]sstr;

	//TRACE("sssssss[%s]\n",sstr);
}

void kos_loader::convXC(CString& ssrc)
{
	//int strN = ssrc.GetLength();
	//char* sstr = new char[strN + 2];
	//strcpy(sstr, ssrc);
	//convXC(sstr);
	//ssrc.Format("%s", sstr);
	//delete[]sstr;
}

char* kos_loader::MultiByte2utfs(const char* ssr)
{

	int size = MultiByteToWideChar(CP_ACP, 0, ssr, -1, 0, 0);

	wchar_t* wbuffer = new wchar_t[size];

	size = MultiByteToWideChar(CP_ACP, 0, ssr, -1, &wbuffer, size);
	char* restr = new char[size * 2 + 1];
	int cnt = WideCharToMultiByte(CP_UTF8, 0, wbuffer, -1, &restr, size * 2, NULL, NULL);
	restr[size * 2] = '\0';

	delete[] wbuffer;
	return restr;


}

char* kos_loader::MultiByte2utfs8(const char* ssr)
{
	// just return origin because error occured
	wchar_t* strUnicode = NULL;
	int nLen = MultiByteToWideChar(CP_ACP, 0, ssr, strlen(ssr), NULL, NULL);
	strUnicode = new wchar_t[nLen];
	memset(strUnicode, 0x0000, nLen);
	MultiByteToWideChar(CP_ACP, 0, ssr, strlen(ssr), &strUnicode, nLen + 2);
	strUnicode[nLen] = '\0';

	char* szStr = NULL;
	int nSize = WideCharToMultiByte(CP_UTF8, 0, strUnicode, -1, NULL, NULL, NULL, NULL);
	szStr = new char[nSize + 1];
	memset(szStr, 0x00, nSize);
	WideCharToMultiByte(CP_UTF8, 0, strUnicode, -1, &szStr, nSize, NULL, NULL);
	szStr[nSize] = '\0';
	return szStr;
}

int kos_loader::SubLevel(long nowlevel, int levelN, TiXmlElement* nownode, Placement* oldpos, long oldlevel)
{
	TiXmlElement* nownode0;
	nownode0 = nownode;
	map<long, kosEntityVVA*>::iterator itormap1;
	itormap1 = m_EntityMapA.find(nowlevel);
	if (itormap1 == m_EntityMapA.end())
		return 0;

	Placement* currpos = oldpos;

	//if (strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "STYLED_ITEM"))
	//	return 0;

	map<long, kosEntityVVA*>::iterator itormap2;

	//for (int ii = 0; ii < levelN; ii++) {
	//	TRACE("   ");
	//}
	//TRACE("-#%d=%s\n", nowlevel, m_EntityNamevector[itormap1->second->dvalue].c_str());

	CString str00 = "";
	CString str01 = "";
	for (int ii = 0; ii < levelN; ii++) {
		str00 += "    ";
	}

	if (strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "etc"))
	{
		str01.Format("-#%d=%s\n", nowlevel, m_EntityNamevector[itormap1->second->dvalue].c_str());
		str00 += str01;
		writeFile.write(str00, str00.GetLength());

	}
	else
	{

		CString str02 = "";
		for (int ii = 0; ii < itormap1->second->ect_content.size(); ii++) {
			str02 += itormap1->second->ect_content[ii].c_str();
		}


		str01.Format("-#%d=%s%s\n", nowlevel, m_EntityNamevector[itormap1->second->dvalue].c_str(), str02.GetBuffer().c_str());
		str00 += str01;
		writeFile.write(str00, str00.GetLength());


	}


	////
	////symbol_target




	for (int iia = 0; iia < itormap1->second->cvvecNum; iia++) {
		CString str1 = itormap1->second->cvvec[iia].cvalue;
		if (str1.GetAt(0) == '#')
		{
			map<long, kosEntityVVA*>::iterator itormap2;
			itormap2 = m_EntityMapA.find(getStrNumInt((itormap1->second->cvvec[iia]).cvalue));
			if (!strcmp(m_EntityNamevector[itormap2->second->dvalue].c_str(), "SYMBOL_TARGET"))
			{

				float scalex = atof((itormap2->second->cvvec[2]).cvalue);
				float scaley = atof((itormap2->second->cvvec[3]).cvalue);

				map<long, kosEntityVVA*>::iterator itormap3;
				itormap3 = m_EntityMapA.find(getStrNumInt((itormap2->second->cvvec[1]).cvalue));
				float* pos = getpoint(getStrNumInt((itormap3->second->cvvec[1]).cvalue));
				float* dir = getpoint(getStrNumInt((itormap3->second->cvvec[2]).cvalue));

				//for (int ii = 0; ii < levelN; ii++) {
				//	TRACE("   ");
				//}
				//TRACE("--POS %f,%f DIR %f,%f \n", pos[0], pos[1], dir[0], dir[1]);

				CString str00 = "";
				CString str01 = "";
				for (int ii = 0; ii < levelN - 1; ii++) {
					str00 += "    ";
				}
				str01.Format("--POS %f,%f DIR %f,%f \n", pos[0], pos[1], dir[0], dir[1]);
				str00 += str01;
				writeFile.write(str00, str00.GetLength());



				CString buf1;
				CString buf2;

				buf1.Format("%f", pos[0]);
				buf2.Format("%f", pos[1] * -1.0f);
				TiXmlElement* node01 = new TiXmlElement("g");
				node01->SetAttribute("transform", "translate(" + buf1 + "," + buf2 + ")");
				nownode0->LinkEndChild(node01);
				nownode0 = node01;

				TiXmlElement* node02 = new TiXmlElement("g");
				float fff = CalAngleXbase(dir[0], dir[1]) * -1.0f;
				buf1.Format("rotate(%f)", fff);
				node02->SetAttribute("transform", buf1);
				nownode0->LinkEndChild(node02);
				nownode0 = node02;

				TiXmlElement* node03 = new TiXmlElement("g");
				buf1.Format("scale(%f,%f)", scalex, scaley);
				node03->SetAttribute("transform", buf1);
				nownode0->LinkEndChild(node03);
				nownode0 = node03;

				currpos = new Placement();
				currpos->position[0] = pos[0];
				currpos->position[1] = pos[1];
				currpos->rotation = fff;
				currpos->scale[0] = scalex;
				currpos->scale[1] = scaley;

			}
			else
				if (!strcmp(m_EntityNamevector[itormap2->second->dvalue].c_str(), "AXIS2_PLACEMENT_2D00") && levelN > 4)
				{
					//map<long, kosEntityVVA*>::iterator itormap3;
					//itormap3 = m_EntityMapA.find(getStrNumInt((itormap2->second->cvvec[1]).cvalue));
					float* pos = getpoint(getStrNumInt((itormap2->second->cvvec[1]).cvalue));
					float* dir = getpoint(getStrNumInt((itormap2->second->cvvec[2]).cvalue));

					//for (int ii = 0; ii < levelN; ii++) {
					//	TRACE("   ");
					//}
					//TRACE("--POS %f,%f DIR %f,%f \n", pos[0], pos[1], dir[0], dir[1]);
					//
					CString str00 = "";
					CString str01 = "";
					for (int ii = 0; ii < levelN - 1; ii++) {
						str00 += "    ";
					}
					str01.Format("--POS %f,%f DIR %f,%f \n", pos[0], pos[1], dir[0], dir[1]);
					str00 += str01;
					writeFile.write(str00, str00.GetLength());

					CString buf1;
					CString buf2;

					buf1.Format("%f", pos[0]);
					buf2.Format("%f", pos[1] * -1.0f);
					TiXmlElement* node01 = new TiXmlElement("g");
					node01->SetAttribute("transform", "translate(" + buf1 + "," + buf2 + ")");
					nownode0->LinkEndChild(node01);
					nownode0 = node01;

					TiXmlElement* node02 = new TiXmlElement("g");
					float fff = CalAngleXbase(dir[0], dir[1]) * -1.0f;
					buf1.Format("rotate(%f)", fff);
					node02->SetAttribute("transform", buf1);
					nownode0->LinkEndChild(node02);
					nownode0 = node02;
				}
		}
	}
	//if (kos_loader::get_PRE_DEFINED_CURVE_FONT(nowlevel))
	//	;
	//if(  get_PRE_DEFINED_COLOUR( nowlevel))
	//;
	//if (kos_loader::get_CURVE_STYLE(nowlevel))
	//;
	if (get_GEOMETRIC_CURVE_SET(nowlevel, nownode0, currpos, oldlevel) == 1)
		return 1;
	//if (get_TEXT_LITERAL_WITH_EXTENT(nowlevel, levelN, nownode0, currpos, oldlevel) == 1)
	//	return 1;
	//if (get_TEXT_LITERAL(nowlevel, levelN, nownode0, currpos, oldlevel) == 1)
	//	return 1;

	//for (int iia = itormap1->second->cvvecNum - 1; iia > -1; iia--) {
	for (int iia = 0; iia < itormap1->second->cvvecNum; iia++) {
		CString str1 = itormap1->second->cvvec[iia].cvalue;
		if (str1.GetAt(0) == '#')
		{
			SubLevel(getStrNumInt(itormap1->second->cvvec[iia].cvalue), levelN + 1, nownode0, currpos, nowlevel);
		}
		for (int iib = 0; iib < itormap1->second->cvvec[iia].ccvecNum; iib++) {
			CString str2 = itormap1->second->cvvec[iia].ccvec[iib];
			if (str2.GetAt(0) == '#')
			{
				SubLevel(getStrNumInt(itormap1->second->cvvec[iia].ccvec[iib]), levelN + 1, nownode0, currpos, nowlevel);

			}
		}
	}

	return 0;
}
int kos_loader::SubLeveltext(long nowlevel, int levelN, TiXmlElement* nownode, Placement* oldpos, long oldlevel)
{
	TiXmlElement* nownode0;
	nownode0 = nownode;
	map<long, kosEntityVVA*>::iterator itormap1;
	itormap1 = m_EntityMapA.find(nowlevel);
	if (itormap1 == m_EntityMapA.end())
		return 0;

	Placement* currpos = oldpos;

	//if (strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "STYLED_ITEM"))
	//	return 0;

	map<long, kosEntityVVA*>::iterator itormap2;

	//for (int ii = 0; ii < levelN; ii++) {
	//	TRACE("   ");
	//}
	//TRACE("-#%d=%s\n", nowlevel, m_EntityNamevector[itormap1->second->dvalue].c_str());

	CString str00 = "";
	CString str01 = "";
	for (int ii = 0; ii < levelN; ii++) {
		str00 += "    ";
	}

	if (strcmp(m_EntityNamevector[itormap1->second->dvalue].c_str(), "etc"))
	{
		str01.Format("-#%d=%s\n", nowlevel, m_EntityNamevector[itormap1->second->dvalue].c_str());
		str00 += str01;
		writeFile.write(str00, str00.GetLength());

	}
	else
	{

		CString str02 = "";
		for (int ii = 0; ii < itormap1->second->ect_content.size(); ii++) {
			str02 += itormap1->second->ect_content[ii].c_str();
		}
		str01.Format("-#%d=%s%s\n", nowlevel, m_EntityNamevector[itormap1->second->dvalue].c_str(), str02.GetBuffer().c_str());
		str00 += str01;
		writeFile.write(str00, str00.GetLength());
	}





	for (int iia = 0; iia < itormap1->second->cvvecNum; iia++) {
		CString str1 = itormap1->second->cvvec[iia].cvalue;
		if (str1.GetAt(0) == '#')
		{
			map<long, kosEntityVVA*>::iterator itormap2;
			itormap2 = m_EntityMapA.find(getStrNumInt((itormap1->second->cvvec[iia]).cvalue));
			if (!strcmp(m_EntityNamevector[itormap2->second->dvalue].c_str(), "SYMBOL_TARGET"))
			{

				float scalex = atof((itormap2->second->cvvec[2]).cvalue);
				float scaley = atof((itormap2->second->cvvec[3]).cvalue);

				map<long, kosEntityVVA*>::iterator itormap3;
				itormap3 = m_EntityMapA.find(getStrNumInt((itormap2->second->cvvec[1]).cvalue));
				float* pos = getpoint(getStrNumInt((itormap3->second->cvvec[1]).cvalue));
				float* dir = getpoint(getStrNumInt((itormap3->second->cvvec[2]).cvalue));

				//for (int ii = 0; ii < levelN; ii++) {
				//	TRACE("   ");
				//}
				//TRACE("--POS %f,%f DIR %f,%f \n", pos[0], pos[1], dir[0], dir[1]);

				CString str00 = "";
				CString str01 = "";
				for (int ii = 0; ii < levelN - 1; ii++) {
					str00 += "    ";
				}
				str01.Format("--POS %f,%f DIR %f,%f \n", pos[0], pos[1], dir[0], dir[1]);
				str00 += str01;
				writeFile.write(str00, str00.GetLength());



				CString buf1;
				CString buf2;

				buf1.Format("%f", pos[0]);
				buf2.Format("%f", pos[1] * -1.0f);
				TiXmlElement* node01 = new TiXmlElement("g");
				node01->SetAttribute("transform", "translate(" + buf1 + "," + buf2 + ")");
				nownode0->LinkEndChild(node01);
				nownode0 = node01;

				TiXmlElement* node02 = new TiXmlElement("g");
				float fff = CalAngleXbase(dir[0], dir[1]) * -1.0f;
				buf1.Format("rotate(%f)", fff);
				node02->SetAttribute("transform", buf1);
				nownode0->LinkEndChild(node02);
				nownode0 = node02;

				TiXmlElement* node03 = new TiXmlElement("g");
				buf1.Format("scale(%f,%f)", scalex, scaley);
				node03->SetAttribute("transform", buf1);
				nownode0->LinkEndChild(node03);
				nownode0 = node03;

				currpos = new Placement();
				currpos->position[0] = pos[0];
				currpos->position[1] = pos[1];
				currpos->rotation = fff;
				currpos->scale[0] = scalex;
				currpos->scale[1] = scaley;

			}

		}
	}
	//if (kos_loader::get_PRE_DEFINED_CURVE_FONT(nowlevel))
	//	;
	//if(  get_PRE_DEFINED_COLOUR( nowlevel))
	//;
	//if (kos_loader::get_CURVE_STYLE(nowlevel))
	//;
	//if (get_GEOMETRIC_CURVE_SET(nowlevel, nownode0, currpos, oldlevel) == 1)
	//	return 1;
	if (get_TEXT_LITERAL_WITH_EXTENT(nowlevel, levelN, nownode0, currpos, oldlevel) == 1)
		return 1;
	if (get_TEXT_LITERAL(nowlevel, levelN, nownode0, currpos, oldlevel) == 1)
		return 1;

	//for (int iia = itormap1->second->cvvecNum - 1; iia > -1; iia--) {
	for (int iia = 0; iia < itormap1->second->cvvecNum; iia++) {
		CString str1 = itormap1->second->cvvec[iia].cvalue;
		if (str1.GetAt(0) == '#')
		{
			SubLeveltext(getStrNumInt(itormap1->second->cvvec[iia].cvalue), levelN + 1, nownode0, currpos, nowlevel);
		}
		for (int iib = 0; iib < itormap1->second->cvvec[iia].ccvecNum; iib++) {
			CString str2 = itormap1->second->cvvec[iia].ccvec[iib];
			if (str2.GetAt(0) == '#')
			{
				SubLeveltext(getStrNumInt(itormap1->second->cvvec[iia].ccvec[iib]), levelN + 1, nownode0, currpos, nowlevel);

			}
		}
	}

	return 0;
}

int kos_loader::SubLevel_item(long nowlevel, int levelN, TiXmlElement* nownode, Placement* oldpos, long oldlevel)
{
	TiXmlElement* nownode0;
	nownode0 = nownode;
	map<long, kosEntityVVA*>::iterator itormap1;
	itormap1 = m_EntityMapA.find(nowlevel);
	if (itormap1 == m_EntityMapA.end())
		return 0;

	Placement* currpos = oldpos;

	map<long, kosEntityVVA*>::iterator itormap2;


	CString str00 = "";
	CString str01 = "";
	for (int ii = 0; ii < levelN; ii++) {
		str00 += "    ";
	}
	str01.Format("item -#%d=%s\n", nowlevel, m_EntityNamevector[itormap1->second->dvalue].c_str());
	str00 += str01;
	writeFile.write(str00, str00.GetLength());

	if (get_PRE_DEFINED_CURVE_FONT(nowlevel))
		;
	if (get_PRE_DEFINED_COLOUR(nowlevel))
		;
	if (get_CURVE_STYLE(nowlevel))
		;
	if (get_PRESENTATION_STYLE_ASSIGNMENT(nowlevel, nownode0, currpos, oldlevel))
		;


	//for (int iia = itormap1->second->cvvecNum - 1; iia > -1; iia--) {
	for (int iia = 0; iia < itormap1->second->cvvecNum; iia++) {
		CString str1 = itormap1->second->cvvec[iia].cvalue;
		if (str1.GetAt(0) == '#')
		{
			SubLevel_item(getStrNumInt(itormap1->second->cvvec[iia].cvalue), levelN + 1, nownode0, currpos, nowlevel);
		}
		for (int iib = 0; iib < itormap1->second->cvvec[iia].ccvecNum; iib++) {
			CString str2 = itormap1->second->cvvec[iia].ccvec[iib];
			if (str2.GetAt(0) == '#')
			{
				SubLevel_item(getStrNumInt(itormap1->second->cvvec[iia].ccvec[iib]), levelN + 1, nownode0, currpos, nowlevel);

			}
		}
	}

	return 0;
}

float* kos_loader::getPresentation_view(long Presentation_view)
{

	map<long, kosEntityVVA*>::iterator itormap0;
	itormap0 = m_EntityMapA.find(Presentation_view);
	if (itormap0 == m_EntityMapA.end())

		if (!strcmp(itormap0->second->cvvec[1].ccvec[0], ""))
			return NULL;



	map<long, kosEntityVVA*>::iterator itormap1;
	itormap1 = m_EntityMapA.find(getStrNumInt(itormap0->second->cvvec[1].ccvec[0]));
	if (itormap1 == m_EntityMapA.end())
		return NULL;

	if (!strcmp(itormap1->second->cvvec[2].cvalue, ""))
		return NULL;

	map<long, kosEntityVVA*>::iterator itormap2;
	itormap2 = m_EntityMapA.find(getStrNumInt(itormap1->second->cvvec[2].cvalue));

	float boxsize[2];
	boxsize[0] = atof((itormap2->second->cvvec[1]).cvalue);
	boxsize[1] = atof((itormap2->second->cvvec[2]).cvalue);


	itormap2 = m_EntityMapA.find(getStrNumInt((itormap2->second->cvvec[3]).cvalue));
	float* pos = getpoint(getStrNumInt((itormap2->second->cvvec[1]).cvalue));
	float* dir = getpoint(getStrNumInt((itormap2->second->cvvec[2]).cvalue));
	float ang = CalAngleXbase(dir[0], dir[1]) * -1.0f;

	float* rev = new float[5];
	rev[0] = boxsize[0];
	rev[1] = boxsize[1];
	rev[2] = pos[0];
	rev[3] = pos[1];
	rev[4] = ang;

	return rev;
}
