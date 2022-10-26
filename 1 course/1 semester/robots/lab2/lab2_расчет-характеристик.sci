w_exp = [0.001, 0.002, 0.003, 0.004, 0.005, 0.006, 0.007, 0.008, 0.01, 0.011, 0.012, 0.013, 0.014, 0.015, 0.016, 0.017, 0.018, 0.019, 0.025, 0.03]
w = linspace(0.001, 0.03, 1000)
p = sqrt(-1)*w;
W = 44.1 ./ (8019 * p.^2 + 255.6 * p + 1) .* exp(-40 .* p);

// АЧХ экспериментальный
A_exp = [43.045, 40.286, 36.633, 32.816, 29.249, 26.081, 23.335, 20.977, 17.215, 15.683, 14.361, 13.195, 12.169, 11.273, 10.443, 9.716, 9.054, 8.458, 5.844, 4.467] 
// ФЧХ
F_exp = [0.330148, 0.567242, 0.782766, 1.0269, 1.233476, 1.400184, 1.540602, 1.663136, 1.90789, 2.004794, 2.106516, 2.209584, 2.28648, 2.36151, 2.44664, 2.537488, 2.639898, 2.71662, 3.114775, 3.45444]
F_exp = F_exp * -1

show_window(1);
calc1 = abs(W);
subplot(221);
plot(w, calc1);
xgrid()
title('calc');
subplot(222);
plot(w_exp, A_exp);
xgrid()
title('exp');
subplot(212);
plot(w, calc1, w_exp, A_exp);
xgrid()
legend(['calc', 'exp']);
title('сравнение АЧХ');

show_window(2);
calc2 = unwrap(atan(imag(W),real(W)));
subplot(221);
plot(w, calc2);
xgrid()
title('calc');
subplot(222);
plot(w_exp, F_exp);
xgrid()
title('exp');
subplot(212);
plot(w, calc2, w_exp, F_exp);
xgrid()
legend(['calc', 'exp']);
title('сравнение ФЧХ');

show_window(3);
subplot(221);
plot(real(W), imag(W));
xgrid()
title('calc');
subplot(222);
Re = A_exp .* cos(F_exp)
Im = A_exp .* sin(F_exp)
plot(Re, Im);
xgrid()
subplot(212);
plot(real(W), imag(W), Re, Im);
xgrid()
legend(['calc', 'exp']);
title('сравнение КЧХ');

