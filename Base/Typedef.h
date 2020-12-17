/*----------------------------------------------------------------------*/
/*                                                                      */
/*      DATA TYPE DEFINEs                                               */
/*                                                           Norix      */
/*                                               written     2000/11/09 */
/*                                               last modify ----/--/-- */
/*----------------------------------------------------------------------*/
#ifndef	__TYPEDEF_INCLUDED__
#define	__TYPEDEF_INCLUDED__
#include <cstdint>

typedef	int		BOOL;

typedef	unsigned char	BYTE;
typedef	unsigned short	WORD;
typedef	unsigned long	DWORD;
typedef	uint64_t QWORD;

typedef float               FLOAT;
typedef FLOAT*              PFLOAT;

typedef	unsigned char	UBYTE;
typedef	unsigned short	UWORD;
typedef	unsigned long	ULONG;
typedef	unsigned long	UDWORD;
typedef	uint64_t UQWORD;

typedef	signed char	SBYTE;
typedef	signed short	SWORD;
typedef	signed long	SLONG;
typedef	signed long	SDWORD;
typedef	int64_t	SQWORD;

typedef	signed int	INT;
typedef	unsigned int	UINT;
typedef	signed short	SHORT;
typedef	signed long	LONG;

typedef	BYTE		*LPBYTE;
typedef	WORD		*LPWORD;
typedef	DWORD		*LPDWORD;

typedef	SBYTE		*LPSBYTE;
typedef	SWORD		*LPSWORD;
typedef	SLONG		*LPSLONG;
typedef	SDWORD		*LPSDWORD;

typedef	UBYTE		*LPUBYTE;
typedef	UWORD		*LPUWORD;
typedef	ULONG		*LPULONG;
typedef	UDWORD		*LPUDWORD;

typedef	SHORT		*LPSHORT;
typedef	LONG		*LPLONG;

//
// ANSI (Multi-byte Character) types
//
typedef char CHAR;
typedef CHAR* PCHAR, * LPCH, * PCH;
typedef const CHAR* LPCCH, * PCCH;

typedef CHAR* NPSTR, * LPSTR, * PSTR;
typedef PSTR* PZPSTR;
typedef const PSTR* PCZPSTR;
typedef const CHAR* LPCSTR, * PCSTR;
typedef PCSTR* PZPCSTR;
typedef const PCSTR* PCZPCSTR;

typedef CHAR* PZZSTR;
typedef const CHAR* PCZZSTR;

typedef  CHAR* PNZCH;
typedef  const CHAR* PCNZCH;

typedef LPCH LPTCH, PTCH;
typedef LPCCH LPCTCH, PCTCH;
typedef LPSTR PTSTR, LPTSTR, PUTSTR, LPUTSTR;
typedef LPCSTR PCTSTR, LPCTSTR, PCUTSTR, LPCUTSTR;
typedef PZZSTR PZZTSTR, PUZZTSTR;
typedef PCZZSTR PCZZTSTR, PCUZZTSTR;
typedef PZPSTR PZPTSTR;
typedef PNZCH PNZTCH, PUNZTCH;
typedef PCNZCH PCNZTCH, PCUNZTCH;


typedef char CCHAR;
typedef DWORD LCID;
typedef WORD   LANGID;

#ifndef BASETYPES
#define BASETYPES
typedef unsigned long ULONG;
typedef ULONG* PULONG;
typedef unsigned short USHORT;
typedef USHORT* PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR* PUCHAR;
typedef char* PSZ;
#endif  /* !BASETYPES */

#if defined(_WIN64) || defined(__x86_64__)
typedef int64_t INT_PTR, * PINT_PTR;
typedef uint64_t UINT_PTR, * PUINT_PTR;

typedef int64_t LONG_PTR, * PLONG_PTR;
typedef uint64_t ULONG_PTR, * PULONG_PTR;

#define __int3264   int64_t

#else
typedef _W64 int INT_PTR, * PINT_PTR;
typedef _W64 unsigned int UINT_PTR, * PUINT_PTR;

typedef _W64 long LONG_PTR, * PLONG_PTR;
typedef _W64 unsigned long ULONG_PTR, * PULONG_PTR;

#define __int3264   __int32

#endif

typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;

typedef void* LPVOID;

// Byte pair
typedef	union	{
	struct	{ BYTE L; BYTE H; } B;
	WORD	W;
} PAIR, *LPPAIR;

#define MAX_PATH          260
#define MAX_FNAME         256

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#ifdef _WIN32
#ifndef CALLBACK
#define CALLBACK __stdcall
#endif
#else
#define CALLBACK
#endif

#ifndef ZeroMemory
#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))
#define FillMemory(Destination, Length, Fill) memset((Destination), (Fill), (Length))
#endif

typedef int* PINT;
typedef int* LPINT;

#endif
