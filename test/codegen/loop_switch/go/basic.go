// Code generated by re2c, DO NOT EDIT.
//go:generate re2go $INPUT -o $OUTPUT --loop-switch -i

package main                              //
                                          //
func lex(str string) {                    // Go code
    var cursor int                        //
                                          //

{
	var yych byte
	yystate := 0
	for {
		switch (yystate) {
		case 0:
			yych = str[cursor]
			cursor += 1
			if (yych <= '0') {
				yystate = 1
				continue
			}
			if (yych <= '9') {
				yystate = 3
				continue
			}
			yystate = 1
			continue
		case 1:
			yystate = 2
			continue
		case 2:
			{ panic("error!"); }
		case 3:
			yych = str[cursor]
			yystate = 4
			continue
		case 4:
			if (yych <= '/') {
				yystate = 5
				continue
			}
			if (yych <= '9') {
				cursor += 1
				yystate = 3
				continue
			}
			yystate = 5
			continue
		case 5:
			{ return }
		default:
			panic("internal lexer error")
		}
	}
}

}                                         //
                                          //
func main() {                             // Go code
    lex("1234\x00")                       //
}                                         //