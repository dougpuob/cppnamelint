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
      pAppCxt->FileName    = FileName;

      string Path1;
      Path::NormPath(FileName.c_str(), Path1);

      String::Replace(Path1, "\\\\", "\\");
      String::Replace(Path1, "\"", "");
      FileName = Path1;
    }

    nLineNumb = FullLocation.getSpellingLineNumber();
    nColNumb  = FullLocation.getSpellingColumnNumber();
    bStatus   = true;
  }

  return bStatus;
}

bool MyASTVisitor::_PrintPosition(Decl *pDecl) {
  string FileName;
  size_t nLineNumb = 0;
  size_t nColNumb  = 0;
  bool bStatus     = _GetPosition(pDecl, FileName, nLineNumb, nColNumb);
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
  SourceLocation MyLoc      = pDecl->getLocation();
  string MyVarType          = std::string(this->m_pSrcMgr->getCharacterData(MyBeginLoc),
                                 this->m_pSrcMgr->getCharacterData(MyLoc) -
                                     this->m_pSrcMgr->getCharacterData(MyBeginLoc));

  VarType = MyVarType;

  QualType MyQualType = pDecl->getType();

  VarName = pDecl->getName().data();
  bIsPtr  = MyQualType->isPointerType();

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

bool MyASTVisitor::_GetStructVarInfo(ValueDecl *pDecl, string &VarType, string &VarName,
                                     bool &bIsPtr) {
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
  SourceLocation MyLoc      = pDecl->getLocation();
  string MyVarType          = std::string(this->m_pSrcMgr->getCharacterData(MyBeginLoc),
                                 this->m_pSrcMgr->getCharacterData(MyLoc) -
                                     this->m_pSrcMgr->getCharacterData(MyBeginLoc));

  VarType = MyVarType;
  VarName = pDecl->getName().data();

  QualType MyQualType = pDecl->getType();
  bIsPtr              = MyQualType->isPointerType();

  String::Trim(VarType);
  String::Trim(VarName);

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
  SourceLocation MyLoc      = pDecl->getLocation();
  string MyValueType        = std::string(this->m_pSrcMgr->getCharacterData(MyBeginLoc),
                                   this->m_pSrcMgr->getCharacterData(MyLoc) -
                                       this->m_pSrcMgr->getCharacterData(MyBeginLoc));
  size_t nPos               = MyValueType.find(",");

  if (std::string::npos != nPos) {
    nPos        = MyValueType.find(" ");
    MyValueType = MyValueType.substr(0, nPos);
  }

  if (MyValueType.length() > 0) {
    this->_ClassifyTypeName(MyValueType);
  }

  QualType MyQualType = pDecl->getType();

  ValueType      = MyValueType;
  ValueName      = pDecl->getNameAsString();
  bIsArray       = MyQualType->isArrayType();
  bIsBuiltinType = MyQualType->isBuiltinType();
  bIsPtr         = MyQualType->isPointerType();

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

  bool bIsPtr         = false;
  bool bIsArray       = false;
  bool bIsBuiltinType = false;

  bool bStauts = this->_GetValueInfo(pDecl, ValueType, ValueName, bIsPtr, bIsArray, bIsBuiltinType);

  if (!bStauts) {
    return false;
  }

  bool bResult = this->m_Detect.CheckVariable(
      this->m_pConfig->General.Rules.VariableName, ValueType, ValueName,
      this->m_pConfig->Hungarian.Options.PreferUpperCamelIfMissed, bIsPtr, bIsArray);

  APP_CONTEXT *pAppCxt = ((APP_CONTEXT *)GetAppCxt());

  pAppCxt->MemoBoard.Checked.nVariable++;
  if (!bResult) {
    pAppCxt->MemoBoard.Error.nVariable++;

    pAppCxt->MemoBoard.ErrorDetailList.push_back(this->_CreateErrorDetail(
        pDecl, CheckType::CT_Variable, bIsPtr, bIsArray, ValueType, ValueName, ""));
  }

  return true;
}

bool MyASTVisitor::_CheckRuleForStructValue(ValueDecl *pDecl) {
  bool bIsPtr = false;
  string ValueType;
  string ValueName;

  bool bStatus = this->_GetStructVarInfo(pDecl, ValueType, ValueName, bIsPtr);
  if (!bStatus) {
    return false;
  }

  bool bResult = this->m_Detect.CheckStructVal(this->m_pConfig->General.Rules.StructValueName,
                                               ValueType, ValueName, bIsPtr);

  APP_CONTEXT *pAppCxt = ((APP_CONTEXT *)GetAppCxt());

  pAppCxt->MemoBoard.Checked.nStruct++;
  if (!bResult) {
    pAppCxt->MemoBoard.Error.nStruct++;

    pAppCxt->MemoBoard.ErrorDetailList.push_back(this->_CreateErrorDetail(
        pDecl, CheckType::CT_StructVal, bIsPtr, NOT_ARRAY, ValueType, ValueName, ""));
  }
  return true;
}

bool MyASTVisitor::_CheckRuleForEnumValue(EnumConstantDecl *pDecl) {
  string ValueType;
  string ValueName;

  bool bIsPtr         = false;
  bool bIsArray       = false;
  bool bIsBuiltinType = false;

  bool bStauts = this->_GetValueInfo(pDecl, ValueType, ValueName, bIsPtr, bIsArray, bIsBuiltinType);

  if (!bStauts) {
    return false;
  }

  bStauts = this->m_Detect.CheckVariable(
      this->m_pConfig->General.Rules.EnumValueName, ValueType, ValueName,
      this->m_pConfig->Hungarian.Options.PreferUpperCamelIfMissed, bIsPtr, bIsArray);

  return bStauts;
}

MyASTVisitor::MyASTVisitor(const SourceManager *pSM, const ASTContext *pAstCxt,
                           const Config *pConfig) {
  this->m_pSrcMgr = pSM;
  this->m_pAstCxt = (ASTContext *)pAstCxt;
  this->m_pConfig = pConfig->GetData();
  DcLib::Log::Out(INFO_ALL, "%s", __func__);
}

bool MyASTVisitor::VisitCXXRecordDecl(CXXRecordDecl *D) {
  DcLib::Log::Out(INFO_ALL, "%s", __func__);
  // std::cout << "VisitCXXRecordDecl " << D->getNameAsString() << std::endl;
  return true;
}

bool MyASTVisitor::VisitFunctionDecl(clang::FunctionDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "%s", __func__);

  if (!this->m_pConfig->General.Options.bCheckFunctionName) {
    DcLib::Log::Out(INFO_ALL, "Skipped, becuase config file is disable. (bCheckFunctionName)");
    return true;
  }

  APP_CONTEXT *pAppCxt = ((APP_CONTEXT *)GetAppCxt());

  string FuncName;
  bool bResult  = false;
  bool bIsPtr   = false;
  bool bIsArray = false;
  bool bStatus  = this->_GetFunctionInfo(pDecl, FuncName);

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

  DcLib::Log::Out(INFO_ALL, "%s", __func__);
  APP_CONTEXT *pAppCxt = ((APP_CONTEXT *)GetAppCxt());

  if (pAppCxt->MemoBoard.Option.bEnableLog) {
    this->m_DumpDecl.PrintDecl(pDecl);
  }

  bool bStatus   = false;
  string VarName = pDecl->getName();

  switch (pDecl->getTagKind()) {
  case TTK_Struct: {
    if (VarName.empty()) {
      DcLib::Log::Out(INFO_ALL, "It is an anonymous structure.");
      bStatus = true;
    } else {
      pAppCxt->MemoBoard.Checked.nStruct++;

      RULETYPE RuleType = this->m_pConfig->General.Rules.StructTagName;

      bStatus = this->m_Detect.CheckStructVal(RuleType, "" /*no type*/, VarName, NOT_PTR);
      if (!bStatus) {
        pAppCxt->MemoBoard.Error.nStruct++;
        pAppCxt->MemoBoard.ErrorDetailList.push_back(this->_CreateErrorDetail(
            pDecl, CheckType::CT_StructTag, NOT_PTR, NOT_ARRAY, "", VarName, ""));
      }
    }
    break;
  }
  case TTK_Union: {
    if (VarName.empty()) {
      DcLib::Log::Out(INFO_ALL, "It is an anonymous union.");
      bStatus = true;
    } else {
      pAppCxt->MemoBoard.Checked.nUnion++;

      RULETYPE RuleType = this->m_pConfig->General.Rules.StructTagName;

      bStatus = this->m_Detect.CheckStructVal(RuleType, "" /*no type*/, VarName, NOT_PTR);
      if (!bStatus) {
        pAppCxt->MemoBoard.Error.nUnion++;
        pAppCxt->MemoBoard.ErrorDetailList.push_back(this->_CreateErrorDetail(
            pDecl, CheckType::CT_StructTag, NOT_PTR, NOT_ARRAY, "", VarName, ""));
      }
    }
    break;
  }
  case TTK_Class: {

    pAppCxt->MemoBoard.Checked.nClass++;

    bool bStatus = this->m_Detect.CheckEnumVal(this->m_pConfig->General.Rules.ClassName, VarName);
    if (!bStatus) {
      pAppCxt->MemoBoard.Error.nClass++;
      pAppCxt->MemoBoard.ErrorDetailList.push_back(this->_CreateErrorDetail(
          pDecl, CheckType::CT_Class, NOT_PTR, NOT_ARRAY, "", VarName, ""));
    }
    break;
  }
  case TTK_Interface:
    VarName = "TTK_Interface";
    break;
  case TTK_Enum:
    VarName = "TTK_Enum";
    break;
  default:
    VarName = "??";
  }

  return true;
}

bool MyASTVisitor::VisitVarDecl(VarDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "%s", __func__);

  if (!this->m_pConfig->General.Options.bCheckVariableName) {
    DcLib::Log::Out(INFO_ALL, "Skipped, becuase config file is disable. (bCheckVariableName)");
    return true;
  }

  if (isa<ParmVarDecl>(pDecl)) {
    return true;
  }

  return _CheckRuleForVariable(pDecl);
}

bool MyASTVisitor::VisitFieldDecl(FieldDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "%s", __func__);

  if (!this->m_pConfig->General.Options.bCheckVariableName) {
    DcLib::Log::Out(INFO_ALL, "Skipped, becuase config file is disable. (bCheckVariableName)");
    return true;
  }

  return _CheckRuleForStructValue(pDecl);
}

bool MyASTVisitor::VisitReturnStmt(ReturnStmt *pRetStmt) {
  DcLib::Log::Out(INFO_ALL, "%s", __func__);

  const Expr *pExpr = pRetStmt->getRetValue();
  if (pExpr) {
    clang::QualType MyQualType = pExpr->getType();
    std::string MyTypeStr      = MyQualType.getAsString();
    return true;
  }
  return false;
}

bool MyASTVisitor::VisitParmVarDecl(ParmVarDecl *pDecl) {
  string VarType;
  string VarName;

  bool bIsPtr     = false;
  bool bIsArray   = false;
  bool bAnonymous = false;
  bool bResult    = false;

  DcLib::Log::Out(INFO_ALL, "%s", __func__);
  APP_CONTEXT *pAppCxt = ((APP_CONTEXT *)GetAppCxt());

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
          this->m_pConfig->Hungarian.Options.PreferUpperCamelIfMissed, bIsPtr, bIsArray);

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
  DcLib::Log::Out(INFO_ALL, "%s", __func__);
  APP_CONTEXT *pAppCxt = ((APP_CONTEXT *)GetAppCxt());

  if (pAppCxt->MemoBoard.Option.bEnableLog) {
    this->m_DumpDecl.PrintDecl(pDecl);
  }
  return true;
}

bool MyASTVisitor::VisitEnumConstantDecl(EnumConstantDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "%s", __func__);
  APP_CONTEXT *pAppCxt = ((APP_CONTEXT *)GetAppCxt());

  if (pAppCxt->MemoBoard.Option.bEnableLog) {
    this->m_DumpDecl.PrintDecl(pDecl);
  }
  pAppCxt->MemoBoard.Checked.nEnum++;

  string EnumValName = pDecl->getName();

  bool bStatus = _CheckRuleForEnumValue(pDecl);
  if (!bStatus) {
    string EnumTagName = "???1";
    if (pAppCxt->MemoBoard.pLastEnumDecl) {
      EnumTagName = pAppCxt->MemoBoard.pLastEnumDecl->getName();
    }
    pAppCxt->MemoBoard.Error.nEnum++;
    pAppCxt->MemoBoard.ErrorDetailList.push_back(this->_CreateErrorDetail(
        pDecl, CheckType::CT_EnumVal, NOT_PTR, NOT_ARRAY, EnumTagName, EnumValName, "???2"));
  }

  return true;
}

bool MyASTVisitor::VisitEnumDecl(EnumDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "%s", __func__);
  APP_CONTEXT *pAppCxt = ((APP_CONTEXT *)GetAppCxt());

  if (pAppCxt->MemoBoard.Option.bEnableLog) {
    this->m_DumpDecl.PrintDecl(pDecl);
  }

  pAppCxt->MemoBoard.pLastEnumDecl = pDecl;
  pAppCxt->MemoBoard.Checked.nEnum++;

  string EnumTagName = pDecl->getName();
  bool bStatus =
      this->m_Detect.CheckEnumVal(this->m_pConfig->General.Rules.EnumTagName, EnumTagName);
  if (!bStatus) {
    pAppCxt->MemoBoard.Error.nEnum++;
    pAppCxt->MemoBoard.ErrorDetailList.push_back(this->_CreateErrorDetail(
        pDecl, CheckType::CT_EnumTag, NOT_PTR, NOT_ARRAY, "", EnumTagName, ""));
  }

  return true;
}
