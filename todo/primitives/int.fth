1 1 eq assert
1 2 eq not assert
1 -1 eq not assert
-1 -1 eq assert

1 1 add 2 eq assert
2 2 add 4 eq assert
1 -1 add 0 eq assert

1 1 mul 1 eq assert
2 2 mul 4 eq assert
2 -1 mul -2 eq assert

1 1 div 1 eq assert
5 2 div 2 eq assert
5 2 mod 1 eq assert

1 int-to-float 1.0 eq assert
