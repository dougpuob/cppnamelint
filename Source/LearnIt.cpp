#include "LearnIt.h"

#include <memory>
#include <string>

using namespace DcLib;

LearnIt::LearnIt() {}

bool LearnIt::LearnFunctionDecl(FunctionDecl &Decl) {
  // clang-format off

  DcLib::Log::Out(INFO_ALL, "v--------------------------------------------------------------------------------v");
  DcLib::Log::Out(INFO_ALL, "Decl.getName()                            = %s" , Decl.getName().str());
  DcLib::Log::Out(INFO_ALL, "Decl.getNameAsString()                    = %s" , Decl.getNameAsString());
  DcLib::Log::Out(INFO_ALL, "Decl.getDeclName()                        = %s" , Decl.getDeclName().getAsString());
//DcLib::Log::Out(INFO_ALL, "Decl.getDeclKindName()                    = %s" , Decl.getDeclKindName());;
  DcLib::Log::Out(INFO_ALL, "Decl.getQualifiedNameAsString()           = %s" , Decl.getQualifiedNameAsString());
//DcLib::Log::Out(INFO_ALL, "Decl.InEnclosingNamespaceSetOf()          = %s" , Decl.InEnclosingNamespaceSetOf()); 
  DcLib::Log::Out(INFO_ALL, "Decl.isCanonicalDecl()                    = %B" , Decl.isCanonicalDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isClosure()                          = %B" , Decl.isClosure());
  DcLib::Log::Out(INFO_ALL, "Decl.isCXXClassMember()                   = %B" , Decl.isCXXClassMember());
  DcLib::Log::Out(INFO_ALL, "Decl.isCXXInstanceMember()                = %B" , Decl.isCXXInstanceMember());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternCXXContext()                 = %B" , Decl.isExternCXXContext());
//DcLib::Log::Out(INFO_ALL, "Decl.isDeclInLexicalTraversal()           = %B" , Decl.isDeclInLexicalTraversal());;
  DcLib::Log::Out(INFO_ALL, "Decl.isDefinedOutsideFunctionOrMethod()   = %B" , Decl.isDefinedOutsideFunctionOrMethod());
  DcLib::Log::Out(INFO_ALL, "Decl.isDependentContext()                 = %B" , Decl.isDependentContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isDeprecated()                       = %B" , Decl.isDeprecated());
  DcLib::Log::Out(INFO_ALL, "Decl.isExported()                         = %B" , Decl.isExported());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternallyDeclarable()             = %B" , Decl.isExternallyDeclarable());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternallyVisible()                = %B" , Decl.isExternallyVisible());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternCContext()                   = %B" , Decl.isExternCContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternCXXContext()                 = %B" , Decl.isExternCXXContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isFileContext()                      = %B" , Decl.isFileContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isFirstDecl()                        = %B" , Decl.isFirstDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isFromASTFile()                      = %B" , Decl.isFromASTFile());
  DcLib::Log::Out(INFO_ALL, "Decl.isFunctionOrFunctionTemplate()       = %B" , Decl.isFunctionOrFunctionTemplate());
  DcLib::Log::Out(INFO_ALL, "Decl.isFunctionOrMethod()                 = %B" , Decl.isFunctionOrMethod());
  DcLib::Log::Out(INFO_ALL, "Decl.isHidden()                           = %B" , Decl.isHidden());
  DcLib::Log::Out(INFO_ALL, "Decl.isImplicit()                         = %B" , Decl.isImplicit());
  DcLib::Log::Out(INFO_ALL, "Decl.isInAnonymousNamespace()             = %B" , Decl.isInAnonymousNamespace());
//DcLib::Log::Out(INFO_ALL, "Decl.isInIdentifierNamespace()            = %B" , Decl.isInIdentifierNamespace());
  DcLib::Log::Out(INFO_ALL, "Decl.isInlineNamespace()                  = %B" , Decl.isInlineNamespace());
  DcLib::Log::Out(INFO_ALL, "Decl.isInStdNamespace()                   = %B" , Decl.isInStdNamespace());
  DcLib::Log::Out(INFO_ALL, "Decl.isInvalidDecl()                      = %B" , Decl.isInvalidDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isLexicallyWithinFunctionOrMethod()  = %B" , Decl.isLexicallyWithinFunctionOrMethod());
  DcLib::Log::Out(INFO_ALL, "Decl.isLinkageValid()                     = %B" , Decl.isLinkageValid());
  DcLib::Log::Out(INFO_ALL, "Decl.isLocalExternDecl()                  = %B" , Decl.isLocalExternDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isLookupContext()                    = %B" , Decl.isLookupContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isModulePrivate()                    = %B" , Decl.isModulePrivate());
//DcLib::Log::Out(INFO_ALL, "Decl.isMsStruct()                         = %B" , Decl.isMsStruct());
  DcLib::Log::Out(INFO_ALL, "Decl.isCompleteDefinitisNamespaceion()    = %B" , Decl.isNamespace());
  DcLib::Log::Out(INFO_ALL, "Decl.isObjCContainer()                    = %B" , Decl.isObjCContainer());
  DcLib::Log::Out(INFO_ALL, "Decl.isOutOfLine()                        = %B" , Decl.isOutOfLine());
  DcLib::Log::Out(INFO_ALL, "Decl.isParameterPack()                    = %B" , Decl.isParameterPack());
  DcLib::Log::Out(INFO_ALL, "Decl.isRecord()                           = %B" , Decl.isRecord());
  DcLib::Log::Out(INFO_ALL, "Decl.isReferenced()                       = %B" , Decl.isReferenced());
  DcLib::Log::Out(INFO_ALL, "Decl.isStdNamespace()                     = %B" , Decl.isStdNamespace());
//DcLib::Log::Out(INFO_ALL, "Decl.isTagIdentifierNamespace()           = %B" , Decl.isTagIdentifierNamespace());;
  DcLib::Log::Out(INFO_ALL, "Decl.isTemplated()                        = %B" , Decl.isTemplated());
  DcLib::Log::Out(INFO_ALL, "Decl.isTemplateDecl()                     = %B" , Decl.isTemplateDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isTemplateParameter()                = %B" , Decl.isTemplateParameter());
  DcLib::Log::Out(INFO_ALL, "Decl.isTemplateParameterPack()            = %B" , Decl.isTemplateParameterPack());
  DcLib::Log::Out(INFO_ALL, "Decl.isThisDeclarationADefinition()       = %B" , Decl.isThisDeclarationADefinition());
  DcLib::Log::Out(INFO_ALL, "Decl.isThisDeclarationReferenced()        = %B" , Decl.isThisDeclarationReferenced());
  DcLib::Log::Out(INFO_ALL, "Decl.isTopLevelDeclInObjCContainer()      = %B" , Decl.isTopLevelDeclInObjCContainer());
  DcLib::Log::Out(INFO_ALL, "Decl.isTranslationUnit()                  = %B" , Decl.isTranslationUnit());
  DcLib::Log::Out(INFO_ALL, "Decl.isTransparentContext()               = %B" , Decl.isTransparentContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isUnavailable()                      = %B" , Decl.isUnavailable());
  DcLib::Log::Out(INFO_ALL, "Decl.isUsed()                             = %B" , Decl.isUsed());
  DcLib::Log::Out(INFO_ALL, "Decl.isWeakImported()                     = %B" , Decl.isWeakImported());
  DcLib::Log::Out(INFO_ALL, "^--------------------------------------------------------------------------------^");

  // clang-format on
  return true;
}

bool LearnIt::LearnRecordDecl(RecordDecl &Decl) {
  // clang-format off

    DcLib::Log::Out(INFO_ALL, "v--------------------------------------------------------------------------------v");
    DcLib::Log::Out(INFO_ALL, "Decl.getName()                            = %s" , Decl.getName().str());
    DcLib::Log::Out(INFO_ALL, "Decl.getNameAsString()                    = %s" , Decl.getNameAsString());
    DcLib::Log::Out(INFO_ALL, "Decl.getDeclName()                        = %s" , Decl.getDeclName().getAsString());
    DcLib::Log::Out(INFO_ALL, "Decl.getKindName()                        = %s" , Decl.getKindName().str());
 // DcLib::Log::Out(INFO_ALL, "Decl.getDeclKindName()                    = %s" , Decl.getDeclKindName());
    DcLib::Log::Out(INFO_ALL, "Decl.getQualifiedNameAsString()           = %s" , Decl.getQualifiedNameAsString());
 // DcLib::Log::Out(INFO_ALL, "Decl.InEnclosingNamespaceSetOf()          = %s" , Decl.InEnclosingNamespaceSetOf());
    DcLib::Log::Out(INFO_ALL, "Decl.isAnonymousStructOrUnion()           = %B" , Decl.isAnonymousStructOrUnion());
    DcLib::Log::Out(INFO_ALL, "Decl.isBeingDefined()                     = %B" , Decl.isBeingDefined());
    DcLib::Log::Out(INFO_ALL, "Decl.isCanonicalDecl()                    = %B" , Decl.isCanonicalDecl());
    DcLib::Log::Out(INFO_ALL, "Decl.isCapturedRecord()                   = %B" , Decl.isCapturedRecord());
    DcLib::Log::Out(INFO_ALL, "Decl.isClass()                            = %B" , Decl.isClass());
    DcLib::Log::Out(INFO_ALL, "Decl.isClosure()                          = %B" , Decl.isClosure());
    DcLib::Log::Out(INFO_ALL, "Decl.isCompleteDefinition()               = %B" , Decl.isCompleteDefinition());
    DcLib::Log::Out(INFO_ALL, "Decl.isCompleteDefinitionRequired()       = %B" , Decl.isCompleteDefinitionRequired());
    DcLib::Log::Out(INFO_ALL, "Decl.isCXXClassMember()                   = %B" , Decl.isCXXClassMember());
    DcLib::Log::Out(INFO_ALL, "Decl.isCXXInstanceMember()                = %B" , Decl.isCXXInstanceMember());
    DcLib::Log::Out(INFO_ALL, "Decl.isExternCXXContext()                 = %B" , Decl.isExternCXXContext());
 // DcLib::Log::Out(INFO_ALL, "Decl.isDeclInLexicalTraversal()           = %B" , Decl.isDeclInLexicalTraversal());;
    DcLib::Log::Out(INFO_ALL, "Decl.isDefinedOutsideFunctionOrMethod()   = %B" , Decl.isDefinedOutsideFunctionOrMethod());
    DcLib::Log::Out(INFO_ALL, "Decl.isDependentContext()                 = %B" , Decl.isDependentContext());
    DcLib::Log::Out(INFO_ALL, "Decl.isDependentType()                    = %B" , Decl.isDependentType());
    DcLib::Log::Out(INFO_ALL, "Decl.isDeprecated()                       = %B" , Decl.isDeprecated());
    DcLib::Log::Out(INFO_ALL, "Decl.isEmbeddedInDeclarator()             = %B" , Decl.isEmbeddedInDeclarator());
    DcLib::Log::Out(INFO_ALL, "Decl.isEnum()                             = %B" , Decl.isEnum());
    DcLib::Log::Out(INFO_ALL, "Decl.isExported()                         = %B" , Decl.isExported());
    DcLib::Log::Out(INFO_ALL, "Decl.isExternallyDeclarable()             = %B" , Decl.isExternallyDeclarable());
    DcLib::Log::Out(INFO_ALL, "Decl.isExternallyVisible()                = %B" , Decl.isExternallyVisible());
    DcLib::Log::Out(INFO_ALL, "Decl.isExternCContext()                   = %B" , Decl.isExternCContext());
    DcLib::Log::Out(INFO_ALL, "Decl.isExternCXXContext()                 = %B" , Decl.isExternCXXContext());
    DcLib::Log::Out(INFO_ALL, "Decl.isFileContext()                      = %B" , Decl.isFileContext());
    DcLib::Log::Out(INFO_ALL, "Decl.isFirstDecl()                        = %B" , Decl.isFirstDecl());
    DcLib::Log::Out(INFO_ALL, "Decl.isFreeStanding()                     = %B" , Decl.isFreeStanding());
    DcLib::Log::Out(INFO_ALL, "Decl.isFromASTFile()                      = %B" , Decl.isFromASTFile());
    DcLib::Log::Out(INFO_ALL, "Decl.isFunctionOrFunctionTemplate()       = %B" , Decl.isFunctionOrFunctionTemplate());
    DcLib::Log::Out(INFO_ALL, "Decl.isFunctionOrMethod()                 = %B" , Decl.isFunctionOrMethod());
    DcLib::Log::Out(INFO_ALL, "Decl.isHidden()                           = %B" , Decl.isHidden());
    DcLib::Log::Out(INFO_ALL, "Decl.isImplicit()                         = %B" , Decl.isImplicit());
    DcLib::Log::Out(INFO_ALL, "Decl.isInAnonymousNamespace()             = %B" , Decl.isInAnonymousNamespace());
 // DcLib::Log::Out(INFO_ALL, "Decl.isInIdentifierNamespace()            = %B" , Decl.isInIdentifierNamespace());
    DcLib::Log::Out(INFO_ALL, "Decl.isInjectedClassName()                = %B" , Decl.isInjectedClassName());
    DcLib::Log::Out(INFO_ALL, "Decl.isInlineNamespace()                  = %B" , Decl.isInlineNamespace());
    DcLib::Log::Out(INFO_ALL, "Decl.isInStdNamespace()                   = %B" , Decl.isInStdNamespace());
    DcLib::Log::Out(INFO_ALL, "Decl.isInterface()                        = %B" , Decl.isInterface());
    DcLib::Log::Out(INFO_ALL, "Decl.isInvalidDecl()                      = %B" , Decl.isInvalidDecl());
    DcLib::Log::Out(INFO_ALL, "Decl.isLambda()                           = %B" , Decl.isLambda());
    DcLib::Log::Out(INFO_ALL, "Decl.isLexicallyWithinFunctionOrMethod()  = %B" , Decl.isLexicallyWithinFunctionOrMethod());
    DcLib::Log::Out(INFO_ALL, "Decl.isLinkageValid()                     = %B" , Decl.isLinkageValid());
    DcLib::Log::Out(INFO_ALL, "Decl.isLocalExternDecl()                  = %B" , Decl.isLocalExternDecl());
    DcLib::Log::Out(INFO_ALL, "Decl.isLookupContext()                    = %B" , Decl.isLookupContext());
    DcLib::Log::Out(INFO_ALL, "Decl.isModulePrivate()                    = %B" , Decl.isModulePrivate());
 // DcLib::Log::Out(INFO_ALL, "Decl.isMsStruct()                         = %B" , Decl.isMsStruct());
    DcLib::Log::Out(INFO_ALL, "Decl.isCompleteDefinitisNamespaceion()    = %B" , Decl.isNamespace());
    DcLib::Log::Out(INFO_ALL, "Decl.isNonTrivialToPrimitiveCopy()        = %B" , Decl.isNonTrivialToPrimitiveCopy());
    DcLib::Log::Out(INFO_ALL, "Decl.isNonTrivialToPrimitiveDefaultInit() = %B" , Decl.isNonTrivialToPrimitiveDefaultInitialize());
    DcLib::Log::Out(INFO_ALL, "Decl.isNonTrivialToPrimitiveDestroy()     = %B" , Decl.isNonTrivialToPrimitiveDestroy());
    DcLib::Log::Out(INFO_ALL, "Decl.isObjCContainer()                    = %B" , Decl.isObjCContainer());
    DcLib::Log::Out(INFO_ALL, "Decl.isOutOfLine()                        = %B" , Decl.isOutOfLine());
    DcLib::Log::Out(INFO_ALL, "Decl.isParamDestroyedInCallee()           = %B" , Decl.isParamDestroyedInCallee());
    DcLib::Log::Out(INFO_ALL, "Decl.isParameterPack()                    = %B" , Decl.isParameterPack());
    DcLib::Log::Out(INFO_ALL, "Decl.isRecord()                           = %B" , Decl.isRecord());
    DcLib::Log::Out(INFO_ALL, "Decl.isReferenced()                       = %B" , Decl.isReferenced());
    DcLib::Log::Out(INFO_ALL, "Decl.isStdNamespace()                     = %B" , Decl.isStdNamespace());
    DcLib::Log::Out(INFO_ALL, "Decl.isStruct()                           = %B" , Decl.isStruct());
 // DcLib::Log::Out(INFO_ALL, "Decl.isTagIdentifierNamespace()           = %B" , Decl.isTagIdentifierNamespace());
    DcLib::Log::Out(INFO_ALL, "Decl.isTemplated()                        = %B" , Decl.isTemplated());
    DcLib::Log::Out(INFO_ALL, "Decl.isTemplateDecl()                     = %B" , Decl.isTemplateDecl());
    DcLib::Log::Out(INFO_ALL, "Decl.isTemplateParameter()                = %B" , Decl.isTemplateParameter());
    DcLib::Log::Out(INFO_ALL, "Decl.isTemplateParameterPack()            = %B" , Decl.isTemplateParameterPack());
    DcLib::Log::Out(INFO_ALL, "Decl.isThisDeclarationADefinition()       = %B" , Decl.isThisDeclarationADefinition());
    DcLib::Log::Out(INFO_ALL, "Decl.isThisDeclarationReferenced()        = %B" , Decl.isThisDeclarationReferenced());
    DcLib::Log::Out(INFO_ALL, "Decl.isTopLevelDeclInObjCContainer()      = %B" , Decl.isTopLevelDeclInObjCContainer());
    DcLib::Log::Out(INFO_ALL, "Decl.isTranslationUnit()                  = %B" , Decl.isTranslationUnit());
    DcLib::Log::Out(INFO_ALL, "Decl.isTransparentContext()               = %B" , Decl.isTransparentContext());
    DcLib::Log::Out(INFO_ALL, "Decl.isUnavailable()                      = %B" , Decl.isUnavailable());
    DcLib::Log::Out(INFO_ALL, "Decl.isCompleteDefiniisUniontion()        = %B" , Decl.isUnion());
    DcLib::Log::Out(INFO_ALL, "Decl.isUsed()                             = %B" , Decl.isUsed());
    DcLib::Log::Out(INFO_ALL, "Decl.isWeakImported()                     = %B" , Decl.isWeakImported());
    DcLib::Log::Out(INFO_ALL, "Decl.canPassInRegisters()                 = %B" , Decl.canPassInRegisters());
    DcLib::Log::Out(INFO_ALL, "Decl.mayInsertExtraPadding()              = %B" , Decl.mayInsertExtraPadding());
    DcLib::Log::Out(INFO_ALL, "^--------------------------------------------------------------------------------^");

  // clang-format on
  return true;
}
