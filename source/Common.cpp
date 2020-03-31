#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

#include "Common.h"

static APP_CONTEXT m_AppCxt;
const APP_CONTEXT *GetAppCxt() { return &m_AppCxt; }

namespace Path {
bool IsExist(const string &Path) {
  FILE *pFile = fopen(Path.c_str(), "r");
  bool bStatus = (NULL != pFile);
  if (bStatus) {
    fclose(pFile);
  }

  return bStatus;
}

const char *FindFileName(const string &Path) {
  size_t nPos = Path.find_last_of("\\");
  if (nPos == string::npos) {
    nPos = Path.find_last_of("/");
    if (nPos == string::npos) {
      return Path.c_str();
    }
  }
  return Path.c_str() + nPos + 1;
}

bool NormPath(const char *szPath, string &NewPath) {
  if (!szPath) {
    return NULL;
  }

  bool bStatus = false;
  size_t nRet = 0;

  char szBuf[4096];

#if WIN32
  memset(szBuf, 0, sizeof(szBuf));
  if (_fullpath(szBuf, szPath, sizeof(szBuf)) != NULL) {
    bStatus = true;
    NewPath.assign(szBuf);
  }
#else
  if (NULL != realpath(szPath, szBuf)) {
    bStatus = true;
    NewPath.assign(szBuf);
  }
#endif

  return bStatus;
}
} // namespace Path

namespace String {

void PadTo(string &Source, size_t nCount, char cChar) {
  if (nCount > Source.length())
    Source.append(nCount - Source.length(), cChar);
}

bool IsLower(const string &Source) {
  bool bStatus = true;
  for (std::string::const_iterator Iter = Source.begin(); Iter != Source.end(); Iter++) {
    if (isupper(*Iter)) {
      bStatus = false;
      break;
    }
  }

  return bStatus;
}

void Replace(string &Source, const string &Patn, const string &New) {
  string::size_type Pos = 0;
  string::size_type SrcLen = Patn.size();
  string::size_type DstLen = New.size();
  while ((Pos = Source.find(Patn, Pos)) != string::npos) {
    Source.replace(Pos, SrcLen, New);
    Pos += DstLen;
  }
}

void Trim(string &Source) {
  if (Source.empty()) {
    return;
  }

  Source.erase(0, Source.find_first_not_of("\t"));
  Source.erase(0, Source.find_first_not_of(" "));
  Source.erase(Source.find_last_not_of("\t") + 1);
  Source.erase(Source.find_last_not_of(" ") + 1);
}

size_t Split(const std::string &txt, std::vector<std::string> &strs, char ch) {
  size_t pos = txt.find(ch);
  size_t initialPos = 0;
  strs.clear();

  // Decompose statement
  while (pos != std::string::npos) {
    strs.push_back(txt.substr(initialPos, pos - initialPos));
    initialPos = pos + 1;

    pos = txt.find(ch, initialPos);
  }

  // Add the last one
  strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

  return strs.size();
}

} // namespace String