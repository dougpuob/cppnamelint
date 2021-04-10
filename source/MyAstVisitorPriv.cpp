#include <iomanip>

#include "Common.h"
#include "MyAstVisitor.h"

using namespace namelint;

bool MyASTVisitor::isMainFile(Decl *pDecl) {
  return this->m_pSrcMgr->isInMainFile(pDecl->getLocation());
}

bool MyASTVisitor::getPos(Decl *pDecl, string &FileName, size_t &nLineNumb, size_t &nColNumb) {
  if (!this->m_pAstCxt) {
    this->m_pAstCxt = &pDecl->getASTContext();
    assert(false);
    return false;
  }

  bool bStatus = false;

  FullSourceLoc FullLocation = this->m_pAstCxt->getFullLoc(pDecl->getBeginLoc());
  if (FullLocation.isValid()) {
    FileName = FullLocation.getFileLoc().getFileEntry()->getName().str();

    if ((FileName != AppCxt::getInstance().FileName) || ("" == AppCxt::getInstance().FileName)) {
      AppCxt &AppCxt  = AppCxt::getInstance();
      AppCxt.FileName = FileName;
    }

    nLineNumb = FullLocation.getSpellingLineNumber();
    nColNumb  = FullLocation.getSpellingColumnNumber();
    bStatus   = true;
  }

  return bStatus;
}

bool MyASTVisitor::removeKeywords(string &TyeName) {
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

bool MyASTVisitor::getFunctionInfo(FunctionDecl *pDecl, string &Name) {
  if (!this->isMainFile(pDecl)) {
    return false;
  }

  this->m_DumpDecl.PrintDecl(pDecl);

  Name = pDecl->getDeclName().getAsString();
  return true;
}

bool MyASTVisitor::getParmsInfo(ParmVarDecl *pDecl, string &VarType, string &VarName, bool &bIsPtr,
                                bool &bAnonymous) {
  if (!pDecl) {
    return false;
  }
  if (!this->isMainFile(pDecl)) {
    return false;
  }

  this->m_DumpDecl.PrintDecl(pDecl);

  SourceLocation MyBeginLoc = pDecl->getBeginLoc();
  SourceLocation MyCurrLoc  = pDecl->getLocation();
  const char *szBegin       = this->m_pSrcMgr->getCharacterData(MyBeginLoc);
  const char *szCurr        = this->m_pSrcMgr->getCharacterData(MyCurrLoc);
  const intptr_t iPtrLen    = szCurr - szBegin;
  if (iPtrLen <= 0) {
    return false;
  }

  VarType             = std::string(szBegin, iPtrLen);
  QualType MyQualType = pDecl->getType();

  VarName = pDecl->getName().data();
  bIsPtr  = MyQualType->isPointerType();

  if (VarType.length() > 0) {
    this->removeKeywords(VarType);
  }

  String::Trim(VarType);
  String::Trim(VarName);

  if (VarName == "") {
    bAnonymous = true;
  }

  return true;
}

bool MyASTVisitor::getStructVarInfo(ValueDecl *pDecl, string &VarType, string &VarName,
                                    bool &bIsPtr) {
  if (!pDecl) {
    return false;
  }
  if (!this->isMainFile(pDecl)) {
    return false;
  }

  AppCxt &AppCxt = AppCxt::getInstance();

  this->m_DumpDecl.PrintDecl(pDecl);

  SourceLocation MyBeginLoc = pDecl->getBeginLoc();
  SourceLocation MyCurrLoc  = pDecl->getLocation();

  const char *szBegin = this->m_pSrcMgr->getCharacterData(MyBeginLoc);
  const char *szCurr  = this->m_pSrcMgr->getCharacterData(MyCurrLoc);

  intptr_t iPtrDiff      = szCurr - szBegin;
  const intptr_t iPtrLen = szCurr - szBegin;
  if (iPtrLen <= 0) {
    AppCxt.MemoBoard.SpdLog->info("iPtrLen value should not be negative.");
    return false;
  }

  VarType = std::string(szBegin, iPtrDiff);
  VarName = pDecl->getName().data();

  QualType MyQualType = pDecl->getType();
  bIsPtr              = MyQualType->isPointerType();

  String::Trim(VarType);
  String::Trim(VarName);

  return true;
}

bool MyASTVisitor::getValueInfo(ValueDecl *pDecl, string &ValueType, string &ValueName,
                                bool &bIsPtr, bool &bIsArray, bool &bIsBuiltinType) {
  if (!pDecl) {
    return false;
  }

  if (!this->isMainFile(pDecl)) {
    return false;
  }

  AppCxt &AppCxt = AppCxt::getInstance();

  // TODO:
  // This will get var type, but need to overcome some situation:
  // 1. Type "unsigned long long int" will get "unsigned long long"
  // 2. Dependency on include file, if can't get definition, it will get "int"
  // 3. Multi-array issue,we need to process string like "[8][]" "[][][]"
  //...
  // auto VarType = pDecl->getType().getAsString();
  SourceRange srcRange      = pDecl->getSourceRange();
  SourceLocation RangeBegin = srcRange.getBegin();
  SourceLocation RangEnd    = srcRange.getEnd();
  const char *szRangeBegin  = this->m_pSrcMgr->getCharacterData(RangeBegin);
  const char *szRangeCurr   = this->m_pSrcMgr->getCharacterData(RangEnd);

  SourceLocation MyBeginLoc = pDecl->getBeginLoc();
  SourceLocation MyCurrLoc  = pDecl->getLocation();
  SourceLocation MyEndLoc   = pDecl->getEndLoc();

  const char *szBegin = this->m_pSrcMgr->getCharacterData(MyBeginLoc);
  const char *szCurr  = this->m_pSrcMgr->getCharacterData(MyCurrLoc);
  const char *szEnd   = this->m_pSrcMgr->getCharacterData(MyEndLoc);

  intptr_t iPtrDiff      = szCurr - szBegin;
  const intptr_t iPtrLen = szCurr - szBegin;
  if (iPtrLen < 0) { // Enum possible equals to ZERO.
    AppCxt.MemoBoard.SpdLog->info("iPtrLen value should not be negative.");
    return false;
  }

  string MyValueType = std::string(szBegin, iPtrDiff);

  size_t nPos = MyValueType.find(",");

  if (std::string::npos != nPos) {
    nPos        = MyValueType.find(" ");
    MyValueType = MyValueType.substr(0, nPos);
  }

  if (MyValueType.length() > 0) {
    this->removeKeywords(MyValueType);
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

ErrorDetail *MyASTVisitor::createErrorDetail(const string &FileName, const string &Suggestion) {
  return new ErrorDetail(FileName, Suggestion);
}

ErrorDetail *MyASTVisitor::createErrorDetail(Decl *pDecl, const CheckType &CheckType,
                                             const bool &bIsPtr, const bool &bIsArray,
                                             const string &TargetName, const string &Suggestion) {

  return this->createErrorDetail(pDecl, CheckType, bIsPtr, bIsArray, "", TargetName, Suggestion);
}

ErrorDetail *MyASTVisitor::createErrorDetail(Decl *pDecl, const CheckType &CheckType,
                                             const bool &bIsPtr, const bool &bIsArray,
                                             const string &TypeName, const string &TargetName,
                                             const string &Suggestion) {
  if (!pDecl) {
    return NULL;
  }

  ErrorDetail *pNew = NULL;

  string FileName;
  CodePos Pos = {0};
  if (this->getPos(pDecl, FileName, Pos.nLine, Pos.nColumn)) {
    pNew = new ErrorDetail(Pos, CheckType, bIsPtr, bIsArray, TypeName, TargetName, Suggestion);
  }
  return pNew;
}

bool MyASTVisitor::checkRuleForVariable(ValueDecl *pDecl) {
  string ValueType;
  string ValueName;

  bool bIsPtr         = false;
  bool bIsArray       = false;
  bool bIsBuiltinType = false;

  bool bStauts = this->getValueInfo(pDecl, ValueType, ValueName, bIsPtr, bIsArray, bIsBuiltinType);

  if (!bStauts) {
    return true;
  }

  AppCxt &AppCxt = AppCxt::getInstance();

  bStauts = this->m_Detect.CheckVariable(
      this->m_pConfig->General.Rules.VariableName, ValueType, ValueName,
      this->m_pConfig->Hungarian.Options.PreferUpperCamelIfMissed, bIsPtr, bIsArray);

  AppCxt.MemoBoard.Checked.nVariable++;
  if (!bStauts) {
    AppCxt.MemoBoard.Error.nVariable++;

    AppCxt.MemoBoard.ErrorDetailList.push_back(this->createErrorDetail(
        pDecl, CheckType::CT_Variable, bIsPtr, bIsArray, ValueType, ValueName, ""));
  }

  return bStauts;
}

bool MyASTVisitor::checkRuleForStructValue(ValueDecl *pDecl) {
  bool bIsPtr = false;
  string ValueType;
  string ValueName;

  bool bStatus = this->getStructVarInfo(pDecl, ValueType, ValueName, bIsPtr);
  if (!bStatus) {
    return false;
  }

  bool bResult = this->m_Detect.CheckStructVal(this->m_pConfig->General.Rules.StructValueName,
                                               ValueType, ValueName, bIsPtr);

  AppCxt &AppCxt = AppCxt::getInstance();

  AppCxt.MemoBoard.Checked.nStruct++;
  if (!bResult) {
    AppCxt.MemoBoard.Error.nStruct++;

    AppCxt.MemoBoard.ErrorDetailList.push_back(this->createErrorDetail(
        pDecl, CheckType::CT_UnionVal, bIsPtr, NOT_ARRAY, ValueType, ValueName, ""));
  }
  return true;
}

bool MyASTVisitor::checkRuleForUnionValue(ValueDecl *pDecl) {
  bool bIsPtr = false;
  string ValueType;
  string ValueName;

  bool bStatus = this->getStructVarInfo(pDecl, ValueType, ValueName, bIsPtr);
  if (!bStatus) {
    return false;
  }

  bool bResult = this->m_Detect.CheckStructVal(this->m_pConfig->General.Rules.StructValueName,
                                               ValueType, ValueName, bIsPtr);

  AppCxt &AppCxt = AppCxt::getInstance();

  AppCxt.MemoBoard.Checked.nUnion++;
  if (!bResult) {
    AppCxt.MemoBoard.Error.nUnion++;

    AppCxt.MemoBoard.ErrorDetailList.push_back(this->createErrorDetail(
        pDecl, CheckType::CT_StructVal, bIsPtr, NOT_ARRAY, ValueType, ValueName, ""));
  }
  return true;
}

bool MyASTVisitor::checkRuleForEnumValue(EnumConstantDecl *pDecl) {
  string ValueType;
  string ValueName;

  bool bIsPtr         = false;
  bool bIsArray       = false;
  bool bIsBuiltinType = false;

  bool bStauts = this->getValueInfo(pDecl, ValueType, ValueName, bIsPtr, bIsArray, bIsBuiltinType);

  if (!bStauts) {
    return false;
  }

  bStauts = this->m_Detect.CheckVariable(
      this->m_pConfig->General.Rules.EnumValueName, ValueType, ValueName,
      this->m_pConfig->Hungarian.Options.PreferUpperCamelIfMissed, bIsPtr, bIsArray);

  return bStauts;
}
