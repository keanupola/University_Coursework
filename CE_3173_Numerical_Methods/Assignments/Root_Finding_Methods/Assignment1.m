%% Laboratory Assignment #1: Basic Programming with MATLAB, Errors, and Root Finding Methods
%Name: Keanu Anderson-Pola
%UTSA ID: Tro893
%Date: 09/29/2024

%% Problem 1. Arithmetic Operations
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Compute x and y
x = 2^5 / (4^2 + 1);
y = (1 / 7^2 - 1)^(-1);

% Compute N
N = sqrt((x / 6) + (x^4 / 2) + (x^(2/3) / 3) - (6 / (x * y)));

% Compute P
P = x + 2 * y + sin(pi / 4) + N;

% Display results
fprintf('x = %.4f\n', x);
fprintf('y = %.4f\n', y);
fprintf('N = %.4f\n', N);
fprintf('P = %.4f\n', P);

%% Problem 2.1. Plotting
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Define x values
x = linspace(-15, 15, 75);

% Define y(x) and t(x)
y = -8 * x - x.^3 .* sin(x) - 100;
t = cos(x / 4).^2;

% Plot y(x)
figure; % Separate plots into their own windows
plot(x, y);
xlabel('x');
ylabel('y(x)');
title('y(x) = -8x - x^3sin(x) - 100');
grid on;

% Plot t(x)
figure;
plot(x, t);
xlabel('x');
ylabel('t(x)');
title('t(x) = cos^2(x/4)');
grid on;

%% Problem 2.2. Plotting
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Define x and y values
x = linspace(-5, 5, 120);
y = linspace(-10, 10, 60);
[X, Y] = meshgrid(x, y); % 3D plot

% Define z(x, y) and v(x, y)
z = X.^4 + (Y.^2 / 11) - 20 * X .* Y;
v = 3 * sin(Y / 2).^2 .* cos(X / 4).^2;

% Plot z(x, y)
figure;
surf(X, Y, z);
xlabel('x');
ylabel('y');
zlabel('z(x, y)');
title('z(x, y) = X^4 + (Y^2 / 11) - 20XY');
grid on;

% Plot v(x, y)
figure;
surf(X, Y, v);
xlabel('x');
ylabel('y');
zlabel('v(x, y)');
title('v(x, y) = 3sin^2(Y/2)cos^2(X/4)');
grid on;


%% Problem 3. Matrix and Vector Operations
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

%Problem 3.1 Matrix Product:
disp('Problem 3.1')
% Create a 10x10 matrix A with random values between 0 and 1
A = rand(10);

% Create a 10x10 matrix B with all elements equal to 10
B = 10 * ones(10);

% Calculate R
R = A * B;

% Display matrix R
disp(R);


%Problem 3.2 Modification of Matrix Elements:
disp('Problem 3.2')

% Replace 3rd column elements with 3
R(:, 3) = 3;

% Replace 6th row elements with ln(10)
R(6, :) = log(10);

% Replace R(3,9), R(1,5), R(8,2), and R(8,8) with 0
R(3, 9) = 0;
R(1, 5) = 0;
R(8, 2) = 0;
R(8, 8) = 0;

% Display R
disp(R);


%Problem 3.3 Computations with Matrix Elements:
disp('Problem 3.3')

% Calculate the product of the second row of A and ninth column of A
x = A(2, :) * A(:, 9);

% Calculate the ratio of A(10, 2) to B(1, 7)
y = A(10, 2) / B(1, 7);

% Calculate m as m = (x * y) / (sqrt(x) + y)
m = (x * y) / (sqrt(x) + y);

% Display x, y, and m
fprintf('x = %.4f\n', x);
fprintf('y = %.4f\n', y);
fprintf('m = %.4f\n', m);

%Problem 3.4 Matrix Properties:
disp('Problem 3.4')

% Compute D = m * R^T
D = m * R';

% Calculate the determinant of D
det_D = det(D);

% Calculate the rank of D
rank_D = rank(D);

% Calculate the eigenvalues of D
eig_D = eig(D);

% Display results
fprintf('Determinant of D = %.4f\n', det_D);
fprintf('Rank of D = %d\n', rank_D);
disp('Eigenvalues of D:');
disp(eig_D);


%% Problem 4.1 Conditionals, Logical Operators, and Loops
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Define test cases for a, b, and c in 3x3 matrix to loop through
test_cases = [1, -3, 2; 1, -2, 1; 1, 2, 5];

for i = 1:size(test_cases, 1)
    a = test_cases(i, 1);
    b = test_cases(i, 2);
    c = test_cases(i, 3);

    % Calculate discriminant
    discriminant = b^2 - 4*a*c;

    % Use conditional statements to check roots
    if discriminant > 0
        % Real and distinct roots
        root1 = (-b + sqrt(discriminant)) / (2*a);
        root2 = (-b - sqrt(discriminant)) / (2*a);
        fprintf('Case %d: Real and distinct roots: root1 = %.4f, root2 = %.4f\n', i, root1, root2);
    elseif discriminant == 0
        % Real and repeated roots
        root = -b / (2*a);
        fprintf('Case %d: Real and repeated root: root = %.4f\n', i, root);
    elseif discriminant < 0
        % Complex roots
        realPart = -b / (2*a);
        imagPart = sqrt(abs(discriminant)) / (2*a);
        fprintf('Case %d: Complex roots: root1 = %.4f + %.4fi, root2 = %.4f - %.4fi\n', i, realPart, imagPart, realPart, imagPart);
    else
        fprintf('Invalid entry\n');
    end
end

%% Problem 4.2 Conditionals, Logical Operators, and Loops
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Define 5 values for 'a'
a_values = [1, 5, 9, 13, 17];

% Create a vector of 200 equally spaced x values between 0 and 20
x = linspace(0, 20, 200);

% Initialize a y matrix to store the results for each 'a'
y = zeros(length(a_values), length(x));

% Hold on to plot all the curves on the same figure
figure;
hold on;

% Loop through each value of 'a'
for i = 1:length(a_values)
    a = a_values(i);
    
    % Loop through each value of x
    for j = 1:length(x)
        if x(j) <= a
            y(i, j) = sin(x(j) - a)^2; % Piece 1: sin^2(x - a)
        else
            y(i, j) = 7 * log(x(j) + a); % Piece 2: 7 ln(x + a)
        end
    end
    
    % Plot the y(x) for the current 'a'
    plot(x, y(i, :), 'DisplayName', sprintf('a = %d', a_values(i)));
end

% Add labels, title, and grid
xlabel('x');
ylabel('y(x)');
title('Piecewise Function y(x) for a');
legend show; 
grid on;
hold off;


%% Problem 4.3 Conditionals, Logical Operators, and Loops
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Create a 10x10 matrix A where each entry is row number / column number
A = zeros(10); % Initialize the matrix A

for i = 1:10
    for j = 1:10
        A(i, j) = i / j; % Row number divided by column number
    end
end

% Use IF conditional statements and FOR loops to create matrix R
R = A; % Copy matrix A into R
for i = 1:10
    for j = 1:10
        if R(i, j) > 1.1
            R(i, j) = 0; % Replace elements greater than 1.1 with 0
        end
    end
end

% Use IF conditional statements and FOR loops to create matrix T
T = A; % Copy matrix A into T
for i = 1:10
    for j = 1:10
        if T(i, j) < 2.5
            T(i, j) = -8; % Replace elements less than 2.5 with -8
        end
    end
end

% Display A, R, and T
disp('Matrix A:');
disp(A);

disp('Matrix R:');
disp(R);

disp('Matrix T:');
disp(T);

%% Problem 5.1 Root Finding with Bisection Method
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Define f(x)
f = @(x) 2400 * log(2.8e6 / (2.8e6 - 1.4e4 * x)) - 9.81 * x - 450;

% Verify function values at initial bounds
% f_xl = f(100);
% f_xu = f(500);
% fprintf('f(100) = %.4f\n', f_xl);
% fprintf('f(500) = %.4f\n', f_xu);

% Define the initial guesses for xl and xu
xl = 100;
xu = 500;

% Set tolerance and max iterations
tol = 1e-4;
max_iter = 50;

% Initialize arrays for storing results
xr_values = zeros(1, max_iter);
error_values = zeros(1, max_iter);

% Bisection method implementation
for i = 1:max_iter
    xr = (xl + xu) / 2;  % Midpoint
    xr_values(i) = xr;   % Store current approximation
    
    % Calculate absolute approximate percentage error
    if i > 1
        error_values(i) = abs((xr_values(i) - xr_values(i-1)) / xr_values(i)) * 100;
    else
        error_values(i) = NaN;  % No error on the first iteration
    end
    
    if f(xr) == 0 || abs((xu - xl) / xr) < tol
        break;  % Root found or tolerance reached
    elseif f(xl) * f(xr) < 0
        xu = xr;  % Root is in the left interval
    else
        xl = xr;  % Root is in the right interval
    end
end

% Trim unused iterations
xr_values = xr_values(1:i);
error_values = error_values(2:i);

% Display the final approximation of the root
fprintf('Approximate root = %.4f\n', xr);

% Plot the approximate solution vs iterations
figure;
plot(1:i, xr_values, '-o');
xlabel('Iteration');
ylabel('Approximate solution (xr)');
title('Approximate Solution vs Iterations');
grid on;

% Plot the absolute approximate percentage error vs iterations
figure;
plot(2:i, error_values, '-o');
xlabel('Iteration');
ylabel('Absolute Approximate Percentage Error (%)');
title('Error vs Iterations');
grid on;


%% Problem 5.2 Root Finding with Newton-Raphson Method
%Clear previous workspace, screen, and close all figures:
clear
clc
close all

% Define the function f(x) and its derivative f'(x)
f = @(x) 2400 * log(2.8e6 / (2.8e6 - 1.4e4 * x)) - 9.81 * x - 450;
f_prime = @(x) (2400 * 1.4e4) / (2.8e6 - 1.4e4 * x) - 9.81;

% Initial guess
x0 = 150; 
tol = 1e-4;
max_iter = 50;  

% Initialize variables to store results
x_values = zeros(1, max_iter);
error_values = zeros(1, max_iter);

% Newton-Raphson method implementation
for i = 1:max_iter
    % Compute the derivative and check if it's too small
    f_prime_value = f_prime(x0);
 
    % Newton-Raphson formula
    x_new = x0 - f(x0) / f_prime_value;
    
    x_values(i) = x_new;  % Store the current approximation
    
    % Calculate absolute approximate percentage error
    if i > 1
        error_values(i) = abs((x_values(i) - x_values(i-1)) / x_values(i)) * 100;
    else
        error_values(i) = NaN;  % No error on the first iteration
    end
    
    % Check if the tolerance is satisfied
    if abs(f(x_new)) < tol
        break;
    end
    
    % Update for the next iteration
    x0 = x_new;
end

% Trim unused iterations
x_values = x_values(1:i);
error_values = error_values(2:i);

% Display the final approximation of the root
fprintf('Approximate root = %.4f\n', x_new);

% Plot the approximate solution vs iterations
figure;
plot(1:i, x_values);
xlabel('Iteration');
ylabel('Approximate solution (x)');
title('Approximate Solution vs Iterations (Newton-Raphson)');
grid on;

% Plot the absolute approximate percentage error vs iterations
figure;
plot(2:i, error_values);
xlabel('Iteration');
ylabel('Absolute Approximate Percentage Error (%)');
title('Error vs Iterations (Newton-Raphson)');
grid on;



%% Problem 5.3 Plot of Nonlinear Function and Approximate Solution
clear
clc
close all

% Define the function f(x) with element-wise operations
f = @(x) 2400 * log(2.8e6 ./ (2.8e6 - 1.4e4 .* x)) - 9.81 .* x - 450;

% Define x values for the plot (range from 0 to 200)
x_plot = linspace(0, 200, 1000);

% Calculate f(x) for the plot
y_plot = f(x_plot);

% Plot the function
figure;
plot(x_plot, y_plot);
hold on;

% Mark the approximate root found by Newton-Raphson
root = 80.8593; % Approximate root
plot(root, f(root), 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'r'); % Red circle for the root

% Add labels and title
xlabel('x');
ylabel('f(x)');
title('Nonlinear Function and Approximate Solution');
grid on;

% Add legend
legend('f(x)', 'Approximate Root');
hold off;