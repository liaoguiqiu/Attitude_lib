
clear;

% Load data
 
trajectory_udu_load;
  
len=1:length(anglex);


figure(1);

plot(len,anglex,'r');
hold on;
plot(len,angley,'g');
plot(len,anglez,'b');

 
len2=1:length(anx);

figure(2);

plot(len2,anx,'r');
hold on;
plot(len2,any,'g')
plot(len2,anz,'b')

figure(3);

plot(len,anglex,'r');
hold on;
plot(len2,anx,'b');