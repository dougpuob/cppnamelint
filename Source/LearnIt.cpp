#include "LearnIt.h"

#include <memory>
#include <string>

using namespace DcLib;

LearnIt::LearnIt() {}

bool LearnIt::LearnFunctionDecl(FunctionDecl &Decl) {
  // clang-format off

  DcLib::Log::Out(INFO_ALL, "sdddddddddddddddd");
  //m_pLogger->Write(TypeAll, "v--------------------------------------------------------------------------------v");

    /*
  PLOGI << "v--------------------------------------------------------------------------------v";
  PLOGI << "Decl.getName()                            = "       << Decl.getName().str();
  PLOGI << "Decl.getNameAsString()                    = "       << Decl.getNameAsString();
  PLOGI << "Decl.getDeclName()                        = "       << Decl.getDeclName().getAsString();
  // PLOGI << "Decl.getDeclKindName()                 = "       << Decl.getDeclKindName());;
  PLOGI << "Decl.getQualifiedNameAsString()           = "       << Decl.getQualifiedNameAsString();
  // PLOGI << "Decl.InEnclosingNamespaceSetOf()       = "       <<  Decl.InEnclosingNamespaceSetOf()); 
  PLOGI << "Decl.isCanonicalDecl()                    = "       << Decl.isCanonicalDecl();
  PLOGI << "Decl.isClosure()                          = "       << Decl.isClosure();
  PLOGI << "Decl.isCXXClassMember()                   = "       << Decl.isCXXClassMember();
  PLOGI << "Decl.isCXXInstanceMember()                = "       << Decl.isCXXInstanceMember();
  PLOGI << "Decl.isExternCXXContext()                 = "       << Decl.isExternCXXContext();
  // PLOGI << "Decl.isDeclInLexicalTraversal()        = "       << Decl.isDeclInLexicalTraversal());;
  PLOGI << "Decl.isDefinedOutsideFunctionOrMethod()   = "       << Decl.isDefinedOutsideFunctionOrMethod();
  PLOGI << "Decl.isDependentContext()                 = "       << Decl.isDependentContext();
  PLOGI << "Decl.isDeprecated()                       = "       << Decl.isDeprecated();
  PLOGI << "Decl.isExported()                         = "       << Decl.isExported();
  PLOGI << "Decl.isExternallyDeclarable()             = "       << Decl.isExternallyDeclarable();
  PLOGI << "Decl.isExternallyVisible()                = "       << Decl.isExternallyVisible();
  PLOGI << "Decl.isExternCContext()                   = "       << Decl.isExternCContext();
  PLOGI << "Decl.isExternCXXContext()                 = "       << Decl.isExternCXXContext();
  PLOGI << "Decl.isFileContext()                      = "       << Decl.isFileContext();
  PLOGI << "Decl.isFirstDecl()                        = "       << Decl.isFirstDecl();
  PLOGI << "Decl.isFromASTFile()                      = "       << Decl.isFromASTFile();
  PLOGI << "Decl.isFunctionOrFunctionTemplate()       = "       << Decl.isFunctionOrFunctionTemplate();
  PLOGI << "Decl.isFunctionOrMethod()                 = "       << Decl.isFunctionOrMethod();
  PLOGI << "Decl.isHidden()                           = "       << Decl.isHidden();
  PLOGI << "Decl.isImplicit()                         = "       << Decl.isImplicit();
  PLOGI << "Decl.isInAnonymousNamespace()             = "       << Decl.isInAnonymousNamespace();
  // PLOGI << "Decl.isInIdentifierNamespace()         = "       << Decl.isInIdentifierNamespace());
  PLOGI << "Decl.isInlineNamespace()                  = "       << Decl.isInlineNamespace();
  PLOGI << "Decl.isInStdNamespace()                   = "       << Decl.isInStdNamespace();
  PLOGI << "Decl.isInvalidDecl()                      = "       << Decl.isInvalidDecl();
  PLOGI << "Decl.isLexicallyWithinFunctionOrMethod()  = "       << Decl.isLexicallyWithinFunctionOrMethod();
  PLOGI << "Decl.isLinkageValid()                     = "       << Decl.isLinkageValid();
  PLOGI << "Decl.isLocalExternDecl()                  = "       << Decl.isLocalExternDecl();
  PLOGI << "Decl.isLookupContext()                    = "       << Decl.isLookupContext();
  PLOGI << "Decl.isModulePrivate()                    = "       << Decl.isModulePrivate();
  // PLOGI << "Decl.isMsStruct()                      = "       << Decl.isMsStruct());
  PLOGI << "Decl.isCompleteDefinitisNamespaceion()    = "       << Decl.isNamespace();
  PLOGI << "Decl.isObjCContainer()                    = "       << Decl.isObjCContainer();
  PLOGI << "Decl.isOutOfLine()                        = "       << Decl.isOutOfLine();
  PLOGI << "Decl.isParameterPack()                    = "       << Decl.isParameterPack();
  PLOGI << "Decl.isRecord()                           = "       << Decl.isRecord();
  PLOGI << "Decl.isReferenced()                       = "       << Decl.isReferenced();
  PLOGI << "Decl.isStdNamespace()                     = "       << Decl.isStdNamespace();
  // PLOGI << "Decl.isTagIdentifierNamespace()        = "       << Decl.isTagIdentifierNamespace());;
  PLOGI << "Decl.isTemplated()                        = "       << Decl.isTemplated();
  PLOGI << "Decl.isTemplateDecl()                     = "       << Decl.isTemplateDecl();
  PLOGI << "Decl.isTemplateParameter()                = "       << Decl.isTemplateParameter();
  PLOGI << "Decl.isTemplateParameterPack()            = "       << Decl.isTemplateParameterPack();
  PLOGI << "Decl.isThisDeclarationADefinition()       = "       << Decl.isThisDeclarationADefinition();
  PLOGI << "Decl.isThisDeclarationReferenced()        = "       << Decl.isThisDeclarationReferenced();
  PLOGI << "Decl.isTopLevelDeclInObjCContainer()      = "       << Decl.isTopLevelDeclInObjCContainer();
  PLOGI << "Decl.isTranslationUnit()                  = "       << Decl.isTranslationUnit();
  PLOGI << "Decl.isTransparentContext()               = "       << Decl.isTransparentContext();
  PLOGI << "Decl.isUnavailable()                      = "       << Decl.isUnavailable();
  PLOGI << "Decl.isUsed()                             = "       << Decl.isUsed();
  PLOGI << "Decl.isWeakImported()                     = "       << Decl.isWeakImported();
  PLOGI << "^--------------------------------------------------------------------------------^";

    */
  // clang-format on
  return true;
}

bool LearnIt::LearnRecordDecl(RecordDecl &Decl) {
  // clang-format off
    /*
    PLOGI << "v--------------------------------------------------------------------------------v";
    PLOGI << "Decl.getName()                            = " << Decl.getName().str();
    PLOGI << "Decl.getNameAsString()                    = " << Decl.getNameAsString();
    PLOGI << "Decl.getDeclName()                        = " << Decl.getDeclName().getAsString();
    PLOGI << "Decl.getKindName()                        = " << Decl.getKindName().str();
    // PLOGI << "Decl.getDeclKindName()                 = " << Decl.getDeclKindName());
    PLOGI << "Decl.getQualifiedNameAsString()           = " << Decl.getQualifiedNameAsString();
    // PLOGI << "Decl.InEnclosingNamespaceSetOf()          = " << Decl.InEnclosingNamespaceSetOf());
    PLOGI << "Decl.isAnonymousStructOrUnion()           = " << Decl.isAnonymousStructOrUnion();
    PLOGI << "Decl.isBeingDefined()                     = " << Decl.isBeingDefined();
    PLOGI << "Decl.isCanonicalDecl()                    = " << Decl.isCanonicalDecl();
    PLOGI << "Decl.isCapturedRecord()                   = " << Decl.isCapturedRecord();
    PLOGI << "Decl.isClass()                            = " << Decl.isClass();
    PLOGI << "Decl.isClosure()                          = " << Decl.isClosure();
    PLOGI << "Decl.isCompleteDefinition()               = " << Decl.isCompleteDefinition();
    PLOGI << "Decl.isCompleteDefinitionRequired()       = " << Decl.isCompleteDefinitionRequired();
    PLOGI << "Decl.isCXXClassMember()                   = " << Decl.isCXXClassMember();
    PLOGI << "Decl.isCXXInstanceMember()                = " << Decl.isCXXInstanceMember();
    PLOGI << "Decl.isExternCXXContext()                 = " << Decl.isExternCXXContext();
    // PLOGI << "Decl.isDeclInLexicalTraversal()        = " << Decl.isDeclInLexicalTraversal());;
    PLOGI << "Decl.isDefinedOutsideFunctionOrMethod()   = " << Decl.isDefinedOutsideFunctionOrMethod();
    PLOGI << "Decl.isDependentContext()                 = " << Decl.isDependentContext();
    PLOGI << "Decl.isDependentType()                    = " << Decl.isDependentType();
    PLOGI << "Decl.isDeprecated()                       = " << Decl.isDeprecated();
    PLOGI << "Decl.isEmbeddedInDeclarator()             = " << Decl.isEmbeddedInDeclarator();
    PLOGI << "Decl.isEnum()                             = " << Decl.isEnum();
    PLOGI << "Decl.isExported()                         = " << Decl.isExported();
    PLOGI << "Decl.isExternallyDeclarable()             = " << Decl.isExternallyDeclarable();
    PLOGI << "Decl.isExternallyVisible()                = " << Decl.isExternallyVisible();
    PLOGI << "Decl.isExternCContext()                   = " << Decl.isExternCContext();
    PLOGI << "Decl.isExternCXXContext()                 = " << Decl.isExternCXXContext();
    PLOGI << "Decl.isFileContext()                      = " << Decl.isFileContext();
    PLOGI << "Decl.isFirstDecl()                        = " << Decl.isFirstDecl();
    PLOGI << "Decl.isFreeStanding()                     = " << Decl.isFreeStanding();
    PLOGI << "Decl.isFromASTFile()                      = " << Decl.isFromASTFile();
    PLOGI << "Decl.isFunctionOrFunctionTemplate()       = " << Decl.isFunctionOrFunctionTemplate();
    PLOGI << "Decl.isFunctionOrMethod()                 = " << Decl.isFunctionOrMethod();
    PLOGI << "Decl.isHidden()                           = " << Decl.isHidden();
    PLOGI << "Decl.isImplicit()                         = " << Decl.isImplicit();
    PLOGI << "Decl.isInAnonymousNamespace()             = " << Decl.isInAnonymousNamespace();
    // PLOGI << "Decl.isInIdentifierNamespace()         = " << Decl.isInIdentifierNamespace());
    PLOGI << "Decl.isInjectedClassName()                = " << Decl.isInjectedClassName();
    PLOGI << "Decl.isInlineNamespace()                  = " << Decl.isInlineNamespace();
    PLOGI << "Decl.isInStdNamespace()                   = " << Decl.isInStdNamespace();
    PLOGI << "Decl.isInterface()                        = " << Decl.isInterface();
    PLOGI << "Decl.isInvalidDecl()                      = " << Decl.isInvalidDecl();
    PLOGI << "Decl.isLambda()                           = " << Decl.isLambda();
    PLOGI << "Decl.isLexicallyWithinFunctionOrMethod()  = " << Decl.isLexicallyWithinFunctionOrMethod();
    PLOGI << "Decl.isLinkageValid()                     = " << Decl.isLinkageValid();
    PLOGI << "Decl.isLocalExternDecl()                  = " << Decl.isLocalExternDecl();
    PLOGI << "Decl.isLookupContext()                    = " << Decl.isLookupContext();
    PLOGI << "Decl.isModulePrivate()                    = " << Decl.isModulePrivate();
    // PLOGI << "Decl.isMsStruct()                      = " << Decl.isMsStruct());
    PLOGI << "Decl.isCompleteDefinitisNamespaceion()    = " << Decl.isNamespace();
    PLOGI << "Decl.isNonTrivialToPrimitiveCopy()        = " << Decl.isNonTrivialToPrimitiveCopy();
    PLOGI << "Decl.isNonTrivialToPrimitiveDefaultInit() = " << Decl.isNonTrivialToPrimitiveDefaultInitialize();
    PLOGI << "Decl.isNonTrivialToPrimitiveDestroy()     = " << Decl.isNonTrivialToPrimitiveDestroy();
    PLOGI << "Decl.isObjCContainer()                    = " << Decl.isObjCContainer();
    PLOGI << "Decl.isOutOfLine()                        = " << Decl.isOutOfLine();
    PLOGI << "Decl.isParamDestroyedInCallee()           = " << Decl.isParamDestroyedInCallee();
    PLOGI << "Decl.isParameterPack()                    = " << Decl.isParameterPack();
    PLOGI << "Decl.isRecord()                           = " << Decl.isRecord();
    PLOGI << "Decl.isReferenced()                       = " << Decl.isReferenced();
    PLOGI << "Decl.isStdNamespace()                     = " << Decl.isStdNamespace();
    PLOGI << "Decl.isStruct()                           = " << Decl.isStruct();
    // PLOGI << "Decl.isTagIdentifierNamespace()        = " << Decl.isTagIdentifierNamespace());
    PLOGI << "Decl.isTemplated()                        = " << Decl.isTemplated();
    PLOGI << "Decl.isTemplateDecl()                     = " << Decl.isTemplateDecl();
    PLOGI << "Decl.isTemplateParameter()                = " << Decl.isTemplateParameter();
    PLOGI << "Decl.isTemplateParameterPack()            = " << Decl.isTemplateParameterPack();
    PLOGI << "Decl.isThisDeclarationADefinition()       = " << Decl.isThisDeclarationADefinition();
    PLOGI << "Decl.isThisDeclarationReferenced()        = " << Decl.isThisDeclarationReferenced();
    PLOGI << "Decl.isTopLevelDeclInObjCContainer()      = " << Decl.isTopLevelDeclInObjCContainer();
    PLOGI << "Decl.isTranslationUnit()                  = " << Decl.isTranslationUnit();
    PLOGI << "Decl.isTransparentContext()               = " << Decl.isTransparentContext();
    PLOGI << "Decl.isUnavailable()                      = " << Decl.isUnavailable();
    PLOGI << "Decl.isCompleteDefiniisUniontion()        = " << Decl.isUnion();
    PLOGI << "Decl.isUsed()                             = " << Decl.isUsed();
    PLOGI << "Decl.isWeakImported()                     = " << Decl.isWeakImported();
    PLOGI << "Decl.canPassInRegisters()                 = " << Decl.canPassInRegisters();
    PLOGI << "Decl.mayInsertExtraPadding()              = " << Decl.mayInsertExtraPadding();
    PLOGI << "^--------------------------------------------------------------------------------^";
    */
  // clang-format on
  return true;
}
