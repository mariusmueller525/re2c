/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i

{
	YYCTYPE yych;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'a':	goto yy3;
	case 'b':	goto yy6;
	default:	goto yy2;
	}
yy2:
	{}
yy3:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'a':	goto yy3;
	case 'b':	goto yy8;
	default:	goto yy5;
	}
yy5:
	{}
yy6:
	++YYCURSOR;
	YYCURSOR -= 1;
	{}
yy8:
	++YYCURSOR;
	YYCURSOR -= 1;
	{}
}

messages/nullable.re:6:11: warning: rule matches empty string [-Wmatch-empty-string]
messages/nullable.re:7:5: warning: rule matches empty string [-Wmatch-empty-string]