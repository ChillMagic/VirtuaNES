#include "CPUExecutor.hpp"

bool CPU::Executor::DoExec(BYTE opcode) {
	switch (opcode) {
	case 0x69: // ADC #$??
		MR_IM();
		ADC();
		ADD_CYCLE(2);
		break;
	case 0x65: // ADC $??
		MR_ZP();
		ADC();
		ADD_CYCLE(3);
		break;
	case 0x75: // ADC $??,X
		MR_ZX();
		ADC();
		ADD_CYCLE(4);
		break;
	case 0x6D: // ADC $????
		MR_AB();
		ADC();
		ADD_CYCLE(4);
		break;
	case 0x7D: // ADC $????,X
		MR_AX();
		ADC();
		CHECK_EA();
		ADD_CYCLE(4);
		break;
	case 0x79: // ADC $????,Y
		MR_AY();
		ADC();
		CHECK_EA();
		ADD_CYCLE(4);
		break;
	case 0x61: // ADC ($??,X)
		MR_IX();
		ADC();
		ADD_CYCLE(6);
		break;
	case 0x71: // ADC ($??),Y
		MR_IY();
		ADC();
		CHECK_EA();
		ADD_CYCLE(4);
		break;

	case 0xE9: // SBC #$??
		MR_IM();
		SBC();
		ADD_CYCLE(2);
		break;
	case 0xE5: // SBC $??
		MR_ZP();
		SBC();
		ADD_CYCLE(3);
		break;
	case 0xF5: // SBC $??,X
		MR_ZX();
		SBC();
		ADD_CYCLE(4);
		break;
	case 0xED: // SBC $????
		MR_AB();
		SBC();
		ADD_CYCLE(4);
		break;
	case 0xFD: // SBC $????,X
		MR_AX();
		SBC();
		CHECK_EA();
		ADD_CYCLE(4);
		break;
	case 0xF9: // SBC $????,Y
		MR_AY();
		SBC();
		CHECK_EA();
		ADD_CYCLE(4);
		break;
	case 0xE1: // SBC ($??,X)
		MR_IX();
		SBC();
		ADD_CYCLE(6);
		break;
	case 0xF1: // SBC ($??),Y
		MR_IY();
		SBC();
		CHECK_EA();
		ADD_CYCLE(5);
		break;

	case 0xC6: // DEC $??
		MR_ZP();
		DEC();
		MW_ZP();
		ADD_CYCLE(5);
		break;
	case 0xD6: // DEC $??,X
		MR_ZX();
		DEC();
		MW_ZP();
		ADD_CYCLE(6);
		break;
	case 0xCE: // DEC $????
		MR_AB();
		DEC();
		MW_EA();
		ADD_CYCLE(6);
		break;
	case 0xDE: // DEC $????,X
		MR_AX();
		DEC();
		MW_EA();
		ADD_CYCLE(7);
		break;

	case 0xCA: // DEX
		DEX();
		ADD_CYCLE(2);
		break;
	case 0x88: // DEY
		DEY();
		ADD_CYCLE(2);
		break;

	case 0xE6: // INC $??
		MR_ZP();
		INC();
		MW_ZP();
		ADD_CYCLE(5);
		break;
	case 0xF6: // INC $??,X
		MR_ZX();
		INC();
		MW_ZP();
		ADD_CYCLE(6);
		break;
	case 0xEE: // INC $????
		MR_AB();
		INC();
		MW_EA();
		ADD_CYCLE(6);
		break;
	case 0xFE: // INC $????,X
		MR_AX();
		INC();
		MW_EA();
		ADD_CYCLE(7);
		break;

	case 0xE8: // INX
		INX();
		ADD_CYCLE(2);
		break;
	case 0xC8: // INY
		INY();
		ADD_CYCLE(2);
		break;

	case 0x29: // AND #$??
		MR_IM();
		AND();
		ADD_CYCLE(2);
		break;
	case 0x25: // AND $??
		MR_ZP();
		AND();
		ADD_CYCLE(3);
		break;
	case 0x35: // AND $??,X
		MR_ZX();
		AND();
		ADD_CYCLE(4);
		break;
	case 0x2D: // AND $????
		MR_AB();
		AND();
		ADD_CYCLE(4);
		break;
	case 0x3D: // AND $????,X
		MR_AX();
		AND();
		CHECK_EA();
		ADD_CYCLE(4);
		break;
	case 0x39: // AND $????,Y
		MR_AY();
		AND();
		CHECK_EA();
		ADD_CYCLE(4);
		break;
	case 0x21: // AND ($??,X)
		MR_IX();
		AND();
		ADD_CYCLE(6);
		break;
	case 0x31: // AND ($??),Y
		MR_IY();
		AND();
		CHECK_EA();
		ADD_CYCLE(5);
		break;

	case 0x0A: // ASL A
		ASL_A();
		ADD_CYCLE(2);
		break;
	case 0x06: // ASL $??
		MR_ZP();
		ASL();
		MW_ZP();
		ADD_CYCLE(5);
		break;
	case 0x16: // ASL $??,X
		MR_ZX();
		ASL();
		MW_ZP();
		ADD_CYCLE(6);
		break;
	case 0x0E: // ASL $????
		MR_AB();
		ASL();
		MW_EA();
		ADD_CYCLE(6);
		break;
	case 0x1E: // ASL $????,X
		MR_AX();
		ASL();
		MW_EA();
		ADD_CYCLE(7);
		break;

	case 0x24: // BIT $??
		MR_ZP();
		BIT();
		ADD_CYCLE(3);
		break;
	case 0x2C: // BIT $????
		MR_AB();
		BIT();
		ADD_CYCLE(4);
		break;

	case 0x49: // EOR #$??
		MR_IM();
		EOR();
		ADD_CYCLE(2);
		break;
	case 0x45: // EOR $??
		MR_ZP();
		EOR();
		ADD_CYCLE(3);
		break;
	case 0x55: // EOR $??,X
		MR_ZX();
		EOR();
		ADD_CYCLE(4);
		break;
	case 0x4D: // EOR $????
		MR_AB();
		EOR();
		ADD_CYCLE(4);
		break;
	case 0x5D: // EOR $????,X
		MR_AX();
		EOR();
		CHECK_EA();
		ADD_CYCLE(4);
		break;
	case 0x59: // EOR $????,Y
		MR_AY();
		EOR();
		CHECK_EA();
		ADD_CYCLE(4);
		break;
	case 0x41: // EOR ($??,X)
		MR_IX();
		EOR();
		ADD_CYCLE(6);
		break;
	case 0x51: // EOR ($??),Y
		MR_IY();
		EOR();
		CHECK_EA();
		ADD_CYCLE(5);
		break;

	case 0x4A: // LSR A
		LSR_A();
		ADD_CYCLE(2);
		break;
	case 0x46: // LSR $??
		MR_ZP();
		LSR();
		MW_ZP();
		ADD_CYCLE(5);
		break;
	case 0x56: // LSR $??,X
		MR_ZX();
		LSR();
		MW_ZP();
		ADD_CYCLE(6);
		break;
	case 0x4E: // LSR $????
		MR_AB();
		LSR();
		MW_EA();
		ADD_CYCLE(6);
		break;
	case 0x5E: // LSR $????,X
		MR_AX();
		LSR();
		MW_EA();
		ADD_CYCLE(7);
		break;

	case 0x09: // ORA #$??
		MR_IM();
		ORA();
		ADD_CYCLE(2);
		break;
	case 0x05: // ORA $??
		MR_ZP();
		ORA();
		ADD_CYCLE(3);
		break;
	case 0x15: // ORA $??,X
		MR_ZX();
		ORA();
		ADD_CYCLE(4);
		break;
	case 0x0D: // ORA $????
		MR_AB();
		ORA();
		ADD_CYCLE(4);
		break;
	case 0x1D: // ORA $????,X
		MR_AX();
		ORA();
		CHECK_EA();
		ADD_CYCLE(4);
		break;
	case 0x19: // ORA $????,Y
		MR_AY();
		ORA();
		CHECK_EA();
		ADD_CYCLE(4);
		break;
	case 0x01: // ORA ($??,X)
		MR_IX();
		ORA();
		ADD_CYCLE(6);
		break;
	case 0x11: // ORA ($??),Y
		MR_IY();
		ORA();
		CHECK_EA();
		ADD_CYCLE(5);
		break;

	case 0x2A: // ROL A
		ROL_A();
		ADD_CYCLE(2);
		break;
	case 0x26: // ROL $??
		MR_ZP();
		ROL();
		MW_ZP();
		ADD_CYCLE(5);
		break;
	case 0x36: // ROL $??,X
		MR_ZX();
		ROL();
		MW_ZP();
		ADD_CYCLE(6);
		break;
	case 0x2E: // ROL $????
		MR_AB();
		ROL();
		MW_EA();
		ADD_CYCLE(6);
		break;
	case 0x3E: // ROL $????,X
		MR_AX();
		ROL();
		MW_EA();
		ADD_CYCLE(7);
		break;

	case 0x6A: // ROR A
		ROR_A();
		ADD_CYCLE(2);
		break;
	case 0x66: // ROR $??
		MR_ZP();
		ROR();
		MW_ZP();
		ADD_CYCLE(5);
		break;
	case 0x76: // ROR $??,X
		MR_ZX();
		ROR();
		MW_ZP();
		ADD_CYCLE(6);
		break;
	case 0x6E: // ROR $????
		MR_AB();
		ROR();
		MW_EA();
		ADD_CYCLE(6);
		break;
	case 0x7E: // ROR $????,X
		MR_AX();
		ROR();
		MW_EA();
		ADD_CYCLE(7);
		break;

	case 0xA9: // LDA #$??
		MR_IM();
		LDA();
		ADD_CYCLE(2);
		break;
	case 0xA5: // LDA $??
		MR_ZP();
		LDA();
		ADD_CYCLE(3);
		break;
	case 0xB5: // LDA $??,X
		MR_ZX();
		LDA();
		ADD_CYCLE(4);
		break;
	case 0xAD: // LDA $????
		MR_AB();
		LDA();
		ADD_CYCLE(4);
		break;
	case 0xBD: // LDA $????,X
		MR_AX();
		LDA();
		CHECK_EA();
		ADD_CYCLE(4);
		break;
	case 0xB9: // LDA $????,Y
		MR_AY();
		LDA();
		CHECK_EA();
		ADD_CYCLE(4);
		break;
	case 0xA1: // LDA ($??,X)
		MR_IX();
		LDA();
		ADD_CYCLE(6);
		break;
	case 0xB1: // LDA ($??),Y
		MR_IY();
		LDA();
		CHECK_EA();
		ADD_CYCLE(5);
		break;

	case 0xA2: // LDX #$??
		MR_IM();
		LDX();
		ADD_CYCLE(2);
		break;
	case 0xA6: // LDX $??
		MR_ZP();
		LDX();
		ADD_CYCLE(3);
		break;
	case 0xB6: // LDX $??,Y
		MR_ZY();
		LDX();
		ADD_CYCLE(4);
		break;
	case 0xAE: // LDX $????
		MR_AB();
		LDX();
		ADD_CYCLE(4);
		break;
	case 0xBE: // LDX $????,Y
		MR_AY();
		LDX();
		CHECK_EA();
		ADD_CYCLE(4);
		break;

	case 0xA0: // LDY #$??
		MR_IM();
		LDY();
		ADD_CYCLE(2);
		break;
	case 0xA4: // LDY $??
		MR_ZP();
		LDY();
		ADD_CYCLE(3);
		break;
	case 0xB4: // LDY $??,X
		MR_ZX();
		LDY();
		ADD_CYCLE(4);
		break;
	case 0xAC: // LDY $????
		MR_AB();
		LDY();
		ADD_CYCLE(4);
		break;
	case 0xBC: // LDY $????,X
		MR_AX();
		LDY();
		CHECK_EA();
		ADD_CYCLE(4);
		break;

	case 0x85: // STA $??
		EA_ZP();
		STA();
		MW_ZP();
		ADD_CYCLE(3);
		break;
	case 0x95: // STA $??,X
		EA_ZX();
		STA();
		MW_ZP();
		ADD_CYCLE(4);
		break;
	case 0x8D: // STA $????
		EA_AB();
		STA();
		MW_EA();
		ADD_CYCLE(4);
		break;
	case 0x9D: // STA $????,X
		EA_AX();
		STA();
		MW_EA();
		ADD_CYCLE(5);
		break;
	case 0x99: // STA $????,Y
		EA_AY();
		STA();
		MW_EA();
		ADD_CYCLE(5);
		break;
	case 0x81: // STA ($??,X)
		EA_IX();
		STA();
		MW_EA();
		ADD_CYCLE(6);
		break;
	case 0x91: // STA ($??),Y
		EA_IY();
		STA();
		MW_EA();
		ADD_CYCLE(6);
		break;

	case 0x86: // STX $??
		EA_ZP();
		STX();
		MW_ZP();
		ADD_CYCLE(3);
		break;
	case 0x96: // STX $??,Y
		EA_ZY();
		STX();
		MW_ZP();
		ADD_CYCLE(4);
		break;
	case 0x8E: // STX $????
		EA_AB();
		STX();
		MW_EA();
		ADD_CYCLE(4);
		break;

	case 0x84: // STY $??
		EA_ZP();
		STY();
		MW_ZP();
		ADD_CYCLE(3);
		break;
	case 0x94: // STY $??,X
		EA_ZX();
		STY();
		MW_ZP();
		ADD_CYCLE(4);
		break;
	case 0x8C: // STY $????
		EA_AB();
		STY();
		MW_EA();
		ADD_CYCLE(4);
		break;

	case 0xAA: // TAX
		TAX();
		ADD_CYCLE(2);
		break;
	case 0x8A: // TXA
		TXA();
		ADD_CYCLE(2);
		break;
	case 0xA8: // TAY
		TAY();
		ADD_CYCLE(2);
		break;
	case 0x98: // TYA
		TYA();
		ADD_CYCLE(2);
		break;
	case 0xBA: // TSX
		TSX();
		ADD_CYCLE(2);
		break;
	case 0x9A: // TXS
		TXS();
		ADD_CYCLE(2);
		break;

	case 0xC9: // CMP #$??
		MR_IM();
		CMP_();
		ADD_CYCLE(2);
		break;
	case 0xC5: // CMP $??
		MR_ZP();
		CMP_();
		ADD_CYCLE(3);
		break;
	case 0xD5: // CMP $??,X
		MR_ZX();
		CMP_();
		ADD_CYCLE(4);
		break;
	case 0xCD: // CMP $????
		MR_AB();
		CMP_();
		ADD_CYCLE(4);
		break;
	case 0xDD: // CMP $????,X
		MR_AX();
		CMP_();
		CHECK_EA();
		ADD_CYCLE(4);
		break;
	case 0xD9: // CMP $????,Y
		MR_AY();
		CMP_();
		CHECK_EA();
		ADD_CYCLE(4);
		break;
	case 0xC1: // CMP ($??,X)
		MR_IX();
		CMP_();
		ADD_CYCLE(6);
		break;
	case 0xD1: // CMP ($??),Y
		MR_IY();
		CMP_();
		CHECK_EA();
		ADD_CYCLE(5);
		break;

	case 0xE0: // CPX #$??
		MR_IM();
		CPX();
		ADD_CYCLE(2);
		break;
	case 0xE4: // CPX $??
		MR_ZP();
		CPX();
		ADD_CYCLE(3);
		break;
	case 0xEC: // CPX $????
		MR_AB();
		CPX();
		ADD_CYCLE(4);
		break;

	case 0xC0: // CPY #$??
		MR_IM();
		CPY();
		ADD_CYCLE(2);
		break;
	case 0xC4: // CPY $??
		MR_ZP();
		CPY();
		ADD_CYCLE(3);
		break;
	case 0xCC: // CPY $????
		MR_AB();
		CPY();
		ADD_CYCLE(4);
		break;

	case 0x90: // BCC
		MR_IM();
		BCC();
		ADD_CYCLE(2);
		break;
	case 0xB0: // BCS
		MR_IM();
		BCS();
		ADD_CYCLE(2);
		break;
	case 0xF0: // BEQ
		MR_IM();
		BEQ();
		ADD_CYCLE(2);
		break;
	case 0x30: // BMI
		MR_IM();
		BMI();
		ADD_CYCLE(2);
		break;
	case 0xD0: // BNE
		MR_IM();
		BNE();
		ADD_CYCLE(2);
		break;
	case 0x10: // BPL
		MR_IM();
		BPL();
		ADD_CYCLE(2);
		break;
	case 0x50: // BVC
		MR_IM();
		BVC();
		ADD_CYCLE(2);
		break;
	case 0x70: // BVS
		MR_IM();
		BVS();
		ADD_CYCLE(2);
		break;

	case 0x4C: // JMP $????
		JMP();
		ADD_CYCLE(3);
		break;
	case 0x6C: // JMP ($????)
		JMP_ID();
		ADD_CYCLE(5);
		break;

	case 0x20: // JSR
		JSR();
		ADD_CYCLE(6);
		break;

	case 0x40: // RTI
		RTI();
		ADD_CYCLE(6);
		break;
	case 0x60: // RTS
		RTS();
		ADD_CYCLE(6);
		break;

		// フラグ制御系
	case 0x18: // CLC
		CLC();
		ADD_CYCLE(2);
		break;
	case 0xD8: // CLD
		CLD();
		ADD_CYCLE(2);
		break;
	case 0x58: // CLI
		CLI();
		ADD_CYCLE(2);
		break;
	case 0xB8: // CLV
		CLV();
		ADD_CYCLE(2);
		break;

	case 0x38: // SEC
		SEC();
		ADD_CYCLE(2);
		break;
	case 0xF8: // SED
		SED();
		ADD_CYCLE(2);
		break;
	case 0x78: // SEI
		SEI();
		ADD_CYCLE(2);
		break;

		// スタック系
	case 0x48: // PHA
		PHA();
		ADD_CYCLE(3);
		break;
	case 0x08: // PHP
		PHP();
		ADD_CYCLE(3);
		break;
	case 0x68: // PLA (N-----Z-)
		PLA();
		ADD_CYCLE(4);
		break;
	case 0x28: // PLP
		PLP();
		ADD_CYCLE(4);
		break;

		// その他
	case 0x00: // BRK
		BRK();
		ADD_CYCLE(7);
		break;

	case 0xEA: // NOP
		ADD_CYCLE(2);
		break;

		// 未公開命令群
	case 0x0B: // ANC #$??
	case 0x2B: // ANC #$??
		MR_IM();
		ANC();
		ADD_CYCLE(2);
		break;

	case 0x8B: // ANE #$??
		MR_IM();
		ANE();
		ADD_CYCLE(2);
		break;

	case 0x6B: // ARR #$??
		MR_IM();
		ARR();
		ADD_CYCLE(2);
		break;

	case 0x4B: // ASR #$??
		MR_IM();
		ASR();
		ADD_CYCLE(2);
		break;

	case 0xC7: // DCP $??
		MR_ZP();
		DCP();
		MW_ZP();
		ADD_CYCLE(5);
		break;
	case 0xD7: // DCP $??,X
		MR_ZX();
		DCP();
		MW_ZP();
		ADD_CYCLE(6);
		break;
	case 0xCF: // DCP $????
		MR_AB();
		DCP();
		MW_EA();
		ADD_CYCLE(6);
		break;
	case 0xDF: // DCP $????,X
		MR_AX();
		DCP();
		MW_EA();
		ADD_CYCLE(7);
		break;
	case 0xDB: // DCP $????,Y
		MR_AY();
		DCP();
		MW_EA();
		ADD_CYCLE(7);
		break;
	case 0xC3: // DCP ($??,X)
		MR_IX();
		DCP();
		MW_EA();
		ADD_CYCLE(8);
		break;
	case 0xD3: // DCP ($??),Y
		MR_IY();
		DCP();
		MW_EA();
		ADD_CYCLE(8);
		break;

	case 0xE7: // ISB $??
		MR_ZP();
		ISB();
		MW_ZP();
		ADD_CYCLE(5);
		break;
	case 0xF7: // ISB $??,X
		MR_ZX();
		ISB();
		MW_ZP();
		ADD_CYCLE(5);
		break;
	case 0xEF: // ISB $????
		MR_AB();
		ISB();
		MW_EA();
		ADD_CYCLE(5);
		break;
	case 0xFF: // ISB $????,X
		MR_AX();
		ISB();
		MW_EA();
		ADD_CYCLE(5);
		break;
	case 0xFB: // ISB $????,Y
		MR_AY();
		ISB();
		MW_EA();
		ADD_CYCLE(5);
		break;
	case 0xE3: // ISB ($??,X)
		MR_IX();
		ISB();
		MW_EA();
		ADD_CYCLE(5);
		break;
	case 0xF3: // ISB ($??),Y
		MR_IY();
		ISB();
		MW_EA();
		ADD_CYCLE(5);
		break;

	case 0xBB: // LAS $????,Y
		MR_AY();
		LAS();
		CHECK_EA();
		ADD_CYCLE(4);
		break;


	case 0xA7: // LAX $??
		MR_ZP();
		LAX();
		ADD_CYCLE(3);
		break;
	case 0xB7: // LAX $??,Y
		MR_ZY();
		LAX();
		ADD_CYCLE(4);
		break;
	case 0xAF: // LAX $????
		MR_AB();
		LAX();
		ADD_CYCLE(4);
		break;
	case 0xBF: // LAX $????,Y
		MR_AY();
		LAX();
		CHECK_EA();
		ADD_CYCLE(4);
		break;
	case 0xA3: // LAX ($??,X)
		MR_IX();
		LAX();
		ADD_CYCLE(6);
		break;
	case 0xB3: // LAX ($??),Y
		MR_IY();
		LAX();
		CHECK_EA();
		ADD_CYCLE(5);
		break;

	case 0xAB: // LXA #$??
		MR_IM();
		LXA();
		ADD_CYCLE(2);
		break;

	case 0x27: // RLA $??
		MR_ZP();
		RLA();
		MW_ZP();
		ADD_CYCLE(5);
		break;
	case 0x37: // RLA $??,X
		MR_ZX();
		RLA();
		MW_ZP();
		ADD_CYCLE(6);
		break;
	case 0x2F: // RLA $????
		MR_AB();
		RLA();
		MW_EA();
		ADD_CYCLE(6);
		break;
	case 0x3F: // RLA $????,X
		MR_AX();
		RLA();
		MW_EA();
		ADD_CYCLE(7);
		break;
	case 0x3B: // RLA $????,Y
		MR_AY();
		RLA();
		MW_EA();
		ADD_CYCLE(7);
		break;
	case 0x23: // RLA ($??,X)
		MR_IX();
		RLA();
		MW_EA();
		ADD_CYCLE(8);
		break;
	case 0x33: // RLA ($??),Y
		MR_IY();
		RLA();
		MW_EA();
		ADD_CYCLE(8);
		break;

	case 0x67: // RRA $??
		MR_ZP();
		RRA();
		MW_ZP();
		ADD_CYCLE(5);
		break;
	case 0x77: // RRA $??,X
		MR_ZX();
		RRA();
		MW_ZP();
		ADD_CYCLE(6);
		break;
	case 0x6F: // RRA $????
		MR_AB();
		RRA();
		MW_EA();
		ADD_CYCLE(6);
		break;
	case 0x7F: // RRA $????,X
		MR_AX();
		RRA();
		MW_EA();
		ADD_CYCLE(7);
		break;
	case 0x7B: // RRA $????,Y
		MR_AY();
		RRA();
		MW_EA();
		ADD_CYCLE(7);
		break;
	case 0x63: // RRA ($??,X)
		MR_IX();
		RRA();
		MW_EA();
		ADD_CYCLE(8);
		break;
	case 0x73: // RRA ($??),Y
		MR_IY();
		RRA();
		MW_EA();
		ADD_CYCLE(8);
		break;

	case 0x87: // SAX $??
		MR_ZP();
		SAX();
		MW_ZP();
		ADD_CYCLE(3);
		break;
	case 0x97: // SAX $??,Y
		MR_ZY();
		SAX();
		MW_ZP();
		ADD_CYCLE(4);
		break;
	case 0x8F: // SAX $????
		MR_AB();
		SAX();
		MW_EA();
		ADD_CYCLE(4);
		break;
	case 0x83: // SAX ($??,X)
		MR_IX();
		SAX();
		MW_EA();
		ADD_CYCLE(6);
		break;

	case 0xCB: // SBX #$??
		MR_IM();
		SBX();
		ADD_CYCLE(2);
		break;

	case 0x9F: // SHA $????,Y
		MR_AY();
		SHA();
		MW_EA();
		ADD_CYCLE(5);
		break;
	case 0x93: // SHA ($??),Y
		MR_IY();
		SHA();
		MW_EA();
		ADD_CYCLE(6);
		break;

	case 0x9B: // SHS $????,Y
		MR_AY();
		SHS();
		MW_EA();
		ADD_CYCLE(5);
		break;

	case 0x9E: // SHX $????,Y
		MR_AY();
		SHX();
		MW_EA();
		ADD_CYCLE(5);
		break;

	case 0x9C: // SHY $????,X
		MR_AX();
		SHY();
		MW_EA();
		ADD_CYCLE(5);
		break;

	case 0x07: // SLO $??
		MR_ZP();
		SLO();
		MW_ZP();
		ADD_CYCLE(5);
		break;
	case 0x17: // SLO $??,X
		MR_ZX();
		SLO();
		MW_ZP();
		ADD_CYCLE(6);
		break;
	case 0x0F: // SLO $????
		MR_AB();
		SLO();
		MW_EA();
		ADD_CYCLE(6);
		break;
	case 0x1F: // SLO $????,X
		MR_AX();
		SLO();
		MW_EA();
		ADD_CYCLE(7);
		break;
	case 0x1B: // SLO $????,Y
		MR_AY();
		SLO();
		MW_EA();
		ADD_CYCLE(7);
		break;
	case 0x03: // SLO ($??,X)
		MR_IX();
		SLO();
		MW_EA();
		ADD_CYCLE(8);
		break;
	case 0x13: // SLO ($??),Y
		MR_IY();
		SLO();
		MW_EA();
		ADD_CYCLE(8);
		break;

	case 0x47: // SRE $??
		MR_ZP();
		SRE();
		MW_ZP();
		ADD_CYCLE(5);
		break;
	case 0x57: // SRE $??,X
		MR_ZX();
		SRE();
		MW_ZP();
		ADD_CYCLE(6);
		break;
	case 0x4F: // SRE $????
		MR_AB();
		SRE();
		MW_EA();
		ADD_CYCLE(6);
		break;
	case 0x5F: // SRE $????,X
		MR_AX();
		SRE();
		MW_EA();
		ADD_CYCLE(7);
		break;
	case 0x5B: // SRE $????,Y
		MR_AY();
		SRE();
		MW_EA();
		ADD_CYCLE(7);
		break;
	case 0x43: // SRE ($??,X)
		MR_IX();
		SRE();
		MW_EA();
		ADD_CYCLE(8);
		break;
	case 0x53: // SRE ($??),Y
		MR_IY();
		SRE();
		MW_EA();
		ADD_CYCLE(8);
		break;

	case 0xEB: // SBC #$?? (Unofficial)
		MR_IM();
		SBC();
		ADD_CYCLE(2);
		break;

	case 0x1A: // NOP (Unofficial)
	case 0x3A: // NOP (Unofficial)
	case 0x5A: // NOP (Unofficial)
	case 0x7A: // NOP (Unofficial)
	case 0xDA: // NOP (Unofficial)
	case 0xFA: // NOP (Unofficial)
		ADD_CYCLE(2);
		break;
	case 0x80: // DOP (CYCLES 2)
	case 0x82: // DOP (CYCLES 2)
	case 0x89: // DOP (CYCLES 2)
	case 0xC2: // DOP (CYCLES 2)
	case 0xE2: // DOP (CYCLES 2)
		DOP();
		ADD_CYCLE(2);
		break;
	case 0x04: // DOP (CYCLES 3)
	case 0x44: // DOP (CYCLES 3)
	case 0x64: // DOP (CYCLES 3)
		DOP();
		ADD_CYCLE(3);
		break;
	case 0x14: // DOP (CYCLES 4)
	case 0x34: // DOP (CYCLES 4)
	case 0x54: // DOP (CYCLES 4)
	case 0x74: // DOP (CYCLES 4)
	case 0xD4: // DOP (CYCLES 4)
	case 0xF4: // DOP (CYCLES 4)
		DOP();
		ADD_CYCLE(4);
		break;
	case 0x0C: // TOP
	case 0x1C: // TOP
	case 0x3C: // TOP
	case 0x5C: // TOP
	case 0x7C: // TOP
	case 0xDC: // TOP
	case 0xFC: // TOP
		TOP();
		ADD_CYCLE(4);
		break;

	case 0x02: /* JAM */
	case 0x12: /* JAM */
	case 0x22: /* JAM */
	case 0x32: /* JAM */
	case 0x42: /* JAM */
	case 0x52: /* JAM */
	case 0x62: /* JAM */
	case 0x72: /* JAM */
	case 0x92: /* JAM */
	case 0xB2: /* JAM */
	case 0xD2: /* JAM */
	case 0xF2: /* JAM */
	default:
		return false;
		//default: __assume(0);
	}
	return true;
}
