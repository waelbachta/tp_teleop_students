clear all;
close all;

data = importdata("output_file.txt","\t",1);

% FIGURE 1 - PAS DE SUPERPOSITION DES POSITIONS DU MAITRE ET DE L'ESCLAVE
figure();

% Robot Maitre positions articulaires
subplot(2,2,1)
hold on;
grid on;
plot(data.data(:,1), data.data(:,2));
plot(data.data(:,1), data.data(:,3));
legend("q1","q2");
title("Maitre - Positions articulaires");

% Robot Esclave positions articulaires
subplot(2,2,2)
hold on;
grid on;
plot(data.data(:,1), data.data(:,4));
plot(data.data(:,1), data.data(:,5));
legend("q1","q2");
title("Esclave - Positions articulaires");

% Robot Maitre position operationnelle
subplot(2,2,3)
hold on;
grid on;
plot(data.data(:,1), data.data(:,6));
plot(data.data(:,1), data.data(:,7));
legend("x","y");
title("Maitre - Position opérationnelle");

% Robot Esclave position operationnelle
subplot(2,2,4)
hold on;
grid on;
plot(data.data(:,1), data.data(:,8));
plot(data.data(:,1), data.data(:,9));
legend("x","y");
title("Esclave - Position opérationnelle");


% FIGURE 2 - SUPERPOSITION DES POSITIONS DU MAITRE ET DE L'ESCLAVE
figure();

% q1
subplot(2,2,1)
hold on;
grid on;
plot(data.data(:,1), data.data(:,2), '--');     % maitre
plot(data.data(:,1), data.data(:,4), '-');      % esclave
legend("maitre","esclave");
xlabel("Temps [msec]");
ylabel("q1 [rad]");
ylim([-pi/4, pi/4]);

% q2
subplot(2,2,2)
hold on;
grid on;
plot(data.data(:,1), data.data(:,3), '--');     % maitre
plot(data.data(:,1), data.data(:,5), '-');      % esclave
legend("maitre","esclave");
xlabel("Temps [msec]");
ylabel("q2 [rad]");
ylim([-3*pi/4, -pi/4]);

% x
subplot(2,2,3)
hold on;
grid on;
plot(data.data(:,1), data.data(:,6), '--');     % maitre
plot(data.data(:,1), data.data(:,8), '-');      % esclave
legend("maitre","esclave");
xlabel("Temps [msec]");
ylabel("x [m]");

% y
subplot(2,2,4)
hold on;
grid on;
plot(data.data(:,1), data.data(:,7), '--');     % maitre
plot(data.data(:,1), data.data(:,9), '-');      % esclave
legend("maitre","esclave");
xlabel("Temps [msec]");
ylabel("y [m]");

% FIGURE 3 - CONSIGNE Q2
figure();
hold on;
grid on;
plot(data.data(:,1), data.data(:,10));
plot(data.data(:,1), data.data(:,11));
legend("q1","q2");
xlabel("Temps [msec]");
ylabel("Consigne articulaire [rad]");
