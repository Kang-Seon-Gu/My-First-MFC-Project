
// MFC_LOAN_FUNCTION_TESTDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC_LOAN_FUNCTION_TEST.h"
#include "MFC_LOAN_FUNCTION_TESTDlg.h"
#include "afxdialogex.h"
#include "math.h"
#include <locale.h>																// 한글 깨짐 해결 방안을 위한 헤더 파일 선언
#pragma once

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnRadioManager();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(IDC_RADIO_MANAGER, &CAboutDlg::OnRadioManager)
END_MESSAGE_MAP()


// CMFCLOANFUNCTIONTESTDlg 대화 상자



CMFCLOANFUNCTIONTESTDlg::CMFCLOANFUNCTIONTESTDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_LOAN_FUNCTION_TEST_DIALOG, pParent)
	, m_DTPLoan_Date(COleDateTime::GetCurrentTime())
	, m_strTotal_Refund_Money(_T(""))
	, m_strTotal_Refund_Original_Money(_T(""))
	, m_strTotal_Interest(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCLOANFUNCTIONTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_REFUND_METHOD, m_CBRefund_Method);
	DDX_Control(pDX, IDC_LIST_CONTROL_RESULT, m_CLCLoan_Result);
	DDX_Control(pDX, IDC_EDIT_LOAN_PERSON_NAME, m_CELoan_Person_Name);
	DDX_Control(pDX, IDC_LIST_CONTROL_RESULT_DETAIL, m_CLCLoan_Result_Detail);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_LOAN_DATE, m_DTPLoan_Date);
	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_Login_Button);
	DDX_Control(pDX, IDC_BUTTON_VIEW_DETAIL, m_View_Detail_Button);
	DDX_Control(pDX, IDC_BUTTON_TEST_LOAN, m_Test_Loan_Button);
	DDX_Control(pDX, IDC_PICTURE_CONTROL_RESULT_DETAIL, m_Result_Detail_Graph);
	DDX_Text(pDX, IDC_EDIT_TOTAL_REFUND_MONEY, m_strTotal_Refund_Money);
	DDX_Text(pDX, IDC_EDIT_TOTAL_REFUND_ORIGINAL_MONEY, m_strTotal_Refund_Original_Money);
	DDX_Text(pDX, IDC_EDIT_TOTAL_INTEREST, m_strTotal_Interest);
}

BEGIN_MESSAGE_MAP(CMFCLOANFUNCTIONTESTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON_INPUT, &CMFCLOANFUNCTIONTESTDlg::OnClickedButtonInput)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CONTROL_RESULT, &CMFCLOANFUNCTIONTESTDlg::OnLvnItemchangedListControlResult)
ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMFCLOANFUNCTIONTESTDlg::OnClickedButtonDelete)
ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CMFCLOANFUNCTIONTESTDlg::OnClickedButtonLogin)
ON_COMMAND(IDC_RADIO_CLIENT, &CMFCLOANFUNCTIONTESTDlg::OnRadioClient)
ON_COMMAND(IDC_RADIO_MANAGER, &CMFCLOANFUNCTIONTESTDlg::OnRadioManager)
ON_WM_CLOSE()
ON_BN_CLICKED(IDC_BUTTON_VIEW_DETAIL, &CMFCLOANFUNCTIONTESTDlg::OnClickedButtonViewDetail)
ON_BN_CLICKED(IDC_BUTTON_TEST_LOAN, &CMFCLOANFUNCTIONTESTDlg::OnClickedButtonTestLoan)
ON_NOTIFY(HDN_ITEMCLICK, 0, &CMFCLOANFUNCTIONTESTDlg::OnItemclickListControlResult)
END_MESSAGE_MAP()


// CMFCLOANFUNCTIONTESTDlg 메시지 처리기

BOOL CMFCLOANFUNCTIONTESTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// 리스트 컨트롤 같은 행 서브 아이템 선택해도 선택 되도록 설정 및 그리드 라인 스타일 적용
	m_CLCLoan_Result.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
	m_CLCLoan_Result_Detail.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);

	// 고객 라디오 버튼 활성화
	CButton* pCheck;
	pCheck = (CButton*)GetDlgItem(IDC_RADIO_CLIENT);
	pCheck->SetCheck(TRUE);
	
	m_bLogin_Statement = FALSE;																// 로그인 비활성화

	m_bIs_View_Detail_Button_Open = FALSE;													// 상세보기 창은 닫혀있음

	CMFCLOANFUNCTIONTESTDlg::StateReset();

	SetWindowPos(&wndTop, 0, 0, 630, 515, SWP_SHOWWINDOW | SWP_NOMOVE);

	GetDlgItem(IDC_LIST_CONTROL_RESULT_DETAIL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_RESULT_DETAIL)->ShowWindow(SW_HIDE);

	m_CBRefund_Method.AddString(_T("원리금균등상환"));
	m_CBRefund_Method.AddString(_T("원금균등상환"));
	m_CBRefund_Method.AddString(_T("만기일시상환"));

	m_CBRefund_Method.SetCurSel(0);

	m_CLCLoan_Result.InsertColumn(0, _T("대출시기"), NULL, 75);
	m_CLCLoan_Result.InsertColumn(1, _T("대출자성명"), NULL, 75);
	m_CLCLoan_Result.InsertColumn(2, _T("대출금액"), NULL, 75);
	m_CLCLoan_Result.InsertColumn(3, _T("이자율"), NULL, 75);
	m_CLCLoan_Result.InsertColumn(4, _T("상환개월수"), NULL, 75);
	m_CLCLoan_Result.InsertColumn(5, _T("납입방법"), NULL, 85);
	m_CLCLoan_Result.InsertColumn(6, _T("식별번호"), NULL, 100);

	m_CLCLoan_Result_Detail.InsertColumn(0, _T("회차"), NULL, 35);
	m_CLCLoan_Result_Detail.InsertColumn(1, _T("상환연월"), NULL, 75);
	m_CLCLoan_Result_Detail.InsertColumn(2, _T("상환금액"), NULL, 75);
	m_CLCLoan_Result_Detail.InsertColumn(3, _T("납입원금"), NULL, 70);
	m_CLCLoan_Result_Detail.InsertColumn(4, _T("납입원금 누계"), NULL, 80);
	m_CLCLoan_Result_Detail.InsertColumn(5, _T("이자"), NULL, 75);
	m_CLCLoan_Result_Detail.InsertColumn(6, _T("이자 누계"), NULL, 75);
	m_CLCLoan_Result_Detail.InsertColumn(7, _T("잔금"), NULL, 75);

	setlocale(LC_ALL, "korean");																									// 한글 깨짐 해결 방안

	// 데이터 베이스 연결
	DB_Connection = mysql_init(&mysql);																													// 데이터 베이스 연결을 위한 초기화
	DB_Connection = mysql_real_connect(&mysql, "123.456.789.012", "loan_manager", "mfcteamproject", "loan_management_system", 3306, NULL, 0);			// 데이터 베이스 대출 관리자 계정으로 로그인 함 (배포 IP)
	//DB_Connection = mysql_real_connect(&mysql, "127.0.0.1", "loan_manager", "mfcteamproject", "loan_management_system", 3306, NULL, 0);				// 데이터 베이스 대출 관리자 계정으로 로그인 함

	mysql_query(&mysql, "set names euckr");																							// 한글 깨짐 해결 방안

	if (DB_Connection != NULL)
	{
		AfxMessageBox(_T("데이터 베이스 연결에 성공하였습니다"));
	}
	else
	{
		AfxMessageBox(_T("데이터 베이스 연결에 실패하였습니다"));
		AfxMessageBox(_T("모의대출 기능만 사용 가능합니다"));
		OnClickedButtonTestLoan();
		GetDlgItem(IDC_BUTTON_TEST_LOAN)->EnableWindow(FALSE);
	}
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCLOANFUNCTIONTESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCLOANFUNCTIONTESTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCLOANFUNCTIONTESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMFCLOANFUNCTIONTESTDlg::OnClickedButtonInput()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString Loan_Person_Name;								// 대출자 이름
	CString strRefund_Method;								// 대출 상환 방법
	int nLoan_Date;											// 대출 날짜
	int nLoan_Year;											// 대출 연도를 입력 받는 변수
	int nLoan_Month;										// 대출 월을 입력 받는 변수
	int nLoan_Day;											// 대출 일을 입력 받는 변수
	int index_Refund_Method = 0;							// 납입방법 콤보박스가 가리키는 인덱스(위치번호) 입력 받는 변수
	int nOriginal_Loan_Money;								// 대출원금							A			에디트박스로부터 입력받을 값
	int nLoan_Refund_Month_Numbers;							// 환급해야하는 달 수				n			에디트박스로부터 입력받을 값
	int nLine = 0;											// 결과창 리스트 컨트롤에서 행 위치를 저장하는 변수
	double dbInterest_Rate_Per_Year;						// 연간 이자율									에디트박스로부터 입력받을 값
	bool bIs_ID_Number_Overlap = FALSE;						// 식별번호가 중복되는지 저장하는 변수

	UpdateData(TRUE);

	// 대출 연도를 입력 받음
	nLoan_Year = m_DTPLoan_Date.GetYear();
	m_strTemp2.Format(_T("%d"), nLoan_Year);
	m_strTemp1.Append(m_strTemp2);

	// 대출 월을 입력 받음
	nLoan_Month = m_DTPLoan_Date.GetMonth();
	m_strTemp2.Format(_T("%02d"), nLoan_Month);
	m_strTemp1.Append(m_strTemp2);

	// 대출 일을 입력 받음
	nLoan_Day = m_DTPLoan_Date.GetDay();
	m_strTemp2.Format(_T("%02d"), nLoan_Day);
	m_strTemp1.Append(m_strTemp2);

	nLoan_Date = _wtoi(m_strTemp1);											// 대출 시기를 입력 받음

	nOriginal_Loan_Money = GetDlgItemInt(IDC_EDIT_LOAN_MONEY);				// IDC_EDIT_LOAN_MONEY(대출 원금)을 입력받는 에디트 컨트롤로부터 전달받음
	dbInterest_Rate_Per_Year = GetDlgItemInt(IDC_EDIT_LOAN_INTEREST_RATE);	// IDC_EDIT_LOAN_INTEREST_RATE(대출 이자율)을 입력받는 에디트 컨트롤로부터 전달받음
	nLoan_Refund_Month_Numbers = GetDlgItemInt(IDC_EDIT_LOAN_PERIOD);		// IDC_EDIT_LOAN_INTEREST_PERIOD(대출 기간 = 환급 하는 달수)을 입력받는 에디트 컨트롤로부터 전달받음
	m_nID_Number = GetDlgItemInt(IDC_EDIT_IDENTITY_NUMBER);					// IDC_EDIT_IDENTITY_NUMBER(식별번호)를 입력받는 에디트 컨트롤로부터 전달받음

	m_CELoan_Person_Name.GetWindowTextW(Loan_Person_Name);					// 대출자 성명을 입력 받음

	m_strTemp2.Format(_T("%d"), m_nID_Number);								// 현재 결과(요약내용) 리스트 컨트롤의 식별번호가 중복되는지 확인하기 위해 대입

	for (nLine = 0; nLine < m_CLCLoan_Result.GetItemCount() && m_bIs_Test_Loan_Activate == TRUE; nLine++)
	{
		// 식별번호 컬럼을 돌면서 입력한 값과 같은 값을 찾는다. 단, 모의대출인 경우에는 작동하지 않음
		if (m_strTemp2.Compare(m_CLCLoan_Result.GetItemText(nLine, 6)) == 0)
		{
			bIs_ID_Number_Overlap = TRUE;
			break;
		}
	}
	// 입력 받아야될 부분 하나라도 빠지거나 식별번호가 중복되는 경우 실행이 안됨 단, 모의대출인 경우에는 이름하고 식별번호가 입력될 필요가 없기 때문에 저 두가지를 제외한 나머지를 입력할 경우에 작동을 함
	if ((nOriginal_Loan_Money != 0 && dbInterest_Rate_Per_Year != 0 && nLoan_Refund_Month_Numbers != 0 && Loan_Person_Name != "" && m_nID_Number != 0 && bIs_ID_Number_Overlap == FALSE) || (nOriginal_Loan_Money != 0 && dbInterest_Rate_Per_Year != 0 && nLoan_Refund_Month_Numbers != 0 && m_bIs_Test_Loan_Activate == TRUE))
	{
		// 대출날짜 출력
		m_CLCLoan_Result.InsertItem(0, m_strTemp1);

		// 대출자 성명 출력
		// GetDlgItemTextW(IDC_EDIT_LOAN_PERSON_NAME, strSelText);			// IDC를 이용해서 이름을 출력하는 경우
		m_strTemp1.Format(Loan_Person_Name);
		m_CLCLoan_Result.SetItem(0, 1, LVIF_TEXT, m_strTemp1, 0, 0, 0, 0);

		// 대출금액 출력
		m_strTemp1.Format(_T("%d"), nOriginal_Loan_Money);
		m_CLCLoan_Result.SetItem(0, 2, LVIF_TEXT, m_strTemp1, 0, 0, 0, 0);

		// 이자율 출력
		m_strTemp1.Format(_T("%d"), (int)dbInterest_Rate_Per_Year);
		m_CLCLoan_Result.SetItem(0, 3, LVIF_TEXT, m_strTemp1, 0, 0, 0, 0);

		// 상환개월수 출력
		m_strTemp1.Format(_T("%d"), nLoan_Refund_Month_Numbers);
		m_CLCLoan_Result.SetItem(0, 4, LVIF_TEXT, m_strTemp1, 0, 0, 0, 0);

		// 대출상환방법 출력
		index_Refund_Method = m_CBRefund_Method.GetCurSel();
		m_CBRefund_Method.GetLBText(index_Refund_Method, m_strTemp2);
		m_strTemp1.Format(m_strTemp2);
		strRefund_Method.Format(m_strTemp2);
		m_CLCLoan_Result.SetItem(0, 5, LVIF_TEXT, m_strTemp1, 0, 0, 0, 0);

		// 식별번호 출력
		if (m_bLogin_User_Type == TRUE && m_bLogin_Statement == TRUE)								// 관리자 계정으로 로그인 한 경우에만 적용
		{
			m_strTemp1.Format(_T("%d"), m_nID_Number);
			// 데이터베이스 테이블에 대출시기/고객 성명/대출 금액/이자율/납입 방식 전달
			sprintf_s(m_cBuffer, sizeof(m_cBuffer), "INSERT INTO client_information_table (Loan_Date, Client_Name, Loan_Money, Interest_Rate, Refund_Month, Refund_Method, ID_Number) VALUES ('%d', '%S', '%d', '%lf', '%d', '%S', '%d')", nLoan_Date, Loan_Person_Name, nOriginal_Loan_Money, dbInterest_Rate_Per_Year, nLoan_Refund_Month_Numbers, strRefund_Method, m_nID_Number);
			mysql_query(&mysql, m_cBuffer);
		}
		else
		{
			m_strTemp1.Format(_T("********"));
		}
		
		m_CLCLoan_Result.SetItem(0, 6, LVIF_TEXT, m_strTemp1, 0, 0, 0, 0);
		
		// 임시 문자열 저장 변수 값 비우기
		m_strTemp1.Empty();
		m_strTemp2.Empty();
	}
	else if(bIs_ID_Number_Overlap == TRUE)
	{
		AfxMessageBox(_T("중복되는 식별번호가 존재합니다"));
	}
	else
	{
		AfxMessageBox(_T("지정되지 않은 값이 있습니다"));
	}
	UpdateData(FALSE);
}



void CMFCLOANFUNCTIONTESTDlg::OnLvnItemchangedListControlResult(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strRefund_Method;												// 납입 방법
	int nRepeat = 0;														// 반복문
	int nResult_Column_Number = 0;											// 결과 리스트 컨트롤의 항목(열) 총 개수를 저장하는 변수
	int nLine = 0;															// 회차
	int nOriginal_Loan_Money = 0;											// 최초 대출 금액(대출원금)
	int nLoan_Year = 0;														// 대출 연도
	int nLoan_Month = 0;													// 대출 월
	int nMonth_Expiration = 0;												// 만기 달
	double dbInterest_Rate_Per_Year = 0;									// 연간 이자율
	double dbInterest = 0;													// 이자금액
	double dbRefund_Money_Per_Month = 0;									// 달마다 상환할 금액
	double dbInterest_About_Loan = 0;										// 전체 이자에 대한 한달 이자
	double dbOriginal_Refund_Money = 0;										// 납입원금(이자를 제외한 상환금액)
	double dbAccumulated_Refund_Money = 0;									// 누적 상환금액
	double dbAccumulated_Interest = 0;										// 누적 이자
	double dbAccumulated_Original_Refund_Money = 0;							// 누적 납입원금(납입원금 누계)
	double dbLoan_Rest_Money = 0;											// 대출금액 상환할때마다 남는 나머지 금액


	if (pNMLV && (pNMLV->uNewState == (UINT)(LVIS_FOCUSED | LVIS_SELECTED)))		// LvnItemchanged가 한번만 호출되기 위해 작성, 그 이상 호출할 경우 리스트 컨트롤 값 지정 위치 변경시 런타임 에러 발생
	{
		m_CLCLoan_Result_Detail.DeleteAllItems();									// 결과 리스트 컨트롤의 모든 항목을 제거

		nResult_Column_Number = m_CLCLoan_Result.GetItemCount();					// 리스트 컨트롤 항목(열)의 총 개수

		// 리스트 컨트롤의 항목 개수를 구한다. 변수 초기화 작업
		for (nRepeat = 0; nRepeat < nResult_Column_Number; nRepeat++)
		{
			// 개별 항목(열)의 현재 상태가 선택된 상태일 경우
			if (LVIS_SELECTED == m_CLCLoan_Result.GetItemState(nRepeat, LVIS_SELECTED))
			{
				m_strTemp2 = m_CLCLoan_Result.GetItemText(nRepeat, 0);					// 상환하는 연도 및 달
				nLoan_Year = _wtoi(m_strTemp2) / 10000;									// 연도값만 구하기
				nLoan_Month = _wtoi(m_strTemp2) / 100 - nLoan_Year * 100;				// 월 값만 구하기

				m_strTemp2 = m_CLCLoan_Result.GetItemText(nRepeat, 2);					// 대출 금액
				nOriginal_Loan_Money = _wtoi(m_strTemp2);

				m_strTemp2 = m_CLCLoan_Result.GetItemText(nRepeat, 3);					// 이자율
				dbInterest_Rate_Per_Year = _wtoi(m_strTemp2);

				m_strTemp2 = m_CLCLoan_Result.GetItemText(nRepeat, 4);					// 만기 개월
				nMonth_Expiration = _wtoi(m_strTemp2);

				strRefund_Method = m_CLCLoan_Result.GetItemText(nRepeat, 5);			// 납입방법

				m_strTemp2 = m_CLCLoan_Result.GetItemText(nRepeat, 6);					// 식별번호 받아오기
				m_nID_Number = _wtoi(m_strTemp2);

				break;
			}
		}

		dbLoan_Rest_Money = nOriginal_Loan_Money;						// 최초 남는 금액은 원래 대출 받은 금액이랑 같음

		// 각 회차(nLine) 별로 세부 내역 띄우기
		for (nLine = 0; nLine <= nMonth_Expiration - 1; nLine++)
		{
			UpdateData(TRUE);

			// 만기 회차까지 연도 및 개월수 구하기
			nLoan_Month = nLoan_Month + 1;

			if (nLoan_Month == 13)										// 대출금액 상환하는 월 값이 13이 됐을때 1월로 지정 해줌
			{
				nLoan_Month = 1;
				nLoan_Year = nLoan_Year + 1;
			}

			m_strTemp1.Format(_T("%03d"), nLine+1);						// 회차 출력
			m_CLCLoan_Result_Detail.InsertItem(nLine, m_strTemp1);

			m_strTemp1.Format(_T("%d"), nLoan_Year);					// 연도 지정
	
			m_strTemp2.Format(_T("%02d"), nLoan_Month);					// 월 지정
			m_strTemp1.Append(m_strTemp2);								// strTemp1에 연도 값이 지정된 상태에서 strTemp2(월) 값을 이어 붙임

			// 각 상환방식별로 한달 상환 금액 구하기
			if (strRefund_Method == "원리금균등상환")					// 매달 상환하는 금액이 같아야함
			{
				// 각 회차별 상환 금액(매달 상환 금액) 구하기
				dbInterest_About_Loan = dbInterest_Rate_Per_Year / 12 / 100;
				dbRefund_Money_Per_Month = (nOriginal_Loan_Money * dbInterest_About_Loan * pow((1 + dbInterest_About_Loan), nMonth_Expiration)) / (pow((1 + dbInterest_About_Loan), nMonth_Expiration) - 1);

				// 각 회차별 이자 구하기
				dbInterest = dbLoan_Rest_Money * (dbInterest_Rate_Per_Year / 12 / 100);

				// 납입 원금 구하기
				dbOriginal_Refund_Money = dbRefund_Money_Per_Month - dbInterest;

			}
			if (strRefund_Method == "원금균등상환")						// 매달 납입 원금이 같아야함
			{	
				// 납입 원금 구하기
				dbOriginal_Refund_Money = nOriginal_Loan_Money / nMonth_Expiration;

				// 각 회차별 이자 구하기
				dbInterest = dbLoan_Rest_Money * (dbInterest_Rate_Per_Year / 12 / 100);

				// 각 회차별 상환 금액(매달 상환 금액) 구하기
				dbRefund_Money_Per_Month = dbInterest + dbOriginal_Refund_Money;

				// 마지막 회차를 납부하고도 잔금이 남아있는 경우
				if (nLine == nMonth_Expiration - 1 && dbLoan_Rest_Money - dbOriginal_Refund_Money != 0)
				{
					// 이 경우 남아있는 잔금을 마지막 회차때 모두 더해준다
					dbOriginal_Refund_Money = dbOriginal_Refund_Money + dbLoan_Rest_Money - dbOriginal_Refund_Money;
				}
			}
			if (strRefund_Method == "만기일시상환")						// 매달 납입하는 금액이 이자금액이고 마지막 회차때 원금이랑 이자랑 모두 합해서 납부
			{
				dbInterest = nOriginal_Loan_Money * (dbInterest_Rate_Per_Year / 12 / 100);
				dbRefund_Money_Per_Month = dbInterest;
				if (nLine == nMonth_Expiration - 1)
				{
					dbRefund_Money_Per_Month = dbRefund_Money_Per_Month + dbLoan_Rest_Money;
					dbOriginal_Refund_Money = dbLoan_Rest_Money;
				}

			}

			///////////////////////////////공통적으로 구하는 부분///////////////////////////////
			// 누적 납입 원금 구하기
			dbAccumulated_Original_Refund_Money = dbAccumulated_Original_Refund_Money + dbOriginal_Refund_Money;

			// 누적 이자 금액 구하기
			dbAccumulated_Interest = dbAccumulated_Interest + dbInterest;

			// 남은 상환 금액 구하기(잔금 구하기)
			dbLoan_Rest_Money = dbLoan_Rest_Money - dbOriginal_Refund_Money;

			// 누적 상환 금액 구하기
			dbAccumulated_Refund_Money = dbAccumulated_Refund_Money + dbRefund_Money_Per_Month;

			///////////////////////////연도와 금액 관련 출력하는 부분///////////////////////////

			// 연도 출력
			m_CLCLoan_Result_Detail.SetItem(nLine, 1, LVIF_TEXT, m_strTemp1, 0, 0, 0, 0);

			// 한달 상환 금액 출력
			m_strTemp1.Format(_T("%d"), (int)dbRefund_Money_Per_Month);
			m_CLCLoan_Result_Detail.SetItem(nLine, 2, LVIF_TEXT, m_strTemp1, 0, 0, 0, 0);

			// 달별 남입 원금 출력
			m_strTemp1.Format(_T("%d"), (int)dbOriginal_Refund_Money);
			m_CLCLoan_Result_Detail.SetItem(nLine, 3, LVIF_TEXT, m_strTemp1, 0, 0, 0, 0);

			// 누적 남입 원금 출력
			m_strTemp1.Format(_T("%d"), (int)dbAccumulated_Original_Refund_Money);
			m_CLCLoan_Result_Detail.SetItem(nLine, 4, LVIF_TEXT, m_strTemp1, 0, 0, 0, 0);

			// 각 회차별 이자 출력
			m_strTemp1.Format(_T("%d"), (int)dbInterest);
			m_CLCLoan_Result_Detail.SetItem(nLine, 5, LVIF_TEXT, m_strTemp1, 0, 0, 0, 0);

			// 누적 이자 출력
			m_strTemp1.Format(_T("%d"), (int)dbAccumulated_Interest);
			m_CLCLoan_Result_Detail.SetItem(nLine, 6, LVIF_TEXT, m_strTemp1, 0, 0, 0, 0);

			// 남은 대출 상환 금액 출력
			m_strTemp1.Format(_T("%d"), (int)dbLoan_Rest_Money);
			m_CLCLoan_Result_Detail.SetItem(nLine, 7, LVIF_TEXT, m_strTemp1, 0, 0, 0, 0);

			if (nLine == nMonth_Expiration - 1)
			{
				// 총 상환 금액 출력
				m_strTotal_Refund_Money.Format(_T("%d"), (int)(dbAccumulated_Original_Refund_Money + dbAccumulated_Interest));
				// 총 납입 원금 출력
				m_strTotal_Refund_Original_Money.Format(_T("%d"), (int)dbAccumulated_Original_Refund_Money);
				// 총 이자 출력
				m_strTotal_Interest.Format(_T("%d"), (int)dbAccumulated_Interest);

				// 그래프 그리기(총 상환금액에서 총 납입원금과 총 이자금액이 차지하는 비율을 알기 위해 해당 변수값들을 전달)
				createChart(0, "threedpieshading0.png", dbAccumulated_Original_Refund_Money, dbAccumulated_Interest);

				// 문자열 임시 저장 변수 비우기
				m_strTemp1.Empty();
				m_strTemp2.Empty();
			}
			UpdateData(FALSE);
		}
		// 그래프 보이게 하기
		GetDlgItem(IDC_PICTURE_CONTROL_RESULT_DETAIL)->ShowWindow(SW_SHOW);
	}
	*pResult = 0;
}

void CMFCLOANFUNCTIONTESTDlg::OnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos;																			// 행의 위치의 값을 알아내기 위한 변수 선언
	pos = m_CLCLoan_Result.GetFirstSelectedItemPosition();									// 선택된 행의 위치 구함
	m_nResult_List_Ctrl_Row = m_CLCLoan_Result.GetNextSelectedItem(pos);					// 행의 위치를 int 형으로 변환

	if (m_nResult_List_Ctrl_Row != -1)														// 결과 리스트 컨트롤의 행이 선택 되어 있는 경우
	{
		m_CLCLoan_Result.DeleteItem(m_nResult_List_Ctrl_Row);								// 결과 리스트 컨트롤 항목 삭제
		m_CLCLoan_Result_Detail.DeleteAllItems();											// 결과의 세부 내용 리스트 컨트롤 내용도 같이 삭제
		GetDlgItem(IDC_PICTURE_CONTROL_RESULT_DETAIL)->ShowWindow(SW_HIDE);					// 그래프 숨기기
		// 평균 금액과 총 금액 출력하는 에디트 컨트롤 내용 비우기
		GetDlgItem(IDC_EDIT_TOTAL_REFUND_MONEY)->SetWindowTextW(_T(""));
		GetDlgItem(IDC_EDIT_TOTAL_REFUND_ORIGINAL_MONEY)->SetWindowTextW(_T(""));
		GetDlgItem(IDC_EDIT_TOTAL_INTEREST)->SetWindowTextW(_T(""));
		
		// DB 내용도 삭제
		sprintf_s(m_cBuffer, sizeof(m_cBuffer), "DELETE FROM client_information_table WHERE ID_Number = %d", m_nID_Number);
		mysql_query(&mysql, m_cBuffer);
		m_nResult_List_Ctrl_Row = -1;
	}
	else
	{
		AfxMessageBox(_T("삭제하려는 행을 지정하십시오"));
	}
}

void CMFCLOANFUNCTIONTESTDlg::OnClickedButtonLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString CSTemp[7] = { NULL };															// m_row 배열을 직접적으로 리스트 컨트롤에 넣어줄수 없으므로 그 배열 값을 받아주는 변수, 인덱스 부분이 8인 이유는 마지막 인덱스에서 미납 현황값을 받아와야 라인이 비기 때문에 이렇게 선언함
	int nRepeat = 0;																		// 반복문 숫자

	GetDlgItemText(IDC_EDIT_ID, m_strID);													// IDC_EDIT_ID 컨트롤로부터 strID로 텍스트 전달
	GetDlgItemText(IDC_EDIT_PASSWORD, m_strPW);												// IDC_EDIT_PASSWORD 컨트롤로부터 strPW로 텍스트 전달

	if (m_bLogin_Statement == FALSE)														// 로그아웃 상태인 경우
	{
		if (m_strID != "" && m_strPW != "")													// ID칸이나 PW칸 하나라도 비어있는지 확인
		{
			if (m_bLogin_User_Type == TRUE)													// 관리자를 선택했을 경우
			{
				sprintf_s(m_cBuffer, sizeof(m_cBuffer), "SELECT * FROM manager_information_table WHERE Manager_Name = '%S' AND ID_Number = '%S'", m_strID, m_strPW);				// 입력한 ID와 PW를 데이터 베이스의 값과 비교

				mysql_query(&mysql, m_cBuffer);
				m_pres = mysql_store_result(&mysql);
				m_nRow = mysql_num_rows(m_pres);

				if (m_nRow == 0)																// 관리자 계정으로 로그인에 실패했을 경우
				{
					AfxMessageBox(_T("계정이 없거나 비밀번호가 틀렸습니다"));
				}
				else																			// 관리자 계정으로 로그인 성공했을 경우
				{
					mysql_free_result(m_pres);
					// 로그인 상태로 전환
					m_bLogin_Statement = TRUE;
					// 로그인 버튼 로그아웃 버튼으로 글자 변경
					m_Login_Button.SetWindowTextW(_T("로그아웃"));
					// 로그인 칸 및 모의대출 비활성화
					CMFCLOANFUNCTIONTESTDlg::DisableLogin();
					GetDlgItem(IDC_BUTTON_TEST_LOAN)->EnableWindow(FALSE);
					// 대출 등록 칸 및 고객정보 칸 활성화
					CMFCLOANFUNCTIONTESTDlg::EnableLoanEnroll();
					CMFCLOANFUNCTIONTESTDlg::EnableLoanResult();
					
					mysql_query(&mysql, "SELECT Loan_Date, Client_Name ,Loan_Money, Interest_Rate, Refund_Month, Refund_Method, ID_Number FROM client_information_table");																// client_information_table에서 Is_Unpaid를 제외한 컬럼 선택

					m_pres = mysql_store_result(&mysql);
					m_nFields = mysql_num_fields(m_pres);

					// 리스트 컨트롤에 모든 고객 내용(대출 결과 요약 내용)만 출력
					while ((m_row = mysql_fetch_row(m_pres)) != NULL)																			// client_information_table로부터 값 가져오기
					{
						for (nRepeat = 0; nRepeat < m_nFields; nRepeat++)
						{
							CSTemp[nRepeat] = m_row[nRepeat];
							if (nRepeat == 0)																									// 리스트 컨트롤의 각 행의 맨 왼쪽 열은 항상 InsertItem이 들어감
							{
								m_CLCLoan_Result.InsertItem(nRepeat, CSTemp[nRepeat]);
							}
							else
							{
								m_CLCLoan_Result.SetItem(0, nRepeat, LVIF_TEXT, CSTemp[nRepeat], 0, 0, 0, 0);
							}
						}
					}
					mysql_free_result(m_pres);
				}
			}
			else																				// 고객을 선택했을 경우
			{
				sprintf_s(m_cBuffer, sizeof(m_cBuffer), "SELECT Loan_Date, Client_Name ,Loan_Money, Interest_Rate, Refund_Month, Refund_Method, ID_Number FROM client_information_table WHERE Client_Name = '%S' AND ID_Number = '%S'", m_strID, m_strPW);				// 입력한 ID와 PW를 비교

				mysql_query(&mysql, m_cBuffer);
				m_pres = mysql_store_result(&mysql);
				m_nRow = mysql_num_rows(m_pres);
				m_nFields = mysql_num_fields(m_pres);

				if (m_nRow == 0)																// 고객 계정으로 로그인에 실패했을 경우
				{
					AfxMessageBox(_T("고객 정보가 없거나 비밀번호가 틀렸습니다"));
				}
				else																			// 고객 계정으로 로그인 성공했을 경우
				{
					// mysql_free_result(m_pres);
					// 로그인 상태로 전환
					m_bLogin_Statement = TRUE;
					// 로그인 버튼 로그아웃 버튼으로 글자 변경
					m_Login_Button.SetWindowTextW(_T("로그아웃"));
					// 로그인 칸 및 모의대출 버튼 비활성화
					CMFCLOANFUNCTIONTESTDlg::DisableLogin();
					GetDlgItem(IDC_BUTTON_TEST_LOAN)->EnableWindow(FALSE);
					// 대출 결과 칸 활성화
					CMFCLOANFUNCTIONTESTDlg::EnableLoanResult();
			
					// 리스트 컨트롤에 로그인 한 고객 내용(대출 결과 요약 내용)만 출력
					while ((m_row = mysql_fetch_row(m_pres)) != NULL)																			// client_information_table로부터 값 가져오기
					{
						for (nRepeat = 0; nRepeat < m_nFields; nRepeat++)
						{
							CSTemp[nRepeat] = m_row[nRepeat];
							if (nRepeat == 0)																									// 리스트 컨트롤의 각 행의 맨 왼쪽 열은 항상 InsertItem이 들어감
							{
								m_CLCLoan_Result.InsertItem(nRepeat, CSTemp[nRepeat]);
							}
							else if(nRepeat == 6)														// 식별번호 출력 하는 부분 고객으로 로그인시 출력되지 않음
							{
								CSTemp[nRepeat].Format(_T("*******"));
								m_CLCLoan_Result.SetItem(0, nRepeat, LVIF_TEXT, CSTemp[nRepeat], 0, 0, 0, 0);
							}
							else
							{
								m_CLCLoan_Result.SetItem(0, nRepeat, LVIF_TEXT, CSTemp[nRepeat], 0, 0, 0, 0);
							}

						}
					}
					mysql_free_result(m_pres);
				}
			}
		}
		else																							// ID칸이나 PW칸중 하나라도 비어있는 경우
		{
			AfxMessageBox(_T("ID와 PASSWORD 모두 입력 하십시오"));
		}
	}
	else																								// 로그인 상태인 경우 (로그아웃 버튼을 눌렀을때)
	{
		// 로그인할때 고객/관리자 구분을 제외한 나머지를 초기상태로 전환
		CMFCLOANFUNCTIONTESTDlg::StateReset();

		// 로그아웃 상태로 전환
		m_bLogin_Statement = FALSE;

		// 로그아웃 버튼 로그인 버튼으로 글자 변경
		m_Login_Button.SetWindowTextW(_T("로그인"));

		// 상세보기 한 상태에서 로그아웃 한 경우 창 닫기
		SetWindowPos(&wndTop, 0, 0, 630, 515, SWP_SHOWWINDOW | SWP_NOMOVE);

		GetDlgItem(IDC_LIST_CONTROL_RESULT_DETAIL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_RESULT_DETAIL)->ShowWindow(SW_HIDE);

		// 상세보기 한 상태에서 로그아웃 한 경우 닫기를 다시 상세보기로 바꿈
		m_View_Detail_Button.SetWindowTextW(_T("상세보기"));
		m_bIs_View_Detail_Button_Open = FALSE;
	}
}

void CMFCLOANFUNCTIONTESTDlg::OnClickedButtonViewDetail()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	if (m_bIs_View_Detail_Button_Open == FALSE)												// 상세보기 창이 닫혀있는 경우
	{
		SetWindowPos(&wndTop, 0, 0, 1250, 515, SWP_SHOWWINDOW | SWP_NOMOVE);

		GetDlgItem(IDC_LIST_CONTROL_RESULT_DETAIL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_RESULT_DETAIL)->ShowWindow(SW_SHOW);

		m_View_Detail_Button.SetWindowTextW(_T("접기"));

		m_bIs_View_Detail_Button_Open = TRUE;
	}
	else																					// 상세보기 창이 열려있는 경우
	{
		SetWindowPos(&wndTop, 0, 0, 630, 515, SWP_SHOWWINDOW | SWP_NOMOVE);

		GetDlgItem(IDC_LIST_CONTROL_RESULT_DETAIL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_RESULT_DETAIL)->ShowWindow(SW_HIDE);

		m_View_Detail_Button.SetWindowTextW(_T("상세보기"));

		m_bIs_View_Detail_Button_Open = FALSE;
	}
}

void CMFCLOANFUNCTIONTESTDlg::OnClickedButtonTestLoan()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_bIs_Test_Loan_Activate == FALSE)													// 모의대출 모드가 비활성화 상태인 경우
	{
		// 로그인 칸 비활성화
		CMFCLOANFUNCTIONTESTDlg::DisableLogin();
		GetDlgItem(IDC_BUTTON_LOGIN)->EnableWindow(FALSE);

		// 모의대출에 필요한 칸 활성화
		GetDlgItem(IDC_DATETIMEPICKER_LOAN_DATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_LOAN_PERIOD)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_LOAN_INTEREST_RATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_REFUND_METHOD)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_LOAN_MONEY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_INPUT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIST_CONTROL_RESULT)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIST_CONTROL_RESULT_DETAIL)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_VIEW_DETAIL)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_INTEREST_RATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_LOAN_DATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_LOAN_MONEY)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_PERIOD)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_REFUND_METHOD)->EnableWindow(TRUE);

		// 이름 칸 모의대출 및 식별번호 고정
		GetDlgItem(IDC_EDIT_LOAN_PERSON_NAME)->SetWindowTextW(_T("모의대출"));
		GetDlgItem(IDC_EDIT_IDENTITY_NUMBER)->SetWindowTextW(_T("0"));

		// 모의대출 버튼 글자 변경
		m_Test_Loan_Button.SetWindowTextW(_T("종료"));

		// 활성화 상태로 변경
		m_bIs_Test_Loan_Activate = TRUE;
	}
	else
	{
		// 로그인 칸 활성화
		CMFCLOANFUNCTIONTESTDlg::EnableLogin();

		// 모의대출에 필요한 칸 비활성화
		GetDlgItem(IDC_DATETIMEPICKER_LOAN_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_LOAN_PERIOD)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_LOAN_INTEREST_RATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_REFUND_METHOD)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_LOAN_MONEY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_INPUT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(FALSE);
		GetDlgItem(IDC_LIST_CONTROL_RESULT)->EnableWindow(FALSE);
		GetDlgItem(IDC_LIST_CONTROL_RESULT_DETAIL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_VIEW_DETAIL)->EnableWindow(FALSE);

		GetDlgItem(IDC_STATIC_INTEREST_RATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_LOAN_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_LOAN_MONEY)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_PERIOD)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_REFUND_METHOD)->EnableWindow(FALSE);

		// 각 에디트 컨트롤 내용 비우기
		CMFCLOANFUNCTIONTESTDlg::EmptyEditControl();

		// 결과 리스트 컨트롤 및 결과 세부 내용 리스트 컨트롤 모든 내용을 제거
		m_CLCLoan_Result.DeleteAllItems();
		m_CLCLoan_Result_Detail.DeleteAllItems();

		// 상세보기 창 접기
		SetWindowPos(&wndTop, 0, 0, 630, 515, SWP_SHOWWINDOW | SWP_NOMOVE);

		GetDlgItem(IDC_LIST_CONTROL_RESULT_DETAIL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_RESULT_DETAIL)->ShowWindow(SW_HIDE);

		m_View_Detail_Button.SetWindowTextW(_T("상세보기"));

		m_bIs_View_Detail_Button_Open = FALSE;

		// 종료 버튼 글자 변경
		m_Test_Loan_Button.SetWindowTextW(_T("모의대출"));

		// 비활성화 상태로 변경
		m_bIs_Test_Loan_Activate = FALSE;
	}
}

int CALLBACK CMFCLOANFUNCTIONTESTDlg::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl* pList = ((SORTPARAM*)lParamSort)->pList;
	int iSortColumn = ((SORTPARAM*)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM*)lParamSort)->bSortDirect;

	LVFINDINFO info1, info2;
	info1.flags = LVFI_PARAM;
	info1.lParam = lParam1;
	info2.flags = LVFI_PARAM;
	info2.lParam = lParam2;
	int irow1 = pList->FindItem(&info1, -1);
	int irow2 = pList->FindItem(&info2, -1);

	CString strItem1 = pList->GetItemText(irow1, iSortColumn);
	CString strItem2 = pList->GetItemText(irow2, iSortColumn);

	return bSortDirect ? strItem1.Compare(strItem2) : -strItem1.Compare(strItem2);
}

void CMFCLOANFUNCTIONTESTDlg::OnItemclickListControlResult(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 클릭한 칼럼의 인덱스
	//int nColumn = pNMLV->iSubItem;
	int nColumn = phdr->iItem;

	// 현재 리스트 컨트롤에 있는 데이터 총 자료 개수만큼 저장
	for (int i = 0; i < (m_CLCLoan_Result.GetItemCount()); i++)
	{
		m_CLCLoan_Result.SetItemData(i, i);
	}

	// 정렬 방식 지정(Ascend, Descend)
	m_bAscending = !m_bAscending;

	// 정렬 관련된 구조체 변수 생성 및 데이터 초기화
	SORTPARAM sortparams;
	sortparams.pList = &m_CLCLoan_Result;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;

	// 정렬 함수 호출
	m_CLCLoan_Result.SortItems(&CompareItem, (LPARAM)&sortparams);

	*pResult = 0;
}

void CMFCLOANFUNCTIONTESTDlg::createChart(int chartIndex, const char* filename, double dbAccumulated_Original_Refund, double dbAccumulated_Interest)
{
	// The data for the pie chart
	PieChart* c;
	double data[2];
	const char* labels[2];
	wchar_t strUni[3][256] = { L"원금", L"이자", L"총 상환금액에 대한 총 원금과 총 이자 금액 비율" };
	char cTemp[3][256] = { 0x00 };

	//	WideCharToMultiByte(CP_UTF8, 0, strUni[2], -1, cTemp, sizeof(char) * 255, 0, 0);

	data[0] = dbAccumulated_Original_Refund;										// 원금
	data[1] = dbAccumulated_Interest;												// 이자

	// The labels for the pie chart

	// Create a PieChart object of size 360 x 300 pixels
	c = new PieChart(360, 160);

	c->setDefaultFonts("batang.ttc", "batang.ttc");									// 한글 폰트 지정

	// Set the center of the pie at (180, 140) and the radius to 100 pixels
	c->setPieSize(180, 80, 40);

	// Add a title to the pie chart
	WideCharToMultiByte(CP_UTF8, 0, strUni[2], -1, cTemp[2], sizeof(char) * 255, 0, 0);
	c->addTitle(cTemp[2]);
	//c->addTitle("총 상환금액에 대한 원금과 이자 비율");

	// Draw the pie in 3D
	c->set3D();

	WideCharToMultiByte(CP_UTF8, 0, strUni[0], -1, cTemp[0], sizeof(char) * 255, 0, 0);
	labels[0] = cTemp[0];
	WideCharToMultiByte(CP_UTF8, 0, strUni[1], -1, cTemp[1], sizeof(char) * 255, 0, 0);
	labels[1] = cTemp[1];

	// Set the pie data and the pie labels
	c->setData(DoubleArray(data, (int)(sizeof(data) / sizeof(data[0]))), StringArray(labels, (int)(sizeof(labels) / sizeof(labels[0]))));

	// Explode the 1st sector (index = 0)
	c->setExplode(0);

	// Output the chart
	c->makeChart("threedpie.png");

	//free up resources
	m_Result_Detail_Graph.setChart(c);
	delete c;
}

void CMFCLOANFUNCTIONTESTDlg::OnRadioClient()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bLogin_User_Type = FALSE;																// TRUE : 관리자 FALSE : 고객
}

void CMFCLOANFUNCTIONTESTDlg::OnRadioManager()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bLogin_User_Type = TRUE;																// TRUE : 관리자 FALSE : 고객
}

void CMFCLOANFUNCTIONTESTDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	mysql_close(DB_Connection);																// DB 연결 해제
	CDialogEx::OnClose();
}

void CMFCLOANFUNCTIONTESTDlg::DisableLogin()											// 로그인 칸 비활성화
{
	GetDlgItem(IDC_EDIT_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_CLIENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_MANAGER)->EnableWindow(FALSE);
	// 로그인 성공시 ID 및 PW 칸 비우기
	GetDlgItem(IDC_EDIT_ID)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowTextW(_T(""));
}

void CMFCLOANFUNCTIONTESTDlg::EnableLogin()												// 로그인 칸 활성화
{
	GetDlgItem(IDC_EDIT_ID)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_CLIENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_MANAGER)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOGIN)->EnableWindow(TRUE);
}

void CMFCLOANFUNCTIONTESTDlg::EmptyEditControl()										// 전체 에디트 컨트롤 내용 비우기
{
	GetDlgItem(IDC_EDIT_ID)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_LOAN_PERIOD)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_LOAN_PERSON_NAME)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_LOAN_INTEREST_RATE)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_LOAN_MONEY)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_IDENTITY_NUMBER)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_TOTAL_REFUND_MONEY)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_TOTAL_REFUND_ORIGINAL_MONEY)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_TOTAL_INTEREST)->SetWindowTextW(_T(""));
}

void CMFCLOANFUNCTIONTESTDlg::EnableLoanEnroll()										// 대출등록 칸 활성화
{
	GetDlgItem(IDC_DATETIMEPICKER_LOAN_DATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_LOAN_PERIOD)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_LOAN_INTEREST_RATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_LOAN_PERSON_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_REFUND_METHOD)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_LOAN_MONEY)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_IDENTITY_NUMBER)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_INPUT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST_CONTROL_RESULT)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST_CONTROL_RESULT_DETAIL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_VIEW_DETAIL)->EnableWindow(TRUE);

	GetDlgItem(IDC_STATIC_IDENTITY_NUMBER)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_INTEREST_RATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_LOAN_DATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_LOAN_MONEY)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_LOAN_PERSON_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_PERIOD)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_REFUND_METHOD)->EnableWindow(TRUE);
}

void CMFCLOANFUNCTIONTESTDlg::EnableLoanResult()										// 대출결과 칸 활성화
{
	GetDlgItem(IDC_LIST_CONTROL_RESULT)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST_CONTROL_RESULT_DETAIL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_VIEW_DETAIL)->EnableWindow(TRUE);
}

void CMFCLOANFUNCTIONTESTDlg::StateReset()												// 초기화
{
	GetDlgItem(IDC_DATETIMEPICKER_LOAN_DATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_LOAN_PERIOD)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_LOAN_INTEREST_RATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_LOAN_PERSON_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_REFUND_METHOD)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_LOAN_MONEY)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_IDENTITY_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_INPUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_VIEW_DETAIL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TEST_LOAN)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST_CONTROL_RESULT)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIST_CONTROL_RESULT_DETAIL)->EnableWindow(FALSE);
	GetDlgItem(IDC_PICTURE_CONTROL_RESULT_DETAIL)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_IDENTITY_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_INTEREST_RATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_LOAN_DATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_LOAN_MONEY)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_LOAN_PERSON_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_PERIOD)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_REFUND_METHOD)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_ID)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_CLIENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_MANAGER)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_ID)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_ID)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_LOAN_PERIOD)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_LOAN_PERSON_NAME)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_LOAN_INTEREST_RATE)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_LOAN_MONEY)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_IDENTITY_NUMBER)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_TOTAL_REFUND_MONEY)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_TOTAL_REFUND_ORIGINAL_MONEY)->SetWindowTextW(_T(""));
	GetDlgItem(IDC_EDIT_TOTAL_INTEREST)->SetWindowTextW(_T(""));

	m_CBRefund_Method.SetCurSel(0);

	m_CLCLoan_Result.DeleteAllItems();
	m_CLCLoan_Result_Detail.DeleteAllItems();
}

BOOL CMFCLOANFUNCTIONTESTDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if (pMsg->wParam == VK_RETURN)
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
