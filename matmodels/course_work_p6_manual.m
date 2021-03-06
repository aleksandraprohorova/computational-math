clear all
clear global variables
syms x1 x2 x3 p4 p6

global eq x2val x3val

global det11 det12 det13 det21 det22 det23 det31 det32 det33

global p1 p2 p3 p5

global x1 x2 x3 p4 p6 p6eq

p1 = double(8.4e-6);
p2 = 6.6667e-4;
p2opp = 66667;
p3 = 1.7778e-5;
p3opp = 177780;
p5 = 2;

x2val = (x1 * x1 + p2 * p4 * x1 - x1) / (p1 - x1);
x3val = x1 / (1 + p4);
p6 = (p1 * x2 + x1 * x2 - p5 * x3) / (p3 * p4) + x2;

det11 = -x2*p2opp + 1*p2opp - 2*x1*p2opp - p4;
det12 = p1 * p2opp - x1 * p2opp;
det13 = 0;
det21 = -x2*p3opp;
det22 = - p1 * p3opp - x1 * p3opp - p4;
det23 = p5*p3opp;
det31 = 1;
det32 = 0;
det33 = - 1 - p4;

det11 = subs(det11, x2, x2val);
det21 = subs(det21, x2, x2val);

res = det ( [det11 det12 det13; det21 det22 det23; det31 det32 det33] );
%res = det11*det22*det33 + det12*det23*det31 + det21*det32*det13 - det13*det22*det31 - det12*det21*det33 - det23*det32*det11;

p6eq = (-p1*x2 + x1*x2 - p5*x3 + p4 * p3 * (p6 - x2))*p3opp == 0;

eq = res == 0;

global fileID fileIDcheck fileIDplot1 fileIDplot2 fileIDplot3;

fileIDplot3 = fopen('forplot3.txt', 'w');
fileID = fopen('resulst.txt', 'w');
fileIDcheck = fopen('check.txt', 'w');
fileIDplot1 = fopen('forplot1.txt', 'w');
fileIDplot2 = fopen('forplot2.txt', 'w');

forrange(1.0, 2.0, 0.1);
forrange(2.0, 10.0, 1.0);
forrange(10.0, 100.0, 10.0);
forrange(100.0, 1500.0, 100.0);

fclose(fileID);
fclose(fileIDcheck);
fclose(fileIDplot1);
fclose(fileIDplot2);
fclose(fileIDplot3);

A = load('forplot1.txt');
B = load('forplot2.txt');
C = load('forplot3.txt');

loglog(A(:,1), A(:,2));
hold on;
loglog(B(:,1),B(:,2));
loglog(C(:,1),C(:,2));
hold off;



function[x11, x12, x13, x2tmp, x3tmp] = subsp4(i)
global p4 x1 eq x2val x3val;
inner = subs(eq, p4, i);
solution = solve(inner, x1);
x11 = solution(1);
x12 = solution(2);
x13 = solution(3);

x2tmp = subs(x2val, p4, i);
x3tmp = subs(x3val, p4, i);
%p6tmp = subs(p6, p4, i);
end

function[p6res] = subsx1(x1in, x2tmp, x3tmp, p6tmp)
global fileID fileIDcheck x1 x2 x3 ;
if (isAlways(x1in > 0) == true)
         x2in = subs(x2tmp, x1, x1in);
         x3in = subs(x3tmp, x1, x1in);
         p6in = subs(p6tmp, x1, x1in);
         p6in = subs(p6in, x2, x2in);
         p6in = subs(p6in, x3, x3in);

         %p6res = solve(p6in, p6);
         p6res = p6in;

         fprintf(fileID, 'x2 = %e x3 = %e p6 = %e\n', x2in, x3in, p6res);
         fprintf(fileIDcheck, '%e %e %e %e\n', x1in, x2in, x3in, p6res);

else
    p6res = -1;
end
end

function forrange(left, right, step)

global fileIDcheck fileID fileIDplot1 fileIDplot2 fileIDplot3 p6 p4;
for i = left: step: right

   fprintf(fileID, 'p4 = %e \n', i);
   fprintf(fileIDcheck, '%e\n', i);

   %p6eqp4 = subs(p6eq, p4, i);
   p6eqp4 = subs(p6, p4, i);

   [x11, x12, x13, x2tmp, x3tmp] = subsp4(i);

   fprintf(fileID, 'x1 = %e x1 = %e x1 = %e\n', x11, x12, x13);

   p6res = subsx1(x11, x2tmp, x3tmp, p6eqp4);

   fprintf(fileIDplot1, '%e %e \n', i, p6res);

   p6res = subsx1(x12, x2tmp, x3tmp, p6eqp4);
   fprintf(fileIDplot2, '%e %e \n', i, p6res);

   p6res = subsx1(x13, x2tmp, x3tmp, p6eqp4);
   fprintf(fileIDplot3, '%e %e \n', i, p6res);

   fprintf(fileID, '\n');
end
end
