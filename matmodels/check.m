syms x1 x2 x3 p1 p2 p3 p4 p5 p6

p1 = 8.4e-6;
p2 = 6.6667e-4;
p3 = 1.7778e-5;
p5 = 2;

det11 = -x2/p2 + 1/p2 - 2*x1/p2 - p4;
det12 = p1 / p2 - x1 / p2;
det13 = 0;
det21 = -x2/p3;
det22 = - p1 / p3 - x1 / p3 - p4;
det23 = p5/p3;
det31 = 1;
det32 = 0;
det33 = - 1 - p4;

res = det ( [det11 det12 det13; det21 det22 det23; det31 det32 det33] );

fid = fopen('check.txt', 'r');
fres = fopen('check_res.txt', 'w');

while ~feof(fid)
    i = fscanf(fid, "%f", 1);
    
    x11 = fscanf(fid, "%f", 1);
    x21 = fscanf(fid, "%f", 1);
    x31 = fscanf(fid, "%f", 1);
    p61 = fscanf(fid, "%f", 1);
    
    x12 = fscanf(fid, "%f", 1);
    x22 = fscanf(fid, "%f", 1);
    x32 = fscanf(fid, "%f", 1);
    p62 = fscanf(fid, "%f", 1);
    %fscanf(fid, '%f %f %f %f\n', x11, x21, x31, p61);
    %fscanf(fid, '%f %f %f %f\n', x12, x22, x32, p62);
    check1 = subs(res, p4, i);
    check1 = subs(check1, x1, x11);
    check1 = subs(check1, x2, x21);
    check1 = subs(check1, x3, x31);
    check1 = subs(check1, p6, p61);
    fprintf(fres, 'p4 = %f,  ', i);
    fprintf(fres, '1: %f, ', check1); 
    
    check2 = subs(res, p4, i);
    check2 = subs(check2, x1, x12);
    check2 = subs(check2, x2, x22);
    check2 = subs(check2, x3, x32);
    check2 = subs(check2, p6, p62);
    fprintf(fres, '2: %f \n', check2); 
    
end


fclose(fid);
fclose(fres);

