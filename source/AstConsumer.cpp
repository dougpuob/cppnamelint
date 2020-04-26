#include <string>

#include "Common.h"
#include "Config.h"

#include "AstConsumer.h"
#include "AstVisitor.h"

using namespace std;

bool MyASTConsumer::HandleTopLevelDecl(DeclGroupRef MyDeclGroupRef) {

  string FileName;
  APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();

  for (DeclGroupRef::iterator Iter = MyDeclGroupRef.begin(), e = MyDeclGroupRef.end(); Iter != e;
       ++Iter) {
    Decl *pDecl              = *Iter;
    const ASTContext &ASTCxt = pDecl->getASTContext();

    const DiagnosticsEngine &diagEngine = ASTCxt.getDiagnostics();
    if (diagEngine.hasErrorOccurred()) {
      pAppCxt->MemoBoard.Assert.nErrorOccurred++;
    }

    pAppCxt->MemoBoard.Assert.nNumWarnings += diagEngine.getNumWarnings();

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
  bool bRet                           = false;
  const DiagnosticsEngine &diagEngine = Ctx.getDiagnostics();

  bool bError     = diagEngine.hasErrorOccurred();
  int iNumWarning = diagEngine.getNumWarnings();
  for (auto DiagIDMappingPair : diagEngine.getDiagnosticMappings()) {
    diag::kind DiagID = DiagIDMappingPair.first;
    bRet              = false;
  }

  bRet = false;
  // Do nothing.
}
