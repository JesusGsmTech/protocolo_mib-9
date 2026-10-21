// IFDDoc.h : interface of the CIFDDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IFDDOC_H__0774E19E_8FFF_4AD1_885A_7ED30380ED27__INCLUDED_)
#define AFX_IFDDOC_H__0774E19E_8FFF_4AD1_885A_7ED30380ED27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CIFDDoc : public CDocument
{
protected: // create from serialization only
	CIFDDoc();
	DECLARE_DYNCREATE(CIFDDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFDDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIFDDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CIFDDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFDDOC_H__0774E19E_8FFF_4AD1_885A_7ED30380ED27__INCLUDED_)
