define square
  dup mul
end

1 square 1 eq assert
2 square 4 eq assert
3 square 9 eq assert

define two 2 end

two square 4 eq assert
