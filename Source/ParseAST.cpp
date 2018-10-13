#include "ParseAST.h"



void MyASTVisitor::keepFileName(string& FilePath)
{
    size_t nPos = FilePath.rfind("\\");
    if (nPos < 0) {
        nPos = FilePath.rfind("/");
    }

    if (nPos > 0) {
        FilePath = FilePath.substr(nPos + 1, FilePath.length() - nPos - 1);
    }
}

bool MyASTVisitor::dumpPosition(Decl* pDecl)
{
    if (!this->m_pAstCxt) {
        this->m_pAstCxt = &pDecl->getASTContext();
    }

    FullSourceLoc FullLocation = this->m_pAstCxt->getFullLoc(pDecl->getBeginLoc());
    if (FullLocation.isValid())
    {
        //const FileEntry* pFileEntry = FullLocation.getFileEntry();
        //string aaa = FullLocation.getFileLoc().getFileEntry()->getName();
        //        
        //if (!pFileEntry) {
        //    cout << " ERROR1 ";
        //    return false;            
        //}

        string FileName = FullLocation.getFileLoc().getFileEntry()->getName();

        this->keepFileName(FileName);  
        if (FileName.length() - 2 == FileName.rfind(".h")) {
            //cout << " ERROR2 ";
            return false;
        }

        cout << FileName
             << " <Line:"
             << FullLocation.getSpellingLineNumber() << ",Col:"
             << FullLocation.getSpellingColumnNumber() << "> ";
    }
    return true;
}


MyASTVisitor::MyASTVisitor(const SourceManager *pSM)
{    
    this->m_pSM     = pSM;    
    this->m_pAstCxt = NULL;
}

bool MyASTVisitor::VisitStmt(clang::Stmt* pStmt) 
{
    string StmtName = pStmt->getStmtClassName();
    //printf("VisitStmt:  %s()\n", StmtName.c_str());
    return true;
}

//bool MyASTVisitor::VisitCXXConstructorDecl(CXXConstructorDecl *D)
//{
//    if (!this->dumpPosition(D)) {
//        return false;
//    }
//
//    printf("VisitCXXConstructorDecl:  %s()\n", D->getNameAsString().c_str());
//    return true;
//}

bool MyASTVisitor::VisitFunctionDecl(clang::FunctionDecl* pFuncDecl)
{
    //if (!this->dumpPosition(pFuncDecl)) {
    //    return false;
    //}

    if (pFuncDecl->hasBody() && this->dumpPosition(pFuncDecl))
    {
        const string funcName = pFuncDecl->getDeclName().getAsString();
                
        printf("VisitFunctionDecl:  %s()\n", funcName.c_str());
        const clang::ArrayRef<clang::ParmVarDecl *> parmRefArray = pFuncDecl->parameters();
        for (int iIdx = 0; iIdx < parmRefArray.size(); iIdx++)
        {
            const ParmVarDecl* pParmVarDecl = parmRefArray[iIdx];
            string      strName         = pParmVarDecl->getNameAsString();
            QualType    qualType        = pParmVarDecl->getType();
            const char *szTypeClassName = qualType->getTypeClassName();
            string      strType         = qualType.getAsString();
            
            this->dumpPosition(pFuncDecl);
            printf("        Parm[%d] : %s (%s) \n", iIdx, strName.c_str(), strType.c_str());
        }
    }
    return true;
}

bool MyASTVisitor::VisitCXXMethodDecl(CXXMethodDecl *D)
{
    if (!this->dumpPosition(D)) {
        return false;
    }

    printf("VisitCXXMethodDecl:  %s()\n", D->getNameAsString().c_str());
    return true;
}

bool MyASTVisitor::VisitRecordDecl(RecordDecl *D)
{    
    if (!this->dumpPosition(D)) {
        return false;
    }

    printf("VisitRecordDecl:  %s (isClass=%d)\n", D->getNameAsString().c_str(), D->isClass());
    return true;
}

//bool MyASTVisitor::VisitCXXRecordDecl(CXXRecordDecl *D)
//{
//    if (!this->dumpPosition(D)) {
//        return false;
//    }
//    printf("VisitCXXRecordDecl:  %s\n", D->getNameAsString().c_str());        
//    return true;
//}


bool MyASTVisitor::VisitVarDecl(VarDecl *pVarDecl)
{
    if (!this->dumpPosition(pVarDecl)) {
        return false;
    }
    printf("    VisitVarDecl:  %s\t%s \n", pVarDecl->getType().getAsString().c_str(), pVarDecl->getNameAsString().c_str());
    return true;
}

bool MyASTVisitor::VisitReturnStmt(ReturnStmt *pRetStmt) 
{
    //pRetStmt->getReturnLoc().
    //if (!this->dumpPosition(pRetStmt)) {
    //    return false;
    //}

    clang::QualType qualType = pRetStmt->getRetValue()->getType();
    std::string strType = qualType.getAsString();

    printf("VisitReturnStmt:  %s \n", strType.c_str());
    return true;
}




//==---------------------------------------------------------------------------------------------==
bool MyASTConsumer::HandleTopLevelDecl(clang::DeclGroupRef declGroupRef) 
{
    for (clang::DeclGroupRef::iterator b = declGroupRef.begin(), e = declGroupRef.end(); b != e; ++b) {        
        Decl *pDecl = *b;
        const ASTContext &Ctx   = pDecl->getASTContext();
        const SourceManager &SM = Ctx.getSourceManager();

        MyASTVisitor myVisitor(&SM);
        myVisitor.TraverseDecl(*b);        
    }       
    
    return true;
}


void MyASTConsumer::HandleTranslationUnit(ASTContext & 	Ctx)
{
}


//==---------------------------------------------------------------------------------------------==
unique_ptr<MyASTConsumer> MyFactory::newASTConsumer() {
    return llvm::make_unique<MyASTConsumer>();
}



//==---------------------------------------------------------------------------------------------==
//void MyIgnoringDiagConsumer::HandleDiagnostic(DiagnosticsEngine::Level DiagLevel, const Diagnostic &Info)
//{
//    cout << "@@@@" << endl;
//    //cout << "DiagLevel : " << DiagLevel << endl;
//    //cout << "Info      : " << Info.getArgStdStr(0) << endl;
//}


