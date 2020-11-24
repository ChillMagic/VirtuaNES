/*---------------------------------------------------------------------*
 * The following (piece of) code, (part of) the 2xSaI engine,          *
 * copyright (c) 2001 by Derek Liauw Kie Fa.                           *
 * Non-Commercial use of the engine is allowed and is encouraged,      *
 * provided that appropriate credit be given and that this copyright   *
 * notice will not be removed under any circumstance.                  *
 * You may freely modify this code, but I request                      *
 * that any improvements to the engine be submitted to me, so          *
 * that I can implement these improvements in newer versions of        *
 * the engine.                                                         *
 * If you need more information, have any comments or suggestions,     *
 * you can e-mail me. My e-mail: DerekL666@yahoo.com                   *
 *---------------------------------------------------------------------*/
//
// This code was converted into VirtuaNES by Norix.
//
static	void	nx_2xSaILine_16bpp_mmx( euI8* pSrc, euI8* pDlt, euI32 srcPitch, euI32 width, euI8* pDst, euI32 dstPitch, euI32 bForceWrite )
{
	__asm {
		mov		eax, pSrc
		mov		ebx, srcPitch
		mov		edx, pDst
		sub		eax, ebx
nx_2xSaILine_16mmx_loop:
		mov		ecx, bForceWrite
		test		ecx, ecx
		jz		nx_2xSaILine_16mmx_normal

		mov		esi, pDlt
		movq		mm6, [eax+colorI]
		movq		[esi+colorI], mm6

		jmp		nx_2xSaILine_16mmx_forcewrite
nx_2xSaILine_16mmx_normal:
		// Check delta
		mov		ecx, pDlt

		// load source img
		lea		esi, [eax+ebx]
		movq		mm0, [eax+colorI]
		movq		mm1, [eax+colorJ]
		movq		mm2, [eax+ebx+colorG]
		movq		mm3, [eax+ebx+colorK]
		movq		mm4, [eax+ebx*2+colorH]
		movq		mm5, [eax+ebx*2+colorL]
		movq		mm6, [esi+ebx*2+colorM]
		movq		mm7, [esi+ebx*2+colorP]

		// compare to delta
		lea		esi, [ecx+ebx]
		pcmpeqw		mm0, [ecx+colorI]
		pcmpeqw		mm1, [ecx+colorJ]
		pcmpeqw		mm2, [ecx+ebx+colorG]
		pcmpeqw		mm3, [ecx+ebx+colorK]
		pcmpeqw		mm4, [ecx+ebx*2+colorH]
		pcmpeqw		mm5, [ecx+ebx*2+colorL]
		pcmpeqw		mm6, [esi+ebx*2+colorM]
		pcmpeqw		mm7, [esi+ebx*2+colorP]

		// compose results
		pand		mm0, mm1
		pand		mm2, mm3
		pand		mm4, mm5
		pand		mm6, mm7
		pand		mm0, mm2
		pand		mm4, mm6
		pxor		mm7, mm7
		pand		mm0, mm4
		movq		mm6, [eax+colorI]
		pcmpeqw		mm7, mm0

		movq		[ecx+colorI], mm6

		packsswb	mm7, mm7
		movd		ecx, mm7
		test		ecx, ecx
		jz		nx_2xSaILine_16mmx_skipprocess
		// End Delta
nx_2xSaILine_16mmx_forcewrite:
		//------------------------------
		// 1
		// if ((colorA == colorD) && (colorB != colorC) && (colorA == colorE) && (colorB == colorL)
		movq		mm0, [eax+ebx+colorA]		// mm0 and mm1 contain colorA
		movq		mm2, [eax+ebx+colorB]		// mm2 and mm3 contain colorB

		movq		mm1, mm0
		movq		mm3, mm2

		pcmpeqw		mm0, [eax+ebx*2+colorD]
		pcmpeqw		mm1, [eax+colorE]
		pcmpeqw		mm2, [eax+ebx*2+colorL]
		pcmpeqw		mm3, [eax+ebx*2+colorC]

		pand		mm0, mm1
		pxor		mm1, mm1
		pand		mm0, mm2
		pcmpeqw		mm3, mm1
		pand		mm0, mm3			// result in mm0

		// if ((colorA == colorC) && (colorB != colorE) && (colorA == colorF) && (colorB == colorJ)
		movq		mm4, [eax+ebx+colorA]		// mm4 and mm5 contain colorA
		movq		mm6, [eax+ebx+colorB]		// mm6 and mm7 contain colorB
		movq		mm5, mm4
		movq		mm7, mm6

		pcmpeqw		mm4, [eax+ebx*2+colorC]
		pcmpeqw		mm5, [eax+colorF]
		pcmpeqw		mm6, [eax+colorJ]
		pcmpeqw		mm7, [eax+colorE]

		pand		mm4, mm5
		pxor		mm5, mm5
		pand		mm4, mm6
		pcmpeqw		mm7, mm5
		pand		mm4, mm7			// result in mm4

		por		mm0, mm4			// combine the masks
		movq		Mask1, mm0

		//------------------------------
		// 2
		// if ((colorB == colorC) && (colorA != colorD) && (colorB == colorF) && (colorA == colorH)
		movq		mm0, [eax+ebx+colorB]		// mm0 and mm1 contain colorB
		movq		mm2, [eax+ebx+colorA]		// mm2 and mm3 contain colorA
		movq		mm1, mm0
		movq		mm3, mm2

		pcmpeqw		mm0, [eax+ebx*2+colorC]
		pcmpeqw		mm1, [eax+colorF]
		pcmpeqw		mm2, [eax+ebx*2+colorH]
		pcmpeqw		mm3, [eax+ebx*2+colorD]

		pand		mm0, mm1
		pxor		mm1, mm1
		pand		mm0, mm2
		pcmpeqw		mm3, mm1
		pand		mm0, mm3			// result in mm0

		// if ((colorB == colorE) && (colorB == colorD) && (colorA != colorF) && (colorA == colorI)
		movq		mm4, [eax+ebx+colorB]		// mm4 and mm5 contain colorB
		movq		mm6, [eax+ebx+colorA]		// mm6 and mm7 contain colorA
		movq		mm5, mm4
		movq		mm7, mm6

		pcmpeqw		mm4, [eax+ebx*2+colorD]
		pcmpeqw		mm5, [eax+colorE]
		pcmpeqw		mm6, [eax+colorI]
		pcmpeqw		mm7, [eax+colorF]

		pand		mm4, mm5
		pxor		mm5, mm5
		pand		mm4, mm6
		pcmpeqw		mm7, mm5
		pand		mm4, mm7			// result in mm4

		por		mm0, mm4			// combine the masks
		movq		Mask2, mm0

		//------------------------------
		// interpolate colorA and colorB
		//------------------------------
		movq		mm0, [eax+ebx+colorA]
		movq		mm1, [eax+ebx+colorB]
		movq		mm2, mm0
		movq		mm3, mm1

		movq		mm6, cMask
		pxor		mm3, mm2
		pand		mm0, mm1
		pand		mm3, mm6
		psrlw		mm3, 1
		paddw		mm0, mm3			// mm0 contains the interpolated values

		// assemble the pixels
		movq		mm1, [eax+ebx+colorA]
		movq		mm2, [eax+ebx+colorB]

		movq		mm3, Mask1
		movq		mm5, mm1
		movq		mm4, Mask2
		movq		mm6, mm1

		pand		mm1, mm3
		por		mm3, mm4
		pxor		mm7, mm7
		pand		mm2, mm4

		pcmpeqw		mm3, mm7
		por		mm1, mm2
		pand		mm0, mm3

		por		mm0, mm1

		punpcklwd	mm5, mm0
		punpckhwd	mm6, mm0

		//------------------------------
		// Write image
		//------------------------------
		movq		[edx+0], mm5
		movq		[edx+8], mm6

		//------------------------------
		// Create the Nextline
		//------------------------------
		// 3
		// if ((colorA == colorD) && (colorB != colorC) && (colorA == colorG) && (colorC == colorO)
		lea		esi, [eax+ebx]

		movq		mm0, [eax+ebx+colorA]		// mm0 and mm1 contain colorA
		movq		mm2, [eax+ebx*2+colorC]		// mm2 and mm3 contain colorC
		movq		mm1, mm0
		movq		mm3, mm2

		pcmpeqw		mm0, [esi+ebx+colorD]
		pcmpeqw		mm1, [esi+colorG]
		pcmpeqw		mm2, [esi+ebx*2+colorO]
		pcmpeqw		mm3, [esi+colorB]

		pand		mm0, mm1
		pxor		mm1, mm1
		pand		mm0, mm2
		pcmpeqw		mm3, mm1
		pand		mm0, mm3			// result in mm0

		// if ((colorA == colorB) && (colorG != colorC) && (colorA == colorH) && (colorC == colorM)
		movq		mm4, [eax+ebx+colorA]		// mm4 and mm5 contain colorA
		movq		mm6, [eax+ebx*2+colorC]		// mm6 and mm7 contain colorC
		movq		mm5, mm4
		movq		mm7, mm6

		pcmpeqw		mm4, [esi+ebx+colorH]
		pcmpeqw		mm5, [esi+colorB]
		pcmpeqw		mm6, [esi+ebx*2+colorM]
		pcmpeqw		mm7, [esi+colorG]

		pand		mm4, mm5
		pxor		mm5, mm5
		pand		mm4, mm6
		pcmpeqw		mm7, mm5
		pand		mm4, mm7			// result in mm4

		por		mm0, mm4			// combine the masks
		movq		Mask1, mm0

		//------------------------------
		// 4
		// if ((colorB == colorC) && (colorA != colorD) && (colorC == colorH) && (colorA == colorF)
		movq		mm0, [eax+ebx*2+colorC]		// mm0 and mm1 contain colorC
		movq		mm2, [eax+ebx+colorA]		// mm2 and mm3 contain colorA
		movq		mm1, mm0
		movq		mm3, mm2

		pcmpeqw		mm0, [eax+ebx+colorB]
		pcmpeqw		mm1, [eax+ebx*2+colorH]
		pcmpeqw		mm2, [eax+colorF]
		pcmpeqw		mm3, [eax+ebx*2+colorD]

		pand		mm0, mm1
		pxor		mm1, mm1
		pand		mm0, mm2
		pcmpeqw		mm3, mm1
		pand		mm0, mm3			// result in mm0

		// if ((colorC == colorG) && (colorC == colorD) && (colorA != colorH) && (colorA == colorI)
		movq		mm4, [eax+ebx*2+colorC]		// mm4 and mm5 contain colorC
		movq		mm6, [eax+ebx+colorA]		// mm6 and mm7 contain colorA
		movq		mm5, mm4
		movq		mm7, mm6

		pcmpeqw		mm4, [eax+ebx*2+colorD]
		pcmpeqw		mm5, [eax+ebx+colorG]
		pcmpeqw		mm6, [eax+colorI]
		pcmpeqw		mm7, [eax+ebx*2+colorH]

		pand		mm4, mm5
		pxor		mm5, mm5
		pand		mm4, mm6
		pcmpeqw		mm7, mm5
		pand		mm4, mm7			// result in mm4

		por		mm0, mm4			;combine the masks
		movq		Mask2, mm0

		//------------------------------
		// interpolate colorA and colorC
		//------------------------------
		movq		mm0, [eax+ebx+colorA]
		movq		mm1, [eax+ebx*2+colorC]
		movq		mm2, mm0
		movq		mm3, mm1

		movq		mm6, cMask
		pxor		mm3, mm2
		pand		mm0, mm1
		pand		mm3, mm6
		psrlw		mm3, 1
		paddw		mm0, mm3			// mm0 contains the interpolated values

		// assemble the pixels
		movq		mm1, [eax+ebx+colorA]
		movq		mm2, [eax+ebx*2+colorC]

		movq		mm3, Mask1
		movq		mm4, Mask2

		pand		mm1, mm3
		pand		mm2, mm4

		por		mm3, mm4
		pxor		mm7, mm7
		por		mm1, mm2

		pcmpeqw		mm3, mm7
		pand		mm0, mm3
		por		mm0, mm1
		movq		ACPixel, mm0

		//------------------------------
		// Decide which "branch" to take
		//------------------------------
		movq		mm0, [eax+ebx+colorA]
		movq		mm1, [eax+ebx+colorB]
		movq		mm6, mm0
		movq		mm7, mm1
		pcmpeqw		mm0, [eax+ebx*2+colorD]
		pcmpeqw		mm1, [eax+ebx*2+colorC]
		pcmpeqw		mm6, mm7

		movq		mm2, mm0
		movq		mm3, mm0

		pand		mm0, mm1			// colorA == colorD && colorB == colorC
		pxor		mm7, mm7

		pcmpeqw		mm2, mm7
		pand		mm6, mm0
		pand		mm2, mm1			// colorA != colorD && colorB == colorC

		pcmpeqw		mm1, mm7

		pand		mm1, mm3			// colorA == colorD && colorB != colorC
		pxor		mm0, mm6
		por		mm1, mm6
		movq		mm7, mm0
		movq		Mask2, mm2
		packsswb	mm7, mm7
		movq		Mask1, mm1

		movd		ecx, mm7
		test		ecx, ecx
		jz		nx_2xSaILine_16mmx_skipguess

		//------------------------------
		// Map of the pixels: I|E F|J
		//                    G|A B|K
		//                    H|C D|L
		//                    M|N O|P
		//------------------------------
		movq		mm6, mm0
		movq		mm4, [eax+ebx+colorA]
		movq		mm5, [eax+ebx+colorB]
		pxor		mm7, mm7
		pand		mm6, ONE

		movq		mm0, [eax+colorE]
		movq		mm1, [eax+ebx+colorG]
		movq		mm2, mm0
		movq		mm3, mm1
		pcmpeqw		mm0, mm4
		pcmpeqw		mm1, mm4
		pcmpeqw		mm2, mm5
		pcmpeqw		mm3, mm5
		pand		mm0, mm6
		pand		mm1, mm6
		pand		mm2, mm6
		pand		mm3, mm6
		paddw		mm0, mm1
		paddw		mm2, mm3

		pxor		mm3, mm3
		pcmpgtw		mm0, mm6
		pcmpgtw		mm2, mm6
		pcmpeqw		mm0, mm3
		pcmpeqw		mm2, mm3
		pand		mm0, mm6
		pand		mm2, mm6
		paddw		mm7, mm0
		psubw		mm7, mm2

		movq		mm0, [eax+colorF]
		movq		mm1, [eax+ebx+colorK]
		movq		mm2, mm0
		movq		mm3, mm1
		pcmpeqw		mm0, mm4
		pcmpeqw		mm1, mm4
		pcmpeqw		mm2, mm5
		pcmpeqw		mm3, mm5
		pand		mm0, mm6
		pand		mm1, mm6
		pand		mm2, mm6
		pand		mm3, mm6
		paddw		mm0, mm1
		paddw		mm2, mm3

		lea		esi, [eax+ebx]

		pxor		mm3, mm3
		pcmpgtw		mm0, mm6
		pcmpgtw		mm2, mm6
		pcmpeqw		mm0, mm3
		pcmpeqw		mm2, mm3
		pand		mm0, mm6
		pand		mm2, mm6
		paddw		mm7, mm0
		psubw		mm7, mm2

		movq		mm0, [esi+ebx+colorH]
		movq		mm1, [esi+ebx*2+colorN]
		movq		mm2, mm0
		movq		mm3, mm1
		pcmpeqw		mm0, mm4
		pcmpeqw		mm1, mm4
		pcmpeqw		mm2, mm5
		pcmpeqw		mm3, mm5
		pand		mm0, mm6
		pand		mm1, mm6
		pand		mm2, mm6
		pand		mm3, mm6
		paddw		mm0, mm1
		paddw		mm2, mm3

		pxor		mm3, mm3
		pcmpgtw		mm0, mm6
		pcmpgtw		mm2, mm6
		pcmpeqw		mm0, mm3
		pcmpeqw		mm2, mm3
		pand		mm0, mm6
		pand		mm2, mm6
		paddw		mm7, mm0
		psubw		mm7, mm2

		movq		mm0, [esi+ebx+colorL]
		movq		mm1, [esi+ebx*2+colorO]
		movq		mm2, mm0
		movq		mm3, mm1
		pcmpeqw		mm0, mm4
		pcmpeqw		mm1, mm4
		pcmpeqw		mm2, mm5
		pcmpeqw		mm3, mm5
		pand		mm0, mm6
		pand		mm1, mm6
		pand		mm2, mm6
		pand		mm3, mm6
		paddw		mm0, mm1
		paddw		mm2, mm3

		pxor		mm3, mm3
		pcmpgtw		mm0, mm6
		pcmpgtw		mm2, mm6
		pcmpeqw		mm0, mm3
		pcmpeqw		mm2, mm3
		pand		mm0, mm6
		pand		mm2, mm6
		paddw		mm7, mm0
		psubw		mm7, mm2

		movq		mm1, mm7
		pxor		mm0, mm0
		pcmpgtw		mm7, mm0
		pcmpgtw		mm0, mm1

		por		mm7, Mask1
		por		mm0, Mask2
		movq		Mask1, mm7
		movq		Mask2, mm0

nx_2xSaILine_16mmx_skipguess:
		//------------------------------
		// interpolate A, B, C and D
		//------------------------------
		movq		mm0, [eax+ebx+colorA]
		movq		mm1, [eax+ebx+colorB]
		movq		mm4, mm0
		movq		mm2, [eax+ebx*2+colorC]
		movq		mm5, mm1
		movq		mm3, qMask			// qcolorMask
		movq		mm6, mm2
		movq		mm7, lMask			// qlowcolorMask

		pand		mm0, mm3
		pand		mm1, mm3
		pand		mm2, mm3
		pand		mm3, [eax+ebx*2+colorD]

		psrlw		mm0, 2
		pand		mm4, mm7
		psrlw		mm1, 2
		pand		mm5, mm7
		psrlw		mm2, 2
		pand		mm6, mm7
		psrlw		mm3, 2
		pand		mm7, [eax+ebx*2+colorD]

		paddw		mm0, mm1
		paddw		mm2, mm3

		paddw		mm4, mm5
		paddw		mm6, mm7

		paddw		mm4, mm6
		movq		mm7, lMask			// qlowcolorMask
		paddw		mm0, mm2
		psrlw		mm4, 2
		pand		mm4, mm7
		paddw		mm0, mm4			// mm0 contains the interpolated value of A, B, C and D

		// assemble the pixels
		movq		mm1, Mask1
		movq		mm2, Mask2
		movq		mm4, [eax+ebx+colorA]
		movq		mm5, [eax+ebx+colorB]
		pand		mm4, mm1
		pand		mm5, mm2

		pxor		mm7, mm7
		por		mm1, mm2
		por		mm4, mm5
		pcmpeqw		mm1, mm7
		pand		mm0, mm1
		por		mm4, mm0			// mm4 contains the diagonal pixels

		movq		mm0, ACPixel
		mov		edi, dstPitch
		movq		mm1, mm0
		punpcklwd	mm0, mm4
		punpckhwd	mm1, mm4

		//------------------------------
		// Write image
		//------------------------------
		movq		[edx+edi+0], mm0
		movq		[edx+edi+8], mm1

nx_2xSaILine_16mmx_skipprocess:
		add		pDlt, 8		// 4 pixels
		lea		eax, [eax+ 8]	// 4 pixels
		lea		edx, [edx+16]	// 8 pixels
		sub		width, 4	// 4 pixels
		jg		nx_2xSaILine_16mmx_loop

		emms
	}
}

static	void	nx_2xSaILine_32bpp_mmx( euI8* pSrc, euI8* pDlt, euI32 srcPitch, euI32 width, euI8* pDst, euI32 dstPitch, euI32 bForceWrite )
{
	__asm {
		mov		eax, pSrc
		mov		ebx, srcPitch
		mov		edx, pDst
		sub		eax, ebx
nx_2xSaILine_32mmx_loop:
		mov		ecx, bForceWrite
		test		ecx, ecx
		jz		nx_2xSaILine_32mmx_normal

		mov		esi, pDlt
		movq		mm6, [eax+colorI]
		movq		[esi+colorI], mm6

		jmp		nx_2xSaILine_32mmx_forcewrite
nx_2xSaILine_32mmx_normal:
		// Check delta
		mov		ecx, pDlt

		// load source img
		lea		esi, [eax+ebx]
		movq		mm0, [eax+colorI]
		movq		mm1, [eax+colorJ]
		movq		mm2, [eax+ebx+colorG]
		movq		mm3, [eax+ebx+colorK]
		movq		mm4, [eax+ebx*2+colorH]
		movq		mm5, [eax+ebx*2+colorL]
		movq		mm6, [esi+ebx*2+colorM]
		movq		mm7, [esi+ebx*2+colorP]

		// compare to delta
		lea		esi, [ecx+ebx]
		pcmpeqw		mm0, [ecx+colorI]
		pcmpeqw		mm1, [ecx+colorJ]
		pcmpeqw		mm2, [ecx+ebx+colorG]
		pcmpeqw		mm3, [ecx+ebx+colorK]
		pcmpeqw		mm4, [ecx+ebx*2+colorH]
		pcmpeqw		mm5, [ecx+ebx*2+colorL]
		pcmpeqw		mm6, [esi+ebx*2+colorM]
		pcmpeqw		mm7, [esi+ebx*2+colorP]

		// compose results
		pand		mm0, mm1
		pand		mm2, mm3
		pand		mm4, mm5
		pand		mm6, mm7
		pand		mm0, mm2
		pand		mm4, mm6
		pxor		mm7, mm7
		pand		mm0, mm4
		movq		mm6, [eax+colorI]
		pcmpeqw		mm7, mm0

		movq		[ecx+colorI], mm6

		packsswb	mm7, mm7
		movd		ecx, mm7
		test		ecx, ecx
		jz		nx_2xSaILine_32mmx_skipprocess
		// End Delta
nx_2xSaILine_32mmx_forcewrite:
		//------------------------------
		// 1
		// if ((colorA == colorD) && (colorB != colorC) && (colorA == colorE) && (colorB == colorL)
		movq		mm0, [eax+ebx+colorA]		// mm0 and mm1 contain colorA
		movq		mm2, [eax+ebx+colorB]		// mm2 and mm3 contain colorB

		movq		mm1, mm0
		movq		mm3, mm2

		pcmpeqw		mm0, [eax+ebx*2+colorD]
		pcmpeqw		mm1, [eax+colorE]
		pcmpeqw		mm2, [eax+ebx*2+colorL]
		pcmpeqw		mm3, [eax+ebx*2+colorC]

		pand		mm0, mm1
		pxor		mm1, mm1
		pand		mm0, mm2
		pcmpeqw		mm3, mm1
		pand		mm0, mm3			// result in mm0

		// if ((colorA == colorC) && (colorB != colorE) && (colorA == colorF) && (colorB == colorJ)
		movq		mm4, [eax+ebx+colorA]		// mm4 and mm5 contain colorA
		movq		mm6, [eax+ebx+colorB]		// mm6 and mm7 contain colorB
		movq		mm5, mm4
		movq		mm7, mm6

		pcmpeqw		mm4, [eax+ebx*2+colorC]
		pcmpeqw		mm5, [eax+colorF]
		pcmpeqw		mm6, [eax+colorJ]
		pcmpeqw		mm7, [eax+colorE]

		pand		mm4, mm5
		pxor		mm5, mm5
		pand		mm4, mm6
		pcmpeqw		mm7, mm5
		pand		mm4, mm7			// result in mm4

		por		mm0, mm4			// combine the masks
		movq		Mask1, mm0

		//------------------------------
		// 2
		// if ((colorB == colorC) && (colorA != colorD) && (colorB == colorF) && (colorA == colorH)
		movq		mm0, [eax+ebx+colorB]		// mm0 and mm1 contain colorB
		movq		mm2, [eax+ebx+colorA]		// mm2 and mm3 contain colorA
		movq		mm1, mm0
		movq		mm3, mm2

		pcmpeqw		mm0, [eax+ebx*2+colorC]
		pcmpeqw		mm1, [eax+colorF]
		pcmpeqw		mm2, [eax+ebx*2+colorH]
		pcmpeqw		mm3, [eax+ebx*2+colorD]

		pand		mm0, mm1
		pxor		mm1, mm1
		pand		mm0, mm2
		pcmpeqw		mm3, mm1
		pand		mm0, mm3			// result in mm0

		// if ((colorB == colorE) && (colorB == colorD) && (colorA != colorF) && (colorA == colorI)
		movq		mm4, [eax+ebx+colorB]		// mm4 and mm5 contain colorB
		movq		mm6, [eax+ebx+colorA]		// mm6 and mm7 contain colorA
		movq		mm5, mm4
		movq		mm7, mm6

		pcmpeqw		mm4, [eax+ebx*2+colorD]
		pcmpeqw		mm5, [eax+colorE]
		pcmpeqw		mm6, [eax+colorI]
		pcmpeqw		mm7, [eax+colorF]

		pand		mm4, mm5
		pxor		mm5, mm5
		pand		mm4, mm6
		pcmpeqw		mm7, mm5
		pand		mm4, mm7			// result in mm4

		por		mm0, mm4			// combine the masks
		movq		Mask2, mm0

		//------------------------------
		// interpolate colorA and colorB
		//------------------------------
		movq		mm0, [eax+ebx+colorA]
		movq		mm1, [eax+ebx+colorB]
		movq		mm2, mm0
		movq		mm3, mm1

		movq		mm6, cMask
		pxor		mm3, mm2
		pand		mm0, mm1
		pand		mm3, mm6
		psrlw		mm3, 1
		paddw		mm0, mm3			// mm0 contains the interpolated values

		// assemble the pixels
		movq		mm1, [eax+ebx+colorA]
		movq		mm2, [eax+ebx+colorB]

		movq		mm3, Mask1
		movq		mm5, mm1
		movq		mm4, Mask2
		movq		mm6, mm1

		pand		mm1, mm3
		por		mm3, mm4
		pxor		mm7, mm7
		pand		mm2, mm4

		pcmpeqw		mm3, mm7
		por		mm1, mm2
		pand		mm0, mm3

		por		mm0, mm1

		punpcklwd	mm5, mm0
		punpckhwd	mm6, mm0

		//------------------------------
		// Write image
		//------------------------------
		// save
		mov		esi, eax
		mov		edi, ebx
		mov		ecx, 0x00F8F8F8		// mask

//		movq		[edx+0], mm5

		movd		eax, mm5
		movd		ebx, mm5
		shl		eax, 3
		shl		ebx, 9
		shl		ah, 3
		and		ebx, ecx
		mov		bx, ax
		psrlq		mm5, 16
		mov		[edx+0], ebx
		movd		eax, mm5
		movd		ebx, mm5
		shl		eax, 3
		shl		ebx, 9
		shl		ah, 3
		and		ebx, ecx
		mov		bx, ax
		psrlq		mm5, 16
		mov		[edx+4], ebx
		movd		eax, mm5
		movd		ebx, mm5
		shl		eax, 3
		shl		ebx, 9
		shl		ah, 3
		and		ebx, ecx
		mov		bx, ax
		psrlq		mm5, 16
		mov		[edx+8], ebx
		movd		eax, mm5
		movd		ebx, mm5
		shl		eax, 3
		shl		ebx, 9
		shl		ah, 3
		and		ebx, ecx
		mov		bx, ax
		mov		[edx+12], ebx

//		movq		[edx+8], mm6

		movd		eax, mm6
		movd		ebx, mm6
		shl		eax, 3
		shl		ebx, 9
		shl		ah, 3
		and		ebx, ecx
		mov		bx, ax
		psrlq		mm6, 16
		mov		[edx+16], ebx
		movd		eax, mm6
		movd		ebx, mm6
		shl		eax, 3
		shl		ebx, 9
		shl		ah, 3
		and		ebx, ecx
		mov		bx, ax
		psrlq		mm6, 16
		mov		[edx+20], ebx
		movd		eax, mm6
		movd		ebx, mm6
		shl		eax, 3
		shl		ebx, 9
		shl		ah, 3
		and		ebx, ecx
		mov		bx, ax
		psrlq		mm6, 16
		mov		[edx+24], ebx
		movd		eax, mm6
		movd		ebx, mm6
		shl		eax, 3
		shl		ebx, 9
		shl		ah, 3
		and		ebx, ecx
		mov		bx, ax
		mov		[edx+28], ebx

		// restore
		mov		eax, esi
		mov		ebx, edi

		//------------------------------
		// Create the Nextline
		//------------------------------
		// 3
		// if ((colorA == colorD) && (colorB != colorC) && (colorA == colorG) && (colorC == colorO)
		lea		esi, [eax+ebx]

		movq		mm0, [eax+ebx+colorA]		// mm0 and mm1 contain colorA
		movq		mm2, [eax+ebx*2+colorC]		// mm2 and mm3 contain colorC
		movq		mm1, mm0
		movq		mm3, mm2

		pcmpeqw		mm0, [esi+ebx+colorD]
		pcmpeqw		mm1, [esi+colorG]
		pcmpeqw		mm2, [esi+ebx*2+colorO]
		pcmpeqw		mm3, [esi+colorB]

		pand		mm0, mm1
		pxor		mm1, mm1
		pand		mm0, mm2
		pcmpeqw		mm3, mm1
		pand		mm0, mm3			// result in mm0

		// if ((colorA == colorB) && (colorG != colorC) && (colorA == colorH) && (colorC == colorM)
		movq		mm4, [eax+ebx+colorA]		// mm4 and mm5 contain colorA
		movq		mm6, [eax+ebx*2+colorC]		// mm6 and mm7 contain colorC
		movq		mm5, mm4
		movq		mm7, mm6

		pcmpeqw		mm4, [esi+ebx+colorH]
		pcmpeqw		mm5, [esi+colorB]
		pcmpeqw		mm6, [esi+ebx*2+colorM]
		pcmpeqw		mm7, [esi+colorG]

		pand		mm4, mm5
		pxor		mm5, mm5
		pand		mm4, mm6
		pcmpeqw		mm7, mm5
		pand		mm4, mm7			// result in mm4

		por		mm0, mm4			// combine the masks
		movq		Mask1, mm0

		//------------------------------
		// 4
		// if ((colorB == colorC) && (colorA != colorD) && (colorC == colorH) && (colorA == colorF)
		movq		mm0, [eax+ebx*2+colorC]		// mm0 and mm1 contain colorC
		movq		mm2, [eax+ebx+colorA]		// mm2 and mm3 contain colorA
		movq		mm1, mm0
		movq		mm3, mm2

		pcmpeqw		mm0, [eax+ebx+colorB]
		pcmpeqw		mm1, [eax+ebx*2+colorH]
		pcmpeqw		mm2, [eax+colorF]
		pcmpeqw		mm3, [eax+ebx*2+colorD]

		pand		mm0, mm1
		pxor		mm1, mm1
		pand		mm0, mm2
		pcmpeqw		mm3, mm1
		pand		mm0, mm3			// result in mm0

		// if ((colorC == colorG) && (colorC == colorD) && (colorA != colorH) && (colorA == colorI)
		movq		mm4, [eax+ebx*2+colorC]		// mm4 and mm5 contain colorC
		movq		mm6, [eax+ebx+colorA]		// mm6 and mm7 contain colorA
		movq		mm5, mm4
		movq		mm7, mm6

		pcmpeqw		mm4, [eax+ebx*2+colorD]
		pcmpeqw		mm5, [eax+ebx+colorG]
		pcmpeqw		mm6, [eax+colorI]
		pcmpeqw		mm7, [eax+ebx*2+colorH]

		pand		mm4, mm5
		pxor		mm5, mm5
		pand		mm4, mm6
		pcmpeqw		mm7, mm5
		pand		mm4, mm7			// result in mm4

		por		mm0, mm4			;combine the masks
		movq		Mask2, mm0

		//------------------------------
		// interpolate colorA and colorC
		//------------------------------
		movq		mm0, [eax+ebx+colorA]
		movq		mm1, [eax+ebx*2+colorC]
		movq		mm2, mm0
		movq		mm3, mm1

		movq		mm6, cMask
		pxor		mm3, mm2
		pand		mm0, mm1
		pand		mm3, mm6
		psrlw		mm3, 1
		paddw		mm0, mm3			// mm0 contains the interpolated values

		// assemble the pixels
		movq		mm1, [eax+ebx+colorA]
		movq		mm2, [eax+ebx*2+colorC]

		movq		mm3, Mask1
		movq		mm4, Mask2

		pand		mm1, mm3
		pand		mm2, mm4

		por		mm3, mm4
		pxor		mm7, mm7
		por		mm1, mm2

		pcmpeqw		mm3, mm7
		pand		mm0, mm3
		por		mm0, mm1
		movq		ACPixel, mm0

		//------------------------------
		// Decide which "branch" to take
		//------------------------------
		movq		mm0, [eax+ebx+colorA]
		movq		mm1, [eax+ebx+colorB]
		movq		mm6, mm0
		movq		mm7, mm1
		pcmpeqw		mm0, [eax+ebx*2+colorD]
		pcmpeqw		mm1, [eax+ebx*2+colorC]
		pcmpeqw		mm6, mm7

		movq		mm2, mm0
		movq		mm3, mm0

		pand		mm0, mm1			// colorA == colorD && colorB == colorC
		pxor		mm7, mm7

		pcmpeqw		mm2, mm7
		pand		mm6, mm0
		pand		mm2, mm1			// colorA != colorD && colorB == colorC

		pcmpeqw		mm1, mm7

		pand		mm1, mm3			// colorA == colorD && colorB != colorC
		pxor		mm0, mm6
		por		mm1, mm6
		movq		mm7, mm0
		movq		Mask2, mm2
		packsswb	mm7, mm7
		movq		Mask1, mm1

		movd		ecx, mm7
		test		ecx, ecx
		jz		nx_2xSaILine_32mmx_skipguess

		//------------------------------
		// Map of the pixels: I|E F|J
		//                    G|A B|K
		//                    H|C D|L
		//                    M|N O|P
		//------------------------------
		movq		mm6, mm0
		movq		mm4, [eax+ebx+colorA]
		movq		mm5, [eax+ebx+colorB]
		pxor		mm7, mm7
		pand		mm6, ONE

		movq		mm0, [eax+colorE]
		movq		mm1, [eax+ebx+colorG]
		movq		mm2, mm0
		movq		mm3, mm1
		pcmpeqw		mm0, mm4
		pcmpeqw		mm1, mm4
		pcmpeqw		mm2, mm5
		pcmpeqw		mm3, mm5
		pand		mm0, mm6
		pand		mm1, mm6
		pand		mm2, mm6
		pand		mm3, mm6
		paddw		mm0, mm1
		paddw		mm2, mm3

		pxor		mm3, mm3
		pcmpgtw		mm0, mm6
		pcmpgtw		mm2, mm6
		pcmpeqw		mm0, mm3
		pcmpeqw		mm2, mm3
		pand		mm0, mm6
		pand		mm2, mm6
		paddw		mm7, mm0
		psubw		mm7, mm2

		movq		mm0, [eax+colorF]
		movq		mm1, [eax+ebx+colorK]
		movq		mm2, mm0
		movq		mm3, mm1
		pcmpeqw		mm0, mm4
		pcmpeqw		mm1, mm4
		pcmpeqw		mm2, mm5
		pcmpeqw		mm3, mm5
		pand		mm0, mm6
		pand		mm1, mm6
		pand		mm2, mm6
		pand		mm3, mm6
		paddw		mm0, mm1
		paddw		mm2, mm3

		lea		esi, [eax+ebx]

		pxor		mm3, mm3
		pcmpgtw		mm0, mm6
		pcmpgtw		mm2, mm6
		pcmpeqw		mm0, mm3
		pcmpeqw		mm2, mm3
		pand		mm0, mm6
		pand		mm2, mm6
		paddw		mm7, mm0
		psubw		mm7, mm2

		movq		mm0, [esi+ebx+colorH]
		movq		mm1, [esi+ebx*2+colorN]
		movq		mm2, mm0
		movq		mm3, mm1
		pcmpeqw		mm0, mm4
		pcmpeqw		mm1, mm4
		pcmpeqw		mm2, mm5
		pcmpeqw		mm3, mm5
		pand		mm0, mm6
		pand		mm1, mm6
		pand		mm2, mm6
		pand		mm3, mm6
		paddw		mm0, mm1
		paddw		mm2, mm3

		pxor		mm3, mm3
		pcmpgtw		mm0, mm6
		pcmpgtw		mm2, mm6
		pcmpeqw		mm0, mm3
		pcmpeqw		mm2, mm3
		pand		mm0, mm6
		pand		mm2, mm6
		paddw		mm7, mm0
		psubw		mm7, mm2

		movq		mm0, [esi+ebx+colorL]
		movq		mm1, [esi+ebx*2+colorO]
		movq		mm2, mm0
		movq		mm3, mm1
		pcmpeqw		mm0, mm4
		pcmpeqw		mm1, mm4
		pcmpeqw		mm2, mm5
		pcmpeqw		mm3, mm5
		pand		mm0, mm6
		pand		mm1, mm6
		pand		mm2, mm6
		pand		mm3, mm6
		paddw		mm0, mm1
		paddw		mm2, mm3

		pxor		mm3, mm3
		pcmpgtw		mm0, mm6
		pcmpgtw		mm2, mm6
		pcmpeqw		mm0, mm3
		pcmpeqw		mm2, mm3
		pand		mm0, mm6
		pand		mm2, mm6
		paddw		mm7, mm0
		psubw		mm7, mm2

		movq		mm1, mm7
		pxor		mm0, mm0
		pcmpgtw		mm7, mm0
		pcmpgtw		mm0, mm1

		por		mm7, Mask1
		por		mm0, Mask2
		movq		Mask1, mm7
		movq		Mask2, mm0

nx_2xSaILine_32mmx_skipguess:
		//------------------------------
		// interpolate A, B, C and D
		//------------------------------
		movq		mm0, [eax+ebx+colorA]
		movq		mm1, [eax+ebx+colorB]
		movq		mm4, mm0
		movq		mm2, [eax+ebx*2+colorC]
		movq		mm5, mm1
		movq		mm3, qMask			// qcolorMask
		movq		mm6, mm2
		movq		mm7, lMask			// qlowcolorMask

		pand		mm0, mm3
		pand		mm1, mm3
		pand		mm2, mm3
		pand		mm3, [eax+ebx*2+colorD]

		psrlw		mm0, 2
		pand		mm4, mm7
		psrlw		mm1, 2
		pand		mm5, mm7
		psrlw		mm2, 2
		pand		mm6, mm7
		psrlw		mm3, 2
		pand		mm7, [eax+ebx*2+colorD]

		paddw		mm0, mm1
		paddw		mm2, mm3

		paddw		mm4, mm5
		paddw		mm6, mm7

		paddw		mm4, mm6
		movq		mm7, lMask			// qlowcolorMask
		paddw		mm0, mm2
		psrlw		mm4, 2
		pand		mm4, mm7
		paddw		mm0, mm4			// mm0 contains the interpolated value of A, B, C and D

		// assemble the pixels
		movq		mm1, Mask1
		movq		mm2, Mask2
		movq		mm4, [eax+ebx+colorA]
		movq		mm5, [eax+ebx+colorB]
		pand		mm4, mm1
		pand		mm5, mm2

		pxor		mm7, mm7
		por		mm1, mm2
		por		mm4, mm5
		pcmpeqw		mm1, mm7
		pand		mm0, mm1
		por		mm4, mm0			// mm4 contains the diagonal pixels

		movq		mm0, ACPixel
		mov		edi, dstPitch
		movq		mm1, mm0
		punpcklwd	mm0, mm4
		punpckhwd	mm1, mm4

		//------------------------------
		// Write image  RGB1555->RGBx888
		//------------------------------
		// save
		movd		mm6, eax
		movd		mm7, ebx
		mov		ecx, 0x00F8F8F8		// mask

//		movq		[edx+edi+0], mm0
		movd		eax, mm0
		movd		ebx, mm0
		shl		eax, 3
		shl		ebx, 9
		shl		ah, 3
		and		ebx, ecx
		mov		bx, ax
		psrlq		mm0, 16
		mov		[edx+edi+0], ebx
		movd		eax, mm0
		movd		ebx, mm0
		shl		eax, 3
		shl		ebx, 9
		shl		ah, 3
		and		ebx, ecx
		mov		bx, ax
		psrlq		mm0, 16
		mov		[edx+edi+4], ebx
		movd		eax, mm0
		movd		ebx, mm0
		shl		eax, 3
		shl		ebx, 9
		shl		ah, 3
		and		ebx, ecx
		mov		bx, ax
		psrlq		mm0, 16
		mov		[edx+edi+8], ebx
		movd		eax, mm0
		movd		ebx, mm0
		shl		eax, 3
		shl		ebx, 9
		shl		ah, 3
		and		ebx, ecx
		mov		bx, ax
		mov		[edx+edi+12], ebx

//		movq		[edx+edi+8], mm1
		movd		eax, mm1
		movd		ebx, mm1
		shl		eax, 3
		shl		ebx, 9
		shl		ah, 3
		and		ebx, ecx
		mov		bx, ax
		psrlq		mm1, 16
		mov		[edx+edi+16], ebx
		movd		eax, mm1
		movd		ebx, mm1
		shl		eax, 3
		shl		ebx, 9
		shl		ah, 3
		and		ebx, ecx
		mov		bx, ax
		psrlq		mm1, 16
		mov		[edx+edi+20], ebx
		movd		eax, mm1
		movd		ebx, mm1
		shl		eax, 3
		shl		ebx, 9
		shl		ah, 3
		and		ebx, ecx
		mov		bx, ax
		psrlq		mm1, 16
		mov		[edx+edi+24], ebx
		movd		eax, mm1
		movd		ebx, mm1
		shl		eax, 3
		shl		ebx, 9
		shl		ah, 3
		and		ebx, ecx
		mov		bx, ax
		mov		[edx+edi+28], ebx

		// restore
		movd		eax, mm6
		movd		ebx, mm7

nx_2xSaILine_32mmx_skipprocess:
		add		pDlt, 8		// 4 pixels
		lea		eax, [eax+ 8]	// 4 pixels
		lea		edx, [edx+32]	// 8 pixels
		sub		width, 4	// 4 pixels
		jg		nx_2xSaILine_32mmx_loop

		emms
	}
}
