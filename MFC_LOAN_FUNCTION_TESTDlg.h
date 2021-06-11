
// MFC_LOAN_FUNCTION_TESTDlg.h: 헤더 파일
//
#include "mysql.h"
#include "chartdir.h"
#include "ChartViewer.h"
#include <string>

#pragma once


// CMFCLOANFUNCTIONTESTDlg 대화 상자
class CMFCLOANFUNCTIONTESTDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCLOANFUNCTIONTESTDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_LOAN_FUNCTION_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonInput();
	afx_msg void OnClickedButtonDelete();
	afx_msg void OnLvnItemchangedListControlResult(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButtonLogin();
	afx_msg void OnRadioClient();
	afx_msg void OnRadioManager();
	afx_msg void OnClose();
	afx_msg void OnClickedButtonViewDetail();
	afx_msg void OnClickedButtonTestLoan();
	afx_msg void OnItemclickListControlResult(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);													// ESC키 Enter키 누르면 종료되는 현상 방지
	void DisableLogin();																			// 로그인 칸 비활성화 함수
	void EnableLogin();;																			// 로그인 칸 활성화 함수																				
	void EmptyEditControl();;																		// 모든 에디트 컨트롤 내용 비우는 함수
	void EnableLoanEnroll();;																		// 대출등록 칸 활성화 함수
	void EnableLoanResult();;																		// 대출결과 칸 활성화 함수
	void StateReset();;																				// 초기 상태로 전환하는 함수
	static int CALLBACK CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);				// 정렬 관련 함수
	void createChart(int, const char*, double, double);												// 그래프 값 지정 관련 함수

	CChartViewer m_Result_Detail_Graph;																// 그래프 이미지 출력 변수

	CComboBox m_CBRefund_Method;									// 상환방식을 지정하는 컨트롤로부터 값을 받아오는 변수
	CListCtrl m_CLCLoan_Result;										// 대출 결과 요약 내용 출력을 담당하는 변수
	CListCtrl m_CLCLoan_Result_Detail;								// 대출 결과 세부 내용 출력을 담당하는 변수
	CEdit m_CELoan_Person_Name;										// 대출자 성명을 입력받는 컨트롤로부터 값을 받아오는 변수
	COleDateTime m_DTPLoan_Date;									// 대출 날짜 지정해주는 컨트롤로부터 값을 받아오는 변수
	CButton m_Login_Button;											// 로그인 버튼
	CButton m_View_Detail_Button;									// 상세보기 버튼
	CButton m_Test_Loan_Button;										// 모의대출 버튼
	CString m_strTemp1;												// 문자열을 임시로 저장하는 변수1
	CString m_strTemp2;												// 문자열을 임시로 저장하는 변수2CString strID = NULL;																	// ID 문자열을 저장할 변수
	CString m_strID = NULL;											// ID(이름) 문자열을 저장할 변수
	CString m_strPW = NULL;											// PW(식별번호) 문자열을 저장할 변수

	CString m_strTotal_Refund_Money;								// 총 상환금액을 출력하기 위한 변수
	CString m_strTotal_Refund_Original_Money;						// 총 납입원금을 출력하기 위한 변수
	CString m_strTotal_Interest;									// 총 이자금액을 출력하기 위한 변수

	bool m_bLogin_Statement;										// 로그인 상태 변수	TRUE : 로그인 FALSE : 로그아웃
	bool m_bLogin_User_Type;										// 사용자 유형 변수	TRUE : 관리자 FALSE : 고객
	bool m_bIs_View_Detail_Button_Open;								// 대출결과 세부 내용 칸 열려있는지 상태를 저장하는 변수
	bool m_bIs_Test_Loan_Activate;									// 모의대출창이 활성화 되어있는지 상태를 저장하는 변수

	int m_nResult_List_Ctrl_Row = 0;								// 결과 리스트 컨트롤의 행의 인덱스 번호를 저장하는 변수 이거 그냥 변수로 바꿀까 생각중
	int m_nFields = 0;
	int m_nID_Number = 0;											// 데이터 베이스에 고유번호 전달
	int m_nRow = 0;

	char m_cBuffer[1024] = { NULL };								// 데이터 베이스로 쿼리 구문을 전달할때 임시로 저장되는 변수

	BOOL m_bAscending;

	// 정렬 구조체
	struct SORTPARAM
	{
		int iSortColumn;
		bool bSortDirect;
		CListCtrl* pList;
	};

	// 데이터 베이스 관련 변수
	MYSQL mysql = { 0 };
	MYSQL* DB_Connection = NULL;
	MYSQL_RES* m_pres = NULL;
	MYSQL_ROW m_row = NULL;
};
