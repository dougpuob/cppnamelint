#include <string>

#include "Common.h"
#include "Config.h"

#include "MyAstConsumer.h"
#include "MyAstVisitor.h"

using namespace std;

bool MyASTConsumer::HandleTopLevelDecl(DeclGroupRef MyDeclGroupRef) {
  string FileName;
  const APP_CONTEXT *pAppCxt = GetAppCxt();

  for (DeclGroupRef::iterator Iter = MyDeclGroupRef.begin(), e = MyDeclGroupRef.end(); Iter != e;
       ++Iter) {
    Decl *pDecl = *Iter;
    const ASTContext &ASTCxt = pDecl->getASTContext();

    FullSourceLoc FullLocation = ASTCxt.getFullLoc(pDecl->getBeginLoc());
    if (FullLocation.isValid()) {
      FileName = FullLocation.getFileLoc().getFileEntry()->getName();
    }

    if (ASTCxt.getSourceManager().isInMainFile(pDecl->getLocation())) {
      const SourceManager &SrcMgr = ASTCxt.getSourceManager();
      MyASTVisitor myVisitor(&SrcMgr, &ASTCxt, &(GetAppCxt()->MemoBoard.Config));
      myVisitor.TraverseDecl(*Iter);
    }
  }

  return true;
}

void MyASTConsumer::HandleTranslationUnit(ASTContext &Ctx) {
  // assert(false);
}
