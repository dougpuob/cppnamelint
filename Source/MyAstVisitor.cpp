#include "MyAstVisitor.h"

#include "Common.h"
#include <iomanip>

using namespace namelint;

bool
MyASTVisitor::_IsMainFile(Decl* pDecl)
{
    if (this->m_pAstCxt->getSourceManager().isInMainFile(
          pDecl->getLocation())) {
        return true;
    }
    return false;
}

void
MyASTVisitor::_KeepFileName(string& FilePath)
{
    size_t nPos = FilePath.rfind("\\");
    if (nPos < 0) {
        nPos = FilePath.rfind("/");
    }

    if (nPos > 0) {
        FilePath = FilePath.substr(nPos + 1, FilePath.length() - nPos - 1);
    }
}

bool
MyASTVisitor::_GetPosition(Decl* pDecl,
                           string& FileName,
                           size_t& nLineNumb,
                           size_t& nColNumb)
{
    if (!this->m_pAstCxt) {
        this->m_pAstCxt = &pDecl->getASTContext();
        assert(false);
        return false;
    }

    bool bStatus = false;

    FullSourceLoc FullLocation =
      this->m_pAstCxt->getFullLoc(pDecl->getBeginLoc());
    if (FullLocation.isValid()) {
        FileName = FullLocation.getFileLoc().getFileEntry()->getName();
        if ((FileName != GetAppCxt()->FileName) ||
            ("" == GetAppCxt()->FileName)) {
            APP_CONTEXT* pAppCxt = (APP_CONTEXT*)GetAppCxt();
            pAppCxt->FileName = FileName;

            string Path1;
            Path::NormPath(FileName.c_str(), Path1);

            String::Replace(Path1, "\\\\", "\\");
            String::Replace(Path1, "\"", "");
            cout << endl << "[" << Path1 << "]" << endl;
        }

        nLineNumb = FullLocation.getSpellingLineNumber();
        nColNumb = FullLocation.getSpellingColumnNumber();
        bStatus = true;
    }

    return bStatus;
}

bool
MyASTVisitor::_PrintPosition(Decl* pDecl)
{
    string FileName;
    size_t nLineNumb = 0;
    size_t nColNumb = 0;
    bool bStatus = _GetPosition(pDecl, FileName, nLineNumb, nColNumb);
    if (bStatus) {
        cout << "  <" << nLineNumb << "," << nColNumb << ">" << setw(12);
    }
    return bStatus;
}

bool
MyASTVisitor::_ClassifyTypeName(string& TyeName)
{
    bool bStatus = true;

    String::Replace(TyeName, "struct", "");
    String::Replace(TyeName, "const", "");
    String::Replace(TyeName, "&", "");
    String::Replace(TyeName, "* ", "*");
    String::Replace(TyeName, " *", "*");
    String::Trim(TyeName);

    return bStatus;
}

bool
MyASTVisitor::_GetFunctionInfo(FunctionDecl* pDecl, string& Name)
{
    if (!pDecl->hasBody()) {
        return false;
    }
    if (!this->_IsMainFile(pDecl)) {
        return false;
    }

    Name = pDecl->getDeclName().getAsString();
    return true;
}

bool
MyASTVisitor::_GetParmsInfo(ParmVarDecl* pDecl,
                            string& VarType,
                            string& VarName)
{
    if (!pDecl) {
        return false;
    }
    if (!this->_IsMainFile(pDecl)) {
        return false;
    }

    bool bInvalid = false;
    clang::StringRef MyStrRef;
    clang::LangOptions MyLangOpt;
    SourceRange MySrcRange(pDecl->getBeginLoc(), pDecl->getLocation());
    MyStrRef = Lexer::getSourceText(CharSourceRange::getCharRange(MySrcRange),
                                    *this->m_pSrcMgr,
                                    MyLangOpt,
                                    &bInvalid);
    VarType = MyStrRef.str();

    QualType QualType = pDecl->getType();

    VarName = pDecl->getName().data();
    // VarType = QualType.getAsString();
    if (VarType.length() > 0) {
        this->_ClassifyTypeName(VarType);
    }

    return true;
}

bool
MyASTVisitor::_GetVarInfo(VarDecl* pDecl, string& VarType, string& VarName)
{
    if (!pDecl) {
        return false;
    }

    if (!this->_IsMainFile(pDecl)) {
        return false;
    }

    bool bInvalid = false;
    clang::StringRef MyStrRef;
    clang::LangOptions MyLangOpt;
    SourceRange MySrcRange(pDecl->getBeginLoc(), pDecl->getLocation());
    MyStrRef = Lexer::getSourceText(CharSourceRange::getCharRange(MySrcRange),
                                    *this->m_pSrcMgr,
                                    MyLangOpt,
                                    &bInvalid);

    string RawSrcText = MyStrRef.str();
    QualType myQualType = pDecl->getType();
    VarName = pDecl->getNameAsString();
    if (RawSrcText.length() > 0) {
        this->_ClassifyTypeName(RawSrcText);
    }
    VarType = RawSrcText;

    // string PossibleVarType = pDecl->getType().getAsString();
    // if (PossibleVarType.length() > 0) {
    //  this->_ClassifyTypeName(PossibleVarType);
    //}

    return true;
}

bool
MyASTVisitor::_AssertWithFunction(FunctionDecl* pDecl, string& FuncName)
{
    this->_PrintPosition(pDecl);
    if ("" == FuncName) {
        cout << "Function:\t<INVALID>" << endl;
    } else {
        cout << "Function:\t" << FuncName << endl;
    }
    return true;
}

bool
MyASTVisitor::_AssertWithParm(ParmVarDecl* pDecl,
                              string& TypeName,
                              string& VarName)
{
    this->_PrintPosition(pDecl);
    if ("" == VarName) {
        cout << "Parameter:\t<INVALID>" << endl;
    } else {
        cout << "Parameter:\t" << VarName << " (" << TypeName << ")" << endl;
    }
    return true;
}

bool
MyASTVisitor::_AssertWithVar(VarDecl* pDecl, string& TypeName, string& VarName)
{
    this->_PrintPosition(pDecl);
    if ("" == VarName) {
        cout << "Variable:\t<INVALID>" << endl;
    } else {
        cout << "Variable:\t" << VarName << " (" << TypeName << ")" << endl;
    }
    return true;
}

MyASTVisitor::MyASTVisitor(const SourceManager* pSM,
                           const ASTContext* pAstCxt,
                           const namelint::Config* pConfig)
{
    this->m_pSrcMgr = pSM;
    this->m_pAstCxt = (ASTContext*)pAstCxt;

    const ConfigData& CfgData = pConfig->GetData();

    this->m_FileExt = CfgData.m_General.FileExtName;
    this->m_bCheckFile = CfgData.m_General.bCheckFileName;
    this->m_bCheckFunction = CfgData.m_General.bCheckFunctionName;
    this->m_bCheckVariable = CfgData.m_General.bCheckVariableName;

    this->m_FileRuleType = CfgData.m_Rule.FileName;
    this->m_FunctionRuleType = CfgData.m_Rule.FunctionName;
    this->m_VariableRuleType = CfgData.m_Rule.VariableName;

    this->m_IgnoredFuncName = CfgData.m_WhiteList.IgnoredFuncName;
    this->m_IgnoredFuncPrefix = CfgData.m_WhiteList.IgnoredFuncPrefix;
    this->m_IgnoredVarPrefix = CfgData.m_WhiteList.VariablePrefix;

    this->m_HungarianList = CfgData.m_HungarianList.MappedTable;
    this->m_HungarianListEx = CfgData.m_HungarianListEx.MappedTable;

    this->bAllowedEndWithUnderscope =
      CfgData.m_WhiteList.bAllowedEndWithUnderscope;
}

bool
MyASTVisitor::VisitFunctionDecl(clang::FunctionDecl* pDecl)
{
    if (!this->m_bCheckFunction) {
        return true;
    }

    string FuncName;
    bool bResult = false;
    bool bStatus = this->_GetFunctionInfo(pDecl, FuncName);
    if (bStatus) {
        bResult = this->m_Detect.CheckFunction(this->m_FunctionRuleType,
                                               FuncName,
                                               this->m_IgnoredFuncName,
                                               this->m_IgnoredFuncPrefix,
                                               this->bAllowedEndWithUnderscope);
        if (!bResult) {
            ((APP_CONTEXT*)GetAppCxt())->nErrorCount++;
            this->_AssertWithFunction(pDecl, FuncName);
        }

        const clang::ArrayRef<clang::ParmVarDecl*> MyRefArray =
          pDecl->parameters();
        for (size_t nIdx = 0; nIdx < MyRefArray.size(); nIdx++) {
            string VarType;
            string VarName;
            ParmVarDecl* pParmVarDecl = MyRefArray[nIdx];

            // SourceRange MySrcRange(pParmVarDecl->getBeginLoc(),
            //                       pParmVarDecl->getLocation());

            // bool Invalid = false;
            // clang::LangOptions MyLangOpt;
            // clang::StringRef MyStrRef =
            //  Lexer::getSourceText(CharSourceRange::getCharRange(MySrcRange),
            //                       *this->m_pSrcMgr,
            //                       MyLangOpt,
            //                       &Invalid);

            // cout << "getLocStart() = " << MyStrRef.str() << endl;

            bStatus = this->_GetParmsInfo(pParmVarDecl, VarType, VarName);
            if (bStatus) {
                bResult = this->m_Detect.CheckVariable(this->m_VariableRuleType,
                                                       VarType,
                                                       VarName,
                                                       this->m_IgnoredVarPrefix,
                                                       this->m_HungarianList,
                                                       this->m_HungarianListEx);
                if (!bResult) {
                    ((APP_CONTEXT*)GetAppCxt())->nErrorCount++;
                    this->_AssertWithParm(pParmVarDecl, VarType, VarName);
                }
            }
        }
    }

    return bStatus;
}

bool
MyASTVisitor::VisitCXXMethodDecl(CXXMethodDecl* pDecl)
{
    // assertWithFunction(pDecl, pDecl->getNameAsString());
    return true;
}

bool
MyASTVisitor::VisitRecordDecl(RecordDecl* pDecl)
{
    if (!this->_IsMainFile(pDecl)) {
        return false;
    }

    return true;
}

bool
MyASTVisitor::VisitVarDecl(VarDecl* pDecl)
{
    if (!this->m_bCheckVariable) {
        return true;
    }

    string VarType;
    string VarName;

    bool bStauts = this->_GetVarInfo(pDecl, VarType, VarName);
    if (bStauts) {
        bool bResult = this->m_Detect.CheckVariable(this->m_VariableRuleType,
                                                    VarType,
                                                    VarName,
                                                    this->m_IgnoredVarPrefix,
                                                    this->m_HungarianList,
                                                    this->m_HungarianListEx);
        if (!bResult) {
            ((APP_CONTEXT*)GetAppCxt())->nErrorCount++;
            this->_AssertWithVar(pDecl, VarType, VarName);
        }
    }

    return bStauts;
}

bool
MyASTVisitor::VisitReturnStmt(ReturnStmt* pRetStmt)
{
    assert(pRetStmt);

    const Expr* pExpr = pRetStmt->getRetValue();
    if (pExpr) {
        clang::QualType MyQualType = pExpr->getType();
        std::string MyTypeStr = MyQualType.getAsString();
        return true;
    }

    return false;
}