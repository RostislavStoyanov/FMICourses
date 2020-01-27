MaxX=300;
MaxY=300;
M=zeros(MaxX,MaxY);
Ax=axes;
image(M');
set(Ax,'YDir','normal');
while (1)
    try
        [X,Y]=ginput(2);
    catch
        clear;
        clc;
        break;
    end
    X1=round(X(1));
    X2=round(X(2));
    Y1=round(Y(1));
    Y2=round(Y(2));
    dxVal=X2-X1;
    dyVal=Y2-Y1;
    RVal=round(sqrt(dxVal^2+dyVal^2));
    color=50;
    CircleBresenham;
    pause(1);
    image(M');
    set(Ax,'YDir','normal');
    hold on;
end