minimize
 obj: +1 x11 + 2 x12 + 5 x23 + 2 x24 + 1 x31 + 2 x33 + 1 x34 
st
c1:   +  x11 +   x12                                           <= 400
c2:                  +   x23 +   x24                           <= 1200
c3:                                  +   x31 +   x33 +   x34   <= 1000
c4:   +  x11                         +   x31                   = 800
c5:          +   x12                                           = 100
c6:                  +   x23                 +   x33           = 500
c7:                          +   x24                 +   x34   = 500
bounds
end
 