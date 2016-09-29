%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Filename: result.m
% Authors: Sylvain Marleau, Vincent Zalzal
% Description:  This script shows filtered trajectories and compares the
%               common kalman filter with the UDU kalman filter.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear;

% Load data
 
trajectory_udu_load;
 
n=1:length(kkkk)
plot(n,kkkk)