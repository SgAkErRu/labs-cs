w = linspace(0.01,0.019,10);
p = sqrt(-1)*w;
W = 44.1 ./ (8019 * p.^2 + 255.6 * p + 1) .* exp(-40 .* p);

// АЧХ экспериментальный
A_exp = [17.215, 15.683, 14.361, 13.195, 12.169, 11.273, 10.443, 9.716, 9.054, 8.458] 
// ФЧХ
F_exp = [1.90789, 2.004794, 2.106516, 2.209584, 2.28648, 2.36151, 2.44664, 2.537488, 2.639898, 2.71662]
F_exp = F_exp * -1

show_window(1);
calc1 = abs(W);
srav1 = [calc1; A_exp];
subplot(221);
plot(w, calc1);
title('calc');
subplot(222);
plot(w, A_exp);
title('exp');
subplot(212);
plot(w, srav1);
legend(['calc', 'exp']);
title('сравнение АЧХ');

show_window(2);
calc2 = unwrap(atan(imag(W),real(W)));
srav2 = [calc2; F_exp];
subplot(221);
plot(w, calc2);
title('calc');
subplot(222);
plot(w, F_exp);
title('exp');
subplot(212);
plot(w, srav2);
legend(['calc', 'exp']);
title('сравнение ФЧХ');

show_window(3);
subplot(221);
plot(real(W), imag(W));
title('calc');
subplot(222);
Re = A_exp .* cos(F_exp)
Im = A_exp .* sin(F_exp)
plot(Re, Im);
subplot(212);
plot(real(W), imag(W), Re, Im);
legend(['calc', 'exp']);
title('сравнение КЧХ');
