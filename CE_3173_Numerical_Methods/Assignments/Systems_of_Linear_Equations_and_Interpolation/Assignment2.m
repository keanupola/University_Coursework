%% Laboratory Assignment #2: Systems of Linear Equations and Interpolation
%Name: Keanu Anderson-Pola
%UTSA ID: tro893
%Date: 10/26/2024

%% Problem 1.1. Partial Pivoting On a Given SLE
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Define matrix A and vector b:
A = [-1 4 2 0 0; 18 4 -6 -2 2; -3 9 6 -3 21; 0 10 -2 5 2; -1 3 0 -6 2];
b = [30; -68; -117; 23; -23];

% Augmented Matrix AM:
AM = [A b];

% Display the initial augmented matrix:
fprintf('Initial Augmented Matrix [A|b]:\n');
disp(AM);

% Manual Row Swaps to make the system diagonally dominant:
% Swap row 1 with row 2
AM([1 2], :) = AM([2 1], :);
fprintf('Swapping row 1 with row 2:\n');
disp(AM);

% Swap row 2 with row 4
AM([2 4], :) = AM([4 2], :);
fprintf('Swapping row 2 with row 4:\n');
disp(AM);

% Swap row 4 with row 5
AM([4 5], :) = AM([5 4], :);
fprintf('Swapping row 4 with row 5:\n');
disp(AM);

% Finally, swap row 5 with row 3
AM([5 3], :) = AM([3 5], :);
fprintf('Swapping row 5 with row 3:\n');
disp(AM);

% Final augmented matrix after all manual swaps:
disp('Final Augmented Matrix after Partial Pivoting:');
disp(AM);

%% Problem 1.2. Solution of SLE with the Gauss-Seidel Method
%Clear screen contents.
clc

% Extract matrix A and vector b from the augmented matrix:
A = AM(:, 1:end-1);
b = AM(:, end);

% Initial guess for the solution vector:
x = [10; -5; -5; -8; 20];  

% Number of rows and columns:
[m, n] = size(A);

% Create auxiliary matrix and vectors:
c = zeros(m, n); 
d = zeros(m, 1);

% Define initial error, tolerance, and initial iteration:
ea = 100;
tol = 2;  % 2% tolerance
iter = 1;

% Initialize arrays to store the values at each iteration for each unknown
% (for 1.3)
x1_vals = [];  
x2_vals = [];  
x3_vals = [];  
x4_vals = []; 
x5_vals = []; 

% Initialize arrays to store absolute approximate percentage errors at each
% iteration (for 1.4)
x1_errors = [];
x2_errors = [];
x3_errors = [];
x4_errors = [];
x5_errors = [];

% Gauss-Seidel iterative method:
while ea > tol
    for i = 1:n
        % Compute vector of coefficients:
        d(i) = b(i) / A(i, i);
        
        % Compute coefficient matrix "c":
        for j = 1:m
            if i == j
                c(i, j) = 0;  % Diagonal of matrix "c" is zeros
            else
                c(i, j) = A(i, j) / A(i, i);  % Non-diagonal elements
            end
        end
        
        % Calculate new solution:
        x_new(i) = d(i) - c(i, :) * x(:);
        
        % Calculate the absolute approximate percentage error:
        ea_vect(i) = abs((x_new(i) - x(i)) / x_new(i) * 100);
        
        % Update the solution vector:
        x(i) = x_new(i);
    end
    
    % Store the current values of x1, x2, x3, x4, x5 at this iteration:
    % (for 1.3)
    x1_vals = [x1_vals, x(1)];
    x2_vals = [x2_vals, x(2)];
    x3_vals = [x3_vals, x(3)];
    x4_vals = [x4_vals, x(4)];
    x5_vals = [x5_vals, x(5)];
    
    % Store the current absolute approximate percentage errors:
    % (for 1.4)
    x1_errors = [x1_errors, ea_vect(1)];
    x2_errors = [x2_errors, ea_vect(2)];
    x3_errors = [x3_errors, ea_vect(3)];
    x4_errors = [x4_errors, ea_vect(4)];
    x5_errors = [x5_errors, ea_vect(5)];
    
    % Determine the maximum error across all unknowns:
    ea = max(ea_vect);
    
    % Print only the iteration number and max error:
    fprintf('Iteration #%d Max EA: %.4f\n', iter, ea)
    
    % Update iteration counter:
    iter = iter + 1;
end

% Display the final solution vector:
disp('Final solution vector x:');
disp(x);



%% Problem 1.3. Plot of Solution to SLE
%Close all figures.
close all

% Plot the results from the Gauss-Seidel iterations
iterations = 1:(iter-1);  % Iteration numbers (from Gauss-Seidel loop)

% Plotting the results:
figure;
plot(iterations, x1_vals, '-r', 'LineWidth', 2); hold on;
plot(iterations, x2_vals, '-g', 'LineWidth', 2);
plot(iterations, x3_vals, '-b', 'LineWidth', 2);
plot(iterations, x4_vals, '-m', 'LineWidth', 2);
plot(iterations, x5_vals, '-k', 'LineWidth', 2);

% Add labels, grid, and legend
xlabel('Iterations');
ylabel('Values of Unknowns');
grid on;
legend('x1', 'x2', 'x3', 'x4', 'x5');
title('Plot of Solution to SLE');

% Final plot setup:
hold off;


%% Problem 1.4. Plot of Absolute Approx. Percentage Errors
%Close all figures.
close all

% Plotting the results:
figure;
plot(iterations, x1_errors, '-r', 'LineWidth', 2); hold on;
plot(iterations, x2_errors, '-g', 'LineWidth', 2);
plot(iterations, x3_errors, '-b', 'LineWidth', 2);
plot(iterations, x4_errors, '-m', 'LineWidth', 2);
plot(iterations, x5_errors, '-k', 'LineWidth', 2);

% Add labels, grid, and legend
xlabel('Iterations');
ylabel('Absolute Approximate Percentage Errors');
grid on;
legend('x1 Error', 'x2 Error', 'x3 Error', 'x4 Error', 'x5 Error');
title('Plot of Absolute Approx. Percentage Errors');

% Final plot setup:
hold off;



%% Problem 1.5. Absolute True Percentage Errors
%Close all figures.
close all

% MATLAB's built-in function
x_true = A \ b;

% Display the true solution
disp('true x:');
disp(x_true);

% Compute the absolute true percentage errors for each variable
true_error_x1 = abs((x_true(1) - x1_vals(end)) / x_true(1)) * 100;
true_error_x2 = abs((x_true(2) - x2_vals(end)) / x_true(2)) * 100;
true_error_x3 = abs((x_true(3) - x3_vals(end)) / x_true(3)) * 100;
true_error_x4 = abs((x_true(4) - x4_vals(end)) / x_true(4)) * 100;
true_error_x5 = abs((x_true(5) - x5_vals(end)) / x_true(5)) * 100;

% Display the true percentage errors:
fprintf('Absolute True Percentage Error for x1: %.4f%%\n', true_error_x1);
fprintf('Absolute True Percentage Error for x2: %.4f%%\n', true_error_x2);
fprintf('Absolute True Percentage Error for x3: %.4f%%\n', true_error_x3);
fprintf('Absolute True Percentage Error for x4: %.4f%%\n', true_error_x4);
fprintf('Absolute True Percentage Error for x5: %.4f%%\n', true_error_x5);



%% Problem 2.1 1st-Order Interpolation with Newton’s Divided-Differences
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Data 
v = [0, 3, 4, 6, 10];  
P = [0, 45, 156, 643, 2720];

% Calculation of coefficients (1st order)
b0 = P(4);  
b1 = (P(5) - b0) / (v(5) - v(4)); 

% Estimate power at v = 9
v_est = 9;
P_est = b0 + b1 * (v_est - v(4));

% Display the estimated power
fprintf('Estimated Power at v = %.2f m/s using 1st-order interpolation: %.2f kW\n', v_est, P_est);

% Plot raw data
figure;
plot(v, P, 'o', 'MarkerEdgeColor', 'b', 'MarkerFaceColor', 'b'); hold on;

% Plot estimated value at v = 9
plot(v_est, P_est, 'xr', 'LineWidth', 10);

% Plot the interpolating polynomial
v_full = linspace(0, 10, 100);  % Full range of wind speeds from 0 to 10
P_interp = b0 + b1 * (v_full - v(4));  % 1st-order polynomial over the full range
plot(v_full, P_interp, '--k', 'LineWidth', 1.5);  % Plot the interpolation line

% Add labels, title, and grid 
xlabel('Wind Speed v (m/s)', 'FontSize', 12);
ylabel('Electrical Power P(v) (kW)', 'FontSize', 12);
title('1st-Order Interpolation with Newton’s Divided-Differences', 'FontSize', 12);
grid on;

hold off;


%% Problem 2.2 2nd-Order Interpolation with Newton’s Divided-Differences
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Data
v = [0, 3, 4, 6, 10];  
P = [0, 45, 156, 643, 2720];

% 2nd-order Newton's divided-difference coefficients
b0 = P(3);  
b1 = (P(4) - P(3)) / (v(4) - v(3));  % 1st-order divided difference between v3 and v4
b2 = ((P(5) - P(4)) / (v(5) - v(4)) - b1) / (v(5) - v(3));  % 2nd-order divided difference

% Estimate power at v = 9
v_est = 9;
P_est = b0 + b1 * (v_est - v(3)) + b2 * (v_est - v(3)) * (v_est - v(4));

% Display the estimated power
fprintf('Estimated Power at v = %.2f m/s using 2nd-order interpolation: %.2f kW\n', v_est, P_est);

% Plot raw data
figure;
plot(v, P, 'o', 'MarkerEdgeColor', 'b', 'MarkerFaceColor', 'b'); hold on;

% Plot estimated value at v = 9
plot(v_est, P_est, 'xr', 'LineWidth', 10);

% Plot the interpolating polynomial
v_full = linspace(0, 10, 100);  % Full range of wind speeds from 0 to 10
P_interp = b0 + b1 * (v_full - v(3)) + b2 * (v_full - v(3)) .* (v_full - v(4));  % 2nd-order polynomial
plot(v_full, P_interp, '--k', 'LineWidth', 1.5);  % Plot the interpolation line

% Add labels, title, and grid
xlabel('Wind Speed v (m/s)', 'FontSize', 12);
ylabel('Electrical Power P(v) (kW)', 'FontSize', 12);
title('2nd-Order Interpolation with Newton’s Divided-Differences', 'FontSize', 12);
grid on;

hold off;




%% Problem 2.3 3rd-Order Interpolation with Newton’s Divided-Differences
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Data
v = [0, 3, 4, 6, 10];
P = [0, 45, 156, 643, 2720];

% 3rd-order Newton's divided-difference coefficients
b0 = P(2);  % P(v2) corresponding to v = 3
b1 = (P(3) - P(2)) / (v(3) - v(2));  % 1st-order divided difference between v2 and v3
b2 = ((P(4) - P(3)) / (v(4) - v(3)) - b1) / (v(4) - v(2));  % 2nd-order divided difference
b3 = (((P(5) - P(4)) / (v(5) - v(4)) - (P(4) - P(3)) / (v(4) - v(3))) / (v(5) - v(3)) - b2) / (v(5) - v(2));  % 3rd-order divided difference

% Estimate power at v = 9
v_est = 9;
P_est = b0 + b1 * (v_est - v(2)) + b2 * (v_est - v(2)) * (v_est - v(3)) + b3 * (v_est - v(2)) * (v_est - v(3)) * (v_est - v(4));

% Display the estimated power
fprintf('Estimated Power at v = %.2f m/s using 3rd-order interpolation: %.2f kW\n', v_est, P_est);

% Plot raw data
figure;
plot(v, P, 'o', 'MarkerEdgeColor', 'b', 'MarkerFaceColor', 'b'); hold on;

% Plot estimated value at v = 9
plot(v_est, P_est, 'xr', 'LineWidth', 10);

% Plot the interpolating polynomial
v_full = linspace(0, 10, 100);  % Full range of wind speeds from 0 to 10
P_interp = b0 + b1 * (v_full - v(2)) + b2 * (v_full - v(2)) .* (v_full - v(3)) + b3 * (v_full - v(2)) .* (v_full - v(3)) .* (v_full - v(4));
plot(v_full, P_interp, '--k', 'LineWidth', 1.5);  % Plot the interpolation line

% Add labels, title, and grid
xlabel('Wind Speed v (m/s)', 'FontSize', 12);
ylabel('Electrical Power P(v) (kW)', 'FontSize', 12);
title('3rd-Order Interpolation with Newton’s Divided-Differences', 'FontSize', 12);
grid on;

hold off;



%% Problem 3.1 1st-order Lagrange Interpolation
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Data set
x = [5, 12];  
y = [1.609, 2.485];

% Evaluation of Lagrange polynomial for x = 10
x_est = 10;
y_est = (x_est - x(2)) / (x(1) - x(2)) * y(1) + ...
        (x_est - x(1)) / (x(2) - x(1)) * y(2);

% Display the estimated value
fprintf('Estimated y at x = %.2f using 1st-order Lagrange interpolation: %.4f\n', x_est, y_est);

% Plot
plot(x, y, 'ob', 'LineWidth', 2); hold on;
plot(x_est, y_est, 'xr', 'LineWidth', 10);
x_full = linspace(5, 20, 100);
y_interp = (x_full - x(2)) ./ (x(1) - x(2)) * y(1) + ...
           (x_full - x(1)) ./ (x(2) - x(1)) * y(2);
plot(x_full, y_interp, '--k', 'LineWidth', 1.5);
xlabel('x', 'FontSize', 12);
ylabel('y(x)', 'FontSize', 12);
title('1st-Order Lagrange Interpolation', 'FontSize', 12);
grid on;
hold off;



%% Problem 3.2 2nd-order Lagrange Interpolation
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Data set
x = [5, 12, 16];  
y = [1.609, 2.485, 2.773];

% Evaluation of Lagrange polynomial for x = 10
x_est = 10;
y_est = (x_est - x(2)) * (x_est - x(3)) / ((x(1) - x(2)) * (x(1) - x(3))) * y(1) + ...
        (x_est - x(1)) * (x_est - x(3)) / ((x(2) - x(1)) * (x(2) - x(3))) * y(2) + ...
        (x_est - x(1)) * (x_est - x(2)) / ((x(3) - x(1)) * (x(3) - x(2))) * y(3);

% Display the estimated value
fprintf('Estimated y at x = %.2f using 2nd-order Lagrange interpolation: %.4f\n', x_est, y_est);

% Plot
plot(x, y, 'ob', 'LineWidth', 2); hold on;
plot(x_est, y_est, 'xr', 'LineWidth', 10);
x_full = linspace(5, 20, 100);
y_interp = (x_full - x(2)) .* (x_full - x(3)) ./ ((x(1) - x(2)) * (x(1) - x(3))) * y(1) + ...
           (x_full - x(1)) .* (x_full - x(3)) ./ ((x(2) - x(1)) * (x(2) - x(3))) * y(2) + ...
           (x_full - x(1)) .* (x_full - x(2)) ./ ((x(3) - x(1)) * (x(3) - x(2))) * y(3);
plot(x_full, y_interp, '--k', 'LineWidth', 1.5);
xlabel('x', 'FontSize', 12);
ylabel('y(x)', 'FontSize', 12);
title('2nd-Order Lagrange Interpolation', 'FontSize', 12);
grid on;
hold off;



%% Problem 3.3 3rd-order Lagrange Interpolation
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Data set
x = [5, 12, 16, 20];  
y = [1.609, 2.485, 2.773, 2.996];

% Evaluation of Lagrange polynomial for x = 10
x_est = 10;
y_est = (x_est - x(2)) * (x_est - x(3)) * (x_est - x(4)) / ((x(1) - x(2)) * (x(1) - x(3)) * (x(1) - x(4))) * y(1) + ...
        (x_est - x(1)) * (x_est - x(3)) * (x_est - x(4)) / ((x(2) - x(1)) * (x(2) - x(3)) * (x(2) - x(4))) * y(2) + ...
        (x_est - x(1)) * (x_est - x(2)) * (x_est - x(4)) / ((x(3) - x(1)) * (x(3) - x(2)) * (x(3) - x(4))) * y(3) + ...
        (x_est - x(1)) * (x_est - x(2)) * (x_est - x(3)) / ((x(4) - x(1)) * (x(4) - x(2)) * (x(4) - x(3))) * y(4);

% Display the estimated value
fprintf('Estimated y at x = %.2f using 3rd-order Lagrange interpolation: %.4f\n', x_est, y_est);

% Plot
plot(x, y, 'ob', 'LineWidth', 2); hold on;
plot(x_est, y_est, 'xr', 'LineWidth', 10);
x_full = linspace(5, 20, 100);
y_interp = (x_full - x(2)) .* (x_full - x(3)) .* (x_full - x(4)) ./ ((x(1) - x(2)) * (x(1) - x(3)) * (x(1) - x(4))) * y(1) + ...
           (x_full - x(1)) .* (x_full - x(3)) .* (x_full - x(4)) ./ ((x(2) - x(1)) * (x(2) - x(3)) * (x(2) - x(4))) * y(2) + ...
           (x_full - x(1)) .* (x_full - x(2)) .* (x_full - x(4)) ./ ((x(3) - x(1)) * (x(3) - x(2)) * (x(3) - x(4))) * y(3) + ...
           (x_full - x(1)) .* (x_full - x(2)) .* (x_full - x(3)) ./ ((x(4) - x(1)) * (x(4) - x(2)) * (x(4) - x(3))) * y(4);
plot(x_full, y_interp, '--k', 'LineWidth', 1.5);
xlabel('x', 'FontSize', 12);
ylabel('y(x)', 'FontSize', 12);
title('3rd-Order Lagrange Interpolation', 'FontSize', 12);
grid on;
hold off;



%% Problem 4.1 2nd-order Interpolation via SLE
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Given Data (t P(t))
A = [0, 2.00; 2, 2.56; 6, 0.00; 8, -1.34; 10, -1.72; 16, 0.90; 20, 0.74; 22, 0.00];
% Point of interest:
t_est = 18.5;
% Initialization of order of interpolation
Order = 2;
R = zeros(Order+1, Order+1);
b = zeros(Order+1, 1);
f = 0;

% Perform interpolation
for k = Order:size(A,1)
    if A(k,1) >= t_est
        % Formulation of coefficient matrix R and vector of constants b
        for i = 1:Order+1
            for j = 1:Order+1
                R(i,j) = A(k+1-i,1)^(Order+1-j);
            end
            b(i) = A(k+1-i,2);
        end
        % Solution of system of equations via the inverse matrix
        coef = R\b;
        
        % Evaluation of interpolating polynomial
        for i = 1:size(coef,1)
            f = f + coef(i)*t_est^(Order+1-i);
        end
        
        fprintf('P(%.2f) = %.4f\n', t_est, f);
        break;
    end
end

% Plot
plot(t_est, f, 'rx', 'LineWidth', 10); hold on;
plot(A(:,1), A(:,2), 'ob', 'LineWidth', 2);
t_full = linspace(min(A(:,1)), max(A(:,1)), 100);
P_interp = zeros(size(t_full));
for p = 1:length(t_full)
    for i = 1:size(coef,1)
        P_interp(p) = P_interp(p) + coef(i) * t_full(p)^(Order+1-i);
    end
end
plot(t_full, P_interp, '--k', 'LineWidth', 1);
xlabel('Time t (s)');
ylabel('Position P(t) (cm)');
title('2nd-order Interpolation via SLE', 'FontSize', 12);
grid on;



%% Problem 4.2 3rd-order Interpolation via SLE
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Given Data (t P(t))
A = [0, 2.00; 2, 2.56; 6, 0.00; 8, -1.34; 10, -1.72; 16, 0.90; 20, 0.74; 22, 0.00];
% Point of interest:
t_est = 18.5;
% Initialization of order of interpolation
Order = 3;
R = zeros(Order+1, Order+1);
b = zeros(Order+1, 1);
f = 0;

% Perform interpolation
for k = Order:size(A,1)
    if A(k,1) >= t_est
        % Form matrix R and vector b
        for i = 1:Order+1
            for j = 1:Order+1
                R(i,j) = A(k+1-i,1)^(Order+1-j);
            end
            b(i) = A(k+1-i,2);
        end
        % Solution of system of equations via the inverse matrix
        coef = R\b;
        
        % Evaluation of interpolating polynomial
        for i = 1:size(coef,1)
            f = f + coef(i)*t_est^(Order+1-i);
        end
        
        fprintf('P(%.2f) = %.4f\n', t_est, f);
        break;
    end
end

% Plot
plot(t_est, f, 'rx', 'LineWidth', 10); hold on;
plot(A(:,1), A(:,2), 'ob', 'LineWidth', 2);
t_full = linspace(min(A(:,1)), max(A(:,1)), 100);
P_interp = zeros(size(t_full));
for p = 1:length(t_full)
    for i = 1:size(coef,1)
        P_interp(p) = P_interp(p) + coef(i) * t_full(p)^(Order+1-i);
    end
end
plot(t_full, P_interp, '--k', 'LineWidth', 1);
legend('Interpolated Value', 'Given Data', 'Interpolating Polynomial');
xlabel('Time t (s)');
ylabel('Position P(t) (cm)');
title('3rd-order Interpolation via SLE', 'FontSize', 12);
grid on;

%% Problem 4.3 7th-order Interpolation via SLE
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Given Data (t P(t))
A = [0, 2.00; 2, 2.56; 6, 0.00; 8, -1.34; 10, -1.72; 16, 0.90; 20, 0.74; 22, 0.00];
% Point of interest:
t_est = 18.5;
% Initialization of order of interpolation
Order = 7;
R = zeros(Order+1, Order+1);
b = zeros(Order+1, 1);
f = 0;

% Formulation of coefficient matrix R and vector of constants b
for i = 1:Order+1
    for j = 1:Order+1
        R(i,j) = A(i,1)^(Order+1-j);
    end
    b(i) = A(i,2);
end

% Solution of system of equations via the inverse matrix
coef = R\b;

% Evaluation of interpolating polynomial
for i = 1:size(coef,1)
    f = f + coef(i)*t_est^(Order+1-i);
end
fprintf('P(%.2f) = %.4f\n', t_est, f);

% Plot
plot(t_est, f, 'rx', 'LineWidth', 10); hold on;
plot(A(:,1), A(:,2), 'ob', 'LineWidth', 2);
t_full = linspace(min(A(:,1)), max(A(:,1)), 100);
P_interp = zeros(size(t_full));
for p = 1:length(t_full)
    for i = 1:size(coef,1)
        P_interp(p) = P_interp(p) + coef(i) * t_full(p)^(Order+1-i);
    end
end
plot(t_full, P_interp, '--k', 'LineWidth', 1);
legend('Interpolated Value', 'Given Data', 'Interpolating Polynomial');
xlabel('Time t (s)');
ylabel('Position P(t) (cm)');
title('7th-order Interpolation via SLE', 'FontSize', 12);
grid on;


%% Problem 4.4 Absolute True Percentage Errors
%Close all figures.
close all

% True value
P_true = 1.15;

% Estimates from Problems 4.1, 4.2, and 4.3
P_4_1 = 0.9788;  
P_4_2 = 1.3134;  
P_4_3 = 1.1184;  

% Calculate absolute true percentage errors
error_4_1 = abs((P_true - P_4_1) / P_true) * 100;
error_4_2 = abs((P_true - P_4_2) / P_true) * 100;
error_4_3 = abs((P_true - P_4_3) / P_true) * 100;

% Display the errors
fprintf('Absolute True Percentage Error for Problem 4.1: %.2f%%\n', error_4_1);
fprintf('Absolute True Percentage Error for Problem 4.2: %.2f%%\n', error_4_2);
fprintf('Absolute True Percentage Error for Problem 4.3: %.2f%%\n', error_4_3);
