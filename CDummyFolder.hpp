#ifndef C_DUMMY_FOLDER_HPP_
#define C_DUMMY_FOLDER_HPP_

#ifndef _INC_WINDOWS
    #include <windows.h>
#endif
#include <shlobj.h>
#include <shobjidl.h>
#include <shlwapi.h>

class CDummyFolder
    : public IShellFolder
    , public IItemNameLimits
{
public:
    CDummyFolder(LPCWSTR valid, LPCWSTR invalid)
        : m_cRefs(1)
    {
        SHStrDupW(valid, &m_valid);
        SHStrDupW(invalid, &m_invalid);
    }

    virtual ~CDummyFolder()
    {
        CoTaskMemFree(m_valid);
        CoTaskMemFree(m_invalid);
    }

    /*** IUnknown methods ***/

    STDMETHODIMP QueryInterface(REFIID riid, void **ppvObject)
    {
        if (!ppvObject)
            return E_POINTER;

        if (IsEqualIID(riid, IID_IShellFolder) || IsEqualIID(riid, IID_IUnknown))
        {
            *ppvObject = static_cast<IShellFolder *>(this);
            AddRef();
            return S_OK;
        }
        if (IsEqualIID(riid, IID_IItemNameLimits))
        {
            *ppvObject = static_cast<IItemNameLimits *>(this);
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }

    STDMETHODIMP_(ULONG) AddRef()
    {
        return ++m_cRefs;
    }

    STDMETHODIMP_(ULONG) Release()
    {
        if (--m_cRefs == 0)
        {
            delete this;
            return 0;
        }
        return m_cRefs;
    }

    /*** IShellFolder methods ***/

    STDMETHODIMP ParseDisplayName(
        HWND hwnd,
        IBindCtx *pbc,
        LPWSTR pszDisplayName,
        ULONG *pchEaten,
        PIDLIST_RELATIVE *ppidl,
        ULONG *pdwAttributes)
    {
        return E_NOTIMPL;
    }

    STDMETHODIMP EnumObjects(
        HWND hwnd,
        SHCONTF grfFlags,
        IEnumIDList **ppenumIDList)
    {
        return E_NOTIMPL;
    }

    STDMETHODIMP BindToObject(
        PCUIDLIST_RELATIVE pidl,
        IBindCtx *pbc,
        REFIID riid,
        void **ppv)
    {
        return E_NOTIMPL;
    }

    STDMETHODIMP BindToStorage(
        PCUIDLIST_RELATIVE pidl,
        IBindCtx *pbc,
        REFIID riid,
        void **ppv)
    {
        return E_NOTIMPL;
    }

    STDMETHODIMP CompareIDs(
        LPARAM lParam,
        PCUIDLIST_RELATIVE pidl1,
        PCUIDLIST_RELATIVE pidl2)
    {
        return E_NOTIMPL;
    }

    STDMETHODIMP CreateViewObject(
        HWND hwndOwner,
        REFIID riid,
        void **ppv)
    {
        return E_NOTIMPL;
    }

    STDMETHODIMP GetAttributesOf(
        UINT cidl,
        PCUITEMID_CHILD_ARRAY apidl,
        SFGAOF *rgfInOut)
    {
        return E_NOTIMPL;
    }

    STDMETHODIMP GetUIObjectOf(
        HWND hwndOwner,
        UINT cidl,
        PCUITEMID_CHILD_ARRAY apidl,
        REFIID riid,
        UINT *rgfReserved,
        void **ppv)
    {
        return E_NOTIMPL;
    }

    STDMETHODIMP GetDisplayNameOf(
        PCUITEMID_CHILD pidl,
        SHGDNF uFlags,
        STRRET *pName)
    {
        return E_NOTIMPL;
    }

    STDMETHODIMP SetNameOf(
        HWND hwnd,
        PCUITEMID_CHILD pidl,
        LPCWSTR pszName,
        SHGDNF uFlags,
        PITEMID_CHILD *ppidlOut)
    {
        return E_NOTIMPL;
    }

    /*** IItemNameLimits methods ***/

    STDMETHODIMP GetMaxLength(
        LPCWSTR pszName,
        int *piMaxNameLen)
    {
        return E_NOTIMPL;
    }

    STDMETHODIMP GetValidCharacters(
        LPWSTR *ppwszValidChars,
        LPWSTR *ppwszInvalidChars)
    {
        if (ppwszValidChars)
        {
            SHStrDupW(m_invalid, ppwszValidChars);
        }
        if (ppwszInvalidChars)
        {
            SHStrDupW(m_valid, ppwszInvalidChars);
        }
        return S_OK;
    }

protected:
    LONG m_cRefs;
    LPWSTR m_valid;
    LPWSTR m_invalid;
};

#endif  // ndef C_DUMMY_FOLDER_HPP_
