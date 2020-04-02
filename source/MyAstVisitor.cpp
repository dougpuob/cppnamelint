#include <iomanip>

#include "Common.h"
#include "MyAstVisitor.h"

using namespace namelint;

bool MyASTVisitor::_IsMainFile(Decl *pDecl) {
  if (this->m_pAstCxt->getSourceManager().isInMainFile(pDecl->getLocation())) {
    return true;
  }
  return false;
}

void MyASTVisitor::_KeepFileName(string &FilePath) {
  size_t nPos = FilePath.rfind("\\");
  if (nPos < 0) {
    nPos = FilePath.rfind("/");
  }

  if (nPos > 0) {
    FilePath = FilePath.substr(nPos + 1, FilePath.length() - nPos - 1);
  }
}

bool MyASTVisitor::_GetPosition(Decl *pDecl, string &FileName, size_t &nLineNumb,
                                size_t &nColNumb) {
  if (!this->m_pAstCxt) {
    this->m_pAstCxt = &pDecl->getASTContext();
    assert(false);
    return false;
  }

  bool bStatus = false;

  FullSourceLoc FullLocation = this->m_pAstCxt->getFullLoc(pDecl->getBeginLoc());
  if (FullLocation.isValid()) {
    FileName = FullLocation.getFileLoc().getFileEntry()->getName();

    if ((FileName != GetAppCxt()->FileName) || ("" == GetAppCxt()->FileName)) {
      APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
      pAppCxt->FileName = FileName;

      string Path1;
      Path::NormPath(FileName.c_str(), Path1);

      String::Replace(Path1, "\\\\", "\\");
      String::Replace(Path1, "\"", "");
      FileName = Path1;
    }

    nLineNumb = FullLocation.getSpellingLineNumber();
    nColNumb = FullLocation.getSpellingColumnNumber();
    bStatus = true;
  }

  return bStatus;
}

bool MyASTVisitor::_PrintPosition(Decl *pDecl) {
  string FileName;
  size_t nLineNumb = 0;
  size_t nColNumb = 0;
  bool bStatus = _GetPosition(pDecl, FileName, nLineNumb, nColNumb);
  if (bStatus) {
    cout << "  <" << nLineNumb << "," << nColNumb << ">" << setw(12);
  }
  return bStatus;
}

bool MyASTVisitor::_ClassifyTypeName(string &TyeName) {
  bool bStatus = true;

  String::Replace(TyeName, "extern", "");
  String::Replace(TyeName, "static", "");
  String::Replace(TyeName, "struct", "");
  String::Replace(TyeName, "const", "");
  String::Replace(TyeName, "&", "");
  String::Replace(TyeName, "*", "");
  // String::Replace(TyeName, "* ", "*");
  // String::Replace(TyeName, " *", "*");
  String::Trim(TyeName);

  return bStatus;
}

bool MyASTVisitor::_GetFunctionInfo(FunctionDecl *pDecl, string &Name) {
  if (!this->_IsMainFile(pDecl)) {
    return false;
  }

  if (GetAppCxt()->MemoBoard.Option.bEnableLog) {
    this->m_DumpDecl.PrintDecl(pDecl);
  }

  Name = pDecl->getDeclName().getAsString();
  return true;
}

bool MyASTVisitor::_GetParmsInfo(ParmVarDecl *pDecl, string &VarType, string &VarName, bool &bIsPtr,
                                 bool &bAnonymous) {
  if (!pDecl) {
    return false;
  }
  if (!this->_IsMainFile(pDecl)) {
    return false;
  }

  if (GetAppCxt()->MemoBoard.Option.bEnableLog) {
    this->m_DumpDecl.PrintDecl(pDecl);
  }

  SourceLocation MyBeginLoc = pDecl->getBeginLoc();
  SourceLocation MyLoc = pDecl->getLocation();
  string MyVarType = std::string(this->m_pSrcMgr->getCharacterData(MyBeginLoc),
                                 this->m_pSrcMgr->getCharacterData(MyLoc) -
                                     this->m_pSrcMgr->getCharacterData(MyBeginLoc));

  VarType = MyVarType;

  QualType MyQualType = pDecl->getType();

  VarName = pDecl->getName().data();
  bIsPtr = MyQualType->isPointerType();

  if (VarType.length() > 0) {
    this->_ClassifyTypeName(VarType);
  }

  String::Trim(VarType);
  String::Trim(VarName);

  if (VarName == "") {
    bAnonymous = true;
  }

  return true;
}

bool MyASTVisitor::_GetValueInfo(ValueDecl *pDecl, string &ValueType, string &ValueName,
                                 bool &bIsPtr, bool &bIsArray, bool &bIsBuiltinType) {
  if (!pDecl) {
    return false;
  }

  if (!this->_IsMainFile(pDecl)) {
    return false;
  }

  if (GetAppCxt()->MemoBoard.Option.bEnableLog) {
    this->m_DumpDecl.PrintDecl(pDecl);
  }

  // TODO:
  // This will get var type, but need to overcome some situation:
  // 1. Type "unsigned long long int" will get "unsigned long long"
  // 2. Dependency on include file, if can't get definition, it will get "int"
  // 3. Multi-array issue,we need to process string like "[8][]" "[][][]"
  //...
  // auto VarType = pDecl->getType().getAsString();

  SourceLocation MyBeginLoc = pDecl->getBeginLoc();
  SourceLocation MyLoc = pDecl->getLocation();
  string MyValueType = std::string(this->m_pSrcMgr->getCharacterData(MyBeginLoc),
                                   this->m_pSrcMgr->getCharacterData(MyLoc) -
                                       this->m_pSrcMgr->getCharacterData(MyBeginLoc));
  size_t nPos = MyValueType.find(",");

  if (std::string::npos != nPos) {
    nPos = MyValueType.find(" ");
    MyValueType = MyValueType.substr(0, nPos);
  }

  if (MyValueType.length() > 0) {
    this->_ClassifyTypeName(MyValueType);
  }

  QualType MyQualType = pDecl->getType();

  ValueType = MyValueType;
  ValueName = pDecl->getNameAsString();
  bIsArray = MyQualType->isArrayType();
  bIsBuiltinType = MyQualType->isBuiltinType();
  bIsPtr = MyQualType->isPointerType();

  String::Trim(ValueType);
  String::Trim(ValueName);

  return true;
}

ErrorDetail *MyASTVisitor::_CreateErrorDetail(const string &FileName, const string &Suggestion) {
  return new ErrorDetail(FileName, Suggestion);
}

ErrorDetail *MyASTVisitor::_CreateErrorDetail(Decl *pDecl, const CheckType &CheckType,
                                              const bool &bIsPtr, const bool &bIsArray,
                                              const string &TargetName, const string &Suggestion) {

  return this->_CreateErrorDetail(pDecl, CheckType, bIsPtr, bIsArray, "", TargetName, Suggestion);
}

ErrorDetail *MyASTVisitor::_CreateErrorDetail(Decl *pDecl, const CheckType &CheckType,
                                              const bool &bIsPtr, const bool &bIsArray,
                                              const string &TypeName, const string &TargetName,
                                              const string &Suggestion) {
  if (!pDecl) {
    return NULL;
  }

  ErrorDetail *pNew = NULL;

  string FileName;
  CodePos Pos = {0};
  if (this->_GetPosition(pDecl, FileName, Pos.nLine, Pos.nColumn)) {
    pNew = new ErrorDetail(Pos, CheckType, bIsPtr, bIsArray, TypeName, TargetName, Suggestion);
  }
  return pNew;
}

bool MyASTVisitor::_CheckRuleForVariable(ValueDecl *pDecl) {
  string ValueType;
  string ValueName;

  bool bIsPtr = false;
  bool bIsArray = false;
  bool bIsBuiltinType = false;

  bool bStauts = this->_GetValueInfo(pDecl, ValueType, ValueName, bIsPtr, bIsArray, bIsBuiltinType);

  if (!bStauts) {
    return false;
  }

  bool bResult = this->m_Detect.CheckVariable(
      this->m_pConfig->General.Rules.VariableName, ValueType, ValueName,
      this->m_pConfig->Hungarian.Others.PreferUpperCamelIfMissed, bIsPtr, bIsArray);

  APP_CONTEXT *pAppCxt = ((APP_CONTEXT *)GetAppCxt());
  if (!pAppCxt) {
    assert(pAppCxt);
    return false;
  }
  pAppCxt->MemoBoard.Checked.nVariable++;
  if (!bResult) {
    pAppCxt->MemoBoard.Error.nVariable++;

    pAppCxt->MemoBoard.ErrorDetailList.push_back(this->_CreateErrorDetail(
        pDecl, CheckType::CT_Variable, bIsPtr, bIsArray, ValueType, ValueName, ""));
  }
  return true;
}

MyASTVisitor::MyASTVisitor(const SourceManager *pSM, const ASTContext *pAstCxt,
                           const Config *pConfig) {
  this->m_pSrcMgr = pSM;
  this->m_pAstCxt = (ASTContext *)pAstCxt;
  this->m_pConfig = pConfig->GetData();

  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();

  {
    RuleOfFunction Rule;
    Rule.bAllowedUnderscopeChar = this->m_pConfig->General.Options.bAllowedUnderscopeChar;
    Rule.IgnoreNames = this->m_pConfig->General.IgnoredList.FunctionName;
    Rule.IgnorePrefixs = this->m_pConfig->General.IgnoredList.FunctionPrefix;

    this->m_Detect.ApplyRuleForFunction(Rule);
  }

  {
    RuleOfVariable Rule;
    Rule.bAllowedUnderscopeChar = this->m_pConfig->General.Options.bAllowedUnderscopeChar;

    Rule.IgnorePrefixs = this->m_pConfig->General.IgnoredList.VariablePrefix;
    Rule.WordListMap = this->m_pConfig->Hungarian.WordList;
    Rule.ArrayNamingMap = this->m_pConfig->Hungarian.ArrayList;
    Rule.NullStringMap = this->m_pConfig->Hungarian.NullStringList;

    this->m_Detect.ApplyRuleForVariable(Rule);
  }
}

bool MyASTVisitor::VisitCXXRecordDecl(CXXRecordDecl *D) {
  // std::cout << "VisitCXXRecordDecl " << D->getNameAsString() << std::endl;
  return true;
}

bool MyASTVisitor::VisitFunctionDecl(clang::FunctionDecl *pDecl) {
  if (!this->m_pConfig->General.Options.bCheckFunctionName) {
    return true;
  }

  APP_CONTEXT *pAppCxt = ((APP_CONTEXT *)GetAppCxt());
  if (!pAppCxt) {
    assert(pAppCxt);
    return false;
  }

  string FuncName;
  bool bResult = false;
  bool bIsPtr = false;
  bool bIsArray = false;
  bool bStatus = this->_GetFunctionInfo(pDecl, FuncName);

  if (bStatus) {
    bResult = this->m_Detect.CheckFunction(this->m_pConfig->General.Rules.FunctionName, FuncName);

    pAppCxt->MemoBoard.Checked.nFunction++;
    if (!bResult) {
      pAppCxt->MemoBoard.Error.nFunction++;

      pAppCxt->MemoBoard.ErrorDetailList.push_back(
          this->_CreateErrorDetail(pDecl, CheckType::CT_Function, bIsPtr, bIsArray, FuncName, ""));
    }
  }

  return bStatus;
}

bool MyASTVisitor::VisitCXXMethodDecl(CXXMethodDecl *pDecl) { return true; }

bool MyASTVisitor::VisitRecordDecl(RecordDecl *pDecl) {
  if (!this->_IsMainFile(pDecl)) {
    return false;
  }

  APP_CONTEXT *pAppCxt = ((APP_CONTEXT *)GetAppCxt());
  assert(pAppCxt);

  if (pAppCxt->MemoBoard.Option.bEnableLog) {
    this->m_DumpDecl.PrintDecl(pDecl);
  }

  return true;
}

bool MyASTVisitor::VisitVarDecl(VarDecl *pDecl) {
  if (!this->m_pConfig->General.Options.bCheckVariableName) {
    return true;
  }

  if (isa<ParmVarDecl>(pDecl)) {
    return true;
  }

  return _CheckRuleForVariable(pDecl);
}

bool MyASTVisitor::VisitFieldDecl(FieldDecl *pDecl) {
  if (!this->m_pConfig->General.Options.bCheckVariableName) {
    return true;
  }

  return _CheckRuleForVariable(pDecl);
}

bool MyASTVisitor::VisitReturnStmt(ReturnStmt *pRetStmt) {
  assert(pRetStmt);

  const Expr *pExpr = pRetStmt->getRetValue();
  if (pExpr) {
    clang::QualType MyQualType = pExpr->getType();
    std::string MyTypeStr = MyQualType.getAsString();
    return true;
  }
  return false;
}

bool MyASTVisitor::VisitParmVarDecl(ParmVarDecl *pDecl) {
  string VarType;
  string VarName;

  bool bIsPtr = false;
  bool bIsArray = false;
  bool bAnonymous = false;
  bool bResult = false;

  APP_CONTEXT *pAppCxt = ((APP_CONTEXT *)GetAppCxt());
  assert(pAppCxt);

  if (pAppCxt->MemoBoard.Option.bEnableLog) {
    this->m_DumpDecl.PrintDecl(pDecl);
  }

  bool bStatus = this->_GetParmsInfo(pDecl, VarType, VarName, bIsPtr, bAnonymous);
  if (!bAnonymous) // if this variable doesn't have name, it doesn't need to be
                   // checked.
  {
    if (bStatus) {
      bResult = this->m_Detect.CheckVariable(
          this->m_pConfig->General.Rules.VariableName, VarType, VarName,
          this->m_pConfig->Hungarian.Others.PreferUpperCamelIfMissed, bIsPtr, bIsArray);

      pAppCxt->MemoBoard.Checked.nParameter++;
      if (!bResult) {
        pAppCxt->MemoBoard.Error.nParameter++;

        pAppCxt->MemoBoard.ErrorDetailList.push_back(this->_CreateErrorDetail(
            pDecl, CheckType::CT_Parameter, bIsPtr, bIsArray, VarType, VarName, ""));
      }
    }
  }

  return true;
}

bool MyASTVisitor::VisitTypedefDecl(TypedefDecl *pDecl) {
  APP_CONTEXT *pAppCxt = ((APP_CONTEXT *)GetAppCxt());

  if (pAppCxt->MemoBoard.Option.bEnableLog) {
    this->m_DumpDecl.PrintDecl(pDecl);
  }
  return true;
}