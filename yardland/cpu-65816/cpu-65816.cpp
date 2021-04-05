#include <yardland/cpu-65816/cpu-65816.hpp>

#define CPU_65816_FLAG_CARRY        0b00000001
#define CPU_65816_FLAG_ZERO         0b00000010
#define CPU_65816_FLAG_INTERRUPT    0b00000100
#define CPU_65816_FLAG_DECIMAL      0b00001000
#define CPU_65816_FLAG_INDEX        0b00010000
#define CPU_65816_FLAG_MEMORY       0b00100000
#define CPU_65816_FLAG_OVERFLOW     0b01000000
#define CPU_65816_FLAG_NEGATIVE     0b10000000

cpu_65816::cpu_65816()
{
	AH = 0, AL = 0;
	XH = 0, XL = 0;
	YH = 0, YL = 0;
	KH = 0, KL = 0b00110000;
	D = 0;
	PCL = 0xe000, PBR = 0, DBR = 0;

	SL = 0xff, SH = 0x01;

	stack.stack_ptr_lsb = &SL;
	stack.stack_ptr_msb = &SH;

	return;
}

void cpu_65816::Step()
{

    // Temporal Pseudo-Registers.

	std::uint8_t  IR /*= memory.prog_getc(PBR, PCL)*/;
	std::uint16_t Addr = 0;
	std::uint8_t  bank = 0;
	std::uint8_t  inmediate = 0;
	std::uint16_t inmediate16 = 0;

	switch(IR)
	{
		case 0x00: // BRK s
			PCL += 2;
			break;
		case 0x01: // ORA (d,x)
			PCL++;
			inmediate = memory.prog_getc(PBR, PCL);
			D += inmediate;
			D += addr_8to16(XH, XL);
			Addr = memory.data_getw(0, D);
			if ((KL & CPUFLAG_MEMORYSELECT) == CPUFLAG_MEMORYSELECT)
				AL |= memory.data_getc(DBR, Addr);
			else
			{
				AL |= memory.data_getc(DBR, Addr);
				AH |= memory.data_getc(DBR, Addr + 1);
			}
			break;
		case 0x02: // COP s
			PCL += 2;
			break;/*
		case 0x03: // ORA d,s
			break;
		case 0x04: // TBS d
			break;
		case 0x05: // ORA d
			break;
		case 0x06: // ASL d
			break;
		case 0x07: // ORA [d]
			break;
		case 0x08: // PHP s
			break;
		case 0x09: // ORA #
			break;
		case 0x0a: // ASL A
			break;
		case 0x0b: // PHD s
			break;
		case 0x0c: // TSB a
			break;
		case 0x0d: // ORA a
			break;
		case 0x0e: // ASL a
			break;
		case 0x0f: // ORA al
			break;
		case 0x10: // BPL r
			break;
		case 0x11: // ORA (d),y
			break;
		case 0x12: // ORA (d)
			break;
		case 0x13: // ORA (d,s),y
			break;
		case 0x14: // TRB d
			break;
		case 0x15: // ORA d,x
			break;
		case 0x16: // ASL zp,x
			break;
		case 0x17: // ORA [d],y
			break;
		case 0x18: // CLC i
			break;
		case 0x19: // ORA a,y
			break;*/
		case 0x1a: // INC A
			AL++;
			if (AL >= 255)
			{
				AL = 0;
				KL |= 0b00000010;
				if ((KL | 0b11101111) == 0b11101111)
					AH++;
			}
			PCL++;
			break;/*
		case 0x1b: // TCS
			break;
		case 0x1c: // TRB a
			break;
		case 0x1d: // ORA a,x
			break;
		case 0x1e: // ASL a,x
			break;
		case 0x1f: // ORA al,x
			break;*/
		case 0x20: // JSR a
			PCL++;
			inmediate16 = memory.prog_getw(PBR, PCL);
			stack.push(addr_16toLsb(PCL));
			stack.push(addr_16toMsb(PCL));
			PCL = inmediate16;
			break;/*
		case 0x21: // AND (zp,x)
			break;
		case 0x22: // JSL al
			break;
		case 0x23: // AND d,s
			break;
		case 0x24: // BIT d
			break;
		case 0x25: // AND d
			break;
		case 0x26: // ROL d
			break;
		case 0x27: // AND [d]
			break;
		case 0x28: // PLP s
			break;
		case 0x29: // AND #
			break;
		case 0x2a: // ROL A
			break;
		case 0x2b: // PLD s
			break;
		case 0x2c: // BIT a
			break;
		case 0x2d: // AND a
			break;
		case 0x2e: // ROL a
			break;
		case 0x2f: // AND al
			break;
		case 0x30: // BMI R
			break;
		case 0x31:
			break;
		case 0x32:
			break;
		case 0x33:
			break;
		case 0x34:
			break;
		case 0x35:
			break;
		case 0x36:
			break;
		case 0x37:
			break;
		case 0x38:
			break;
		case 0x39:
			break;
		case 0x3a:
			break;
		case 0x3b:
			break;
		case 0x3c:
			break;
		case 0x3d:
			break;
		case 0x3e:
			break;
		case 0x3f:
			break;
		case 0x40:
			break;
		case 0x41:
			break;*/
		case 0x42: // WDM
			PCL++;
			switch (memory.prog_getc(PBR, PCL))
			{
				case 0x00:
					terminal_enable = terminal_enable ? false : true;
					break;
				case 0x01:
					render_enable = render_enable ? false : true;
					break;
				default:
					break;
			}
			PCL++;
			break;/*
		case 0x43:
			break;
		case 0x44:
			break;
		case 0x45:
			break;
		case 0x46:
			break;
		case 0x47:
			break;*/
		case 0x48: // PHA s
			if ((KL & CPUFLAG_MEMORYSELECT) == CPUFLAG_MEMORYSELECT)
				stack.push(AL);
			else
			{
				stack.push(AL);
				stack.push(AH);
			}
			PCL++;
			break;/*
		case 0x49:
			break;
		case 0x4a:
			break;
		case 0x4b:
			break;
		case 0x4c:
			break;
		case 0x4d:
			break;
		case 0x4e:
			break;
		case 0x4f:
			break;
		case 0x50:
			break;
		case 0x51:
			break;
		case 0x52:
			break;
		case 0x53:
			break;
		case 0x54:
			break;
		case 0x55:
			break;
		case 0x56:
			break;
		case 0x57:
			break;
		case 0x58:
			break;
		case 0x59:
			break;*/
		case 0x5a: // PHY s
			if ((KL & CPUFLAG_INDEXSELECT) == CPUFLAG_INDEXSELECT)
				stack.push(YL);
			else
			{
				stack.push(YL);
				stack.push(YH);
			}
			PCL++;
			break;/*
		case 0x5b:
			break;
		case 0x5c:
			break;
		case 0x5d:
			break;
		case 0x5e:
			break;
		case 0x5f:
			break;*/
		case 0x60: // RTS s
			inmediate = stack.pull();
			Addr = stack.pull();
			PCL = addr_8to16(inmediate, Addr);
			PCL += 2;
			break;/*
		case 0x61:
			break;
		case 0x62:
			break;
		case 0x63:
			break;
		case 0x64:
			break;
		case 0x65:
			break;
		case 0x66:
			break;
		case 0x67:
			break;*/
		case 0x68: // PLA s
			if ((KL & 0b00010000) == 0b00010000)
				AL = stack.pull();
			else
			{
				AH = stack.pull();
				AL = stack.pull();
			}
			PCL++;
			break;/*
		case 0x69:
			break;
		case 0x6a:
			break;
		case 0x6b:
			break;
		case 0x6c:
			break;*/
		case 0x6d: // ADC a
			inmediate = addr_8to16(AH, AL);
			PCL++;
			Addr = memory.prog_getw(PBR, PCL);
			inmediate += memory.data_getc(DBR, Addr);
			PCL++;
			break;/*
		case 0x6e:
			break;
		case 0x6f:
			break;
		case 0x70:
			break;
		case 0x71:
			break;
		case 0x72:
			break;
		case 0x73:
			break;*/
		case 0x74: // STZ d,x
			PCL++;
			Addr = memory.prog_getw(PBR, PCL);
			Addr += D;
			if ((KL & CPUFLAG_INDEXSELECT) == CPUFLAG_INDEXSELECT)
				Addr += XL;
			else
				Addr += addr_8to16(XH, XL);
			PCL += 2;
			memory.data_putc(0, Addr, 0);
			break;/*
		case 0x75:
			break;
		case 0x76:
			break;
		case 0x77:
			break;
		case 0x78:
			break;
		case 0x79:
			break;*/
		case 0x7a: // PLY
			if ((KL & CPUFLAG_INDEXSELECT) == CPUFLAG_INDEXSELECT)
				YL = stack.pull();
			else
			{
				YH = stack.pull();
				YL = stack.pull();
			}
			PCL++;
			break;/*
		case 0x7b:
			break;
		case 0x7c:
			break;
		case 0x7d:
			break;
		case 0x7e:
			break;
		case 0x7f:
			break;*/
		case 0x80: // BRA r
			PCL++;
			PCL += (int8_t)memory.prog_getc(PBR, PCL);
			PCL++;
			break;/*
		case 0x81:
			break;
		case 0x82:
			break;
		case 0x83:
			break;
		case 0x84:
			break;
		case 0x85:
			break;
		case 0x86:
			break;
		case 0x87:
			break;
		case 0x88:
			break;
		case 0x89:
			break;
		case 0x8a:
			break;*/
		case 0x8b: // PHB s
			stack.push(DBR);
			PCL++; 
			break;
		case 0x8c: // STY a
			PCL++;
			Addr = memory.prog_getw(PBR, PCL);
			PCL += 2;
			if ((KL & CPUFLAG_INDEXSELECT) == CPUFLAG_INDEXSELECT)
				memory.data_putc(DBR, Addr, YL);
			else
				memory.data_putw(DBR, Addr, YL, YH);
			break;
		case 0x8d: // STA a
			PCL++;
			Addr = memory.prog_getw(PBR, PCL);
			PCL += 2;
			if ((KL & 0b00100000) == 0b00100000)
				memory.data_putc(DBR, Addr, AL);
			else
				memory.data_putw(DBR, Addr, AL, AH);
			break;
		case 0x8e: // STX a
			PCL++; 
			Addr = memory.prog_getw(PBR, PCL);
			PCL += 2; 
			if ((KL & CPUFLAG_INDEXSELECT) == CPUFLAG_INDEXSELECT)
				memory.data_putc(DBR, Addr, XL);
			else
				memory.data_putw(DBR, Addr, XL, XH);
			break;/*
		case 0x8f:
			break;
		case 0x90:
			break;
		case 0x91:
			break;
		case 0x92:
			break;
		case 0x93:
			break;
		case 0x94:
			break;
		case 0x95:
			break;
		case 0x96:
			break;
		case 0x97:
			break;
		case 0x98:
			break;
		case 0x99:
			break;*/
		case 0x9a: // TXS i
			SL = XL;
			SH = XH;
			PCL++;
			break;/*
		case 0x9b:
			break;
		case 0x9c:
			break;
		case 0x9d:
			break;*/
		case 0x9e: // STZ a,x
			PCL++;
			Addr = memory.prog_getw(PBR, PCL);
			if ((KL & CPUFLAG_INDEXSELECT) == CPUFLAG_INDEXSELECT)
				Addr += XL;
			else
				Addr += addr_8to16(XH, XL);
			PCL += 2;
			memory.data_putc(DBR, Addr, 0);
			break;
		case 0x9f: // STA al,x
			PCL++;
			Addr = memory.prog_getw(PBR, PCL);
			if ((KL & CPUFLAG_INDEXSELECT) == CPUFLAG_INDEXSELECT)
				Addr += XL;
			else
				Addr += addr_8to16(XH, XL);
			PCL += 2;
			bank = memory.prog_getc(PBR, PCL);
			if ((KL & 0b00100000) == 0b00100000)
				memory.data_putc(bank, Addr, AL);
			else
				memory.data_putw(bank, Addr, AL, AH);
			PCL++;
			break;
		case 0xa0: // LDY #
			PCL++;
			if ((KL & CPUFLAG_INDEXSELECT) == CPUFLAG_INDEXSELECT)
				YL = memory.prog_getc(DBR, PCL);
			else
			{
				YL = memory.prog_getc(DBR, PCL);
				PCL++;
				YH = memory.prog_getc(DBR, PCL);
			}
			PCL++; 
			break;
		case 0xa1: // LDA (d,x)
			break;
		case 0xa2: // LDX #
			PCL++;
			if ((KL & CPUFLAG_INDEXSELECT) == CPUFLAG_INDEXSELECT)
				XL = memory.prog_getc(DBR, PCL);
			else
			{
				XL = memory.prog_getc(DBR, PCL);
				PCL++;
				XH = memory.prog_getc(DBR, PCL);
			}
			PCL++;
			break;/*
		case 0xa3: // LDA d,s
			break;
		case 0xa4:
			break;
		case 0xa5:
			break;
		case 0xa6:
			break;
		case 0xa7:
			break;
		case 0xa8:
			break;*/
		case 0xa9: // LDA #
			PCL++;
			if ((KL & 0b00100000) == 0b00100000)
				AL = memory.prog_getc(DBR, PCL);
			else
			{
				AL = memory.prog_getc(DBR, PCL);
				PCL++;
				AH = memory.prog_getc(DBR, PCL);
			}
			PCL++;
			break;
		case 0xaa:
			break;
		case 0xab: // PLB s
			DBR = stack.pull();
			PCL++; 
			break;/*
		case 0xac:
			break;*/
		case 0xad: // LDA a
			PCL++;
			Addr = memory.prog_getw(PBR, PCL);
			PCL += 2;
			if ((KL & 0b00010000) == 0b00010000)
				AL = memory.prog_getc(DBR, Addr);
			else
			{
				AL = memory.prog_getc(DBR, Addr);
				AH = memory.prog_getc(DBR, Addr + 1);
			}
			break;
		case 0xae: // LDX a
			PCL++; 
			Addr = memory.prog_getw(PBR, PCL);
			PCL += 2; 
			if ((KL & CPUFLAG_INDEXSELECT) == CPUFLAG_INDEXSELECT)
				XL = memory.data_getc(DBR, Addr);
			else
			{
				XL = memory.data_getc(DBR, Addr);
				XH = memory.data_getc(DBR, Addr + 1);
			}
			break;/*
		case 0xaf:
			break;
		case 0xb0:
			break;
		case 0xb1:
			break;
		case 0xb2:
			break;
		case 0xb3:
			break;
		case 0xb4:
			break;*/
		case 0xb5: // LDA d,x
			PCL++;
			inmediate = memory.prog_getc(PBR, PCL);
			Addr = D;
			Addr += inmediate;
			Addr += addr_8to16(XH, XL);
			if ((KL & CPUFLAG_MEMORYSELECT) == CPUFLAG_MEMORYSELECT)
				AL = memory.data_getc(0, Addr);
			else
			{
				AL = memory.data_getc(0, Addr);
				AH = memory.data_getc(0, Addr + 1);
			}
			PCL++;
			break;/*
		case 0xb6:
			break;
		case 0xb7:
			break;
		case 0xb8:
			break;*/
		case 0xb9: // LDA a,y
			PCL++; 
			Addr  = memory.prog_getw(PBR, PCL);
			Addr += (uint32_t)YL;
			PCL += 2; 
			if ((KL & 0b00100000) == 0b00100000)
				AL = memory.prog_getc(DBR, Addr);
			else
			{
				AL = memory.prog_getc(DBR, Addr);
				AH = memory.prog_getc(DBR, Addr + 1);
			}
			break;/*
		case 0xba:
			break;
		case 0xbb:
			break;
		case 0xbc:
			break;*/
		case 0xbd: // LDA a,x
			PCL++;
			Addr = memory.prog_getw(PBR, PCL);
			Addr += (uint32_t)XL;
			PCL += 2;
			if ((KL & 0b00100000) == 0b00100000)
				AL = memory.data_getc(DBR, Addr);
			else
			{
				AL = memory.data_getc(DBR, Addr);
				AH = memory.data_getc(DBR, Addr + 1);
			}
			break;/*
		case 0xbe:
			break;
		case 0xbf:
			break;*/
		case 0xc0: // CPY #
			PCL++;
			if ((KL & 0b00010000) == 0b00010000)
			{
				inmediate = memory.prog_getc(PBR, PCL);
				if (inmediate == YL)
				{
					KL |= 0b00000010; // Set zero flag
					KL &= 0b01111111; // Reset Negative flag
				}
				else
				{
					KL |= 0b10000000; // Set negative flag
					KL &= 0b11111101; // Reset Zero flag
				}
			}
			else
			{
				inmediate16 = memory.prog_getw(PBR, PCL);
				if (inmediate16 == addr_8to16(YH, YL))
				{
					KL |= 0b00000010; // Set zero flag
					KL &= 0b01111111; // Reset Negative flag
				}
				else
				{
					KL |= 0b10000000; // Set negative flag
					KL &= 0b11111101; // Reset Zero flag
				}
				PCL++;
			}
			PCL++;
			break;/*
		case 0xc1:
			break;*/
		case 0xc2: // REP #
			PCL++;
			KL &= ~memory.prog_getc(PBR, PCL);
			PCL++;
			break;/*
		case 0xc3:
			break;
		case 0xc4:
			break;
		case 0xc5:
			break;
		case 0xc6:
			break;
		case 0xc7:
			break;*/
		case 0xc8: // INY i
			YL++;
			if (YL > 255)
			{
				YL = 0;
				KL |= 0b00000010;
			}
			PCL++; 
			break;
		case 0xc9: // CMP #
			PCL++; 
			if ((KL & CPUFLAG_MEMORYSELECT) == CPUFLAG_MEMORYSELECT)
			{
				inmediate = memory.prog_getc(PBR, PCL);
				if (inmediate == AL)
				{
					KL |= CPUFLAG_ZERO;			// Set zero flag
					KL &= ~CPUFLAG_NEGATIVE;	// Reset Negative flag
				}
				else
				{
					KL |= CPUFLAG_NEGATIVE;		// Set negative flag
					KL &= ~CPUFLAG_ZERO;		// Reset Zero flag
				}
			}
			else
			{
				inmediate16 = memory.prog_getw(PBR, PCL);
				if (inmediate16 == addr_8to16(AH, AL))
				{
					KL |= CPUFLAG_ZERO;			// Set zero flag
					KL &= ~CPUFLAG_NEGATIVE;	// Reset Negative flag
				}
				else
				{
					KL |= CPUFLAG_NEGATIVE;		// Set negative flag
					KL &= ~CPUFLAG_ZERO;		// Reset Zero flag
				}
				PCL++;
			}
			PCL++;
			break;/*
		case 0xca:
			break;
		case 0xcb:
			break;
		case 0xcc:
			break;
		case 0xcd:
			break;
		case 0xce:
			break;
		case 0xcf:
			break;*/
		case 0xd0: // BNE r
			PCL++;
			if((KL | 0b11111101) == 0b11111101)
				PCL += (int8_t)memory.prog_getc(PBR, PCL);
			PCL++; 
			break;/*
		case 0xd1:
			break;
		case 0xd2:
			break;
		case 0xd3:
			break;
		case 0xd4:
			break;
		case 0xd5:
			break;
		case 0xd6:
			break;
		case 0xd7:
			break;
		case 0xd8:
			break;
		case 0xd9:
			break;*/
		case 0xda: // PHX s
			if ((KL & 0b00010000) == 0b00010000)
				stack.push(XL);
			else
			{
				stack.push(XL);
				stack.push(XH);
			}
			PCL++;
			break;
		case 0xdb: // STP i
			return 1;
			break;/*
		case 0xde:
			break;
		case 0xdf:
			break;*/
		case 0xe0: // CPX #
			PCL++;
			if ((KL & 0b00010000) == 0b00010000)
			{
				inmediate = memory.prog_getc(PBR, PCL);
				if (inmediate == XL)
				{
					KL |= 0b00000010; // Set zero flag
					KL &= 0b01111111; // Reset Negative flag
				}
				else
				{
					KL |= 0b10000000; // Set negative flag
					KL &= 0b11111101; // Reset Zero flag
				}
			}
			else
			{
				inmediate16 = memory.prog_getw(PBR, PCL);
				if (inmediate16 == addr_8to16(XH, XL))
				{
					KL |= 0b00000010; // Set zero flag
					KL &= 0b01111111; // Reset Negative flag
				}
				else
				{
					KL |= 0b10000000; // Set negative flag
					KL &= 0b11111101; // Reset Zero flag
				}
				PCL++;
			}
			PCL++;
			break;/*
		case 0xe1:
			break;*/
		case 0xe2: // SEP #
			PCL++;
			KL |= memory.prog_getc(PBR, PCL);
			PCL++;
			break;/*
		case 0xe3:
			break;
		case 0xe4:
			break;
		case 0xe5:
			break;
		case 0xe6:
			break;
		case 0xe7:
			break;*/
		case 0xe8: // INX i
			XL++;
			if (XL >= 255) 
			{
				XL = 0;
				KL |= 0b00000010;
				if ((KL | 0b11101111) == 0b11101111)
					XH++;
			}
			PCL++;
			break;
		case 0xe9:
			break;
		case 0xea: // NOP i
			PCL++;
			break;/*
		case 0xeb:
			break;
		case 0xec:
			break;*/
		case 0xed: // SBC a
			if ((KL & CPUFLAG_MEMORYSELECT) == CPUFLAG_MEMORYSELECT)
			{
				PCL++;
				Addr = memory.prog_getw(PBR, PCL);
				PCL++;
				AL -= memory.data_getc(DBR, Addr);
			}
			else
			{
				inmediate16 = addr_8to16(AH, AL);
				PCL++;
				Addr = memory.prog_getw(PBR, PCL);
				PCL++;
				inmediate16 -= memory.data_getc(DBR, Addr);
				AH = addr_16toMsb(inmediate16);
				AL = addr_16toLsb(inmediate16);
			}
			PCL++;
			break;/*
		case 0xee:
			break;
		case 0xef:
			break;*/
		case 0xf0: // BEQ r
			PCL++;
			if((KL & 0b00000010) == 0b00000010)
				PCL += (int8_t)memory.prog_getc(PBR, PCL);
			PCL++;
			break;/*
		case 0xf1:
			break;
		case 0xf2:
			break;
		case 0xf3:
			break;
		case 0xf4:
			break;
		case 0xf5:
			break;
		case 0xf6:
			break;
		case 0xf7:
			break;
		case 0xf8:
			break;
		case 0xf9:
			break;*/
		case 0xfa: // PLX s
			if ((KL & 0b00010000) == 0b00010000)
				XL = stack.pull();
			else
			{
				XH = stack.pull();
				XL = stack.pull();
			}
			PCL++;
			break;/*
		case 0xfb:
			break;
		case 0xfc:
			break;
		case 0xfd:
			break;
		case 0xfe:
			break;
		case 0xff:
			break;*/
		default:
			std::cerr << std::showbase << std::hex;
			std::cerr << "[Yardland/vcpu816] Error!, Found an illegal opcode (" << (int)IR << ") " << "at address (" << (int)PCL << ")." << std::endl;
			PCL++;
			break;
	}
	return 0;
}
