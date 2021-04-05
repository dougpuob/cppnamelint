#include <iomanip>

#include "Common.h"
#include "MyAstVisitor.h"

using namespace namelint;

LOG_DECISION_DEFAULT(false);

MyASTVisitor::MyASTVisitor(const SourceManager *pSM, const ASTContext *pAstCxt,
                           const Config *pConfig) {
  DcLib::Log::Out(INFO_ALL, "%s() (==", __func__);
  this->m_DumpDecl.SetSourceManager(pSM);
  this->m_pSrcMgr = pSM;
  this->m_pAstCxt = (ASTContext *)pAstCxt;
  this->m_pConfig = pConfig->GetData();
  DcLib::Log::Out(INFO_ALL, "%s() ==)", __func__);
}

bool MyASTVisitor::VisitCXXRecordDecl(CXXRecordDecl *D) {
  DcLib::Log::Out(INFO_ALL, "%s() (==", __func__);
  DcLib::Log::Out(INFO_ALL, "%s() ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitFunctionDecl(clang::FunctionDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "%s() (==", __func__);

  if (!this->m_pConfig->General.Options.bCheckFunctionName) {
    DcLib::Log::Out(INFO_ALL, "Skipped, becuase config file is disable. (bCheckFunctionName)");
    DcLib::Log::Out(INFO_ALL, "%s() ==)", __func__);
    return true;
  }

  string FuncName;
  bool bResult = this->getFunctionInfo(pDecl, FuncName);
  if (!bResult) {
    DcLib::Log::Out(INFO_ALL, "%s() ==) x Failed to call getFunctionInfo()", __func__);
    return true;
  }

  AppCxt &AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.Checked.nFunction++;

  // This FunctionDecl may just an external function.
  if (pDecl->isInvalidDecl()) {
    DcLib::Log::Out(INFO_ALL, "Found an invalid FunctionDecl. (%s)", FuncName.c_str());

    AppCxt.MemoBoard.Assert.nInvalidDecl++;

    if (true == this->m_pConfig->General.Options.bBypassInvalidDecl) {
      DcLib::Log::Out(INFO_ALL, "%s() ==)| Bypass invalid decl.", __func__);
      return true;
    }
  }

  if (bResult) {
    bool bIsPtr   = false;
    bool bIsArray = false;
    bResult = this->m_Detect.CheckFunction(this->m_pConfig->General.Rules.FunctionName, FuncName);

    if (!bResult) {
      AppCxt.MemoBoard.Error.nFunction++;

      AppCxt.MemoBoard.ErrorDetailList.push_back(
          this->createErrorDetail(pDecl, CheckType::CT_Function, bIsPtr, bIsArray, FuncName, ""));
    }
  }

  DcLib::Log::Out(INFO_ALL, "%s() ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitCXXMethodDecl(CXXMethodDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "%s() (==", __func__);
  DcLib::Log::Out(INFO_ALL, "%s() ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitRecordDecl(RecordDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "%s() (==", __func__);
  if (!this->isMainFile(pDecl)) {
    DcLib::Log::Out(INFO_ALL, "%s() ==)x Is NOT in main file.", __func__);
    return true;
  }

  DcLib::Log::Out(INFO_ALL, "%s", __func__);

  AppCxt &AppCxt = AppCxt::getInstance();
  this->m_DumpDecl.PrintDecl(pDecl);

  bool bStatus   = false;
  string VarName = pDecl->getNameAsString();

  if (pDecl->isInvalidDecl()) {
    DcLib::Log::Out(INFO_ALL, "Found an invalid RecordDecl. (%s)", VarName.c_str());

    AppCxt.MemoBoard.Assert.nInvalidDecl++;

    if (true == this->m_pConfig->General.Options.bBypassInvalidDecl) {
      DcLib::Log::Out(INFO_ALL, "%s() ==)| Bypass invalid decl.", __func__);
      return true;
    }
  }

  switch (pDecl->getTagKind()) {
  case TTK_Struct: {
    if (VarName.empty()) {
      DcLib::Log::Out(INFO_ALL, "It is an anonymous structure.");
      bStatus = true;
    } else {
      AppCxt.MemoBoard.Checked.nStruct++;

      RULETYPE RuleType = this->m_pConfig->General.Rules.StructTagName;

      bStatus = this->m_Detect.CheckStructVal(RuleType, "" /*no type*/, VarName, NOT_PTR);
      if (!bStatus) {
        AppCxt.MemoBoard.Error.nStruct++;
        AppCxt.MemoBoard.ErrorDetailList.push_back(this->createErrorDetail(
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
      AppCxt.MemoBoard.Checked.nUnion++;

      RULETYPE RuleType = this->m_pConfig->General.Rules.StructTagName;

      bStatus = this->m_Detect.CheckStructVal(RuleType, "" /*no type*/, VarName, NOT_PTR);
      if (!bStatus) {
        AppCxt.MemoBoard.Error.nUnion++;
        AppCxt.MemoBoard.ErrorDetailList.push_back(this->createErrorDetail(
            pDecl, CheckType::CT_UnionTag, NOT_PTR, NOT_ARRAY, "", VarName, ""));
      }
    }
    break;
  }
  case TTK_Class: {

    AppCxt.MemoBoard.Checked.nClass++;

    bool bStatus = this->m_Detect.CheckEnumVal(this->m_pConfig->General.Rules.ClassName, VarName);
    if (!bStatus) {
      AppCxt.MemoBoard.Error.nClass++;
      AppCxt.MemoBoard.ErrorDetailList.push_back(
          this->createErrorDetail(pDecl, CheckType::CT_Class, NOT_PTR, NOT_ARRAY, "", VarName, ""));
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

  DcLib::Log::Out(INFO_ALL, "%s() ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitVarDecl(VarDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "%s() (==", __func__);
  this->m_DumpDecl.PrintDecl(pDecl);

  if (!this->m_pConfig->General.Options.bCheckVariableName) {
    DcLib::Log::Out(INFO_ALL, "Skipped, becuase config file is disable. (bCheckVariableName)");
    DcLib::Log::Out(INFO_ALL, "%s() ==)| Skipped.", __func__);
    return true;
  }

  if (pDecl->isInvalidDecl()) {
    DcLib::Log::Out(INFO_ALL, "Found an invalid VarDecl. (%s)", pDecl->getName());

    AppCxt &AppCxt = AppCxt::getInstance();
    AppCxt.MemoBoard.Assert.nInvalidDecl++;

    if (true == this->m_pConfig->General.Options.bBypassInvalidDecl) {
      DcLib::Log::Out(INFO_ALL, "%s() ==)| Bypass invalid decl.", __func__);
      return true;
    }
  }

  if (isa<ParmVarDecl>(pDecl)) {
    DcLib::Log::Out(INFO_ALL, "%s() ==)|", __func__);
    return true;
  }

  bool bRet = checkRuleForVariable(pDecl);
  DcLib::Log::Out(INFO_ALL, "%s() ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitFieldDecl(FieldDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "%s() (==", __func__);
  this->m_DumpDecl.PrintDecl(pDecl);

  if (!this->m_pConfig->General.Options.bCheckVariableName) {
    DcLib::Log::Out(INFO_ALL, "Skipped, becuase config file is disable. (bCheckVariableName)");
    DcLib::Log::Out(INFO_ALL, "%s() ==)| Skipped.", __func__);
    return true;
  }

  if (pDecl->isInvalidDecl()) {
    DcLib::Log::Out(INFO_ALL, "Found an invalid FieldDecl. (%s)", pDecl->getName());

    AppCxt &AppCxt = AppCxt::getInstance();
    AppCxt.MemoBoard.Assert.nInvalidDecl++;

    if (true == this->m_pConfig->General.Options.bBypassInvalidDecl) {
      DcLib::Log::Out(INFO_ALL, "%s() ==)| Bypass invalid decl.", __func__);
      return true;
    }
  }

  bool bRet = false;
  auto aaa  = pDecl->getParent()->getTagKind();
  switch (pDecl->getParent()->getTagKind()) {
  case TTK_Struct: {
    bRet = checkRuleForStructValue(pDecl);
    break;
  case TTK_Class:
    bRet = checkRuleForVariable(pDecl);
    break;
  case TTK_Union:
    bRet = checkRuleForUnionValue(pDecl);
    break;
  default:
    bRet = checkRuleForStructValue(pDecl);
  }
  }

  DcLib::Log::Out(INFO_ALL, "%s() ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitReturnStmt(ReturnStmt *pRetStmt) {
  DcLib::Log::Out(INFO_ALL, "%s() (==", __func__);

  const Expr *pExpr = pRetStmt->getRetValue();
  if (pExpr) {
    clang::QualType MyQualType = pExpr->getType();
    std::string MyTypeStr      = MyQualType.getAsString();
    DcLib::Log::Out(INFO_ALL, "MyQualType.getAsString() = %s", MyTypeStr.c_str());
  }

  DcLib::Log::Out(INFO_ALL, "%s() ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitParmVarDecl(ParmVarDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "%s() (==", __func__);
  this->m_DumpDecl.PrintDecl(pDecl);

  string VarType;
  string VarName;

  bool bIsPtr     = false;
  bool bIsArray   = false;
  bool bAnonymous = false;
  bool bResult    = false;

  AppCxt &AppCxt = AppCxt::getInstance();

  if (pDecl->isInvalidDecl()) {
    DcLib::Log::Out(INFO_ALL, "Found an invalid ParmVarDecl. (%s)", pDecl->getName());

    AppCxt.MemoBoard.Assert.nInvalidDecl++;

    if (true == this->m_pConfig->General.Options.bBypassInvalidDecl) {
      DcLib::Log::Out(INFO_ALL, "%s() ==)| Bypass invalid decl.", __func__);
      return true;
    }
  }

  bool bStatus = this->getParmsInfo(pDecl, VarType, VarName, bIsPtr, bAnonymous);
  if (!bAnonymous) // if this variable doesn't have name, it doesn't need to be
                   // checked.
  {
    if (bStatus) {
      bResult = this->m_Detect.CheckVariable(
          this->m_pConfig->General.Rules.VariableName, VarType, VarName,
          this->m_pConfig->Hungarian.Options.PreferUpperCamelIfMissed, bIsPtr, bIsArray);

      AppCxt.MemoBoard.Checked.nParameter++;
      if (!bResult) {
        AppCxt.MemoBoard.Error.nParameter++;

        AppCxt.MemoBoard.ErrorDetailList.push_back(this->createErrorDetail(
            pDecl, CheckType::CT_Parameter, bIsPtr, bIsArray, VarType, VarName, ""));
      }
    }
  }

  DcLib::Log::Out(INFO_ALL, "%s() ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitTypedefDecl(TypedefDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "%s() (==", __func__);
  this->m_DumpDecl.PrintDecl(pDecl);

  AppCxt &AppCxt = AppCxt::getInstance();

  DcLib::Log::Out(INFO_ALL, "%s() ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitEnumConstantDecl(EnumConstantDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "%s() (==", __func__);
  this->m_DumpDecl.PrintDecl(pDecl);

  AppCxt &AppCxt = AppCxt::getInstance();

  AppCxt.MemoBoard.Checked.nEnum++;

  string EnumValName = pDecl->getNameAsString();

  if (pDecl->isInvalidDecl()) {
    DcLib::Log::Out(INFO_ALL, "Found an invalid EnumConstantDecl. (%s)", EnumValName.c_str());

    AppCxt.MemoBoard.Assert.nInvalidDecl++;

    if (true == this->m_pConfig->General.Options.bBypassInvalidDecl) {
      DcLib::Log::Out(INFO_ALL, "%s() ==)| Bypass invalid decl.", __func__);
      return true;
    }
  }

  bool bStatus = checkRuleForEnumValue(pDecl);
  if (!bStatus) {
    string EnumTagName = "???1";
    if (AppCxt.MemoBoard.pLastEnumDecl) {
      EnumTagName = AppCxt.MemoBoard.pLastEnumDecl->getName().str();
    }
    AppCxt.MemoBoard.Error.nEnum++;
    AppCxt.MemoBoard.ErrorDetailList.push_back(this->createErrorDetail(
        pDecl, CheckType::CT_EnumVal, NOT_PTR, NOT_ARRAY, EnumTagName, EnumValName, "???2"));
  }

  DcLib::Log::Out(INFO_ALL, "%s() ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitEnumDecl(EnumDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "%s() (==", __func__);
  this->m_DumpDecl.PrintDecl(pDecl);

  AppCxt &AppCxt = AppCxt::getInstance();

  AppCxt.MemoBoard.pLastEnumDecl = pDecl;
  AppCxt.MemoBoard.Checked.nEnum++;

  string EnumTagName = pDecl->getNameAsString();
  if (!EnumTagName.empty()) {

    if (pDecl->isInvalidDecl()) {
      DcLib::Log::Out(INFO_ALL, "Found an invalid EnumDecl. (%s)", EnumTagName.c_str());

      AppCxt.MemoBoard.Assert.nInvalidDecl++;

      if (true == this->m_pConfig->General.Options.bBypassInvalidDecl) {
        DcLib::Log::Out(INFO_ALL, "%s() ==)| Bypass invalid decl.", __func__);
        return true;
      }
    }

    bool bStatus =
        this->m_Detect.CheckEnumVal(this->m_pConfig->General.Rules.EnumTagName, EnumTagName);
    if (!bStatus) {
      AppCxt.MemoBoard.Error.nEnum++;
      AppCxt.MemoBoard.ErrorDetailList.push_back(this->createErrorDetail(
          pDecl, CheckType::CT_EnumTag, NOT_PTR, NOT_ARRAY, "", EnumTagName, ""));
    }
  }

  DcLib::Log::Out(INFO_ALL, "%s() ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitTagTypeLoc(TagTypeLoc TagTypeLocDecl) {
  DcLib::Log::Out(INFO_ALL, "%s() (==", __func__);

  // TagDecl* pDecl = TL.getDecl();

  // SourceLocation MyBeginLoc = pDecl->getBeginLoc();
  // SourceLocation MyCurrLoc = pDecl->getLocation();
  // SourceLocation MyEndLoc = pDecl->getEndLoc();

  // const char *szBegin = this->m_pSrcMgr->getCharacterData(MyBeginLoc);
  // const char *szCurr = this->m_pSrcMgr->getCharacterData(MyCurrLoc);
  // const char *szEnd = this->m_pSrcMgr->getCharacterData(MyEndLoc);

  DcLib::Log::Out(INFO_ALL, "%s() ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitArrayTypeLoc(ArrayTypeLoc TL) {
  DcLib::Log::Out(INFO_ALL, "%s() (==", __func__);
  // SourceLocation MyBeginLoc = TL.getBeginLoc();
  // SourceLocation MyEndLoc = TL.getEndLoc();
  //
  // const char *szBegin = this->m_pSrcMgr->getCharacterData(MyBeginLoc);
  // const char *szEnd = this->m_pSrcMgr->getCharacterData(MyEndLoc);
  DcLib::Log::Out(INFO_ALL, "%s() ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitFunctionTypeLoc(FunctionTypeLoc TL, bool SkipResultType) {
  DcLib::Log::Out(INFO_ALL, "%s() (==", __func__);
  SourceLocation MyBeginLoc = TL.getBeginLoc();
  SourceLocation MyEndLoc   = TL.getEndLoc();

  const char *szBegin = this->m_pSrcMgr->getCharacterData(MyBeginLoc);
  const char *szEnd   = this->m_pSrcMgr->getCharacterData(MyEndLoc);

  DcLib::Log::Out(INFO_ALL, "%s() ==)", __func__);
  return true;
}