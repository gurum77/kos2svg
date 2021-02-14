#pragma once

#include "WindowsToLinuxDefine.h"
#include "glMath.h"

#define MAX_LINE_KOS 10000000
using namespace std;

typedef char* charP;

class kos_layer {
public:
	CString Name;
	bool On;
	bool On_in_all_views;
	bool Blocked;
	bool Linewidth;

	bool Frozen;
	int Layer_number;

	CString Color;
	float* Line_colour;
	float* Fill_area_style_colour;

	CString line_type_Name;
	int line_type_Segment;
	float line_type_Pitch[28];



};

class kos_User_defined_colour_type {
public:
	CString Name;
	int Red;
	int Green;
	int Blue;
};

class kos_User_defined_line_type {
public:
	CString Name;
	int Segment;
	float Pitch[28];
};

class kos_Point_marker {
public:
	CString Layer_name;
	float* Location;
	float Rotate_angle;
	float Ratio_x;
	float Ratio_y;
	int Color[3];
	CString Marker_code;
	CString Paper_id;


};

class kos_Line {
public:
	int checkflag; // 0 X ,1tree , 2item, 3two 
	CString Layer_name;
	vector<float> Start_width;
	vector<float> End_width;
	vector<float> Vertex;
	vector<float> Bulge;
	CString Flag;
	CString Paper_id;

	int lineN;
	float width;
	float transform[5];
	float Line_colour[3];
	float Fill_area_style_colour[3];

	CString line_type_Name;
	int line_type_Segment;
	float line_type_Pitch[28];
};

class kos_Polyline {
public:
	int checkflag; // 0 X ,1tree , 2item, 3two 
	CString Layer_name;
	vector<float> Start_width;
	vector<float> End_width;
	vector<float> Vertex;
	vector<float> Bulge;
	CString Flag;
	CString Paper_id;

	int lineN;
	float width;
	float transform[5];
	float Line_colour[3];
	float Fill_area_style_colour[3];

	CString line_type_Name;
	int line_type_Segment;
	float line_type_Pitch[28];


};

class kos_Circle {
public:
	int checkflag; // 0 X ,1tree , 2item, 3two 
	CString Layer_name;
	float Color;
	int Linetype;
	float Width;
	float* Center_point;
	float Radius;
	CString Paper_id;

	int lineN;
	float width;
	float transform[5];
	float Line_colour[3];
	float Fill_area_style_colour[3];

	CString line_type_Name;
	int line_type_Segment;
	float line_type_Pitch[28];
};

class kos_Arc {
public:
	int checkflag; // 0 X ,1tree , 2item, 3two 
	CString Layer_name;
	float Color;
	int Linetype;
	float Width;
	float* Center_point;
	float Rotation[3];
	float Radius;
	float Start_angle;
	float End_angle;
	int LArraw;
	CString Paper_id;

	int lineN;
	float width;
	float transform[5];
	float Line_colour[3];
	float Fill_area_style_colour[3];

	CString line_type_Name;
	int line_type_Segment;
	float line_type_Pitch[28];
};



class kos_Ellipse {
public:
	int checkflag; // 0 X ,1tree , 2item, 3two 
	CString Layer_name;
	float Color;
	int Linetype;
	float Width;
	float* Center_point;
	float Radius_x;
	float Radius_y;
	float Rotation;
	CString Paper_id;

	int lineN;
	float width;
	float transform[5];
	float Line_colour[3];
	float Fill_area_style_colour[3];

	CString line_type_Name;
	int line_type_Segment;
	float line_type_Pitch[28];
};

class kos_Ellipse_Arc {
public:
	CString Layer_name;
	float Color;
	int Linetype;
	float Width;
	float* Center_point;
	float Radius_x;
	float Radius_y;
	float Rotation;
	float* Start_angle;
	float* End_angle;
	CString Paper_id;

	int lineN;
	float width;
	float transform[5];
	float Line_colour[3];
	float Fill_area_style_colour[3];

};

class kos_Spline {
public:
	CString Layer_name;
	int Color;
	int Linetype;
	float Width;
	int Order;
	int Number;
	float* Control_point;
	CString Paper_id;
};

class kos_Text_string {
public:
	CString Layer_name;
	CString Font_file;
	float Height;
	float Widthfactor;
	bool Filled;
	float Slant;
	float Spacing_gap;
	CString Mirror_type;
	CString Path;
	CString Adjust;
	float Location[2];
	float Rotation;
	int Color;
	CString Str;
	CString Style_name;
	float Str_width;
	float Str_height;
	CString Paper_id;

	int lineN;
	float width;
	float transform[5];
	float Line_colour[3];
	float Fill_area_style_colour[3];

};


class kos_Multi_text_string {
public:
	CString Layer_name;
	CString Font_file;
	float Height;
	float Widthfactor;
	bool Filled;
	float Slant;
	float Spacing_gap;
	CString Mirror_type;
	CString Path;
	CString Adjust;
	float Location[2];
	float Rotation;
	int Color;
	float Line_gap;
	CString* Strs;
	CString Style_name;
	float Str_width;
	float Str_height;
	float Total_width;
	float Total_height;
	CString Paper_id;
};


class kos_Subfigure_organization {
public:
	CString Name;
	int Number;
	int* Elements;
	float Standard_pt[2];
};


class kos_Subfigure_locate {
public:
	CString Layer_name;
	float Location[2];
	float Rotation;
	float Ratio_x;
	float Ratio_y;
	int Sfig;
	int Color;
	int Linetype;
	float Linewidth;
	CString Paper_id;
};

class kos_Externally_defined_symbol {
public:
	CString Layer_name;
	CString Name;
	float Location[2];
	float Rotate_angle;
	float Ratio_x;
	float Ratio_y;
	int Color;
	float* Segments;
	CString Paper_id;
};

class kos_Linear_dimension {
public:
	CString Layer_name;
	CString Dim_type;
	CString Font_file;
	float Height;
	float Widthfactor;
	bool Filled;
	float Slant;
	float Spacing_gap;
	CString Mirror_type;
	CString Path;
	CString Adjust;
	float Text_location[2];
	float Rotation;
	int Text_Color;
	CString Str;
	CString Text_style_name;
	float Str_width;
	float Str_height;
	CString Line_type;
	bool Flag;
	int Dim_Color;
	float Dim_start_pt[2];
	float Dim_end_pt[2];
	float Dim_pt_1[2];
	float Dim_pt_2[2];
	int Ext_Color;
	float Ext_width;
	bool Flag1;
	float Ext_line_1_pt_1[2];
	float Ext_line_1_pt_2[2];
	bool Flag2;
	float Ext_line_2_pt_1[2];
	float Ext_line_2_pt_2[2];

	float Arr1_scale;
	CString Arr1_code_1;
	CString* Arr1_list;
	CString Arr1_code_2;
	float Arr1_Location[2];

	float Arr2_scale;
	CString Arr2_code_1;
	CString* Arr2_list;
	CString Arr2_code_2;
	float Arr2_Location[2];
	float Proj_b_1_pt[2];
	float Proj_b_2_pt[2];

	CString Paper_id;
};

class kos_Angular_dimension {
public:
	CString Layer_name;
	CString Font_file;
	float Height;
	float Widthfactor;
	bool Filled;
	float Slant;
	float Spacing_gap;
	CString Mirror_type;
	CString Path;
	CString Adjust;
	float Text_location[2];
	float Rotation;
	int Text_Color;
	CString Str;
	CString Text_style_name;
	float Str_width;
	float Str_height;
	CString Line_type;
	bool Flag;
	int Dim_color;
	int Dim_width;
	float Center_origin_pt[2];
	float Radius;
	float Dim_start_angle;
	float Dim_end_angle;
	float Dim_angle_1;
	float Dim_angle_2;

	int Ext_Color;
	float Ext_width;
	bool Flag1;
	float Ext_line_1_pt_1[2];
	float Ext_line_1_pt_2[2];
	bool Flag2;
	float Ext_line_2_pt_1[2];
	float Ext_line_2_pt_2[2];

	float Arr1_scale;
	CString Arr1_code_1;
	CString* Arr1_list;
	CString Arr1_code_2;
	float Arr1_Location_angle;

	float Arr2_scale;
	CString Arr2_code_1;
	CString* Arr2_list;
	CString Arr2_code_2;
	float Arr2_Location_angle;

	float Proj_b_1_pt_1;
	float Proj_b_1_pt_2;
	float Proj_b_2_pt_1;
	float Proj_b_2_pt_2;

	CString Paper_id;
};


class kos_Radius_dimension {
public:
	CString Layer_name;
	CString Font_file;
	float Height;
	float Widthfactor;
	bool Filled;
	float Slant;
	float Spacing_gap;
	CString Mirror_type;
	CString Path;
	CString Adjust;
	float Text_location[2];
	float Rotation;
	int Text_Color;
	CString Str;
	CString Text_style_name;
	float Str_width;
	float Str_height;
	CString Line_type;
	bool Flag;
	int Dim_color;
	int Dim_width;
	float Dim_start_pt;
	float Dim_end_pt;
	float Dim_pt_1;
	float Dim_pt_2;

	float Arr1_scale;
	CString Arr1_code_1;
	CString* Arr1_list;
	CString Arr1_code_2;
	float Arr1_Location;
	float Center_pt[2];

	CString Paper_id;
};


class kos_Diameter_dimension {
public:
	CString Layer_name;
	CString Font_file;
	float Height;
	float Widthfactor;
	bool Filled;
	float Slant;
	float Spacing_gap;
	CString Mirror_type;
	CString Path;
	CString Adjust;
	float Text_location[2];
	float Rotation;
	int Text_Color;
	CString Str;
	CString Text_style_name;
	float Str_width;
	float Str_height;
	CString Line_type;
	bool Flag;
	int Dim_color;
	int Dim_width;
	float Dim_start_pt;
	float Dim_end_pt;
	float Dim_pt_1;
	float Dim_pt_2;

	float Arr1_scale;
	CString Arr1_code_1;
	CString* Arr1_list;
	CString Arr1_code_2;
	float Arr1_Location;
	float Arr2_scale;
	CString Arr2_code_1;
	CString* Arr2_list;
	CString Arr2_code_2;
	float Arr2_Location;

	float Center_pt[2];

	CString Paper_id;
};



class kos_Label_leader {
public:
	CString Layer_name;
	CString Font_file;
	float Height;
	float Widthfactor;
	bool Filled;
	float Slant;
	float Spacing_gap;
	CString Mirror_type;
	CString Path;
	CString Adjust;
	float Text_location[2];
	float Rotation;
	int Text_Color;
	CString Str;
	CString Text_style_name;
	float Str_width;
	float Str_height;
	CString Line_type;
	bool Flag;
	int Dim_color;
	int Dim_width;
	float Dim_start_pt;
	float Dim_end_pt;
	float Dim_pt_1;
	float Dim_pt_2;

	float Arr1_scale;
	CString Arr1_code_1;
	CString* Arr1_list;
	CString Arr1_code_2;
	float Arr1_Location;
	float Arr2_scale;
	CString Arr2_code_1;
	CString* Arr2_list;
	CString Arr2_code_2;
	float Arr2_Location;

	float Center_pt[2];

	CString Paper_id;
};





class kosCVV {
public:
	char* cvalue;
	vector<char*> ccvec;

	kosCVV() { cvalue = NULL; }
	~kosCVV() { cvalue = NULL; ccvec.clear(); }
};

class kosCVVA {
public:
	char* cvalue;
	charP* ccvec;	// 문자열의 리스트를 저장 할 이중포인터
	int ccvecNum;

	kosCVVA() { cvalue = NULL; ccvec = NULL; ccvecNum = 0; }
	~kosCVVA()
	{
		if (NULL != cvalue)
		{
			delete[] cvalue;
			cvalue = NULL;
		}

		if (NULL != ccvec)
		{
			for (int i = 0; i < ccvecNum; ++i)
			{
				delete[] ccvec[i];
				ccvec[i] = NULL;
			}
			delete[] ccvec;
			ccvec = NULL;
		}
	}
};


class kosEntityVV {
public:
	long dvalue;
	vector<kosCVV*> cvvec;
	BOOL bChecked;

	vector<string> ect_content;

	kosEntityVV() { dvalue = 0; bChecked = FALSE; }
	~kosEntityVV()
	{
		dvalue = 0;
		bChecked = FALSE;

		for (int i = 0; i < (int)cvvec.size(); ++i)
			delete cvvec[i];
		cvvec.clear();
		{//jslim : stl 클리어
			vector<kosCVV*> vcvvecClear;
			cvvec.swap(vcvvecClear);
		}
	}
};


class kosEntityVVA {
public:
	long dvalue;
	kosCVVA* cvvec;
	int cvvecNum;
	BOOL bChecked;

	vector<string> ect_content;

	kosEntityVVA() { dvalue = 0; cvvec = NULL; cvvecNum = 0; bChecked = FALSE; }
	~kosEntityVVA()
	{
		if (NULL != cvvec)
		{
			delete[] cvvec;
			cvvec = NULL;
		}
	}
};

class Placement {
public:
	float position[2];
	float rotation;
	float scale[2];
	Placement() {
		position[0] = 0.0f;
		position[1] = 0.0f;
		rotation = 0.0f;
		scale[0] = 1.0f;
		scale[1] = 1.0f;
	}
};

class kos_loader
{
public:
	HANDLE m_hMem;

	int m_SizeFile;			//파일 싸이즈
	char* m_pBuffer;		//파일에 따른 버퍼 싸이즈
	int m_IndexBuffer;		//파싱용 버퍼 1
	int m_IndexBuffer2;		//파싱용 버퍼 2
	CString m_FileName;		//파일명 
	CString m_FileNameOnly;		//파일명 
	char* m_pBufferLine;	//파싱용 공정라인버퍼[10000]
	map<long, kosEntityVVA*> m_EntityMapA; // 문자 파싱용 자료
	map<string, long> m_EntityNameMapSL;		//커맨드스트링 인덱스
	vector<string> m_EntityNamevector;			//커맨드 스트링 자료구조

/// Layer
	multimap< long, long> Presentation_layer_assignment;//인덱스
	multimap< long, long> 	DRAUGHTING_CALLOUT_RELATIONSHIP;//인덱스
	multimap< long, long> Layer_style_assignment;//인덱스
	map< long, long> Layer_properties;//인덱스

	vector< long> Text_literal_with_extent;//인덱스
	long Presentation_size;
	long Presentation_view;
	float* getPresentation_view(long Presentation_view);

	float  TempLine_colour[3];
	float  TempLine_width;
	float  TempFill_area_style_colour[3];
	kos_User_defined_line_type* TempLine_ltype;

	map< long, kos_Polyline*> Line_List;//인덱스
	map< long, kos_Polyline*> Polyline_List;//인덱스
	map< long, kos_Circle*> Circle_List;//인덱스
	map< long, kos_Ellipse*> Ellipse_List;//인덱스
	map< long, kos_Arc*> ArcList;//인덱스




	vector<string> m_PIarr;			//Project_Information
	vector<string> m_PAarr;			//Project_Additional_Information
	vector<string> m_EIarr;			//Employer_Information
	vector<string> m_CIarr;			//Contractor_Information
	vector<string> m_DParr;			//Drawing_Preview_Information

	vector<string> m_DIarr;			//Drawing_Index_Information
	vector<string> m_DAarr;			//Drawing_Additional_Information
	vector<string> m_DCarr;			//Drawing_Change_Information
	vector<string> m_FIarr;			//Facility_Information
	vector<string> m_UDarr;			//User_Defined_Information

	TiXmlDocument* m_doc;
	TiXmlElement* m_pnode1;
	TiXmlElement* m_pnode1_1;
	TiXmlElement* m_pnode2;
	TiXmlElement* m_pnode_Text;
	TiXmlElement* m_pnode3;

	ofstream writeFile;            //쓸 목적의 파일 선언
	ofstream write_log;            //쓸 목적의 파일 선언

	kos_loader(void);
	~kos_loader(void);

	void XmlPropertyExport();

	int Run(CString filename, CString pathonly, CString filenameonly);

	int ReadFile(CString filename);
	int ReadLine();
	int CountDef();
	int CheckVersion();
	float* getpoint(int nnn);
	void get_layer();
	bool  get_CURVE_STYLE(int nnn);
	bool  get_PRE_DEFINED_CURVE_FONT(int nnn);
	bool  get_PRE_DEFINED_COLOUR(int nnn);
	int get_GEOMETRIC_CURVE_SET(long nnn, TiXmlElement* nownode, Placement* currpos, long oldlevel);
	int get_PRESENTATION_STYLE_ASSIGNMENT(long nnn, TiXmlElement* nownode, Placement* currpos, long oldlevel);
	int cnt_PRESENTATION_STYLE_ASSIGNMENT;
	int get_TEXT_LITERAL_WITH_EXTENT(long nnn, int levelN, TiXmlElement* nownode, Placement* currpos, long oldlevel);

	int get_TEXT_LITERAL(long nnn, int levelN, TiXmlElement* nownode, Placement* currpos, long oldlevel);

	//float*  get_Color(int nnn);
	//kos_User_defined_line_type*  get_linetype(int nnn);


	void convXC(char* ssrc);
	void convXC(CString& ssrc);
	void convX2C(char* ssrc, char* res);


	int SubLevel_item(long nowlevel, int levelN, TiXmlElement* nownode, Placement* currpos, long oldlevel);
	int SubLevel(long nowlevel, int levelN, TiXmlElement* nownode, Placement* currpos, long oldlevel);
	int SubLeveltext(long nowlevel, int levelN, TiXmlElement* nownode, Placement* currpos, long oldlevel);

	char* MultiByte2utfs(const char* ssr);
	char* MultiByte2utfs8(const char* ssr);

	int cnt_TEXT;
	int cnt_COMPOSITE_CURVE;
	int cnt_TRIMMED_CURVE;
	int cnt_ELLIPSE;
	int cnt_CIRCLE;
	int cnt_POLYLINE;
};

