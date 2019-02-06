#include "ParseAST.h"
#include <assert.h>

#if __has_include("filesystem")
#    include <filesystem>
using namespace filesystem;
#else
#    include <boost/filesystem.hpp>
using namespace boost::filesystem;
#endif

#include <iomanip>
#include "Common.h"

using namespace namelint;

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

bool MyASTVisitor::getPosition(Decl *pDecl, string &FileName, size_t &nLineNumb, size_t &nColNumb)
{
    if (!this->m_pAstCxt)
    {
        this->m_pAstCxt = &pDecl->getASTContext();
        assert(false);
        return false;
    }

    bool bStatus = false;

    FullSourceLoc FullLocation = this->m_pAstCxt->getFullLoc(pDecl->getBeginLoc());
    if (FullLocation.isValid())
    {
        FileName = FullLocation.getFileLoc().getFileEntry()->getName();
        if ((FileName != GetAppCxt()->FileName) || ("" == GetAppCxt()->FileName))
        {
            APP_CONTEXT *pAppCxt = (APP_CONTEXT *)GetAppCxt();
            pAppCxt->FileName    = FileName;

            path Path1   = FileName;
            string Path2 = Path1.lexically_normal().string();

            String::Replace(Path2, "\\\\", "\\");
            String::Replace(Path2, "\"", "");
            cout << endl << "[" << Path2 << "]" << endl;
        }

        nLineNumb = FullLocation.getSpellingLineNumber();
        nColNumb  = FullLocation.getSpellingColumnNumber();
        bStatus   = true;
    }

    return bStatus;
}

bool MyASTVisitor::printPosition(Decl *pDecl)
{
    string FileName;
    size_t nLineNumb = 0;
    size_t nColNumb  = 0;
    bool bStatus     = getPosition(pDecl, FileName, nLineNumb, nColNumb);
    if (bStatus)
    {
        cout << "  <" << nLineNumb << "," << nColNumb << ">" << setw(12);
    }
    return bStatus;
}

bool MyASTVisitor::classifyTypeName(string &TyeName)
{
    bool bStatus = true;

    String::Replace(TyeName, "struct", "");
    String::Replace(TyeName, "const", "");
    String::Replace(TyeName, "&", "");
    String::Replace(TyeName, "* ", "*");
    String::Replace(TyeName, " *", "*");
    String::Trim(TyeName);

    return bStatus;
}

bool MyASTVisitor::getFunctionInfo(FunctionDecl *pFuncDecl, string &FuncName)
{
    if (!pFuncDecl->hasBody())
    {
        return false;
    }
    if (!this->isMainFile(pFuncDecl))
    {
        return false;
    }

    FuncName = pFuncDecl->getDeclName().getAsString();
    return true;
}

bool MyASTVisitor::getParmsInfo(ParmVarDecl *pParmVarDecl, string &VarType, string &VarName)
{
    if (!pParmVarDecl)
    {
        return false;
    }
    if (!this->isMainFile(pParmVarDecl))
    {
        return false;
    }

    QualType QualType = pParmVarDecl->getType();

    VarName = pParmVarDecl->getName().data();
    VarType = QualType.getAsString();
    if (VarType.length() > 0)
    {
        this->classifyTypeName(VarType);
    }

    return true;
}

bool MyASTVisitor::getVarInfo(VarDecl *pVarDecl, string &VarType, string &VarName)
{
    if (!pVarDecl)
    {
        return false;
    }

    if (!this->isMainFile(pVarDecl))
    {
        return false;
    }

    QualType myQualType = pVarDecl->getType();
    VarName             = pVarDecl->getNameAsString();
    VarType             = pVarDecl->getType().getAsString();
    if (VarType.length() > 0)
    {
        this->classifyTypeName(VarType);
    }

    return true;
}

bool MyASTVisitor::assertWithFunction(FunctionDecl *pDecl, string &FuncName)
{
    this->printPosition(pDecl);
    if ("" == FuncName)
    {
        cout << "Function:\t<INVALID>" << endl;
    }
    else
    {
        cout << "Function:\t" << FuncName << endl;
    }
    return true;
}

bool MyASTVisitor::assertWithParm(ParmVarDecl *pDecl, string &TypeName, string &VarName)
{
    this->printPosition(pDecl);
    if ("" == VarName)
    {
        cout << "Parameter:\t<INVALID>" << endl;
    }
    else
    {
        cout << "Parameter:\t" << VarName << " (" << TypeName << ")" << endl;
    }
    return true;
}

bool MyASTVisitor::assertWithVar(VarDecl *pDecl, string &TypeName, string &VarName)
{
    this->printPosition(pDecl);
    if ("" == VarName)
    {
        cout << "Variable:\t<INVALID>" << endl;
    }
    else
    {
        cout << "Variable:\t" << VarName << " (" << TypeName << ")" << endl;
    }
    return true;
}

MyASTVisitor::MyASTVisitor(const SourceManager *pSM,
                           const ASTContext *pAstCxt,
                           const namelint::Config *pConfig)
{
    this->m_pSrcMgr = pSM;
    this->m_pAstCxt = (ASTContext *)pAstCxt;

    this->m_bCheckFile     = pConfig->GetData().m_General.bCheckFileName;
    this->m_bCheckFunction = pConfig->GetData().m_General.bCheckFunctionName;
    this->m_bCheckVariable = pConfig->GetData().m_General.bCheckVariableName;

    this->m_FileRuleType     = pConfig->GetData().m_Rule.FileName;
    this->m_FunctionRuleType = pConfig->GetData().m_Rule.FunctionName;
    this->m_VariableRuleType = pConfig->GetData().m_Rule.VariableName;

    this->m_FileExt              = pConfig->GetData().m_General.FileExtName;
    this->m_FunctionIgnorePrefix = pConfig->GetData().m_WhiteList.FunctionPrefix;
    this->m_VariableIgnorePrefix = pConfig->GetData().m_WhiteList.VariablePrefix;
    this->m_IgnoreFunctions      = pConfig->GetData().m_WhiteList.IgnoreFunctions;

    this->m_HungarianMappedList = pConfig->GetData().m_HungarianList.MappedTable;

    this->bAllowedEndWithUnderscopeChar = pConfig->GetData().m_WhiteList.bAllowedUnderscopeChar;
}

bool MyASTVisitor::VisitFunctionDecl(clang::FunctionDecl *pDecl)
{
    if (!this->m_bCheckFunction)
    {
        return true;
    }

    string FuncName;
    bool bResult = false;
    bool bStatus = this->getFunctionInfo(pDecl, FuncName);
    if (bStatus)
    {
        bResult = this->m_Detect.CheckFunction(this->m_FunctionRuleType, FuncName,
                                               this->m_FunctionIgnorePrefix,
                                               this->bAllowedEndWithUnderscopeChar);
        if (!bResult)
        {
            ((APP_CONTEXT *)GetAppCxt())->nAsserted++;
            this->assertWithFunction(pDecl, FuncName);
        }

        const clang::ArrayRef<clang::ParmVarDecl *> parmRefArray = pDecl->parameters();
        for (size_t nIdx = 0; nIdx < parmRefArray.size(); nIdx++)
        {
            string VarType;
            string VarName;
            ParmVarDecl *pParmVarDecl = parmRefArray[nIdx];

            bStatus = this->getParmsInfo(pParmVarDecl, VarType, VarName);
            if (bStatus)
            {
                bResult = this->m_Detect.CheckVariable(this->m_VariableRuleType, VarType, VarName,
                                                       this->m_VariableIgnorePrefix,
                                                       this->m_HungarianMappedList);
                if (!bResult)
                {
                    ((APP_CONTEXT *)GetAppCxt())->nAsserted++;
                    this->assertWithParm(pParmVarDecl, VarType, VarName);
                }
            }
        }
    }

    return bStatus;
}

bool MyASTVisitor::VisitCXXMethodDecl(CXXMethodDecl *pDecl)
{
    if (!this->printPosition(pDecl))
    {
        return false;
    }

    assert(false);
    printf("VisitCXXMethodDecl:  %s()\n", pDecl->getNameAsString().c_str());
    return true;
}

bool MyASTVisitor::VisitRecordDecl(RecordDecl *pDecl)
{
    if (!this->isMainFile(pDecl))
    {
        return false;
    }

    if (!this->printPosition(pDecl))
    {
        return false;
    }

    assert(false);
    printf("VisitRecordDecl:  %s (isClass=%d)\n", pDecl->getNameAsString().c_str(),
           pDecl->isClass());
    return true;
}

bool MyASTVisitor::VisitVarDecl(VarDecl *pDecl)
{
    if (!this->m_bCheckVariable)
    {
        return true;
    }

    string VarType;
    string VarName;

    bool bStauts = this->getVarInfo(pDecl, VarType, VarName);
    if (bStauts)
    {
        bool bResult =
            this->m_Detect.CheckVariable(this->m_VariableRuleType, VarType, VarName,
                                         this->m_VariableIgnorePrefix, this->m_HungarianMappedList);
        if (!bResult)
        {
            ((APP_CONTEXT *)GetAppCxt())->nAsserted++;
            this->assertWithVar(pDecl, VarType, VarName);
        }
    }

    return bStauts;
}

bool MyASTVisitor::VisitReturnStmt(ReturnStmt *pRetStmt)
{
    assert(pRetStmt);

    const Expr *pExpr = pRetStmt->getRetValue();
    if (pExpr)
    {
        clang::QualType qualType = pExpr->getType();
        std::string strType      = qualType.getAsString();
        return true;
    }

    // printf("VisitReturnStmt:  %s \n", strType.c_str());
    return false;
}

//==---------------------------------------------------------------------------------------------==
bool MyASTConsumer::HandleTopLevelDecl(clang::DeclGroupRef declGroupRef)
{
    string FileName;
    for (clang::DeclGroupRef::iterator Iter = declGroupRef.begin(), e = declGroupRef.end();
         Iter != e; ++Iter)
    {
        Decl *pDecl = *Iter;

        const ASTContext &ASTCxt = pDecl->getASTContext();

        FullSourceLoc FullLocation = ASTCxt.getFullLoc(pDecl->getBeginLoc());
        if (FullLocation.isValid())
        {
            FileName = FullLocation.getFileLoc().getFileEntry()->getName();
        }

        if (ASTCxt.getSourceManager().isInMainFile(pDecl->getLocation()))
        {
            namelint::Config *pCfg = (namelint::Config *)GetAppCxt()->pTomlConfig;

            const SourceManager &SrcMgr = ASTCxt.getSourceManager();
            MyASTVisitor myVisitor(&SrcMgr, &ASTCxt, pCfg);
            myVisitor.TraverseDecl(*Iter);
        }
    }

    return true;
}

void MyASTConsumer::HandleTranslationUnit(ASTContext &Ctx) {}

//==---------------------------------------------------------------------------------------------==
unique_ptr<MyASTConsumer> MyFactory::newASTConsumer() { return llvm::make_unique<MyASTConsumer>(); }
