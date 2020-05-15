clear;
clc;

SK6812 = readtable('neopixel2.csv');
SK6812Zoom = load('neopixel.mat');
%t = SK6812{75:4600, 1}; % Time
%V = SK6812{75:4600, 2}; % Voltage
t = linspace(SK6812Zoom.Tstart, SK6812Zoom.Length * SK6812Zoom.Tinterval + SK6812Zoom.Tstart, SK6812Zoom.Length);
V = SK6812Zoom.A;

% semilogx(z_freq, z_impe);
figure();
plot(t, V, 'LineWidth', 1); %* 0.925
xlabel('Time [µs]');
ylabel('Voltage [V]');
legend('A0 Pin - DIN');
set(gcf, 'Position',  [100, 100, 800, 125]);
grid on;
set(gca, 'XLimSpec', 'Tight');
hold off;