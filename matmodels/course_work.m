syms x1 x2 x3 p4 p6
%double p1 p2 p3 p5

p1 = 8.4e-6;
p2 = 6.6667e-4;
p3 = 1.7778e-5;
p5 = 2;

x2val = (x1 * x1 + p2 * p4 * x1 - x1) / (p1 - x1);
x3val = x1 / (1 + p4);
p6 = (p1 * x2 + x1 * x2 - p5 * x3) / p3 * p4 + x2;

det11 = -x2/p2 + 1/p2 - 2*x1/p2 - p4;
det12 = p1 / p2 - x1 / p2;
det13 = 0;
det21 = -x2/p3;
det22 = - p1 / p3 - x1 / p3 - p4;
det23 = p5/p3;
det31 = 1;
det32 = 0;
det33 = - 1 - p4;

det11 = subs(det11, x2, x2val);
det21 = subs(det21, x2, x2val);

res = det ( [det11 det12 det13; det21 det22 det23; det31 det32 det33] );
res2 = det ( [det11 det12 det13; det21 det22 det23; det31 det32 det33] );

eq = res2 == 0;

fileID = fopen('resulst.txt', 'w');
fileIDcheck = fopen('check.txt', 'w');

%for i = 1.0: 0.1: 2.0
for i = 10.0: 1.0: 10.0
    %p4 = i;
   inner = subs(eq, p4, i);
   x2tmp = subs(x2val, p4, i);
   x3tmp = subs(x3val, p4, i);
   p6tmp = subs(p6, p4, i);
   check = subs(res, p4, i);
   
   fprintf(fileID, 'p4 = %f \n', i);
   fprintf(fileIDcheck, '%f\n', i);
   
   %solution = sym(solve(inner, x1,'IgnoreProperties', true));
   %solution = solve(res, x1);
   solution = solve(inner, x1);
   if (isempty(solution)==false)
       x11 = solution(1, 1);
       x12 = solution(2, 1);
       x13 = solution(3, 1);
       
       
       fprintf(fileID, 'x11 = %f x12 = %f \n', x11, x12);
       if (isAlways(x11 > 0) == true)
         x21 = subs(x2tmp, x1, x11);
         x31 = subs(x3tmp, x1, x11);
         p6res = subs(p6tmp, x1, x11);
         p6res = subs(p6res, x2, x21);
         p6res = subs(p6res, x3, x31);
         fprintf(fileID, 'x21 = %f x31 = %f p6 = %f \n', x21, x31, p6res);
         p6check = (8.4e-6 * x21 + x11 * x21 - 2 * x31) / 1.7778e-5 * i + x21;
         
         check1 = subs(check, x1, x11);
         fprintf(fileIDcheck, '%f %f %f %f\n', x11, x21, x31, p6res);
         
       end
       if (isAlways(x12 > 0))
         x22 = subs(x2tmp, x1, x12);
         x32 = subs(x3tmp, x1, x12);
         p6res = subs(p6tmp, x1, x12);
         p6res = subs(p6res, x2, x22);
         p6res = subs(p6res, x3, x32);
         fprintf(fileID, 'x22 = %f x32 = %f p6 = %f \n', x22, x32, p6res);
         p6check = (8.4e-6 * x22 + x12 * x22 - 2 * x32) / 1.7778e-5 * i + x22;
         
         check2 = subs(check, x1, x12);
         fprintf(fileID, 'check = %f \n', check2);
         fprintf(fileIDcheck, '%f %f %f %f\n', x12, x22, x32, p6res);
       end
       if (isAlways(x13 > 0) == true)
         x23 = subs(x2tmp, x1, x13);
         x33 = subs(x3tmp, x1, x13);
         p6res = subs(p6tmp, x1, x13);
         p6res = subs(p6res, x2, x23);
         p6res = subs(p6res, x3, x33);
         fprintf(fileID, 'x23 = %f x33 = %f p6 = %f \n', x23, x33, p6res);
         p6check = (8.4e-6 * x23 + x13 * x23 - 2 * x33) / 1.7778e-5 * i + x23;
         
         check3 = subs(check, x1, x13);
         fprintf(fileID, 'check = %f \n', check3);
         fprintf(fileIDcheck, '%f %f %f %f\n', x13, x23, x33, p6res);
       end
       fprintf(fileID, '\n');
   end
   
   
end
fclose(fileID);
