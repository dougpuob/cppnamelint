
static const uint8_t u8UhsSpeeds[];
static const uint8_t *u8UhsSpeeds[];

static const char *const szUhsSpeeds[];
char *szBuf   = NULL;
int *piValueA = NULL, iValueB = 1, iValueC = 2;
int *piValueD = NULL, *piValueE = NULL, *piValueF = NULL;
int iValueG = 0, iValueH = 1, iValueI = 2;

void InCallee(_In_ int *pInt) { int i = *pInt; }

void GoodInOptCallee(_In_opt_ int *pInt) {
    if (pInt != NULL) {
        int i = *pInt;
    }
}

void GoodOutCallee(_Out_ int *pInt) { *pInt = 5; }
