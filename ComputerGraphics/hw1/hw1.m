MaxX = 50;
MaxY = 45;

M = zeros(MaxX,MaxY);
Ax = axes;
image(M');
set(Ax, 'YDir', 'normal');

color = 50;
colorAround = 30;

while(true)
    
    try
        [X,Y] = ginput(2);
    catch
        clear;
        clc;
        break;
    end
    
    X1 = round(X(1));
    Y1 = round(Y(1));

    X2 = round(X(2));
    Y2 = round(Y(2));

    M(X1,Y1) = color;
    M(X2,Y2) = color;
    
    image(M');
    set(Ax, 'YDir', 'normal');

    bersenhamLineModified;
    
    image(M');
    set(Ax, 'YDir', 'normal');
    hold on
    
end