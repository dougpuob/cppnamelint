#include "MyAstConsumer.h"
#include "MyAstVisitor.h"

#include "Common.h"
#include "Config.h"

#include <string>

using namespace std;

bool
MyASTConsumer::HandleTopLevelDecl(DeclGroupRef MyDeclGroupRef)
{
    string FileName;
    for (DeclGroupRef::iterator Iter = MyDeclGroupRef.begin(),
                                e = MyDeclGroupRef.end();
         Iter != e;
         ++Iter) {
        Decl* pDecl = *Iter;

        const ASTContext& ASTCxt = pDecl->getASTContext();

        FullSourceLoc FullLocation = ASTCxt.getFullLoc(pDecl->getBeginLoc());
        if (FullLocation.isValid()) {
            FileName = FullLocation.getFileLoc().getFileEntry()->getName();
        }

        if (ASTCxt.getSourceManager().isInMainFile(pDecl->getLocation())) {
            namelint::Config* pCfg =
              (namelint::Config*)GetAppCxt()->pTomlConfig;

            const SourceManager& SrcMgr = ASTCxt.getSourceManager();
            MyASTVisitor myVisitor(&SrcMgr, &ASTCxt, pCfg);
            myVisitor.TraverseDecl(*Iter);
        }
    }

    return true;
}

void
MyASTConsumer::HandleTranslationUnit(ASTContext& Ctx)
{
    assert(false);
}
