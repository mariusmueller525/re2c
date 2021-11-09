// Code generated by re2c, DO NOT EDIT.
//go:generate re2go $INPUT -o $OUTPUT --loop-switch -i
package main

import (
	"errors"
	"testing"
)

var (
	eSyntax   = errors.New("syntax error")
	eOverflow = errors.New("overflow error")
)

const u32Limit uint64 = 1<<32

func parse_u32(str string) (uint32, error) {
	var cursor, marker int
	result := uint64(0)

	add_digit := func(base uint64, offset byte) {
		result = result * base + uint64(str[cursor-1] - offset)
		if result >= u32Limit {
			result = u32Limit
		}
	}

	
{
	var yych byte
	yystate := 1
	for {
		switch (yystate) {
		case 1:
			yych = str[cursor]
			cursor += 1
			switch (yych) {
			case '0':
				yystate = 4
				continue
			case '1':
				fallthrough
			case '2':
				fallthrough
			case '3':
				fallthrough
			case '4':
				fallthrough
			case '5':
				fallthrough
			case '6':
				fallthrough
			case '7':
				fallthrough
			case '8':
				fallthrough
			case '9':
				yystate = 6
				continue
			default:
				yystate = 2
				continue
			}
		case 2:
			yystate = 3
			continue
		case 3:
			{ goto err }
		case 4:
			marker = cursor
			yych = str[cursor]
			switch (yych) {
			case 'B':
				fallthrough
			case 'b':
				cursor += 1
				yystate = 8
				continue
			case 'X':
				fallthrough
			case 'x':
				cursor += 1
				yystate = 10
				continue
			default:
				yystate = 5
				continue
			}
		case 5:
			{ goto oct }
		case 6:
			yystate = 7
			continue
		case 7:
			cursor += -1
			{ goto dec }
		case 8:
			yych = str[cursor]
			switch (yych) {
			case '0':
				fallthrough
			case '1':
				cursor += 1
				yystate = 11
				continue
			default:
				yystate = 9
				continue
			}
		case 9:
			cursor = marker
			yystate = 5
			continue
		case 10:
			yych = str[cursor]
			switch (yych) {
			case '0':
				fallthrough
			case '1':
				fallthrough
			case '2':
				fallthrough
			case '3':
				fallthrough
			case '4':
				fallthrough
			case '5':
				fallthrough
			case '6':
				fallthrough
			case '7':
				fallthrough
			case '8':
				fallthrough
			case '9':
				fallthrough
			case 'A':
				fallthrough
			case 'B':
				fallthrough
			case 'C':
				fallthrough
			case 'D':
				fallthrough
			case 'E':
				fallthrough
			case 'F':
				fallthrough
			case 'a':
				fallthrough
			case 'b':
				fallthrough
			case 'c':
				fallthrough
			case 'd':
				fallthrough
			case 'e':
				fallthrough
			case 'f':
				cursor += 1
				yystate = 13
				continue
			default:
				yystate = 9
				continue
			}
		case 11:
			yystate = 12
			continue
		case 12:
			cursor += -1
			{ goto bin }
		case 13:
			yystate = 14
			continue
		case 14:
			cursor += -1
			{ goto hex }
		}
	}
}

bin:
	
{
	var yych byte
	yystate := 16
	for {
		switch (yystate) {
		case 16:
			yych = str[cursor]
			cursor += 1
			switch (yych) {
			case 0x00:
				yystate = 17
				continue
			case '0':
				fallthrough
			case '1':
				yystate = 21
				continue
			default:
				yystate = 19
				continue
			}
		case 17:
			yystate = 18
			continue
		case 18:
			{ goto end }
		case 19:
			yystate = 20
			continue
		case 20:
			{ goto err }
		case 21:
			yystate = 22
			continue
		case 22:
			{ add_digit(2, '0'); goto bin }
		}
	}
}

oct:
	
{
	var yych byte
	yystate := 24
	for {
		switch (yystate) {
		case 24:
			yych = str[cursor]
			cursor += 1
			switch (yych) {
			case 0x00:
				yystate = 25
				continue
			case '0':
				fallthrough
			case '1':
				fallthrough
			case '2':
				fallthrough
			case '3':
				fallthrough
			case '4':
				fallthrough
			case '5':
				fallthrough
			case '6':
				fallthrough
			case '7':
				yystate = 29
				continue
			default:
				yystate = 27
				continue
			}
		case 25:
			yystate = 26
			continue
		case 26:
			{ goto end }
		case 27:
			yystate = 28
			continue
		case 28:
			{ goto err }
		case 29:
			yystate = 30
			continue
		case 30:
			{ add_digit(8, '0'); goto oct }
		}
	}
}

dec:
	
{
	var yych byte
	yystate := 32
	for {
		switch (yystate) {
		case 32:
			yych = str[cursor]
			cursor += 1
			switch (yych) {
			case 0x00:
				yystate = 33
				continue
			case '0':
				fallthrough
			case '1':
				fallthrough
			case '2':
				fallthrough
			case '3':
				fallthrough
			case '4':
				fallthrough
			case '5':
				fallthrough
			case '6':
				fallthrough
			case '7':
				fallthrough
			case '8':
				fallthrough
			case '9':
				yystate = 37
				continue
			default:
				yystate = 35
				continue
			}
		case 33:
			yystate = 34
			continue
		case 34:
			{ goto end }
		case 35:
			yystate = 36
			continue
		case 36:
			{ goto err }
		case 37:
			yystate = 38
			continue
		case 38:
			{ add_digit(10, '0'); goto dec }
		}
	}
}

hex:
	
{
	var yych byte
	yystate := 40
	for {
		switch (yystate) {
		case 40:
			yych = str[cursor]
			cursor += 1
			switch (yych) {
			case 0x00:
				yystate = 41
				continue
			case '0':
				fallthrough
			case '1':
				fallthrough
			case '2':
				fallthrough
			case '3':
				fallthrough
			case '4':
				fallthrough
			case '5':
				fallthrough
			case '6':
				fallthrough
			case '7':
				fallthrough
			case '8':
				fallthrough
			case '9':
				yystate = 45
				continue
			case 'A':
				fallthrough
			case 'B':
				fallthrough
			case 'C':
				fallthrough
			case 'D':
				fallthrough
			case 'E':
				fallthrough
			case 'F':
				yystate = 47
				continue
			case 'a':
				fallthrough
			case 'b':
				fallthrough
			case 'c':
				fallthrough
			case 'd':
				fallthrough
			case 'e':
				fallthrough
			case 'f':
				yystate = 49
				continue
			default:
				yystate = 43
				continue
			}
		case 41:
			yystate = 42
			continue
		case 42:
			{ goto end }
		case 43:
			yystate = 44
			continue
		case 44:
			{ goto err }
		case 45:
			yystate = 46
			continue
		case 46:
			{ add_digit(16, '0');    goto hex }
		case 47:
			yystate = 48
			continue
		case 48:
			{ add_digit(16, 'A'-10); goto hex }
		case 49:
			yystate = 50
			continue
		case 50:
			{ add_digit(16, 'a'-10); goto hex }
		}
	}
}

end:
	if result < u32Limit {
		return uint32(result), nil
	} else {
		return 0, eOverflow
	}
err:
	return 0, eSyntax
}

func TestLex(t *testing.T) {
	var tests = []struct {
		num uint32
		str string
		err error
	}{
		{1234567890, "1234567890\000", nil},
		{13, "0b1101\000", nil},
		{0x7fe, "0x007Fe\000", nil},
		{0644, "0644\000", nil},
		{0, "9999999999\000", eOverflow},
		{0, "123??\000", eSyntax},
	}

	for _, x := range tests {
		t.Run(x.str, func(t *testing.T) {
			num, err := parse_u32(x.str)
			if !(num == x.num && err == x.err) {
				t.Errorf("got %d, want %d", num, x.num)
			}
		})
	}
}