#include "LearnIt.h"

#include <memory>
#include <string>

using namespace DcLib;

LearnIt::LearnIt() {}

bool LearnIt::PrintDecl(FunctionDecl &Decl) {
  // clang-format off

  DcLib::Log::Out(INFO_ALL, "v--------------------------------------------------------------------------------v");
  DcLib::Log::Out(INFO_ALL, "FunctionDecl");
  DcLib::Log::Out(INFO_ALL, "Decl.getName()                              = %s" , Decl.getName().str().c_str());
  DcLib::Log::Out(INFO_ALL, "Decl.getNameAsString()                      = %s" , Decl.getNameAsString().c_str());
  DcLib::Log::Out(INFO_ALL, "Decl.getDeclName()                          = %s" , Decl.getDeclName().getAsString().c_str());
//DcLib::Log::Out(INFO_ALL, "Decl.getDeclKindName()                      = %s" , Decl.getDeclKindName());;
  DcLib::Log::Out(INFO_ALL, "Decl.getQualifiedNameAsString()             = %s" , Decl.getQualifiedNameAsString().c_str());
//DcLib::Log::Out(INFO_ALL, "Decl.InEnclosingNamespaceSetOf()            = %s" , Decl.InEnclosingNamespaceSetOf()); 
  DcLib::Log::Out(INFO_ALL, "Decl.isCanonicalDecl()                      = %d" , Decl.isCanonicalDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isClosure()                            = %d" , Decl.isClosure());
  DcLib::Log::Out(INFO_ALL, "Decl.isCXXClassMember()                     = %d" , Decl.isCXXClassMember());
  DcLib::Log::Out(INFO_ALL, "Decl.isCXXInstanceMember()                  = %d" , Decl.isCXXInstanceMember());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternCXXContext()                   = %d" , Decl.isExternCXXContext());
//DcLib::Log::Out(INFO_ALL, "Decl.isDeclInLexicalTraversal()             = %d" , Decl.isDeclInLexicalTraversal());;
  DcLib::Log::Out(INFO_ALL, "Decl.isDefinedOutsideFunctionOrMethod()     = %d" , Decl.isDefinedOutsideFunctionOrMethod());
  DcLib::Log::Out(INFO_ALL, "Decl.isDependentContext()                   = %d" , Decl.isDependentContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isDeprecated()                         = %d" , Decl.isDeprecated());
  DcLib::Log::Out(INFO_ALL, "Decl.isExported()                           = %d" , Decl.isExported());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternallyDeclarable()               = %d" , Decl.isExternallyDeclarable());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternallyVisible()                  = %d" , Decl.isExternallyVisible());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternCContext()                     = %d" , Decl.isExternCContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternCXXContext()                   = %d" , Decl.isExternCXXContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isFileContext()                        = %d" , Decl.isFileContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isFirstDecl()                          = %d" , Decl.isFirstDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isFromASTFile()                        = %d" , Decl.isFromASTFile());
  DcLib::Log::Out(INFO_ALL, "Decl.isFunctionOrFunctionTemplate()         = %d" , Decl.isFunctionOrFunctionTemplate());
  DcLib::Log::Out(INFO_ALL, "Decl.isFunctionOrMethod()                   = %d" , Decl.isFunctionOrMethod());
  DcLib::Log::Out(INFO_ALL, "Decl.isHidden()                             = %d" , Decl.isHidden());
  DcLib::Log::Out(INFO_ALL, "Decl.isImplicit()                           = %d" , Decl.isImplicit());
  DcLib::Log::Out(INFO_ALL, "Decl.isInAnonymousNamespace()               = %d" , Decl.isInAnonymousNamespace());
//DcLib::Log::Out(INFO_ALL, "Decl.isInIdentifierNamespace()              = %d" , Decl.isInIdentifierNamespace());
  DcLib::Log::Out(INFO_ALL, "Decl.isInlineNamespace()                    = %d" , Decl.isInlineNamespace());
  DcLib::Log::Out(INFO_ALL, "Decl.isInStdNamespace()                     = %d" , Decl.isInStdNamespace());
  DcLib::Log::Out(INFO_ALL, "Decl.isInvalidDecl()                        = %d" , Decl.isInvalidDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isLexicallyWithinFunctionOrMethod()    = %d" , Decl.isLexicallyWithinFunctionOrMethod());
  DcLib::Log::Out(INFO_ALL, "Decl.isLinkageValid()                       = %d" , Decl.isLinkageValid());
  DcLib::Log::Out(INFO_ALL, "Decl.isLocalExternDecl()                    = %d" , Decl.isLocalExternDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isLookupContext()                      = %d" , Decl.isLookupContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isModulePrivate()                      = %d" , Decl.isModulePrivate());
//DcLib::Log::Out(INFO_ALL, "Decl.isMsStruct()                           = %d" , Decl.isMsStruct());
  DcLib::Log::Out(INFO_ALL, "Decl.isCompleteDefinitisNamespaceion()      = %d" , Decl.isNamespace());
  DcLib::Log::Out(INFO_ALL, "Decl.isObjCContainer()                      = %d" , Decl.isObjCContainer());
  DcLib::Log::Out(INFO_ALL, "Decl.isOutOfLine()                          = %d" , Decl.isOutOfLine());
  DcLib::Log::Out(INFO_ALL, "Decl.isParameterPack()                      = %d" , Decl.isParameterPack());
  DcLib::Log::Out(INFO_ALL, "Decl.isRecord()                             = %d" , Decl.isRecord());
  DcLib::Log::Out(INFO_ALL, "Decl.isReferenced()                         = %d" , Decl.isReferenced());
  DcLib::Log::Out(INFO_ALL, "Decl.isStdNamespace()                       = %d" , Decl.isStdNamespace());
//DcLib::Log::Out(INFO_ALL, "Decl.isTagIdentifierNamespace()             = %d" , Decl.isTagIdentifierNamespace());;
  DcLib::Log::Out(INFO_ALL, "Decl.isTemplated()                          = %d" , Decl.isTemplated());
  DcLib::Log::Out(INFO_ALL, "Decl.isTemplateDecl()                       = %d" , Decl.isTemplateDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isTemplateParameter()                  = %d" , Decl.isTemplateParameter());
  DcLib::Log::Out(INFO_ALL, "Decl.isTemplateParameterPack()              = %d" , Decl.isTemplateParameterPack());
  DcLib::Log::Out(INFO_ALL, "Decl.isThisDeclarationADefinition()         = %d" , Decl.isThisDeclarationADefinition());
  DcLib::Log::Out(INFO_ALL, "Decl.isThisDeclarationReferenced()          = %d" , Decl.isThisDeclarationReferenced());
  DcLib::Log::Out(INFO_ALL, "Decl.isTopLevelDeclInObjCContainer()        = %d" , Decl.isTopLevelDeclInObjCContainer());
  DcLib::Log::Out(INFO_ALL, "Decl.isTranslationUnit()                    = %d" , Decl.isTranslationUnit());
  DcLib::Log::Out(INFO_ALL, "Decl.isTransparentContext()                 = %d" , Decl.isTransparentContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isUnavailable()                        = %d" , Decl.isUnavailable());
  DcLib::Log::Out(INFO_ALL, "Decl.isUsed()                               = %d" , Decl.isUsed());
  DcLib::Log::Out(INFO_ALL, "Decl.isWeakImported()                       = %d" , Decl.isWeakImported());
  DcLib::Log::Out(INFO_ALL, "^--------------------------------------------------------------------------------^\n\n");

  // clang-format on
  return true;
}

bool LearnIt::PrintDecl(RecordDecl &Decl) {
  // clang-format off

  DcLib::Log::Out(INFO_ALL, "v--------------------------------------------------------------------------------v");
  DcLib::Log::Out(INFO_ALL, "RecordDecl");
  DcLib::Log::Out(INFO_ALL, "Decl.getName()                              = %s" , Decl.getName().str().c_str());
  DcLib::Log::Out(INFO_ALL, "Decl.getNameAsString()                      = %s" , Decl.getNameAsString().c_str());
  DcLib::Log::Out(INFO_ALL, "Decl.getDeclName()                          = %s" , Decl.getDeclName().getAsString().c_str());
//DcLib::Log::Out(INFO_ALL, "Decl.getDeclKindName()                      = %s" , Decl.getDeclKindName());;
  DcLib::Log::Out(INFO_ALL, "Decl.getQualifiedNameAsString()             = %s" , Decl.getQualifiedNameAsString().c_str());
//DcLib::Log::Out(INFO_ALL, "Decl.InEnclosingNamespaceSetOf()            = %s" , Decl.InEnclosingNamespaceSetOf()); 
  DcLib::Log::Out(INFO_ALL, "Decl.isCanonicalDecl()                      = %d" , Decl.isCanonicalDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isClosure()                            = %d" , Decl.isClosure());
  DcLib::Log::Out(INFO_ALL, "Decl.isCXXClassMember()                     = %d" , Decl.isCXXClassMember());
  DcLib::Log::Out(INFO_ALL, "Decl.isCXXInstanceMember()                  = %d" , Decl.isCXXInstanceMember());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternCXXContext()                   = %d" , Decl.isExternCXXContext());
//DcLib::Log::Out(INFO_ALL, "Decl.isDeclInLexicalTraversal()             = %d" , Decl.isDeclInLexicalTraversal());;
  DcLib::Log::Out(INFO_ALL, "Decl.isDefinedOutsideFunctionOrMethod()     = %d" , Decl.isDefinedOutsideFunctionOrMethod());
  DcLib::Log::Out(INFO_ALL, "Decl.isDependentContext()                   = %d" , Decl.isDependentContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isDeprecated()                         = %d" , Decl.isDeprecated());
  DcLib::Log::Out(INFO_ALL, "Decl.isExported()                           = %d" , Decl.isExported());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternallyDeclarable()               = %d" , Decl.isExternallyDeclarable());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternallyVisible()                  = %d" , Decl.isExternallyVisible());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternCContext()                     = %d" , Decl.isExternCContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternCXXContext()                   = %d" , Decl.isExternCXXContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isFileContext()                        = %d" , Decl.isFileContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isFirstDecl()                          = %d" , Decl.isFirstDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isFromASTFile()                        = %d" , Decl.isFromASTFile());
  DcLib::Log::Out(INFO_ALL, "Decl.isFunctionOrFunctionTemplate()         = %d" , Decl.isFunctionOrFunctionTemplate());
  DcLib::Log::Out(INFO_ALL, "Decl.isFunctionOrMethod()                   = %d" , Decl.isFunctionOrMethod());
  DcLib::Log::Out(INFO_ALL, "Decl.isHidden()                             = %d" , Decl.isHidden());
  DcLib::Log::Out(INFO_ALL, "Decl.isImplicit()                           = %d" , Decl.isImplicit());
  DcLib::Log::Out(INFO_ALL, "Decl.isInAnonymousNamespace()               = %d" , Decl.isInAnonymousNamespace());
//DcLib::Log::Out(INFO_ALL, "Decl.isInIdentifierNamespace()              = %d" , Decl.isInIdentifierNamespace());
  DcLib::Log::Out(INFO_ALL, "Decl.isInlineNamespace()                    = %d" , Decl.isInlineNamespace());
  DcLib::Log::Out(INFO_ALL, "Decl.isInStdNamespace()                     = %d" , Decl.isInStdNamespace());
  DcLib::Log::Out(INFO_ALL, "Decl.isInvalidDecl()                        = %d" , Decl.isInvalidDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isLexicallyWithinFunctionOrMethod()    = %d" , Decl.isLexicallyWithinFunctionOrMethod());
  DcLib::Log::Out(INFO_ALL, "Decl.isLinkageValid()                       = %d" , Decl.isLinkageValid());
  DcLib::Log::Out(INFO_ALL, "Decl.isLocalExternDecl()                    = %d" , Decl.isLocalExternDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isLookupContext()                      = %d" , Decl.isLookupContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isModulePrivate()                      = %d" , Decl.isModulePrivate());
//DcLib::Log::Out(INFO_ALL, "Decl.isMsStruct()                           = %d" , Decl.isMsStruct());
  DcLib::Log::Out(INFO_ALL, "Decl.isCompleteDefinitisNamespaceion()      = %d" , Decl.isNamespace());
  DcLib::Log::Out(INFO_ALL, "Decl.isObjCContainer()                      = %d" , Decl.isObjCContainer());
  DcLib::Log::Out(INFO_ALL, "Decl.isOutOfLine()                          = %d" , Decl.isOutOfLine());
  DcLib::Log::Out(INFO_ALL, "Decl.isParameterPack()                      = %d" , Decl.isParameterPack());
  DcLib::Log::Out(INFO_ALL, "Decl.isRecord()                             = %d" , Decl.isRecord());
  DcLib::Log::Out(INFO_ALL, "Decl.isReferenced()                         = %d" , Decl.isReferenced());
  DcLib::Log::Out(INFO_ALL, "Decl.isStdNamespace()                       = %d" , Decl.isStdNamespace());
//DcLib::Log::Out(INFO_ALL, "Decl.isTagIdentifierNamespace()             = %d" , Decl.isTagIdentifierNamespace());;
  DcLib::Log::Out(INFO_ALL, "Decl.isTemplated()                          = %d" , Decl.isTemplated());
  DcLib::Log::Out(INFO_ALL, "Decl.isTemplateDecl()                       = %d" , Decl.isTemplateDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isTemplateParameter()                  = %d" , Decl.isTemplateParameter());
  DcLib::Log::Out(INFO_ALL, "Decl.isTemplateParameterPack()              = %d" , Decl.isTemplateParameterPack());
  DcLib::Log::Out(INFO_ALL, "Decl.isThisDeclarationADefinition()         = %d" , Decl.isThisDeclarationADefinition());
  DcLib::Log::Out(INFO_ALL, "Decl.isThisDeclarationReferenced()          = %d" , Decl.isThisDeclarationReferenced());
  DcLib::Log::Out(INFO_ALL, "Decl.isTopLevelDeclInObjCContainer()        = %d" , Decl.isTopLevelDeclInObjCContainer());
  DcLib::Log::Out(INFO_ALL, "Decl.isTranslationUnit()                    = %d" , Decl.isTranslationUnit());
  DcLib::Log::Out(INFO_ALL, "Decl.isTransparentContext()                 = %d" , Decl.isTransparentContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isUnavailable()                        = %d" , Decl.isUnavailable());
  DcLib::Log::Out(INFO_ALL, "Decl.isUsed()                               = %d" , Decl.isUsed());
  DcLib::Log::Out(INFO_ALL, "Decl.isWeakImported()                       = %d" , Decl.isWeakImported());
  DcLib::Log::Out(INFO_ALL, "^--------------------------------------------------------------------------------^\n\n");

  // clang-format on
  return true;
}

bool LearnIt::PrintDecl(VarDecl &Decl) {
  // clang-format off
    
    DcLib::Log::Out(INFO_ALL, "v--------------------------------------------------------------------------------v");
    DcLib::Log::Out(INFO_ALL, "VarDecl");
    DcLib::Log::Out(INFO_ALL, "Decl.getName()                            = %s" , Decl.getName().str().c_str());
    DcLib::Log::Out(INFO_ALL, "Decl.getNameAsString()                    = %s" , Decl.getNameAsString().c_str());
    DcLib::Log::Out(INFO_ALL, "Decl.getDeclName()                        = %s" , Decl.getDeclName().getAsString().c_str());
  //DcLib::Log::Out(INFO_ALL, "Decl.getKindName()                        = %s" , Decl.getKindName().str().c_str());
    DcLib::Log::Out(INFO_ALL, "Decl.getDeclKindName()                    = %s" , Decl.getDeclKindName());
    DcLib::Log::Out(INFO_ALL, "Decl.getQualifiedNameAsString()           = %s" , Decl.getQualifiedNameAsString().c_str());
  //DcLib::Log::Out(INFO_ALL, "Decl.InEnclosingNamespaceSetOf()          = %s" , Decl.InEnclosingNamespaceSetOf());
  //DcLib::Log::Out(INFO_ALL, "Decl.isAnonymousStructOrUnion()           = %d" , Decl.isAnonymousStructOrUnion());
  //DcLib::Log::Out(INFO_ALL, "Decl.isBeingDefined()                     = %d" , Decl.isBeingDefined());
    DcLib::Log::Out(INFO_ALL, "Decl.isCanonicalDecl()                    = %d" , Decl.isCanonicalDecl());
  //DcLib::Log::Out(INFO_ALL, "Decl.isCapturedRecord()                   = %d" , Decl.isCapturedRecord());
  //DcLib::Log::Out(INFO_ALL, "Decl.isClass()                            = %d" , Decl.isClass());
  //DcLib::Log::Out(INFO_ALL, "Decl.isClosure()                          = %d" , Decl.isClosure());
  //DcLib::Log::Out(INFO_ALL, "Decl.isCompleteDefinition()               = %d" , Decl.isCompleteDefinition());
  //DcLib::Log::Out(INFO_ALL, "Decl.isCompleteDefinitionRequired()       = %d" , Decl.isCompleteDefinitionRequired());
    DcLib::Log::Out(INFO_ALL, "Decl.isCXXClassMember()                   = %d" , Decl.isCXXClassMember());
    DcLib::Log::Out(INFO_ALL, "Decl.isCXXInstanceMember()                = %d" , Decl.isCXXInstanceMember());
  //DcLib::Log::Out(INFO_ALL, "Decl.isExternCXXContext()                 = %d" , Decl.isExternCXXContext());
  //DcLib::Log::Out(INFO_ALL, "Decl.isDeclInLexicalTraversal()           = %d" , Decl.isDeclInLexicalTraversal());;
    DcLib::Log::Out(INFO_ALL, "Decl.isDefinedOutsideFunctionOrMethod()   = %d" , Decl.isDefinedOutsideFunctionOrMethod());
  //DcLib::Log::Out(INFO_ALL, "Decl.isDependentContext()                 = %d" , Decl.isDependentContext());
  //DcLib::Log::Out(INFO_ALL, "Decl.isDependentType()                    = %d" , Decl.isDependentType());
    DcLib::Log::Out(INFO_ALL, "Decl.isDeprecated()                       = %d" , Decl.isDeprecated());
  //DcLib::Log::Out(INFO_ALL, "Decl.isEmbeddedInDeclarator()             = %d" , Decl.isEmbeddedInDeclarator());
  //DcLib::Log::Out(INFO_ALL, "Decl.isEnum()                             = %d" , Decl.isEnum());
    DcLib::Log::Out(INFO_ALL, "Decl.isExported()                         = %d" , Decl.isExported());
    DcLib::Log::Out(INFO_ALL, "Decl.isExternallyDeclarable()             = %d" , Decl.isExternallyDeclarable());
    DcLib::Log::Out(INFO_ALL, "Decl.isExternallyVisible()                = %d" , Decl.isExternallyVisible());
  //DcLib::Log::Out(INFO_ALL, "Decl.isExternCContext()                   = %d" , Decl.isExternCContext());
  //DcLib::Log::Out(INFO_ALL, "Decl.isExternCXXContext()                 = %d" , Decl.isExternCXXContext());
  //DcLib::Log::Out(INFO_ALL, "Decl.isFileContext()                      = %d" , Decl.isFileContext());
    DcLib::Log::Out(INFO_ALL, "Decl.isFirstDecl()                        = %d" , Decl.isFirstDecl());
  //DcLib::Log::Out(INFO_ALL, "Decl.isFreeStanding()                     = %d" , Decl.isFreeStanding());
    DcLib::Log::Out(INFO_ALL, "Decl.isFromASTFile()                      = %d" , Decl.isFromASTFile());
    DcLib::Log::Out(INFO_ALL, "Decl.isFunctionOrFunctionTemplate()       = %d" , Decl.isFunctionOrFunctionTemplate());
  //DcLib::Log::Out(INFO_ALL, "Decl.isFunctionOrMethod()                 = %d" , Decl.isFunctionOrMethod());
    DcLib::Log::Out(INFO_ALL, "Decl.isHidden()                           = %d" , Decl.isHidden());
    DcLib::Log::Out(INFO_ALL, "Decl.isImplicit()                         = %d" , Decl.isImplicit());
    DcLib::Log::Out(INFO_ALL, "Decl.isInAnonymousNamespace()             = %d" , Decl.isInAnonymousNamespace());
  //DcLib::Log::Out(INFO_ALL, "Decl.isInIdentifierNamespace()            = %d" , Decl.isInIdentifierNamespace());
  //DcLib::Log::Out(INFO_ALL, "Decl.isInjectedClassName()                = %d" , Decl.isInjectedClassName());
  //DcLib::Log::Out(INFO_ALL, "Decl.isInlineNamespace()                  = %d" , Decl.isInlineNamespace());
    DcLib::Log::Out(INFO_ALL, "Decl.isInStdNamespace()                   = %d" , Decl.isInStdNamespace());
  //DcLib::Log::Out(INFO_ALL, "Decl.isInterface()                        = %d" , Decl.isInterface());
    DcLib::Log::Out(INFO_ALL, "Decl.isInvalidDecl()                      = %d" , Decl.isInvalidDecl());
  //DcLib::Log::Out(INFO_ALL, "Decl.isLambda()                           = %d" , Decl.isLambda());
    DcLib::Log::Out(INFO_ALL, "Decl.isLexicallyWithinFunctionOrMethod()  = %d" , Decl.isLexicallyWithinFunctionOrMethod());
    DcLib::Log::Out(INFO_ALL, "Decl.isLinkageValid()                     = %d" , Decl.isLinkageValid());
    DcLib::Log::Out(INFO_ALL, "Decl.isLocalExternDecl()                  = %d" , Decl.isLocalExternDecl());
  //DcLib::Log::Out(INFO_ALL, "Decl.isLookupContext()                    = %d" , Decl.isLookupContext());
    DcLib::Log::Out(INFO_ALL, "Decl.isModulePrivate()                    = %d" , Decl.isModulePrivate());
  //DcLib::Log::Out(INFO_ALL, "Decl.isMsStruct()                         = %d" , Decl.isMsStruct());
  //DcLib::Log::Out(INFO_ALL, "Decl.isCompleteDefinitisNamespaceion()    = %d" , Decl.isNamespace());
  //DcLib::Log::Out(INFO_ALL, "Decl.isNonTrivialToPrimitiveCopy()        = %d" , Decl.isNonTrivialToPrimitiveCopy());
  //DcLib::Log::Out(INFO_ALL, "Decl.isNonTrivialToPrimitiveDefaultInit() = %d" , Decl.isNonTrivialToPrimitiveDefaultInitialize());
  //DcLib::Log::Out(INFO_ALL, "Decl.isNonTrivialToPrimitiveDestroy()     = %d" , Decl.isNonTrivialToPrimitiveDestroy());
  //DcLib::Log::Out(INFO_ALL, "Decl.isObjCContainer()                    = %d" , Decl.isObjCContainer());
    DcLib::Log::Out(INFO_ALL, "Decl.isOutOfLine()                        = %d" , Decl.isOutOfLine());
  //DcLib::Log::Out(INFO_ALL, "Decl.isParamDestroyedInCallee()           = %d" , Decl.isParamDestroyedInCallee());
    DcLib::Log::Out(INFO_ALL, "Decl.isParameterPack()                    = %d" , Decl.isParameterPack());
  //DcLib::Log::Out(INFO_ALL, "Decl.isRecord()                           = %d" , Decl.isRecord());
    DcLib::Log::Out(INFO_ALL, "Decl.isReferenced()                       = %d" , Decl.isReferenced());
  //DcLib::Log::Out(INFO_ALL, "Decl.isStdNamespace()                     = %d" , Decl.isStdNamespace());
  //DcLib::Log::Out(INFO_ALL, "Decl.isStruct()                           = %d" , Decl.isStruct());
  //DcLib::Log::Out(INFO_ALL, "Decl.isTagIdentifierNamespace()           = %d" , Decl.isTagIdentifierNamespace());
    DcLib::Log::Out(INFO_ALL, "Decl.isTemplated()                        = %d" , Decl.isTemplated());
    DcLib::Log::Out(INFO_ALL, "Decl.isTemplateDecl()                     = %d" , Decl.isTemplateDecl());
    DcLib::Log::Out(INFO_ALL, "Decl.isTemplateParameter()                = %d" , Decl.isTemplateParameter());
    DcLib::Log::Out(INFO_ALL, "Decl.isTemplateParameterPack()            = %d" , Decl.isTemplateParameterPack());
    DcLib::Log::Out(INFO_ALL, "Decl.isThisDeclarationADefinition()       = %d" , Decl.isThisDeclarationADefinition());
    DcLib::Log::Out(INFO_ALL, "Decl.isThisDeclarationReferenced()        = %d" , Decl.isThisDeclarationReferenced());
    DcLib::Log::Out(INFO_ALL, "Decl.isTopLevelDeclInObjCContainer()      = %d" , Decl.isTopLevelDeclInObjCContainer());
  //DcLib::Log::Out(INFO_ALL, "Decl.isTranslationUnit()                  = %d" , Decl.isTranslationUnit());
  //DcLib::Log::Out(INFO_ALL, "Decl.isTransparentContext()               = %d" , Decl.isTransparentContext());
    DcLib::Log::Out(INFO_ALL, "Decl.isUnavailable()                      = %d" , Decl.isUnavailable());
  //DcLib::Log::Out(INFO_ALL, "Decl.isCompleteDefiniisUniontion()        = %d" , Decl.isUnion());
    DcLib::Log::Out(INFO_ALL, "Decl.isUsed()                             = %d" , Decl.isUsed());
    DcLib::Log::Out(INFO_ALL, "Decl.isWeakImported()                     = %d" , Decl.isWeakImported());
  //DcLib::Log::Out(INFO_ALL, "Decl.canPassInRegisters()                 = %d" , Decl.canPassInRegisters());
  //DcLib::Log::Out(INFO_ALL, "Decl.mayInsertExtraPadding()              = %d" , Decl.mayInsertExtraPadding());
  DcLib::Log::Out(INFO_ALL, "^--------------------------------------------------------------------------------^\n\n");

  // clang-format on
  return true;
}

bool LearnIt::PrintDecl(ParmVarDecl &Decl) {
  // clang-format off

  DcLib::Log::Out(INFO_ALL, "v--------------------------------------------------------------------------------v");
  DcLib::Log::Out(INFO_ALL, "ParmVarDecl");
  DcLib::Log::Out(INFO_ALL, "Decl.getName()                              = %s" , Decl.getName().str().c_str());
  DcLib::Log::Out(INFO_ALL, "Decl.getNameAsString()                      = %s" , Decl.getNameAsString().c_str());
  DcLib::Log::Out(INFO_ALL, "Decl.getDeclName()                          = %s" , Decl.getDeclName().getAsString().c_str());
  DcLib::Log::Out(INFO_ALL, "Decl.getDeclKindName()                      = %s" , Decl.getDeclKindName());;
  DcLib::Log::Out(INFO_ALL, "Decl.getQualifiedNameAsString()             = %s" , Decl.getQualifiedNameAsString().c_str());
//DcLib::Log::Out(INFO_ALL, "Decl.InEnclosingNamespaceSetOf()            = %s" , Decl.InEnclosingNamespaceSetOf()); 
  DcLib::Log::Out(INFO_ALL, "Decl.isCanonicalDecl()                      = %d" , Decl.isCanonicalDecl());
//DcLib::Log::Out(INFO_ALL, "Decl.isClosure()                            = %d" , Decl.isClosure());
  DcLib::Log::Out(INFO_ALL, "Decl.isCXXClassMember()                     = %d" , Decl.isCXXClassMember());
  DcLib::Log::Out(INFO_ALL, "Decl.isCXXInstanceMember()                  = %d" , Decl.isCXXInstanceMember());
//DcLib::Log::Out(INFO_ALL, "Decl.isExternCXXContext()                   = %d" , Decl.isExternCXXContext());
//DcLib::Log::Out(INFO_ALL, "Decl.isDeclInLexicalTraversal()             = %d" , Decl.isDeclInLexicalTraversal());;
  DcLib::Log::Out(INFO_ALL, "Decl.isDefinedOutsideFunctionOrMethod()     = %d" , Decl.isDefinedOutsideFunctionOrMethod());
//DcLib::Log::Out(INFO_ALL, "Decl.isDependentContext()                   = %d" , Decl.isDependentContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isDeprecated()                         = %d" , Decl.isDeprecated());
  DcLib::Log::Out(INFO_ALL, "Decl.isExported()                           = %d" , Decl.isExported());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternallyDeclarable()               = %d" , Decl.isExternallyDeclarable());
  DcLib::Log::Out(INFO_ALL, "Decl.isExternallyVisible()                  = %d" , Decl.isExternallyVisible());
//DcLib::Log::Out(INFO_ALL, "Decl.isExternCContext()                     = %d" , Decl.isExternCContext());
//DcLib::Log::Out(INFO_ALL, "Decl.isExternCXXContext()                   = %d" , Decl.isExternCXXContext());
//DcLib::Log::Out(INFO_ALL, "Decl.isFileContext()                        = %d" , Decl.isFileContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isFirstDecl()                          = %d" , Decl.isFirstDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isFromASTFile()                        = %d" , Decl.isFromASTFile());
  DcLib::Log::Out(INFO_ALL, "Decl.isFunctionOrFunctionTemplate()         = %d" , Decl.isFunctionOrFunctionTemplate());
//DcLib::Log::Out(INFO_ALL, "Decl.isFunctionOrMethod()                   = %d" , Decl.isFunctionOrMethod());
  DcLib::Log::Out(INFO_ALL, "Decl.isHidden()                             = %d" , Decl.isHidden());
  DcLib::Log::Out(INFO_ALL, "Decl.isImplicit()                           = %d" , Decl.isImplicit());
  DcLib::Log::Out(INFO_ALL, "Decl.isInAnonymousNamespace()               = %d" , Decl.isInAnonymousNamespace());
//DcLib::Log::Out(INFO_ALL, "Decl.isInIdentifierNamespace()              = %d" , Decl.isInIdentifierNamespace());
//DcLib::Log::Out(INFO_ALL, "Decl.isInlineNamespace()                    = %d" , Decl.isInlineNamespace());
  DcLib::Log::Out(INFO_ALL, "Decl.isInStdNamespace()                     = %d" , Decl.isInStdNamespace());
  DcLib::Log::Out(INFO_ALL, "Decl.isInvalidDecl()                        = %d" , Decl.isInvalidDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isLexicallyWithinFunctionOrMethod()    = %d" , Decl.isLexicallyWithinFunctionOrMethod());
  DcLib::Log::Out(INFO_ALL, "Decl.isLinkageValid()                       = %d" , Decl.isLinkageValid());
  DcLib::Log::Out(INFO_ALL, "Decl.isLocalExternDecl()                    = %d" , Decl.isLocalExternDecl());
//DcLib::Log::Out(INFO_ALL, "Decl.isLookupContext()                      = %d" , Decl.isLookupContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isModulePrivate()                      = %d" , Decl.isModulePrivate());
//DcLib::Log::Out(INFO_ALL, "Decl.isMsStruct()                           = %d" , Decl.isMsStruct());
//DcLib::Log::Out(INFO_ALL, "Decl.isCompleteDefinitisNamespaceion()      = %d" , Decl.isNamespace());
//DcLib::Log::Out(INFO_ALL, "Decl.isObjCContainer()                      = %d" , Decl.isObjCContainer());
  DcLib::Log::Out(INFO_ALL, "Decl.isOutOfLine()                          = %d" , Decl.isOutOfLine());
  DcLib::Log::Out(INFO_ALL, "Decl.isParameterPack()                      = %d" , Decl.isParameterPack());
//DcLib::Log::Out(INFO_ALL, "Decl.isRecord()                             = %d" , Decl.isRecord());
  DcLib::Log::Out(INFO_ALL, "Decl.isReferenced()                         = %d" , Decl.isReferenced());
//DcLib::Log::Out(INFO_ALL, "Decl.isStdNamespace()                       = %d" , Decl.isStdNamespace());
//DcLib::Log::Out(INFO_ALL, "Decl.isTagIdentifierNamespace()             = %d" , Decl.isTagIdentifierNamespace());;
  DcLib::Log::Out(INFO_ALL, "Decl.isTemplated()                          = %d" , Decl.isTemplated());
  DcLib::Log::Out(INFO_ALL, "Decl.isTemplateDecl()                       = %d" , Decl.isTemplateDecl());
  DcLib::Log::Out(INFO_ALL, "Decl.isTemplateParameter()                  = %d" , Decl.isTemplateParameter());
  DcLib::Log::Out(INFO_ALL, "Decl.isTemplateParameterPack()              = %d" , Decl.isTemplateParameterPack());
  DcLib::Log::Out(INFO_ALL, "Decl.isThisDeclarationADefinition()         = %d" , Decl.isThisDeclarationADefinition());
  DcLib::Log::Out(INFO_ALL, "Decl.isThisDeclarationReferenced()          = %d" , Decl.isThisDeclarationReferenced());
  DcLib::Log::Out(INFO_ALL, "Decl.isTopLevelDeclInObjCContainer()        = %d" , Decl.isTopLevelDeclInObjCContainer());
//DcLib::Log::Out(INFO_ALL, "Decl.isTranslationUnit()                    = %d" , Decl.isTranslationUnit());
//DcLib::Log::Out(INFO_ALL, "Decl.isTransparentContext()                 = %d" , Decl.isTransparentContext());
  DcLib::Log::Out(INFO_ALL, "Decl.isUnavailable()                        = %d" , Decl.isUnavailable());
  DcLib::Log::Out(INFO_ALL, "Decl.isUsed()                               = %d" , Decl.isUsed());
  DcLib::Log::Out(INFO_ALL, "Decl.isWeakImported()                       = %d" , Decl.isWeakImported());
  DcLib::Log::Out(INFO_ALL, "^--------------------------------------------------------------------------------^\n\n");

  // clang-format on
  return true;
}
