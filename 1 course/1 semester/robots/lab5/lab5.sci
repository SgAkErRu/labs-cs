w = 0.001:0.001:1
m = 0.3;
s = -m*w + sqrt(-1)*w
W = 0.8 ./ (694967 * s.^3 + 18562 * s.^2 + 216 * s + 1) .* exp(-175 .* s);

W_inv = 1 ./ W

c0 = w * (m.^2 + 1) .* imag(W_inv)
c1 = m * imag(W_inv) - real(W_inv)

show_window(1);
calc1 = c1-c0;
plot(w, calc1);
xgrid()

//show_window(3);
//subplot(221);
//plot(real(W), imag(W));
//xgrid()
//title('calc');
//subplot(222);
//Re = A_exp .* cos(F_exp)
//Im = A_exp .* sin(F_exp)
//plot(Re, Im);
//xgrid()
//subplot(212);
//plot(real(W), imag(W), Re, Im);
//xgrid()
//legend(['calc', 'exp']);
//title('сравнение КЧХ');

