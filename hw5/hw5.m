% X_MAX = 100;
% Y_MAX = 200;
% Ax = axes('Position',[0.1,0.1,0.8,0.8],'XLim',[0,X_MAX],'YLim',[0,Y_MAX]);
% hold on;
% 
% NPOINTS = 5;
% 
% try
%   [X,Y] = ginput(NPOINTS);
% catch
%   clear;
%   clc;
% end
% 
% plot(X,Y,'o');
% [s0,s1,s2,s3] = cubic_spline(X,Y);
% plot_cubic_spline(X,s0,s1,s2,s3);
% 

clear;
MaxX=300;
MaxY=300;
nodeSize=5;
color=[1,0,0];
tResolution = 100;
Ax=axes('Position',[0.1,0.1,0.8,0.8],'XLim',[0 MaxX],'YLim',[0 MaxY]);
XBin = zeros(100);
YBin = zeros(100);
i = 0;
B = 0;
while (B~=3)
    i = i + 1;
    [X,Y,B]=ginput(1);
    XBin(i)=round(X);
    YBin(i)=round(Y);
    rectangle('Curvature',[1 1],'Position',[XBin(i)-nodeSize,...
        YBin(i)-nodeSize,2*nodeSize,2*nodeSize],'FaceColor',[0,0,1]);
end
n = i;
XBin = XBin(1:n);
YBin = YBin(1:n);
interpolationSpline;
while(1)
    try
        changeNode
    catch
        clear;
        clc;
        break;
    end
end