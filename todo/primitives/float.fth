0.1 0.1 eq? assert
0.1 0.2 eq? not assert
0.1 -0.1 eq? not assert
-0.1 -0.1 eq? assert

0.1 0.1 fadd 0.2 eq? assert
0.2 0.2 fadd 0.4 eq? assert
0.1 -0.1 fadd 0.0 eq? assert

0.1 0.1 fdiv 1.0 eq? assert
0.5 0.2 fdiv 2.5 eq? assert
5.0 2.0 fdiv 2.5 eq? assert

1.0 float-to-int 1 eq? assert
