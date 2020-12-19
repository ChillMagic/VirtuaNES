/*----------------------------------------------------------------------*/
/*                                                                      */
/*      NES Mapeers                                                     */
/*                                                           Norix      */
/*                                               written     2000/02/05 */
/*                                               last modify ----/--/-- */
/*----------------------------------------------------------------------*/
/*--------------[ INCLUDE               ]-------------------------------*/
#include "../Nes.h"
#include "../MMU.h"

#include "Mapper.h"

/*--------------[ DEFINE                ]-------------------------------*/
/*--------------[ EXTERNAL PROGRAM      ]-------------------------------*/
/*--------------[ EXTERNAL WORK         ]-------------------------------*/
/*--------------[ WORK                  ]-------------------------------*/
/*--------------[ PROTOTYPE             ]-------------------------------*/
/*--------------[ CONST                 ]-------------------------------*/
/*--------------[ PROGRAM               ]-------------------------------*/

//////////////////////////////////////////////////////////////////////////
// Based class implement
//////////////////////////////////////////////////////////////////////////
Mapper::Mapper( NES* parent ) : nes(parent)
{
}

Mapper::~Mapper()
{
}

// $4100-$7FFF Lower Memory read
BYTE	Mapper::ReadLow( WORD addr )
{
	// $6000-$7FFF WRAM
	if( addr >= 0x6000 && addr <= 0x7FFF ) {
		return	nes->mmu.CPU_MEM_BANK[addr>>13][addr&0x1FFF];
	}

	return	(BYTE)(addr>>8);
}

// $4100-$7FFF Lower Memory write
void	Mapper::WriteLow( WORD addr, BYTE data )
{
	// $6000-$7FFF WRAM
	if( addr >= 0x6000 && addr <= 0x7FFF ) {
		nes->mmu.CPU_MEM_BANK[addr>>13][addr&0x1FFF] = data;
	}
}

