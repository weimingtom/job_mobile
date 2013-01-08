// ddxm.cpp : implementation file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ddxm.h"
#include "wordpad.h"
#include "resource.h"

// this routine prints a floatingpoint number with 2 digits after the decimal
void PASCAL DDX_Twips(CDataExchange* pDX, int nIDC, int& value)
{
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	TCHAR szT[64];

	if (pDX->m_bSaveAndValidate)
	{
		::GetWindowText(hWndCtrl, szT, sizeof(szT));
		if (szT[0] != NULL) // not empty
		{
			if (!theApp.ParseMeasurement(szT, value))
			{
				AfxMessageBox(IDS_INVALID_MEASUREMENT,MB_OK|MB_ICONINFORMATION);
				pDX->Fail();            // throws exception
			}
			theApp.PrintTwips(szT, value, 2);
			theApp.ParseMeasurement(szT, value);
		}
		else // empty
			value = INT_MAX;
	}
	else
	{
		// convert from twips to default units
		if (value != INT_MAX)
		{
			theApp.PrintTwips(szT, value, 2);
			SetWindowText(hWndCtrl, szT);
		}
	}
}

void PASCAL DDV_MinMaxTwips(CDataExchange* pDX, int value, int minVal, int maxVal)
{
	ASSERT(minVal <= maxVal);
	if (value < minVal || value > maxVal)
	{
		// "The measurement must be between %1 and %2."
		if (!pDX->m_bSaveAndValidate)
		{
			TRACE0("Warning: initial dialog data is out of range.\n");
			return;     // don't stop now
		}
		TCHAR szMin[64];
		TCHAR szMax[64];
		theApp.PrintTwips(szMin, minVal, 2);
		theApp.PrintTwips(szMax, maxVal, 2);
		CString prompt;
		AfxFormatString2(prompt, IDS_MEASUREMENT_RANGE, szMin, szMax);
		AfxMessageBox(prompt, MB_ICONEXCLAMATION, AFX_IDS_APP_TITLE);
		prompt.Empty(); // exception prep
		pDX->Fail();
	}
}
