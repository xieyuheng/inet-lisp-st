define my-drop
  ( x )
end

1 2 my-drop 1 eq? assert

define my-swap
  ( x y )
  y x
end

1 2 swap
1 eq? assert
2 eq? assert
