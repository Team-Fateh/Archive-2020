opts = spreadsheetImportOptions("NumVariables", 4);

% Specify sheet and range
opts.Sheet = "Sheet1";
opts.DataRange = "A1:D7284";

% Specify column names and types
opts.VariableNames = ["VarName1", "VarName2", "VarName3", "VarName4"];
opts.SelectedVariableNames = ["VarName1", "VarName2", "VarName3", "VarName4"];
opts.VariableTypes = ["double", "double", "double", "double"];

% Import the data
datafatehtest2 = readtable("C:\Users\Aman Arora\Desktop\datafatehtest2.xlsx", opts, "UseExcel", false);
datafatehtest2=table2array(datafatehtest2);
clc
for i = 1:7284
    t(i) = datafatehtest2(i,1); 
    x(i) = datafatehtest2(i,2);
    y(i) = datafatehtest2(i,3);
    z(i) = datafatehtest2(i,4);
end
 n = medfilt1(y);
% subplot(2,1,1)
% plot(t,y)
% subplot(2,1,2)
% plot(t,n)
% subplot(3,1,3)
% plot(h)
ft = dsp.FFT();
Y = ft(y);
N=ft(n);
subplot(2,2,1)
plot(t,y)
 subplot(2,2,2)
 plot(100/2*linspace(0,1,21022), 2*abs(Y(1:21022)/1024))
 subplot(2,2,3)
 plot(t,n)
 subplot(2,2,4)
 plot(100/2*linspace(0,1,21022), 2*abs(N(1:21022)/1024))