// [General.Rules]
// FileName                = 1 # 1: UpperCamel
// FunctionName            = 1 # 1: UpperCamel
// variableName            = 4 # 4: Hungarian
// AllowedUnderscopeChar   = false

// clang-format off
//
// variables (Pointer)
//
void*			varVoidPtr			= NULL;
int*			varIntPtr			= NULL;
int8_t*			varInt8Ptr			= NULL;
int16_t*		varInt16Ptr			= NULL;
int32_t*		varInt32Ptr			= NULL;
int64_t*		varInt64Ptr			= NULL;
uint8_t*		varUint8Ptr			= NULL;
uint16_t*		varUint16Ptr 		= NULL;
uint32_t*		varUint32Ptr 		= NULL;
uint64_t*		varUint64Ptr 		= NULL;

//
// variables (Array)
//
int 			varInt[8]         	= {0};
int8_t 			varInt8[8]     		= {0};
int16_t 		varInt16[8]   		= {0};
int32_t 		varInt32[8]   		= {0};
int64_t 		varInt64[8]   		= {0};
uint8_t 		varUint8[8]   		= {0};
uint16_t 		varUint16[8] 		= {0};
uint32_t 		varUint32[8] 		= {0};
uint64_t 		varUint64[8] 		= {0};

//
// variables
//
size_t 						varSize					= 0;
int8_t 						varInt8					= 0;
int16_t 					varInt16				= 0;
int32_t 					varInt32				= 0;
int64_t 					varInt64				= 0;
uint8_t 					varUint8				= 0;
uint16_t 					varUint16				= 0;
uint32_t 					varUint32				= 0;
uint64_t 					varUint64				= 0;
char 						varCahr					= 'C';
_Bool 						varBool1				= false;
bool 						varBool2				= false;
wchar_t 					varWideChar				= L"WideCharString";
signed char 				varSignedChar			= 0;
unsigned char 				varUnsignedChar			= 0;
short 						varShort				= 0;
short int 					varShortInt				= 0;
signed short 				varSignedShort			= 0;
signed short int 			varSignedShortInt		= 0;
unsigned short 				varUnsignedShort		= 0;
unsigned short int 			varUnsignedShortInt		= 0;
int 						varInt					= 0;
signed 						varSinged				= 0;
signed int 					varSignedInt			= 0;
unsigned 					varUnsigned				= 0;
unsigned int 				varUnsignedInt			= 0;
long 						varLong					= 0;
long int 					varLongInt				= 0;
signed long 				varSingedLong           = 0;
signed long int 			varSingedLongInt        = 0;
unsigned long 				varUnsingedLong         = 0;
unsigned long int 			varUnsignedLongInt      = 0;
long long 					varLongLong             = 0;
long long int 				varLongLongInt          = 0;
signed long long 			varSignedLongLong       = 0;
signed long long int 		varSignedLongLongInt    = 0;
unsigned long long 			varUnsignedLongLong     = 0;
unsigned long long int 		varUnsignedLongLongInt 	= 0;
float 						varFloat				= 0.0;
double 						varDouble				= 0.0;
long double					varLongDouble			= 0.0;

ULONG 						winVarUlong       	= 0;
DWORD 						winVarDword      	= 0;
DWORD64 					winVarDword64   	= 0;
WORD 						winVarWord         	= 0;
CHAR 						winVarChar         	= 'C';
BYTE 						winVarByte         	= 0;
HANDLE 						winVarHandle     	= NULL;
BOOLEAN 					winVarBoolean   	= FALSE;
LONGLONG 					winVarLongLong 		= 0;

//
// Function
//
int myFunc(int my_val) { return 0; }
int myFunc_1(int my_val) { return 0; }

//
// Function (Prefix String)
//
int _myFunc(int my_val) { return 0; }
int __myFunc(int my_val) { return 0; }
int XXX_myFunc(int my_val) { return 0; }

//
// Function (Underscore)
//
int myFunc1(int myVal) { return 0; }
int myFunc_(int myVal) { return 0; }
int myFunc_1(int myVal) { return 0; }

// clang-format on