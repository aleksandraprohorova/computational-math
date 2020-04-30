clear all
syms x1 x2 x3 p1 p2 p3 p4 p5 p6

p1 = double(8.4e-6);
p2 = 6.6667e-4;
p2opp = 66667;
p3 = 1.7778e-5;
p3opp = 177780;
p5 = 2;

det11 = -x2*p2opp + 1*p2opp - 2*x1*p2opp - p4;
det12 = p1 * p2opp - x1 * p2opp;
det13 = 0;
det21 = -x2*p3opp;
det22 = - p1 * p3opp - x1 * p3opp - p4;
det23 = p5*p3opp;
det31 = 1;
det32 = 0;
det33 = - 1 - p4;

res =  ( [det11 det12 det13; det21 det22 det23; det31 det32 det33] );
matrix = [det11 det12 det13; det21 det22 det23; det31 det32 det33];
detcheck = det ( [-1 det12 det13; 0 det22 det23; 0 det32 det33] );

eq1 = (p1*x2 - x1*x2 + x1 - x1^2) / p2 - p4*x1;
eq2 = (-p1*x2 - x1*x2 + p5*x3)/p3 + p4 * (p6 - x2);
eq3 = x1 - x3 - p4*x3;


fid = fopen('check.txt', 'r');
fres = fopen('check_res.txt', 'w');

while ~feof(fid)
    i = fscanf(fid, "%e", 1);
    
    x11 = fscanf(fid, "%e", 1);
    x21 = fscanf(fid, "%e", 1);
    x31 = fscanf(fid, "%e", 1);
    p61 = fscanf(fid, "%e", 1);
    
    x12 = fscanf(fid, "%e", 1);
    x22 = fscanf(fid, "%e", 1);
    x32 = fscanf(fid, "%e", 1);
    p62 = fscanf(fid, "%e", 1);
    %fscanf(fid, '%f %f %f %f\n', x11, x21, x31, p61);
    %fscanf(fid, '%f %f %f %f\n', x12, x22, x32, p62);
    check1 = subs(res, p4, i);
    check1 = subs(check1, x1, x11);
    check1 = subs(check1, x2, x21);
    check1 = subs(check1, x3, x31);
    check1 = subs(check1, p6, p61);
    check1tmp = det(check1);
    fprintf(fres, 'p4 = %f \n', i);
    fprintf(fres, '1:\n det = %f\n', check1tmp); 
    eigenvalues = eig(check1);
    fprintf(fres, 'eigenvalues: %f % f %f\n', eigenvalues(1), eigenvalues(2), eigenvalues(3));
    
    checkeq1 = subs(eq1, p4, i);
    checkeq1 = subs(checkeq1, x1, x11);
    checkeq1 = subs(checkeq1, x2, x21);
    checkeq1 = subs(checkeq1, x3, x31);
    checkeq1 = subs(checkeq1, p6, p61);
    fprintf(fres, 'System: %f, ', checkeq1); 
    
    checkeq1 = subs(eq2, p4, i);
    checkeq1 = subs(checkeq1, x1, x11);
    checkeq1 = subs(checkeq1, x2, x21);
    checkeq1 = subs(checkeq1, x3, x31);
    checkeq1 = subs(checkeq1, p6, p61);
    fprintf(fres, '%f, ', checkeq1); 
    
    checkeq1 = subs(eq3, p4, i);
    checkeq1 = subs(checkeq1, x1, x11);
    checkeq1 = subs(checkeq1, x2, x21);
    checkeq1 = subs(checkeq1, x3, x31);
    checkeq1 = subs(checkeq1, p6, p61);
    fprintf(fres, ', %f\n', checkeq1); 
    
    detcheck1 = subs(detcheck, p4, i);
    detcheck1 = subs(detcheck1, x1, x11);
    detcheck1 = subs(detcheck1, x2, x21);
    detcheck1 = subs(detcheck1, x3, x31);
    detcheck1 = subs(detcheck1, p6, p61);
    fprintf(fres, 'detcheck: %f\n\n', detcheck1);
    
    check2 = subs(res, p4, i);
    check2 = subs(check2, x1, x12);
    check2 = subs(check2, x2, x22);
    check2 = subs(check2, x3, x32);
    check2 = subs(check2, p6, p62);
    check2tmp = det(check2);
    fprintf(fres, '2:\n det = %f \n', check2tmp); 
    eigenvalues = eig(check2);
    fprintf(fres, 'eigenvalues: %f % f %f\n', eigenvalues(1), eigenvalues(2), eigenvalues(3));
    
    checkeq2 = subs(eq1, p4, i);
    checkeq2 = subs(checkeq2, x1, x12);
    checkeq2 = subs(checkeq2, x2, x22);
    checkeq2 = subs(checkeq2, x3, x32);
    checkeq2 = subs(checkeq2, p6, p62);
    fprintf(fres, 'System: %f, ', checkeq2); 
    
    checkeq2 = subs(eq2, p4, i);
    checkeq2 = subs(checkeq2, x1, x12);
    checkeq2 = subs(checkeq2, x2, x22);
    checkeq2 = subs(checkeq2, x3, x32);
    checkeq2 = subs(checkeq2, p6, p62);
    fprintf(fres, '%f, ', checkeq2); 
    
    checkeq2 = subs(eq3, p4, i);
    checkeq2 = subs(checkeq2, x1, x12);
    checkeq2 = subs(checkeq2, x2, x22);
    checkeq2 = subs(checkeq2, x3, x32);
    checkeq2 = subs(checkeq2, p6, p62);
    fprintf(fres, '%f \n', checkeq2); 
    
    detcheck2 = subs(detcheck, p4, i);
    detcheck2 = subs(detcheck2, x1, x12);
    detcheck2 = subs(detcheck2, x2, x22);
    detcheck2 = subs(detcheck2, x3, x32);
    detcheck2 = subs(detcheck2, p6, p62);
    fprintf(fres, 'detcheck: %f\n\n', detcheck2);
    
    
    
end


fclose(fid);
fclose(fres);


