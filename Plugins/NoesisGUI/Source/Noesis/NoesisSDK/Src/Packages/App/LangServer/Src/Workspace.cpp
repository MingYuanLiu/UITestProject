////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "Workspace.h"
#include "DocumentHelper.h"

#include <NsApp/LangServer.h>


#ifdef NS_LANG_SERVER_ENABLED

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::Workspace::Workspace()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::Workspace::IsInitialized() const
{
    return mIsInitialized;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::Workspace::Initialize()
{
    mIsInitialized = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::Workspace::DeInitialize()
{
    mIsInitialized = false;
    mDocuments.ClearShrink();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::Workspace::HasDocument(const Noesis::Uri& uri)
{
    return mDocuments.Find(uri.Str()) != mDocuments.End();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::DocumentContainer& NoesisApp::Workspace::GetDocument(const Noesis::Uri& uri)
{
    return mDocuments.Find(uri.Str())->value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::Workspace::DocumentMap& NoesisApp::Workspace::GetDocuments()
{
    return mDocuments;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::Workspace::AddDocument(const Noesis::Uri& uri, const char* vsCodeUri,
    const char* text, const uint32_t version)
{
    const auto it = mDocuments.Find(uri.Str());
    if (it != mDocuments.End())
    {
        return false;
    }
            
    DocumentContainer document{ uri, vsCodeUri, true, 0, text, {},
        version, false };
    DocumentHelper::GenerateLineNumbers(document);
    mDocuments.Insert(uri.Str(), document);
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::Workspace::RemoveDocument(const Noesis::Uri& uri)
{
    const auto it = mDocuments.Find(uri.Str());
    if (it != mDocuments.End()) 
    {
        mDocuments.Erase(it);
        mDocuments.ShrinkToFit();
        return true;
    }
    return false;
}

#endif
