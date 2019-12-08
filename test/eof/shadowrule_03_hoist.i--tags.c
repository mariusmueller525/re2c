/* Generated by re2c */
// R1 matches any string of two characters (or more). Because of greediness
// ANY rule cannot match on a single-character string (it is shadowed and
// gets eliminated) => tags are hoisted

{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR++;
	yych = *YYCURSOR;
	yyt1 = YYCURSOR;
yy3:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'a':	goto yy3;
	default:	goto yy5;
	}
yy5:
	x = yyt1;
	{ /* R1, x must be set */ }
}


// R1 matches any string of two characters (or more). ANY rule is not shadowed
// because with EOF rule YYFILL returns and rolls back to ANY. Untagged
// fallback transition to ANY prevents tag hoisting.

{
	YYCTYPE yych;
yy7_:
	yych = *YYCURSOR;
	if (yych >= 0x01) goto yy8;
	if (YYLIMIT <= YYCURSOR) {
		if (YYFILL () == 0) goto yy7_;
		goto yyeof;
	}
yy8:
	++YYCURSOR;
yy8_:
	yych = *YYCURSOR;
	if (yych <= 0x00) {
		if (YYLIMIT <= YYCURSOR) {
			if (YYFILL () == 0) goto yy8_;
			goto yy9;
		}
		yyt1 = YYCURSOR;
		goto yy10;
	}
	yyt1 = YYCURSOR;
	goto yy10;
yy9:
	{ /* ANY, x must not be set */ }
yy10:
	++YYCURSOR;
yy10_:
	yych = *YYCURSOR;
	switch (yych) {
	case 'a':	goto yy10;
	default:
		if (YYLIMIT <= YYCURSOR) {
			if (YYFILL () == 0) goto yy10_;
		}
		goto yy12;
	}
yy12:
	x = yyt1;
	{ /* R1, x must be set */ }
yyeof:
	{ /* EOF, x must not be set */ }
}

eof/shadowrule_03_hoist.i--tags.re:6:16: warning: unreachable rule (shadowed by rule at line 5) [-Wunreachable-rules]
