#ifndef __NAMELINT_MY_AST_VISITOR__H__
#define __NAMELINT_MY_AST_VISITOR__H__

#include <iostream>
#include <vector>

#include "Config.h"
#include "Detection.h"
#include "DumpDecl.h"
#include "MyAstConsumer.h"
#include "TraceMemo.h"

using namespace std;
using namespace clang;
using namespace clang::tooling;
using namespace llvm;
using namespace clang::driver;
using namespace clang::tooling;
using namespace namelint;

class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor> {
private:
  DumpDecl m_DumpDecl;

  ASTContext *m_pAstCxt;
  const SourceManager *m_pSrcMgr;

  Detection m_Detect;
  shared_ptr<ConfigData> m_pConfig;

  bool _IsMainFile(Decl *pDecl);
  bool _PrintPosition(Decl *pDecl);
  void _KeepFileName(string &Path);
  bool _GetPosition(Decl *pDecl, string &FileName, size_t &nLineNumb, size_t &nColNumb);

  bool _ClassifyTypeName(string &TyeName);

  ErrorDetail *_CreateErrorDetail(const string &FileName, const string &Suggestion);

  ErrorDetail *_CreateErrorDetail(Decl *pDecl, const CheckType &CheckType, const bool &bIsPtr,
                                  const bool &bIsArray, const string &TargetName,
                                  const string &Expected);

  ErrorDetail *_CreateErrorDetail(Decl *pDecl, const CheckType &CheckType, const bool &bIsPtr,
                                  const bool &bIsArray, const string &TypeName,
                                  const string &TargetName, const string &Suggestion);

  bool _GetFunctionInfo(FunctionDecl *pDecl, string &FuncName);

  bool _GetParmsInfo(ParmVarDecl *pDecl, string &VarType, string &VarName, bool &bIsPtr,
                     bool &bAnonymous);

  bool _GetValueInfo(ValueDecl *pDecl, string &ValueType, string &ValueName, bool &bIsPtr,
                     bool &bIsArray, bool &bIsBuiltinType);

  bool _CheckRuleForVariable(ValueDecl *pDecl);

public:
  MyASTVisitor(const SourceManager *pSM, const ASTContext *pAstCxt, const Config *pConfig);
  // bool VisitStmt(Stmt *pStmt);
  // bool VisitCXXRecordDecl(CXXRecordDecl *D);
  // bool VisitCXXConstructorDecl(CXXConstructorDecl *D);

  bool VisitCXXRecordDecl(CXXRecordDecl *D);
  bool VisitFunctionDecl(FunctionDecl *pDecl);
  bool VisitCXXMethodDecl(CXXMethodDecl *pDecl);
  bool VisitRecordDecl(RecordDecl *pDecl);
  bool VisitVarDecl(VarDecl *pDecl);
  bool VisitFieldDecl(FieldDecl *pDecl);
  bool VisitReturnStmt(ReturnStmt *pRetStmt);
  bool VisitParmVarDecl(ParmVarDecl *pDecl);
  bool VisitTypedefDecl(TypedefDecl *pDecl);
};

/*
  // Declaration visitors
  bool VisitTypeAliasTemplateDecl(TypeAliasTemplateDecl *D);
  bool VisitTypeAliasDecl(TypeAliasDecl *D);
  bool VisitAttributes(Decl *D);
  bool VisitBlockDecl(BlockDecl *B);
  bool VisitCXXRecordDecl(CXXRecordDecl *D);
  Optional<bool> shouldVisitCursor(CXCursor C);
  bool VisitDeclContext(DeclContext *DC);
  bool VisitTranslationUnitDecl(TranslationUnitDecl *D);
  bool VisitTypedefDecl(TypedefDecl *D);
  bool VisitTagDecl(TagDecl *D);
  bool VisitClassTemplateSpecializationDecl(ClassTemplateSpecializationDecl *D);
  bool VisitClassTemplatePartialSpecializationDecl(
                                     ClassTemplatePartialSpecializationDecl *D);
  bool VisitTemplateTypeParmDecl(TemplateTypeParmDecl *D);
  bool VisitEnumConstantDecl(EnumConstantDecl *D);
  bool VisitDeclaratorDecl(DeclaratorDecl *DD);
  bool VisitFunctionDecl(FunctionDecl *ND);
  bool VisitFieldDecl(FieldDecl *D);
  bool VisitVarDecl(VarDecl *);
  bool VisitNonTypeTemplateParmDecl(NonTypeTemplateParmDecl *D);
  bool VisitFunctionTemplateDecl(FunctionTemplateDecl *D);
  bool VisitClassTemplateDecl(ClassTemplateDecl *D);
  bool VisitTemplateTemplateParmDecl(TemplateTemplateParmDecl *D);
  bool VisitObjCTypeParamDecl(ObjCTypeParamDecl *D);
  bool VisitObjCMethodDecl(ObjCMethodDecl *ND);
  bool VisitObjCContainerDecl(ObjCContainerDecl *D);
  bool VisitObjCCategoryDecl(ObjCCategoryDecl *ND);
  bool VisitObjCProtocolDecl(ObjCProtocolDecl *PID);
  bool VisitObjCPropertyDecl(ObjCPropertyDecl *PD);
  bool VisitObjCTypeParamList(ObjCTypeParamList *typeParamList);
  bool VisitObjCInterfaceDecl(ObjCInterfaceDecl *D);
  bool VisitObjCImplDecl(ObjCImplDecl *D);
  bool VisitObjCCategoryImplDecl(ObjCCategoryImplDecl *D);
  bool VisitObjCImplementationDecl(ObjCImplementationDecl *D);
  // FIXME: ObjCCompatibleAliasDecl requires aliased-class locations.
  bool VisitObjCPropertyImplDecl(ObjCPropertyImplDecl *PD);
  bool VisitLinkageSpecDecl(LinkageSpecDecl *D);
  bool VisitNamespaceDecl(NamespaceDecl *D);
  bool VisitNamespaceAliasDecl(NamespaceAliasDecl *D);
  bool VisitUsingDirectiveDecl(UsingDirectiveDecl *D);
  bool VisitUsingDecl(UsingDecl *D);
  bool VisitUnresolvedUsingValueDecl(UnresolvedUsingValueDecl *D);
  bool VisitUnresolvedUsingTypenameDecl(UnresolvedUsingTypenameDecl *D);
  bool VisitStaticAssertDecl(StaticAssertDecl *D);
  bool VisitFriendDecl(FriendDecl *D);

  // Name visitor
  bool VisitDeclarationNameInfo(DeclarationNameInfo Name);
  bool VisitNestedNameSpecifier(NestedNameSpecifier *NNS, SourceRange Range);
  bool VisitNestedNameSpecifierLoc(NestedNameSpecifierLoc NNS);

  // Template visitors
  bool VisitTemplateParameters(const TemplateParameterList *Params);
  bool VisitTemplateName(TemplateName Name, SourceLocation Loc);
  bool VisitTemplateArgumentLoc(const TemplateArgumentLoc &TAL);

  // Type visitors
#define ABSTRACT_TYPELOC(CLASS, PARENT)
#define TYPELOC(CLASS, PARENT) \
  bool Visit##CLASS##TypeLoc(CLASS##TypeLoc TyLoc);
#include "clang/AST/TypeLocNodes.def"

  bool VisitTagTypeLoc(TagTypeLoc TL);
  bool VisitArrayTypeLoc(ArrayTypeLoc TL);
  bool VisitFunctionTypeLoc(FunctionTypeLoc TL, bool SkipResultType = false);
*/

#endif // __NAMELINT_MY_AST_VISITOR__H__
