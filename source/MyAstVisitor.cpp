#include <iomanip>

#include "Common.h"
#include "MyAstVisitor.h"
#include "spdlog/spdlog.h"

using namespace namelint;

MyASTVisitor::MyASTVisitor(const SourceManager *pSM, const ASTContext *pAstCxt,
                           const Config *pConfig) {
  AppCxt &AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("[{}] (==", __func__);
  this->m_DumpDecl.SetSourceManager(pSM);
  this->m_pSrcMgr = pSM;
  this->m_pAstCxt = (ASTContext *)pAstCxt;
  this->m_pConfig = pConfig->GetData();
  AppCxt.MemoBoard.SpdLog->info("[{}] ==)", __func__);
}

// Iterator that traverses the base classes of a class.
bool MyASTVisitor::VisitCXXRecordDecl(CXXRecordDecl * pDecl) {
  AppCxt &AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("[{}] (==", __func__);
  this->m_DumpDecl.PrintDecl(pDecl);

  if (!this->m_pConfig->General.Options.bCheckClass) {
      AppCxt.MemoBoard.SpdLog->info("Skipped, becuase config file is disable. (bCheckClass)");
      AppCxt.MemoBoard.SpdLog->info("{} ==)| Skipped.", __func__);
      return true;
  }

  if (pDecl->isUnion()) {
      AppCxt.MemoBoard.SpdLog->info("{} ==)| Skipped. (Union)", __func__);
      return true;
  }
 
  string ClassName;
  bool bResult = this->getClassInfo(pDecl, ClassName);

  // This FunctionDecl may just an external function.
  if (pDecl->isInvalidDecl()) {
      AppCxt.MemoBoard.SpdLog->info("Found an invalid CXXRecordDecl. ({})", ClassName.c_str());

      AppCxt.MemoBoard.Assert.nInvalidDecl++;

      if (true == this->m_pConfig->General.Options.bBypassInvalidDecl) {
          AppCxt.MemoBoard.SpdLog->info("{} ==)| Bypass invalid decl.", __func__);
          return true;
      }
  }

  // struct
  if (pDecl->isStruct() && pDecl->methods().empty()) {
  }
  // class or struct(class) 
  else {
      if (!bResult) {
          AppCxt.MemoBoard.SpdLog->info("{} ==) x Failed to call VisitCXXRecordDecl()", __func__);
          return true;
      }

      AppCxt.MemoBoard.Checked.nClass++;
      if (bResult) {
          bool bIsPtr = false;
          bool bIsArray = false;
          bResult = this->m_Detect.CheckClass(this->m_pConfig->General.Rules.ClassName, ClassName, pDecl->isAbstract());

          if (!bResult) {
              AppCxt.MemoBoard.Error.nClass++;

              AppCxt.MemoBoard.ErrorDetailList.push_back(
                  this->createErrorDetail(pDecl, CheckType::CT_Class, FALSE, FALSE, ClassName, ""));
          }
      }
  }





  AppCxt.MemoBoard.SpdLog->info("[{}] ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitFunctionDecl(clang::FunctionDecl *pDecl) {
  AppCxt &AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("[{}] (==", __func__);

  if (!this->m_pConfig->General.Options.bCheckFunctionName) {
    AppCxt.MemoBoard.SpdLog->info("Skipped, becuase config file is disable. (bCheckFunctionName)");
    AppCxt.MemoBoard.SpdLog->info("[{}] ==)", __func__);
    return true;
  }

  string FuncName;
  bool bResult = this->getFunctionInfo(pDecl, FuncName);
  if (!bResult) {
    AppCxt.MemoBoard.SpdLog->info("{} ==) x Failed to call getFunctionInfo()", __func__);
    return true;
  }

  AppCxt.MemoBoard.Checked.nFunction++;

  // This FunctionDecl may just an external function.
  if (pDecl->isInvalidDecl()) {
    AppCxt.MemoBoard.SpdLog->info("Found an invalid FunctionDecl. ({})", FuncName.c_str());

    AppCxt.MemoBoard.Assert.nInvalidDecl++;

    if (true == this->m_pConfig->General.Options.bBypassInvalidDecl) {
      AppCxt.MemoBoard.SpdLog->info("{} ==)| Bypass invalid decl.", __func__);
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

  AppCxt.MemoBoard.SpdLog->info("[{}] ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitCXXMethodDecl(CXXMethodDecl *pDecl) {
  AppCxt &AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("[{}] (==", __func__);

  AppCxt.MemoBoard.SpdLog->info("Name = {}", pDecl->getNameAsString());
  this->m_DumpDecl.PrintDecl(pDecl);

  AppCxt.MemoBoard.SpdLog->info("[{}] ==)", __func__);
  return true;
}

// Represents a struct/union/class.
bool MyASTVisitor::VisitRecordDecl(RecordDecl *pDecl) {
  AppCxt &AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("[{}] (==", __func__);
  if (!this->isMainFile(pDecl)) {
    AppCxt.MemoBoard.SpdLog->info("{} ==)x Is NOT in main file.", __func__);
    return true;
  }

  AppCxt.MemoBoard.SpdLog->info("%s", __func__);

  this->m_DumpDecl.PrintDecl(pDecl);

  bool bStatus   = false;
  string VarName = pDecl->getNameAsString();

  if (pDecl->isInvalidDecl()) {
    AppCxt.MemoBoard.SpdLog->info("Found an invalid RecordDecl. ({})", VarName.c_str());

    AppCxt.MemoBoard.Assert.nInvalidDecl++;

    if (true == this->m_pConfig->General.Options.bBypassInvalidDecl) {
      AppCxt.MemoBoard.SpdLog->info("{} ==)| Bypass invalid decl.", __func__);
      return true;
    }
  }

  switch (pDecl->getTagKind()) {
  case TTK_Struct: {
    if (VarName.empty()) {
      AppCxt.MemoBoard.SpdLog->info("It is an anonymous structure.");
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
      AppCxt.MemoBoard.SpdLog->info("It is an anonymous union.");
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
  case TTK_Interface:
    VarName = "TTK_Interface";
    break;
  case TTK_Enum:
    VarName = "TTK_Enum";
    break;
  default:
    VarName = "??";
  }

  AppCxt.MemoBoard.SpdLog->info("[{}] ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitVarDecl(VarDecl *pDecl) {
  AppCxt &AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("[{}] (==", __func__);
  this->m_DumpDecl.PrintDecl(pDecl);

  if (!this->m_pConfig->General.Options.bCheckVariableName) {
    AppCxt.MemoBoard.SpdLog->info("Skipped, becuase config file is disable. (bCheckVariableName)");
    AppCxt.MemoBoard.SpdLog->info("{} ==)| Skipped.", __func__);
    return true;
  }

  if (pDecl->isInvalidDecl()) {
    AppCxt.MemoBoard.SpdLog->info("Found an invalid VarDecl. ({})", pDecl->getName().str());

    AppCxt.MemoBoard.Assert.nInvalidDecl++;

    if (true == this->m_pConfig->General.Options.bBypassInvalidDecl) {
      AppCxt.MemoBoard.SpdLog->info("{} ==)| Bypass invalid decl.", __func__);
      return true;
    }
  }

  if (isa<ParmVarDecl>(pDecl)) {
    AppCxt.MemoBoard.SpdLog->info("{} ==)|", __func__);
    return true;
  }

  bool bRet = checkRuleForVariable(pDecl);
  AppCxt.MemoBoard.SpdLog->info("[{}] ==)", __func__);
  return true;
}

// Represents a member of a struct/union/class.
bool MyASTVisitor::VisitFieldDecl(FieldDecl *pDecl) {
  AppCxt &AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("[{}] (==", __func__);
  this->m_DumpDecl.PrintDecl(pDecl);

  if (!this->m_pConfig->General.Options.bCheckVariableName) {
    AppCxt.MemoBoard.SpdLog->info("Skipped, becuase config file is disable. (bCheckVariableName)");
    AppCxt.MemoBoard.SpdLog->info("{} ==)| Skipped.", __func__);
    return true;
  }

  if (pDecl->isInvalidDecl()) {
    AppCxt.MemoBoard.SpdLog->info("Found an invalid FieldDecl. ({})", pDecl->getName().str());

    AppCxt.MemoBoard.Assert.nInvalidDecl++;

    if (true == this->m_pConfig->General.Options.bBypassInvalidDecl) {
      AppCxt.MemoBoard.SpdLog->info("{} ==)| Bypass invalid decl.", __func__);
      return true;
    }
  }

  bool bRet = false;
  auto ParentTag = pDecl->getParent()->getTagKind();
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
  }
  }

  AppCxt.MemoBoard.SpdLog->info("[{}] ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitReturnStmt(ReturnStmt *pRetStmt) {
  AppCxt &AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("[{}] (==", __func__);

  const Expr *pExpr = pRetStmt->getRetValue();
  if (pExpr) {
    clang::QualType MyQualType = pExpr->getType();
    AppCxt.MemoBoard.SpdLog->info("MyQualType.getAsString() = {}", MyQualType.getAsString());
  }

  AppCxt.MemoBoard.SpdLog->info("[{}] ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitParmVarDecl(ParmVarDecl *pDecl) {
  AppCxt &AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("[{}] (==", __func__);
  this->m_DumpDecl.PrintDecl(pDecl);

  string VarType;
  string VarName;

  bool bIsPtr     = false;
  bool bIsArray   = false;
  bool bAnonymous = false;
  bool bResult    = false;

  if (pDecl->isInvalidDecl()) {
    AppCxt.MemoBoard.SpdLog->info("Found an invalid ParmVarDecl. ({})", pDecl->getName().str());

    AppCxt.MemoBoard.Assert.nInvalidDecl++;

    if (true == this->m_pConfig->General.Options.bBypassInvalidDecl) {
      AppCxt.MemoBoard.SpdLog->info("{} ==)| Bypass invalid decl.", __func__);
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

  AppCxt.MemoBoard.SpdLog->info("[{}] ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitTypedefDecl(TypedefDecl *pDecl) {
  AppCxt &AppCxt = AppCxt::getInstance();

  AppCxt.MemoBoard.SpdLog->info("[{}] (==", __func__);
  this->m_DumpDecl.PrintDecl(pDecl);

  AppCxt.MemoBoard.SpdLog->info("[{}] ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitEnumConstantDecl(EnumConstantDecl *pDecl) {
  AppCxt &AppCxt = AppCxt::getInstance();

  AppCxt.MemoBoard.SpdLog->info("[{}] (==", __func__);
  this->m_DumpDecl.PrintDecl(pDecl);

  AppCxt.MemoBoard.Checked.nEnum++;

  string EnumValName = pDecl->getNameAsString();

  if (pDecl->isInvalidDecl()) {
    AppCxt.MemoBoard.SpdLog->info("Found an invalid EnumConstantDecl. ({})", EnumValName.c_str());

    AppCxt.MemoBoard.Assert.nInvalidDecl++;

    if (true == this->m_pConfig->General.Options.bBypassInvalidDecl) {
      AppCxt.MemoBoard.SpdLog->info("{} ==)| Bypass invalid decl.", __func__);
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

  AppCxt.MemoBoard.SpdLog->info("[{}] ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitEnumDecl(EnumDecl *pDecl) {
  AppCxt &AppCxt = AppCxt::getInstance();

  AppCxt.MemoBoard.SpdLog->info("[{}] (==", __func__);
  this->m_DumpDecl.PrintDecl(pDecl);

  AppCxt.MemoBoard.pLastEnumDecl = pDecl;
  AppCxt.MemoBoard.Checked.nEnum++;

  string EnumTagName = pDecl->getNameAsString();
  if (!EnumTagName.empty()) {

    if (pDecl->isInvalidDecl()) {
      AppCxt.MemoBoard.SpdLog->info("Found an invalid EnumDecl. ({})", EnumTagName);

      AppCxt.MemoBoard.Assert.nInvalidDecl++;

      if (true == this->m_pConfig->General.Options.bBypassInvalidDecl) {
        AppCxt.MemoBoard.SpdLog->info("{} ==)| Bypass invalid decl.", __func__);
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

  AppCxt.MemoBoard.SpdLog->info("[{}] ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitTagTypeLoc(TagTypeLoc TagTypeLocDecl) {
  AppCxt &AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("[{}] (==", __func__);

  // TagDecl* pDecl = TL.getDecl();

  // SourceLocation MyBeginLoc = pDecl->getBeginLoc();
  // SourceLocation MyCurrLoc = pDecl->getLocation();
  // SourceLocation MyEndLoc = pDecl->getEndLoc();

  // const char *szBegin = this->m_pSrcMgr->getCharacterData(MyBeginLoc);
  // const char *szCurr = this->m_pSrcMgr->getCharacterData(MyCurrLoc);
  // const char *szEnd = this->m_pSrcMgr->getCharacterData(MyEndLoc);

  AppCxt.MemoBoard.SpdLog->info("[{}] ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitArrayTypeLoc(ArrayTypeLoc TL) {
  AppCxt &AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("[{}] (==", __func__);
  // SourceLocation MyBeginLoc = TL.getBeginLoc();
  // SourceLocation MyEndLoc = TL.getEndLoc();
  //
  // const char *szBegin = this->m_pSrcMgr->getCharacterData(MyBeginLoc);
  // const char *szEnd = this->m_pSrcMgr->getCharacterData(MyEndLoc);
  AppCxt.MemoBoard.SpdLog->info("[{}] ==)", __func__);
  return true;
}

bool MyASTVisitor::VisitFunctionTypeLoc(FunctionTypeLoc TL, bool SkipResultType) {
  AppCxt &AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("[{}] (==", __func__);
  SourceLocation MyBeginLoc = TL.getBeginLoc();
  SourceLocation MyEndLoc   = TL.getEndLoc();

  const char *szBegin = this->m_pSrcMgr->getCharacterData(MyBeginLoc);
  const char *szEnd   = this->m_pSrcMgr->getCharacterData(MyEndLoc);

  AppCxt.MemoBoard.SpdLog->info("[{}] ==)", __func__);
  return true;
}