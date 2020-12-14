#include "CPUExecutor.hpp"

static CPU::Executor::OpcodeDataType GetOpcodeDataBase();

static const CPU::Executor::OpcodeDataType& GetOpcodeData() {
	static CPU::Executor::OpcodeDataType data = GetOpcodeDataBase();
	return data;
}

bool CPU::Executor::DoExec(BYTE opcode) {
	const OpCode& r = GetOpcodeData()[opcode];
	if (r.cycle == 0) {
		return false;
	}
	for (auto f : r.funcs) {
		if (f == nullptr) {
			break;
		}
		(this->*f)();
	}
	ADD_CYCLE(r.cycle);
	return true;
}

static CPU::Executor::OpcodeDataType GetOpcodeDataBase() {
	CPU::Executor::OpcodeDataType data = {};
	using OpCode = CPU::Executor::OpCode;
	using Executor = CPU::Executor;

	data[0x69] = // ADC #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::ADC,
		}, 2);
	data[0x65] = // ADC $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::ADC,
		}, 3);
	data[0x75] = // ADC $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::ADC,
		}, 4);
	data[0x6D] = // ADC $????
		OpCode({
			&Executor::MR_AB,
			&Executor::ADC,
		}, 4);
	data[0x7D] = // ADC $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::ADC,
			&Executor::CHECK_EA,
		}, 4);
	data[0x79] = // ADC $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::ADC,
			&Executor::CHECK_EA,
		}, 4);
	data[0x61] = // ADC ($??,X)
		OpCode({
			&Executor::MR_IX,
			&Executor::ADC,
		}, 6);
	data[0x71] = // ADC ($??),Y
		OpCode({
			&Executor::MR_IY,
			&Executor::ADC,
			&Executor::CHECK_EA,
		}, 4);

	data[0xE9] = // SBC #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::SBC,
		}, 2);
	data[0xE5] = // SBC $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::SBC,
		}, 3);
	data[0xF5] = // SBC $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::SBC,
		}, 4);
	data[0xED] = // SBC $????
		OpCode({
			&Executor::MR_AB,
			&Executor::SBC,
		}, 4);
	data[0xFD] = // SBC $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::SBC,
			&Executor::CHECK_EA,
		}, 4);
	data[0xF9] = // SBC $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::SBC,
			&Executor::CHECK_EA,
		}, 4);
	data[0xE1] = // SBC ($??,X)
		OpCode({
			&Executor::MR_IX,
			&Executor::SBC,
		}, 6);
	data[0xF1] = // SBC ($??),Y
		OpCode({
			&Executor::MR_IY,
			&Executor::SBC,
			&Executor::CHECK_EA,
		}, 5);

	data[0xC6] = // DEC $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::DEC,
			&Executor::MW_ZP,
		}, 5);
	data[0xD6] = // DEC $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::DEC,
			&Executor::MW_ZP,
		}, 6);
	data[0xCE] = // DEC $????
		OpCode({
			&Executor::MR_AB,
			&Executor::DEC,
			&Executor::MW_EA,
		}, 6);
	data[0xDE] = // DEC $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::DEC,
			&Executor::MW_EA,
		}, 7);

	data[0xCA] = // DEX
		OpCode({
			&Executor::DEX,
		}, 2);
	data[0x88] = // DEY
		OpCode({
			&Executor::DEY,
		}, 2);

	data[0xE6] = // INC $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::INC,
			&Executor::MW_ZP,
		}, 5);
	data[0xF6] = // INC $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::INC,
			&Executor::MW_ZP,
		}, 6);
	data[0xEE] = // INC $????
		OpCode({
			&Executor::MR_AB,
			&Executor::INC,
			&Executor::MW_EA,
		}, 6);
	data[0xFE] = // INC $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::INC,
			&Executor::MW_EA,
		}, 7);

	data[0xE8] = // INX
		OpCode({
			&Executor::INX,
		}, 2);
	data[0xC8] = // INY
		OpCode({
			&Executor::INY,
		}, 2);

	data[0x29] = // AND #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::AND,
		}, 2);
	data[0x25] = // AND $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::AND,
		}, 3);
	data[0x35] = // AND $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::AND,
		}, 4);
	data[0x2D] = // AND $????
		OpCode({
			&Executor::MR_AB,
			&Executor::AND,
		}, 4);
	data[0x3D] = // AND $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::AND,
			&Executor::CHECK_EA,
		}, 4);
	data[0x39] = // AND $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::AND,
			&Executor::CHECK_EA,
		}, 4);
	data[0x21] = // AND ($??,X)
		OpCode({
			&Executor::MR_IX,
			&Executor::AND,
		}, 6);
	data[0x31] = // AND ($??),Y
		OpCode({
			&Executor::MR_IY,
			&Executor::AND,
			&Executor::CHECK_EA,
		}, 5);

	data[0x0A] = // ASL A
		OpCode({
			&Executor::ASL_A,
		}, 2);
	data[0x06] = // ASL $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::ASL,
			&Executor::MW_ZP,
		}, 5);
	data[0x16] = // ASL $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::ASL,
			&Executor::MW_ZP,
		}, 6);
	data[0x0E] = // ASL $????
		OpCode({
			&Executor::MR_AB,
			&Executor::ASL,
			&Executor::MW_EA,
		}, 6);
	data[0x1E] = // ASL $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::ASL,
			&Executor::MW_EA,
		}, 7);

	data[0x24] = // BIT $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::BIT,
		}, 3);
	data[0x2C] = // BIT $????
		OpCode({
			&Executor::MR_AB,
			&Executor::BIT,
		}, 4);

	data[0x49] = // EOR #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::EOR,
		}, 2);
	data[0x45] = // EOR $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::EOR,
		}, 3);
	data[0x55] = // EOR $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::EOR,
		}, 4);
	data[0x4D] = // EOR $????
		OpCode({
			&Executor::MR_AB,
			&Executor::EOR,
		}, 4);
	data[0x5D] = // EOR $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::EOR,
			&Executor::CHECK_EA,
		}, 4);
	data[0x59] = // EOR $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::EOR,
			&Executor::CHECK_EA,
		}, 4);
	data[0x41] = // EOR ($??,X)
		OpCode({
			&Executor::MR_IX,
			&Executor::EOR,
		}, 6);
	data[0x51] = // EOR ($??),Y
		OpCode({
			&Executor::MR_IY,
			&Executor::EOR,
			&Executor::CHECK_EA,
		}, 5);

	data[0x4A] = // LSR A
		OpCode({
			&Executor::LSR_A,
		}, 2);
	data[0x46] = // LSR $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::LSR,
			&Executor::MW_ZP,
		}, 5);
	data[0x56] = // LSR $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::LSR,
			&Executor::MW_ZP,
		}, 6);
	data[0x4E] = // LSR $????
		OpCode({
			&Executor::MR_AB,
			&Executor::LSR,
			&Executor::MW_EA,
		}, 6);
	data[0x5E] = // LSR $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::LSR,
			&Executor::MW_EA,
		}, 7);

	data[0x09] = // ORA #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::ORA,
		}, 2);
	data[0x05] = // ORA $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::ORA,
		}, 3);
	data[0x15] = // ORA $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::ORA,
		}, 4);
	data[0x0D] = // ORA $????
		OpCode({
			&Executor::MR_AB,
			&Executor::ORA,
		}, 4);
	data[0x1D] = // ORA $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::ORA,
			&Executor::CHECK_EA,
		}, 4);
	data[0x19] = // ORA $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::ORA,
			&Executor::CHECK_EA,
		}, 4);
	data[0x01] = // ORA ($??,X)
		OpCode({
			&Executor::MR_IX,
			&Executor::ORA,
		}, 6);
	data[0x11] = // ORA ($??),Y
		OpCode({
			&Executor::MR_IY,
			&Executor::ORA,
			&Executor::CHECK_EA,
		}, 5);

	data[0x2A] = // ROL A
		OpCode({
			&Executor::ROL_A,
		}, 2);
	data[0x26] = // ROL $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::ROL,
			&Executor::MW_ZP,
		}, 5);
	data[0x36] = // ROL $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::ROL,
			&Executor::MW_ZP,
		}, 6);
	data[0x2E] = // ROL $????
		OpCode({
			&Executor::MR_AB,
			&Executor::ROL,
			&Executor::MW_EA,
		}, 6);
	data[0x3E] = // ROL $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::ROL,
			&Executor::MW_EA,
		}, 7);

	data[0x6A] = // ROR A
		OpCode({
			&Executor::ROR_A,
		}, 2);
	data[0x66] = // ROR $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::ROR,
			&Executor::MW_ZP,
		}, 5);
	data[0x76] = // ROR $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::ROR,
			&Executor::MW_ZP,
		}, 6);
	data[0x6E] = // ROR $????
		OpCode({
			&Executor::MR_AB,
			&Executor::ROR,
			&Executor::MW_EA,
		}, 6);
	data[0x7E] = // ROR $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::ROR,
			&Executor::MW_EA,
		}, 7);

	data[0xA9] = // LDA #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::LDA,
		}, 2);
	data[0xA5] = // LDA $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::LDA,
		}, 3);
	data[0xB5] = // LDA $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::LDA,
		}, 4);
	data[0xAD] = // LDA $????
		OpCode({
			&Executor::MR_AB,
			&Executor::LDA,
		}, 4);
	data[0xBD] = // LDA $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::LDA,
			&Executor::CHECK_EA,
		}, 4);
	data[0xB9] = // LDA $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::LDA,
			&Executor::CHECK_EA,
		}, 4);
	data[0xA1] = // LDA ($??,X)
		OpCode({
			&Executor::MR_IX,
			&Executor::LDA,
		}, 6);
	data[0xB1] = // LDA ($??),Y
		OpCode({
			&Executor::MR_IY,
			&Executor::LDA,
			&Executor::CHECK_EA,
		}, 5);

	data[0xA2] = // LDX #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::LDX,
		}, 2);
	data[0xA6] = // LDX $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::LDX,
		}, 3);
	data[0xB6] = // LDX $??,Y
		OpCode({
			&Executor::MR_ZY,
			&Executor::LDX,
		}, 4);
	data[0xAE] = // LDX $????
		OpCode({
			&Executor::MR_AB,
			&Executor::LDX,
		}, 4);
	data[0xBE] = // LDX $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::LDX,
			&Executor::CHECK_EA,
		}, 4);

	data[0xA0] = // LDY #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::LDY,
		}, 2);
	data[0xA4] = // LDY $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::LDY,
		}, 3);
	data[0xB4] = // LDY $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::LDY,
		}, 4);
	data[0xAC] = // LDY $????
		OpCode({
			&Executor::MR_AB,
			&Executor::LDY,
		}, 4);
	data[0xBC] = // LDY $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::LDY,
			&Executor::CHECK_EA,
		}, 4);

	data[0x85] = // STA $??
		OpCode({
			&Executor::EA_ZP,
			&Executor::STA,
			&Executor::MW_ZP,
		}, 3);
	data[0x95] = // STA $??,X
		OpCode({
			&Executor::EA_ZX,
			&Executor::STA,
			&Executor::MW_ZP,
		}, 4);
	data[0x8D] = // STA $????
		OpCode({
			&Executor::EA_AB,
			&Executor::STA,
			&Executor::MW_EA,
		}, 4);
	data[0x9D] = // STA $????,X
		OpCode({
			&Executor::EA_AX,
			&Executor::STA,
			&Executor::MW_EA,
		}, 5);
	data[0x99] = // STA $????,Y
		OpCode({
			&Executor::EA_AY,
			&Executor::STA,
			&Executor::MW_EA,
		}, 5);
	data[0x81] = // STA ($??,X)
		OpCode({
			&Executor::EA_IX,
			&Executor::STA,
			&Executor::MW_EA,
		}, 6);
	data[0x91] = // STA ($??),Y
		OpCode({
			&Executor::EA_IY,
			&Executor::STA,
			&Executor::MW_EA,
		}, 6);

	data[0x86] = // STX $??
		OpCode({
			&Executor::EA_ZP,
			&Executor::STX,
			&Executor::MW_ZP,
		}, 3);
	data[0x96] = // STX $??,Y
		OpCode({
			&Executor::EA_ZY,
			&Executor::STX,
			&Executor::MW_ZP,
		}, 4);
	data[0x8E] = // STX $????
		OpCode({
			&Executor::EA_AB,
			&Executor::STX,
			&Executor::MW_EA,
		}, 4);

	data[0x84] = // STY $??
		OpCode({
			&Executor::EA_ZP,
			&Executor::STY,
			&Executor::MW_ZP,
		}, 3);
	data[0x94] = // STY $??,X
		OpCode({
			&Executor::EA_ZX,
			&Executor::STY,
			&Executor::MW_ZP,
		}, 4);
	data[0x8C] = // STY $????
		OpCode({
			&Executor::EA_AB,
			&Executor::STY,
			&Executor::MW_EA,
		}, 4);

	data[0xAA] = // TAX
		OpCode({
			&Executor::TAX,
		}, 2);
	data[0x8A] = // TXA
		OpCode({
			&Executor::TXA,
		}, 2);
	data[0xA8] = // TAY
		OpCode({
			&Executor::TAY,
		}, 2);
	data[0x98] = // TYA
		OpCode({
			&Executor::TYA,
		}, 2);
	data[0xBA] = // TSX
		OpCode({
			&Executor::TSX,
		}, 2);
	data[0x9A] = // TXS
		OpCode({
			&Executor::TXS,
		}, 2);

	data[0xC9] = // CMP #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::CMP_,
		}, 2);
	data[0xC5] = // CMP $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::CMP_,
		}, 3);
	data[0xD5] = // CMP $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::CMP_,
		}, 4);
	data[0xCD] = // CMP $????
		OpCode({
			&Executor::MR_AB,
			&Executor::CMP_,
		}, 4);
	data[0xDD] = // CMP $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::CMP_,
			&Executor::CHECK_EA,
		}, 4);
	data[0xD9] = // CMP $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::CMP_,
			&Executor::CHECK_EA,
		}, 4);
	data[0xC1] = // CMP ($??,X)
		OpCode({
			&Executor::MR_IX,
			&Executor::CMP_,
		}, 6);
	data[0xD1] = // CMP ($??),Y
		OpCode({
			&Executor::MR_IY,
			&Executor::CMP_,
			&Executor::CHECK_EA,
		}, 5);

	data[0xE0] = // CPX #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::CPX,
		}, 2);
	data[0xE4] = // CPX $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::CPX,
		}, 3);
	data[0xEC] = // CPX $????
		OpCode({
			&Executor::MR_AB,
			&Executor::CPX,
		}, 4);

	data[0xC0] = // CPY #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::CPY,
		}, 2);
	data[0xC4] = // CPY $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::CPY,
		}, 3);
	data[0xCC] = // CPY $????
		OpCode({
			&Executor::MR_AB,
			&Executor::CPY,
		}, 4);

	data[0x90] = // BCC
		OpCode({
			&Executor::MR_IM,
			&Executor::BCC,
		}, 2);
	data[0xB0] = // BCS
		OpCode({
			&Executor::MR_IM,
			&Executor::BCS,
		}, 2);
	data[0xF0] = // BEQ
		OpCode({
			&Executor::MR_IM,
			&Executor::BEQ,
		}, 2);
	data[0x30] = // BMI
		OpCode({
			&Executor::MR_IM,
			&Executor::BMI,
		}, 2);
	data[0xD0] = // BNE
		OpCode({
			&Executor::MR_IM,
			&Executor::BNE,
		}, 2);
	data[0x10] = // BPL
		OpCode({
			&Executor::MR_IM,
			&Executor::BPL,
		}, 2);
	data[0x50] = // BVC
		OpCode({
			&Executor::MR_IM,
			&Executor::BVC,
		}, 2);
	data[0x70] = // BVS
		OpCode({
			&Executor::MR_IM,
			&Executor::BVS,
		}, 2);

	data[0x4C] = // JMP $????
		OpCode({
			&Executor::JMP,
		}, 3);
	data[0x6C] = // JMP ($????)
		OpCode({
			&Executor::JMP_ID,
		}, 5);

	data[0x20] = // JSR
		OpCode({
			&Executor::JSR,
		}, 6);

	data[0x40] = // RTI
		OpCode({
			&Executor::RTI,
		}, 6);
	data[0x60] = // RTS
		OpCode({
			&Executor::RTS,
		}, 6);

		// フラグ制御系
	data[0x18] = // CLC
		OpCode({
			&Executor::CLC,
		}, 2);
	data[0xD8] = // CLD
		OpCode({
			&Executor::CLD,
		}, 2);
	data[0x58] = // CLI
		OpCode({
			&Executor::CLI,
		}, 2);
	data[0xB8] = // CLV
		OpCode({
			&Executor::CLV,
		}, 2);

	data[0x38] = // SEC
		OpCode({
			&Executor::SEC,
		}, 2);
	data[0xF8] = // SED
		OpCode({
			&Executor::SED,
		}, 2);
	data[0x78] = // SEI
		OpCode({
			&Executor::SEI,
		}, 2);

		// スタック系
	data[0x48] = // PHA
		OpCode({
			&Executor::PHA,
		}, 3);
	data[0x08] = // PHP
		OpCode({
			&Executor::PHP,
		}, 3);
	data[0x68] = // PLA (N-----Z-)
		OpCode({
			&Executor::PLA,
		}, 4);
	data[0x28] = // PLP
		OpCode({
			&Executor::PLP,
		}, 4);

		// その他
	data[0x00] = // BRK
		OpCode({
			&Executor::BRK,
		}, 7);

	data[0xEA] = // NOP
		OpCode({
		}, 2);

		// 未公開命令群
	data[0x0B] = // ANC #$??
	data[0x2B] = // ANC #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::ANC,
		}, 2);

	data[0x8B] = // ANE #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::ANE,
		}, 2);

	data[0x6B] = // ARR #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::ARR,
		}, 2);

	data[0x4B] = // ASR #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::ASR,
		}, 2);

	data[0xC7] = // DCP $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::DCP,
			&Executor::MW_ZP,
		}, 5);
	data[0xD7] = // DCP $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::DCP,
			&Executor::MW_ZP,
		}, 6);
	data[0xCF] = // DCP $????
		OpCode({
			&Executor::MR_AB,
			&Executor::DCP,
			&Executor::MW_EA,
		}, 6);
	data[0xDF] = // DCP $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::DCP,
			&Executor::MW_EA,
		}, 7);
	data[0xDB] = // DCP $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::DCP,
			&Executor::MW_EA,
		}, 7);
	data[0xC3] = // DCP ($??,X)
		OpCode({
			&Executor::MR_IX,
			&Executor::DCP,
			&Executor::MW_EA,
		}, 8);
	data[0xD3] = // DCP ($??),Y
		OpCode({
			&Executor::MR_IY,
			&Executor::DCP,
			&Executor::MW_EA,
		}, 8);

	data[0xE7] = // ISB $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::ISB,
			&Executor::MW_ZP,
		}, 5);
	data[0xF7] = // ISB $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::ISB,
			&Executor::MW_ZP,
		}, 5);
	data[0xEF] = // ISB $????
		OpCode({
			&Executor::MR_AB,
			&Executor::ISB,
			&Executor::MW_EA,
		}, 5);
	data[0xFF] = // ISB $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::ISB,
			&Executor::MW_EA,
		}, 5);
	data[0xFB] = // ISB $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::ISB,
			&Executor::MW_EA,
		}, 5);
	data[0xE3] = // ISB ($??,X)
		OpCode({
			&Executor::MR_IX,
			&Executor::ISB,
			&Executor::MW_EA,
		}, 5);
	data[0xF3] = // ISB ($??),Y
		OpCode({
			&Executor::MR_IY,
			&Executor::ISB,
			&Executor::MW_EA,
		}, 5);

	data[0xBB] = // LAS $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::LAS,
			&Executor::CHECK_EA,
		}, 4);


	data[0xA7] = // LAX $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::LAX,
		}, 3);
	data[0xB7] = // LAX $??,Y
		OpCode({
			&Executor::MR_ZY,
			&Executor::LAX,
		}, 4);
	data[0xAF] = // LAX $????
		OpCode({
			&Executor::MR_AB,
			&Executor::LAX,
		}, 4);
	data[0xBF] = // LAX $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::LAX,
			&Executor::CHECK_EA,
		}, 4);
	data[0xA3] = // LAX ($??,X)
		OpCode({
			&Executor::MR_IX,
			&Executor::LAX,
		}, 6);
	data[0xB3] = // LAX ($??),Y
		OpCode({
			&Executor::MR_IY,
			&Executor::LAX,
			&Executor::CHECK_EA,
		}, 5);

	data[0xAB] = // LXA #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::LXA,
		}, 2);

	data[0x27] = // RLA $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::RLA,
			&Executor::MW_ZP,
		}, 5);
	data[0x37] = // RLA $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::RLA,
			&Executor::MW_ZP,
		}, 6);
	data[0x2F] = // RLA $????
		OpCode({
			&Executor::MR_AB,
			&Executor::RLA,
			&Executor::MW_EA,
		}, 6);
	data[0x3F] = // RLA $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::RLA,
			&Executor::MW_EA,
		}, 7);
	data[0x3B] = // RLA $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::RLA,
			&Executor::MW_EA,
		}, 7);
	data[0x23] = // RLA ($??,X)
		OpCode({
			&Executor::MR_IX,
			&Executor::RLA,
			&Executor::MW_EA,
		}, 8);
	data[0x33] = // RLA ($??),Y
		OpCode({
			&Executor::MR_IY,
			&Executor::RLA,
			&Executor::MW_EA,
		}, 8);

	data[0x67] = // RRA $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::RRA,
			&Executor::MW_ZP,
		}, 5);
	data[0x77] = // RRA $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::RRA,
			&Executor::MW_ZP,
		}, 6);
	data[0x6F] = // RRA $????
		OpCode({
			&Executor::MR_AB,
			&Executor::RRA,
			&Executor::MW_EA,
		}, 6);
	data[0x7F] = // RRA $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::RRA,
			&Executor::MW_EA,
		}, 7);
	data[0x7B] = // RRA $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::RRA,
			&Executor::MW_EA,
		}, 7);
	data[0x63] = // RRA ($??,X)
		OpCode({
			&Executor::MR_IX,
			&Executor::RRA,
			&Executor::MW_EA,
		}, 8);
	data[0x73] = // RRA ($??),Y
		OpCode({
			&Executor::MR_IY,
			&Executor::RRA,
			&Executor::MW_EA,
		}, 8);

	data[0x87] = // SAX $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::SAX,
			&Executor::MW_ZP,
		}, 3);
	data[0x97] = // SAX $??,Y
		OpCode({
			&Executor::MR_ZY,
			&Executor::SAX,
			&Executor::MW_ZP,
		}, 4);
	data[0x8F] = // SAX $????
		OpCode({
			&Executor::MR_AB,
			&Executor::SAX,
			&Executor::MW_EA,
		}, 4);
	data[0x83] = // SAX ($??,X)
		OpCode({
			&Executor::MR_IX,
			&Executor::SAX,
			&Executor::MW_EA,
		}, 6);

	data[0xCB] = // SBX #$??
		OpCode({
			&Executor::MR_IM,
			&Executor::SBX,
		}, 2);

	data[0x9F] = // SHA $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::SHA,
			&Executor::MW_EA,
		}, 5);
	data[0x93] = // SHA ($??),Y
		OpCode({
			&Executor::MR_IY,
			&Executor::SHA,
			&Executor::MW_EA,
		}, 6);

	data[0x9B] = // SHS $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::SHS,
			&Executor::MW_EA,
		}, 5);

	data[0x9E] = // SHX $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::SHX,
			&Executor::MW_EA,
		}, 5);

	data[0x9C] = // SHY $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::SHY,
			&Executor::MW_EA,
		}, 5);

	data[0x07] = // SLO $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::SLO,
			&Executor::MW_ZP,
		}, 5);
	data[0x17] = // SLO $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::SLO,
			&Executor::MW_ZP,
		}, 6);
	data[0x0F] = // SLO $????
		OpCode({
			&Executor::MR_AB,
			&Executor::SLO,
			&Executor::MW_EA,
		}, 6);
	data[0x1F] = // SLO $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::SLO,
			&Executor::MW_EA,
		}, 7);
	data[0x1B] = // SLO $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::SLO,
			&Executor::MW_EA,
		}, 7);
	data[0x03] = // SLO ($??,X)
		OpCode({
			&Executor::MR_IX,
			&Executor::SLO,
			&Executor::MW_EA,
		}, 8);
	data[0x13] = // SLO ($??),Y
		OpCode({
			&Executor::MR_IY,
			&Executor::SLO,
			&Executor::MW_EA,
		}, 8);

	data[0x47] = // SRE $??
		OpCode({
			&Executor::MR_ZP,
			&Executor::SRE,
			&Executor::MW_ZP,
		}, 5);
	data[0x57] = // SRE $??,X
		OpCode({
			&Executor::MR_ZX,
			&Executor::SRE,
			&Executor::MW_ZP,
		}, 6);
	data[0x4F] = // SRE $????
		OpCode({
			&Executor::MR_AB,
			&Executor::SRE,
			&Executor::MW_EA,
		}, 6);
	data[0x5F] = // SRE $????,X
		OpCode({
			&Executor::MR_AX,
			&Executor::SRE,
			&Executor::MW_EA,
		}, 7);
	data[0x5B] = // SRE $????,Y
		OpCode({
			&Executor::MR_AY,
			&Executor::SRE,
			&Executor::MW_EA,
		}, 7);
	data[0x43] = // SRE ($??,X)
		OpCode({
			&Executor::MR_IX,
			&Executor::SRE,
			&Executor::MW_EA,
		}, 8);
	data[0x53] = // SRE ($??),Y
		OpCode({
			&Executor::MR_IY,
			&Executor::SRE,
			&Executor::MW_EA,
		}, 8);

	data[0xEB] = // SBC #$?? (Unofficial)
		OpCode({
			&Executor::MR_IM,
			&Executor::SBC,
		}, 2);

	data[0x1A] = // NOP (Unofficial)
	data[0x3A] = // NOP (Unofficial)
	data[0x5A] = // NOP (Unofficial)
	data[0x7A] = // NOP (Unofficial)
	data[0xDA] = // NOP (Unofficial)
	data[0xFA] = // NOP (Unofficial)
		OpCode({
		}, 2);
	data[0x80] = // DOP (CYCLES 2)
	data[0x82] = // DOP (CYCLES 2)
	data[0x89] = // DOP (CYCLES 2)
	data[0xC2] = // DOP (CYCLES 2)
	data[0xE2] = // DOP (CYCLES 2)
		OpCode({
			&Executor::DOP,
		}, 2);
	data[0x04] = // DOP (CYCLES 3)
	data[0x44] = // DOP (CYCLES 3)
	data[0x64] = // DOP (CYCLES 3)
		OpCode({
			&Executor::DOP,
		}, 3);
	data[0x14] = // DOP (CYCLES 4)
	data[0x34] = // DOP (CYCLES 4)
	data[0x54] = // DOP (CYCLES 4)
	data[0x74] = // DOP (CYCLES 4)
	data[0xD4] = // DOP (CYCLES 4)
	data[0xF4] = // DOP (CYCLES 4)
		OpCode({
			&Executor::DOP,
		}, 4);
	data[0x0C] = // TOP
	data[0x1C] = // TOP
	data[0x3C] = // TOP
	data[0x5C] = // TOP
	data[0x7C] = // TOP
	data[0xDC] = // TOP
	data[0xFC] = // TOP
		OpCode({
			&Executor::TOP,
		}, 4);

	data[0x02] = /* JAM */
	data[0x12] = /* JAM */
	data[0x22] = /* JAM */
	data[0x32] = /* JAM */
	data[0x42] = /* JAM */
	data[0x52] = /* JAM */
	data[0x62] = /* JAM */
	data[0x72] = /* JAM */
	data[0x92] = /* JAM */
	data[0xB2] = /* JAM */
	data[0xD2] = /* JAM */
	data[0xF2] = /* JAM */
		OpCode();

	return data;
}
