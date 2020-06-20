#include <string>

#include "Common.h"
#include "Config.h"

#include "AstConsumer.h"
#include "AstVisitor.h"

using namespace std;

bool MyASTConsumer::HandleTopLevelDecl(DeclGroupRef DeclGrpRef) {
  string FileName;

  APP_CONTEXT *pAppCxt  = (APP_CONTEXT *)GetAppCxt();
  const Config *pConfig = &pAppCxt->MemoBoard.Config;

  DeclGroupRef::iterator Iter = DeclGrpRef.begin();
  DeclGroupRef::iterator End  = DeclGrpRef.end();

  for (; Iter != End; ++Iter) {
    Decl *pDecl = *Iter;

    const ASTContext &ASTCxt   = pDecl->getASTContext();
    FullSourceLoc FullLocation = ASTCxt.getFullLoc(pDecl->getBeginLoc());
    if (FullLocation.isValid()) {
      FileName = FullLocation.getFileLoc().getFileEntry()->getName();
    }

    const bool bIsInMainFile = ASTCxt.getSourceManager().isInMainFile(pDecl->getLocation());
    if (bIsInMainFile) {
      const DiagnosticsEngine &diagEngine = ASTCxt.getDiagnostics();
      if (diagEngine.hasErrorOccurred()) {
        pAppCxt->MemoBoard.Assert.nErrorOccurred++;
      }
      pAppCxt->MemoBoard.Assert.nNumWarnings += diagEngine.getNumWarnings();

      const SourceManager &SrcMgr = ASTCxt.getSourceManager();
      MyASTVisitor myVisitor(&SrcMgr, &ASTCxt, pConfig);
      myVisitor.TraverseDecl(*Iter);
    }
  }

  return true;
}