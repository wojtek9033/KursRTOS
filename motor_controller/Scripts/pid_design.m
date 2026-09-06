clear;
clc;

A = 1.18;
Q = 0.75;
w0 = 2 * pi * 1.75

s = tf('s');
G = A * w0^2/(s^2 + w0/Q * 2 * s + w0^2);

buffer = load ('observer_test.log', '-ascii');

y = buffer(:, 3)'/10000;
dt = 0.5e-3;
N = floor(length(y)/2);
n = 0:N-1;
t = n*dt;
y=y(:,1:N);

figure(1);

step(G);
hold on;
plot(t,y);
hold off;
grid on;
xlabel('t [s]');
ylabel('v [rot/s]');

figure(2);
bode(G);

