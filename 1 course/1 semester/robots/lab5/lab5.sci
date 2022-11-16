function str=precision(h)
    pt = h.data;
    str=msprintf('X:%.4f\nY:%.5f', pt(1),pt(2))
endfunction

w = 0:0.00001:0.02

// степень колебательности системы
m = 0.3;

s = -m*w + sqrt(-1)*w

// передаточная функция
W = 44.1 ./ (8019 * s.^2 + 255.6 * s + 1) .* exp(-40 .* s);

W_inv = 1 ./ W

c0 = w * (m.^2 + 1) .* imag(W_inv)
c1 = m * imag(W_inv) - real(W_inv)

show_window(1);

plot(c1, c0);

xgrid()
