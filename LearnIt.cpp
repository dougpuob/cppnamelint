#include "LearnIt.h"

#include <memory>
#include <string>

using namespace DcLib;

LearnIt::LearnIt() {}

bool LearnIt::PrintDecl(Decl *pDecl) {
	if (!pDecl)
	{
		return false;
	}
	// clang-format off

	DcLib::Log::Out(INFO_ALL, "v--start line--------------------------------------------------------------------v");
	if (isa<NamedDecl>(pDecl))
	{
		_PrintNamedDecl(dyn_cast<NamedDecl> (pDecl));
	}

	if (isa<RecordDecl>(pDecl))
	{
		_PrintRecordDecl(dyn_cast<RecordDecl> (pDecl));
	}

	if (isa<ValueDecl>(pDecl))
	{
		_PrintValueDecl(dyn_cast<ValueDecl> (pDecl));
	}

	if (isa<FieldDecl>(pDecl))
	{
		_PrintFieldDecl(dyn_cast<FieldDecl> (pDecl));
	}

	if (isa<VarDecl>(pDecl))
	{
		_PrintVarDecl(dyn_cast<VarDecl> (pDecl));
	}

	if (isa<FunctionDecl>(pDecl))
	{
		_PrintFunctionDecl(dyn_cast<FunctionDecl> (pDecl));
	}

	if (isa<ParmVarDecl>(pDecl))
	{
		_PrintParmVarDecl(dyn_cast<ParmVarDecl> (pDecl));
	}

	DcLib::Log::Out(INFO_ALL, "v--end line-----------------------------------------------------------------------v");
	// clang-format on

	return true;
}

void LearnIt::_PrintNamedDecl(NamedDecl *pDecl) {

	DcLib::Log::Out(INFO_ALL, "NamedDecl");
	DcLib::Log::Out(INFO_ALL, "Decl.getName()                                = %s", pDecl->getName().str().c_str());
	DcLib::Log::Out(INFO_ALL, "Decl.getNameAsString()                        = %s", pDecl->getNameAsString().c_str());
	DcLib::Log::Out(INFO_ALL, "Decl.getDeclName()                            = %s", pDecl->getDeclName().getAsString().c_str());
	DcLib::Log::Out(INFO_ALL, "Decl.getDeclKindName()                        = %s", pDecl->getDeclKindName());;
	DcLib::Log::Out(INFO_ALL, "Decl.getQualifiedNameAsString()               = %s", pDecl->getQualifiedNameAsString().c_str());
	DcLib::Log::Out(INFO_ALL, "Decl.isCanonicalDecl()                        = %d", pDecl->isCanonicalDecl());
	DcLib::Log::Out(INFO_ALL, "Decl.isCXXClassMember()                       = %d", pDecl->isCXXClassMember());
	DcLib::Log::Out(INFO_ALL, "Decl.isCXXInstanceMember()                    = %d", pDecl->isCXXInstanceMember());
	DcLib::Log::Out(INFO_ALL, "Decl.isDefinedOutsideFunctionOrMethod()       = %d", pDecl->isDefinedOutsideFunctionOrMethod());
	DcLib::Log::Out(INFO_ALL, "Decl.isDeprecated()                           = %d", pDecl->isDeprecated());
	DcLib::Log::Out(INFO_ALL, "Decl.isExported()                             = %d", pDecl->isExported());
	DcLib::Log::Out(INFO_ALL, "Decl.isExternallyDeclarable()                 = %d", pDecl->isExternallyDeclarable());
	DcLib::Log::Out(INFO_ALL, "Decl.isExternallyVisible()                    = %d", pDecl->isExternallyVisible());
	DcLib::Log::Out(INFO_ALL, "Decl.isFirstDecl()                            = %d", pDecl->isFirstDecl());
	DcLib::Log::Out(INFO_ALL, "Decl.isFromASTFile()                          = %d", pDecl->isFromASTFile());
	DcLib::Log::Out(INFO_ALL, "Decl.isFunctionOrFunctionTemplate()           = %d", pDecl->isFunctionOrFunctionTemplate());
	DcLib::Log::Out(INFO_ALL, "Decl.isHidden()                               = %d", pDecl->isHidden());
	DcLib::Log::Out(INFO_ALL, "Decl.isImplicit()                             = %d", pDecl->isImplicit());
	DcLib::Log::Out(INFO_ALL, "Decl.isInAnonymousNamespace()                 = %d", pDecl->isInAnonymousNamespace());
	DcLib::Log::Out(INFO_ALL, "Decl.isInStdNamespace()                       = %d", pDecl->isInStdNamespace());
	DcLib::Log::Out(INFO_ALL, "Decl.isInvalidDecl()                          = %d", pDecl->isInvalidDecl());
	DcLib::Log::Out(INFO_ALL, "Decl.isLexicallyWithinFunctionOrMethod()      = %d", pDecl->isLexicallyWithinFunctionOrMethod());
	DcLib::Log::Out(INFO_ALL, "Decl.isLinkageValid()                         = %d", pDecl->isLinkageValid());
	DcLib::Log::Out(INFO_ALL, "Decl.isLocalExternDecl()                      = %d", pDecl->isLocalExternDecl());
	DcLib::Log::Out(INFO_ALL, "Decl.isModulePrivate()                        = %d", pDecl->isModulePrivate());
	DcLib::Log::Out(INFO_ALL, "Decl.isOutOfLine()                            = %d", pDecl->isOutOfLine());
	DcLib::Log::Out(INFO_ALL, "Decl.isParameterPack()                        = %d", pDecl->isParameterPack());
	DcLib::Log::Out(INFO_ALL, "Decl.isReferenced()                           = %d", pDecl->isReferenced());
	DcLib::Log::Out(INFO_ALL, "Decl.isTemplated()                            = %d", pDecl->isTemplated());
	DcLib::Log::Out(INFO_ALL, "Decl.isTemplateDecl()                         = %d", pDecl->isTemplateDecl());
	DcLib::Log::Out(INFO_ALL, "Decl.isTemplateParameter()                    = %d", pDecl->isTemplateParameter());
	DcLib::Log::Out(INFO_ALL, "Decl.isTemplateParameterPack()                = %d", pDecl->isTemplateParameterPack());
	DcLib::Log::Out(INFO_ALL, "Decl.isThisDeclarationReferenced()            = %d", pDecl->isThisDeclarationReferenced());
	DcLib::Log::Out(INFO_ALL, "Decl.isTopLevelDeclInObjCContainer()          = %d", pDecl->isTopLevelDeclInObjCContainer());
	DcLib::Log::Out(INFO_ALL, "Decl.isUnavailable()                          = %d", pDecl->isUnavailable());
	DcLib::Log::Out(INFO_ALL, "Decl.isUsed()                                 = %d", pDecl->isUsed());
	DcLib::Log::Out(INFO_ALL, "Decl.isWeakImported()                         = %d", pDecl->isWeakImported());
}

void LearnIt::_PrintValueDecl(ValueDecl *pDecl) {

	DcLib::Log::Out(INFO_ALL, "ValueDecl");
	DcLib::Log::Out(INFO_ALL, "ValueDecl.isWeak()                            = %d", pDecl->isWeak());
}

void LearnIt::_PrintFieldDecl(FieldDecl *pDecl) {

	DcLib::Log::Out(INFO_ALL, "FieldDecl");
	DcLib::Log::Out(INFO_ALL, "FieldDecl.isBitField()                        = %d", pDecl->isBitField());
	DcLib::Log::Out(INFO_ALL, "FieldDecl.isAnonymousStructOrUnion()          = %d", pDecl->isAnonymousStructOrUnion());

}

void LearnIt::_PrintVarDecl(VarDecl *pDecl) {

	DcLib::Log::Out(INFO_ALL, "VarDecl");
	DcLib::Log::Out(INFO_ALL, "VarDecl.isExternC()                           = %d", pDecl->isExternC());
	DcLib::Log::Out(INFO_ALL, "VarDecl.isInExternCContext()                  = %d", pDecl->isInExternCContext());
	DcLib::Log::Out(INFO_ALL, "VarDecl.isInExternCXXContext()                = %d", pDecl->isInExternCXXContext());
	DcLib::Log::Out(INFO_ALL, "VarDecl.isLocalVarDecl()                      = %d", pDecl->isLocalVarDecl());
	DcLib::Log::Out(INFO_ALL, "VarDecl.isLocalVarDeclOrParm()                = %d", pDecl->isLocalVarDeclOrParm());
	DcLib::Log::Out(INFO_ALL, "VarDecl.isFunctionOrMethodVarDecl()           = %d", pDecl->isFunctionOrMethodVarDecl());
	DcLib::Log::Out(INFO_ALL, "VarDecl.isStaticDataMember()                  = %d", pDecl->isStaticDataMember());
	DcLib::Log::Out(INFO_ALL, "VarDecl.isFileVarDecl()                       = %d", pDecl->isFileVarDecl());
	DcLib::Log::Out(INFO_ALL, "VarDecl.hasInit()                             = %d", pDecl->hasInit());
}


void LearnIt::_PrintFunctionDecl(FunctionDecl *pDecl) {

	DcLib::Log::Out(INFO_ALL, "FunctionDecl");
	DcLib::Log::Out(INFO_ALL, "FunctionDecl.getNameInfo()                    = %s", pDecl->getNameInfo().getAsString().c_str());
	DcLib::Log::Out(INFO_ALL, "FunctionDecl.isDefined()                      = %d", pDecl->isDefined());
	DcLib::Log::Out(INFO_ALL, "FunctionDecl.isThisDeclarationADefinition()   = %d", pDecl->isThisDeclarationADefinition());
	DcLib::Log::Out(INFO_ALL, "FunctionDecl.doesThisDeclarationHaveABody()   = %d", pDecl->doesThisDeclarationHaveABody());
	DcLib::Log::Out(INFO_ALL, "FunctionDecl.isVariadic()                     = %d", pDecl->isVariadic());
	DcLib::Log::Out(INFO_ALL, "FunctionDecl.isVirtualAsWritten()             = %d", pDecl->isVirtualAsWritten());
	DcLib::Log::Out(INFO_ALL, "FunctionDecl.isPure()                         = %d", pDecl->isPure());
	DcLib::Log::Out(INFO_ALL, "FunctionDecl.isDefaulted()                    = %d", pDecl->isDefaulted());
	DcLib::Log::Out(INFO_ALL, "FunctionDecl.hasPrototype()                   = %d", pDecl->hasPrototype());
	DcLib::Log::Out(INFO_ALL, "FunctionDecl.isMain()                         = %d", pDecl->isMain());
	DcLib::Log::Out(INFO_ALL, "FunctionDecl.isExternC()                      = %d", pDecl->isExternC());
	DcLib::Log::Out(INFO_ALL, "FunctionDecl.isInExternCContext()             = %d", pDecl->isInExternCContext());
	DcLib::Log::Out(INFO_ALL, "FunctionDecl.isInExternCXXContext()           = %d", pDecl->isInExternCXXContext());
	DcLib::Log::Out(INFO_ALL, "FunctionDecl.isGlobal()                       = %d", pDecl->isGlobal());
	DcLib::Log::Out(INFO_ALL, "FunctionDecl.isInlined()                      = %d",pDecl->isInlined());
}

void LearnIt::_PrintParmVarDecl(ParmVarDecl *pDecl) {

	DcLib::Log::Out(INFO_ALL, "ParmVarDecl");
	DcLib::Log::Out(INFO_ALL, "ParmVarDecl.isObjCMethodParameter()          = %d", pDecl->isObjCMethodParameter());
	DcLib::Log::Out(INFO_ALL, "ParmVarDecl.hasDefaultArg()                  = %d", pDecl->hasDefaultArg());
	DcLib::Log::Out(INFO_ALL, "ParmVarDecl.hasUnparsedDefaultArg()          = %d", pDecl->hasUnparsedDefaultArg());
	DcLib::Log::Out(INFO_ALL, "ParmVarDecl.hasInheritedDefaultArg()         = %d", pDecl->hasInheritedDefaultArg());

}

void LearnIt::_PrintRecordDecl(RecordDecl *pDecl) {

	DcLib::Log::Out(INFO_ALL, "RecordDecl");
	DcLib::Log::Out(INFO_ALL, "RecordDecl.hasFlexibleArrayMember()           = %d", pDecl->hasFlexibleArrayMember());
	DcLib::Log::Out(INFO_ALL, "RecordDecl.isAnonymousStructOrUnion()         = %d", pDecl->isAnonymousStructOrUnion());
	DcLib::Log::Out(INFO_ALL, "RecordDecl.hasObjectMember()                  = %d", pDecl->hasObjectMember());
	DcLib::Log::Out(INFO_ALL, "RecordDecl.hasVolatileMember()                = %d", pDecl->hasVolatileMember());
	DcLib::Log::Out(INFO_ALL, "RecordDecl.isLambda()                         = %d", pDecl->isLambda());
}