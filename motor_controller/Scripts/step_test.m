clear;
clc;

% buffer = load ('motor_step_test.log', '-ascii');
buffer = load ('observer_test.log', '-ascii');
encoder_pulses_per_revolution = 3840;

% the data from encoder comes every 0.5e-3 seconds
dt = 0.5e-3;
% Shaft position based on encoder data, in revolution count
y = buffer(:, 1)/encoder_pulses_per_revolution;

% MCUobserver results
x_ = buffer(:, 2:3)'/10000;

N = length(y);
n = 0:N-1;
t = n*dt;

v = [0; diff(y)/dt];

% State vector
x = zeros(2, N);
x(1,1) = y(1);

beta = (1- 60*dt);
Ke = 0.001
for idx = 2 : N
%[teta ] = [1 dt  ][teta(k-1) ]
%[omega]   [0 beta][omega(k-1)]
%
% predict pos:
% newpos = old pos + old velocity times dt
  x1_ = x(1, idx -1) + x(2, idx-1)*dt;

% predict velocity:
% new velocity = beta (aka friction, losses) times prev velocity
  x2_ = beta * x(2, idx-1);

% "Enhance" estimated position and velocity
  error = y(idx) - x1_;
  x1_ = x1_ + Ke*error;
  x2_ = x2_ + Ke*error/dt;

% Actualize state
  x(1,idx) = x1_;
  x(2,idx) = x2_;
end

figure(1);
subplot(211);
plot(t,y);
hold on;
plot(t,x(1,:));
plot(t, x_(1,:), 'LineWidth', 2);
hold off;
grid on;
xlabel('t [s]');
ylabel('pos [revolutions]');
legend('measurements', 'observer', 'observer (MCU)');

subplot(212);
plot(t,v);
hold on;
plot(t,x(2,:));
plot(t, x_(2,:), 'LineWidth', 2);
hold off;
grid on;
xlabel('t [s]');
ylabel('v [rev/s]');
legend('measurements', 'observer', 'observer (MCU)');
