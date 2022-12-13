function str=precision(h)
    pt = h.data;
    str=msprintf('X:%.4f\nY:%.5f', pt(1),pt(2))
endfunction

x = linspace(0, 2, 10000)
y = 1.4*x + exp(abs(x-2))

plot(x,y)

xgrid()
