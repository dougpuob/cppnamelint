#include <memory>
#include <string>

#include "Common.h"
#include "DumpDecl.h"
#include <clang/AST/Decl.h>

// clang-format off

DumpDecl::DumpDecl() {
  AppCxt &AppCxt = AppCxt::getInstance();
}

void DumpDecl::SetSourceManager(const SourceManager *pSm) { this->m_pSm = (SourceManager *)pSm; }

bool DumpDecl::PrintDecl(Decl *pDecl) {
  if (!pDecl) {
    return false;
  }
  AppCxt& AppCxt = AppCxt::getInstance();
  
  AppCxt.MemoBoard.SpdLog->info("");
  AppCxt.MemoBoard.SpdLog->info("V==start line====================================================================V");

  if (isa<Decl>(pDecl)) {
    _PrintDecl(dyn_cast<Decl> (pDecl));
  }

  if (isa<EnumConstantDecl>(pDecl)) {
    _PrintEnumConstantDecl(dyn_cast<EnumConstantDecl> (pDecl));
  }

  if (isa<EnumDecl>(pDecl)) {
    _PrintEnumDecl(dyn_cast<EnumDecl> (pDecl));
  }

  if (isa<RecordDecl>(pDecl)) {
    _PrintRecordDecl(dyn_cast<RecordDecl> (pDecl));
  }

  if (isa<ValueDecl>(pDecl)) {
    _PrintValueDecl(dyn_cast<ValueDecl> (pDecl));
  }

  if (isa<FieldDecl>(pDecl)) {
    _PrintFieldDecl(dyn_cast<FieldDecl> (pDecl));
  }

  if (isa<VarDecl>(pDecl)) {
    _PrintVarDecl(dyn_cast<VarDecl> (pDecl));
  }

  if (isa<FunctionDecl>(pDecl)) {
    _PrintFunctionDecl(dyn_cast<FunctionDecl> (pDecl));
  }

  if (isa<ParmVarDecl>(pDecl)) {
    _PrintParmVarDecl(dyn_cast<ParmVarDecl> (pDecl));
  }

  if (isa<TypedefDecl>(pDecl)) {
    _PrintTypedefDecl(dyn_cast<TypedefDecl> (pDecl));
  }

  AppCxt.MemoBoard.SpdLog->info("----------------------------------------------------------------------------------");
  // Keep this as the last.
  if (isa<NamedDecl>(pDecl)) {
    _PrintNamedDecl(dyn_cast<NamedDecl> (pDecl));
  }

  AppCxt.MemoBoard.SpdLog->info("^==end line=======================================================================^");
  return true;
}

void DumpDecl::_PrintNamedDecl(NamedDecl *pDecl) {
  AppCxt& AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.getNameAsString()                   = {}", pDecl->getNameAsString().c_str());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.getDeclName()                       = {}", pDecl->getDeclName().getAsString().c_str());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.getDeclKindName()                   = {}", pDecl->getDeclKindName());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.getQualifiedNameAsString()          = {}", pDecl->getQualifiedNameAsString().c_str());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isCanonicalDecl()                   = {}", pDecl->isCanonicalDecl());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isCXXClassMember()                  = {}", pDecl->isCXXClassMember());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isCXXInstanceMember()               = {}", pDecl->isCXXInstanceMember());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isDefinedOutsideFunctionOrMethod()  = {}", pDecl->isDefinedOutsideFunctionOrMethod());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isDeprecated()                      = {}", pDecl->isDeprecated());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isExternallyDeclarable()            = {}", pDecl->isExternallyDeclarable());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isExternallyVisible()               = {}", pDecl->isExternallyVisible());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isFirstDecl()                       = {}", pDecl->isFirstDecl());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isFromASTFile()                     = {}", pDecl->isFromASTFile());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isFunctionOrFunctionTemplate()      = {}", pDecl->isFunctionOrFunctionTemplate());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isImplicit()                        = {}", pDecl->isImplicit());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isInAnonymousNamespace()            = {}", pDecl->isInAnonymousNamespace());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isInStdNamespace()                  = {}", pDecl->isInStdNamespace());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isInvalidDecl()                     = {}", pDecl->isInvalidDecl());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isLinkageValid()                    = {}", pDecl->isLinkageValid());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isLocalExternDecl()                 = {}", pDecl->isLocalExternDecl());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isModulePrivate()                   = {}", pDecl->isModulePrivate());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isOutOfLine()                       = {}", pDecl->isOutOfLine());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isParameterPack()                   = {}", pDecl->isParameterPack());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isReferenced()                      = {}", pDecl->isReferenced());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isTemplated()                       = {}", pDecl->isTemplated());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isTemplateDecl()                    = {}", pDecl->isTemplateDecl());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isTemplateParameter()               = {}", pDecl->isTemplateParameter());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isTemplateParameterPack()           = {}", pDecl->isTemplateParameterPack());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isThisDeclarationReferenced()       = {}", pDecl->isThisDeclarationReferenced());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isTopLevelDeclInObjCContainer()     = {}", pDecl->isTopLevelDeclInObjCContainer());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isUnavailable()                     = {}", pDecl->isUnavailable());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isUsed()                            = {}", pDecl->isUsed());
  AppCxt.MemoBoard.SpdLog->info("NamedDecl.isWeakImported()                    = {}", pDecl->isWeakImported());
}

void DumpDecl::_PrintValueDecl(ValueDecl *pDecl) {
    AppCxt& AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("ValueDecl.isWeak()                            = {}", pDecl->isWeak());
}

void DumpDecl::_PrintFieldDecl(FieldDecl *pDecl) {
    AppCxt& AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("FieldDecl.isBitField()                        = {}", pDecl->isBitField());
  AppCxt.MemoBoard.SpdLog->info("FieldDecl.isAnonymousStructOrUnion()          = {}", pDecl->isAnonymousStructOrUnion());
}

void DumpDecl::_PrintVarDecl(VarDecl *pDecl) {
    AppCxt& AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("VarDecl.isExternC()                           = {}", pDecl->isExternC());
  AppCxt.MemoBoard.SpdLog->info("VarDecl.isInExternCContext()                  = {}", pDecl->isInExternCContext());
  AppCxt.MemoBoard.SpdLog->info("VarDecl.isInExternCXXContext()                = {}", pDecl->isInExternCXXContext());
  AppCxt.MemoBoard.SpdLog->info("VarDecl.isLocalVarDecl()                      = {}", pDecl->isLocalVarDecl());
  AppCxt.MemoBoard.SpdLog->info("VarDecl.isLocalVarDeclOrParm()                = {}", pDecl->isLocalVarDeclOrParm());
  AppCxt.MemoBoard.SpdLog->info("VarDecl.isFunctionOrMethodVarDecl()           = {}", pDecl->isFunctionOrMethodVarDecl());
  AppCxt.MemoBoard.SpdLog->info("VarDecl.isStaticDataMember()                  = {}", pDecl->isStaticDataMember());
  AppCxt.MemoBoard.SpdLog->info("VarDecl.isFileVarDecl()                       = {}", pDecl->isFileVarDecl());
  AppCxt.MemoBoard.SpdLog->info("VarDecl.hasInit()                             = {}", pDecl->hasInit());
}

void DumpDecl::_PrintFunctionDecl(FunctionDecl *pDecl) {
    AppCxt& AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("FunctionDecl.getNameInfo()                    = {}", pDecl->getNameInfo().getAsString().c_str());
  AppCxt.MemoBoard.SpdLog->info("FunctionDecl.isDefined()                      = {}", pDecl->isDefined());
  AppCxt.MemoBoard.SpdLog->info("FunctionDecl.isThisDeclarationADefinition()   = {}", pDecl->isThisDeclarationADefinition());
  AppCxt.MemoBoard.SpdLog->info("FunctionDecl.doesThisDeclarationHaveABody()   = {}", pDecl->doesThisDeclarationHaveABody());
  AppCxt.MemoBoard.SpdLog->info("FunctionDecl.isVariadic()                     = {}", pDecl->isVariadic());
  AppCxt.MemoBoard.SpdLog->info("FunctionDecl.isVirtualAsWritten()             = {}", pDecl->isVirtualAsWritten());
  AppCxt.MemoBoard.SpdLog->info("FunctionDecl.isPure()                         = {}", pDecl->isPure());
  AppCxt.MemoBoard.SpdLog->info("FunctionDecl.isDefaulted()                    = {}", pDecl->isDefaulted());
  AppCxt.MemoBoard.SpdLog->info("FunctionDecl.hasPrototype()                   = {}", pDecl->hasPrototype());
  AppCxt.MemoBoard.SpdLog->info("FunctionDecl.isMain()                         = {}", pDecl->isMain());
  AppCxt.MemoBoard.SpdLog->info("FunctionDecl.isExternC()                      = {}", pDecl->isExternC());
  AppCxt.MemoBoard.SpdLog->info("FunctionDecl.isInExternCContext()             = {}", pDecl->isInExternCContext());
  AppCxt.MemoBoard.SpdLog->info("FunctionDecl.isInExternCXXContext()           = {}", pDecl->isInExternCXXContext());
  AppCxt.MemoBoard.SpdLog->info("FunctionDecl.isGlobal()                       = {}", pDecl->isGlobal());
  AppCxt.MemoBoard.SpdLog->info("FunctionDecl.isInlined()                      = {}", pDecl->isInlined());
}

void DumpDecl::_PrintParmVarDecl(ParmVarDecl *pDecl) {
    AppCxt& AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("ParmVarDecl.isObjCMethodParameter()           = {}", pDecl->isObjCMethodParameter());
  AppCxt.MemoBoard.SpdLog->info("ParmVarDecl.hasDefaultArg()                   = {}", pDecl->hasDefaultArg());
  AppCxt.MemoBoard.SpdLog->info("ParmVarDecl.hasUnparsedDefaultArg()           = {}", pDecl->hasUnparsedDefaultArg());
  AppCxt.MemoBoard.SpdLog->info("ParmVarDecl.hasInheritedDefaultArg()          = {}", pDecl->hasInheritedDefaultArg());
}

void DumpDecl::_PrintRecordDecl(RecordDecl *pDecl) {
  char *szTagKind = NULL;
  switch (pDecl->getTagKind()) {
  case TTK_Struct:
    szTagKind = "TTK_Struct";
    break;
  case TTK_Interface:
    szTagKind = "TTK_Interface";
    break;
  case TTK_Union:
    szTagKind = "TTK_Union";
    break;
  case TTK_Class:
    szTagKind = "TTK_Class";
    break;
  case TTK_Enum:
    szTagKind = "TTK_Enum";
    break;
  }

  AppCxt& AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("RecordDecl.getTagKind() [switch-case]         = {}", szTagKind);
  AppCxt.MemoBoard.SpdLog->info("RecordDecl.hasFlexibleArrayMember()           = {}", pDecl->hasFlexibleArrayMember());
  AppCxt.MemoBoard.SpdLog->info("RecordDecl.isAnonymousStructOrUnion()         = {}", pDecl->isAnonymousStructOrUnion());
  AppCxt.MemoBoard.SpdLog->info("RecordDecl.hasObjectMember()                  = {}", pDecl->hasObjectMember());
  AppCxt.MemoBoard.SpdLog->info("RecordDecl.hasVolatileMember()                = {}", pDecl->hasVolatileMember());
  AppCxt.MemoBoard.SpdLog->info("RecordDecl.isLambda()                         = {}", pDecl->isLambda());
}

void DumpDecl::_PrintTypedefDecl(TypedefDecl *pDecl) {
    AppCxt& AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("TypedefDecl");
  // TypedefDecl
  // static bool classof(const Decl *D) { return classofKind(D->getKind()); }
  // static bool classofKind(Kind K) { return K == Typedef; }
}

void DumpDecl::_PrintEnumConstantDecl(EnumConstantDecl *pDecl) {
    AppCxt& AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("EnumConstantDecl");
}

void DumpDecl::_PrintEnumDecl(EnumDecl *pDecl) {
    AppCxt& AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("EnumDecl");
}

void DumpDecl::_PrintDecl(Decl *pDecl) {
  //AppCxt& AppCxt = AppCxt::getInstance();
  // SourceLocation MyBeginLoc = pDecl->getBeginLoc();
  // SourceLocation MyCurrLoc = pDecl->getLocation();
  // SourceLocation MyEndLoc = pDecl->getEndLoc();

  // const char *szBegin = this->m_pSm->getCharacterData(MyBeginLoc);
  // const char *szCurr = this->m_pSm->getCharacterData(MyCurrLoc);
  // const char *szEnd = this->m_pSm->getCharacterData(MyEndLoc);
  // pDecl->
  // AppCxt.MemoBoard.SpdLog->info("Decl.getBeginLoc().printToString              = {}",
  // pDecl->getBeginLoc().printToString(*this->m_pSm).c_str()); AppCxt.MemoBoard.SpdLog->info(" = {}",
  // szBegin); AppCxt.MemoBoard.SpdLog->info("Decl.getLocation().printToString              = {}",
  // pDecl->getLocation().printToString(*this->m_pSm).c_str()); AppCxt.MemoBoard.SpdLog->info(" = {}",
  // szCurr); AppCxt.MemoBoard.SpdLog->info("Decl.getEndLoc().printToString                = {}",
  // pDecl->getEndLoc().printToString(*this->m_pSm).c_str()); AppCxt.MemoBoard.SpdLog->info(" = {}",
  // szEnd);
  //AppCxt.MemoBoard.SpdLog->info("Decl");
}

void DumpDecl::_PrintSrcLocStr(Decl *pDecl) {
  SourceLocation MyBeginLoc = pDecl->getBeginLoc();
  SourceLocation MyCurrLoc  = pDecl->getLocation();
  SourceLocation MyEndLoc   = pDecl->getEndLoc();

  const char *szBegin = this->m_pSm->getCharacterData(MyBeginLoc);
  const char *szCurr  = this->m_pSm->getCharacterData(MyCurrLoc);
  const char *szEnd   = this->m_pSm->getCharacterData(MyEndLoc);

  AppCxt& AppCxt = AppCxt::getInstance();
  AppCxt.MemoBoard.SpdLog->info("Decl.getBeginLoc().printToString              = {}",
                  pDecl->getBeginLoc().printToString(*this->m_pSm).c_str());
  AppCxt.MemoBoard.SpdLog->info("Decl.getLocation().printToString              = {}",
                  pDecl->getLocation().printToString(*this->m_pSm).c_str());
  AppCxt.MemoBoard.SpdLog->info("Decl.getEndLoc().printToString                = {}",
                  pDecl->getEndLoc().printToString(*this->m_pSm).c_str());

  if ((szCurr - szBegin) > 0) {
    string Begin2Curr(szBegin, szCurr - szBegin);
    AppCxt.MemoBoard.SpdLog->info("Begin2Curr                                    = {}",
                    Begin2Curr.c_str());
  }

  if ((szEnd - szBegin) > 0) {
    string Begin2End(szBegin, szEnd - szBegin);
    AppCxt.MemoBoard.SpdLog->info("Begin2End                                     = {}",
                    Begin2End.c_str());
  }
  if (szCurr - szEnd) {
    string Curr2End(szCurr, szCurr - szEnd);
    AppCxt.MemoBoard.SpdLog->info("Curr2End                                      = {}",
                    Curr2End.c_str());
  }
}
// clang-format on