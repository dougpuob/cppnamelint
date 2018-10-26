#include "ParseAST.h"

bool MyASTVisitor::isMainFile(Decl *pDecl)
{
    if (this->m_pAstCxt->getSourceManager().isInMainFile(pDecl->getLocation()))
    {
        return true;
    }
    return false;
}

void MyASTVisitor::keepFileName(string &FilePath)
{
    size_t nPos = FilePath.rfind("\\");
    if (nPos < 0)
    {
        nPos = FilePath.rfind("/");
    }

    if (nPos > 0)
    {
        FilePath = FilePath.substr(nPos + 1, FilePath.length() - nPos - 1);
    }
}

bool MyASTVisitor::dumpPosition(Decl *pDecl)
{
    if (!this->m_pAstCxt)
    {
        this->m_pAstCxt = &pDecl->getASTContext();
    }

    FullSourceLoc FullLocation = this->m_pAstCxt->getFullLoc(pDecl->getBeginLoc());
    if (FullLocation.isValid())
    {
        string FileName = FullLocation.getFileLoc().getFileEntry()->getName();
        this->keepFileName(FileName);
        cout << FileName << " <Line:" << FullLocation.getSpellingLineNumber()
             << ",Col:" << FullLocation.getSpellingColumnNumber() << "> ";
    }
    return true;
}

MyASTVisitor::MyASTVisitor(const SourceManager *pSM, const ASTContext *pAstCxt)
{
    this->m_pSM     = pSM;
    this->m_pAstCxt = (ASTContext *)pAstCxt;
}

bool MyASTVisitor::VisitStmt(clang::Stmt *pStmt)
{
    string StmtName = pStmt->getStmtClassName();
    // printf("VisitStmt:  %s()\n", StmtName.c_str());
    return true;
}

// bool MyASTVisitor::VisitCXXConstructorDecl(CXXConstructorDecl *D)
//{
//    if (!this->dumpPosition(D)) {
//        return false;
//    }
//
//    printf("VisitCXXConstructorDecl:  %s()\n", D->getNameAsString().c_str());
//    return true;
//}

bool MyASTVisitor::VisitFunctionDecl(clang::FunctionDecl *pFuncDecl)
{
    if (!this->isMainFile(pFuncDecl))
    {
        return false;
    }

    if (pFuncDecl->hasBody() && this->dumpPosition(pFuncDecl))
    {
        const string funcName = pFuncDecl->getDeclName().getAsString();

        printf("VisitFunctionDecl:  %s()\n", funcName.c_str());
        const clang::ArrayRef<clang::ParmVarDecl *> parmRefArray = pFuncDecl->parameters();
        for (size_t nIdx = 0; nIdx < parmRefArray.size(); nIdx++)
        {
            const ParmVarDecl *pParmVarDecl = parmRefArray[nIdx];
            string strName                  = pParmVarDecl->getNameAsString();
            QualType qualType               = pParmVarDecl->getType();
            const char *szTypeClassName     = qualType->getTypeClassName();
            string strType                  = qualType.getAsString();

            this->dumpPosition(pFuncDecl);
            printf("        Parm[%d] : %s (%s) \n", nIdx, strName.c_str(), strType.c_str());
        }
    }
    return true;
}

bool MyASTVisitor::VisitCXXMethodDecl(CXXMethodDecl *D)
{
    if (!this->dumpPosition(D))
    {
        return false;
    }

    printf("VisitCXXMethodDecl:  %s()\n", D->getNameAsString().c_str());
    return true;
}

bool MyASTVisitor::VisitRecordDecl(RecordDecl *pDecl)
{
    if (!this->isMainFile(pDecl))
    {
        return false;
    }

    if (!this->dumpPosition(pDecl))
    {
        return false;
    }

    printf("VisitRecordDecl:  %s (isClass=%d)\n", pDecl->getNameAsString().c_str(), pDecl->isClass());
    return true;
}

// bool MyASTVisitor::VisitCXXRecordDecl(CXXRecordDecl *D)
//{
//    if (!this->dumpPosition(D)) {
//        return false;
//    }
//    printf("VisitCXXRecordDecl:  %s\n", D->getNameAsString().c_str());
//    return true;
//}

bool MyASTVisitor::VisitVarDecl(VarDecl *pVarDecl)
{
    if (!this->isMainFile(pVarDecl))
    {
        return false;
    }

    if (!this->dumpPosition(pVarDecl))
    {
        return false;
    }
    printf("    VisitVarDecl:  %s\t%s \n", pVarDecl->getType().getAsString().c_str(),
           pVarDecl->getNameAsString().c_str());
    return true;
}

bool MyASTVisitor::VisitReturnStmt(ReturnStmt *pRetStmt)
{
    clang::QualType qualType = pRetStmt->getRetValue()->getType();
    std::string strType      = qualType.getAsString();

    printf("VisitReturnStmt:  %s \n", strType.c_str());
    return true;
}

//==---------------------------------------------------------------------------------------------==
bool MyASTConsumer::HandleTopLevelDecl(clang::DeclGroupRef declGroupRef)
{
    for (clang::DeclGroupRef::iterator b = declGroupRef.begin(), e = declGroupRef.end(); b != e; ++b)
    {
        Decl *pDecl             = *b;
        const ASTContext &Ctx   = pDecl->getASTContext();
        const SourceManager &SM = Ctx.getSourceManager();

        MyASTVisitor myVisitor(&SM, &Ctx);
        myVisitor.TraverseDecl(*b);
    }

    return true;
}

void MyASTConsumer::HandleTranslationUnit(ASTContext &Ctx) {}

//==---------------------------------------------------------------------------------------------==
unique_ptr<MyASTConsumer> MyFactory::newASTConsumer() { return llvm::make_unique<MyASTConsumer>(); }
