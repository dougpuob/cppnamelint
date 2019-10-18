#include "LearnIt.h"

LearnIt::LearnIt() {
  plog::init(plog::debug, "LearnIt.log");
}


bool LearnIt::LearnFunctionDecl(FunctionDecl &Decl) {
    // clang-format OFF
  PLOGI << "---------------------------------------------------------------------------------"                  << std::endl;
  PLOGI << "Decl.getName()                            = "       << Decl.getName().str()                         << std::endl;
  PLOGI << "Decl.getNameAsString()                    = "       << Decl.getNameAsString()                       << std::endl;
  PLOGI << "Decl.getDeclName()                        = "       << Decl.getDeclName().getAsString()             << std::endl;
  // PLOGI << "Decl.getDeclKindName()                 = "       << Decl.getDeclKindName());                     << std::endl;
  PLOGI << "Decl.getQualifiedNameAsString()           = "       << Decl.getQualifiedNameAsString()              << std::endl;
  PLOGI << "---------------------------------------------------------------------------------"                  << std::endl;
  // PLOGI << "Decl.InEnclosingNamespaceSetOf()       = "       <<  Decl.InEnclosingNamespaceSetOf());          << std::endl;
  PLOGI << "Decl.isCanonicalDecl()                    = "       << Decl.isCanonicalDecl()                       << std::endl;
  PLOGI << "Decl.isClosure()                          = "       << Decl.isClosure()                             << std::endl;
  PLOGI << "Decl.isCXXClassMember()                   = "       << Decl.isCXXClassMember()                      << std::endl;
  PLOGI << "Decl.isCXXInstanceMember()                = "       << Decl.isCXXInstanceMember()                   << std::endl;
  PLOGI << "Decl.isExternCXXContext()                 = "       << Decl.isExternCXXContext()                    << std::endl;
  // PLOGI << "Decl.isDeclInLexicalTraversal()        = "       << Decl.isDeclInLexicalTraversal());            << std::endl;
  PLOGI << "Decl.isDefinedOutsideFunctionOrMethod()   = "       << Decl.isDefinedOutsideFunctionOrMethod()      << std::endl;
  PLOGI << "Decl.isDependentContext()                 = "       << Decl.isDependentContext()                    << std::endl;
  PLOGI << "Decl.isDeprecated()                       = "       << Decl.isDeprecated()                          << std::endl;
  PLOGI << "Decl.isExported()                         = "       << Decl.isExported()                            << std::endl;
  PLOGI << "Decl.isExternallyDeclarable()             = "       << Decl.isExternallyDeclarable()                << std::endl;
  PLOGI << "Decl.isExternallyVisible()                = "       << Decl.isExternallyVisible()                   << std::endl;
  PLOGI << "Decl.isExternCContext()                   = "       << Decl.isExternCContext()                      << std::endl;
  PLOGI << "Decl.isExternCXXContext()                 = "       << Decl.isExternCXXContext()                    << std::endl;
  PLOGI << "Decl.isFileContext()                      = "       << Decl.isFileContext()                         << std::endl;
  PLOGI << "Decl.isFirstDecl()                        = "       << Decl.isFirstDecl()                           << std::endl;
  PLOGI << "Decl.isFromASTFile()                      = "       << Decl.isFromASTFile()                         << std::endl;
  PLOGI << "Decl.isFunctionOrFunctionTemplate()       = "       << Decl.isFunctionOrFunctionTemplate()          << std::endl;
  PLOGI << "Decl.isFunctionOrMethod()                 = "       << Decl.isFunctionOrMethod()                    << std::endl;
  PLOGI << "Decl.isHidden()                           = "       << Decl.isHidden()                              << std::endl;
  PLOGI << "Decl.isImplicit()                         = "       << Decl.isImplicit()                            << std::endl;
  PLOGI << "Decl.isInAnonymousNamespace()             = "       << Decl.isInAnonymousNamespace()                << std::endl;
  // PLOGI << "Decl.isInIdentifierNamespace()         = "       << Decl.isInIdentifierNamespace());             << std::endl;
  PLOGI << "Decl.isInlineNamespace()                  = "       << Decl.isInlineNamespace()                     << std::endl;
  PLOGI << "Decl.isInStdNamespace()                   = "       << Decl.isInStdNamespace()                      << std::endl;
  PLOGI << "Decl.isInvalidDecl()                      = "       << Decl.isInvalidDecl()                         << std::endl;
  PLOGI << "Decl.isLexicallyWithinFunctionOrMethod()  = "       << Decl.isLexicallyWithinFunctionOrMethod()     << std::endl;
  PLOGI << "Decl.isLinkageValid()                     = "       << Decl.isLinkageValid()                        << std::endl;
  PLOGI << "Decl.isLocalExternDecl()                  = "       << Decl.isLocalExternDecl()                     << std::endl;
  PLOGI << "Decl.isLookupContext()                    = "       << Decl.isLookupContext()                       << std::endl;
  PLOGI << "Decl.isModulePrivate()                    = "       << Decl.isModulePrivate()                       << std::endl;
  // PLOGI << "Decl.isMsStruct()                      = "       << Decl.isMsStruct());                          << std::endl;
  PLOGI << "Decl.isCompleteDefinitisNamespaceion()    = "       << Decl.isNamespace()                           << std::endl;
  PLOGI << "Decl.isObjCContainer()                    = "       << Decl.isObjCContainer()                       << std::endl;
  PLOGI << "Decl.isOutOfLine()                        = "       << Decl.isOutOfLine()                           << std::endl;
  PLOGI << "Decl.isParameterPack()                    = "       << Decl.isParameterPack()                       << std::endl;
  PLOGI << "Decl.isRecord()                           = "       << Decl.isRecord()                              << std::endl;
  PLOGI << "Decl.isReferenced()                       = "       << Decl.isReferenced()                          << std::endl;
  PLOGI << "Decl.isStdNamespace()                     = "       << Decl.isStdNamespace()                        << std::endl;
  // PLOGI << "Decl.isTagIdentifierNamespace()        = "       << Decl.isTagIdentifierNamespace());            << std::endl;
  PLOGI << "Decl.isTemplated()                        = "       << Decl.isTemplated()                           << std::endl;
  PLOGI << "Decl.isTemplateDecl()                     = "       << Decl.isTemplateDecl()                        << std::endl;
  PLOGI << "Decl.isTemplateParameter()                = "       << Decl.isTemplateParameter()                   << std::endl;
  PLOGI << "Decl.isTemplateParameterPack()            = "       << Decl.isTemplateParameterPack()               << std::endl;
  PLOGI << "Decl.isThisDeclarationADefinition()       = "       << Decl.isThisDeclarationADefinition()          << std::endl;
  PLOGI << "Decl.isThisDeclarationReferenced()        = "       << Decl.isThisDeclarationReferenced()           << std::endl;
  PLOGI << "Decl.isTopLevelDeclInObjCContainer()      = "       << Decl.isTopLevelDeclInObjCContainer()         << std::endl;
  PLOGI << "Decl.isTranslationUnit()                  = "       << Decl.isTranslationUnit()                     << std::endl;
  PLOGI << "Decl.isTransparentContext()               = "       << Decl.isTransparentContext()                  << std::endl;
  PLOGI << "Decl.isUnavailable()                      = "       << Decl.isUnavailable()                         << std::endl;
  PLOGI << "Decl.isUsed()                             = "       << Decl.isUsed()                                << std::endl;
  PLOGI << "Decl.isWeakImported()                     = "       << Decl.isWeakImported()                        << std::endl;
  PLOGI << "---------------------------------------------------------------------------------"                  << std::endl;
  // clang-format ON
  return true;
}

bool LearnIt::LearnRecordDecl(RecordDecl &Decl) {
    // clang-format OFF

    PLOGI << "Hello log!";             // short macro
    PLOGI << "Hello log!";             // long macro
    PLOG(plog::debug) << "Hello log!"; // function-style macro

    PLOGI << "---------------------------------------------------------------------------------"                << std::endl;
    PLOGI << "Decl.getName()                            = " << Decl.getName().str()                             << std::endl;
    PLOGI << "Decl.getNameAsString()                    = " << Decl.getNameAsString()                           << std::endl;
    PLOGI << "Decl.getDeclName()                        = " << Decl.getDeclName().getAsString()                 << std::endl;
    PLOGI << "Decl.getKindName()                        = " << Decl.getKindName().str()                         << std::endl;
    // PLOGI << "Decl.getDeclKindName()                 = " << Decl.getDeclKindName());                         << std::endl;
    PLOGI << "Decl.getQualifiedNameAsString()           = " << Decl.getQualifiedNameAsString()                  << std::endl;
    PLOGI << "---------------------------------------------------------------------------------\n"              << std::endl;
    // PLOGI << "Decl.InEnclosingNamespaceSetOf()          = " << Decl.InEnclosingNamespaceSetOf());            << std::endl;
    PLOGI << "Decl.isAnonymousStructOrUnion()           = " << Decl.isAnonymousStructOrUnion()                  << std::endl;
    PLOGI << "Decl.isBeingDefined()                     = " << Decl.isBeingDefined()                            << std::endl;
    PLOGI << "Decl.isCanonicalDecl()                    = " << Decl.isCanonicalDecl()                           << std::endl;
    PLOGI << "Decl.isCapturedRecord()                   = " << Decl.isCapturedRecord()                          << std::endl;
    PLOGI << "Decl.isClass()                            = " << Decl.isClass()                                   << std::endl;
    PLOGI << "Decl.isClosure()                          = " << Decl.isClosure()                                 << std::endl;
    PLOGI << "Decl.isCompleteDefinition()               = " << Decl.isCompleteDefinition()                      << std::endl;
    PLOGI << "Decl.isCompleteDefinitionRequired()       = " << Decl.isCompleteDefinitionRequired()              << std::endl;
    PLOGI << "Decl.isCXXClassMember()                   = " << Decl.isCXXClassMember()                          << std::endl;
    PLOGI << "Decl.isCXXInstanceMember()                = " << Decl.isCXXInstanceMember()                       << std::endl;
    PLOGI << "Decl.isExternCXXContext()                 = " << Decl.isExternCXXContext()                        << std::endl;
    // PLOGI << "Decl.isDeclInLexicalTraversal()        = " << Decl.isDeclInLexicalTraversal());                << std::endl;
    PLOGI << "Decl.isDefinedOutsideFunctionOrMethod()   = " << Decl.isDefinedOutsideFunctionOrMethod()          << std::endl;
    PLOGI << "Decl.isDependentContext()                 = " << Decl.isDependentContext()                        << std::endl;
    PLOGI << "Decl.isDependentType()                    = " << Decl.isDependentType()                           << std::endl;
    PLOGI << "Decl.isDeprecated()                       = " << Decl.isDeprecated()                              << std::endl;
    PLOGI << "Decl.isEmbeddedInDeclarator()             = " << Decl.isEmbeddedInDeclarator()                    << std::endl;
    PLOGI << "Decl.isEnum()                             = " << Decl.isEnum()                                    << std::endl;
    PLOGI << "Decl.isExported()                         = " << Decl.isExported()                                << std::endl;
    PLOGI << "Decl.isExternallyDeclarable()             = " << Decl.isExternallyDeclarable()                    << std::endl;
    PLOGI << "Decl.isExternallyVisible()                = " << Decl.isExternallyVisible()                       << std::endl;
    PLOGI << "Decl.isExternCContext()                   = " << Decl.isExternCContext()                          << std::endl;
    PLOGI << "Decl.isExternCXXContext()                 = " << Decl.isExternCXXContext()                        << std::endl;
    PLOGI << "Decl.isFileContext()                      = " << Decl.isFileContext()                             << std::endl;
    PLOGI << "Decl.isFirstDecl()                        = " << Decl.isFirstDecl()                               << std::endl;
    PLOGI << "Decl.isFreeStanding()                     = " << Decl.isFreeStanding()                            << std::endl;
    PLOGI << "Decl.isFromASTFile()                      = " << Decl.isFromASTFile()                             << std::endl;
    PLOGI << "Decl.isFunctionOrFunctionTemplate()       = " << Decl.isFunctionOrFunctionTemplate()              << std::endl;
    PLOGI << "Decl.isFunctionOrMethod()                 = " << Decl.isFunctionOrMethod()                        << std::endl;
    PLOGI << "Decl.isHidden()                           = " << Decl.isHidden()                                  << std::endl;
    PLOGI << "Decl.isImplicit()                         = " << Decl.isImplicit()                                << std::endl;
    PLOGI << "Decl.isInAnonymousNamespace()             = " << Decl.isInAnonymousNamespace()                    << std::endl;
    // PLOGI << "Decl.isInIdentifierNamespace()         = " << Decl.isInIdentifierNamespace());                 << std::endl;
    PLOGI << "Decl.isInjectedClassName()                = " << Decl.isInjectedClassName()                       << std::endl;
    PLOGI << "Decl.isInlineNamespace()                  = " << Decl.isInlineNamespace()                         << std::endl;
    PLOGI << "Decl.isInStdNamespace()                   = " << Decl.isInStdNamespace()                          << std::endl;
    PLOGI << "Decl.isInterface()                        = " << Decl.isInterface()                               << std::endl;
    PLOGI << "Decl.isInvalidDecl()                      = " << Decl.isInvalidDecl()                             << std::endl;
    PLOGI << "Decl.isLambda()                           = " << Decl.isLambda()                                  << std::endl;
    PLOGI << "Decl.isLexicallyWithinFunctionOrMethod()  = " << Decl.isLexicallyWithinFunctionOrMethod()         << std::endl;
    PLOGI << "Decl.isLinkageValid()                     = " << Decl.isLinkageValid()                            << std::endl;
    PLOGI << "Decl.isLocalExternDecl()                  = " << Decl.isLocalExternDecl()                         << std::endl;
    PLOGI << "Decl.isLookupContext()                    = " << Decl.isLookupContext()                           << std::endl;
    PLOGI << "Decl.isModulePrivate()                    = " << Decl.isModulePrivate()                           << std::endl;
    // PLOGI << "Decl.isMsStruct()                      = " << Decl.isMsStruct());                              << std::endl;
    PLOGI << "Decl.isCompleteDefinitisNamespaceion()    = " << Decl.isNamespace()                               << std::endl;
    PLOGI << "Decl.isNonTrivialToPrimitiveCopy()        = " << Decl.isNonTrivialToPrimitiveCopy()               << std::endl;
    PLOGI << "Decl.isNonTrivialToPrimitiveDefaultInit() = " << Decl.isNonTrivialToPrimitiveDefaultInitialize()  << std::endl;
    PLOGI << "Decl.isNonTrivialToPrimitiveDestroy()     = " << Decl.isNonTrivialToPrimitiveDestroy()            << std::endl;
    PLOGI << "Decl.isObjCContainer()                    = " << Decl.isObjCContainer()                           << std::endl;
    PLOGI << "Decl.isOutOfLine()                        = " << Decl.isOutOfLine()                               << std::endl;
    PLOGI << "Decl.isParamDestroyedInCallee()           = " << Decl.isParamDestroyedInCallee()                  << std::endl;
    PLOGI << "Decl.isParameterPack()                    = " << Decl.isParameterPack()                           << std::endl;
    PLOGI << "Decl.isRecord()                           = " << Decl.isRecord()                                  << std::endl;
    PLOGI << "Decl.isReferenced()                       = " << Decl.isReferenced()                              << std::endl;
    PLOGI << "Decl.isStdNamespace()                     = " << Decl.isStdNamespace()                            << std::endl;
    PLOGI << "Decl.isStruct()                           = " << Decl.isStruct()                                  << std::endl;
    // PLOGI << "Decl.isTagIdentifierNamespace()        = " << Decl.isTagIdentifierNamespace());                << std::endl;
    PLOGI << "Decl.isTemplated()                        = " << Decl.isTemplated()                               << std::endl;
    PLOGI << "Decl.isTemplateDecl()                     = " << Decl.isTemplateDecl()                            << std::endl;
    PLOGI << "Decl.isTemplateParameter()                = " << Decl.isTemplateParameter()                       << std::endl;
    PLOGI << "Decl.isTemplateParameterPack()            = " << Decl.isTemplateParameterPack()                   << std::endl;
    PLOGI << "Decl.isThisDeclarationADefinition()       = " << Decl.isThisDeclarationADefinition()              << std::endl;
    PLOGI << "Decl.isThisDeclarationReferenced()        = " << Decl.isThisDeclarationReferenced()               << std::endl;
    PLOGI << "Decl.isTopLevelDeclInObjCContainer()      = " << Decl.isTopLevelDeclInObjCContainer()             << std::endl;
    PLOGI << "Decl.isTranslationUnit()                  = " << Decl.isTranslationUnit()                         << std::endl;
    PLOGI << "Decl.isTransparentContext()               = " << Decl.isTransparentContext()                      << std::endl;
    PLOGI << "Decl.isUnavailable()                      = " << Decl.isUnavailable()                             << std::endl;
    PLOGI << "Decl.isCompleteDefiniisUniontion()        = " << Decl.isUnion()                                   << std::endl;
    PLOGI << "Decl.isUsed()                             = " << Decl.isUsed()                                    << std::endl;
    PLOGI << "Decl.isWeakImported()                     = " << Decl.isWeakImported()                            << std::endl;
    PLOGI << "---------------------------------------------------------------------------------"                << std::endl;
    PLOGI << "Decl.isCompleteDefinition()               = " << Decl.canPassInRegisters()                        << std::endl;
    PLOGI << "Decl.isCompleteDefinition()               = " << Decl.mayInsertExtraPadding()                     << std::endl;
    PLOGI << "---------------------------------------------------------------------------------"                << std::endl;

   // clang-format ON
    return true;
}